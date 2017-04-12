#include "stdafx.h"
#include "shududatabase.h"


shududatabase::shududatabase()
{
}

shududatabase::~shududatabase()
{
}

void shududatabase::SetData(char c[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (c[i][j] > 0x30)
			{//如果是字符,转成数字
				data[i][j].insert(c[i][j] - 0x30);
			}
			else if (c[i][j] != 0 && c[i][j] != 0x30)
			{
				data[i][j].insert(c[i][j]);
			}
		}
	}
}

void shududatabase::SetData(std::unordered_set<char> _data[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			data[i][j] = _data[i][j];
		}
	}
}