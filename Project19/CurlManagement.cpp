#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>

#include <curl/curl.h>

using namespace std;

namespace Project19 {

    const int CURL_REQUEST_TYPE_LOGIN = 0, CURL_REQUEST_TYPE_REGISTER = 1, CURL_REQUEST_TYPE_STATISTICS_GET = 2, CURL_REQUEST_TYPE_STATISTICS_UPLOAD_VICTORY = 3, CURL_REQUEST_TYPE_STATISTICS_UPLOAD_DEFEAT = 4,
              CURL_REQUEST_TYPE_PUZZLES_GET = 5, CURL_REQUEST_TYPE_PUZZLE_FROMFILE = 6, CURL_REQUEST_TYPE_PUZZLE_UPLOADFILE = 7;

    vector<string> createVectorFromContent(string content)
    {
        vector <string> words;

        unsigned int next_space, next_paragraph;
        string currentword = "";
        while (!content.empty())
        {
            while (content[0] == ' ')
            {
                content.replace(0, 1, "");
            }
            if (content.empty())
            {
                continue;
            }

            if (content.find(" ") != -1)
            {
                currentword = content.substr(0, content.find(" "));
            }
            else
            {
                currentword = content.substr(0, content.length());
            }
            content.replace(content.find(currentword), currentword.length(), "");
            words.push_back(currentword);
        }

        return words;
    }

    void parseJsonString(vector<string>& result, const string& jsonString) {
        size_t start = jsonString.find("[");
        size_t end = jsonString.find("]");

        if (start == string::npos || end == string::npos || start >= end) {
            throw(exception("Invalid JSON format."));
        }

        string namesSection = jsonString.substr(start + 1, end - start - 1);
        size_t pos = 0;
        while ((pos = namesSection.find("\"")) != string::npos) {
            size_t endQuote = namesSection.find("\"", pos + 1);
            if (endQuote == string::npos) break;
            result.push_back(namesSection.substr(pos + 1, endQuote - pos - 1));
            namesSection = namesSection.substr(endQuote + 1);
        }
    }

    void parseJsonString(vector<pair<string, int>>& result, const string& jsonString) {
        string key;
        int value = 0;
        bool isKey = true;

        for (size_t i = 0; i < jsonString.size(); i++) {
            if (jsonString[i] == '{' || jsonString[i] == '}' || jsonString[i] == ' ' || jsonString[i] == ',') {
                continue;
            }
            if (jsonString[i] == '"') {
                // Extract key
                size_t end = jsonString.find('"', i + 1);
                if (end == string::npos) break;

                string extracted = jsonString.substr(i + 1, end - i - 1);
                i = end;  // Move index to end of extracted string

                if (isKey) {
                    key = extracted;
                    isKey = false;
                }
            }
            else if (jsonString[i] == ':') {
                // Extract integer value
                size_t start = i + 1;
                while (start < jsonString.size() && !isdigit(jsonString[start]) && jsonString[start] != '-') {
                    start++;  // Skip any spaces or colons
                }

                size_t end = start;
                while (end < jsonString.size() && (isdigit(jsonString[end]) || jsonString[end] == '-')) {
                    end++;  // Capture full number
                }

                value = stoi(jsonString.substr(start, end - start));
                result.emplace_back(key, value);
                i = end - 1;
                isKey = true;
            }
        }
    }

