#include "mouseReader.h"
#include "ConsoleLib.h"

/*
void Mouse::readMouseState()
{
	Mouse localVal;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	DWORD dwOldMode, dwMode, dwNumRead;

	// Сохраняем текущий режим ввода для будущего восстановления при выходе из программы
	GetConsoleMode(hStdIn, &dwOldMode);
	// Включаем получение событий от мыши
	dwMode = ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdIn, dwMode);

	INPUT_RECORD irInBuf[128];
	char strBuffer[20];
	COORD mousePos;
	DWORD mouseButtonState;

	while (1)
	{
		ReadConsoleInput(hStdIn, irInBuf, 128, &dwNumRead);
		for (DWORD i = 0; i < dwNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
				// События мыши
			case MOUSE_EVENT:
				// Координаты мыши
				mousePos = irInBuf[i].Event.MouseEvent.dwMousePosition;

				// Мышь переместили
				if (irInBuf[i].Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
				{
					sprintf(strBuffer, "[%2d, %2d]", mousePos.X, mousePos.Y);
					WriteStr(0, 0, strBuffer);
					localVal.mousePos.X = mousePos.X;
					localVal.mousePos.Y = mousePos.Y;
				}
				// Состояние кнопок мыши
				mouseButtonState = irInBuf[i].Event.MouseEvent.dwButtonState;

				// Нажата левая кнопка мыши
				if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					lButton = true;
					std::cout << "Left";
				}
				else if (mouseButtonState == RIGHTMOST_BUTTON_PRESSED)
				{
					rButton = true;
					std::cout << "Right";

				}
			}
		}
	}
}
*/