#ifndef __TEXT_FIELD_H__
#define __TEXT_FIELD_H__

#include "container.h"

class TextField : public Container
{
public:
	TextField();
	TextField(const std::string& str);
	virtual ~TextField() override;

	void setString( const std::string& str );
	std::string getString();

	virtual int getWidth() override;
	virtual int getHeight() override;
	
	void setMaxLength(int length);
	int getMaxLength();

	void setFocused(bool focused);
	bool isFocused();

	void setIsPassword(bool isPassword);
	bool isPassword();

protected:
	virtual void onDraw(COORD offset);

	virtual bool dispatchKeyEvent(unsigned char c) override;

	virtual void onUpdate() override;

private:

	std::string mString;
	bool mIsPassword;
	int mMaxLength;
	bool mIsFocused;
	int mLastTime;
};



#endif
