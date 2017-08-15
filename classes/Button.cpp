#include "Button.h"
#include "ConsoleLib.h"
#include <iomanip>

Button::Button()
	: mTimePressed( 0 )
{
}

Button::~Button()
{
}

void Button::onDraw(COORD offset)
{
	bool isPressed = mTimePressed != 0 && ( clock() - mTimePressed ) < 500;

	if (isPressed)
	{
		SetColor(ConsoleColor::Black, ConsoleColor::White);
	}
	else
	{
		SetColor(ConsoleColor::White, ConsoleColor::Black);
	}

	const unsigned char LeftTop = 201;
	const unsigned char Horz = 205;
	const unsigned char Vert = 186;
	const unsigned char RightTop = 187;
	const unsigned char LeftBottom = 200;
	const unsigned char RightBottom = 188;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int inerY = offset.Y;
	int inerW = getWidth() - 2;
	int inerH = getHeight() - 2;
	SetConsoleCursorPosition(hStdOut, {(SHORT)offset.X, (SHORT)inerY});

	std::cout << LeftTop;
	for (int i = 0; i < inerW; i++)
	{
		std::cout << Horz;
	}
	std::cout << RightTop;
	
	for (int i = 0; i < inerH; i++)
	{
		if (isPressed)
		{
			SetColor(ConsoleColor::Black, ConsoleColor::White);
		}
		else
		{
			SetColor(ConsoleColor::White, ConsoleColor::Black);
		}
		SetConsoleCursorPosition(hStdOut, { (SHORT)offset.X, (SHORT)++inerY });
		std::cout << Vert;

		SetColor(ConsoleColor::White, ConsoleColor::Black);
		for (int i = 0; i < inerW; i++)
		{
			std::cout << ' ';
		}
		std::cout << Vert;
	}

	if (isPressed)
	{
		SetColor(ConsoleColor::Black, ConsoleColor::White);
	}
	else
	{
		SetColor(ConsoleColor::White, ConsoleColor::Black);
	}

	SetConsoleCursorPosition(hStdOut, {(SHORT)offset.X, (SHORT)++inerY});
	std::cout << LeftBottom;
	for (int i = 0; i < inerW; i++)
	{
		std::cout << Horz;
	}
	std::cout << RightBottom;

	SetColor(ConsoleColor::White, ConsoleColor::Black);
}

bool Button::dispatchMouseEvent(sMouse* event)
{
	bool result = isContainCoord(event->mousePos);
	
	if ( result )
	{
		if (mMouseListener)
		{
			result = mMouseListener(this, event);
		}
		else
		{
			result = false;
		}

		if (result)
		{
			mTimePressed = clock();
			setDirty();
		}
	}
	
	return result;
}

void Button::onUpdate()
{
	if (mTimePressed > 0)
	{
		if ((clock() - mTimePressed) > 300)
		{
			mTimePressed = 0;
			setDirtyTransform();
		}
	}
}