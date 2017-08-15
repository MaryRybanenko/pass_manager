#include "Box.h"
#include <iomanip>

Box::Box()
{
}

Box::~Box()
{
}

void Box::onDraw(COORD offset)
{
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
		SetConsoleCursorPosition(hStdOut, { (SHORT)offset.X, (SHORT)++inerY });
		std::cout << Vert;
		for (int i = 0; i < inerW; i++)
		{
			std::cout << ' ';
		}
		std::cout << Vert;
	}

	SetConsoleCursorPosition(hStdOut, {(SHORT)offset.X, (SHORT)++inerY});
	std::cout << LeftBottom;
	for (int i = 0; i < inerW; i++)
	{
		std::cout << Horz;
	}
	std::cout << RightBottom;
}