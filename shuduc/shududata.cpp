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
	{//������
		if (data[x][i].size() == 1)
		{
			set1_9.erase(*data[x][i].begin());
		}
	}
	for (int i = 0; i < 9; i++)
	{//������
		if (data[i][y].size() == 1)
		{
			set1_9.erase(*data[i][y].begin());
		}
	}
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
	{//����С��
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
	return set1_9.size();//�������0,���Ǵ���
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
		{//���û�е�����,����û����,��ѹջ�Ӷ����ѡһ��
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
{//����ÿ����,����ǻ�û������,���ҽ�
	int iRet;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (data[i][j].size() != 1)
			{
				iRet = Traversal(i, j);
				if (iRet == 0)
				{//����޽�,�ʹ�ջ��ȡ��һ��
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
{//�Ƿ��Ѿ�ȫ��
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
		{//�����ǰ�����Ķ��㻹��ֵ������
			SetData(ptr->data);//���³�ʼ�����ݵ�ջ��״̬
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
{//���һ�û�������ٵĶ���
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
				{//���������
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
		std::shared_ptr<datastack> dstack = std::make_shared<datastack>();//Ҫѹջ������
		dstack->SetData(data);
		dstack->currmuilpointsindex = dstack->data[p.x][p.y].begin();//�ӱ����ĵ�ĵ�һ������ʼ��
		dstack->currmuilpointsd = p;
		data[p.x][p.y].clear();
		data[p.x][p.y].insert(*dstack->currmuilpointsindex);
		stacked.push(dstack);
		return true;
	}
	return false;
}