// ���뻷����Win10 + VS2019 + EasyX_20200727
//

// �趨����ϵͳ�汾Ϊ Win10����Ҫ�ŵ� #include <graphics.h> ǰ�棩
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <graphics.h>
#include <conio.h>
#include <ShellScalingApi.h>		// ����ͷ�ļ�
#pragma comment(lib, "Shcore.lib")	// ���ӿ��ļ�

int main()
{
	// ���øý��̲���ϵͳ DPI ����Ӱ��
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	// ����ͼ�δ��ڣ�����һ��Բ
	initgraph(640, 480);
	circle(320, 240, 200);

	// ��������رջ�ͼ����
	_getch();
	closegraph();
	return 0;
}