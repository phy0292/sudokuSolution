// shuduc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "shududata.h"


int main()
{
	using namespace std;
	shududata dataclass;
	char c[9][9] = { {3,8,0,0,0,0,0,0,0},
					{0,0,0,3,4,0,0,9,0},
					{0,7,9,6,0,0,0,4,0},
					{2,1,7,0,0,4,0,0,0},
					{0,0,0,0,0,0,0,0,0},
					{0,0,0,5,0,0,2,1,7},
					{0,4,0,0,0,5,9,2,0},
					{0,5,0,0,3,1,0,0,0},
					{0,0,0,0,0,0,0,8,1}
	};
	/*for (int i = 0; i < 9; i++)
	{
		cout << "�������" << i + 1 << "�е�9������,ÿ�����ݿ����Կո����Ҳ���Բ��ÿո�,δ֪����0��ʾ" << endl;
		cin >> c[i][0] >> c[i][1] >> c[i][2] >> c[i][3] >> c[i][4] >> c[i][5] >> c[i][6] >> c[i][7] >> c[i][8];
	}*/
	dataclass.SetData(c);
	DWORD dwTick = GetTickCount();
	if (!dataclass.start())
	{
		cout << "�޽�!" << endl;
	}
	cout << dataclass;
	cout << "��ʱ:" << GetTickCount() - dwTick << "����" << endl;
	cin.get();
	cin.get();
	return 0;
}

