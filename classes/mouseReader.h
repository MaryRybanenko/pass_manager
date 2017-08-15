#ifndef __MOUSER_H__
#define __MOUSER_H__

#include<Windows.h>
#include <iostream>

struct sMouse
{
	COORD mousePos;
	bool lButton;
	bool rButton;

	bool leftDown;
	bool leftUp;

	bool rightDown;
	bool rightUp;

	sMouse() :
		mousePos{ 0, 0 },
		lButton(false),
		rButton(false)
	{}
};

#endif

