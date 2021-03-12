#include "stdafx.h"
#include "shududata.h"

std::ostream & operator<<(std::ostream &os, const shududata &c)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (std::unordered_set<char>::iterator iter=c.data[i][j].begin();iter!=c.data[i][j].end();++iter)
			{
				os << char((*iter) + '0');
			}
			os << " ";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}

shududata::shududata()
{
}

shududata::~shududata()
{
}

size_t shududata::Traversal(char x, char y)
{
	std::unordered_set<char> set1_9;
	for(int i = 1;i <= 9;i++)
	{
		set1_9.insert(i);
	}
	for (int i = 0; i < 9; i++)
	{//遍历行
		if (data[x][i].size() == 1)
		{
			set1_9.erase(*data[x][i].begin());
		}
	}
	for (int i = 0; i < 9; i++)
	{//遍历列
		if (data[i][y].size() == 1)
		{
			set1_9.erase(*data[i][y].begin());
		}
	}
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
	{//遍历小宫
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
		{
			if (data[i][j].size() == 1)
			{
				set1_9.erase(*data[i][j].begin());
			}
		}
	}
	if (set1_9.size() != 0)
	{
		data[x][y] = set1_9;
	}
	return set1_9.size();//如果返回0,就是错误
}

bool shududata::start()
{
	bool b;
	do
	{
		if (!computer())return false;
		if (IsOver())
		{
			break;
		}
		else
		{//如果没有单解了,但还没搞完,就压栈从多解中选一个
			b = screanMuilP();
			if (!b)
			{
				b = screanNextIndex();
			}
		}
	} while (b);
	
	return IsOver();
}

bool shududata::computer()
{//遍历每个点,如果是还没解或多解的,就找解
	int iRet;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (data[i][j].size() != 1)
			{
				iRet = Traversal(i, j);
				if (iRet == 0)
				{//如果无解,就从栈中取下一个
					if (screanNextIndex())
					{
						computer();
					}
					else return false;
				}
				if (iRet == 1)
				{
					computer();// success = true;
				}
			}
		}
	}
	return true;
}

bool shududata::IsOver()
{//是否已经全解
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (data[i][j].size() != 1)
			{
				//std::cout << std::endl << *this << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool shududata::screanNextIndex()
{
	if (stacked.empty())
	{
		return false;
	}
	else
	{
		std::shared_ptr<datastack> ptr = stacked.top();
		ptr->currmuilpointsindex++;
		if (ptr->currmuilpointsindex != ptr->data[ptr->currmuilpointsd.x][ptr->currmuilpointsd.y].end())
		{//如果当前被看的多解点还有值可以试
			SetData(ptr->data);//重新初始化数据到栈顶状态
			data[ptr->currmuilpointsd.x][ptr->currmuilpointsd.y].clear();
			data[ptr->currmuilpointsd.x][ptr->currmuilpointsd.y].insert(*ptr->currmuilpointsindex);
			return true;
		}
		else
		{
			stacked.pop();
			//std::cout << "stacksize=" << stacked.size();
			return screanNextIndex();
		}
	}
}

bool shududata::screanMuilP()
{//查找还没看的最少的多解点
	POINTS p = { -1, -1 };
	POINTS ptemp;
	size_t s = 100, temp;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp = data[i][j].size();
			if(temp > 1)
			{
				if (temp < s)
				{//如果解数少
					ptemp.x = i;
					ptemp.y = j;
					s = temp;
					p = ptemp;
				}
			}
		}
	}
	if (p.x != -1)
	{
		std::shared_ptr<datastack> dstack = std::make_shared<datastack>();//要压栈的数据
		dstack->SetData(data);
		dstack->currmuilpointsindex = dstack->data[p.x][p.y].begin();//从被看的点的第一个数开始试
		dstack->currmuilpointsd = p;
		data[p.x][p.y].clear();
		data[p.x][p.y].insert(*dstack->currmuilpointsindex);
		stacked.push(dstack);
		return true;
	}
	return false;
}