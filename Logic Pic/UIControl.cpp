#include"UI.h"

UIManager* UIManager::uiManager = nullptr;


//���¹���
void Square::Reconstruct(int x, int y, int size)
{
	this->x = x;
	this->y = y;
	this->size = size;
}

//���÷���״̬(�ɹ��ı�״̬�����棬���򷵻ؼ�)
bool Square::SetState(UINT message)
{
	switch (state)
	{
	case SquareState::ordinary:
		state = message == WM_LBUTTONDOWN ? SquareState::beenClicked : SquareState::prohibitory;
		return true;

	case SquareState::beenClicked:
		state = message == WM_LBUTTONDOWN ? SquareState::ordinary : SquareState::beenClicked;
		return state == SquareState::beenClicked ? false : true;

	case SquareState::prohibitory:
		state = message == WM_RBUTTONDOWN ? SquareState::ordinary :SquareState::prohibitory;
		return state == SquareState::prohibitory ? false : true;

	default:
		return false;
	}
}

//���÷���״̬
void Square::SetState(int state)
{
	this->state = (SquareState)state;
}

//��÷����״̬
SquareState Square::GetState()
{
	return state;
}


//���캯��
BaseUI::BaseUI()
{
	UIManager::GetUIManager()->AddControl(this);
}

//���캯��
//�ؼ�����λ�á���С���������ȼ���������ʵ��ʱ�Ƿ�ֱ�Ӽ���ؼ�������
BaseUI::BaseUI(const wchar_t* name, int x = 0, int y = 0, int width = 0,
	int height = 0, int putPriority = 0, bool addInControlTree = true)
{
	this->name = name;
	this->x = x, this->y = y;
	this->width = width;
	this->height = height;
	this->putPriority = putPriority;
	if (addInControlTree)
	{
		UIManager::GetUIManager()->AddControl(this);
	}
}


//���ÿؼ��Ļ������ȼ�
void BaseUI::SetPutPriority(int putPriority)
{
	this->putPriority = putPriority;
	UIManager::GetUIManager()->SortControls();
}

//��ȡ�ؼ��Ļ������ȼ�
int BaseUI::GetPutPriority() 
{
	return putPriority;
}

//���ÿؼ��Ŀɼ�״̬
void BaseUI::SetVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

//��ȡ�ؼ��Ŀɼ�״̬
bool BaseUI::GetVisible()
{
	return isVisible;
}

