#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "randomkey.h"

using namespace std;
const UINT32 MAX_BUFF_SIZE(1024);

int main(int argc, char* argv[])
{
	char buff[MAX_BUFF_SIZE] = {0};
	//格式 时间-序号mix-max.csv

	char namebuff[120] = {0};
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	sprintf_s(namebuff, 120, "%lu-%lu@%d%02d%02d%02d%02d%02d.csv",
		KEY_BEGIN, 
		KEY_END,
		timeinfo.tm_year + 1900,
		timeinfo.tm_mon,
		timeinfo.tm_mday,
		timeinfo.tm_hour,
		timeinfo.tm_min,
		timeinfo.tm_sec);
	ofstream of(namebuff, ofstream::binary);

	initGiftID();

	string strTmp;
	strTmp.clear();
	strTmp = "Id,Key,GiftId\r\n注释\r\n";
	sprintf_s(buff, MAX_BUFF_SIZE, strTmp.c_str());
	of.write(buff, strTmp.size());

	char buffidx[120] = {0};
	memset(buffidx, 0, 120);
	for (UINT32 i = KEY_BEGIN; i <= KEY_END; ++i)
	{
		strTmp.clear();
		memset(buffidx, 0, 120);
		sprintf_s(buffidx, 120, "%07lu,", i);
		strTmp.append(buffidx, 8);
		sprintf_s(buff, MAX_BUFF_SIZE, strTmp.c_str());
		of.write(buff, strTmp.size());

		strTmp.clear();
		memset(buff, 0, MAX_BUFF_SIZE);
		generateKey(i, strTmp);
		sprintf_s(buff, MAX_BUFF_SIZE, strTmp.c_str());
		of.write(buff, strTmp.size());

		strTmp.clear();
		memset(buffidx, 0, 120);
		sprintf_s(buffidx, 120, ",%07lu", getGiftID(i));
		strTmp.append(buffidx, 8);
		sprintf_s(buff, MAX_BUFF_SIZE, strTmp.c_str());
		of.write(buff, strTmp.size());

		memset(buff, 0, MAX_BUFF_SIZE);
		sprintf_s(buff, MAX_BUFF_SIZE, "\r\n");
		of.write(buff, 1);
	}

	of.close();
	return 0;
}