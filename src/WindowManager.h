#pragma once
#include <windows.h>
#include "resource.h"
#include "utils.h"

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    BOOL InitInstance(HINSTANCE hInstance, LPCTSTR lpCmdLine);
    static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK ButtonWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    HWND GetMainWindow() const;

private:
    HWND m_mainWindow;
    // Diğer pencere yönetimiyle ilgili değişkenler buraya eklenebilir
};
