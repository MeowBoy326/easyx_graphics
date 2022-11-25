/*****************************************************************
* �������ƣ�������� V3.0
* ���뻷����Microsoft Visual Studio 2017��EasyX_20190314(beta)
* �������ߣ�ϯ��
* �ʡ����䣺no1xijin@126.com
* �������ڣ�2019-02-22
* ����޸ģ�2019-03-31
*****************************************************************/
//-----ͷ�ļ�
#include <stdio.h>
#include <graphics.h>					// ����ͼ�ο�ͷ�ļ�
#include <conio.h>						// ����������⺯��
#include <locale.h>						// �����ַ�����ת��Ϊunicode�������Ϣ
#include <io.h>							// ��������_waccess()�����ж��ļ��л����ļ��Ƿ����
#pragma comment(lib,"winmm.lib")		// �����������������ͷ�ļ�
#pragma comment( lib, "MSIMG32.LIB")	// ���øÿ����ʹ�� AlphaBlend ����

//-----�궨����ų���
// С��Ƭ��ʵʱ������Ƭ����Ƭ��Ӧ���ֵ����ֵ
#define myMAX 50
// �汾��Ϣ
const wchar_t wPROGRAMINFO[] = _T("�������ƣ�������� V3.0 \n�������ߣ�ϯ�� \n����ʱ�䣺2019��3��31�� \n��ϵ���䣺no1xijin@126.com \n\n����˵����\n1.���С��Ƭ��������Ӧ�Ĵ���Ƭ����Ƭӡ�� \n2.�����ͬ�Ĺ���ͼ�꽫������ͬ��Ч�� \n3.֧�ְ���wsad��������,���÷ֱ��������ƶ������ҷ�ҳ \n4.֧����ת����������Ƭ \n5.֧������DIY��������������readme.txt��Set.ini����ϵ���ߣ� \n6.rc�ļ�Ϊ����ͼ�꣬�����޸� \n7.resΪ����DIY���������ļ��У��������ݽԿ��޸�");

//-----�洢 Set.ini ���ñ���ֵ��ȫ�ֱ���
// �洢[Window]�ڵ�����
struct iniWindow
{
	int		width;		// ���ڿ�
	int		height;		// ���ڸ�
	wchar_t	name[300];	// ���ڱ���
};
iniWindow myWindow;

// �洢[BkMusic]�ڵ�����
wchar_t  bkMusic[300];	// ��������·��

// �洢[HomeScreen]�ڵ�����
struct iniHomeScreen
{
	wchar_t	photo[300];	// ������ͼƬ·��
	int		pX;			// ������ͼƬ������
	int		pY;			// ������ͼƬ������
	int		adjust;		// �Ƿ����������ͼƬ��С
	int		width;		// ������ͼƬ��
	int		height;		// ������ͼƬ��
};
iniHomeScreen myHomeScreen;

// �洢[Tool*]�ڵ�����(ToolAbout��ToolSet��ToolRefresh��ToolBuzzer��ToolUp��ToolDown��ToolLeft��ToolRight��ToolPlay��ToolGoto)
struct iniTool
{
	int		isShow;		// ����-* �Ƿ���ʾ��0����ʾ��1��ʾ
	int		size;		// ����-* �ߴ�
	long	color;		// ����-* ��ɫ
	int		pX;			// ����-* ������
	int		pY;			// ����-* ������
};
// ����-*�������ԣ�����Ϊ ���ڡ����á�ˢ�¡����ȡ����ơ����ơ���(��)������(��)�����Զ����������ת
iniTool myAbout, myRefresh, myBuzzer, myUp, myDown, myLeft, myRight, myPlay, myGoto;

// �洢[DecoratePicture]�ڵ�����
struct iniDecoratePicture
{
	int		isValid;	// �Ƿ����װ����ͼƬ��0�ޣ�1��
	int		number;		// װ����ͼƬ������
	wchar_t	res[300];	// װ����ͼƬ·��������
	int		width;		// װ����ͼƬ��
	int		height;		// װ����ͼƬ��
	int		pX;			// װ����ͼƬ������
	int		pY;			// װ����ͼƬ������
};
iniDecoratePicture  myDecoratePicture[myMAX];	// װ����ͼƬ����Ϊ��0��myMAX

// �洢[DecorateTxt]�ڵ�����
struct iniDecorateTxt
{
	int		isValid;	// �Ƿ����װ�������֣�0�ޣ�1��
	int		number;		// װ��������������
	wchar_t	res[300];	// װ������������
	int		width;		// װ����������ʾ�����
	int		height;		// װ����������ʾ�����
	int		pX;			// װ����������ʾ��ʼ������
	int		pY;			// װ����������ʾ��ʼ������
	int		size;		// װ�������������С
	wchar_t	font[50];	// װ������������
	long	color;		// װ��������������ɫ
	int		IsBk;		// װ�������ֱ�����ɫ�������0�ޣ�1��
	long	bkColor;	// װ�������ֱ�����ɫ
};
iniDecorateTxt  myDecorateTxt[myMAX];	// װ������������Ϊ��0��myMAX

// �洢[SmallPhoto]�ڵ�����
struct iniSmallPhoto
{
	int		number;		// С��Ƭ����
	int		width;		// С��Ƭ��
	int		height;		// С��Ƭ��
	int		pX;			// С��Ƭ������
	int		pY;			// С��Ƭ������
	long	color;		// С��Ƭ�߿���ɫ
};
iniSmallPhoto mySmallPhoto[myMAX];	// С��Ƭ����Ϊ��1��myMAX

// �洢[BigPhoto]�ڵ�����
struct iniBigPhoto
{
	int		width;		// ����Ƭ��
	int		height;		// ����Ƭ��
	int		pX;			// ����Ƭ������
	int		pY;			// ����Ƭ������
	int		snPX;		// ����Ƭ��������Ƭ�е������ʾ��ʼ������
	int		snPY;		// ����Ƭ��������Ƭ�е������ʾ��ʼ������
	int		snSize;		// ����Ƭ��������Ƭ�е���������С
	wchar_t	snFont[50];	// ����Ƭ��������Ƭ�е��������
	long	snColor;	// ����Ƭ��������Ƭ�е����������ɫ
	int		snIsBk;		// ����Ƭ��������Ƭ�е���ű�����ɫ�������0�ޣ�1��
	long	snBkColor;	// ����Ƭ��������Ƭ�е���ű�����ɫ
};
iniBigPhoto myBigPhoto;

// �洢[photo]�ڵ�����
int			photoNumber;			// �����������Ƭ����
wchar_t		myPhoto[myMAX][300];	// ʵʱ���ص���Ƭ·��������������С��Ƭ����һ�£���ΧΪ��1-myMAX

// �洢[photoTxt*]�ڵ�����
struct iniphotoTxt
{
	wchar_t	res[300];	// ��Ƭ��Ӧ��������
	int		width;		// ��Ƭ��Ӧ������ʾ��
	int		height;		// ��Ƭ��Ӧ������ʾ��
	int		pX;			// ��Ƭ��Ӧ������ʾ��ʼ������
	int		pY;			// ��Ƭ��Ӧ������ʾ��ʼ������
	int		size;		// ��Ƭ��Ӧ���������С
	wchar_t	font[50];	// ��Ƭ��Ӧ��������
	long	color;		// ��Ƭ��Ӧ����������ɫ
	int		IsBk;		// ��Ƭ��Ӧ���ֱ�����ɫ�������0�ޣ�1��
	long	bkColor;	// ��Ƭ��Ӧ���ֱ�����ɫ
};
iniphotoTxt myPhotoTxt[myMAX];	// ʵʱ������Ƭ��Ӧ���֣�����������С��Ƭ����һ�£���ΧΪ��1-myMAX

// �洢��������Ҫ�õ���һЩȫ�ֱ��
struct allFlag
{
	long	mysmallPhotoNumberInAll;	// С��Ƭ��ʾ��һ����������Ƭ�еı��
	int		mysmallPhotoNumberInsmall;	// ѡ�е�С��Ƭ����ʾ��С��Ƭ�еı��
	long	myBigPhotoNumberInAll;		// ��ʾ�Ĵ���Ƭ��������Ƭ�еı��
	int		myBuzzerFlag;				// ��ǵ�ǰ�������ֲ���״̬��0��ͣ��1����
	int		myUpFlag;					// ��ǵ�ǰ�ܷ����ƣ�0���ܣ�1��
	int		myDownFlag;					// ��ǵ�ǰ�ܷ����ƣ�0���ܣ�1��
	int		myLeftFlag;					// ��ǵ�ǰ�ܷ���(��)����0���ܣ�1��
	int		myRightFlag;				// ��ǵ�ǰ�ܷ���(��)����0���ܣ�1��
	int		myPlayFlag;					// ��ǵ�ǰ���Զ�ѭ�����Ż����ֶ���0�Զ���1�ֶ�
	long	myGotoFlag;					// ����û����������ת��������Ƭ��ֵ
	HWND	hwnd;						// ���ھ��������������ơ���ʾ��Ϣʱ��
};
allFlag myAllFlag;

//-----��������
// ��������������
void demo();
// �������ļ�Set.ini����ȡ�������ݸ�ȫ�ֱ�����ֵ������ֵ0������-1�쳣����δ���÷���ֵ
int readSet();
// ʵʱ��ȡ��Ƭ����Ƭӡ����������
void realTimeReadSet();
// ��������ʱ��������ˢ����ʾ�Ľ���,���������ֲ��Ų���
void demoShow();
// ��͸����ͼ����
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
// ������������ʱ��Ӧ������,����������,����ֵ0�����˳���1ˢ�³���
int MouseHandle();

