#include <windows.h>
#include "stdio.h"
#include <stdlib.h>

HHOOK KeyboardHook;

BOOL shift=FALSE;
BOOL ctrl=FALSE;
BOOL alt=FALSE;
BOOL tab=FALSE;
BOOL caps=FALSE;

LPTSTR mapCodeToText(int code){
    if (code==VK_F12) {return "IntelliJ";}
    if (code==VK_F1) {return "Firefox";}
    if (code==VK_F3) {return "Chrome";}
    if (code==VK_F4) {return "cmd";}
    if (code==VK_F7) {return "MINGW";}
    if (code==VK_F6) {return "Sky";}
    if (code==VK_F5) {return "PyCharm";}
    printf("ret null");
    return NULL;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd,  LPARAM lParam){
    char cWindow[1000];
    GetWindowTextA(hwnd,cWindow,sizeof(cWindow));
    printf("%s\r\n", cWindow);
    if(strstr(cWindow, (LPTSTR)lParam)) {
        SetForegroundWindow(hwnd);
        printf("%s_", cWindow);
        return FALSE;
    }
    return TRUE;
}
void press(int code, BOOL up){
    INPUT input;
    WORD vkey = code;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = vkey;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    if (up)
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void pressCtrlCode(int code){
    press(VK_LCONTROL, FALSE);
    press(code,TRUE);
    press(VK_LCONTROL,TRUE);
}

LRESULT CALLBACK HookProcedure2(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
    if (nCode == HC_ACTION)
    {
        printf("code %lu\n", p->vkCode);
        LPTSTR te= mapCodeToText(p->vkCode);
        if(te != NULL && GetAsyncKeyState(VK_LSHIFT)){
            press(VK_LSHIFT,TRUE);
            printf("%s mapped to %lu\n", te, p->vkCode);
            EnumWindows(&EnumWindowsProc, (LPARAM)te);

            return -1;
        }
        else{
            if (p->vkCode==VK_F11)
            {
                press(VK_LSHIFT,TRUE);
                press(VK_LWIN,TRUE);
                return -1;
            }
            if (p->vkCode==VK_F8)
            {
                press(VK_LSHIFT,TRUE);
                press(VK_LMENU,FALSE);
                press(VK_TAB,TRUE);
                pressCtrlCode('T');
                return -1;
            }
            if (p->vkCode==VK_F2)
            {
                press(VK_LSHIFT,TRUE);
                UnhookWindowsHookEx(KeyboardHook);
                exit(0);
                return -1;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


int main (void) {
    printf("start\n");
    KeyboardHook = SetWindowsHookEx(
            WH_KEYBOARD_LL,
            HookProcedure2,
            GetModuleHandle(NULL),
            0
            );
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    printf("unhook\n");
    UnhookWindowsHookEx(KeyboardHook);
    return 0;
}
