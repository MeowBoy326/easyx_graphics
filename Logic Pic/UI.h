#pragma once
#include<graphics.h>
#include<string>
#include<map>
#include"GameData.h"
//UI����

//�궨��һЩ��ɫ������ʹ��
#define IVORY			0xFAFFFF	//�����ף�ƫ�ף�			��Ϸ����
#define GRAY			0xCCCCCC	//��ɫ						�����ɫ���ı�
#define LIGHTBLACK		0x323232	//ǳ��ɫ���Ⱥ�ɫ��ǳ��		���ʱ�������Ӱ
#define _DARKGRAY		0x808080	//���ɫ					��ֹʱ������Ӱ
#define _LIGHTGRAY		0xE0E0E0	//ǳ��ɫ��ƫ�ף�			��ֹʱ�����ɫ
#define LIGHTDARKGREEN	0xDED09C	//ǳ����ɫ					��ʾ������̬ͨ�°�ť��ɫ
#define DARKGREEN		0xBEAE73	//����ɫ					��ʾ������̬ͨ�°�ť��Ӱ�����̬�°�ť��ɫ
#define DARKDARKGREEN	0x857025	//������ɫ					���̬�°�ť��Ӱ



//�����״̬
enum class SquareState
{
	ordinary = 0,		//��ͨ״̬
	beenClicked = 1,	//�����״̬
	prohibitory = 2		//��ֹ״̬
};


//����
class Square
{
public:
	Square()
	{

	}

	~Square()
	{

	}

public:
	int x = 0, y = 0;							//λ��
	int size = 0;								//��С
	SquareState state = SquareState::ordinary;	//״̬

public:
	void Reconstruct(int x, int y, int size);	//�����蹹��
	bool SetState(UINT message);				//���÷���״̬
	void SetState(int state);					//���÷���״̬
	SquareState GetState();						//��ȡ����״̬
};


//�ؼ�����
enum class ControlID
{
	base,			//����
	textBlock,		//�ı�����
	imageButton,	//ͼƬ��ť
	rectButton,		//���ΰ�ť
	checkBox,		//��ѡ��
	slideBar,		//������
	squaresArea,	//��������		
	popWindow		//����
};


/******һЩ�򵥵Ŀؼ�******/

//�ؼ�����
class BaseUI
{
public:
	BaseUI();
	BaseUI(const wchar_t* name, int x, int y, int width, int height, int putPriority, bool addInControlTree);

	virtual ~BaseUI()
	{

	}

protected:
	ControlID id = ControlID::base;		//�ؼ�����������
	bool isVisible = true;				//�ÿؼ��Ƿ�ɼ�
	int putPriority = 0;				//�������ȼ�
	bool beenPressed = false;			//�ÿؼ��Ƿ��Ѿ������£����ڵ���¼����ж�

public:
	std::wstring name = _T("");			//�ؼ���������Ϊ�ؼ���Ψһ��־
	int x = 0, y = 0;					//�ؼ�λ��
	int width = 0, height = 0;			//�ؼ���С��������Բ�οؼ���
	MOUSEMSG mouseMsg{};				//�����Ϣ

	void (*mouseInThisEvent) (BaseUI*) = nullptr;	//����ڿؼ����¼�
	void (*leftButtonDownEvent) (BaseUI*) = nullptr;//�����������¼�
	void (*leftButtonUpEvent) (BaseUI*) = nullptr;	//������̧���¼�
	void (*clickEvent) (BaseUI*) = nullptr;			//����¼�

public:
	ControlID GetControlID();									//��ȡ�ؼ�������
	virtual void SetPutPriority(int putPriority);				//���ÿؼ��Ļ������ȼ�
	virtual int GetPutPriority();								//��ȡ�ؼ��Ļ������ȼ�
	virtual void SetVisible(bool isVisible);					//���ÿؼ��Ŀɼ�����
	virtual bool GetVisible();									//��ȡ�ؼ��Ŀɼ�����
	virtual void Reset(int x, int y, int width, int height);	//�������ÿؼ��Ļ�������
	virtual bool MouseInThis();									//����ڸÿؼ���
	virtual bool LeftButtonDown();								//����������
	virtual bool LeftButtonUp();								//������̧��
	virtual bool Click();										//���
	virtual void Event();										//�¼�
	virtual void Put() = 0;										//����
};


