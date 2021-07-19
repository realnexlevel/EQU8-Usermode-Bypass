#include <Windows.h>

__declspec(dllexport) LRESULT CALLBACK OurCallbackFunction(int code, WPARAM wparam, LPARAM lparam) {
	MSG* msg = (MSG*)lparam;

	if (msg->message == (WM_USER + 432)) {
		MessageBoxA(0, "Injected", "Success", MB_OK);
	}

	return CallNextHookEx(0, code, wparam, lparam);
}