#include "container.h"

Container::Container()
	: mPosition({0,0})
	, mWidth(0)
	, mHeight(0)
	, mIsDirty( true )
	, mIsDirtyTransform( true )
	, mParent( nullptr )
	, mIsVisible( true )
{
}

Container::~Container()
{
	removeAllChildren();
}

void Container::setPosition(COORD srcPosition)
{
	mPosition = srcPosition;
	mIsDirty = true;
}

void Container::setWidth(int srcWidth)
{
	mWidth = srcWidth;
	mIsDirty = true;
}

void Container::setName(const std::string& name)
{
	mName = name;
}

void Container::setHeight(int srcHeight)
{
	mHeight = srcHeight;
	mIsDirty = true;
}

COORD Container::getPosition()
{
	return mPosition;
}

int Container::getWidth()
{
	return mWidth;
}

int Container::getHeight()
{
	return mHeight;
}

std::string Container::getName()
{
	return mName;
}

void Container::setParent(Container* parent)
{
	mParent = parent;

	if ( mIsDirty )
	{
		mParent->setDirty();
	}
}

Container* Container::getParent()
{
	return mParent;
}

std::list< Container* > Container::getChildren()
{
	return mChildren;
}

void Container::setVisible(bool visible)
{
	if (mIsVisible != visible)
	{
		mIsVisible = visible;
		if (getParent())
		{
			getParent()->setDirtyTransform();
		}
	}
}

bool Container::isVisible()
{
	return mIsVisible;
}

void Container::addChild(Container* child)
{
	if (child->getParent())
	{
		return;
	}

	auto it = std::find(mChildren.begin(), mChildren.end(), child);
	if (it == mChildren.end())
	{
		child->retain();
		child->setParent(this);
		mChildren.push_back(child);
		mIsDirtyTransform = true;
	}
}

void Container::removeChild(Container* child)
{
	auto it = std::find(mChildren.begin(), mChildren.end(), child);
	if (it != mChildren.end())
	{
		child->release();
		child->setParent(nullptr);
		mChildren.erase(it);
		mIsDirtyTransform = true;
	}
}

void Container::removeAllChildren()
{
	for ( auto child : mChildren )
	{
		child->release();
		child->setParent(nullptr);
	}

	mChildren.clear();
	mIsDirtyTransform = true;
}

void Container::removeChildByName(const std::string& name)
{
	auto it = mChildren.begin();
	for (; it != mChildren.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			(*it)->release();
			(*it)->setParent(nullptr);
			mChildren.erase(it);
			mIsDirtyTransform = true;
			break;
		}
	}
}

Container* Container::getChildByName(const std::string& name)
{
	Container* result = nullptr;

	for (auto it = mChildren.begin(); it != mChildren.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			result = *it;
		}
	}

	return result;
}

bool Container::isDirtyTransform()
{
	bool result = mIsDirtyTransform;

	for (auto child : mChildren)
	{
		mIsDirtyTransform = mIsDirtyTransform || child->isDirtyTransform() && child->isVisible();
	}

	return mIsDirtyTransform;
}

void Container::draw(COORD offset, bool flagIsDirty)
{
	if (mIsVisible)
	{
		flagIsDirty = flagIsDirty || mIsDirty;

		if (flagIsDirty)
		{
			onDraw(offset + mPosition);
		}

		for (auto child : mChildren)
		{
			child->draw(offset + mPosition, flagIsDirty);
		}

		mIsDirty = false;
	}

	mIsDirtyTransform = false;
}

void Container::onDraw(COORD offset)
{
}

void Container::setKeyListener(std::function< bool(Container*, unsigned char) > callback)
{
	mKeyListener = callback;
}

bool Container::dispatchKeyEvent(unsigned char c)
{
	bool result = false;

	if ( mKeyListener )
	{
		result = mKeyListener(this, c);
	}

	return result;
}

void Container::setMouseListener(std::function< bool(Container*, sMouse*) > callback)
{
	mMouseListener = callback;
}

bool Container::dispatchMouseEvent(sMouse* event)
{
	bool result = false;

	if ( mMouseListener && isContainCoord(event->mousePos))
	{
		result = mMouseListener(this, event);
	}

	return result;
}

void Container::setDirty()
{
	mIsDirty = true;
}

void Container::setDirtyTransform()
{
	mIsDirtyTransform = true;
}

bool Container::isContainCoord( COORD position)
{
	auto pos = convertToContainerSpace(position);

	return pos.X >= 0
		&& pos.X < mWidth
		&& pos.Y >= 0
		&& pos.Y < mHeight;
}

COORD Container::convertToContainerSpace(COORD position)
{
	COORD result = position;

	if (mParent)
	{
		result = mParent->convertToContainerSpace(result);

		result = result - getPosition();
	}

	return result;
}

void Container::update()
{
	for (auto child : mChildren)
	{
		child->update();
	}
	onUpdate();
}

void Container::onUpdate()
{
}