//�ı���ʾ��
class TextBlock : public BaseUI
{
public:
	TextBlock() : BaseUI()
	{
		id = ControlID::textBlock;
		gettextstyle(&textFont);
	}

	TextBlock(const wchar_t* name, int x, int y, int width, int height,
		int putPriority = 0, bool addInControlTree = true)
		: BaseUI(name, x, y, width, height, putPriority, addInControlTree)
	{
		id = ControlID::textBlock;
		gettextstyle(&textFont);
	}

	virtual ~TextBlock()
	{

	}

public:
	std::wstring text = _T("");		//�ı�
	LOGFONT textFont;				//����
	COLORREF textColor = BLACK;		//������ɫ
	UINT format = NULL;				//�ı������ʽ

public:
	virtual void Put();				//����
};


//ͼƬ��ť
class ImageButton : public BaseUI
{
public:
	ImageButton() : BaseUI()
	{
		id = ControlID::imageButton;
	}

	ImageButton(const wchar_t* name, int x, int y, int width, int height,
		int putPriority = 0, bool addInControlTree = true)
		: BaseUI(name, x, y, width, height, putPriority, addInControlTree)
	{
		id = ControlID::imageButton;
		currentImage.Resize(width, height);
		ordinaryImage.Resize(width, height);
		beenClickedImage.Resize(width, height);
	}

	virtual ~ImageButton()
	{

	}

public:
	IMAGE currentImage{};		//��ǰ��Ҫ���Ƶ�ͼƬ
	IMAGE ordinaryImage{};		//��ͨ״̬�°�ťͼƬ
	IMAGE beenClickedImage{};	//��ѹ״̬�°�ťͼƬ

public:
	virtual bool Click();		//���
	virtual void Event();		//�¼�
	virtual void Put();			//����
};


//���ΰ�ť
class RectButton : public TextBlock
{
public:
	RectButton() : TextBlock()
	{
		id = ControlID::rectButton;
		format = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	}

	RectButton(const wchar_t* name, int x, int y, int width, int height, int putPriority = 0, bool addInControlTree = true)
		: TextBlock(name, x, y, width, height, putPriority, addInControlTree)
	{
		id = ControlID::rectButton;
		format = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	}

	RectButton(const wchar_t* name, const RectButton& rectButton) : RectButton(rectButton)
	{
		this->name = name;
	}

	virtual ~RectButton()
	{

	}

public:
	COLORREF ordinaryColor = LIGHTGRAY;		//��ͨ״̬��ɫ
	COLORREF beenClickedColor = GRAY;		//�����ʱ��ɫ
	COLORREF borderColor = BLACK;			//�߿���ɫ

public:
	virtual bool Click();					//���
	virtual void Event();					//�¼�
	virtual void Put();						//����
};


//��ѡ��
class CheckBox : public BaseUI
{
public:
	CheckBox() : BaseUI()
	{
		id = ControlID::checkBox;
	}

	CheckBox(const wchar_t* name, int x, int y, int width, int height, int putPriority, bool addInControlTree = true)
		: BaseUI(name, x, y, width, height, putPriority, addInControlTree)
	{
		id = ControlID::checkBox;
	}

	virtual ~CheckBox()
	{

	}

public:
	bool beenChoosen = false;			//�Ƿ�ѡ��
	COLORREF borderColor = BLACK;		//�߿���ɫ
	COLORREF choosenColor = BLACK;		//��ѡ��ʱ�м䷽�����ɫ
	COLORREF fillColor = WHITE;			//���հײ��ֵ���ɫ

public:
	virtual void Event();				//����¼�
	virtual void Put();					//���Ƹ�ѡ��
};


//������(����ؼ�)
//������ SlideBar �ؼ�������ؼ�
class Slider : public BaseUI
{
	Slider()
	{

	}
public:
	virtual ~Slider()
	{

	}
private:
	bool isDrag = false;

public:
	COLORREF color = LIGHTGRAY;		//��������ɫ

public:
	void DragMove();				//�϶���������x����
	virtual void Put();				//����
	
public:
	friend class SlideBar;
};


//������
class SlideBar : public BaseUI
{
public:
	SlideBar() : BaseUI()
	{
		id = ControlID::slideBar;
	}

