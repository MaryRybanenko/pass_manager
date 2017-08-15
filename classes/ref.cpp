#include "ref.h"
#include "pool.h"


Ref::Ref()
	: mRefCount(0)
{
	Pool::getInstance()->addRef(this);
}
Ref::~Ref()
{

}
void Ref::retain()
{
	mRefCount++;
}

void Ref::release()
{
	mRefCount--;
}

int Ref::getRefCount()
{
	return mRefCount;
}
