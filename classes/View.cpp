#include"View.h"
#include "ConsoleLib.h"
#include "EventDispatcher.h"

View::View() 
	: mIsExit(false)
{}

View::~View()
{}

void View::start()
{
	char currentCode = 0;
	
	while (!mIsExit)
	{
		draw( { 0 ,0 }, isDirtyTransform() );

		HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
		SetConsoleCursorPosition(hStdOut, { (SHORT)0, (SHORT)24 });

		EventDispatcher::getInstance()->update( this );

		update();

		Pool::getInstance()->checkRefs();

		//Sleep(16);
	}

	mIsExit = false;
}

void View::stop()
{
	mIsExit = true;
}

