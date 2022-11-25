#pragma once
#include<graphics.h>
#include<string>
#include<map>
#include"GameData.h"
//UI绘制

//宏定义一些颜色，方便使用
#define IVORY			0xFAFFFF	//象牙白（偏白）			游戏背景
#define GRAY			0xCCCCCC	//灰色						方格底色、文本
#define LIGHTBLACK		0x323232	//浅黑色（比黑色稍浅）		点击时方格的阴影
#define _DARKGRAY		0x808080	//深灰色					禁止时方格阴影
#define _LIGHTGRAY		0xE0E0E0	//浅灰色（偏白）			禁止时方格表色
#define LIGHTDARKGREEN	0xDED09C	//浅青绿色					提示区域、普通态下按钮表色
#define DARKGREEN		0xBEAE73	//青绿色					提示区域、普通态下按钮阴影、点击态下按钮表色
#define DARKDARKGREEN	0x857025	//深青绿色					点击态下按钮阴影



//方格的状态
enum class SquareState
{
	ordinary = 0,		//普通状态
	beenClicked = 1,	//被点击状态
	prohibitory = 2		//禁止状态
};


//方格
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
	int x = 0, y = 0;							//位置
	int size = 0;								//大小
	SquareState state = SquareState::ordinary;	//状态

public:
	void Reconstruct(int x, int y, int size);	//重新设构造
	bool SetState(UINT message);				//设置方格状态
	void SetState(int state);					//设置方格状态
	SquareState GetState();						//获取方格状态
};


//控件种类
enum class ControlID
{
	base,			//基类
	textBlock,		//文本区域
	imageButton,	//图片按钮
	rectButton,		//矩形按钮
	checkBox,		//复选框
	slideBar,		//滑动条
	squaresArea,	//方格区域		
	popWindow		//弹窗
};


/******一些简单的控件******/

//控件基类
class BaseUI
{
public:
	BaseUI();
	BaseUI(const wchar_t* name, int x, int y, int width, int height, int putPriority, bool addInControlTree);

	virtual ~BaseUI()
	{

	}

protected:
	ControlID id = ControlID::base;		//控件所属的种类
	bool isVisible = true;				//该控件是否可见
	int putPriority = 0;				//绘制优先级
	bool beenPressed = false;			//该控件是否已经被按下，用于点击事件的判断

public:
	std::wstring name = _T("");			//控件名，可作为控件的唯一标志
	int x = 0, y = 0;					//控件位置
	int width = 0, height = 0;			//控件大小（不考虑圆形控件）
	MOUSEMSG mouseMsg{};				//鼠标消息

	void (*mouseInThisEvent) (BaseUI*) = nullptr;	//鼠标在控件上事件
	void (*leftButtonDownEvent) (BaseUI*) = nullptr;//鼠标左键按下事件
	void (*leftButtonUpEvent) (BaseUI*) = nullptr;	//鼠标左键抬起事件
	void (*clickEvent) (BaseUI*) = nullptr;			//点击事件

public:
	ControlID GetControlID();									//获取控件的种类
	virtual void SetPutPriority(int putPriority);				//设置控件的绘制优先级
	virtual int GetPutPriority();								//获取控件的绘制优先级
	virtual void SetVisible(bool isVisible);					//设置控件的可见属性
	virtual bool GetVisible();									//获取控件的可见属性
	virtual void Reset(int x, int y, int width, int height);	//重新设置控件的基本属性
	virtual bool MouseInThis();									//鼠标在该控件上
	virtual bool LeftButtonDown();								//鼠标左键按下
	virtual bool LeftButtonUp();								//鼠标左键抬起
	virtual bool Click();										//点击
	virtual void Event();										//事件
	virtual void Put() = 0;										//绘制
};


//文本显示区
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
	std::wstring text = _T("");		//文本
	LOGFONT textFont;				//字体
	COLORREF textColor = BLACK;		//文字颜色
	UINT format = NULL;				//文本输出格式

public:
	virtual void Put();				//绘制
};


//图片按钮
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
	IMAGE currentImage{};		//当前需要绘制的图片
	IMAGE ordinaryImage{};		//普通状态下按钮图片
	IMAGE beenClickedImage{};	//按压状态下按钮图片

public:
	virtual bool Click();		//点击
	virtual void Event();		//事件
	virtual void Put();			//绘制
};


//矩形按钮
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
	COLORREF ordinaryColor = LIGHTGRAY;		//普通状态颜色
	COLORREF beenClickedColor = GRAY;		//被点击时颜色
	COLORREF borderColor = BLACK;			//边框颜色

public:
	virtual bool Click();					//点击
	virtual void Event();					//事件
	virtual void Put();						//绘制
};


//复选框
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
	bool beenChoosen = false;			//是否被选中
	COLORREF borderColor = BLACK;		//边框颜色
	COLORREF choosenColor = BLACK;		//被选中时中间方块的颜色
	COLORREF fillColor = WHITE;			//填充空白部分的颜色

public:
	virtual void Event();				//鼠标事件
	virtual void Put();					//绘制复选框
};


//滑动块(特殊控件)
//从属于 SlideBar 控件的特殊控件
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
	COLORREF color = LIGHTGRAY;		//滑动块颜色

public:
	void DragMove();				//拖动（仅限于x方向）
	virtual void Put();				//绘制
	
public:
	friend class SlideBar;
};


//滑动条
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
	int value = 0;							//滑动条所表示的值

public:
	Slider slider;							//滑块
	COLORREF slidedColor = 0xffcc66;		//滑块划过地方的颜色
	COLORREF borderColor = BLACK;			//滑动条边框颜色
	void (*slideEvent)(BaseUI*) = nullptr;	//滑动事件

