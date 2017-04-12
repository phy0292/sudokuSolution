#pragma once
#include "shududatabase.h"
class datastack : public shududatabase
{
public:
	POINTS currmuilpointsd;// 当前在看的多解点.
	std::unordered_set<char>::iterator currmuilpointsindex;//当前看的多解点的第index索引正被看
public:
	datastack();
	~datastack();
};

