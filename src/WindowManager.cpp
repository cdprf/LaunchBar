#include <windows.h>
#include "WindowManager.h"

WindowManager::WindowManager() : m_mainWindow(nullptr) {}
WindowManager::~WindowManager() {}

BOOL WindowManager::InitInstance(HINSTANCE hInstance, LPCTSTR lpCmdLine) {
    // Eski InitInstance fonksiyonundaki ana pencere oluşturma kodları buraya taşınabilir
    // Şimdilik sadece iskelet
    return TRUE;
}


LRESULT CALLBACK WindowManager::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static bool dragging = false;
    static POINT dragOffset = {0, 0};
    switch (message) {
        case WM_MBUTTONDOWN: {
            SetCapture(hWnd);
            dragging = true;
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);
            dragOffset = pt;
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (dragging && (wParam & MK_MBUTTON)) {
                POINT pt;
                GetCursorPos(&pt);
                // Ekran koordinatında barı taşı
                SetWindowPos(hWnd, NULL, pt.x - dragOffset.x, pt.y - dragOffset.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                // Pozisyonu kaydetmek için burada değişken güncellenebilir
                return 0;
            }
            break;
        }
        case WM_MBUTTONUP: {
            if (dragging) {
                ReleaseCapture();
                dragging = false;
                // Son pozisyonu kaydet
                RECT rect;
                GetWindowRect(hWnd, &rect);
                extern int gBarPosX, gBarPosY;
                gBarPosX = rect.left;
                gBarPosY = rect.top;
                extern BOOL SavePrefs();
                SavePrefs();
                return 0;
            }
            break;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}


LRESULT CALLBACK WindowManager::ButtonWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static bool dragging = false;
    static POINT dragOffset = {0, 0};
    switch (message) {
        case WM_MBUTTONDOWN: {
            SetCapture(hWnd);
            dragging = true;
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);
            dragOffset = pt;
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (dragging && (wParam & MK_MBUTTON)) {
                POINT pt;
                GetCursorPos(&pt);
                SetWindowPos(hWnd, NULL, pt.x - dragOffset.x, pt.y - dragOffset.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                // Pozisyonu kaydetmek için burada değişken güncellenebilir
                return 0;
            }
            break;
        }
        case WM_MBUTTONUP: {
            if (dragging) {
                ReleaseCapture();
                dragging = false;
                // Son pozisyonu kaydet
                POINT pt;
                GetWindowRect(hWnd, (LPRECT)&pt);
                // Burada pozisyonu ayarlara yazabilirsiniz
                return 0;
            }
            break;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND WindowManager::GetMainWindow() const {
    return m_mainWindow;
}
