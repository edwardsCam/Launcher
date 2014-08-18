#include <iostream>
#include <Windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
    LPTSTR title = 0;

        GetWindowText(hwnd, title, sizeof(title));
        std::cout << "Window Name: " << std::endl;

        return true;
}

int main(int argc, char* argv[]) // SUBSYSTEM:CONSOLE
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow) // SUBSYSTEM:WINDOWS
{
        EnumWindows(EnumWindowsProc, NULL);

        std::cin.get();
        return 0;
}