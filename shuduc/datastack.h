#pragma once
#include "shududatabase.h"
class datastack : public shududatabase
{
public:
	POINTS currmuilpointsd;// ��ǰ�ڿ��Ķ���.
	std::unordered_set<char>::iterator currmuilpointsindex;//��ǰ���Ķ���ĵ�index����������
public:
	datastack();
	~datastack();
};

