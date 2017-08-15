#include "MainController.h"
#include <iostream>
#include <functional>
#include "CommonFunction.h"
#include "DataManager.h"


using namespace std::placeholders;

#define CALLBACK_2( _METHOD_, _OBJ_) std::bind(&_METHOD_, _OBJ_, _1, _2)

MainController::MainController()
	: mCurrentPage(0)
{
}

MainController::~MainController()
{
}

void MainController::run()
{
	mMainView = new View();
	mMainView->retain();
	mMainView->setHeight(24);
	mMainView->setWidth(80);
	mMainView->setName("MainView");

	mBackground = new Box();
	mBackground->setHeight(mMainView->getHeight());
	mBackground->setWidth(mMainView->getWidth());
	mMainView->addChild(mBackground);

	initLoginPanel();

	mMainView->start();
	mMainView->release();
	Pool::getInstance()->checkRefs();
}

void MainController::initLoginPanel()
{
	mLoginPanel = new Box();
	mLoginPanel->setPosition({ 23,3 });
	mLoginPanel->setWidth( 34 );
	mLoginPanel->setHeight( 16 );
	mLoginPanel->setName( "LoginPanel" );
	mLoginPanel->setMouseListener(CALLBACK_2(MainController::onLoginMouseListener, this));
	mBackground->addChild(mLoginPanel);

	mLoginPanel->setVisible(true);


	auto loginBox = new Box();
	loginBox->setPosition({ 2,3 });
	loginBox->setWidth(30);
	loginBox->setHeight(3);
	loginBox->setName( "LoginBox" );
	loginBox->setMouseListener(CALLBACK_2(MainController::onLoginMouseListener, this));
	mLoginPanel->addChild(loginBox);

	mLoginField = new TextField("");
	mLoginField->setPosition({ 1,1 });
	mLoginField->setName("LoginField");
	mLoginField->setKeyListener(CALLBACK_2(MainController::onLoginKeyListener, this));
	mLoginField->setMaxLength( 24 );
	loginBox->addChild(mLoginField);

	auto loginLabel = new Label("Login");
	loginLabel->setPosition({2,2});
	loginLabel->setName( "LoginTitle" );
	mLoginPanel->addChild(loginLabel);

	
	auto passwordBox = new Box();
	passwordBox->setPosition({ 2,7 });
	passwordBox->setWidth(30);
	passwordBox->setHeight(3);
	passwordBox->setName("PasswordBox");
	passwordBox->setMouseListener(CALLBACK_2(MainController::onLoginMouseListener, this));
	mLoginPanel->addChild(passwordBox);

	mPasswordField = new TextField("");
	mPasswordField->setPosition({ 1,1 });
	mPasswordField->setIsPassword(true);
	mPasswordField->setMaxLength(24);
	passwordBox->addChild(mPasswordField);

	auto passwordLabel = new Label("Password");
	passwordLabel->setPosition({ 2,6 });
	passwordLabel->setName("PasswordTitle");
	mLoginPanel->addChild(passwordLabel);

	mButtonLoginApply = new Button();
	mButtonLoginApply->setPosition({ 9,10 });
	mButtonLoginApply->setWidth(17);
	mButtonLoginApply->setName( "ButtonLogin" );
	mButtonLoginApply->setHeight(5);
	mButtonLoginApply->setMouseListener(CALLBACK_2(MainController::onLoginMouseListener, this));
	mLoginPanel->addChild(mButtonLoginApply);

	auto buttonLabel = new Label("Apply");
	buttonLabel->setPosition({6,2});
	mButtonLoginApply->addChild(buttonLabel);
}