	SlideBar(const wchar_t* name, int x, int y, int width, int height, int putPriority = 0, bool addInControlTree = true)
		: BaseUI(name, x, y, width, height, putPriority, addInControlTree)
	{
		id = ControlID::slideBar;
		slider.x = x;
		slider.y = y - height;
		slider.width = height;
		slider.height = 3 * height;
	}

	virtual ~SlideBar()
	{

	}

private:
	int value = 0;							//����������ʾ��ֵ

public:
	Slider slider;							//����
	COLORREF slidedColor = 0xffcc66;		//���黮���ط�����ɫ
	COLORREF borderColor = BLACK;			//�������߿���ɫ
	void (*slideEvent)(BaseUI*) = nullptr;	//�����¼�

private:
	virtual bool MouseInThis();				//����Ƿ��ڸÿؼ���
	virtual bool LeftButtonDown();			//�������Ƿ���
	void Slide();							//��������

public:
	void SetValue(int value);				//���û�������ֵ
	int GetValue();							//��ȡ��������ֵ
	virtual void Event();					//�¼�
	virtual void Put();						//����
};


//������������ؼ���
//��Ϊ����Ϸ�����Ķ��ؿؼ�
class SquaresArea : public BaseUI
{
public:
	SquaresArea() : BaseUI()
	{
		id = ControlID::squaresArea;
	}

	SquaresArea(const wchar_t* name) : BaseUI(name, 0, 0, 0, 0, 0, true)
	{
		id = ControlID::squaresArea;
	}

	virtual ~SquaresArea()
	{

	}

private:
	int lineDivideSize = 3;						//�зָ��߼��
	int rowDivideSize = 3;						//�зָ��߼��

public:
	int squareSize = 0;							//����ߴ�
	COLORREF backgroundColor = WHITE;			//��ɫ
	IMAGE ordinaryImage{};						//��ͨ״̬�µķ���ͼƬ
	IMAGE beenClickedImage{};					//���״̬�µķ���ͼƬ
	IMAGE prohibitoryImage{};					//��ֹ״̬�µķ���ͼƬ
	void (*hitEvent)(void) = nullptr;			//����¼�
	void (*soundEvent)(int) = nullptr;			//��Ч�¼�
	vector<vector<Square>> squares;				//����
	int arePlay = 7;							//������Щ��Ч

private:
	bool RightButtonDown();						//����Ҽ��Ƿ���
	void InitDivideLine();						//��ʼ���ָ��߼��

public:
	void InitSquares(int lineNum, int rowNum);	//��ʼ������
	virtual void Event();						//�¼�
	virtual void Put();							//���Ʒ�������
};


//����������ؼ���
//ӵ���ӿؼ���ӵ�ж����¼�
class PopWindow : public BaseUI
{
public:
	PopWindow() : BaseUI()
	{
		id = ControlID::popWindow;
		isVisible = false;
	}

	PopWindow(const wchar_t *name, int x, int y, int width, int height, int putPriority = 0, bool addInControlTree = true)
		: BaseUI(name, x, y, width, height, putPriority, addInControlTree)
	{
		isVisible = false;
		id = ControlID::popWindow;
	}

	virtual ~PopWindow()
	{
		for (auto item : controlTree)
		{
			delete item.second;
		}
	}

private:
	std::map<std::wstring, BaseUI*> controlTree;	//�ؼ���

public:
	COLORREF backgroundColor = WHITE;				//������ɫ

public:
	virtual void SetVisible(bool isVisible);		//���ÿؼ��Ŀɼ�����
	virtual void Event();							//�¼�
	virtual void Put();								//����
	void AddControl(BaseUI* baseUI);				//��ӿؼ�
	BaseUI* GetControl(const wchar_t* name);		//���ݿؼ�����ȡ�ؼ�ָ��
};


//�ؼ�������
class UIManager
{
	static UIManager *uiManager;
	UIManager()
	{

	}

public:
	~UIManager()
	{
		for (auto item : controlTree)
		{
			delete item.second;
		}
	}

private:
	std::map<std::wstring, BaseUI*> controlTree;		//�ؼ���
	std::multimap<int, BaseUI*> controlSortTree;		//�ؼ�������
	bool isPopWindowEvent = false;						//�Ƿ��е����¼�

public:
	//��ÿؼ�������
	static UIManager* GetUIManager()
	{
		if (!uiManager)
		{
			uiManager = new UIManager;
		}

		return uiManager;
	}

