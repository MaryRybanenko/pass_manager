#ifndef __REF_H__
#define __REF_H__

class Ref
{
public:
	Ref();
	virtual ~Ref();

	void retain();
	void release();
	int getRefCount();

private:
	int mRefCount;
};


#endif