/*
*������:main()
*��������:������
*����˵��:��
*����0������-1�쳣����δ���÷���ֵ
*/
int main()
{
	// ��ʼ��һЩȫ�ֱ�Ǳ���
	myAllFlag.myBuzzerFlag = 1;
	// ��ǵ�ǰ�������ֲ���״̬��0��ͣ��1����
	myAllFlag.myUpFlag = 0;
	// ��ǵ�ǰ�ܷ����ƣ�0���ܣ�1��
	myAllFlag.myDownFlag = 0;
	// ��ǵ�ǰ�ܷ����ƣ�0���ܣ�1��
	myAllFlag.myLeftFlag = 0;
	// ��ǵ�ǰ�ܷ���(��)����0���ܣ�1��
	myAllFlag.myRightFlag = 0;
	// ��ǵ�ǰ�ܷ���(��)����0���ܣ�1��
	myAllFlag.mysmallPhotoNumberInAll = 0;
	// С��Ƭ��ʾ��һ����������Ƭ�еı��
	myAllFlag.mysmallPhotoNumberInsmall = 0;
	// ѡ�е�С��Ƭ����ʾ��С��Ƭ�еı��
	myAllFlag.myBigPhotoNumberInAll = 0;
	// ��ʾ�Ĵ���Ƭ��������Ƭ�еı��
	myAllFlag.myPlayFlag = 1;
	// ��ǵ�ǰ���Զ�ѭ�����Ż����ֶ���0�Զ���1�ֶ�
	myAllFlag.myGotoFlag = 0;
	// ����û����������ת��������Ƭ��ֵ

	demo();			// �����������ӿ�

	closegraph();	// �رջ�ͼ����

	return 0;		// �˳�
}

/*
*������:demo()
*��������:��������������
*����˵��:��
*������
*/
void demo()
{
	wchar_t temp[300];
	int		i;
	while (1)	// ˢ��ʱʹ��
	{
		readSet();			// �������ļ�
		realTimeReadSet();	// ʵʱ��ȡ�������ļ�-С��Ƭ�Ͷ�Ӧ����

		/*
		*_waccess�����ж��ļ��л����ļ��Ƿ����
		*����ԭ�ͣ� int _waccess( const wchar_t *path, int mode );
		*����ͷ�ļ���io.h
		*path��������д�ļ���·�������ļ�·��
		*mode��0 ��F_OK�� ֻ�ж��Ƿ����
		*      2 ��R_OK�� �ж�д��Ȩ��
		*      4 ��W_OK�� �ж϶�ȡȨ��
		*      6 ��X_OK�� �ж�ִ��Ȩ��
		*�����ж��ļ����Ƿ���ڵ�ʱ��modeȡ0���ж��ļ��Ƿ���ڵ�ʱ��;mode����ȡ0��2��4��6��
		*�����ڻ��߾���Ȩ�ޣ�����ֵΪ0�������ڻ�����Ȩ�ޣ�����ֵΪ-1��
		*/
		if (_waccess(bkMusic, 0) < 0)	// ��鱳�������Ƿ���ڣ�����������ֹͣ���б�����
		{
			_stprintf_s(temp, _T("��������(%s)��Դȱʧ�������޷��������С�\n��ȷ�������ִ�����·����������ȷ��"), bkMusic);
			MessageBox(myAllFlag.hwnd, temp, _T("����������Դȱʧ"), MB_OK | MB_ICONHAND);
			exit(0);
		}

		_stprintf_s(temp, _T("open %s alias backGroundMp3"), bkMusic);
		i = mciSendString(temp, NULL, 0, NULL);	// ���ر������ֳɹ�����0�����򷵻ش�����롣���سɹ��򽫱��������ñ���backGroundMp3����,���سɹ���ǵ���close����Ա������ֵ�ռ��
		if (0 != i)
		{
			_stprintf_s(temp, _T("��������(%s)��Դ����ʧ�ܣ������޷��������С�\n��ȷ��������δ����������ռ�ã�"), bkMusic);
			MessageBox(myAllFlag.hwnd, temp, _T("����������Դ����ʧ��"), MB_OK | MB_ICONHAND);
			exit(0);
		}
		i = mciSendString(_T("play backGroundMp3 repeat"), NULL, 0, NULL);	// ѭ�����ű������ֳɹ�����0�����򷵻ش������
		if (0 != i)
		{
			mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// ���ű�������ʧ�ܣ�����Ա������ֵ�ռ��	
			_stprintf_s(temp, _T("��������(%s)��Դ����ʧ�ܣ������޷��������С�\n��ȷ��������δ����������ռ�ã�"), bkMusic);
			MessageBox(myAllFlag.hwnd, temp, _T("����������Դ����ʧ��"), MB_OK | MB_ICONHAND);
			exit(0);
		}

		myAllFlag.myBuzzerFlag = 1;						// ��ǵ�ǰ�������ֲ���״̬��0��ͣ��1����

		initgraph(myWindow.width, myWindow.height);		// ����ͼ�δ���
		cleardevice();									// �õ�ǰ����ɫ�����Ļ��������ǰ������ (0, 0)��
		myAllFlag.hwnd = GetHWnd();						// ��ȡ���ھ��
		SetWindowText(myAllFlag.hwnd, myWindow.name);	// ������ᴰ������

		demoShow();										// ��ʾ������

		i = MouseHandle();								// ������������ʱ��Ӧ�����ֵ������,����ֵ0�����˳���1ˢ�³���
		if (i < 0)
			break;
	}
}


