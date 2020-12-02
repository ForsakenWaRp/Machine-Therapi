#include "Console.h"

namespace Utility {

	static Console g_Console;

	void Console::Allocate() {

		if (isAllocated) {
			return;
		}

		/* AllocConsole(); 
		
		Since allocconsole detected by same anticheats we prefer to use custom one 
		credits - unex 2020
		*/
		Bypass::AllocConsole();
		
		SetConsoleTitleA("DEBUG CONSOLE");

		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);

		outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		const int width = 110;
		const int height = 30;

		// Add some more scrolling
		COORD size;
		size.X = width;
		size.Y = height * 10;
		SetConsoleScreenBufferSize(outputHandle, size);

		// Resize our console window
		SMALL_RECT rect;
		rect.Left = rect.Top = 0;
		rect.Right = width - 1;
		rect.Bottom = height - 1;
		SetConsoleWindowInfo(outputHandle, TRUE, &rect);

		isAllocated = true;
	}

	void Console::DeAllocate() {

		if (!isAllocated) {
			return;
		}

		FreeConsole();
	}

	void Console::SetTitle(const std::string& title) {

		SetConsoleTitleA(title.c_str());
	}

	/*
	const std::string Console::GetTitle() {

		TCHAR title[MAX_PATH];
		GetConsoleTitle(title, MAX_PATH);

		// BURAYI COZEMED�M SENDE MAK
		return title;
	} */

	void Console::Clear() {

		system("cls");
	}

	void Console::SetTextColor(const int color) {

		if (!isAllocated) {
			return;
		}

		CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
		GetConsoleScreenBufferInfo(outputHandle, &screenBuffer);

		WORD attributes = screenBuffer.wAttributes & ~FOREGROUND_RED & ~FOREGROUND_GREEN & ~FOREGROUND_BLUE & ~FOREGROUND_INTENSITY;
		attributes |= color;

		SetConsoleTextAttribute(outputHandle, attributes);
	}

	void Console::SetBackgroundColor(const int color) {

		if (!isAllocated) {
			return;
		}

		CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
		GetConsoleScreenBufferInfo(outputHandle, &screenBuffer);

		WORD attributes = screenBuffer.wAttributes & ~BACKGROUND_RED & ~BACKGROUND_GREEN & ~BACKGROUND_BLUE & ~BACKGROUND_INTENSITY;
		attributes |= color;

		SetConsoleTextAttribute(outputHandle, attributes);
	}

	Console* GetConsole() {

		return &g_Console;
	}
}