#include <Windows.h>
#include <iostream>

int main() {
	HMODULE lib = LoadLibraryA("example.dll");
	if (!lib) {
		std::cout << " [-] Failed to load target module!" << std::endl;

		std::cin.get();

		return -1;
	}

	HOOKPROC proc = reinterpret_cast<HOOKPROC>(GetProcAddress(lib, "?OurCallbackFunction@@YA_JH_K_J@Z"));
	if (!proc) {
		std::cout << " [-] Failed to get exported function address!" << std::endl;

		std::cin.get();

		return -1;
	}

	HWND GameWindow = FindWindowA(0, "PortalWars  ");
	if (!GameWindow) {
		std::cout << " [-] Failed to get game window!" << std::endl;

		std::cin.get();

		return -1;
	}

	DWORD ProcessID = 0, ThreadID = GetWindowThreadProcessId(GameWindow, &ProcessID);
	if (!ThreadID) {
		std::cout << " [-] Failed to get thread id!" << std::endl;

		std::cin.get();

		return -1;
	}

	HHOOK hook = SetWindowsHookExW(WH_GETMESSAGE, proc, lib, ThreadID);
	if (!hook) {
		std::cout << " [-] Failed to place hook!" << std::endl;

		std::cin.get();

		return -1;
	}

	PostThreadMessageW(ThreadID, WM_USER + 432, 0, reinterpret_cast<LPARAM>(hook));

	std::cout << " [+] DLL injected into process!" << std::endl;

	std::cin.get();

	return 0;
}