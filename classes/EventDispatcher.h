#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include <iostream>
#include <list>
#include "container.h"


class EventDispatcher
{
public:
	static EventDispatcher* getInstance();

	void update( Container* container );

private:
	EventDispatcher();
	~EventDispatcher();
	static EventDispatcher* mInstance;

	void dispatchKeyEvent(unsigned char c, Container* container);
	void dispatchMouseEvent(sMouse* event, Container* container);

	void sortChildren(Container* container, std::list<Container*>& resultList);

	bool mIsMouseLeftButtonPressed;
	bool mIsMouseRigthButtonPressed;
	COORD prevPosition;

};



#endif
