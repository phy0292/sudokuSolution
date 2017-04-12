#pragma once
#include "shududatabase.h"
#include "datastack.h"
class shududata : public shududatabase
{
private:
	std::stack<std::shared_ptr<datastack> > stacked;
	size_t Traversal(char x, char y);
	bool computer();
	bool IsOver();
	bool screanNextIndex();
	bool screanMuilP();//�������ٵĶ���
	friend std::ostream &operator<<(std::ostream &os, const shududata &c);
public:
	shududata();
	~shududata();
	bool start();
};