    void parseJsonString(vector<vector<vector<bool>>>& directionsArr, vector<vector<vector<bool>>>& originsMatrix,
                         vector<vector<char>>& gameMatrix, vector<int>& gameParams, const string& jsonStr) {

        size_t pos = 0;

        // Helper function to extract an array
        auto extractArray = [&](const string& key) -> string {
            size_t start = jsonStr.find(key, pos);
            if (start == string::npos)
                throw(exception("Key not found."));
            start = jsonStr.find("[", start);
            if (start == string::npos)
                throw(exception("Malformed JSON: No opening bracket."));

            int bracketCount = 1;
            size_t end = start + 1;
            while (bracketCount > 0 && end < jsonStr.size()) {
                if (jsonStr[end] == '[') bracketCount++;
                if (jsonStr[end] == ']') bracketCount--;
                end++;
            }
            return jsonStr.substr(start, end - start);
        };

        auto parse3DBoolArray = [&](const string& arrayStr, int expectedInnerSize) -> vector<vector<vector<bool>>> {
            vector<vector<vector<bool>>> result;
            vector<vector<bool>> outer;
            vector<bool> inner;
            stringstream ss(arrayStr);
            char ch;

            int closedBracketCount = 0;

            while (ss >> ch) {
                if (ch == '[' || ch == ']') {
                    if (ch == '[')
                        closedBracketCount = 0;
                    else
                        closedBracketCount++;

                    if (!inner.empty()) {
                        if (inner.size() != expectedInnerSize)
                            throw exception("Invalid inner array size.");
                        outer.push_back(inner);
                        inner.clear();
                    }
                    if (closedBracketCount == 2)
                    {
                        if (!outer.empty()) {
                            result.push_back(outer);
                            outer.clear();
                        }
                    }
                }
                else if (ch == 't') { // Expecting 'true'
                    closedBracketCount = 0;
                    char buffer[3];  // Buffer for "rue"
                    ss.read(buffer, 3);
                    if (strncmp(buffer, "rue", 3) == 0) {
                        inner.push_back(true);
                    }
                    else {
                        throw exception("Invalid boolean value (expected 'true').");
                    }
                }
                else if (ch == 'f') { // Expecting 'false'
                    closedBracketCount = 0;
                    char buffer[4];  // Buffer for "alse"
                    ss.read(buffer, 4);
                    if (strncmp(buffer, "alse", 4) == 0) {
                        inner.push_back(false);
                    }
                    else {
                        throw exception("Invalid boolean value (expected 'false').");
                    }
                }
            }
            return result;
        };

        auto parse2DCharArray = [&](const string& arrayStr) -> vector<vector<char>> {
            vector<vector<char>> result;
            vector<char> row;

            stringstream ss(arrayStr);
            char ch;

            while (ss >> ch) {
                if (ch == '"') continue;
                if (ch == '[') {
                    row.clear();
                }
                else if (ch == ']') {
                    if (!row.empty()) result.push_back(row);
                    row.clear();
                }
                else if (ch != ',') {
                    row.push_back(ch);
                }
            }
            return result;
        };

        auto parse1DIntArray = [&](const string& arrayStr) -> vector<int> {
            vector<int> result;
            stringstream ss(arrayStr);
            char ch;
            int num;

            while (ss >> ch) {
                if (isdigit(ch) || ch == '-') {
                    ss.putback(ch);
                    ss >> num;
                    result.push_back(num);
                }
            }
            return result;
        };

        // Parse each array
        directionsArr = parse3DBoolArray(extractArray("\"directionsArr\":"), 2);
        originsMatrix = parse3DBoolArray(extractArray("\"originsMatrix\":"), 4);
        gameMatrix = parse2DCharArray(extractArray("\"gameMatrix\":"));
        gameParams = parse1DIntArray(extractArray("\"gameParams\":"));

        //cout << "Parsing completed successfully!\n";
    }

    extern size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
        std::string* response = static_cast<std::string*>(userdata);
        size_t totalSize = size * nmemb;
        response->append(ptr, totalSize);
        return totalSize;
    }

    typedef void (*ResponseCallback)(const string&);

    static class curlClient {
    public:
        curlClient(void)
        {

        }
        const string CURL_SERVER_LINK = "http://www.example.com/"; // Switch to the API link

        string getRequestLink(int type)
        {
            switch (type)
            {
            case CURL_REQUEST_TYPE_LOGIN: return CURL_SERVER_LINK + "user/login/";
            case CURL_REQUEST_TYPE_REGISTER: return CURL_SERVER_LINK + "user/register/";
            case CURL_REQUEST_TYPE_STATISTICS_GET: return CURL_SERVER_LINK + "user/statistics/";
            case CURL_REQUEST_TYPE_STATISTICS_UPLOAD_VICTORY: return CURL_SERVER_LINK + "user/statistics/update/1/";
            case CURL_REQUEST_TYPE_STATISTICS_UPLOAD_DEFEAT: return CURL_SERVER_LINK + "user/statistics/update/-1/";
            case CURL_REQUEST_TYPE_PUZZLES_GET: return CURL_SERVER_LINK + "keyword/names/";
            case CURL_REQUEST_TYPE_PUZZLE_FROMFILE: return CURL_SERVER_LINK + "keyword/fromfile/";
            case CURL_REQUEST_TYPE_PUZZLE_UPLOADFILE: return CURL_SERVER_LINK + "keyword/uploadfile/";
            default: throw(exception("Unidentified request ID."));
            }
        }

        void performCurlRequest(ResponseCallback callback, int requestType, vector<pair<string, string>> jsonArgs) {
            CURL* curl = curl_easy_init();
            if (curl) {
                string response;

                string json_data = "{";
                for (pair<string, string> kvPair : jsonArgs)
                {
                    if (kvPair.first.empty())
                    {
                        throw(exception("Supplied with an empty key."));
                    }
                    json_data += "\"" + kvPair.first + "\": \"" + kvPair.second + "\"";
                    if (jsonArgs[jsonArgs.size() - 1] != kvPair)
                    {
                        json_data += ", ";
                    }
                }
                json_data += "}";

                //cout << "Resulting json data: " << json_data << endl;

                struct curl_slist* headers = nullptr;
                headers = curl_slist_append(headers, "Content-Type: application/json");
                headers = curl_slist_append(headers, "Accept: application/json");

                curl_easy_setopt(curl, CURLOPT_URL, getRequestLink(requestType).c_str());
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
                curl_easy_setopt(curl, CURLOPT_POST, 1L);

                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
                //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

                // Set up the write callback function
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

                // Pass response string to write function
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                curl_easy_perform(curl);
                curl_easy_cleanup(curl);

                // Call the user-supplied callback function with the response
                if (callback) {
                    callback(response);
                }
            }
            else
            {
                throw(exception("Failed attempt to initialize cURL."));
            }
        }
    };
}