	//��ؼ�����������ӿؼ�
	void AddControl(BaseUI* control)
	{
		if (!control->name.length())
		{
			return;
		}

		controlTree.insert(std::pair<std::wstring, BaseUI*>(control->name, control));
		controlSortTree.insert(std::pair<int, BaseUI*>(control->GetPutPriority(), control));
	}

	//�Ƴ�ָ���ؼ�
	void DeleteControl(const wchar_t* name)
	{
		controlTree.erase(name);
		SortControls();
	}

	//���ݿؼ�����ÿؼ�ָ��
	BaseUI* GetControl(const wchar_t* name)
	{
		return controlTree.find(name) == controlTree.end() ? nullptr : controlTree[name];
	}

	//�Կؼ����������ȼ���������
	void SortControls()
	{
		controlSortTree.clear();
		for (auto item : controlTree)
		{
			controlSortTree.insert(std::pair<int, BaseUI*>(item.second->GetPutPriority(), item.second));
		}
	}

	//�Ƿ���뵯���¼�
	void SetPopWindowEvent(bool isPopWindowEvent)
	{
		this->isPopWindowEvent = isPopWindowEvent;
	}

	///�Ƿ���뵯���¼�
	bool GetPopWindowEvent()
	{
		return isPopWindowEvent;
	}

	//���ƿؼ�
	void Put()
	{
		for (auto item : controlSortTree)
		{
			item.second->Put();
		}
	}

	//�¼�����
	void Event()
	{
		while (MouseHit())
		{
			MOUSEMSG mouseMsg = GetMouseMsg();
			for (auto item : controlTree)
			{			
				if (!isPopWindowEvent || item.second->GetControlID() == ControlID::popWindow)
				{
					item.second->mouseMsg = mouseMsg;
					item.second->Event();
				}
			}
		}
	}
};


/******��Ϸ��Ҫ�õ��Ļ�ͼԪ��******/

//��ʾ����
class PromptArea
{
public:
	PromptArea()
	{

	}

	~PromptArea()
	{

	}

public:
	int x = 0, y = 0;				//λ��
	int width = 0, height = 0;		//��С

public:
	void Reconstruct(int x, int y, int width, int height);	//�������û�������
};


//��ʾ����
class DisplayArea
{
public:
	DisplayArea()
	{

	}

	~DisplayArea()
	{

	}

public:
	int x = 0, y = 0;						//λ��
	int width = 0, height = 0;				//��С
	int frameWidth = 0, frameHeight = 0;	//�߿��С
	int squareWidth = 0, squareHeight = 0;	//��ʾ�ķ����С
};


//��Ϸ����
class UI
{
public:
	UI();

	~UI()
	{
		delete uiManager;
	}

private:
	int promptNumSize = 0;					//������ʾ��������ռ�ݵ����ռ�
	LOGFONT  promptNumFont;					//��ʾ���ֵȵ�����
	clock_t startTime = 0;					//��ʼʱ��
	clock_t currentTime = 0;				//��ǰʱ��
	clock_t lastTime = 0;					//�ϴ���Ϸ���õ�ʱ��
	vector<PromptArea> linePromptAreas;		//����ʾ����
	vector<PromptArea> rowPromptAreas;		//����ʾ����
	DisplayArea displayArea;				//��ʾ����

public:
	GameData gameData;						//��Ϸ����
	SquaresArea* squaresArea = nullptr;		//��������
	UIManager* uiManager = nullptr;			//�ؼ�������

private:	
	void Init();							//��ʼ����������
	void InitSquares();						//��ʼ������
	void InitButtons();						//��ʼ����ť
	void InitPopWindows();					//��ʼ������
	void PutTime();							//����ʱ��
	void PutDisplayArea();					//������ʾ����
	void PutPromptAreas();					//������ʾ����

public:
	void Reconstruct();						//���¹���ö���
	void StartTime();						//��ʼ��ʱ
	long GetTime();							//��ȡ��Ϸʱ��
	void PutStartUI();						//������Ϸ��ʼǰ����
	void Put();								//����
};