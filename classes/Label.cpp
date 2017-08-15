#include "Label.h"
#include <iomanip>

Label::Label()
: mMaxLength(99)
, mIsPassword(false)
{
}

Label::Label(const std::string& str)
	: mString( str )
	, mMaxLength( 99 )
	, mIsPassword(false)
{

}

Label::~Label()
{
}

void Label::setIsPassword(bool isPassword)
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

bool Label::isPassword()
{
	return mIsPassword;
}

void Label::onDraw(COORD offset)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hStdOut, { (SHORT)offset.X, (SHORT)offset.Y });
	if (mIsPassword)
	{
		for (int i = 0; i < mString.length(); i++)
		{
			std::cout << "*";
		}
	}
	else
	{
		std::cout << mString;
	}
}

void Label::setString(const std::string& str)
{
	mString = str;
	if (getParent())
	{
		getParent()->setDirty();
	}
	
}

std::string Label::getString()
{
	return mString;
}

void Label::setMaxLength(int length)
{
	mMaxLength = length;
}

int Label::getMaxLength()
{
	return mMaxLength;
}

int Label::getWidth()
{
	return (mMaxLength < mString.length()) ? mMaxLength : mString.length();
}

int Label::getHeight()
{
	return 1;
}