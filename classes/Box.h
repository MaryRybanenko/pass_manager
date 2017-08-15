#ifndef __BOX_H__
#define __BOX_H__

#include "container.h"

class Box : public Container
{
public:
	Box();
	virtual ~Box() override;
	
protected:
	virtual void onDraw(COORD offset);

};



#endif