/*
*������:MouseHandle()
*��������:������������ʱ��Ӧ������
*����˵��:��
*����ֵ0�����˳���1ˢ�³���
*/
int MouseHandle()
{
	MOUSEMSG	mou;	// ������
	int			delay;	// �Զ�����ʱ����ʱֵ
	char		c;		// �ݴ水����Ϣ
	wchar_t		temp[300];
	int			i;
	int			showflag = 0;	//	���ѭ��ʱ�����ͼ���ı��

	while (1)
	{
		// ����Ƿ����Զ�����״̬
		if (myAllFlag.myPlayFlag < 1)	// ��ǵ�ǰ���Զ�ѭ�����Ż����ֶ���0�Զ���1�ֶ�
		{
			// �Զ����Ų���
			delay = myPlay.isShow;		// ����myPlay.isShow��ֵ��ʵ����ʱ���������й����в��ı�myPlay.isShow��ֵ
			while (1)
			{
				Sleep(1);				// ��ʱ1����
				delay--;
				if (delay < 1)
				{
					break;
				}
				// ���������Ϣ-��Ӧ�������-���ڡ����ȡ� �Զ��������ֶ������л�
				while (MouseHit())					// ���������Ϣ��ʱ��ִ��
				{
					mou = GetMouseMsg();			// ���һ�������Ϣ
					if (mou.uMsg == WM_LBUTTONUP)	// ����������(1)
					{
						if (myAbout.isShow > 0 && mou.x > myAbout.pX && mou.x < (myAbout.pX + myAbout.size) && mou.y > myAbout.pY && mou.y < (myAbout.pY + myAbout.size))
						{
							// ��Ӧ ����-����
							MessageBox(myAllFlag.hwnd, wPROGRAMINFO, _T("����"), MB_OK | MB_ICONASTERISK);
							showflag = 0;
						}
						else if (myBuzzer.isShow > 0 && mou.x > myBuzzer.pX && mou.x < (myBuzzer.pX + myBuzzer.size) && mou.y > myBuzzer.pY && mou.y < (myBuzzer.pY + myBuzzer.size))
						{
							// ��Ӧ ����-����
							if (myAllFlag.myBuzzerFlag > 0)
							{
								mciSendString(_T("stop backGroundMp3"), NULL, 0, NULL);		// ֹͣ��������
								myAllFlag.myBuzzerFlag = 0;									// ���ֹͣ��������
								mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// ����Ա������ֵ�ռ��	
							}
							else
							{
								_stprintf_s(temp, _T("open %s alias backGroundMp3"), bkMusic);
								i = mciSendString(temp, NULL, 0, NULL);	// ���ر������ֳɹ�����0�����򷵻ش�����롣���سɹ��򽫱��������ñ���backGroundMp3����,���سɹ���ǵ���close����Ա������ֵ�ռ��
								if (0 != i)
								{
									_stprintf_s(temp, _T("��������(%s)��Դ����ʧ�ܣ������޷��������С�\n��ȷ��������δ����������ռ�ã�"), bkMusic);
									MessageBox(myAllFlag.hwnd, temp, _T("����������Դ����ʧ��"), MB_OK | MB_ICONHAND);
									exit(0);
								}
								i = mciSendString(_T("play backGroundMp3 repeat"), NULL, 0, NULL);	// ѭ�����ű������ֳɹ�����0�����򷵻ش������
								if (0 != i)
								{
									mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// ���ű�������ʧ�ܣ�����Ա������ֵ�ռ��	
									_stprintf_s(temp, _T("��������(%s)��Դ����ʧ�ܣ������޷��������С�\n��ȷ��������δ����������ռ�ã�"), bkMusic);
									MessageBox(myAllFlag.hwnd, temp, _T("����������Դ����ʧ��"), MB_OK | MB_ICONHAND);
									exit(0);
								}
								myAllFlag.myBuzzerFlag = 1;	// ��ǵ�ǰ�������ֲ���״̬��0��ͣ��1����
							}
							showflag = 1;
						}
						else if (myPlay.isShow > 0 && mou.x > myPlay.pX && mou.x < (myPlay.pX + myPlay.size) && mou.y > myPlay.pY && mou.y < (myPlay.pY + myPlay.size))
						{
							// ��Ӧ ����-�Զ��������ֶ�����,�˲��ֽ������Զ��л����ֶ�����
							i = MessageBox(myAllFlag.hwnd, _T("��ǰΪ�Զ����ţ��Ƿ��л����ֶ����ţ�"), _T("�Զ������л����ֶ�����"), MB_YESNO | MB_ICONQUESTION);
							if (IDYES == i)
							{
								myAllFlag.myPlayFlag = 1;
							}
						}
					}
				}
			}
			if (myAllFlag.myPlayFlag > 0)	// ��ǵ�ǰ���Զ�ѭ�����Ż����ֶ���0�Զ���1�ֶ�
			{
				demoShow();					//	��ˢ�½����е��Զ����ţ�����Ҫ����С��Ƭ����Ӧ�����֣���˵�������
				continue;					// ��ʱ��Ӧ�Զ������л��ֶ����ţ����Զ�����ʱ�л�Ϊ�ֶ������ˣ��򲻼������£����Ǽ�ӵ��˳��Զ�����ģʽ�������ֶ�����
			}
			myAllFlag.mysmallPhotoNumberInsmall++;	// С��Ƭ�Լ�1
			if ((myAllFlag.mysmallPhotoNumberInsmall < mySmallPhoto[0].number) && (myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll < photoNumber))	// �Ƿ���Ҫ���·�ҳ
			{
				// ����Ҫ��ҳ
				showflag = 2;
			}
			else
			{
				// ��Ҫ���·�ҳ
				if (myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll < (photoNumber - 1))	// �Ƿ���Ҫ��0
				{
					myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// ����ʾ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
					myAllFlag.mysmallPhotoNumberInsmall = 0;
				}
				else	// ��0
				{
					myAllFlag.mysmallPhotoNumberInsmall = 0;
					myAllFlag.mysmallPhotoNumberInAll = 0;
				}
				showflag = 2;
			}

			// �����Զ����Ų��ֵĻ�ͼ
			if (showflag > 1)
			{
				myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı��
				realTimeReadSet();	// ʵʱ��ȡ��Ƭ����Ƭ��Ӧ������Ϣ���Ա���ˢ��ʱ����Ϣ�����µ�
				demoShow();			// ������ͼ��ˢ����������
			}
			else if (showflag > 0)
			{
				demoShow();			// j = 1ʱ��������ͼ��ˢ����������
			}
			else
			{
				;	// j = 0ʱ���޲���������ʱ
			}
		}
		else
		{
			// �ֶ����Ų���
			// �ֶ����Ų���Ӧ����
			while (_kbhit())				// ���м�����Ϣ��ʱ��ִ��
			{
				c = _getch();
				if (c == 0xE0 || c == 0)	// ��ȡ�����԰����������Ҽ�ͷ
				{
					c = _getch();
				}
				switch (c)
				{
				case 'W':
				case 'w':
				case 72:	// �����԰��� ��
					// ����һλ
					if (myAllFlag.mysmallPhotoNumberInsmall < 1)	// ��ǰ�޷�����
					{
						// ����ܷ��Ϸ�ҳ
						if (myAllFlag.myUpFlag > 0)	// ���Ϸ�
						{
							myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// ����ʾ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
							if (myAllFlag.mysmallPhotoNumberInAll < 0)	// �Ϸ�������ʾ����ҳ
							{
								myAllFlag.mysmallPhotoNumberInAll = 0;	// ������Ƭ��Դ�еĵ�һ��
							}
							myAllFlag.mysmallPhotoNumberInsmall = mySmallPhoto[0].number - 1;	//	��С��Ƭ��С��Ƭ�еı������Ϊ���һ��
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı��
							showflag = 2;
						}
						else
						{
							showflag = 0;
						}
					}
					else
					{
						myAllFlag.mysmallPhotoNumberInsmall -= 1;
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı��
						showflag = 2;
					}
					break;
				case 'S':
				case 's':
				case 80:	// �����԰��� ��
					// ����һλ
					if ((myAllFlag.mysmallPhotoNumberInsmall == mySmallPhoto[0].number - 1) || ((myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 2)))	// ��ǰ��������
					{
						// ����ܷ��·�ҳ
						if (myAllFlag.myDownFlag > 0)	// ���·�ҳ
						{
							myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
							myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 			
							showflag = 2;
						}
						else
						{
							showflag = 0;
						}
					}
					else
					{
						myAllFlag.mysmallPhotoNumberInsmall += 1;
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 			
						showflag = 2;
					}
					break;
				case 'A':
				case 'a':
				case 75:	// �����԰��� ��
					// �Ϸ�һҳ
					// ����ܷ��Ϸ�ҳ
					if (myAllFlag.myLeftFlag > 0)
					{
						myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// ����ʾ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
						if (myAllFlag.mysmallPhotoNumberInAll < 0)	// �Ϸ��ܷ���ʾ����ҳ
						{
							myAllFlag.mysmallPhotoNumberInAll = 0;	// ������Ƭ��Դ�еĵ�һ��
						}
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 			
						showflag = 2;
					}
					else
					{
						//MessageBox(myAllFlag.hwnd, _T("�Ѿ������ˣ��޷��Ϸ�!"), _T("�Ϸ�ʧ��"), MB_OK | MB_ICONHAND);
						showflag = 0;
					}
					break;
				case 'D':
				case 'd':
				case 77:	// �����԰��� ��
					// �·�һҳ
					// ����ܷ��·�ҳ
					if (myAllFlag.myRightFlag > 0)
					{
						myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 	
						showflag = 2;
					}
					else
					{
						//MessageBox(myAllFlag.hwnd, _T("�Ѿ������ˣ��޷��·�!"), _T("�·�ʧ��"), MB_OK | MB_ICONHAND);
						showflag = 0;
					}
					break;
				}
			}
			while (MouseHit())					// ���������Ϣ��ʱ��ִ��
			{
				mou = GetMouseMsg();			// ���һ�������Ϣ
				if (mou.uMsg == WM_LBUTTONUP)	// ����������(1)
				{
					// ��Ӧ����Ƭ��ʾ������
					if (myAbout.isShow > 0 && mou.x > myAbout.pX && mou.x < (myAbout.pX + myAbout.size) && mou.y > myAbout.pY && mou.y < (myAbout.pY + myAbout.size))
					{
						// ��Ӧ ����-����
						MessageBox(myAllFlag.hwnd, wPROGRAMINFO, _T("����"), MB_OK | MB_ICONASTERISK);
						showflag = 0;
					}
					else if (myRefresh.isShow > 0 && mou.x > myRefresh.pX && mou.x < (myRefresh.pX + myRefresh.size) && mou.y > myRefresh.pY && mou.y < (myRefresh.pY + myRefresh.size))
					{
						// ��Ӧ ����-ˢ��
						closegraph();		// �رջ�ͼ����
						mciSendString(_T("stop backGroundMp3"), NULL, 0, NULL);	// ֹͣ��������
						myAllFlag.myBuzzerFlag = 0;	// ���ֹͣ��������
						mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// ���ű�������ʧ�ܣ�����Ա������ֵ�ռ��	
						return 1;	//	ͨ������ֵ���������б�����һ��
					}
					else if (myBuzzer.isShow > 0 && mou.x > myBuzzer.pX && mou.x < (myBuzzer.pX + myBuzzer.size) && mou.y > myBuzzer.pY && mou.y < (myBuzzer.pY + myBuzzer.size))
					{
						// ��Ӧ ����-����
						if (myAllFlag.myBuzzerFlag > 0)
						{
							mciSendString(_T("stop backGroundMp3"), NULL, 0, NULL);	// ֹͣ��������
							myAllFlag.myBuzzerFlag = 0;	// ���ֹͣ��������
							mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// ���ű�������ʧ�ܣ�����Ա������ֵ�ռ��	
						}
						else
						{
							_stprintf_s(temp, _T("open %s alias backGroundMp3"), bkMusic);
							i = mciSendString(temp, NULL, 0, NULL);	// ���ر������ֳɹ�����0�����򷵻ش�����롣���سɹ��򽫱��������ñ���backGroundMp3����,���سɹ���ǵ���close����Ա������ֵ�ռ��
							if (0 != i)
							{
								_stprintf_s(temp, _T("��������(%s)��Դ����ʧ�ܣ������޷��������С�\n��ȷ��������δ����������ռ�ã�"), bkMusic);
								MessageBox(myAllFlag.hwnd, temp, _T("����������Դ����ʧ��"), MB_OK | MB_ICONHAND);
								exit(0);
							}
							i = mciSendString(_T("play backGroundMp3 repeat"), NULL, 0, NULL);	// ѭ�����ű������ֳɹ�����0�����򷵻ش������
							if (0 != i)
							{
								mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// ���ű�������ʧ�ܣ�����Ա������ֵ�ռ��	
								_stprintf_s(temp, _T("��������(%s)��Դ����ʧ�ܣ������޷��������С�\n��ȷ��������δ����������ռ�ã�"), bkMusic);
								MessageBox(myAllFlag.hwnd, temp, _T("����������Դ����ʧ��"), MB_OK | MB_ICONHAND);
								exit(0);
							}
							myAllFlag.myBuzzerFlag = 1;	// ��ǵ�ǰ�������ֲ���״̬��0��ͣ��1����
						}
						showflag = 1;
					}
					else if (myUp.isShow > 0 && myAllFlag.myUpFlag > 0 && mou.x > myUp.pX && mou.x < (myUp.pX + myUp.size) && mou.y > myUp.pY && mou.y < (myUp.pY + myUp.size))
					{
						// ��Ӧ ����-���ƣ���Ӧ����������������趨�⣬�����������Ƶ��޶����ܷ�������demoShow()�����м��
						if (myAllFlag.mysmallPhotoNumberInsmall < 1)	// ��ǰ�޷�����
						{
							// ���Ϸ�ҳ
							myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// ����ʾ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
							if (myAllFlag.mysmallPhotoNumberInAll < 0)	// �Ϸ��ܷ���ʾ����ҳ
							{
								myAllFlag.mysmallPhotoNumberInAll = 0;	// ������Ƭ��Դ�еĵ�һ��
							}
							myAllFlag.mysmallPhotoNumberInsmall = mySmallPhoto[0].number - 1;
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 	    
							showflag = 2;
						}
						else
						{
							myAllFlag.mysmallPhotoNumberInsmall -= 1;
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 	
							showflag = 2;
						}
					}
					else if (myDown.isShow > 0 && myAllFlag.myDownFlag > 0 && mou.x > myDown.pX && mou.x < (myDown.pX + myDown.size) && mou.y > myDown.pY && mou.y < (myDown.pY + myDown.size))
					{
						// ��Ӧ ����-���ƣ���Ӧ����������������趨�⣬�����������Ƶ��޶����ܷ�������demoShow()�����м��
						if ((myAllFlag.mysmallPhotoNumberInsmall == mySmallPhoto[0].number - 1) || ((myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 2)))	// ��ǰ��������
						{
							// ���·�ҳ
							myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
							myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 
							showflag = 2;
						}
						else
						{
							myAllFlag.mysmallPhotoNumberInsmall += 1;
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 
							showflag = 2;
						}
					}
					else if (myLeft.isShow > 0 && myAllFlag.myLeftFlag > 0 && mou.x > myLeft.pX && mou.x < (myLeft.pX + myLeft.size) && mou.y > myLeft.pY && mou.y < (myLeft.pY + myLeft.size))
					{
						// ��Ӧ ����-��(��)������Ӧ����������������趨�⣬����������(��)�����޶����ܷ���(��)����demoShow()�����м��
						myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// ����ʾ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
						if (myAllFlag.mysmallPhotoNumberInAll < 0)	// �Ϸ��ܷ���ʾ����ҳ
						{
							myAllFlag.mysmallPhotoNumberInAll = 0;
						}
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 
						showflag = 2;
					}
					else if (myRight.isShow > 0 && myAllFlag.myRightFlag > 0 && mou.x > myRight.pX && mou.x < (myRight.pX + myRight.size) && mou.y > myRight.pY && mou.y < (myRight.pY + myRight.size))
					{
						// ��Ӧ ����-��(��)������Ӧ����������������趨�⣬����������(��)�����޶����ܷ���(��)����demoShow()�����м��
						myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// ����ʾ��һ��С��Ƭ������Ƭ�е�λ�ü�С��Ƭ����
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 
						showflag = 2;
					}
					else if (myPlay.isShow > 0 && mou.x > myPlay.pX && mou.x < (myPlay.pX + myPlay.size) && mou.y > myPlay.pY && mou.y < (myPlay.pY + myPlay.size))
					{
						// ��Ӧ ����-�Զ��������ֶ����ţ��˲��ֽ������ֶ��л����Զ�����
						i = MessageBox(myAllFlag.hwnd, _T("��ǰΪ�ֶ����ţ��Ƿ��л����Զ����ţ�\n���л����Զ����ź���ֻ��Ӧ�����еĹ��ڡ����ȡ��Զ��������"), _T("�ֶ������л����Զ�����"), MB_YESNO | MB_ICONQUESTION);
						if (IDYES == i)
						{
							myAllFlag.myPlayFlag = 0;
							showflag = 1;
						}
					}
					else if (myGoto.isShow > 0 && mou.x > myGoto.pX && mou.x < (myGoto.pX + myGoto.size) && mou.y > myGoto.pY && mou.y < (myGoto.pY + myGoto.size))
					{
						// ��Ӧ ����-��ת
						i = MessageBox(myAllFlag.hwnd, _T("�Ƿ���Ҫ��ת��ָ��λ�õ���Ƭ��"), _T("��ת��ָ��λ��"), MB_YESNO | MB_ICONQUESTION);
						if (IDYES == i)
						{
							wchar_t temp2[300];
							if (photoNumber < 1)
							{
								MessageBox(myAllFlag.hwnd, _T("��ǰ����Ƭ��Դ���޷�������ת!"), _T("��תʧ��"), MB_OK | MB_ICONHAND);
								showflag = 0;
							}
							_stprintf_s(temp2, _T("��������Ҫ��ת������Ƭ���\n��ֵ��ΧΪ��1- %d���磺%d��"), photoNumber, (photoNumber - 1) < 1 ? 1 : photoNumber - 1);	// ��Ŀ�����(?:)�������Ǵ���������Ƭ��ԴphotoNumber=1�����
							i = InputBox(temp, 100, temp2, _T("��ת��ָ��λ��"), NULL, 0, 0, false);
							if (1 == i)	// ȷ���Ƿ�����ֵ��
							{
								// �������г�������,�ȼ��������λ����Ȼ��������ַ���ת���ɶ�Ӧ������ֵ
								i = (int)wcslen(temp);
								int j, k = 0;
								for (j = 0; j < i; j++)	// ��������ַ���ת��������
								{
									k *= 10;
									k += (temp[j] - '0');
								}
								if (k > photoNumber || k < 0)	// ���Ҫ��ת��ͼƬ�Ƿ����
								{
									_stprintf_s(temp, _T("���벻��ȷ����ȷ���������ֵ��ΧΪ��1 - %d"), photoNumber);
									MessageBox(myAllFlag.hwnd, temp, _T("��ת��ָ��λ��ʧ��"), MB_OK | MB_ICONHAND);
									showflag = 0;
								}
								else
								{
									myAllFlag.mysmallPhotoNumberInsmall = 0;	// Ĭ�Ϸ�ҳ�������Ƭ��ʾ��ΪС��Ƭ�еĵ�һ��
									myAllFlag.mysmallPhotoNumberInAll = k - 1;	// ����ʾ����ʾ��һ��С��Ƭ������Ƭ�е�λ������Ϊ��ת��λ��
									myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı�� 
									showflag = 2;
								}
							}
							else
							{
								showflag = 0;
							}
						}
						else
						{
							showflag = 0;
						}
					}
					else
					{
						// ��Ӧ��Ƭ��ʾ�����������õ�С��Ƭ��������ʵ����Ƭ��ʱ���ٵ�Ϊ׼		
						showflag = 0;
						for (i = 0; (i < mySmallPhoto[0].number) && ((i + myAllFlag.mysmallPhotoNumberInAll) < photoNumber); i++)
						{
							if (mou.x > mySmallPhoto[i].pX && mou.x < (mySmallPhoto[i].pX + mySmallPhoto[i].width) && mou.y > mySmallPhoto[i].pY && mou.y < (mySmallPhoto[i].pY + mySmallPhoto[i].height))
							{
								if (i != myAllFlag.mysmallPhotoNumberInsmall)
								{
									// �����ͬһ����Ƭ����Ҫ������ʾ�����򲻸�����ʾ
									myAllFlag.mysmallPhotoNumberInsmall = i;
									myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// ����Ƭ��ʾ��ΪС��Ƭ������Ƭ�еı��+С��Ƭ��С��Ƭ�еı��
									showflag = 2;
									break;	// �ҵ����������Ĳ����������˳��������ң���Ϊ��ѭ���з������������ֻ��1��
								}
							}
						}
					}
				}
			}

			// �������ֶ����Ų��ֵĻ�ͼ
			if (showflag > 1)
			{
				realTimeReadSet();	// ʵʱ��ȡ��Ƭ����Ƭ��Ӧ������Ϣ���Ա���ˢ��ʱ����Ϣ�����µ�
				demoShow();			// ������ͼ��ˢ����������
			}
			else if (showflag > 0)
			{
				demoShow();			// j = 1ʱ��������ͼ��ˢ����������
			}
			else
			{
				;	// j = 0ʱ���޲���������ʱ
			}

			Sleep(30);			// ��ʱ30ms������cpuռ����
		}
	}
	return 0;
}


