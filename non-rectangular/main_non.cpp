#include <graphics.h>
#include <conio.h>

int main()
{
	initgraph(200, 200);			// ��ʼ��ͼ�δ���
	HWND hWnd = GetHWnd();			// ��ȡ���ھ��

	// ��ȡ���ڱ߿���
	RECT rcClient, rcWind;
	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWind);
	int cx = ((rcWind.right - rcWind.left) - rcClient.right) / 2;
	int cy = ((rcWind.bottom - rcWind.top + GetSystemMetrics(SM_CYCAPTION)) - rcClient.bottom) / 2;

	// ����Բ������
	HRGN rgn = CreateEllipticRgn(0 + cx, 0 + cy, 200 + cx, 200 + cy);
	SetWindowRgn(hWnd, rgn, true);

	// ���ʺ���
	setlinestyle(PS_SOLID, 2);
	for (int r = 99; r > 0; r--)
	{
		setlinecolor(HSLtoRGB(360 - r * 3.6f, 1, 0.5));
		circle(99, 99, r);
	}

	ExMessage m;						// ���������Ϣ

	while (true)
	{
		m = getmessage(EM_MOUSE);		// ��ȡһ�������Ϣ

		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			// ���������£���ƭ windows �����˱�������
			PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
			break;

		case WM_RBUTTONUP:			// ������Ҽ��˳�����
			closegraph();
			return 0;
		}
	}
}