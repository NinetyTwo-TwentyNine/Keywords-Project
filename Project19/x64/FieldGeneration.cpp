#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

namespace Project19 {

    const int DIR_HORIZONTAL = 0, DIR_VERTICAL = 1;
    const int DIR_UP = 0, DIR_DOWN = 1, DIR_LEFT = 2, DIR_RIGHT = 3;

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

    void initialMatrixSetup(vector<vector<char>>& matrix, vector <vector<vector<bool>>>& originsArr, vector <vector<vector<bool>>>& directionArr)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                matrix[i][j] = '-';
                originsArr[i][j] = vector <bool>{ false, false, false, false };
                directionArr[i][j] = vector <bool>{ false, false };
            }
        }
    }

    void sortWords(vector<string>& words)
    {
        string duplicate;
        bool shouldSort = true;
        while (shouldSort)
        {
            shouldSort = false;
            for (int i = 1; i < words.size(); i++)
            {
                if (words[i - 1].length() > words[i].length())
                {
                    shouldSort = true;
                    duplicate = words[i];
                    words[i] = words[i - 1];
                    words[i - 1] = duplicate;
                }
            }
        }
    }

    void limitWords(vector<string>& words, int matrix_side)
    {
        sortWords(words);

        const int ARR_SIZE = matrix_side;
        for (int i = words.size() - 1; i > 0; i--)
        {
            if (words[i].length() < 2 || words[i].length() >= ARR_SIZE)
            {
                string duplicate = words[i];
                words[i] = words[words.size() - 1];
                words[words.size() - 1] = duplicate;
                words.pop_back();
                sortWords(words);
            }
        }
    }

    void insertTheWordIntoMatrix(vector<vector<char>>& matrix, string word, pair <int, int> origin, int direction, vector <vector<vector<bool>>>& originsArr, vector <vector<vector<bool>>>& directionArr)
    {
        int x = origin.first, y = origin.second;
        originsArr[y][x][direction] = true;
        for (int i = 0; i < word.length(); i++)
        {
            matrix[y][x] = word[i];
            if (direction == DIR_RIGHT || direction == DIR_LEFT)
            {
                directionArr[y][x][DIR_HORIZONTAL] = true;
                if (direction == DIR_RIGHT)
                {
                    x = x + 1;
                }
                if (direction == DIR_LEFT)
                {
                    x = x - 1;
                }
            }
            if (direction == DIR_UP || direction == DIR_DOWN)
            {
                directionArr[y][x][DIR_VERTICAL] = true;
                if (direction == DIR_UP)
                {
                    y = y - 1;
                }
                if (direction == DIR_DOWN)
                {
                    y = y + 1;
                }
            }
        }
    }

    vector<vector<int>> getDirectionsFromPos(vector<vector<char>>& matrix, vector <vector<vector<bool>>>& directionArr, pair <int, int> pos, string word)
    {
        vector <int> dirfrompos(2);
        int x = pos.first, y = pos.second;
        vector<vector<int>> possibleDirsFromPos;
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == matrix[y][x])
            {
                bool left_possible = true, right_possible = true, up_possible = true, down_possible = true;

                if (x >= i + 1)
                {
                    if (matrix[y][x - i - 1] != '-')
                    {
                        right_possible = false;
                    }
                }
                if (x + word.length() - i < matrix.size())
                {
                    if (matrix[y][x + word.length() - i] != '-')
                    {
                        right_possible = false;
                    }
                }

                if (x + i + 1 < matrix.size())
                {
                    if (matrix[y][x + i + 1] != '-')
                    {
                        left_possible = false;
                    }
                }
                if (x + i >= word.length())
                {
                    if (matrix[y][x + i - word.length()] != '-')
                    {
                        left_possible = false;
                    }
                }

                if (y + i + 1 < matrix.size())
                {
                    if (matrix[y + i + 1][x] != '-')
                    {
                        up_possible = false;
                    }
                }
                if (y + i >= word.length())
                {
                    if (matrix[y + i - word.length()][x] != '-')
                    {
                        up_possible = false;
                    }
                }

                if (y >= i + 1)
                {
                    if (matrix[y - i - 1][x] != '-')
                    {
                        down_possible = false;
                    }
                }
                if (y + word.length() - i < matrix.size())
                {
                    if (matrix[y + word.length() - i][x] != '-')
                    {
                        down_possible = false;
                    }
                }

                for (int j = 0; j < word.length(); j++)
                {
                    int right_x = x + j - i;
                    if (right_x < 0 || right_x >= matrix.size())
                    {
                        right_possible = false;
                    }
                    else
                    {
                        if (directionArr[y][right_x][DIR_HORIZONTAL])
                        {
                            right_possible = false;
                        }
                        if (matrix[y][right_x] != word[j] && matrix[y][right_x] != '-')
                        {
                            right_possible = false;
                        }
                        if (y > 0 && j != i)
                        {
                            if (matrix[y - 1][right_x] != '-')
                            {
                                right_possible = false;
                            }
                        }
                        if (y < matrix.size() - 1 && j != i)
                        {
                            if (matrix[y + 1][right_x] != '-')
                            {
                                right_possible = false;
                            }
                        }
                    }

                    int left_x = x - j + i;
                    if (left_x < 0 || left_x >= matrix.size())
                    {
                        left_possible = false;
                    }
                    else
                    {
                        if (directionArr[y][left_x][DIR_HORIZONTAL])
                        {
                            left_possible = false;
                        }
                        if (matrix[y][left_x] != word[j] && matrix[y][left_x] != '-')
                        {
                            left_possible = false;
                        }
                        if (y > 0 && j != i)
                        {
                            if (matrix[y - 1][left_x] != '-')
                            {
                                left_possible = false;
                            }
                        }
                        if (y < matrix.size() - 1 && j != i)
                        {
                            if (matrix[y + 1][left_x] != '-')
                            {
                                left_possible = false;
                            }
                        }
                    }

                    int down_y = y + j - i;
                    if (down_y < 0 || down_y >= matrix.size())
                    {
                        down_possible = false;
                    }
                    else
                    {
                        if (directionArr[down_y][x][DIR_VERTICAL])
                        {
                            down_possible = false;
                        }
                        if (matrix[down_y][x] != word[j] && matrix[down_y][x] != '-')
                        {
                            down_possible = false;
                        }
                        if (x > 0 && j != i)
                        {
                            if (matrix[down_y][x - 1] != '-')
                            {
                                down_possible = false;
                            }
                        }
                        if (x < matrix.size() - 1 && j != i)
                        {
                            if (matrix[down_y][x + 1] != '-')
                            {
                                down_possible = false;
                            }
                        }
                    }

                    int up_y = y - j + i;
                    if (up_y < 0 || up_y >= matrix.size())
                    {
                        up_possible = false;
                    }
                    else
                    {
                        if (directionArr[up_y][x][DIR_VERTICAL])
                        {
                            up_possible = false;
                        }
                        if (matrix[up_y][x] != word[j] && matrix[up_y][x] != '-')
                        {
                            up_possible = false;
                        }
                        if (x > 0 && j != i)
                        {
                            if (matrix[up_y][x - 1] != '-')
                            {
                                up_possible = false;
                            }
                        }
                        if (x < matrix.size() - 1 && j != i)
                        {
                            if (matrix[up_y][x + 1] != '-')
                            {
                                up_possible = false;
                            }
                        }
                    }
                }

                dirfrompos[0] = i;
                if (left_possible)
                {
                    dirfrompos[1] = DIR_LEFT;
                    possibleDirsFromPos.push_back(dirfrompos);
                }
                if (right_possible)
                {
                    dirfrompos[1] = DIR_RIGHT;
                    possibleDirsFromPos.push_back(dirfrompos);
                }
                if (up_possible)
                {
                    dirfrompos[1] = DIR_UP;
                    possibleDirsFromPos.push_back(dirfrompos);
                }
                if (down_possible)
                {
                    dirfrompos[1] = DIR_DOWN;
                    possibleDirsFromPos.push_back(dirfrompos);
                }
            }
        }
        return possibleDirsFromPos;
    }

    vector<pair<int, int>> getPossibleSpots(vector<vector<char>>& matrix, vector <vector<vector<bool>>>& directionArr, string word)
    {
        vector <pair<int, int>> possibleSpots;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] != '-')
                {
                    pair <int, int> pos{ j, i };
                    if (getDirectionsFromPos(matrix, directionArr, pos, word).size() > 0)
                    {
                        possibleSpots.push_back(pos);
                    }
                }
            }
        }
        return possibleSpots;
    }

    void actualMatrixSetup(vector<vector<char>>& matrix, vector<string> words, vector <vector<vector<bool>>>& originsArr, vector <vector<vector<bool>>>& directionArr)
    {
        if (words.empty())
        {
            return;
        }

        srand(time(0));
        const int ARR_SIZE = matrix.size();

        string first_word = words[words.size() - 1];
        int first_x = ARR_SIZE / 2, first_y = ARR_SIZE / 2;
        int first_dir = rand() % 4;
        if (first_dir == DIR_UP)
        {
            first_y += first_word.size() / 2;
        }
        if (first_dir == DIR_DOWN)
        {
            first_y -= first_word.size() / 2;
        }
        if (first_dir == DIR_LEFT)
        {
            first_x += first_word.size() / 2;
        }
        if (first_dir == DIR_RIGHT)
        {
            first_x -= first_word.size() / 2;
        }
        pair <int, int> first_pos{ first_x, first_y };
        insertTheWordIntoMatrix(matrix, first_word, first_pos, first_dir, originsArr, directionArr);

        int chosen, dir;
        pair <int, int> pos;
        vector <pair<int, int>> possibleSpots;
        vector <vector<int>> possibleDirs;
        for (int i = 0; i < words.size() - 1; i++)
        {
            possibleSpots = getPossibleSpots(matrix, directionArr, words[i]);
            if (possibleSpots.size() > 0)
            {
                chosen = rand() % possibleSpots.size();
                pos = possibleSpots[chosen];
                possibleDirs = getDirectionsFromPos(matrix, directionArr, pos, words[i]);
                chosen = rand() % possibleDirs.size();
                dir = possibleDirs[chosen][1];
                if (dir == DIR_LEFT)
                {
                    pos.first += possibleDirs[chosen][0];
                }
                if (dir == DIR_RIGHT)
                {
                    pos.first -= possibleDirs[chosen][0];
                }
                if (dir == DIR_UP)
                {
                    pos.second += possibleDirs[chosen][0];
                }
                if (dir == DIR_DOWN)
                {
                    pos.second -= possibleDirs[chosen][0];
                }
                insertTheWordIntoMatrix(matrix, words[i], pos, dir, originsArr, directionArr);
            }
        }
    }
}