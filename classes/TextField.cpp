#include "TextField.h"
#include <iomanip>
#include <time.h>

TextField::TextField()
	: mMaxLength(99)
	, mIsFocused( false )
	, mIsPassword( false )
{
}

TextField::TextField(const std::string& str)
	: mString( str )
	, mMaxLength( 99 )
	, mIsFocused(false)
	, mIsPassword(false)
{

}

TextField::~TextField()
{
}

void TextField::setIsPassword(bool isPassword)
{
	if (mIsPassword != isPassword)
	{
		mIsPassword = isPassword;
		setDirty();

		if (getParent())
		{
			setDirty();
		}
	}
}

bool TextField::isPassword()
{
	return mIsPassword;
}

void TextField::onDraw(COORD offset)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hStdOut, { (SHORT)offset.X, (SHORT)offset.Y });

	if (mIsPassword)
	{
		for( int i = 0 ; i < mString.length(); i++ )
		{
			std::cout << "*";
		}
	}
	else
	{
		std::cout << mString;
	}

	if (mIsFocused && mLastTime % 2)
	{
		std::cout << "_";
	}
}

void TextField::setString(const std::string& str)
{
	mString = str;
	setDirty();
}

std::string TextField::getString()
{
	return mString;
}

void TextField::setMaxLength(int length)
{
	mMaxLength = length;
	if (mMaxLength < mString.length())
	{
		mString = mString.substr(0, mMaxLength);
	}
}

int TextField::getMaxLength()
{
	return mMaxLength;
}

int TextField::getWidth()
{
	return (mMaxLength > mString.length()) ? mMaxLength : mString.length();
}

int TextField::getHeight()
{
	return 1;
}

bool TextField::dispatchKeyEvent(unsigned char c)
{
	bool result = false;

	result = mIsFocused && Container::dispatchKeyEvent(c);

	if (mIsFocused)
	{
		if (isprint(c))
		{
			if (mString.length() < mMaxLength)
			{
				mString.append(1, c);
				getParent()->setDirty();
			}
		}
		else if (c == 8)
		{
			if (mString.length() > 0)
			{
				mString = mString.substr(0, mString.length() - 1);
				getParent()->setDirty();
			}
		}
		else if (c == 13)
		{

		}
		
		result = true;
	}

	return result;
}

void TextField::setFocused(bool focused)
{
	mIsFocused = focused;
}

bool TextField::isFocused()
{
	return mIsFocused;
}

void TextField::onUpdate()
{
	if (mIsFocused)
	{
		int currentTime = clock() / 500;
		if (mLastTime != currentTime)
		{
			mLastTime = currentTime;
			getParent()->setDirty();
		}
	}
}