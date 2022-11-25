/**********************************************************
 项目名称：计算器
 编译环境：Visual Studio 2017 Community + EasyX_20190219(beta)
 发布日期：2019-1-21
 作　　者：尔灵尔亿
 邮　　箱：2117610943@qq.com
 最后修改：2019-2-28
**********************************************************/

/***************头文件***************/
#include "set.h"
#include "help.h"
#include "science.h"
#include "standard.h"
#include "loadimage.h"
#include "bignumber.h"
#include "conversion.h"
#include "transparent.h"
#include "SolveSolution.h"
#include "transformation.h"



// 函数指针
void(*FP[][2])() = { {updatewithinput0, showscreen0}, {updatewithinput_, showscreen_}, {updatewithinput,  showscreen},
					 {updatewithinput1, showscreen1}, {updatewithinput2, showscreen2}, {updatewithinput3, showscreen3},
				     {updatewithinput5, showscreen5}, {updatewithinput6, showscreen6}, {updatewithinput7, showscreen7},
				     {updatewithinput8, showscreen8}, {updatewithinput9, showscreen9}, {updatewithinput10,showscreen10},
				     {updatewithinput11,showscreen11},{updatewithinput12,showscreen12},{updatewithinput13,showscreen13},
				     {updatewithinput14,showscreen14},{updatewithinput15,showscreen15},{updatewithinput16,showscreen16}, 
                     {updatewithinput4, showscreen4}
};


int main()
{
	initgraph(400, 600);					// 窗口大小
	SetWindowText(GetHWnd(), _T("计算器"));	// 标题

	while (true)
	{
		int k = software[0] + 1;
		if (k == 18 && !_tcslen(SS))		// 如果没有加载文件
			loadtext();
		if (k >= 6 && k <= 17)MemStr();		// 初始化转换关系

		while (true)
		{
			for (int i = 0; i < 2; i++)
				FP[k][i]();
			if (k != software[0] + 1)
				break;
			Sleep(20);						// 延时
		}
	}
	return 0;
}

