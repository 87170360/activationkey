/*************************************************
Copyright liushuxin. All rights reserved.
Author: liushuxin, linux.book.heart@gmail.com
Date:2013-09-18
Description:产生激活码
**************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "randomkey.h"

using namespace std;
const UINT32 MAX_BUFF_SIZE(1024);

/*
int main(int argc, char* argv[])
{
	std::vector<ReadData> m_config;
	m_config = parseInputFile();
    return 0;
}
*/


int main(int argc, char* argv[])
{
	std::vector<ReadData> m_config;
	m_config = parseInputFile();
	assert(m_config.size());
	
	char buff[MAX_BUFF_SIZE] = {0};
	//格式 时间-序号mix-max.csv

	char namebuff[120] = {0};
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	sprintf_s(namebuff, 120, "%lu-%lu@%d%02d%02d%02d%02d%02d.csv",
		m_config.begin()->config[0], 
		m_config.back().config[1],
		timeinfo.tm_year + 1900,
		timeinfo.tm_mon,
		timeinfo.tm_mday,
		timeinfo.tm_hour,
		timeinfo.tm_min,
		timeinfo.tm_sec);
	ofstream of(namebuff, ofstream::binary);


	initGiftID(m_config);

	string strTmp;
	strTmp.clear();
	strTmp = "Id,Key,GiftId\r\n注释\r\n";
	sprintf_s(buff, MAX_BUFF_SIZE, strTmp.c_str());
	of.write(buff, strTmp.size());

	char buffidx[120] = {0};
	memset(buffidx, 0, 120);
	for(std::vector<ReadData>::const_iterator iter = m_config.begin(); iter != m_config.end(); ++iter)
	{
		for (UINT32 i = iter->config[0]; i <= iter->config[1]; ++i)
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
	}
	of.close();
	return 0;
}