void MainController::initListPanel()
{
	mListPanel = new Container();
	mListPanel->setHeight(mBackground->getHeight());
	mListPanel->setWidth(mBackground->getWidth());
	mListPanel->setName("ListPanel");
	mListPanel->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	mListPanel->setVisible(false);
	mBackground->addChild(mListPanel);


	mRecordPanel = new Container();
	mRecordPanel->setWidth(mListPanel->getWidth());
	mRecordPanel->setHeight(mListPanel->getHeight());
	mListPanel->addChild(mRecordPanel);

	initRecordsList();


	mButtonAddRecord = new Button();
	mButtonAddRecord->setPosition({ 62,1 });
	mButtonAddRecord->setWidth(16);
	mButtonAddRecord->setHeight(5);
	mButtonAddRecord->setName("ButtonAddRecord");
	mButtonAddRecord->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	mListPanel->addChild(mButtonAddRecord);

	auto mButtonAddRecordTitle = new Label("Add");
	mButtonAddRecordTitle->setPosition({ 6,2 });
	mButtonAddRecord->addChild(mButtonAddRecordTitle);


	mButtonListUp = new Button();
	mButtonListUp->setPosition({ 62,12 });
	mButtonListUp->setWidth(16);
	mButtonListUp->setHeight(5);
	mButtonListUp->setName("ButtonListUp");
	mButtonListUp->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	mListPanel->addChild(mButtonListUp);

	auto mButtonListUpTitle = new Label("Page Up");
	mButtonListUpTitle->setPosition({ 3,2 });
	mButtonListUp->addChild(mButtonListUpTitle);


	mButtonListDown = new Button();
	mButtonListDown->setPosition({ 62,17 });
	mButtonListDown->setWidth(16);
	mButtonListDown->setHeight(5);
	mButtonListDown->setName("ButtonListDown");
	mButtonListDown->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	mListPanel->addChild(mButtonListDown);

	auto mButtonListDownTitle = new Label("Page Down");
	mButtonListDownTitle->setPosition({ 3,2 });
	mButtonListDown->addChild(mButtonListDownTitle);

	
	Button* mButtonListUp;
	Button* mButtonListDown;
}

void MainController::initRecordsList(int page)
{
	mRecordPanel->removeAllChildren();

	int countRecords = DataManager::getInstance()->getCountRecords();
	int counter = 0;

	int index = page * 7;

	if (index > countRecords)
	{
		index = 0;
	}

	for ( ; index < countRecords && counter < 7; index++ )
	{
		auto record = DataManager::getInstance()->getRecord(index);

		char* buffer = static_cast<char*>( malloc(10) );

		std::string id(itoa(index, buffer, 10));

		free(buffer);

		auto recordContainer = createRecordContainer(record->resource);
		recordContainer->setName(id);
		recordContainer->setPosition({ 1,1 + static_cast< SHORT >(counter * recordContainer->getHeight()) });
		mRecordPanel->addChild(recordContainer);

		counter++;
	}
}

Container* MainController::createRecordContainer(const std::string& title)
{
	Container* result = new Button();
	result->setWidth(60);
	result->setHeight(3);
	result->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));

	auto labelResource = new Label(title);
	labelResource->setPosition({ 1, 1});
	labelResource->setMaxLength(57);
	labelResource->setName("Resource");
	result->addChild(labelResource);

	return result;
}

void MainController::initShowRecordPanel()
{
	mShowRecordPanel = new Container();
	mShowRecordPanel->setWidth(mBackground->getWidth());
	mShowRecordPanel->setHeight(mBackground->getHeight());
	mShowRecordPanel->setName("ShowRecordPanel");
	mShowRecordPanel->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	mBackground->addChild(mShowRecordPanel);
	mShowRecordPanel->setVisible(false);

	auto background = new Box();
	background->setPosition({ 10,3 });
	background->setWidth(60);
	background->setHeight(16);
	background->setName("Background");
	background->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	mShowRecordPanel->addChild(background);
	
	
	mShowRecordResource = new Label("");
	mShowRecordResource->setPosition({ 1, 1 });
	mShowRecordResource->setMaxLength(58);
	mShowRecordResource->setName("Resource");
	background->addChild(mShowRecordResource);

	auto label1 = new Label("Login:");
	label1->setPosition({ 1, 3 });
	label1->setMaxLength(58);
	background->addChild(label1);

	auto label2 = new Label("Password:");
	label2->setPosition({ 1, 5 });
	label2->setMaxLength(58);
	background->addChild(label2);

	mShowRecordLogin = new Label("");
	mShowRecordLogin->setPosition({ 2 + static_cast< SHORT >(label1->getWidth()) , 3 });
	mShowRecordLogin->setMaxLength(24);
	background->addChild(mShowRecordLogin);

	mShowRecordPassword = new Label("");
	mShowRecordPassword->setPosition({ 2 + static_cast< SHORT >(label2->getWidth()), 5 });
	mShowRecordPassword->setMaxLength(24);
	mShowRecordPassword->setIsPassword(true);
	background->addChild(mShowRecordPassword);

	mButtonCopyLogin = new Button();
	mButtonCopyLogin->setPosition({ 5,10 });
	mButtonCopyLogin->setWidth(14);
	mButtonCopyLogin->setHeight(5);
	mButtonCopyLogin->setName("ButtonCopyLogin");
	mButtonCopyLogin->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	background->addChild(mButtonCopyLogin);

	auto labelRecordLogin = new Label("Copy login");
	labelRecordLogin->setPosition({ 2, 2 });
	labelRecordLogin->setMaxLength(10);
	mButtonCopyLogin->addChild(labelRecordLogin);


	mButtonCopyPassword = new Button();
	mButtonCopyPassword->setPosition({ 22,10 });
	mButtonCopyPassword->setWidth(13);
	mButtonCopyPassword->setHeight(5);
	mButtonCopyPassword->setName("ButtonCopyPassword");
	mButtonCopyPassword->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	background->addChild(mButtonCopyPassword);

	auto labelRecordPass = new Label("Copy pass");
	labelRecordPass->setPosition({ 2, 2 });
	mButtonCopyPassword->addChild(labelRecordPass);


	mButtonShowPassword = new Button();
	mButtonShowPassword->setPosition({ 37,10 });
	mButtonShowPassword->setWidth(17);
	mButtonShowPassword->setHeight(5);
	mButtonShowPassword->setName("ButtonShowPassword");
	mButtonShowPassword->setMouseListener(CALLBACK_2(MainController::onListRecordsMouseListener, this));
	background->addChild(mButtonShowPassword);

	mLabelShowPassword = new Label("Show password");
	mLabelShowPassword->setPosition({ 2, 2 });
	mButtonShowPassword->addChild(mLabelShowPassword);
	
}