/*
*������:demoShow()
*��������:��������ʱ��ʾ�Ľ���,���������ֲ��Ų���
*����˵��:��
*������
*/
void demoShow()
{
	IMAGE	systemimg;						// �洢������ͼƬ
	IMAGE	DecoratePicture[myMAX];			// װ����ͼƬ
	IMAGE	imgBigPhoto1, imgBigPhoto2;		// �洢��ʾ�Ĵ���Ƭ��1ԭͼ��С��2���ų��ʺ���ʾ�Ĵ�С
	double	imgBigPhotoD1, imgBigPhotoD2;	// ���ڴ���Ƭ��ʾʱ�ߴ�����ʱ��
	IMAGE	Zooimg0To9[myMAX], Zooimg0To92[myMAX];	// �洢С��Ƭ,ʵʱ��ȡ,1ԭͼ��С��2���ų��ʺ���ʾ�Ĵ�С
	wchar_t	temp[300];
	int		i;

	BeginBatchDraw();	// ��ʼ������ͼ

	// ��������汳��ͼ
	if (_waccess(myHomeScreen.photo, 0) < 0)	// ���������ͼƬ�Ƿ���ڣ����������򲻼������½���
	{
		_stprintf_s(temp, _T("������ͼƬ(%s)��Դȱʧ�������޷��������С�\n��ȷ����ͼƬ������·����������ȷ��"), myHomeScreen.photo);
		MessageBox(myAllFlag.hwnd, temp, _T("������ͼƬ��Դȱʧ"), MB_OK | MB_ICONHAND);
		exit(0);
	}
	switch (myHomeScreen.adjust)	// ����������ͼƬ��С                                                                                                         
	{
	case 1:
		// 1 �������������ͼƬ��СΪ���ڴ�С��ͼƬ��Ҫ����
		loadimage(&systemimg, myHomeScreen.photo, myWindow.width, myWindow.height);
		break;
	case 2:
		// 2 �������������ͼƬ��СΪ�Զ����С��ͼƬ��Ҫ����
		loadimage(&systemimg, myHomeScreen.photo, myHomeScreen.width, myHomeScreen.height);
		break;
	default:
		// 0 �� Ĭ�� ���������ͼƬ��СΪԭͼ��С��ͼƬ��С�����봰�ڲ�ƥ��
		loadimage(&systemimg, myHomeScreen.photo);
		break;
	}
	putimage(myHomeScreen.pX, myHomeScreen.pY, &systemimg);

	// ���С��Ƭ�ܷ���(��)��
	if (myAllFlag.mysmallPhotoNumberInAll > 0)
	{
		myAllFlag.myLeftFlag = 1;	// ����(��)��
	}
	else
	{
		myAllFlag.myLeftFlag = 0;
	}

	// ���С��Ƭ�ܷ���(��)��
	if (myAllFlag.mysmallPhotoNumberInAll < (photoNumber - mySmallPhoto[0].number))
	{
		myAllFlag.myRightFlag = 1;// ����(��)��
	}
	else
	{
		myAllFlag.myRightFlag = 0;
	}

	// ���С��Ƭ�ܷ�����-�����ȼ���ܷ���(��)��ҳ����������ܷ����ƣ���������ǰһ�ε�˳���ܵ���
	if (myAllFlag.mysmallPhotoNumberInsmall < 1)	// ��ǰ�޷�����
	{
		// ����ܷ���(��)��ҳ
		if (myAllFlag.myLeftFlag > 0)	// ����(��)��ҳ
			myAllFlag.myUpFlag = 1;		// ������
		else
			myAllFlag.myUpFlag = 0;		// ��������
	}
	else
	{
		myAllFlag.myUpFlag = 1;			// ������
	}

	// ���С��Ƭ�ܷ�����-�����ȼ���ܷ���(��)��ҳ����������ܷ����ƣ���������ǰһ�ε�˳���ܵ���
	if ((myAllFlag.mysmallPhotoNumberInsmall == mySmallPhoto[0].number - 1) || ((myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 2)))	// ��ǰ��������
	{
		// ����ܷ���(��)��ҳ
		if (myAllFlag.myRightFlag > 0)	// ����(��)��ҳ
			myAllFlag.myDownFlag = 1;	// ������
		else
			myAllFlag.myDownFlag = 0;	// ��������
	}
	else
	{
		myAllFlag.myDownFlag = 1;		// ������
	}

	// �������ͼ�꣺���ڡ����á�ˢ�¡����ȡ��Ϸ����·�
	setbkmode(TRANSPARENT);	// ����ͼ�������������ʱ�ı���ģʽΪTRANSPARENT (1) ʵ����������ޱ���ɫ
	// ��������ַ�ͼ��-���ڣ�����������Ϣ��Ӧ����Ȧi(webdinhs�����0x69)
	if (myAbout.isShow > 0)
	{
		settextcolor(myAbout.color);					// ����������ɫ
		settextstyle(myAbout.size, 0, _T("webdings"));	// ���������С������(_T("webdinhs"))
		outtextxy(myAbout.pX, myAbout.pY, 0x69);		// ���������Ϣ��Ӧ����Ȧi
	}

	// ��������ַ�ͼ��-ˢ�£�������ʾ��覴û��ֶ��޸����ÿ��������ʾ��Ӧ����Ȧ��ͷ(wingdings 3�����0x50)
	if (myRefresh.isShow > 0)
	{
		settextcolor(myRefresh.color);
		settextstyle(myRefresh.size, 0, _T("wingdings 3"));
		outtextxy(myRefresh.pX, myRefresh.pY, 0x50);
	}

	// ��������ַ�ͼ��-���ȣ��������ֿ�ʼ����ͣ��Ӧ��������>>>(webdings�����0x55)������(webdings�����0x56)
	if (myBuzzer.isShow > 0)
	{
		if (myAllFlag.myBuzzerFlag > 0)		// myBuzzerFlag��ǵ�ǰ�������ֲ���״̬��0��ͣ��1����
		{
			settextcolor(myBuzzer.color);
			settextstyle(myBuzzer.size, 0, _T("webdings"));
			outtextxy(myBuzzer.pX, myBuzzer.pY, 0x55);
		}
		else
		{
			settextcolor(myBuzzer.color);
			settextstyle(myBuzzer.size, 0, _T("webdings"));
			outtextxy(myBuzzer.pX, myBuzzer.pY, 0x56);
		}
	}

	// ��������ַ�ͼ��-�ϼ�ͷ����Ƭ������Ӧ�����ϼ�ͷ(webdings�����0x35)
	if (myUp.isShow > 0)
	{
		if (myAllFlag.myUpFlag > 0)	// ��������Ҫ��ʾ
		{
			// myAllFlag.myUpFlag��ǵ�ǰ�ܷ����ƣ�0���ܣ�1��
			settextcolor(myUp.color);
			settextstyle(myUp.size, 0, _T("webdings"));
			outtextxy(myUp.pX, myUp.pY, 0x35);
		}
	}

	// ��������ַ�ͼ��-�¼�ͷ����Ƭ������Ӧ�����¼�ͷ(webdings�����0x36)
	if (myDown.isShow > 0)
	{
		if (myAllFlag.myDownFlag > 0)	// ��������Ҫ��ʾ
		{
			// myAllFlag.myDownFlag��ǵ�ǰ�ܷ����ƣ�0���ܣ�1��
			settextcolor(myDown.color);
			settextstyle(myDown.size, 0, _T("webdings"));
			outtextxy(myDown.pX, myDown.pY, 0x36);
		}
	}

	// ��������ַ�ͼ��-���ͷ����Ƭ��(��)��ҳ��Ӧ�������ͷ(webdings�����0x37)
	if (myLeft.isShow > 0)
	{
		if (myAllFlag.myLeftFlag > 0)	// ����(��)��ҳ��Ҫ��ʾ
		{
			// myAllFlag.myLeftFlag��ǵ�ǰ�ܷ���(��)��ҳ��0���ܣ�1��
			settextcolor(myLeft.color);
			settextstyle(myLeft.size, 0, _T("webdings"));
			outtextxy(myLeft.pX, myLeft.pY, 0x37);
		}
	}

	// ��������ַ�ͼ��-�Ҽ�ͷ����Ƭ��(��)��ҳ��Ӧ�����Ҽ�ͷ(webdings�����0x38)
	if (myRight.isShow > 0)
	{
		if (myAllFlag.myRightFlag > 0)	// ����(��)��ҳ��Ҫ��ʾ
		{
			// myAllFlag.myRightFlag��ǵ�ǰ�ܷ���(��)��ҳ��0���ܣ�1��
			settextcolor(myRight.color);
			settextstyle(myRight.size, 0, _T("webdings"));
			outtextxy(myRight.pX, myRight.pY, 0x38);
		}
	}

	// ��������ַ�ͼ��-�Զ����ţ��л��ֶ���ҳ���Զ���ҳ����ʽ��������ǰ��Ҫ����ȷ����Ϣ
	if (myPlay.isShow > 0)
	{
		if (myAllFlag.myPlayFlag > 0)
		{
			// ��ǵ�ǰ���Զ�ѭ�����Ż����ֶ���0�Զ���1�ֶ�
			settextcolor(myPlay.color);
			settextstyle(myPlay.size, 0, _T("webdings"));
			outtextxy(myPlay.pX, myPlay.pY, 0x3C);
		}
		else
		{
			settextcolor(myPlay.color);
			settextstyle(myPlay.size, 0, _T("webdings"));
			outtextxy(myPlay.pX, myPlay.pY, 0x3B);
		}
	}

	// ��������ַ�ͼ��-��ת����ת���Ѽ�����Ƭ������һ�ţ���ʽ��������ǰ��Ҫ����ȷ����Ϣ
	if (myGoto.isShow > 0)
	{
		settextcolor(myGoto.color);
		settextstyle(myGoto.size, 0, _T("wingdings 3"));
		outtextxy(myGoto.pX, myGoto.pY, 0xCC);
	}

	// ���װ����ͼƬ
	if (myDecoratePicture[0].isValid > 0)	// ����װ����ͼƬ
	{
		for (i = 0; i < myDecoratePicture[0].number; i++)
		{
			if (_waccess(myDecoratePicture[i].res, 0) < 0)	// ���װ����ͼƬ�Ƿ���ڣ����������򲻼������½���
			{
				MessageBox(myAllFlag.hwnd, _T("װ����ͼƬ��Դȱʧ�������޷��������С�\n��ȷ��װ����ͼƬ������·����������ȷ��"), _T("װ����ͼƬȱʧ"), MB_OK | MB_ICONHAND);
				exit(0);
			}
			// ���ر���͸����װ����ͼƬ��������͸��ɫ���
			loadimage(&DecoratePicture[i], myDecoratePicture[i].res, myDecoratePicture[i].width, myDecoratePicture[i].height);
			transparentimage(NULL, myDecoratePicture[i].pX, myDecoratePicture[i].pY, &DecoratePicture[i]);
		}
	}

	// ���װ��������
	if (myDecorateTxt[0].isValid > 0)	// ����װ����ͼƬ
	{
		for (i = 0; i < myDecorateTxt[0].number; i++)
		{
			RECT Album = { myDecorateTxt[i].pX, myDecorateTxt[i].pY, myDecorateTxt[i].pX + myDecorateTxt[i].width, myDecorateTxt[i].pY + myDecorateTxt[i].height };
			if (myDecorateTxt[i].IsBk > 0)	// �Ƿ����װ�������ֱ���
			{
				setbkcolor(myDecorateTxt[i].bkColor);	// ���õ�ǰ������ɫ
				setbkmode(OPAQUE);						// ���ֱ����õ�ǰ������ɫ���
			}
			else
				setbkmode(TRANSPARENT);					// ���ֱ�����͸����
			settextcolor(myDecorateTxt[i].color);		// ����������ɫ
			settextstyle(myDecorateTxt[i].size, 0, myDecorateTxt[i].font);	// ���������С������
			drawtext(myDecorateTxt[i].res, &Album, DT_WORDBREAK);			// ����Ļָ��λ������������ DT_WORDBREAK �Զ�����
		}
	}

	// ���С��Ƭ
	for (i = 0; i < mySmallPhoto[0].number; i++)	// ����С��Ƭ����������ʾ
	{
		if ((i + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 1))
		{
			// �����õ�С��Ƭ��Ӧ������������Ƭ����������ʾ�����С��Ƭ��Ӧ��
			break;
		}
		if (_waccess(myPhoto[i], 0) < 0)	// �����Ƭ�Ƿ���ڣ����������򲻼������½���
		{
			_stprintf_s(temp, _T("��Ƭ(%s)��Դȱʧ�������޷��������С�\n��ȷ����ͼƬ������·����������ȷ��"), myPhoto[i]);
			MessageBox(myAllFlag.hwnd, temp, _T("��Ƭ��Դȱʧ"), MB_OK | MB_ICONHAND);
			exit(0);
		}
		// ������Ƭ��Դ,ԭ������
		loadimage(&Zooimg0To9[i], myPhoto[i], 0, 0, true);
		// �������Ŵ�С�����ͼ���Ŵ���ԭ��һ��
		imgBigPhotoD1 = ((double)mySmallPhoto[i].height) / Zooimg0To9[i].getheight();
		imgBigPhotoD2 = ((double)mySmallPhoto[i].width) / Zooimg0To9[i].getwidth();
		if (imgBigPhotoD1 > imgBigPhotoD2)
		{
			imgBigPhotoD1 = imgBigPhotoD2;	// ѡ���ʺ���ʾ�ı���
		}
		// ������Ƭ��Դ,���ż���
		loadimage(&Zooimg0To92[i], myPhoto[i], (int)(Zooimg0To9[i].getwidth()*imgBigPhotoD1), (int)(Zooimg0To9[i].getheight()*imgBigPhotoD1), true);
		// С��Ƭ�����ԭ������������
		putimage(mySmallPhoto[i].pX + (mySmallPhoto[i].width - Zooimg0To92[i].getwidth()) / 2, mySmallPhoto[i].pY + (mySmallPhoto[i].height - Zooimg0To92[i].getheight()) / 2, &Zooimg0To92[i]);

		setlinecolor(mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].color);	// ���õ�ǰѡ�е�С��Ƭ�߿���ɫ
		setlinestyle(PS_SOLID, 3);	// ���õ�ǰѡ�е�С��Ƭ�߿�Ϊʵ�ߣ���3
		// �����ǰѡ�е�С��Ƭ�߿�
		rectangle(mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pX - 3, mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pY - 3, (mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pX + mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].width + 3), (mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pY + mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].height + 3));
	}

	// �������Ƭ,С��Ƭ�Ѿ������Դ�ˣ��˴������ټ��
	// ���ش���ƬͼƬ��Ȼ�����ų��ʺ���ʾ�Ĵ�С������ʾ
	loadimage(&imgBigPhoto1, myPhoto[myAllFlag.mysmallPhotoNumberInsmall]);
	imgBigPhotoD1 = ((double)myBigPhoto.height) / imgBigPhoto1.getheight();
	imgBigPhotoD2 = ((double)myBigPhoto.width) / imgBigPhoto1.getwidth();
	if (imgBigPhotoD1 > imgBigPhotoD2)
	{
		imgBigPhotoD1 = imgBigPhotoD2;	// ѡ���ʺ���ʾ�ı���
	}
	loadimage(&imgBigPhoto2, myPhoto[myAllFlag.mysmallPhotoNumberInsmall], (int)(imgBigPhoto1.getwidth()*imgBigPhotoD1), (int)(imgBigPhoto1.getheight()*imgBigPhotoD1));
	// ����Ƭ�����ԭ������������
	putimage(myBigPhoto.pX + (myBigPhoto.width - imgBigPhoto2.getwidth()) / 2, myBigPhoto.pY + (myBigPhoto.height  - imgBigPhoto2.getheight()) / 2, &imgBigPhoto2);

	// �������Ƭ��������Ƭ�е����
	if (myBigPhoto.snIsBk > 0)				// �Ƿ����������ֱ���
	{
		setbkcolor(myBigPhoto.snBkColor);	// ���õ�ǰ������ɫ
		setbkmode(OPAQUE);					// ���ֱ����õ�ǰ������ɫ���
	}
	else
		setbkmode(TRANSPARENT);				// ���ֱ�����͸����
	settextcolor(myBigPhoto.snColor);		// ����������ɫ
	settextstyle(myBigPhoto.snSize, 0, myBigPhoto.snFont);	// ���������С������
	_stprintf_s(temp, _T("%d / %d"), (photoNumber < 1) ? 0 : myAllFlag.myBigPhotoNumberInAll + 1, photoNumber);	// ��Ŀ�����(?:)�������Ǵ���δ������Ƭ��Դ(��photoNumber=0)�����
	outtextxy(myBigPhoto.snPX, myBigPhoto.snPY, temp);

	// �������Ƭ��Ӧ������
	RECT Album2 = { myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pX, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pY, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pX + myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].width, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pY + myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].height };
	if (myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].IsBk > 0)	// �Ƿ�������ֱ���
	{
		setbkcolor(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].bkColor);	// ���õ�ǰ������ɫ
		setbkmode(OPAQUE);						// ���ֱ����õ�ǰ������ɫ���
	}
	else
		setbkmode(TRANSPARENT);					// ���ֱ�����͸����
	settextcolor(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].color);		// ����������ɫ
	settextstyle(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].size, 0, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].font);	// ���������С������
	drawtext(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].res, &Album2, DT_WORDBREAK);	// ����Ļָ��λ������������ DT_WORDBREAK �Զ�����

	EndBatchDraw();	// �����������ƣ���ִ��δ��ɵĻ�������
}


