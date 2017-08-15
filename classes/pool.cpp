#include "pool.h"

Pool* Pool::mInstance = new Pool;

Pool::Pool()
{
	
}

Pool::~Pool()
{

}

Pool* Pool::getInstance()
{
	return mInstance;
}

void Pool::addRef(Ref* ref)
{
	mRefList.push_back(ref);
}

void Pool::checkRefs()
{
	for (std::list<Ref*>::iterator refIt = mRefList.begin() ; refIt != mRefList.end() ; refIt++ )
	{
		if ( !( (*refIt)->getRefCount() ) )
		{
			delete (*refIt);
			mRefList.erase(refIt);
			refIt = mRefList.begin();
		}
	}
}