private:
	virtual bool MouseInThis();				//鼠标是否在该控件上
	virtual bool LeftButtonDown();			//鼠标左键是否按下
	void Slide();							//滑动滑块

public:
	void SetValue(int value);				//设置滑动条的值
	int GetValue();							//获取滑动条的值
	virtual void Event();					//事件
	virtual void Put();						//绘制
};


//方格区域（特殊控件）
//仅为该游戏所属的独特控件
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
	int lineDivideSize = 3;						//行分割线间隔
	int rowDivideSize = 3;						//列分割线间隔

public:
	int squareSize = 0;							//方格尺寸
	COLORREF backgroundColor = WHITE;			//底色
	IMAGE ordinaryImage{};						//普通状态下的方格图片
	IMAGE beenClickedImage{};					//点击状态下的方格图片
	IMAGE prohibitoryImage{};					//禁止状态下的方格图片
	void (*hitEvent)(void) = nullptr;			//点击事件
	void (*soundEvent)(int) = nullptr;			//音效事件
	vector<vector<Square>> squares;				//方格
	int arePlay = 7;							//播放哪些音效

private:
	bool RightButtonDown();						//鼠标右键是否按下
	void InitDivideLine();						//初始化分割线间距

public:
	void InitSquares(int lineNum, int rowNum);	//初始化方格
	virtual void Event();						//事件
	virtual void Put();							//绘制方格区域
};


//弹窗（特殊控件）
//拥有子控件，拥有独立事件
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
	std::map<std::wstring, BaseUI*> controlTree;	//控件树

public:
	COLORREF backgroundColor = WHITE;				//背景颜色

public:
	virtual void SetVisible(bool isVisible);		//设置控件的可见属性
	virtual void Event();							//事件
	virtual void Put();								//绘制
	void AddControl(BaseUI* baseUI);				//添加控件
	BaseUI* GetControl(const wchar_t* name);		//根据控件名获取控件指针
};


//控件管理器
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
	std::map<std::wstring, BaseUI*> controlTree;		//控件树
	std::multimap<int, BaseUI*> controlSortTree;		//控件排序树
	bool isPopWindowEvent = false;						//是否有弹窗事件

public:
	//获得控件管理器
	static UIManager* GetUIManager()
	{
		if (!uiManager)
		{
			uiManager = new UIManager;
		}

		return uiManager;
	}

	//向控件管理器中添加控件
	void AddControl(BaseUI* control)
	{
		if (!control->name.length())
		{
			return;
		}

		controlTree.insert(std::pair<std::wstring, BaseUI*>(control->name, control));
		controlSortTree.insert(std::pair<int, BaseUI*>(control->GetPutPriority(), control));
	}

	//移除指定控件
	void DeleteControl(const wchar_t* name)
	{
		controlTree.erase(name);
		SortControls();
	}

	//根据控件名获得控件指针
	BaseUI* GetControl(const wchar_t* name)
	{
		return controlTree.find(name) == controlTree.end() ? nullptr : controlTree[name];
	}

	//对控件按绘制优先级进行排序
	void SortControls()
	{
		controlSortTree.clear();
		for (auto item : controlTree)
		{
			controlSortTree.insert(std::pair<int, BaseUI*>(item.second->GetPutPriority(), item.second));
		}
	}

	//是否进入弹窗事件
	void SetPopWindowEvent(bool isPopWindowEvent)
	{
		this->isPopWindowEvent = isPopWindowEvent;
	}

	///是否进入弹窗事件
	bool GetPopWindowEvent()
	{
		return isPopWindowEvent;
	}

	//绘制控件
	void Put()
	{
		for (auto item : controlSortTree)
		{
			item.second->Put();
		}
	}

	//事件处理
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


/******游戏需要用到的绘图元素******/

//提示区域
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
	int x = 0, y = 0;				//位置
	int width = 0, height = 0;		//大小

public:
	void Reconstruct(int x, int y, int width, int height);	//重新设置基本属性
};


//显示区域
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
	int x = 0, y = 0;						//位置
	int width = 0, height = 0;				//大小
	int frameWidth = 0, frameHeight = 0;	//边框大小
	int squareWidth = 0, squareHeight = 0;	//显示的方格大小
};


//游戏界面
class UI
{
public:
	UI();

	~UI()
	{
		delete uiManager;
	}

private:
	int promptNumSize = 0;					//单个提示数字所能占据的最大空间
	LOGFONT  promptNumFont;					//提示数字等的字体
	clock_t startTime = 0;					//开始时间
	clock_t currentTime = 0;				//当前时间
	clock_t lastTime = 0;					//上次游戏所用的时间
	vector<PromptArea> linePromptAreas;		//行提示区域
	vector<PromptArea> rowPromptAreas;		//列提示区域
	DisplayArea displayArea;				//显示区域

public:
	GameData gameData;						//游戏数据
	SquaresArea* squaresArea = nullptr;		//方格区域
	UIManager* uiManager = nullptr;			//控件管理器

private:	
	void Init();							//初始化基础数据
	void InitSquares();						//初始化方格
	void InitButtons();						//初始化按钮
	void InitPopWindows();					//初始化弹窗
	void PutTime();							//绘制时间
	void PutDisplayArea();					//绘制显示区域
	void PutPromptAreas();					//绘制提示区域

public:
	void Reconstruct();						//重新构造该对象
	void StartTime();						//开始计时
	long GetTime();							//获取游戏时间
	void PutStartUI();						//绘制游戏开始前界面
	void Put();								//绘制
};