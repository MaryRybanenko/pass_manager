#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "HeaderCommon.h"

struct sRecord
{
	std::string resource;
	std::string login;
	std::string pasword;
};

class DataManager
{
public:
	static DataManager* getInstance();

	int addRecord(const sRecord& record);
	sRecord* getRecord(int index);
	int getCountRecords();

	void loadFromBuffer( void* buffer, unsigned int size);
	void saveToBuffer(void** buffer, unsigned int& size);

private:
	DataManager();
	~DataManager();

	std::vector< sRecord > mRecords;
};


#endif // !__DATA_MANAGER_H__
