#include"breakthroughPage.h"
BreakthroughPage::BreakthroughPage(MatrixUI& UI):UI(UI) {//���캯��

}

//�жϵ�����Ƿ��ھ��η�Χ��
bool BreakthroughPage::_judgeInRect(MOUSEMSG& m, struct Rect rect) {
    if (m.x >= rect.ltx && m.x <= rect.rbx && m.y >= rect.lty && m.y <= rect.rby) {
        return true;
    }
    else {
        return false;
    }
}

void BreakthroughPage::_buttonHover(bool button[9], MOUSEMSG& m) {
    //�ж������Ƿ�����Ÿ���ť��
    int target = -1;//���ھŸ���ť��
    for (int i = 0; i < 9; i++) {
        if (_judgeInRect(m, _buttonRange[i])) {
            button[i] = true;
            for (int j = 0; j < 9; j++) {
                if (i != j) {
                    button[j] = false;
                }
            }
            target = i;
            break;
        }
    }//�������ڵ�״̬

    int same = 1;//����һ��û�б仯
    for (int i = 0; i < 9; i++) {
        if (_lastHoverStatus[i] != button[i]) {
            same = 0;
            break;
        }
    }



    if (target == -1&&same==0) {//���ھŸ���ť��,�Ҷ�����һ���б仯
        for (int i = 0; i < 9; i++) {
            button[i] = false;
        }
        //��ԭͼ
        IMAGE img;
        loadimage(&img, _T("./img/breakthroughpage.png"));
        putimage(0, 0, &img);
        return;
    }
    if (same)return;//״̬���޸ı�         
   
    //��¼��һ�εİ�ť״̬��������һ�ε�����
    for (int j = 0; j < 9; j++) {
        _lastHoverStatus[j] = button[j];
    }
    _resizeButton(button,target);
}


//���������趨��ť�Ĵ�С
void BreakthroughPage::_resizeButton(bool button[9],int target) {
    if (target == -1) {
        return;
    }
    //ʹ�ð�ťΧ�����ķŴ�
    IMAGE img;
    switch (target)
    {
    case 0:
        loadimage(&img, _T("./img/buttonResize/button0.png"));
        putimage(0, 0, &img); 
        break;
    case 1:
        loadimage(&img, _T("./img/buttonResize/button1.png"));
        putimage(0, 0, &img);
        break;
    case 2:
        loadimage(&img, _T("./img/buttonResize/button2.png"));
        putimage(0, 0, &img);
        break;
    case 3:
        loadimage(&img, _T("./img/buttonResize/button3.png"));
        putimage(0, 0, &img);
        break;
    case 4:
        loadimage(&img, _T("./img/buttonResize/button4.png"));
        putimage(0, 0, &img);
        break;
    case 5:
        loadimage(&img, _T("./img/buttonResize/button5.png"));
        putimage(0, 0, &img);
        break;
    case 6:
        loadimage(&img, _T("./img/buttonResize/button6.png"));
        putimage(0, 0, &img);
        break;
    case 7:
        loadimage(&img, _T("./img/buttonResize/button7.png"));
        putimage(0, 0, &img);
        break;
    case 8:
        loadimage(&img, _T("./img/buttonResize/button8.png"));
        putimage(0, 0, &img);
        break;
    default:
        break;
    }
}

int BreakthroughPage::_mClick(MOUSEMSG& m) {
    for (int i = 0; i < 9; i++) {
        if (_judgeInRect(m, _buttonRange[i])) {
            return i;
        }
    }
    return -1;
}


int BreakthroughPage::process(void) {//ѭ������
	//��ҳ��ͼ
	IMAGE img;
	loadimage(&img, _T("./img/breakthroughpage.png"));
	putimage(0, 0, &img);
    MOUSEMSG m;//����¼�
    bool button[9] = { 0 };//��ť
    while (true)
    {
        // ��ȡһ�������Ϣ
        m = GetMouseMsg();
        _buttonHover(button,m);
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            int event = _mClick(m);
            //���صİ�ť���Ϊ0-8,0-7λ�ؿ���˳��8Ϊ�˳��˻ص���һ���İ�ť
            if (event == 8) {
                cout << 8 << endl;
                return 8;
            }
            else if(0<=event&&event<=7){
                LevelPage level(event+49);
                cout << event + 49 <<endl;
                level.process();//����������ָ����ؽ���
                _resetUI();
            }
            break;
        }
    }
}
void BreakthroughPage::_resetUI(void) {
    //������
    IMAGE img;
    loadimage(&img, _T("./img/breakthroughpage.png"));
    putimage(0, 0, &img);
}


