#ifndef __CONT_H__
#define __CONT_H__

#include "ref.h"
#include <windows.h>
#include <string>
#include <functional>
#include <list>
#include "mouseReader.h"
#include "pool.h"

static COORD operator +(const COORD& lValue, COORD rValue)
{
	return { lValue.X + rValue.X, lValue.Y + rValue.Y };
}

static COORD operator -(const COORD& lValue, COORD rValue)
{
	return { lValue.X - rValue.X, lValue.Y - rValue.Y };
}

static bool operator !=(const COORD& lValue, COORD rValue)
{
	return { lValue.X != rValue.X || lValue.Y != rValue.Y };
}

static bool operator ==(const COORD& lValue, COORD rValue)
{
	return { lValue.X == rValue.X && lValue.Y == rValue.Y };
}


class Container : public Ref
{
public:
	Container();
	virtual ~Container() override;

	void addChild(Container* child);
	void removeChild(Container* child);
	void removeAllChildren();
	void removeChildByName(const std::string& name);
	Container* getChildByName(const std::string& name);

	void setName(const std::string& name);
	void setPosition(COORD srcPosition);
	void setWidth(int srcWidth);
	void setHeight(int srcHeight);
	void setVisible(bool visible);

	std::string getName();
	COORD getPosition();
	virtual int getWidth();
	virtual int getHeight();
	bool isVisible();

	void setDirty();
	void setDirtyTransform();

	std::list< Container* > getChildren();

	void setKeyListener(std::function< bool(Container*, unsigned char) > callback);
	void setMouseListener(std::function< bool(Container*, sMouse*) > callback);

	bool isContainCoord( COORD position );
	COORD convertToContainerSpace( COORD position );

	void setParent(Container* parent);
	Container* getParent();

	virtual bool dispatchKeyEvent(unsigned char c);
	virtual bool dispatchMouseEvent(sMouse* event);

protected:
	virtual void onDraw(COORD offset);
	void draw(COORD offset = {0,0}, bool flagIsDirty = false);

	bool isDirtyTransform();

	std::function< bool(Container*, unsigned char) > mKeyListener;
	std::function< bool(Container*, sMouse*) > mMouseListener;

	void update();
	virtual void onUpdate();

private:
	std::list< Container* > mChildren;

	bool mIsDirty;
	bool mIsDirtyTransform;

	bool mIsVisible;
	Container* mParent;
	std::string mName;
	COORD mPosition;
	int mWidth;
	int mHeight;
};


#endif