/* ��͸����ͼ����
* ������
*            dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
*            x, y:  Ŀ����ͼλ��
*            srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
*/
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/*
*������:readSet()
*��������:�������ļ�Set.ini����ȡ�������ݸ�ȫ�ֱ�����ֵ
*����˵��:��
*����0������-1�쳣����δ���÷���ֵ
*/
int readSet()
{
	int		i;
	wchar_t	temp[300];

	// ����ini����[Window]�����ݣ���������
	myWindow.width = GetPrivateProfileInt(_T("Window"), _T("Width"), 932, _T(".\\Set.ini"));
	myWindow.height = GetPrivateProfileInt(_T("Window"), _T("Height"), 540, _T(".\\Set.ini"));
	GetPrivateProfileString(_T("Window"), _T("Name"), _T("��̫�� and ��̫�� LOVE memories"), myWindow.name, sizeof(myWindow.name), _T(".\\Set.ini"));

	// ����ini����[BkMusic]�����ݣ���������·��
	GetPrivateProfileString(_T("BkMusic"), _T("Music"), _T("res\\bk.mp3"), bkMusic, sizeof(bkMusic), _T(".\\Set.ini"));

	// ����ini����[HomeScreen]�����ݣ�������ͼƬ
	GetPrivateProfileString(_T("HomeScreen"), _T("Photo"), _T("res\\bk.jpg"), myHomeScreen.photo, sizeof(myHomeScreen.photo), _T(".\\Set.ini"));
	myHomeScreen.pX = GetPrivateProfileInt(_T("HomeScreen"), _T("PX"), 0, _T(".\\Set.ini"));
	myHomeScreen.pY = GetPrivateProfileInt(_T("HomeScreen"), _T("PY"), 0, _T(".\\Set.ini"));
	myHomeScreen.adjust = GetPrivateProfileInt(_T("HomeScreen"), _T("Adjust"), 1, _T(".\\Set.ini"));
	myHomeScreen.width = GetPrivateProfileInt(_T("HomeScreen"), _T("Width"), 600, _T(".\\Set.ini"));
	myHomeScreen.height = GetPrivateProfileInt(_T("HomeScreen"), _T("Height"), 800, _T(".\\Set.ini"));

	// ����ini����[ToolAbout]�����ݣ�����-����
	myAbout.isShow = GetPrivateProfileInt(_T("ToolAbout"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myAbout.size = GetPrivateProfileInt(_T("ToolAbout"), _T("Size"), 40, _T(".\\Set.ini"));
	myAbout.color = GetPrivateProfileInt(_T("ToolAbout"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myAbout.color = ((myAbout.color % 0x100) * 0x10000) + (((myAbout.color % 0x10000) / 0x100) * 0x100) + (myAbout.color / 0x10000);
	myAbout.pX = GetPrivateProfileInt(_T("ToolAbout"), _T("PX"), 0, _T(".\\Set.ini"));
	myAbout.pY = GetPrivateProfileInt(_T("ToolAbout"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolRefresh]�����ݣ�����-ˢ��
	myRefresh.isShow = GetPrivateProfileInt(_T("ToolRefresh"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myRefresh.size = GetPrivateProfileInt(_T("ToolRefresh"), _T("Size"), 40, _T(".\\Set.ini"));
	myRefresh.color = GetPrivateProfileInt(_T("ToolRefresh"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myRefresh.color = ((myRefresh.color % 0x100) * 0x10000) + (((myRefresh.color % 0x10000) / 0x100) * 0x100) + (myRefresh.color / 0x10000);
	myRefresh.pX = GetPrivateProfileInt(_T("ToolRefresh"), _T("PX"), 0, _T(".\\Set.ini"));
	myRefresh.pY = GetPrivateProfileInt(_T("ToolRefresh"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolBuzzer]�����ݣ�����-����
	myBuzzer.isShow = GetPrivateProfileInt(_T("ToolBuzzer"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myBuzzer.size = GetPrivateProfileInt(_T("ToolBuzzer"), _T("Size"), 40, _T(".\\Set.ini"));
	myBuzzer.color = GetPrivateProfileInt(_T("ToolBuzzer"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myBuzzer.color = ((myBuzzer.color % 0x100) * 0x10000) + (((myBuzzer.color % 0x10000) / 0x100) * 0x100) + (myBuzzer.color / 0x10000);
	myBuzzer.pX = GetPrivateProfileInt(_T("ToolBuzzer"), _T("PX"), 0, _T(".\\Set.ini"));
	myBuzzer.pY = GetPrivateProfileInt(_T("ToolBuzzer"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolUp]�����ݣ�����-����
	myUp.isShow = GetPrivateProfileInt(_T("ToolUp"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myUp.size = GetPrivateProfileInt(_T("ToolUp"), _T("Size"), 40, _T(".\\Set.ini"));
	myUp.color = GetPrivateProfileInt(_T("ToolUp"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myUp.color = ((myUp.color % 0x100) * 0x10000) + (((myUp.color % 0x10000) / 0x100) * 0x100) + (myUp.color / 0x10000);
	myUp.pX = GetPrivateProfileInt(_T("ToolUp"), _T("PX"), 0, _T(".\\Set.ini"));
	myUp.pY = GetPrivateProfileInt(_T("ToolUp"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolDown]�����ݣ�����-����
	myDown.isShow = GetPrivateProfileInt(_T("ToolDown"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myDown.size = GetPrivateProfileInt(_T("ToolDown"), _T("Size"), 40, _T(".\\Set.ini"));
	myDown.color = GetPrivateProfileInt(_T("ToolDown"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myDown.color = ((myDown.color % 0x100) * 0x10000) + (((myDown.color % 0x10000) / 0x100) * 0x100) + (myDown.color / 0x10000);
	myDown.pX = GetPrivateProfileInt(_T("ToolDown"), _T("PX"), 0, _T(".\\Set.ini"));
	myDown.pY = GetPrivateProfileInt(_T("ToolDown"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolLeft]�����ݣ�����-��(��)��ҳ
	myLeft.isShow = GetPrivateProfileInt(_T("ToolLeft"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myLeft.size = GetPrivateProfileInt(_T("ToolLeft"), _T("Size"), 40, _T(".\\Set.ini"));
	myLeft.color = GetPrivateProfileInt(_T("ToolLeft"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myLeft.color = ((myLeft.color % 0x100) * 0x10000) + (((myLeft.color % 0x10000) / 0x100) * 0x100) + (myLeft.color / 0x10000);
	myLeft.pX = GetPrivateProfileInt(_T("ToolLeft"), _T("PX"), 0, _T(".\\Set.ini"));
	myLeft.pY = GetPrivateProfileInt(_T("ToolLeft"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolRight]�����ݣ�����-��(��)��ҳ
	myRight.isShow = GetPrivateProfileInt(_T("ToolRight"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myRight.size = GetPrivateProfileInt(_T("ToolRight"), _T("Size"), 40, _T(".\\Set.ini"));
	myRight.color = GetPrivateProfileInt(_T("ToolRight"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myRight.color = ((myRight.color % 0x100) * 0x10000) + (((myRight.color % 0x10000) / 0x100) * 0x100) + (myRight.color / 0x10000);
	myRight.pX = GetPrivateProfileInt(_T("ToolRight"), _T("PX"), 0, _T(".\\Set.ini"));
	myRight.pY = GetPrivateProfileInt(_T("ToolRight"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolPlay]�����ݣ�����-�Զ�����
	myPlay.isShow = GetPrivateProfileInt(_T("ToolPlay"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myPlay.size = GetPrivateProfileInt(_T("ToolPlay"), _T("Size"), 40, _T(".\\Set.ini"));
	myPlay.color = GetPrivateProfileInt(_T("ToolPlay"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myPlay.color = ((myPlay.color % 0x100) * 0x10000) + (((myPlay.color % 0x10000) / 0x100) * 0x100) + (myPlay.color / 0x10000);
	myPlay.pX = GetPrivateProfileInt(_T("ToolPlay"), _T("PX"), 0, _T(".\\Set.ini"));
	myPlay.pY = GetPrivateProfileInt(_T("ToolPlay"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[ToolGoto]�����ݣ�����-��ת
	myGoto.isShow = GetPrivateProfileInt(_T("ToolGoto"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myGoto.size = GetPrivateProfileInt(_T("ToolGoto"), _T("Size"), 40, _T(".\\Set.ini"));
	myGoto.color = GetPrivateProfileInt(_T("ToolGoto"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myGoto.color = ((myGoto.color % 0x100) * 0x10000) + (((myGoto.color % 0x10000) / 0x100) * 0x100) + (myGoto.color / 0x10000);
	myGoto.pX = GetPrivateProfileInt(_T("ToolGoto"), _T("PX"), 0, _T(".\\Set.ini"));
	myGoto.pY = GetPrivateProfileInt(_T("ToolGoto"), _T("PY"), 0, _T(".\\Set.ini"));

	// ����ini����[DecoratePictureTitle]��[DecoratePicture*]�����ݣ�װ����ͼƬ����
	myDecoratePicture[0].isValid = GetPrivateProfileInt(_T("DecoratePictureTitle"), _T("IsValid"), 0, _T(".\\Set.ini"));
	if (myDecoratePicture[0].isValid > 0)	// ����װ����ͼƬ����ʼ��ȡ[DecoratePicture]��ʣ�µ�����
	{
		myDecoratePicture[0].number = GetPrivateProfileInt(_T("DecoratePictureTitle"), _T("Number"), 0, _T(".\\Set.ini"));
		for (i = 0; i < myDecoratePicture[0].number; i++)
		{
			// �ṹ������myDecoratePicture�е�isValid��number������0λ��ͬ
			myDecoratePicture[i].isValid = myDecoratePicture[0].isValid;
			myDecoratePicture[i].number = myDecoratePicture[0].number;

			_stprintf_s(temp, _T("DecoratePicture%d"), i);	// [DecoratePicture*]������

			GetPrivateProfileString(temp, _T("Res"), _T("res\\test.jpg"), myDecoratePicture[i].res, sizeof(myDecoratePicture[i].res), _T(".\\Set.ini"));
			myDecoratePicture[i].width = GetPrivateProfileInt(temp, _T("Width"), 0, _T(".\\Set.ini"));
			myDecoratePicture[i].height = GetPrivateProfileInt(temp, _T("Height"), 0, _T(".\\Set.ini"));
			myDecoratePicture[i].pX = GetPrivateProfileInt(temp, _T("PX"), 0, _T(".\\Set.ini"));
			myDecoratePicture[i].pY = GetPrivateProfileInt(temp, _T("PY"), 0, _T(".\\Set.ini"));
		}
	}

	// ����ini����[DecorateTxtTitle]��[DecorateTxt*]�����ݣ�װ������������
	myDecorateTxt[0].isValid = GetPrivateProfileInt(_T("DecorateTxtTitle"), _T("IsValid"), 0, _T(".\\Set.ini"));
	if (myDecorateTxt[0].isValid > 0)	// ����װ�������֣���ʼ��ȡ[DecorateTxt]��ʣ�µ�����
	{
		myDecorateTxt[0].number = GetPrivateProfileInt(_T("DecorateTxtTitle"), _T("Number"), 0, _T(".\\Set.ini"));
		for (i = 0; i < myDecorateTxt[0].number; i++)
		{
			// �ṹ������myDecorateTxt�е�isValid��number������0λ��ͬ
			myDecorateTxt[i].isValid = myDecorateTxt[0].isValid;
			myDecorateTxt[i].number = myDecorateTxt[0].number;

			_stprintf_s(temp, _T("DecorateTxt%d"), i);	// [DecorateTxt*]������

			GetPrivateProfileString(temp, _T("Res"), _T("test"), myDecorateTxt[i].res, sizeof(myDecorateTxt[i].res), _T(".\\Set.ini"));
			myDecorateTxt[i].width = GetPrivateProfileInt(temp, _T("Width"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].height = GetPrivateProfileInt(temp, _T("Height"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].pX = GetPrivateProfileInt(temp, _T("PX"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].pY = GetPrivateProfileInt(temp, _T("PY"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].size = GetPrivateProfileInt(temp, _T("Size"), 20, _T(".\\Set.ini"));
			GetPrivateProfileString(temp, _T("Font"), _T("΢���ź�"), myDecorateTxt[i].font, sizeof(myDecorateTxt[i].font), _T(".\\Set.ini"));
			myDecorateTxt[i].color = GetPrivateProfileInt(temp, _T("Color"), 0xFF0000, _T(".\\Set.ini"));
			// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
			myDecorateTxt[i].color = ((myDecorateTxt[i].color % 0x100) * 0x10000) + (((myDecorateTxt[i].color % 0x10000) / 0x100) * 0x100) + (myDecorateTxt[i].color / 0x10000);
			myDecorateTxt[i].IsBk = GetPrivateProfileInt(temp, _T("IsBk"), 0, _T(".\\Set.ini"));
			if (myDecorateTxt[i].IsBk > 0)	// �������ֱ���ɫ
			{
				myDecorateTxt[i].bkColor = GetPrivateProfileInt(temp, _T("BkColor"), 0xFF0000, _T(".\\Set.ini"));
				// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
				myDecorateTxt[i].bkColor = ((myDecorateTxt[i].bkColor % 0x100) * 0x10000) + (((myDecorateTxt[i].bkColor % 0x10000) / 0x100) * 0x100) + (myDecorateTxt[i].bkColor / 0x10000);
			}
		}
	}

	// ����ini����[SmallPhoto]�����ݣ�С��Ƭ��������
	mySmallPhoto[0].number = GetPrivateProfileInt(_T("SmallPhotoTitle"), _T("Number"), 0, _T(".\\Set.ini"));
	for (i = 0; i < mySmallPhoto[0].number; i++)
	{
		// �ṹ������mySmallPhoto�е�number��0λ��ͬ
		mySmallPhoto[i].number = mySmallPhoto[0].number;

		_stprintf_s(temp, _T("SmallPhoto%d"), i);

		mySmallPhoto[i].width = GetPrivateProfileInt(temp, _T("Width"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].height = GetPrivateProfileInt(temp, _T("Height"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].pX = GetPrivateProfileInt(temp, _T("PX"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].pY = GetPrivateProfileInt(temp, _T("PY"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].color = GetPrivateProfileInt(temp, _T("Color"), 0xFF0000, _T(".\\Set.ini"));
		// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
		mySmallPhoto[i].color = ((mySmallPhoto[i].color % 0x100) * 0x10000) + (((mySmallPhoto[i].color % 0x10000) / 0x100) * 0x100) + (mySmallPhoto[i].color / 0x10000);
	}

	// ����ini����[BigPhoto]�����ݣ�����Ƭ��������
	myBigPhoto.width = GetPrivateProfileInt(_T("BigPhoto"), _T("Width"), 50, _T(".\\Set.ini"));
	myBigPhoto.height = GetPrivateProfileInt(_T("BigPhoto"), _T("Height"), 50, _T(".\\Set.ini"));
	myBigPhoto.pX = GetPrivateProfileInt(_T("BigPhoto"), _T("PX"), 50, _T(".\\Set.ini"));
	myBigPhoto.pY = GetPrivateProfileInt(_T("BigPhoto"), _T("PY"), 50, _T(".\\Set.ini"));
	myBigPhoto.snPX = GetPrivateProfileInt(_T("BigPhoto"), _T("SNPX"), 0, _T(".\\Set.ini"));
	myBigPhoto.snPY = GetPrivateProfileInt(_T("BigPhoto"), _T("SNPY"), 0, _T(".\\Set.ini"));
	myBigPhoto.snSize = GetPrivateProfileInt(_T("BigPhoto"), _T("SNSize"), 20, _T(".\\Set.ini"));
	GetPrivateProfileString(_T("BigPhoto"), _T("SNFont"), _T("΢���ź�"), myBigPhoto.snFont, sizeof(myBigPhoto.snFont), _T(".\\Set.ini"));
	myBigPhoto.snColor = GetPrivateProfileInt(_T("BigPhoto"), _T("SNColor"), 0xFF0000, _T(".\\Set.ini"));
	// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
	myBigPhoto.snColor = ((myBigPhoto.snColor % 0x100) * 0x10000) + (((myBigPhoto.snColor % 0x10000) / 0x100) * 0x100) + (myBigPhoto.snColor / 0x10000);
	myBigPhoto.snIsBk = GetPrivateProfileInt(_T("BigPhoto"), _T("SNIsBk"), 0, _T(".\\Set.ini"));
	if (myBigPhoto.snIsBk > 0)	// �������ֱ���ɫ
	{
		myBigPhoto.snBkColor = GetPrivateProfileInt(_T("BigPhoto"), _T("SNBkColor"), 0xFF0000, _T(".\\Set.ini"));
		// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
		myBigPhoto.snBkColor = ((myBigPhoto.snBkColor % 0x100) * 0x10000) + (((myBigPhoto.snBkColor % 0x10000) / 0x100) * 0x100) + (myBigPhoto.snBkColor / 0x10000);
	}

	// ����ini����[photo]�����ݣ���Ƭ��Դ·��
	photoNumber = GetPrivateProfileInt(_T("photo"), _T("Number"), 0, _T(".\\Set.ini"));
	if (photoNumber < 0)	// ����������Ƭ��Դ��ĿΪ����ʱ������Ϊ0���Ա������ȷ����
		photoNumber = 0;

	// ��Ƭ��Դ�����Ӻ���realTimeReadSet()ʵʱ��ȡ
	// ��Ƭӡ�ǵ����Ӻ���realTimeReadSet()ʵʱ��ȡ
	return 0;
}

/*
*������:realTimeReadSet()
*��������:ʵʱ��ȡ��Ƭ����Ƭӡ����������
*����˵��:��
*�޷���ֵ
*/
void realTimeReadSet()
{
	int		i;
	wchar_t	temp[300];

	// photoNumber = GetPrivateProfileInt(_T("photo"), _T("Number"), 0, _T(".\\Set.ini"));
	// ʵʱ��ȡ��Ƭ��Դ
	for (i = 0; (i + myAllFlag.mysmallPhotoNumberInAll < photoNumber) && (i < mySmallPhoto[0].number); i++)
	{
		_stprintf_s(temp, _T("Photo%d"), i + myAllFlag.mysmallPhotoNumberInAll);
		GetPrivateProfileString(_T("photo"), temp, _T("res\\test.jpg"), myPhoto[i], sizeof(myPhoto[i]), _T(".\\Set.ini"));
	}
	// ʵʱ��ȡ��Ƭӡ��
	for (i = 0; (i + myAllFlag.mysmallPhotoNumberInAll < photoNumber) && (i < mySmallPhoto[0].number); i++)
	{
		_stprintf_s(temp, _T("photoTxt%d"), i + myAllFlag.mysmallPhotoNumberInAll);	// [photoTxt*]��

		GetPrivateProfileString(temp, _T("Res"), _T("����"), myPhotoTxt[i].res, sizeof(myPhotoTxt[i].res), _T(".\\Set.ini"));
		myPhotoTxt[i].width = GetPrivateProfileInt(temp, _T("Width"), 50, _T(".\\Set.ini"));
		myPhotoTxt[i].height = GetPrivateProfileInt(temp, _T("Height"), 50, _T(".\\Set.ini"));
		myPhotoTxt[i].pX = GetPrivateProfileInt(temp, _T("PX"), 50, _T(".\\Set.ini"));
		myPhotoTxt[i].pY = GetPrivateProfileInt(temp, _T("PY"), 50, _T(".\\Set.ini"));

		myPhotoTxt[i].size = GetPrivateProfileInt(temp, _T("Size"), 20, _T(".\\Set.ini"));
		GetPrivateProfileString(temp, _T("Font"), _T("΢���ź�"), myPhotoTxt[i].font, sizeof(myPhotoTxt[i].font), _T(".\\Set.ini"));
		myPhotoTxt[i].color = GetPrivateProfileInt(temp, _T("Color"), 0xFF0000, _T(".\\Set.ini"));
		// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
		myPhotoTxt[i].color = ((myPhotoTxt[i].color % 0x100) * 0x10000) + (((myPhotoTxt[i].color % 0x10000) / 0x100) * 0x100) + (myPhotoTxt[i].color / 0x10000);
		myPhotoTxt[i].IsBk = GetPrivateProfileInt(temp, _T("IsBk"), 0, _T(".\\Set.ini"));
		if (myPhotoTxt[i].IsBk > 0)	// �������ֱ���ɫ
		{
			myPhotoTxt[i].bkColor = GetPrivateProfileInt(temp, _T("BkColor"), 0xFF0000, _T(".\\Set.ini"));
			// ����ɫ����˳��(RGB)ת���ɺ���ʹ����Ҫ��˳��(BGR)
			myPhotoTxt[i].bkColor = ((myPhotoTxt[i].bkColor % 0x100) * 0x10000) + (((myPhotoTxt[i].bkColor % 0x10000) / 0x100) * 0x100) + (myPhotoTxt[i].bkColor / 0x10000);
		}
	}
}