void MainController::initAddRecordPanel()
{
	mAddRecordPanel = new Container();
	mAddRecordPanel->setHeight(mBackground->getHeight());
	mAddRecordPanel->setWidth(mBackground->getWidth());
	mAddRecordPanel->setName("AddRecordPanel");
	mAddRecordPanel->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	mBackground->addChild(mAddRecordPanel);

	mAddRecordPanel->setVisible(false);

	auto background = new Box();
	background->setPosition({ 13,2 });
	background->setWidth(55);
	background->setHeight(20);
	background->setName("Background");
	background->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	mAddRecordPanel->addChild(background);

	
	auto addResourceBox = new Box();
	addResourceBox->setPosition({ 2,2 });
	addResourceBox->setWidth(50);
	addResourceBox->setHeight(3);
	addResourceBox->setName("ResourceBox");
	addResourceBox->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	background->addChild(addResourceBox);

	mAddResourceField = new TextField("");
	mAddResourceField->setPosition({ 1,1 });
	mAddResourceField->setName("AddResourceField");
	mAddResourceField->setKeyListener(CALLBACK_2(MainController::onAddRecordKeyListener, this));
	mAddResourceField->setMaxLength(50);
	addResourceBox->addChild(mAddResourceField);

	auto resourceLabel = new Label("Resource");
	resourceLabel->setPosition({ 2,-2 });
	mAddResourceField->addChild(resourceLabel);


	auto addLoginBox = new Box();
	addLoginBox->setPosition({ 2,6 });
	addLoginBox->setWidth(26);
	addLoginBox->setHeight(3);
	addLoginBox->setName("LoginBox");
	addLoginBox->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	background->addChild(addLoginBox);

	mAddLoginField = new TextField("");
	mAddLoginField->setPosition({ 1,1 });
	mAddLoginField->setName("AddLoginField");
	mAddLoginField->setKeyListener(CALLBACK_2(MainController::onAddRecordKeyListener, this));
	mAddLoginField->setMaxLength(24);
	addLoginBox->addChild(mAddLoginField);

	auto addLabel = new Label("Login");
	addLabel->setPosition({ 2,-2 });
	addLabel->setName("AddLogin");
	mAddLoginField->addChild(addLabel);


	auto passwordAddBox = new Box();
	passwordAddBox->setPosition({ 2,10 });
	passwordAddBox->setWidth(26);
	passwordAddBox->setHeight(3);
	passwordAddBox->setName("PasswordBox");
	passwordAddBox->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	background->addChild(passwordAddBox);

	mAddPasswordField = new TextField("");
	mAddPasswordField->setPosition({ 1,1 });
	mAddPasswordField->setIsPassword(true);
	mAddPasswordField->setMaxLength(24);
	passwordAddBox->addChild(mAddPasswordField);

	auto passwordAddLabel = new Label("Password");
	passwordAddLabel->setPosition({ 2,-2 });
	passwordAddLabel->setName("PasswordTitle");
	mAddPasswordField->addChild(passwordAddLabel);


	mButtonGeneratePass = new Button();
	mButtonGeneratePass->setPosition({ 33,10 });
	mButtonGeneratePass->setWidth(14);
	mButtonGeneratePass->setName("ButtonGenPas");
	mButtonGeneratePass->setHeight(3);
	mButtonGeneratePass->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	background->addChild(mButtonGeneratePass);

	auto buttonLabelGenerate = new Label("Gen pass");
	buttonLabelGenerate->setPosition({ 3,1 });
	mButtonGeneratePass->addChild(buttonLabelGenerate);

	mButtonAddApply = new Button();
	mButtonAddApply->setPosition({ 20,14});
	mButtonAddApply->setWidth(11);
	mButtonAddApply->setName("ButtonApply");
	mButtonAddApply->setHeight(5);
	mButtonAddApply->setMouseListener(CALLBACK_2(MainController::onAddRecordMouseListener, this));
	background->addChild(mButtonAddApply);

	auto buttonLabel = new Label("Add");
	buttonLabel->setPosition({ 4,2 });
	mButtonAddApply->addChild(buttonLabel);
	
}

