#include <windows.h>

void registerHotkey() {
    RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, 0x42); // ALT + B
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            // Обработка горячей клавиши
        }
    }
}