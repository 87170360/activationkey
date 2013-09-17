#ifndef __RANDOM_LSX_H__
#define __RANDOM_LSX_H__

#include <string>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <map>

using namespace std;

typedef unsigned int UINT32;

//1 分配激活码范围
//2 设置礼包ID
//3 已使用 1-9675

const UINT32 KEY_BEGIN(9696);
const UINT32 KEY_END(9705);

const UINT32 RAND_SIZE(12);
UINT32 ONE((unsigned)time(NULL));
const UINT32 ALPHABET_SIZE(37);
const char alphabet[ALPHABET_SIZE] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
typedef std::map<UINT32, UINT32> UINT32UINT32MAP;
typedef UINT32UINT32MAP::const_iterator UINT32UINT32MAP_CITER;
UINT32UINT32MAP GiftMap;

void generateKey(UINT32 idx, string &str)
{
	for(UINT32 i = 0; i < RAND_SIZE; ++i)
	{
		srand(++ONE);
		int rad = rand();
		rad = rad > 0 ? rad : -rad;
		str.append(1, alphabet[rad % (ALPHABET_SIZE - 2)]);
	}

	char buffer[8] = {0};
	sprintf_s(buffer, 8, "%07lu", idx);
	str.append(buffer, 7);
	cout << str << endl;
}

UINT32 getGiftID(UINT32 index)
{
	UINT32UINT32MAP_CITER iter = GiftMap.find(index);
	if (iter != GiftMap.end())
	{
		return iter->second;
	}
	assert(0);
	return 0;
}

void initGiftID(void)
{
	for (UINT32 i = KEY_BEGIN; i <= KEY_END; ++i)
	{
		GiftMap[i] = 2520;
	}
}

#endif //__RANDOM_LSX_H__