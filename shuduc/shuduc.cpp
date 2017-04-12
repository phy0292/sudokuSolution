// shuduc.cpp : 定义控制台应用程序的入口点。
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
		cout << "请输入第" << i + 1 << "行的9个数据,每个数据可以以空格隔开也可以不用空格,未知的用0表示" << endl;
		cin >> c[i][0] >> c[i][1] >> c[i][2] >> c[i][3] >> c[i][4] >> c[i][5] >> c[i][6] >> c[i][7] >> c[i][8];
	}*/
	dataclass.SetData(c);
	DWORD dwTick = GetTickCount();
	if (!dataclass.start())
	{
		cout << "无解!" << endl;
	}
	cout << dataclass;
	cout << "耗时:" << GetTickCount() - dwTick << "毫秒" << endl;
	cin.get();
	cin.get();
	return 0;
}

