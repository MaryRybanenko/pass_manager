#include "EventDispatcher.h"
#include <conio.h>
#include "ConsoleLib.h"

EventDispatcher* EventDispatcher::mInstance = new EventDispatcher;

EventDispatcher::EventDispatcher()
	: mIsMouseLeftButtonPressed(false)
	, mIsMouseRigthButtonPressed(false)
	, prevPosition({ 0,0 })
{
}

EventDispatcher::~EventDispatcher()
{
}

EventDispatcher* EventDispatcher::getInstance()
{
	return mInstance;
}

void EventDispatcher::update(Container* container)
{
	DWORD countEvent = 0;
	GetNumberOfConsoleInputEvents(hStdIn, &countEvent);

	sMouse mouseCurrent;

	if (countEvent)
	{
		INPUT_RECORD irInBuf[128];
		DWORD dwNumRead;
		ReadConsoleInput(hStdIn, irInBuf, 128, &dwNumRead);
		for (DWORD i = 0; i < dwNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case MOUSE_EVENT:
			{
				auto mouseButtonState = irInBuf[i].Event.MouseEvent.dwButtonState;
				auto eventFlag = irInBuf[i].Event.MouseEvent.dwEventFlags;
				bool hasChanged = false;

				if (mIsMouseLeftButtonPressed != static_cast< bool >(mouseButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
				{
					mIsMouseLeftButtonPressed = static_cast< bool >(mouseButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
					hasChanged = true;

					mouseCurrent.lButton = mIsMouseLeftButtonPressed;

					mouseCurrent.leftDown = mIsMouseLeftButtonPressed;
					mouseCurrent.leftUp = !mIsMouseLeftButtonPressed;
				}
				else
				{
					mouseCurrent.leftDown = false;
					mouseCurrent.leftUp = false;
				}

				if (mIsMouseRigthButtonPressed != static_cast< bool >(mouseButtonState & RIGHTMOST_BUTTON_PRESSED))
				{
					mIsMouseRigthButtonPressed = static_cast< bool >(mouseButtonState & RIGHTMOST_BUTTON_PRESSED);
					hasChanged = true;

					mouseCurrent.rButton = mIsMouseRigthButtonPressed;

					mouseCurrent.rightDown = mIsMouseRigthButtonPressed;
					mouseCurrent.rightUp = !mIsMouseRigthButtonPressed;
				}
				else
				{
					mouseCurrent.rightDown = false;
					mouseCurrent.rightUp = false;
				}

				if (prevPosition != irInBuf[i].Event.MouseEvent.dwMousePosition)
				{
					prevPosition = irInBuf[i].Event.MouseEvent.dwMousePosition;
					hasChanged = true;
				}

				mouseCurrent.mousePos = prevPosition;

				if (hasChanged)
				{
					dispatchMouseEvent(&mouseCurrent, container);
				}
			}
			break;
			case KEY_EVENT:
			{
				if (irInBuf[i].Event.KeyEvent.bKeyDown)
				{
					unsigned char currentCode = irInBuf[i].Event.KeyEvent.uChar.AsciiChar;
					dispatchKeyEvent(currentCode, container);
				}
			}
			break;
			}
		}
	}
}

void EventDispatcher::dispatchKeyEvent(unsigned char c, Container* container)
{
	std::list<Container*> sortContainerList;
	sortChildren(container, sortContainerList);

	for (auto cont : sortContainerList)
	{
		if (cont->dispatchKeyEvent(c))
		{
			break;
		}
	}
}

void EventDispatcher::dispatchMouseEvent(sMouse* event, Container* container)
{
	if (event->leftUp)
	{
		std::list<Container*> sortContainerList;
		sortChildren(container, sortContainerList);

		for (auto cont : sortContainerList)
		{
			if (cont->dispatchMouseEvent(event))
			{
				break;
			}
		}
	}
}

void EventDispatcher::sortChildren(Container* container, std::list<Container*>& resultList)
{
	if (container->isVisible())
	{
		for (auto child : container->getChildren())
		{
			sortChildren(child, resultList);
		}

		resultList.push_back(container);
	}
}