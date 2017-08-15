#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

DataManager* DataManager::getInstance()
{
	static DataManager instance;
	return &instance;
}

int DataManager::addRecord(const sRecord& record)
{
	int result = mRecords.size();

	mRecords.push_back(record);

	return result;
}

sRecord* DataManager::getRecord(int index)
{
	sRecord* result = nullptr;

	if (index < mRecords.size())
	{
		result = &( mRecords[index] );
	}

	return result;
}

int DataManager::getCountRecords()
{
	return mRecords.size();
}

void DataManager::loadFromBuffer(void* buffer, unsigned int size)
{
	mRecords.clear();
	unsigned prevSeparator = 0;
	unsigned currentSeparator = 0;

	char* cStr = static_cast<char*>(buffer);

	for (int i = 1; i < size; ++i)
	{
		currentSeparator = i;
		if (cStr[i-1] != '\\' && cStr[i] == '|')
		{
			std::string str(cStr + prevSeparator, currentSeparator - prevSeparator);

			auto pos1 = str.find("=");
			while (pos1 == 0 || str[pos1 - 1] == '\\')
			{
				pos1 = str.find("=", pos1 + 1);
			}

			auto pos2 = str.find("=", pos1 + 1);
			while (pos2 == 0 || str[pos2 - 1] == '\\')
			{
				pos2 = str.find("=", pos2 + 1);
			}
			
			sRecord record;
			record.resource = str.substr(0, pos1);
			record.login = str.substr(pos1 + 1, pos2 - (pos1 + 1) );
			record.pasword = str.substr(pos2 + 1);

			prevSeparator = currentSeparator;

			mRecords.push_back(record);
		}
	}
	
	std::string str(cStr + prevSeparator + 1, currentSeparator - prevSeparator);

	auto pos1 = str.find("=");
	while (pos1 == 0 || str[pos1 - 1] == '\\')
	{
		pos1 = str.find("=", pos1 + 1);
	}

	auto pos2 = str.find("=", pos1 + 1);
	while (pos2 == 0 || str[pos2 - 1] == '\\')
	{
		pos2 = str.find("=", pos2 + 1);
	}

	sRecord record;
	record.resource = str.substr(0, pos1);
	record.login = str.substr(pos1 + 1, pos2 - (pos1 + 1));
	record.pasword = str.substr(pos2 + 1);
	
	mRecords.push_back(record);


	for (auto& record : mRecords)
	{
		std::string temp = record.resource;

		record.resource = "";
		for (int i = 0 ; i < temp.length() - 1 ; ++i)
		{
			if ( temp[i] == '\\' && temp[i + 1] == '=')
			{
				record.resource += "=";
				i++;
			}
			else if (temp[i] == '\\' && temp[i + 1] == '|')
			{
				record.resource += "|";
				i++;
			}
			else
			{
				record.resource += temp[i];
			}
		}
		record.resource += temp[temp.length() - 1];


		temp = record.login;
		record.login = "";
		for (int i = 0; i < temp.length() - 1; ++i)
		{
			if (temp[i] == '\\' && temp[i + 1] == '=')
			{
				record.login += "=";
				i++;
			}
			else if (temp[i] == '\\' && temp[i + 1] == '|')
			{
				record.login += "|";
				i++;
			}
			else
			{
				record.login += temp[i];
			}
		}
		record.login += temp[temp.length() - 1];

		temp = record.pasword;
		record.pasword = "";
		for (int i = 0; i < temp.length() - 1; ++i)
		{
			if (temp[i] == '\\' && temp[i + 1] == '=')
			{
				record.pasword += "=";
				i++;
			}
			else if (temp[i] == '\\' && temp[i + 1] == '|')
			{
				record.pasword += "|";
				i++;
			}
			else
			{
				record.pasword += temp[i];
			}
		}
		record.pasword += temp[temp.length() - 1];

	}

}

void DataManager::saveToBuffer(void** buffer, unsigned int& size)
{
	std::string resultString;

	int counter = 1;
	for (auto record : mRecords)
	{
		std::string temp;

		for (auto ch : record.resource)
		{
			if (ch == '=')
			{
				temp += "\\=";
			}
			else if (ch == '|')
			{
				temp += "\\|";
			}
			else
			{
				temp += ch;
			}
		}
		resultString += temp + "=";

		temp = "";
		for (auto ch : record.login)
		{
			if (ch == '=')
			{
				temp += "\\=";
			}
			else if (ch == '|')
			{
				temp += "\\|";
			}
			else
			{
				temp += ch;
			}
		}
		resultString += temp + "=";

		temp = "";
		for (auto ch : record.pasword)
		{
			if (ch == '=')
			{
				temp += "\\=";
			}
			else if (ch == '|')
			{
				temp += "\\|";
			}
			else
			{
				temp += ch;
			}
		}
		resultString += temp;

		if (counter != mRecords.size())
		{
			resultString += "|";
		}
		counter++;
	}

	size = resultString.length();
	*buffer = malloc(size);

	memcpy(*buffer, resultString.c_str(), size);
}