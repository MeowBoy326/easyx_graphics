#include"indexPage.h"
IndexPage::IndexPage(MatrixUI& UI):UI(UI){//���캯��
	_buttonRange[0] = { 500 + 120, 500 + 673, 50 + 105, 50 + 207 };
	_buttonRange[0] = { 500 + 136, 500 + 672, 50 + 264, 50 + 367 };
	_buttonRange[0] = { 500 + 133, 500 + 684, 50 + 427, 50 + 528 };
}

bool IndexPage::_judgeInRect(MOUSEMSG& m,struct Rect rect ) {
    if (m.x >= rect.ltx&&m.x<=rect.rbx&&m.y>=rect.lty&&m.y<=rect.rby) {
        return true;
    }
    else {
        return false;
    }
}

void IndexPage::_buttonHover(bool button[3], MOUSEMSG& m) {//��ťhover��ɫ
    static int sum = 0;
    if ( _judgeInRect(m,_buttonRange[0])) {
        button[0] = true;
        button[1] = false;
        button[2] = false;
        sum++;
        //cout << "����" << sum << endl;
    }
    else if (_judgeInRect(m, _buttonRange[1])) {
        button[0] = false;
        button[1] = true;
        button[2] = false;
        sum++;
        //cout << "�浵"<<sum<<endl;
    }
    else if (_judgeInRect(m, _buttonRange[2])) {
        button[0] = false;
        button[1] = false;
        button[2] = true;
        sum++;
        //cout << "�˳���Ϸ"<<sum<<endl;
    }
    else {
        button[0] = false;
        button[1] = false;
        button[2] = false;
        sum++;
        //cout << "û�д�����ť"<<sum<<endl;
    }
    if (sum > 2000) {
        sum = 0;
    }
    //�ж�������İ�ť��ɫ
    int target;
    if (button[0]&&_diffHoverStatus(button)) {
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton1.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
    else if (button[1] && _diffHoverStatus(button)) {
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton2.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
    else if (button[2] && _diffHoverStatus(button)) {
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton3.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
    else if(_diffHoverStatus(button)){
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
}


int IndexPage::process(void) {
    struct Point point;
    UI.setBkColor(255, 255, 255);

    for (int i = 0; i < UI.getWidth(); i++) {//��ҳ����
        for (int j = 0; j < 50; j++) {
            point.y = j;
            point.x = i;
            UI.setUIBuffer(point,180,124,72);
        }
    }

    FlushBatchDraw();
    IMAGE img1, img2;
    loadimage(&img1, _T("./img/test.png"));
    putimage(0, 50, &img1);
    loadimage(&img2, _T("./img/indexPageButton.png"));
    putimage(500, 50, &img2);
    MOUSEMSG m;//����¼�
    bool button[3] = { 0 };//��ťhover��̬Ч��
    while (true)
    {
        // ��ȡһ�������Ϣ
        m = GetMouseMsg();
        _buttonHover(button, m);//��ťhoverЧ��
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            if (_judgeInRect(m, _buttonRange[0])) {
                _resetAll();
                cout << "����\n";
                return 1;
            }
            else if (_judgeInRect(m, _buttonRange[1])) {
                _resetAll();
                cout << "ʵ����\n";
                return 2;
            }
            else if (_judgeInRect(m, _buttonRange[2])) {
                _resetAll();
                cout << "�˳���Ϸ\n";
                return 3;
            }
            break;
        }
    }

}


//�ж���һ������һ���Ƿ��б仯
bool IndexPage::_diffHoverStatus(bool button[3]) {
    if (button[0] != _lastHoverStatus[0]) {
        return 1;
    }
    if (button[1] != _lastHoverStatus[1]) {
        return 1;
    }
    if (button[2] != _lastHoverStatus[2]) {
        return 1;
    }
    return 0;//û�б仯
}

//������һ�ε�hover״̬
void IndexPage::_setLastHoverStatus(bool button[3]) {
    for (int i = 0; i < 3; i++) {
        _lastHoverStatus[i] = button[i];
    }
}


//���ý��棬��������ʱ
void IndexPage::_resetAll(void) {
    _lastHoverStatus[0] = false;
    _lastHoverStatus[1] = false;
    _lastHoverStatus[2] = false;
    IMAGE img;
    loadimage(&img, _T("./img/indexPageButton.png"));
    putimage(500, 50, &img);
}