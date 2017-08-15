#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "container.h"

class Button : public Container
{
public:
	Button();
	virtual ~Button() override;

	virtual bool dispatchMouseEvent(sMouse* event) override;

protected:
	virtual void onDraw(COORD offset);


	virtual void onUpdate() override;
private:

	int mTimePressed;
};



#endif
