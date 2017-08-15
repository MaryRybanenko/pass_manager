#ifndef __POOL_H__
#define __POOL_H__

#include <iostream>
#include <list>
#include "ref.h"


class Pool
{
public:
	static Pool* getInstance();
	
	void checkRefs();

	void addRef(Ref* ref);

private:
	Pool();
	~Pool();
	static Pool* mInstance;
	std::list <Ref*> mRefList;
};

#endif
