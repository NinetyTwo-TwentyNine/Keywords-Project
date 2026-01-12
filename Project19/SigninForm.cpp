#include "SigninForm.h"
#include <Windows.h>

using namespace Project19;

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    CURLcode globalInit = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (globalInit != CURLE_OK) {
        MessageBox::Show("Curl global init failed!");
        return 1;
    }

    /*
    AllocConsole();  // Create a new console window
    freopen("CONOUT$", "w", stdout);  // Redirect stdout to console
    freopen("CONOUT$", "w", stderr);  // Redirect stderr to console
    cout << "Console is now attached!" << endl;
    */

    Application::Run(gcnew SigninForm);

    curl_global_cleanup();
    return 0;
}