//�������ÿؼ��Ļ�������
void BaseUI:: Reset(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

//����Ƿ��ڸÿؼ���
bool BaseUI::MouseInThis()
{
	return mouseMsg.x > x && mouseMsg.x < x + width
		&& mouseMsg.y > y && mouseMsg.y < y + height;
}

//�������Ƿ���
bool BaseUI::LeftButtonDown()
{
	return MouseInThis() && mouseMsg.uMsg == WM_LBUTTONDOWN;
}

//�������Ƿ�̧��
bool BaseUI::LeftButtonUp()
{
	return MouseInThis() && mouseMsg.uMsg == WM_LBUTTONUP;
}

//�Ƿ���
bool BaseUI::Click()
{
	return beenPressed && LeftButtonUp();
}

//�����¼��ļ��д���
void BaseUI::Event()
{
	if (!isVisible)
	{
		return;
	}

	beenPressed = beenPressed && MouseInThis();
	if (MouseInThis() && mouseInThisEvent)
	{
		mouseInThisEvent(this);
	}

	if (LeftButtonDown())
	{
		beenPressed = true;
		if (leftButtonDownEvent)
		{
			leftButtonDownEvent(this);
		}
	}

	if (Click() && clickEvent)
	{
		clickEvent(this);
	}

	if (LeftButtonUp())
	{
		beenPressed = false;
		if (leftButtonUpEvent)
		{
			leftButtonUpEvent(this);
		}
	}
}

//��øÿؼ�������
ControlID BaseUI::GetControlID()
{
	return id;
}


//����
void TextBlock::Put()
{
	if (!isVisible)
	{
		return;
	}

	RECT rect{ x, y, x + width, y + height };

	settextstyle(&textFont);
	settextcolor(textColor);

	drawtext(text.c_str(), &rect, format);
}


//�Ƿ���
bool ImageButton::Click()
{
	currentImage = beenPressed ? ordinaryImage : beenClickedImage;

	return beenPressed && LeftButtonUp();
}

//�¼�
void ImageButton::Event()
{
	if (!isVisible)
	{
		return;
	}

	beenPressed = beenPressed && MouseInThis();

	if (LeftButtonDown())
	{
		beenPressed = true;
		Put();
	}

	if (Click() && clickEvent)
	{
		clickEvent(this);
		Put();
	}

	if (LeftButtonUp())
	{
		beenPressed = false;
		Put();
	}
}

//����
void ImageButton::Put()
{
	if (!isVisible)
	{
		return;
	}
	putimage(x, y, beenPressed ? &beenClickedImage : &ordinaryImage);
}


//�Ƿ���
bool RectButton::Click()
{
	return beenPressed && LeftButtonUp();
}

//�¼�
void RectButton::Event()
{
	if (!isVisible)
	{
		return;
	}

	beenPressed = beenPressed && MouseInThis();

	if (LeftButtonDown())
	{
		beenPressed = true;
		Put();
	}

	if (Click() && clickEvent)
	{
		clickEvent(this);
		//Put();
	}

	if (LeftButtonUp())
	{
		beenPressed = false;
		//Put();
	}
}

//����
void RectButton::Put()
{
	if (!isVisible)
	{
		return;
	}

	setlinecolor(borderColor);
	setfillcolor(beenPressed ? beenClickedColor : ordinaryColor);

	fillrectangle(x, y, x + width, y + height);

	TextBlock::Put();
}



//�¼�
void CheckBox::Event()
{
	if (!isVisible)
	{
		return;
	}

	if (LeftButtonDown())
	{
		beenChoosen = !beenChoosen;
		if (leftButtonDownEvent)
		{
			leftButtonDownEvent(this);
		}

		Put();
	}
}

//����
void CheckBox::Put()
{
	if (!isVisible)
	{
		return;
	}

	setfillcolor(borderColor);
	solidrectangle(x, y, x + width, y + height);

	setfillcolor(fillColor);
	solidrectangle(x + width / 6, y + height / 6,
		x + width - width / 6, y + height - height / 6);

	if (beenChoosen)
	{
		setfillcolor(choosenColor);
		solidrectangle(x + width / 3, y + height / 3,
			x + width - width / 3, y + height - height / 3);
	}
}



//�ƶ�����
void Slider::DragMove()
{
	static int mouseX = 0;
	if (LeftButtonDown())
	{
		mouseX = mouseMsg.x;
		isDrag = true;
	}

	if (isDrag && mouseMsg.uMsg == WM_LBUTTONUP)
	{
		isDrag = false;
	}

	if (isDrag && mouseMsg.x != mouseX)
	{
		x += (mouseMsg.x - mouseX);
		mouseX = mouseMsg.x;
	}
}

//����
void Slider::Put()
{
	if (!isVisible)
	{
		return;
	}
	setfillcolor(color);
	solidrectangle(x, y, x + width, y + height);
}


//���û���ֵ
void SlideBar::SetValue(int value)
{
	this->value = value;
	slider.x = x + value * (width - slider.width) / 100;
}

//��ȡ����ֵ
int SlideBar::GetValue()
{
	return value;
}

//����Ƿ��ڸÿؼ���
bool SlideBar::MouseInThis()
{
	return slider.MouseInThis() || (mouseMsg.x >= x && mouseMsg.x <= x + width && 
		mouseMsg.y >= slider.y && mouseMsg.y <= slider.y + slider.height);
}

//�������Ƿ���
bool SlideBar::LeftButtonDown()
{
	return mouseMsg.uMsg == WM_LBUTTONDOWN && MouseInThis();
}

//��������
void SlideBar::Slide()
{
	if (value == 0 || value == 100)
	{
		if (mouseMsg.x >= x && mouseMsg.x < x + width || mouseMsg.uMsg == WM_LBUTTONUP)
		{
			slider.mouseMsg = mouseMsg;
			slider.DragMove();
		}
	}
	else
	{
		slider.mouseMsg = mouseMsg;
		slider.DragMove();
	}

	//�����������ڻ�������
	if (slider.x + slider.width >= x + width)
	{
		slider.x = x + width - slider.width;
	}
	else if (slider.x <= x)
	{
		slider.x = x;
	}

	value = (slider.x - x) * 100 / (width - slider.width);
}

//�¼�
void SlideBar::Event()
{
	if (!isVisible)
	{
		return;
	}

	Slide();

	if (LeftButtonDown())
	{
		slider.x = mouseMsg.x;
		if (slider.x + slider.width >= x + width)
		{
			slider.x = x + width - slider.width;
		}
		else if (slider.x <= x)
		{
			slider.x = x;
		}

		value = (slider.x - x) * 100 / (width - slider.width);
	}

	if (slideEvent)
	{
		slideEvent(this);
	}

	Put();
}

//����
void SlideBar::Put()
{
	if (!isVisible)
	{
		return;
	}
	setlinecolor(borderColor);
	rectangle(x, y, x + width, y + height);

	setfillcolor(slidedColor);
	solidrectangle(x + 1, y + 1, slider.x, y + height - 1);

	slider.Put();
}



//���ÿؼ��Ŀɼ�����
void PopWindow::SetVisible(bool isVisible)
{
	this->isVisible = isVisible;
	for (auto item : controlTree)
	{
		item.second->SetVisible(isVisible);
	}
	UIManager::GetUIManager()->SetPopWindowEvent(isVisible);

	//������������״̬������ۼ������»���
	if (!isVisible)
	{
		cleardevice();
		UIManager::GetUIManager()->Put();
	}
}

//�¼�
void PopWindow::Event()
{
	if (!isVisible)
	{
		return;
	}

	for (auto item : controlTree)
	{
		item.second->mouseMsg = mouseMsg;
		item.second->Event();
	}

	Put();
}

//����
void PopWindow::Put()
{
	if (!isVisible)
	{
		return;
	}

	setfillcolor(backgroundColor);
	solidrectangle(x, y, x + width, y + height);

	for (auto item : controlTree)
	{
		item.second->Put();
	}
}

//��ӿؼ�
void PopWindow::AddControl(BaseUI* baseUI)
{
	controlTree.insert(std::pair<std::wstring, BaseUI*>(baseUI->name, baseUI));
}

//���ݿؼ�����ȡ�ؼ�ָ��
BaseUI* PopWindow::GetControl(const wchar_t* name)
{
	return controlTree.find(name) == controlTree.end() ? nullptr : controlTree[name];
}



//��ʼ������
void SquaresArea::InitSquares(int lineNum, int rowNum)
{
	squares.resize(lineNum);
	for (int i = 0; i < squares.size(); i++ )
	{
		squares[i].resize(rowNum);
		for (int j = 0; j < squares[i].size(); j++)
		{
			squares[i][j].Reconstruct(x + squareSize * j + 1,
				y + squareSize * i + 1, squareSize);
		}
	}

	InitDivideLine();
}

//��ʼ���ָ��߼��
void SquaresArea::InitDivideLine()
{
	int lineNum = (int)squares.size(), rowNum = (int)squares[0].size();

	//��ȡ�ָ���λ��
	while (lineNum > 3 * lineDivideSize ||
		(lineNum % lineDivideSize > 0 && lineNum % lineDivideSize < 3))
	{
		lineDivideSize++;
	}

	while (rowNum > 3 * rowDivideSize ||
		(rowNum % rowDivideSize > 0 && rowNum % rowDivideSize < 3))
	{
		rowDivideSize++;
	}
}

//����Ҽ��Ƿ���
bool SquaresArea::RightButtonDown()
{
	return MouseInThis() && mouseMsg.uMsg == WM_RBUTTONDOWN;
}

//�¼�
void SquaresArea::Event()
{
	if (LeftButtonDown() || RightButtonDown())
	{
		int beenClickedSquareX = (mouseMsg.x - x + squareSize) / squareSize - 1;
		int beenClickedSquareY = (mouseMsg.y - y + squareSize) / squareSize - 1;

		if (squares[beenClickedSquareY][beenClickedSquareX].SetState(mouseMsg.uMsg) && soundEvent)
		{
			soundEvent((int)squares[beenClickedSquareY][beenClickedSquareX].GetState());
		}

		if (hitEvent)
		{
			hitEvent();
		}

		Put();
	}
}

//����
void SquaresArea::Put()
{
	if (!isVisible)
	{
		return;
	}
	setfillcolor(backgroundColor);
	solidrectangle(x, y, x + width, y + height);

	for (vector<Square> squareList : squares)
	{
		for (Square square : squareList)
		{
			switch (square.GetState())
			{
			case SquareState::ordinary:
				putimage(square.x, square.y, &ordinaryImage);
				break;

			case SquareState::beenClicked:
				putimage(square.x, square.y, &beenClickedImage);
				break;

			case SquareState::prohibitory:
				putimage(square.x, square.y, &prohibitoryImage);
				break;

			default:
				break;
			}
		}
	}

	//���Ʒָ���
	setfillcolor(LIGHTBLACK);
	
	for (int i = lineDivideSize; i < squares.size(); i += lineDivideSize)
	{
		solidrectangle(x + 2, squares[i][0].y - 1, x + width - 2, squares[i][0].y);	
	}

	for (int i = rowDivideSize; i < squares[0].size(); i += rowDivideSize)
	{
		solidrectangle(squares[0][i].x - 1, y + 2, squares[0][i].x, y + height - 2);
	}
}