bool MainController::onLoginKeyListener(Container* sender, char c)
{
	bool result = false;

	std::string name = sender->getName();

	if (name == "LoginField")
	{
		if (c == 13 || c == 9)
		{
			mPasswordField->setFocused(true);
			mLoginField->setFocused(false);
		}
		result = true;
	}

	return result;
}

bool MainController::onLoginMouseListener(Container* sender, sMouse* event)
{
	bool result = false;

	std::string name = sender->getName();

	////////////////////////////////////

	if (name == "LoginBox")
	{
		mLoginField->setFocused(true);
		mPasswordField->setFocused(false);
		result = true;
	}
	else if (name == "PasswordBox")
	{
		mPasswordField->setFocused(true);
		mLoginField->setFocused(false);
		result = true;
	}
	else if (name == "ButtonLogin")
	{
		mLoginField->setFocused(false);
		mPasswordField->setFocused(false);
		validationLoginData();
		result = true;
	}
	else if ( name == "LoginPanel" )
	{
		mLoginField->setFocused(false);
		mPasswordField->setFocused(false);
		result = true;
	}

	return result;
}

bool MainController::onListRecordsMouseListener(Container* sender, sMouse* event)
{
	bool result = false;
	std::string name = sender->getName();

	if (!mShowRecordPanel->isVisible())
	{
		if (name == "ButtonAddRecord")
		{
			mListPanel->setVisible(false);
			mAddRecordPanel->setVisible(true);

			mAddResourceField->setString("");
			mAddLoginField->setString("");
			mAddPasswordField->setString("");
			result = true;
		}
		else if (name == "ButtonListUp")
		{
			if (mCurrentPage > 0)
			{
				mCurrentPage--;
				initRecordsList(mCurrentPage);
			}

			result = true;
		}
		else if (name == "ButtonListDown")
		{
			int count = DataManager::getInstance()->getCountRecords();
			int countPage = count / 7;

			if (mCurrentPage < countPage)
			{
				mCurrentPage++;
				initRecordsList(mCurrentPage);
			}

			result = true;
		}
		else if (name == "ListPanel")
		{

			result = true;
		}
		else
		{
			int index = atoi(name.c_str());

			showRecord(index);

			mListPanel->setVisible(false);
			mShowRecordPanel->setVisible(true);
			result = true;
		}
	}
	else
	{
		if (name == "Background")
		{
			result = true;
		}
		else if (name == "ButtonCopyLogin")
		{
			toClipBoard(mShowRecordLogin->getString());
			result = true;
		}
		else if (name == "ButtonCopyPassword")
		{
			toClipBoard(mShowRecordPassword->getString());
			result = true;
		}
		else if (name == "ButtonShowPassword")
		{
			mShowRecordPassword->setIsPassword(!mShowRecordPassword->isPassword());

			if (mShowRecordPassword->isPassword())
			{
				mLabelShowPassword->setString("Show password");
			}
			else
			{
				mLabelShowPassword->setString("Hide password");
			}

			result = true;
		}
		else
		{
			mShowRecordPanel->setVisible(false);
			mListPanel->setVisible(true);
		}
	}

	return result;
}

bool MainController::onAddRecordKeyListener(Container* sender, char c)
{
	bool result = false;

	return result;
}

