#include "SigninForm.h"
#include <Windows.h>

using namespace Project19;

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew SigninForm);
    return 0;
}