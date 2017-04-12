#pragma once
#ifdef __linux__
typedef struct _points
{
	short x;
	short y;
}POINTS;
#else
#include <windows.h>
#endif
class shududatabase
{
public:
	std::unordered_set<char> data[9][9];
	void SetData(char c[9][9]);
	void SetData(std::unordered_set<char> _data[9][9]);
	shududatabase();
	~shududatabase();
};

