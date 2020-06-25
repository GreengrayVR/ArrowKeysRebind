#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

HHOOK hHook = 0;

#define I_KEY 0x49
#define J_KEY 0x4A
#define K_KEY 0x4B
#define L_KEY 0x4C

static bool LeftAltHold = false;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (p->vkCode == VK_CAPITAL)
        {

            if (wParam == 256)
            {
                LeftAltHold = true;
            }
            else if (wParam == 257)
            {
                LeftAltHold = false;
            }
            return 1;
        }

        if (p->vkCode == J_KEY && LeftAltHold)
        {
            if (wParam == 256)
            {
                keybd_event(VK_LEFT, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
                keybd_event(VK_LEFT, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            }
            return 1;
        }

        if (p->vkCode == K_KEY && LeftAltHold)
        {
            if (wParam == 256)
            {
                keybd_event(VK_DOWN, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
                keybd_event(VK_DOWN, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            }
            return 1;
        }

        if (p->vkCode == L_KEY && LeftAltHold)
        {
            if (wParam == 256)
            {
                keybd_event(VK_RIGHT, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
                keybd_event(VK_RIGHT, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            }
            return 1;
        }

        if (p->vkCode == I_KEY && LeftAltHold)
        {
            if (wParam == 256)
            {
                keybd_event(VK_UP, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
                keybd_event(VK_UP, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            }
            return 1;
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, hThisInstance, NULL);

    if (hHook == NULL)
        return 1;

    MSG messages;

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
 
    return messages.wParam;
}