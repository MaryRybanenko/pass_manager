#ifndef __VIEW_H__
#define __VIEW_H__

#include "container.h"

class View : public Container
{
public:
	View();
	virtual ~View() override;

	void start();
	void stop();

private:

	bool mIsExit;


};

#endif