bool MainController::onAddRecordMouseListener(Container* sender, sMouse* event)
{
	bool result = false;

	std::string name = sender->getName();

	if (name == "AddRecordPanel")
	{
		mAddRecordPanel->setVisible(false);
		mListPanel->setVisible(true);
		mAddResourceField->setFocused(false);
		mAddLoginField->setFocused(false);
		mAddPasswordField->setFocused(false);
		result = true;
	}
	else if (name == "ResourceBox")
	{
		mAddResourceField->setFocused(!mAddResourceField->isFocused());
		
		mAddLoginField->setFocused(false);
		mAddPasswordField->setFocused(false);
		result = true;
	}
	else if (name == "LoginBox")
	{
		mAddLoginField->setFocused(!mAddLoginField->isFocused());

		mAddResourceField->setFocused(false);
		mAddPasswordField->setFocused(false);
		result = true;
	}
	else if (name == "PasswordBox")
	{
		mAddPasswordField->setFocused(!mAddPasswordField->isFocused());
		
		mAddResourceField->setFocused(false);
		mAddLoginField->setFocused(false);
		result = true;
	}
	else if (name == "ButtonGenPas")
	{
		mAddResourceField->setFocused(false);
		mAddLoginField->setFocused(false);
		mAddPasswordField->setFocused(false);

		mAddPasswordField->setString(gen_pw(24));
		result = true;
	}
	else if (name == "ButtonApply")
	{
		mAddRecordPanel->setVisible(false);
		mListPanel->setVisible(true);
		mAddResourceField->setFocused(false);
		mAddLoginField->setFocused(false);
		mAddPasswordField->setFocused(false);

		sRecord newRecord;

		newRecord.resource = mAddResourceField->getString();
		newRecord.login = mAddLoginField->getString();
		newRecord.pasword = mAddPasswordField->getString();

		int index = DataManager::getInstance()->addRecord(newRecord);

		saveRecords();

		mCurrentPage = index / 7;

		initRecordsList( mCurrentPage );

		result = true;
	}
	else if (name == "Background")
	{
		mAddResourceField->setFocused(false);
		mAddLoginField->setFocused(false);
		mAddPasswordField->setFocused(false);
		result = true;
	}
	
	return result;
}

void MainController::showRecord(int index)
{
	sRecord* record = DataManager::getInstance()->getRecord(index);

	mShowRecordResource->setString(record->resource);
	mShowRecordLogin->setString(record->login);
	mShowRecordPassword->setString( record->pasword );

	mShowRecordPassword->setIsPassword(true);
	mLabelShowPassword->setString("Show password");
}

void MainController::validationLoginData()
{
	bool isOk = true;

	auto loginTitle = static_cast<Label*>(mLoginPanel->getChildByName("LoginTitle"));
	std::string error = isLoginPasswordValid(mLoginField->getString());
	if (error.length())
	{
		loginTitle->setString("Login - " + error);
		isOk = false;
	}
	else
	{
		loginTitle->setString("Login");
	}

	auto passwordTitle = static_cast<Label*>(mLoginPanel->getChildByName("PasswordTitle"));
	error = isLoginPasswordValid(mPasswordField->getString());
	if (error.length())
	{
		passwordTitle->setString("Password - " + error);
		isOk = false;
	}
	else
	{
		passwordTitle->setString("Password");
	}

	if (isOk)
	{
		mLogin = mLoginField->getString();
		mPassword = mPasswordField->getString();

		loadRecords();

		initListPanel();
		initShowRecordPanel();
		initAddRecordPanel();


		mLoginPanel->setVisible(false);
		mListPanel->setVisible(true);
	}
}

std::string MainController::isLoginPasswordValid(const std::string& str)
{
	std::string result = "";

	if (str.length() < 8)
	{
		result = "min size 8 simbols";
	}

	if (result.empty())
	{
		for (auto c : str)
		{
			if (
				!(
				(c >= 97 && c <= 122)
					|| (c >= 65 && c <= 90)
					|| (c >= 48 && c <= 57)
					)
				)
			{
				result = "unresolved characters";
				break;
			}
		}
	}

	return result;
}

void MainController::loadRecords()
{
	void* buffer = nullptr;
	unsigned size = 0;

	std::string fileName = getHesh( mPassword + mLogin ) + getHesh(mPassword + "pass") + getHesh("login" + mLogin);
	std::string key = getHesh( mLogin + "sold" + mPassword ) + getHesh(mLogin + "soldLogin") + getHesh(mPassword + "soldPass");

	loadBufferFromFile(&buffer, size, fileName, key);

	if (buffer)
	{
		DataManager::getInstance()->loadFromBuffer(buffer, size);
	}

}

void MainController::saveRecords()
{
	void* buffer = nullptr;
	unsigned size = 0;

	DataManager::getInstance()->saveToBuffer(&buffer, size);

	if (buffer && size > 0)
	{
		std::string fileName = getHesh(mPassword + mLogin) + getHesh(mPassword + "pass") + getHesh("login" + mLogin);
		std::string key = getHesh(mLogin + "sold" + mPassword) + getHesh(mLogin + "soldLogin") + getHesh(mPassword + "soldPass");

		saveBufferToFile(buffer, size, fileName, key );
	}
}