#ifndef __LABEL_H__
#define __LABEL_H__

#include "container.h"

class Label : public Container
{
public:
	Label();
	Label(const std::string& str);
	virtual ~Label() override;

	void setString( const std::string& str );
	std::string getString();
	
	virtual int getWidth() override;
	virtual int getHeight() override;

	void setMaxLength(int length);
	int getMaxLength();

	void setIsPassword(bool isPassword);
	bool isPassword();

protected:
	virtual void onDraw(COORD offset);

	std::string mString;
	bool mIsPassword;
	int mMaxLength;
};



#endif
