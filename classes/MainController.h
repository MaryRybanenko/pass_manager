#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include "HeaderCommon.h"

class MainController
{
public:
	MainController();
	~MainController();
	
	void run();


private:
	
	////////////////////////////////////////
	/// VARIABLE

	std::string mLogin;
	std::string mPassword;

	View* mMainView;
	Box* mBackground;

	//////// LOGIN PANEL

	Box* mLoginPanel;
	TextField* mLoginField;
	TextField* mPasswordField;
	Button* mButtonLoginApply;

	//////// LIST PANEL

	Container* mListPanel;
	Container* mRecordPanel;
	Button* mButtonAddRecord;
	Button* mButtonListUp;
	Button* mButtonListDown;

	int mCurrentPage;

	//////// SHOW RECORD

	Container* mShowRecordPanel;
	Label* mShowRecordResource;
	Label* mShowRecordLogin;
	Label* mShowRecordPassword;
	Button* mButtonCopyLogin;
	Button* mButtonCopyPassword;
	Button* mButtonShowPassword;
	Label* mLabelShowPassword;


	//////// ADD RECORD

	Container* mAddRecordPanel;
	TextField* mAddResourceField;
	TextField* mAddLoginField;
	TextField* mAddPasswordField;
	Button* mButtonAddApply;
	Button* mButtonGeneratePass;



	////////////////////////////////////////
	/// FUNCTIONS

	void initLoginPanel();
	void initListPanel();
	void initShowRecordPanel();
	void initAddRecordPanel();

	void showRecord(int index);

	void initRecordsList(int page = 0);
	Container* createRecordContainer( const std::string& title );

	void saveRecords();
	void loadRecords();

	void validationLoginData();
	std::string isLoginPasswordValid(const std::string& str);

	bool onLoginKeyListener(Container* sender, char c);
	bool onLoginMouseListener(Container* sender, sMouse* event);

	bool onListRecordsMouseListener(Container* sender, sMouse* event);

	bool onAddRecordKeyListener(Container* sender, char c);
	bool onAddRecordMouseListener(Container* sender, sMouse* event);

};


#endif
