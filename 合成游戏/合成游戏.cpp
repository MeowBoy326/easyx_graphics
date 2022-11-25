#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <direct.h>
using namespace std;

struct JN					//����ͼ��
{
	LPCTSTR name;			//��������
	int cs;					//���ܲ���
	int lb;					//�������
	int bh;					//���ܱ��
};

struct mowu					//ħ��ͼ��
{
	LPCTSTR race;			//��
	int ns;					//"��"������
	int clan;				//��(����)
	int pz;					//Ʒ��
	int pj;					//Ʒ��/��
	LPCTSTR tp;				//ͼƬ
};

struct TBOC					//�ٻ�֮��(ҳ��) / Ұ��ħ��
{
	int race;				//��
	int clan;				//��(����)
	int pz;					//Ʒ��
	int pj;					//Ʒ��/��
	int pjz;				//���н���ֵ
	int dj;					//�ȼ�
	int srd;				//�����ȼ�
	unsigned long long ep;	//����
	int hlm;				//��߻�������
	int hls;				//�ѻ�������
	int hlz;				//�����׼�ֵ
	long long s_gj;			//������
	long long s_fy;			//������
	long long s_hp;			//����ֵ
	long long s_zl;			//ս��
	long long s_sd;			//�ٶ�
	int bjl;				//������
	int gdl;				//����
	int rsh;				//����λ��
	int js;					//ӵ�м�������
	vector<JN> jns;			//����ӵ�м���
};

struct PL					//̽��֮·�ص�
{
	LPCTSTR name;			//�ص���
	int ns;					//�ص�����
	int gl;					//�ɼ�����
	LPCTSTR tp;				//ͼƬ
};

struct WP					//��Ʒͼ��
{
	LPCTSTR name;			//��Ʒ����
	int ns;					//��Ʒ����
	int bh_j;				//�����ֱ��	�Ǿ���Ϊ0
	int bh_z;				//��������	�Ǿ���Ϊ0
	long long b_jg;			//����۸�
	long long s_jg;			//�۳��۸�
};

struct CK					//�ֿ���Ʒ
{
	int wz;					//��Ʒ����
	int wt;					//����Ʒͼ���б��
	int sum;				//����
};

struct KMW					//̽��֮·��ˢ��ħ��
{
	int clan;				//��
	int rl;					//�����
	int rh;					//�����
	int pzl;				//���Ʒ��
	int pzh;				//���Ʒ��
	int djl;				//��͵ȼ�
	int djh;				//��ߵȼ�
	int srl;				//��ͻ���
	int srh;				//��߻���
};

struct WRH					//��Ʒ�ں�ͼ��
{
	int mz;					//�ںϺ���Ʒ����
	int mr;					//�ںϺ���Ʒ���
	int n;					//��Ҫ�ںϵ���Ʒ����
	vector<int> nz;			//��Ҫ�ںϵĵ�i����Ʒ����
	vector<int> nr;			//��Ҫ�ںϵĵ�i����Ʒ���
	vector<int> ns;			//��Ҫ�ںϵĵ�i����Ʒ����
};

struct CDWP					//ħ��ɵ�����Ʒ
{
	int z;					//����
	int j;					//���
	int suml;				//��������
	int sumh;				//�������
	int gl;					//��ø���
};

struct MWZ					//ͼ��ħ�������ֵ
{
	int top;				//���Ʒ��
	int bs_pj;				//����Ʒ��
	long long s_gj;			//������
	long long s_fy;			//������
	long long s_hp;			//����ֵ
	long long s_sd;			//�ٶ�
	int bjl;				//������
	int gdl;				//����
};

double bbh;					//¼��汾��
int mn = 3;					//ͼ��ħ������
int tsl;					//̽��֮·�ص�����
int bks;					//�ٻ�֮����ҳ��
int now_where;				//̽���е�ǰλ��
int rhsum;					//�ں���Ʒ����
int zrbh[20];				//�������ٻ������ٻ�֮���б��
int wpls[10];				//������Ʒ����
long long ys;				//��ʯ����
long long nep[20] = { 1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15,1e16,1e17 };
long long npj[30] = { 0,1,4,16,16 * 4,64 * 4,256 * 4,1024 * 4,4096 * 4,16384 * 4,65536 * 4,262144 * 4,1048576 * 4,4194304 * 4,16777216 * 4,67108864 * 4,268435456 * 4 };
long long hlz[30] = { 100 * 5,200 * 5,400 * 5,800 * 5,1600 * 5,3200 * 5,6400 * 5,12800 * 5,25600 * 5,51200 * 5,102400 * 5,204800 * 5,409600 * 5,819200 * 5,819200 * 2 * 5 };
double dsj[160];			//�ȼ������ӳɱ���
double pzj[100];			//Ʒ�ʼӳɱ���
double pjj[100];			//Ʒ�׼ӳɱ���
vector<CK> cwp;				//�ֿ���Ʒ
vector<int>	mp[100];		//̽��֮··��
vector<TBOC>sob[100];		//̽��֮·ħ��
vector<KMW> kmw[100];		//�ص�i��ˢ��ħ��
vector<CDWP>dmw[20][20];	//ħ��ɵ�����Ʒ
MOUSEMSG m;
string buf;
LPCTSTR JNLB[10] = { _T("��"),_T("������"),_T("ת����"),_T("��ͨ��"),_T("�޶���"),_T("���Ѽ�") };
LPCTSTR CLAN[20] = { _T("��"),_T("�粼��"),_T("ʯ��"),_T("��ҳ��"),_T("���漦"),_T("���"),_T("ˮԪ��") };
LPCTSTR PJ[30] = { _T("��"),_T("��ͨ*"),_T("��ͨ**"),_T("��ͨ***"),_T("ϡ��*"),_T("ϡ��**") ,_T("ϡ��***") ,_T("����*") ,_T("����**") ,_T("����***") ,_T("����*") ,_T("����**") ,_T("����***") ,_T("ʷʫ*") ,_T("ʷʫ**") ,_T("ʷʫ***") ,_T("��˵*") ,_T("��˵**") ,_T("��˵***") ,_T("��*") ,_T("��**") ,_T("��***") ,_T("����*") ,_T("����**") ,_T("����***") };
LPCTSTR PZ[30] = { _T("��"),_T("����"),_T("����"),_T("����") ,_T("����") ,_T("����") ,_T("�ۻ�") ,_T("ʥ��") ,_T("λ��") ,_T("����") ,_T("����") };
mowu pmw[20][20];			//ͼ��ħ��
TBOC pt[20];				//�ٻ�֮���ٻ���
PL place[100];				//̽��֮·�ص�
WP thing[4][100];			//��Ʒͼ�� thing[1]..ħ�ﾫ��  thing[2]..��Ʒ
WRH rhwp[20];				//��Ʒ�ں�ͼ��
MWZ mws[20];				//����ħ���������
JN pjn[20][10][10];			//����ħ����㼼��

long long random(int l, int r);				//�����
void cl_tj();								//ħ��ͼ����ʼ��
void in_bok();								//¼���ٻ�֮��
void open();								//��ʼҳ��
void main_page();							//��ҳ��
void bok(int k, int f);						//�ٻ�֮��ҳ��
void ele(int k);							//̽��
void cl_map();								//��ʼ����ͼ
void cl_ts(int z);							//ˢ��̽��֮·�ٻ���
bool PvE(TBOC E[], int tot, int tos);		//��ս����
bool cs_page(int z, bool r);					//����ҳ��
void cc_page();								//����ҳ��
bool lor_mw(int f, TBOC k);					//�鿴ħ����ϸ����
void cl_wp();								//��ʼ����Ʒͼ��
void cl();									//��ʼ������
void in_map();								//¼��̽��֮·ħ��
void out_map();								//����̽��֮·ħ��
void outs();								//��������
void mw_lt(int c, int r, int z, int dj);		//ħ�������Ʒ
int find_wp(int z, int k);					//���Ҳֿ���Ʒ
void out_bok();								//�����ٻ�֮��
void out_ck();								//����ֿ�
void in_ck();								//¼��ֿ�
void get_jy(int k, int f);					//��ȡ����
void rh_page(int k);						//�ں�ҳ��
void lor_wp(CK k, int f);					//�鿴��Ʒ��ϸ����
bool wp_ef(int z, int k);					//��Ʒʹ��Ч��
void sg_page(int k);						//����ҳ��
bool ck_px(CK a, CK b);						//�ֿ�����
void rl_page(int f, int k, int z);			//����ҳ��
void cl_rh();								//��ʼ����Ʒ�ں�ͼ��
void cl_dw();								//��ʼ��ħ��ɵ�����Ʒ
void zr_page();								//��λҳ��
void map_page();							//�鿴��ͼҳ��
void in_bbh();								//¼��汾��
void out_bbh();								//����汾��
void hl_page(int k);						//����ҳ��
void wp_ms(int z, int t);					//��Ʒ����
void sh_page(int k);						//����ҳ��
bool bok_px(TBOC a, TBOC b);				//�ٻ�֮������
void sc_page(int t, int z);					//�̳�ҳ��
void cl_jn();								//����ͼ��


long long random(int l, int r)
{
	int x = rand() + rand() / rand() * (rand() + 1239) + rand();
	return x % (max(r - l + 1, 1)) + l;
}

void cl_tj()		//ħ��ͼ����ʼ��
{
	pmw[0][0].race = _T("��"), pmw[0][0].ns = 3, pmw[0][0].clan = 0;
	mws[0].bs_pj = 1;
	//�粼������
	mws[1].top = 16, mws[1].bs_pj = 1, mws[1].s_gj = 15, mws[1].s_fy = 5, mws[1].s_hp = 100, mws[1].s_sd = 10, mws[1].bjl = 10, mws[1].gdl = 10;
	pmw[1][1].race = _T("�粼��"), pmw[1][1].ns = 3, pmw[1][1].clan = 1, pmw[1][1].pz = 1, pmw[1][1].pj = 1, pmw[1][1].tp = _T("res\\�粼��.jpg");
	pmw[1][2].race = _T("��粼��"), pmw[1][2].ns = 4, pmw[1][2].clan = 1, pmw[1][2].pz = 1, pmw[1][2].pj = 2, pmw[1][2].tp = _T("res\\��粼��.jpg");
	pmw[1][3].race = _T("�粼����ʿ"), pmw[1][3].ns = 5, pmw[1][3].clan = 1, pmw[1][3].pz = 1, pmw[1][3].pj = 3, pmw[1][3].tp = _T("res\\�粼����ʿ.jpg");
	pmw[1][4].race = _T("�粼������"), pmw[1][4].ns = 5, pmw[1][4].clan = 1, pmw[1][4].pz = 1, pmw[1][4].pj = 4, pmw[1][4].tp = _T("res\\�粼������.jpg");
	pmw[1][5].race = _T("�粼�ִ�����"), pmw[1][5].ns = 6, pmw[1][5].clan = 1, pmw[1][5].pz = 1, pmw[1][5].pj = 5, pmw[1][5].tp = _T("res\\�粼�ִ�����.jpg");
	pmw[1][6].race = _T("�粼�ּ�ʦ"), pmw[1][6].ns = 5, pmw[1][6].clan = 1, pmw[1][6].pz = 1, pmw[1][6].pj = 6, pmw[1][6].tp = _T("res\\�粼�ּ�ʦ.jpg");
	pmw[1][7].race = _T("�粼������"), pmw[1][7].ns = 5, pmw[1][7].clan = 1, pmw[1][7].pz = 1, pmw[1][7].pj = 7, pmw[1][7].tp = _T("res\\�粼������.jpg");
	pmw[1][8].race = _T("�粼������"), pmw[1][8].ns = 5, pmw[1][8].clan = 1, pmw[1][8].pz = 1, pmw[1][8].pj = 8, pmw[1][8].tp = _T("res\\�粼������.jpg");
	pmw[1][9].race = _T("�粼�ֿ�սħ"), pmw[1][9].ns = 6, pmw[1][9].clan = 1, pmw[1][9].pz = 1, pmw[1][9].pj = 9, pmw[1][9].tp = _T("res\\�粼�ֿ�սħ.jpg");
	pmw[1][10].race = _T("Ѫ�ڸ粼��"), pmw[1][10].ns = 5, pmw[1][10].clan = 1, pmw[1][10].pz = 1, pmw[1][10].pj = 10, pmw[1][10].tp = _T("res\\Ѫ�ڸ粼��.jpg");
	pmw[1][11].race = _T("Ѫ�������粼��"), pmw[1][11].ns = 7, pmw[1][11].clan = 1, pmw[1][11].pz = 1, pmw[1][11].pj = 11, pmw[1][11].tp = _T("res\\Ѫ�������粼��.jpg");
	pmw[1][12].race = _T("�粼����ɱ��"), pmw[1][12].ns = 6, pmw[1][12].clan = 1, pmw[1][12].pz = 1, pmw[1][12].pj = 12, pmw[1][12].tp = _T("res\\�粼����ɱ��.jpg");
	pmw[1][13].race = _T("�����粼��"), pmw[1][13].ns = 5, pmw[1][13].clan = 1, pmw[1][13].pz = 1, pmw[1][13].pj = 13, pmw[1][13].tp = _T("res\\�����粼��.jpg");
	pmw[1][14].race = _T("����.����粼��"), pmw[1][14].ns = 7, pmw[1][14].clan = 1, pmw[1][14].pz = 1, pmw[1][14].pj = 14, pmw[1][14].tp = _T("res\\����.����粼��.jpg");
	pmw[1][15].race = _T("��ȭ.ս�׸粼��"), pmw[1][15].ns = 7, pmw[1][15].clan = 1, pmw[1][15].pz = 1, pmw[1][15].pj = 15, pmw[1][15].tp = _T("res\\��ȭ.ս�׸粼��.jpg");
	pmw[1][16].race = _T("Ӱҹ.�粼��ɱ��"), pmw[1][16].ns = 7, pmw[1][16].clan = 1, pmw[1][16].pz = 1, pmw[1][16].pj = 16, pmw[1][16].tp = _T("res\\Ӱҹ.�粼��ɱ��.jpg");

	//ʯ������
	mws[2].top = 13, mws[2].bs_pj = 2, mws[2].s_gj = 10, mws[2].s_fy = 18, mws[2].s_hp = 130, mws[2].s_sd = 3, mws[2].bjl = 5, mws[2].gdl = 15;
	pmw[2][1].race = _T("ʯ�ӹ�"), pmw[2][1].ns = 3, pmw[2][1].clan = 2, pmw[2][1].pz = 1, pmw[2][1].pj = 2, pmw[2][1].tp = _T("res\\ʯ�ӹ�.jpg");
	pmw[2][2].race = _T("Сʯ��"), pmw[2][2].ns = 3, pmw[2][2].clan = 2, pmw[2][2].pz = 1, pmw[2][2].pj = 3, pmw[2][2].tp = _T("res\\Сʯ��.jpg");
	pmw[2][3].race = _T("ʯͷ��"), pmw[2][3].ns = 3, pmw[2][3].clan = 2, pmw[2][3].pz = 1, pmw[2][3].pj = 4, pmw[2][3].tp = _T("res\\ʯͷ��.jpg");
	pmw[2][4].race = _T("����ʯ��"), pmw[2][4].ns = 4, pmw[2][4].clan = 2, pmw[2][4].pz = 1, pmw[2][4].pj = 5, pmw[2][4].tp = _T("res\\����ʯ��.jpg");
	pmw[2][5].race = _T("����ʯ��"), pmw[2][5].ns = 4, pmw[2][5].clan = 2, pmw[2][5].pz = 1, pmw[2][5].pj = 6, pmw[2][5].tp = _T("res\\����ʯ��.jpg");
	pmw[2][6].race = _T("�����Ҿ�"), pmw[2][6].ns = 4, pmw[2][6].clan = 2, pmw[2][6].pz = 1, pmw[2][6].pj = 7, pmw[2][6].tp = _T("res\\�����Ҿ�.jpg");
	pmw[2][7].race = _T("��ʯ��"), pmw[2][7].ns = 3, pmw[2][7].clan = 2, pmw[2][7].pz = 1, pmw[2][7].pj = 8, pmw[2][7].tp = _T("res\\��ʯ��.jpg");
	pmw[2][8].race = _T("����ʯ��"), pmw[2][8].ns = 4, pmw[2][8].clan = 2, pmw[2][8].pz = 1, pmw[2][8].pj = 9, pmw[2][8].tp = _T("res\\����ʯ��.jpg");
	pmw[2][9].race = _T("����ʯ��"), pmw[2][9].ns = 4, pmw[2][9].clan = 2, pmw[2][9].pz = 1, pmw[2][9].pj = 10, pmw[2][9].tp = _T("res\\����ʯ��.jpg");
	pmw[2][10].race = _T("�ͱ�ħ����"), pmw[2][10].ns = 5, pmw[2][10].clan = 2, pmw[2][10].pz = 1, pmw[2][10].pj = 11, pmw[2][10].tp = _T("res\\�ͱ�ħ����.jpg");
	pmw[2][11].race = _T("����.���ְ���"), pmw[2][11].ns = 7, pmw[2][11].clan = 2, pmw[2][11].pz = 1, pmw[2][11].pj = 12, pmw[2][11].tp = _T("res\\����.���ְ���.jpg");
	pmw[2][12].race = _T("ʯ��.����"), pmw[2][12].ns = 4, pmw[2][12].clan = 2, pmw[2][12].pz = 1, pmw[2][12].pj = 13, pmw[2][12].tp = _T("res\\ʯ��.����.jpg");

	//��ҳ����
	mws[3].top = 3, mws[3].bs_pj = 3, mws[3].s_gj = 25, mws[3].s_fy = 15, mws[3].s_hp = 90, mws[3].s_sd = 20, mws[3].bjl = 20, mws[3].gdl = 20;
	pmw[3][1].race = _T("ѧ��"), pmw[3][1].ns = 3, pmw[3][1].clan = 3, pmw[3][1].pz = 3, pmw[3][1].pj = 3, pmw[3][1].tp = _T("res\\ѧ��.jpg");
	pmw[3][2].race = _T("ѧ��"), pmw[3][2].ns = 3, pmw[3][2].clan = 3, pmw[3][2].pz = 5, pmw[3][2].pj = 5, pmw[3][2].tp = _T("res\\ѧ��.jpg");
	pmw[3][3].race = _T("ѧ��"), pmw[3][3].ns = 3, pmw[3][3].clan = 3, pmw[3][3].pz = 7, pmw[3][3].pj = 7, pmw[3][3].tp = _T("res\\ѧ��.jpg");

	//���漦��
	mws[4].top = 12, mws[4].bs_pj = 4, mws[4].s_gj = 20, mws[4].s_fy = 6, mws[4].s_hp = 75, mws[4].s_sd = 12, mws[4].bjl = 15, mws[4].gdl = 5;
	pmw[4][1].race = _T("��ɫ����"), pmw[4][1].ns = 4, pmw[4][1].clan = 4, pmw[4][1].pz = 1, pmw[4][1].pj = 4, pmw[4][1].tp = _T("res\\��ɫ����.jpg");
	pmw[4][2].race = _T("��ɫ��"), pmw[4][2].ns = 3, pmw[4][2].clan = 4, pmw[4][2].pz = 1, pmw[4][2].pj = 5, pmw[4][2].tp = _T("res\\��ɫ��.jpg");
	pmw[4][3].race = _T("���漦"), pmw[4][3].ns = 3, pmw[4][3].clan = 4, pmw[4][3].pz = 1, pmw[4][3].pj = 6, pmw[4][3].tp = _T("res\\���漦.jpg");
	pmw[4][4].race = _T("��༦"), pmw[4][4].ns = 3, pmw[4][4].clan = 4, pmw[4][4].pz = 1, pmw[4][4].pj = 7, pmw[4][4].tp = _T("res\\��༦.jpg");
	pmw[4][5].race = _T("����"), pmw[4][5].ns = 3, pmw[4][5].clan = 4, pmw[4][5].pz = 1, pmw[4][5].pj = 8, pmw[4][5].tp = _T("res\\����.jpg");
	pmw[4][6].race = _T("����㼦"), pmw[4][6].ns = 4, pmw[4][6].clan = 4, pmw[4][6].pz = 1, pmw[4][6].pj = 9, pmw[4][6].tp = _T("res\\����㼦.jpg");
	pmw[4][7].race = _T("���׶�ս��"), pmw[4][7].ns = 5, pmw[4][7].clan = 4, pmw[4][7].pz = 1, pmw[4][7].pj = 10, pmw[4][7].tp = _T("res\\���׶�ս��.jpg");
	pmw[4][8].race = _T("����.���㶷��"), pmw[4][8].ns = 7, pmw[4][8].clan = 4, pmw[4][8].pz = 1, pmw[4][8].pj = 11, pmw[4][8].tp = _T("res\\����.���㶷��.jpg");
	pmw[4][9].race = _T("����.�ػ�ʼ�"), pmw[4][9].ns = 7, pmw[4][9].clan = 4, pmw[4][9].pz = 1, pmw[4][9].pj = 12, pmw[4][9].tp = _T("res\\����.�ػ�ʼ�.jpg");

	//�����
	mws[5].top = 14, mws[5].bs_pj = 3, mws[5].s_gj = 15, mws[5].s_fy = 12, mws[5].s_hp = 105, mws[5].s_sd = 14, mws[5].bjl = 12, mws[5].gdl = 8;
	pmw[5][1].race = _T("�׿����"), pmw[5][1].ns = 4, pmw[5][1].clan = 5, pmw[5][1].pz = 1, pmw[5][1].pj = 3, pmw[5][1].tp = _T("res\\�׿����.jpg");
	pmw[5][2].race = _T("�߼����"), pmw[5][2].ns = 4, pmw[5][2].clan = 5, pmw[5][2].pz = 1, pmw[5][2].pj = 4, pmw[5][2].tp = _T("res\\�߼����.jpg");
	pmw[5][3].race = _T("�߼׶����"), pmw[5][3].ns = 5, pmw[5][3].clan = 5, pmw[5][3].pz = 1, pmw[5][3].pj = 5, pmw[5][3].tp = _T("res\\�߼׶����.jpg");
	pmw[5][4].race = _T("����߶���"), pmw[5][4].ns = 5, pmw[5][4].clan = 5, pmw[5][4].pz = 1, pmw[5][4].pj = 6, pmw[5][4].tp = _T("res\\����߶���.jpg");
	pmw[5][5].race = _T("ǧ���϶���"), pmw[5][5].ns = 5, pmw[5][5].clan = 5, pmw[5][5].pz = 1, pmw[5][5].pj = 7, pmw[5][5].tp = _T("res\\ǧ���϶���.jpg");
	pmw[5][6].race = _T("�ж�������"), pmw[5][6].ns = 5, pmw[5][6].clan = 5, pmw[5][6].pz = 1, pmw[5][6].pj = 8, pmw[5][6].tp = _T("res\\�ж�������.jpg");
	pmw[5][7].race = _T("��������"), pmw[5][7].ns = 4, pmw[5][7].clan = 5, pmw[5][7].pz = 1, pmw[5][7].pj = 9, pmw[5][7].tp = _T("res\\��������.jpg");
	pmw[5][8].race = _T("�������"), pmw[5][8].ns = 4, pmw[5][8].clan = 5, pmw[5][8].pz = 1, pmw[5][8].pj = 10, pmw[5][8].tp = _T("res\\�������.jpg");
	pmw[5][9].race = _T("�����ϵ���"), pmw[5][9].ns = 5, pmw[5][9].clan = 5, pmw[5][9].pz = 1, pmw[5][9].pj = 11, pmw[5][9].tp = _T("res\\�����ϵ���.jpg");
	pmw[5][10].race = _T("����������"), pmw[5][10].ns = 5, pmw[5][10].clan = 5, pmw[5][10].pz = 1, pmw[5][10].pj = 12, pmw[5][10].tp = _T("res\\����������.jpg");
	pmw[5][11].race = _T("��Ԫ��������"), pmw[5][11].ns = 6, pmw[5][11].clan = 5, pmw[5][11].pz = 1, pmw[5][11].pj = 13, pmw[5][11].tp = _T("res\\��Ԫ��������.jpg");
	pmw[5][12].race = _T("���.��������"), pmw[5][12].ns = 6, pmw[5][12].clan = 5, pmw[5][12].pz = 1, pmw[5][12].pj = 14, pmw[5][12].tp = _T("res\\���.��������.jpg");

	//ˮԪ����
	mws[6].top = 9, mws[6].bs_pj = 1, mws[6].s_gj = 9, mws[6].s_fy = 9, mws[6].s_hp = 120, mws[6].s_sd = 15, mws[6].bjl = 3, mws[6].gdl = 12;
	pmw[6][1].race = _T("ˮ��"), pmw[6][1].ns = 3, pmw[6][1].clan = 6, pmw[6][1].pz = 1, pmw[6][1].pj = 1, pmw[6][1].tp = _T("res\\ˮ��.jpg");
	pmw[6][2].race = _T("ˮ��"), pmw[6][2].ns = 3, pmw[6][2].clan = 6, pmw[6][2].pz = 1, pmw[6][2].pj = 2, pmw[6][2].tp = _T("res\\ˮ��.jpg");
	pmw[6][3].race = _T("ˮ��ҹ��"), pmw[6][3].ns = 4, pmw[6][3].clan = 6, pmw[6][3].pz = 1, pmw[6][3].pj = 3, pmw[6][3].tp = _T("res\\ˮ��ҹ��.jpg");
	pmw[6][4].race = _T("ˮ����"), pmw[6][4].ns = 3, pmw[6][4].clan = 6, pmw[6][4].pz = 1, pmw[6][4].pj = 4, pmw[6][4].tp = _T("res\\ˮ����.jpg");
	pmw[6][5].race = _T("Ϫ������.ˮ��"), pmw[6][5].ns = 6, pmw[6][5].clan = 6, pmw[6][5].pz = 1, pmw[6][5].pj = 5, pmw[6][5].tp = _T("res\\Ϫ������.ˮ��.jpg");
	pmw[6][6].race = _T("��������.ˮ��"), pmw[6][6].ns = 6, pmw[6][6].clan = 6, pmw[6][6].pz = 1, pmw[6][6].pj = 6, pmw[6][6].tp = _T("res\\��������.ˮ��.jpg");
	pmw[6][7].race = _T("Ϫ�������"), pmw[6][7].ns = 5, pmw[6][7].clan = 6, pmw[6][7].pz = 1, pmw[6][7].pj = 7, pmw[6][7].tp = _T("res\\Ϫ�������.jpg");
	pmw[6][8].race = _T("���·��"), pmw[6][8].ns = 5, pmw[6][8].clan = 6, pmw[6][8].pz = 1, pmw[6][8].pj = 8, pmw[6][8].tp = _T("res\\���·��.jpg");
	pmw[6][9].race = _T("����������"), pmw[6][9].ns = 5, pmw[6][9].clan = 6, pmw[6][9].pz = 1, pmw[6][9].pj = 9, pmw[6][9].tp = _T("res\\����������.jpg");

}


void in_bok()		//¼���ٻ�֮��
{
	TCHAR ss[50];
	bks = GetPrivateProfileInt(_T("sy"), _T("bks"), 3, _T("data\\ZHZS.ini"));
	for (int i = 1; i <= bks; i++)
	{

		bool tf;	//��ҳ�Ƿ����ٻ���
		_stprintf(ss, _T("m%d"), i);
		tf = GetPrivateProfileInt(ss, _T("tf"), 0, _T("data\\ZHZS.ini"));
		if (!tf)
		{
			pt[i].race = 0, pt[i].clan = 0, pt[i].pz, pt[i].pj = 0, pt[i].pjz = 0, pt[i].dj = 0, pt[i].srd = 0, pt[i].ep = 0, pt[i].s_hp = 0, pt[i].s_gj = 0, pt[i].s_fy = 0, pt[i].s_zl = 0, pt[i].hlm = 0, pt[i].hls = 0, pt[i].hlz = 0, pt[i].s_sd = 0, pt[i].bjl = 0, pt[i].gdl = 0, pt[i].s_zl = 0;
			continue;
		}
		pt[i].race = GetPrivateProfileInt(ss, _T("race"), 0, _T("data\\ZHZS.ini"));
		pt[i].clan = GetPrivateProfileInt(ss, _T("clan"), 0, _T("data\\ZHZS.ini"));
		pt[i].pz = GetPrivateProfileInt(ss, _T("pz"), 0, _T("data\\ZHZS.ini"));
		pt[i].pjz = GetPrivateProfileInt(ss, _T("pjz"), 0, _T("data\\ZHZS.ini"));
		pt[i].dj = GetPrivateProfileInt(ss, _T("dj"), 0, _T("data\\ZHZS.ini"));
		pt[i].srd = GetPrivateProfileInt(ss, _T("srd"), 0, _T("data\\ZHZS.ini"));
		pt[i].ep = GetPrivateProfileInt(ss, _T("ep"), 0, _T("data\\ZHZS.ini"));

		if (bbh <= 1.3)pt[i].hlm = 6, pt[i].hls = 0, pt[i].hlz = 0;
		if (bbh >= 1.4)
		{
			pt[i].hlm = GetPrivateProfileInt(ss, _T("hlm"), 6, _T("data\\ZHZS.ini"));
			pt[i].hls = GetPrivateProfileInt(ss, _T("hls"), 0, _T("data\\ZHZS.ini"));
			pt[i].hlz = GetPrivateProfileInt(ss, _T("hlz"), 0, _T("data\\ZHZS.ini"));
			pt[i].rsh = 0;
		}
		if (bbh >= 1.5)
		{
			pt[i].rsh = GetPrivateProfileInt(ss, _T("rsh"), 0, _T("data\\ZHZS.ini"));
			if (pt[i].rsh != 0)zrbh[pt[i].rsh] = i;
		}
		pt[i].pj = pmw[pt[i].clan][pt[i].race].pj;
		pt[i].s_hp = mws[pt[i].clan].s_hp * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].s_gj = mws[pt[i].clan].s_gj * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].s_fy = mws[pt[i].clan].s_fy * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].s_sd = mws[pt[i].clan].s_sd * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].bjl = mws[pt[i].clan].bjl;
		pt[i].gdl = mws[pt[i].clan].gdl;
		pt[i].s_zl = pt[i].s_hp / 15 + pt[i].s_gj * 6 / 5 + pt[i].s_fy / 2;
	}
	//zrbh[13] >> ys;
	zrbh[13] = GetPrivateProfileInt(_T("els"), _T("dt"), 0, _T("data\\ZHZS.ini"));
	ys = GetPrivateProfileInt(_T("els"), _T("ys"), 0, _T("data\\ZHZS.ini"));
}

void open()			//��ʼҳ��
{
	loadimage(NULL, _T("res\\��ʼҳ��.jpg"), 1000, 600);
	settextcolor(RGB(0, 0, 0));
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)break;
	}
}

void main_page()	//��ҳ��
{
	TCHAR ss[50];
	//����
	outs();
	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);
	//��ͼ��
	IMAGE jpg;				//¼��ͼƬ��ָ��
	loadimage(&jpg, _T("res\\��ʼ.jpg"), 1000, 600);
	putimage(0, 0, 1000, 600, &jpg, 0, 0);

	//��ʯͼ��
	setfillcolor(RGB(60, 179, 113));
	fillrectangle(50, 10, 250, 40);
	settextcolor(RGB(0, 0, 0));
	settextstyle(26, 0, _T("����"));
	_stprintf(ss, _T("��ʯ��%d"), ys);
	outtextxy(52, 15, ss);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (880 <= m.x && m.x <= 980 && 450 <= m.y && m.y <= 570) bok(1, 1);
			if (740 <= m.x && m.x < 860 && 490 <= m.y && m.y <= 570) cc_page();
			if (620 <= m.x && m.x < 720 && 450 <= m.y && m.y <= 570) rl_page(1, 1, 1);
			if (510 <= m.x && m.x < 610 && 480 <= m.y && m.y <= 570) zr_page();
			if (390 <= m.x && m.x < 490 && 480 <= m.y && m.y <= 570) sc_page(1, 1);
			if (0 <= m.x && m.x <= 1000 && 0 <= m.y && m.y <= 500) ele(now_where);
		}
	}

}

void bok(int k, int f)		//�ٻ�֮��ҳ��
{
	while (1)
	{
		//����
		outs();

		//����
		for (int i = 1; i <= bks; i++)
			for (int j = i + 1; j <= bks; j++)
				if (pt[i].rsh != 0 && pt[j].rsh != 0 && pt[i].rsh > pt[j].rsh)
					swap(pt[i], pt[j]);
				else if (pt[i].rsh == 0 && pt[j].rsh != 0)
					swap(pt[i], pt[j]);

		//����
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(0, i, 1000, i);

		//�ٻ���ͼ
		IMAGE jpg;				//¼��ͼƬ��ָ��
		loadimage(&jpg, pmw[pt[k].clan][pt[k].race].tp, 400, 500);
		putimage(30, 20, 430, 520, &jpg, 0, 0);

		//�Ƿ�����
		if (pt[k].rsh != 0)
		{
			loadimage(&jpg, _T("res\\������.jpg"), 200, 120);
			putimage(680, 10, 200, 120, &jpg, 0, 0);
		}

		//��ǰҳ��
		TCHAR ss[50];
		_stprintf(ss, _T("page %d"), k);
		settextstyle(25, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, 540, ss);

		//��һҳ/��һҳ
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(180, 540, 280, 570);
		settextstyle(16, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(182, 545, _T("��һҳ"));
		outtextxy(232, 545, _T("��һҳ"));
		if (k <= 1)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(180, 540, 230, 570);
		}
		if (k >= bks)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(230, 540, 280, 570);
		}
		setlinecolor(RGB(0, 0, 0));
		line(230, 541, 230, 569);

		//������ҳ��ͼ��
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(900, 530, 980, 580);
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(910, 540, _T("����"));

		//�������
		setfillcolor(RGB(210, 105, 30));
		for (int i = 1; i <= 6; i++)
			fillrectangle(890, 10 + (i - 1) * 60, 990, 70 + (i - 1) * 60);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(890, 10 + (f - 1) * 60, 990, 70 + (f - 1) * 60);
		setfillcolor(RGB(192, 192, 192));
		fillrectangle(890, 250, 990, 310);
		fillrectangle(890, 310, 990, 370);
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(910, 25, _T("����"));
		outtextxy(910, 85, _T("����"));
		outtextxy(910, 145, _T("����"));
		outtextxy(910, 205, _T("����"));
		outtextxy(910, 265, _T("����"));
		outtextxy(910, 325, _T("�"));

		if (f == 1)
		{
			TCHAR ss[50];
			settextstyle(32, 0, _T("����"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(500, 60, _T("��:"));
			outtextxy(545, 60, pmw[pt[k].clan][pt[k].race].race);
			outtextxy(500, 100, _T("��:"));
			outtextxy(545, 100, CLAN[pt[k].clan]);
			outtextxy(500, 140, _T("Ʒ��:"));
			outtextxy(580, 140, PJ[pt[k].pj]);
			outtextxy(690, 140, _T("Ʒ��:"));
			outtextxy(770, 140, PZ[pt[k].pz]);
			_stprintf(ss, _T("�ȼ�:%d"), pt[k].dj);
			outtextxy(500, 180, ss);
			_stprintf(ss, _T("����:%d"), pt[k].srd);
			outtextxy(620, 180, ss);
			_stprintf(ss, _T("����:%d"), pt[k].s_hp);
			outtextxy(500, 250, ss);
			_stprintf(ss, _T("����:%d"), pt[k].s_gj);
			outtextxy(500, 290, ss);
			_stprintf(ss, _T("����:%d"), pt[k].s_fy);
			outtextxy(500, 330, ss);
			_stprintf(ss, _T("�ٶ�:%d"), pt[k].s_sd);
			outtextxy(670, 250, ss);
			_stprintf(ss, _T("������:%d %%"), pt[k].bjl);
			outtextxy(670, 290, ss);
			_stprintf(ss, _T("����:%d %%"), pt[k].gdl);
			outtextxy(670, 330, ss);
			settextstyle(32, 0, _T("����"));
			settextcolor(RGB(255, 0, 0));
			_stprintf(ss, _T("ս��:%d"), pt[k].s_zl);
			outtextxy(500, 460, ss);
		}
		if (f == 2 && pt[k].clan != 0) sg_page(k);
		if (f == 3 && pt[k].clan != 0) rh_page(k);
		if (f == 4 && pt[k].clan != 0) hl_page(k);

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//������ҳ��
					main_page();
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//��һҳ
				{
					k--;
					break;
				}
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//��һҳ
				{
					k++;
					break;
				}
				bool rl = 0;
				for (int i = 1; i <= 4; i++)		//��������ѡ��
					if (i != f && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
					{
						f = i;
						rl = 1;
						break;
					}
				if (rl)break;
			}
		}
	}
}

void ele(int k)		//̽��
{
	//����
	outs();

	//����λ��
	now_where = k;

	//����
	IMAGE jpg;				//¼��ͼƬ��ָ��
	loadimage(&jpg, place[k].tp, 1000, 600);
	putimage(0, 0, 1000, 600, &jpg, 0, 0);

	//��ҳ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(600, 520, 700, 570);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(620, 530, _T("����"));

	//��ͼ
	loadimage(&jpg, _T("res\\��ͼ.jpg"), 150, 120);
	putimage(800, 20, 150, 120, &jpg, 0, 0);
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, _T("����"));
	outtextxy(860, 150, _T("��ͼ"));

	//��ǰ�ɼ��ص�
	vector<int> x;
	for (int i = 0; i < mp[k].size(); i++)
		if (random(1, 100) <= place[mp[k][i]].gl)
			x.push_back(mp[k][i]);

	//�ص�ͼ��
	settextcolor(RGB(0, 0, 0));
	settextstyle(32, 0, _T("����"));
	outtextxy(50, 30, place[k].name);
	for (int i = 0; i < x.size(); i++)
	{
		if (place[x[i]].gl == 100) setfillcolor(RGB(0, 255, 0));
		else setfillcolor(RGB(147, 112, 219));
		fillrectangle(100 + 120 * i, 80, 200 + 120 * i, 130);
		settextstyle(80 / place[x[i]].ns, 40 / place[x[i]].ns, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(105 + 120 * i, 90, place[x[i]].name);
	}

	//ս��ͼ��
	setfillcolor(RGB(210, 105, 30));
	fillrectangle(100, 200, 200, 250);
	settextstyle(30, 0, _T("����"));
	outtextxy(120, 210, _T("ս��"));

	//ˢ��ͼ��
	setfillcolor(RGB(210, 105, 30));
	fillrectangle(230, 200, 330, 250);
	settextstyle(30, 0, _T("����"));
	outtextxy(250, 210, _T("ˢ��"));

	//Ұ��ħ��ͼ��
	for (int i = 1; i <= ceil((double)sob[k].size() / (double)7); i++)
	{
		for (int j = 0; j < min(7, sob[k].size() - (i - 1) * 7); j++)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(100 + 120 * j, 200 + i * 80, 200 + 120 * j, 260 + i * 80);
			settextstyle(80 / pmw[sob[k][(i - 1) * 7 + j].clan][sob[k][(i - 1) * 7 + j].race].ns, 40 / pmw[sob[k][(i - 1) * 7 + j].clan][sob[k][(i - 1) * 7 + j].race].ns, _T("����"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(105 + 120 * j, 220 + i * 80, pmw[sob[k][(i - 1) * 7 + j].clan][sob[k][(i - 1) * 7 + j].race].race);
		}
	}

	//ѡ��
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (600 <= m.x && m.x <= 700 && 520 <= m.y && m.y <= 570)
				main_page();

			if (800 <= m.x && m.x <= 950 && 20 <= m.y && m.y <= 140)
			{
				map_page();
				ele(k);
			}

			if (230 <= m.x && m.x <= 330 && 200 <= m.y && m.y <= 250)
			{
				cl_ts(k);
				ele(k);
			}

			for (int i = 0; i < x.size(); i++)
				if (100 + 120 * i <= m.x && m.x <= 200 + 120 * i && 80 <= m.y && m.y <= 130)
					ele(x[i]);

			//����
			for (int i = 1; i <= ceil((double)sob[k].size() / (double)7); i++)
				for (int j = 0; j < min(7, sob[k].size() - (i - 1) * 7); j++)
					if (100 + 120 * j <= m.x && m.x <= 200 + 120 * j && 200 + 80 * i <= m.y && m.y <= 260 + 80 * i)
						if (lor_mw(k, sob[k][j + (i - 1) * 7]))
						{
							TBOC R[3];
							R[1] = sob[k][j + (i - 1) * 7];
							if (!cs_page(1, PvE(R, 1, 1)))
							{
								//ħ�������Ʒ
								mw_lt(sob[k][j + (i - 1) * 7].clan, sob[k][j + (i - 1) * 7].race, sob[k][j + (i - 1) * 7].pz, sob[k][j + (i - 1) * 7].dj);

								//����ħ��
								vector<TBOC> x;
								for (int ii = 0; ii < sob[k].size(); ii++)
									if (ii != j + (i - 1) * 7)
										x.push_back(sob[k][ii]);
								sob[k].clear();
								for (int ks = 0; ks < x.size(); ks++)sob[k].push_back(x[ks]);
							}
							ele(k);
						}
						else ele(k);

			//����Ծ�
			if (100 <= m.x && m.x <= 200 && 200 <= m.y && m.y <= 250 && sob[k].size() > 0)
			{
				TBOC R[30];
				for (int i = 1; i <= min(6, sob[k].size()); i++)
					R[i] = sob[k][i - 1];
				if (!cs_page(1, PvE(R, min(6, sob[k].size()), 6)))
				{
					//ħ�������Ʒ
					for (int i = 1; i <= min(6, sob[k].size()); i++)
						mw_lt(sob[k][i - 1].clan, sob[k][i - 1].race, sob[k][i - 1].pz, sob[k][i - 1].dj);

					//����ħ��
					vector<TBOC> x;
					for (int i = 6; i < sob[k].size(); i++)
						x.push_back(sob[k][i]);
					sob[k].clear();
					for (int ks = 0; ks < x.size(); ks++)sob[k].push_back(x[ks]);
				}
				ele(k);
			}
		}
	}
}

void cl_map()		//��ʼ��̽��֮·
{
	tsl = 36;
	place[1].name = _T("��԰"), place[1].ns = 3, place[1].gl = 100, place[1].tp = _T("res\\��԰.jpg");
	place[2].name = _T("���ж���"), place[2].ns = 4, place[2].gl = 100, place[2].tp = _T("res\\���ж���.jpg");
	place[3].name = _T("�����Ͻ�"), place[3].ns = 4, place[3].gl = 100, place[3].tp = _T("res\\�����Ͻ�.jpg");
	place[4].name = _T("��������"), place[4].ns = 4, place[4].gl = 100, place[4].tp = _T("res\\��������.jpg");
	place[5].name = _T("���б���"), place[5].ns = 4, place[5].gl = 100, place[5].tp = _T("res\\���б���.jpg");
	place[6].name = _T("���ľ�"), place[6].ns = 3, place[6].gl = 100, place[6].tp = _T("res\\���ľ�.jpg");
	place[7].name = _T("����"), place[7].ns = 3, place[7].gl = 15, place[7].tp = _T("res\\����.jpg");
	place[8].name = _T("ͭ��ɽ��"), place[8].ns = 4, place[8].gl = 100, place[8].tp = _T("res\\ͭ��ɽ��.jpg");
	place[9].name = _T("ͭ��ɽ��ɽ��"), place[9].ns = 6, place[9].gl = 100, place[9].tp = _T("res\\ͭ��ɽ��ɽ��.jpg");
	place[10].name = _T("��ͷɽ��"), place[10].ns = 4, place[10].gl = 10, place[10].tp = _T("res\\��ͷɽ��.jpg");
	place[11].name = _T("����ɽ"), place[11].ns = 3, place[11].gl = 100, place[11].tp = _T("res\\����ɽ.jpg");
	place[12].name = _T("��ʯ��"), place[12].ns = 3, place[12].gl = 100, place[12].tp = _T("res\\��ʯ��.jpg");
	place[13].name = _T("���ҽ���"), place[13].ns = 4, place[13].gl = 100, place[13].tp = _T("res\\���ҽ���.jpg");
	place[14].name = _T("������ɽ"), place[14].ns = 4, place[14].gl = 100, place[14].tp = _T("res\\������ɽ.jpg");
	place[15].name = _T("������ɽ��"), place[15].ns = 5, place[15].gl = 100, place[15].tp = _T("res\\������ɽ��.jpg");
	place[16].name = _T("������ָɽ"), place[16].ns = 5, place[16].gl = 10, place[16].tp = _T("res\\������ָɽ.jpg");
	place[17].name = _T("��ϣ��"), place[17].ns = 3, place[17].gl = 100, place[17].tp = _T("res\\��ϣ��.jpg");
	place[18].name = _T("�ݺ�"), place[18].ns = 3, place[18].gl = 100, place[18].tp = _T("res\\�ݺ�.jpg");
	place[19].name = _T("����"), place[19].ns = 3, place[19].gl = 100, place[19].tp = _T("res\\����.jpg");
	place[20].name = _T("«έ��"), place[20].ns = 3, place[20].gl = 100, place[20].tp = _T("res\\«έ��.jpg");
	place[21].name = _T("«����"), place[21].ns = 3, place[21].gl = 5, place[21].tp = _T("res\\«����.jpg");
	place[22].name = _T("ʮ������"), place[22].ns = 4, place[22].gl = 100, place[22].tp = _T("res\\ʮ������.jpg");
	place[23].name = _T("��Ϫ"), place[23].ns = 3, place[23].gl = 15, place[23].tp = _T("res\\��Ϫ.jpg");
	place[24].name = _T("���׽�����"), place[24].ns = 5, place[24].gl = 100, place[24].tp = _T("res\\���׽�����.jpg");
	place[25].name = _T("�����ܶ�"), place[25].ns = 4, place[25].gl = 10, place[25].tp = _T("res\\�����ܶ�.jpg");
	place[26].name = _T("�ܵ�"), place[26].ns = 3, place[26].gl = 100, place[26].tp = _T("res\\�ܵ�.jpg");
	place[27].name = _T("�����"), place[27].ns = 3, place[27].gl = 30, place[27].tp = _T("res\\�����.jpg");
	place[28].name = _T("��Ӱ��"), place[28].ns = 3, place[28].gl = 25, place[28].tp = _T("res\\��Ӱ��.jpg");
	place[29].name = _T("���ֵ�"), place[29].ns = 3, place[29].gl = 20, place[29].tp = _T("res\\���ֵ�.jpg");
	place[30].name = _T("����ɽ"), place[30].ns = 3, place[30].gl = 100, place[30].tp = _T("res\\����ɽ.jpg");
	place[31].name = _T("˪ѩ��"), place[31].ns = 3, place[31].gl = 100, place[31].tp = _T("res\\˪ѩ��.jpg");
	place[32].name = _T("�����"), place[32].ns = 3, place[32].gl = 10, place[32].tp = _T("res\\�����.jpg");
	place[33].name = _T("����ʥɽ"), place[33].ns = 4, place[33].gl = 100, place[33].tp = _T("res\\����ʥɽ.jpg");
	place[34].name = _T("�����˫��"), place[34].ns = 5, place[34].gl = 10, place[34].tp = _T("res\\�����˫��.jpg");
	place[35].name = _T("�ҽ�ӿԴ��"), place[35].ns = 5, place[35].gl = 15, place[35].tp = _T("res\\�ҽ�ӿԴ��.jpg");
	place[36].name = _T("��ͷɽ��"), place[36].ns = 4, place[36].gl = 100, place[36].tp = _T("res\\��ͷɽ��.jpg");

	KMW x;

	x.clan = 1, x.rl = 1, x.rh = 1, x.pzl = 1, x.pzh = 1, x.djl = 0, x.djh = 0, x.srl = 0, x.srh = 0, kmw[1].push_back(x);//��԰

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[2].push_back(x);//����
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[2].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[2].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[3].push_back(x);//�Ͻ�
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[3].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[3].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[4].push_back(x);//����
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[4].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[4].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[5].push_back(x);//����
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[5].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[5].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[6].push_back(x);//���ľ�
	x.clan = 5, x.rl = 3, x.rh = 6, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[6].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[7].push_back(x);//����
	x.clan = 3, x.rl = 1, x.rh = 1, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[7].push_back(x);
	x.clan = 5, x.rl = 3, x.rh = 6, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[7].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[8].push_back(x);//ͭ��ɽ��
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[8].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[9].push_back(x);//ͭ��ɽ��ɽ��
	x.clan = 2, x.rl = 4, x.rh = 8, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[9].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[10].push_back(x);//��ͷɽ��
	x.clan = 2, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[10].push_back(x);
	x.clan = 5, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[10].push_back(x);

	x.clan = 1, x.rl = 4, x.rh = 6, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[11].push_back(x);//����ɽ
	x.clan = 2, x.rl = 1, x.rh = 4, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[11].push_back(x);

	x.clan = 1, x.rl = 4, x.rh = 6, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[12].push_back(x);//��ʯ��
	x.clan = 2, x.rl = 2, x.rh = 6, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[12].push_back(x);

	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[13].push_back(x);//���ҽ���
	x.clan = 4, x.rl = 1, x.rh = 4, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[13].push_back(x);

	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[14].push_back(x);//������ɽ
	x.clan = 4, x.rl = 3, x.rh = 6, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[14].push_back(x);

	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[15].push_back(x);//������ɽ��

	x.clan = 1, x.rl = 8, x.rh = 14, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);//������ָɽ
	x.clan = 2, x.rl = 8, x.rh = 12, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);
	x.clan = 3, x.rl = 2, x.rh = 2, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);
	x.clan = 4, x.rl = 6, x.rh = 9, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[17].push_back(x);//��ϣ��
	x.clan = 4, x.rl = 2, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[17].push_back(x);
	x.clan = 6, x.rl = 1, x.rh = 6, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[17].push_back(x);

	x.clan = 1, x.rl = 5, x.rh = 8, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[18].push_back(x);//�ݺ�
	x.clan = 6, x.rl = 3, x.rh = 8, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[18].push_back(x);

	x.clan = 6, x.rl = 4, x.rh = 8, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[19].push_back(x);//����

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[20].push_back(x);//«έ��

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[21].push_back(x);//«����
	x.clan = 6, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[21].push_back(x);

	x.clan = 1, x.rl = 4, x.rh = 9, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[22].push_back(x);//ʮ������

	x.clan = 6, x.rl = 5, x.rh = 9, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[23].push_back(x);//��Ϫ

	x.clan = 6, x.rl = 6, x.rh = 9, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[24].push_back(x);//���׽�����

	x.clan = 3, x.rl = 1, x.rh = 1, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[25].push_back(x);//�����ܶ�
	x.clan = 5, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[25].push_back(x);
	x.clan = 6, x.rl = 4, x.rh = 9, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[25].push_back(x);

	x.clan = 2, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[26].push_back(x);//�ܵ�

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[27].push_back(x);//�����
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[27].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[28].push_back(x);//��Ӱ��
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[28].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 8, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[29].push_back(x);//���ֵ�
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[29].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[30].push_back(x);//����ɽ
	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[30].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[31].push_back(x);//˪ѩ��

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[32].push_back(x);//�����

	x.clan = 2, x.rl = 5, x.rh = 6, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[33].push_back(x);//����ʥɽ

	x.clan = 1, x.rl = 10, x.rh = 16, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);//�����˫��
	x.clan = 2, x.rl = 5, x.rh = 8, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);
	x.clan = 3, x.rl = 3, x.rh = 3, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);
	x.clan = 4, x.rl = 5, x.rh = 8, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);

	x.clan = 2, x.rl = 5, x.rh = 7, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[35].push_back(x);//�ҽ�ӿԴ��
	x.clan = 4, x.rl = 3, x.rh = 6, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[35].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 8, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[36].push_back(x);//��ͷɽ��
	x.clan = 4, x.rl = 1, x.rh = 3, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[36].push_back(x);


	mp[1].push_back(2);			//��->���ж���
	mp[1].push_back(3);			//��->�����Ͻ�
	mp[1].push_back(4);			//��->��������
	mp[1].push_back(5);			//��->���б���

	mp[2].push_back(1);			//���ж���->��
	mp[2].push_back(27);		//���ж���->�����

	mp[3].push_back(1);			//�����Ͻ�->��
	mp[3].push_back(11);		//�����Ͻ�->����ɽ

	mp[4].push_back(1);			//��������->��
	mp[4].push_back(17);		//��������->��ϣ��

	mp[5].push_back(1);			//���б���->��
	mp[5].push_back(6);			//���б���->���ľ�
	mp[5].push_back(8);			//���б���->ͭ��ɽ��

	mp[6].push_back(5);			//���ľ�->���б���
	mp[6].push_back(7);			//���ľ�->����
	mp[6].push_back(8);			//���ľ�->ͭ��ɽ��
	mp[6].push_back(29);		//���ľ�->���ֵ�

	mp[7].push_back(6);			//����->���ľ�
	mp[7].push_back(23);		//����->��Ϫ

	mp[8].push_back(5);			//ͭ��ɽ��->���б���
	mp[8].push_back(6);			//ͭ��ɽ��->���ľ�
	mp[8].push_back(9);			//ͭ��ɽ��->ͭ��ɽ��ɽ��

	mp[9].push_back(8);			//ͭ��ɽ��ɽ��->ͭ��ɽ��
	mp[9].push_back(36);		//ͭ��ɽ��ɽ��->��ͷɽ��

	mp[10].push_back(36);		//��ͷɽ��->��ͷɽ��

	mp[11].push_back(3);		//����ɽ->�����Ͻ�
	mp[11].push_back(12);		//����ɽ->��ʯ��
	mp[11].push_back(15);		//����ɽ->������ɽ��

	mp[12].push_back(11);		//��ʯ��->����ɽ
	mp[12].push_back(13);		//��ʯ��->���ҽ���
	mp[12].push_back(15);		//��ʯ��->������ɽ��
	mp[12].push_back(16);		//��ʯ��->������ָɽ

	mp[13].push_back(12);		//���ҽ���->��ʯ��
	mp[13].push_back(14);		//���ҽ���->������ɽ��

	mp[14].push_back(13);		//������ɽ��->���ҽ���
	mp[14].push_back(15);		//������ɽ��->������ɽ
	mp[14].push_back(35);		//������ɽ��->�ҽ�ӿԴ��

	mp[15].push_back(11);		//������ɽ->����ɽ
	mp[15].push_back(12);		//������ɽ->��ʯ��
	mp[15].push_back(14);		//������ɽ->������ɽ��

	mp[16].push_back(12);		//������ָɽ->��ʯ��
	mp[16].push_back(26);		//������ָɽ->�ܵ�

	mp[17].push_back(4);		//��ϣ��->����
	mp[17].push_back(18);		//��ϣ��->�ݺ�
	mp[17].push_back(19);		//��ϣ��->����
	mp[17].push_back(20);		//��ϣ��->«έ��

	mp[18].push_back(17);		//�ݺ�->��ϣ��
	mp[18].push_back(19);		//�ݺ�->����
	mp[18].push_back(20);		//�ݺ�->«έ��

	mp[19].push_back(17);		//����->��ϣ��
	mp[19].push_back(18);		//����->�ݺ�
	mp[19].push_back(20);		//����->«έ��
	mp[19].push_back(24);		//����->���׽�����

	mp[20].push_back(17);		//«έ��->��ϣ��
	mp[20].push_back(18);		//«έ��->�ݺ�
	mp[20].push_back(19);		//«έ��->����
	mp[20].push_back(21);		//«έ��->«����

	mp[21].push_back(20);		//«����->«έ��
	mp[21].push_back(22);		//«����->ʮ������

	mp[22].push_back(21);		//ʮ������->«����
	mp[22].push_back(23);		//ʮ������->��Ϫ

	mp[23].push_back(7);		//��Ϫ->����
	mp[23].push_back(22);		//��Ϫ->ʮ������

	mp[24].push_back(19);		//���׽�����->����
	mp[24].push_back(25);		//���׽�����->�����ܶ�

	mp[25].push_back(24);		//�����ܶ�->���׽�����
	mp[25].push_back(26);		//�����ܶ�->�ܵ�

	mp[26].push_back(16);		//�ܵ�->������ָɽ
	mp[26].push_back(25);		//�ܵ�->�����ܶ�

	mp[27].push_back(2);		//�����->����
	mp[27].push_back(28);		//�����->��Ӱ��
	mp[27].push_back(30);		//�����->����ɽ

	mp[28].push_back(27);		//��Ӱ��->�����
	mp[28].push_back(29);		//��Ӱ��->���ֵ�
	mp[28].push_back(30);		//��Ӱ��->����ɽ

	mp[29].push_back(6);		//���ֵ�->���ľ�
	mp[29].push_back(28);		//���ֵ�->��Ӱ��

	mp[30].push_back(27);		//����ɽ->�����
	mp[30].push_back(28);		//����ɽ->��Ӱ��
	mp[30].push_back(31);		//����ɽ->˪ѩ��

	mp[31].push_back(30);		//˪ѩ��->����ɽ
	mp[31].push_back(32);		//˪ѩ��->�����

	mp[32].push_back(31);		//�����->˪ѩ��
	mp[32].push_back(33);		//�����->����ʥɽ

	mp[33].push_back(32);		//����ʥɽ->�����
	mp[33].push_back(34);		//����ʥɽ->�����˫��

	mp[34].push_back(33);		//�����˫��->����ʥɽ
	mp[34].push_back(35);		//�����˫��->�ҽ�ӿԴ��

	mp[35].push_back(14);		//�ҽ�ӿԴ��->������ɽ
	mp[35].push_back(34);		//�ҽ�ӿԴ��->�����˫��

	mp[36].push_back(9);		//ͭ��ɽ��ɽ��
	mp[36].push_back(10);		//��ͷɽ��

}

void cl_ts(int z)				//ˢ��̽��֮·ħ��
{
	int f = bks;
	for (int i = 1; i <= f; i++)
	{
		if (sob[z].size() >= 21)break;
		TBOC x;
		if (kmw[z].size() <= 0)continue;
		int k = random(0, kmw[z].size() - 1);
		x.clan = kmw[z][k].clan;
		x.race = random(kmw[z][k].rl, kmw[z][k].rh);
		x.pz = random(kmw[z][k].pzl, kmw[z][k].pzh);
		x.dj = random(kmw[z][k].djl, kmw[z][k].djh);
		x.srd = random(kmw[z][k].srl, kmw[z][k].srh);
		x.pj = pmw[x.clan][x.race].pj;
		x.s_hp = mws[x.clan].s_hp * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
		x.s_gj = mws[x.clan].s_gj * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
		x.s_fy = mws[x.clan].s_fy * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
		x.s_sd = mws[x.clan].s_sd * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
		x.bjl = mws[x.clan].bjl;
		x.gdl = mws[x.clan].gdl;
		x.s_zl = x.s_hp / 15 + x.s_gj * 6 / 5 + x.s_fy / 2;
		sob[z].push_back(x);
	}

	//����
	outs();
}

bool PvE(TBOC E[], int tot, int tos)		//��ս����
{
	int r = random(0, 1);		//�ж�����
	int pd;						//�жϽ��
	int xxs = 0;				//��Ϣ����
	int f1 = 1, f2 = 1;			//�ҷ����з���ֻ���λ��
	int hhs = 0;					//�غ���
	TCHAR ss[50];
	TBOC P[30];
	if (tos == 1)P[1] = pt[zrbh[13]];
	else
	{
		vector<TBOC> x;
		for (int i = 1; i <= tos; i++)
			if (pt[zrbh[i]].clan != 0)
				x.push_back(pt[zrbh[i]]);
		for (int i = 1; i <= x.size(); i++)
			P[i] = x[i - 1];
		tos = x.size();
	}

	if (r == 0)
		while (++hhs)
		{
			if (hhs > 50)return 1;

			for (int ks = 0; ks <= 600; ks++)
				line(0, ks, 1000, ks);
			settextcolor(RGB(0, 0, 0));
			settextstyle(30, 0, _T("����"));
			_stprintf(ss, _T("�� %d �غ�"), hhs);
			outtextxy(400, 5, ss);
			xxs = 0;

			//���
			for (int i = f1; i <= tos; i++)
			{
				bool bjrl = 0, gdrl = 0, sbrl = 0;
				int gj = random(P[i].s_gj, P[i].s_gj * 6 / 5);
				int fy = random(E[f2].s_fy / 2, E[f2].s_fy * 7 / 10);

				if (random(1, 100) <= P[i].bjl)
				{
					gj *= 2;
					fy *= 2;
					bjrl = 1;
				}
				if (random(1, 100) <= E[f2].gdl)
				{
					gj /= 2;
					fy /= 2;
					gdrl = 1;
				}
				if (random(1, P[i].s_sd + E[f2].s_sd) <= E[f2].s_sd / 5) sbrl = 1;

				if (sbrl == 0)E[f2].s_hp = max(0, (E[f2].s_hp - max(1, gj - fy)));
				if (E[f2].s_hp == 0)f2++;
				if (f2 > tot)return 0;

				xxs %= 15;
				if (xxs == 0)
				{
					for (int ks = 0; ks <= 600; ks++)
						line(0, ks, 1000, ks);
					settextcolor(RGB(0, 0, 0));
					settextstyle(30, 0, _T("����"));
					_stprintf(ss, _T("�� %d �غ�"), hhs);
					outtextxy(400, 5, ss);
				}
				settextcolor(RGB(0, 0, 255));
				settextstyle(16, 0, _T("����"));
				if (sbrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���з�������"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("�ҷ�%s�����з�%s������˺�%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���ҷ�����������˺�%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���з��񵲣�����˺�%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}

				Sleep(300);
			}

			//����
			for (int i = f2; i <= tot; i++)
			{
				bool bjrl = 0, gdrl = 0, sbrl = 0;
				int gj = random(E[i].s_gj, E[i].s_gj * 6 / 5);
				int fy = random(P[f1].s_fy / 2, P[f1].s_fy * 7 / 10);

				if (random(1, 100) <= E[i].bjl)
				{
					gj *= 2;
					fy *= 2;
					bjrl = 1;
				}
				if (random(1, 100) <= P[f1].gdl)
				{
					gj /= 2;
					fy /= 2;
					gdrl = 1;
				}
				if (random(1, E[i].s_sd + P[f1].s_sd) <= P[f1].s_sd / 5) sbrl = 1;

				if (sbrl == 0)P[f1].s_hp = max(0, (P[f1].s_hp - max(1, gj - fy)));
				if (P[f1].s_hp == 0)f1++;
				if (f1 > tos)return 1;

				xxs %= 15;
				if (xxs == 0)
				{
					for (int ks = 0; ks <= 600; ks++)
						line(0, ks, 1000, ks);
					settextcolor(RGB(0, 0, 0));
					settextstyle(30, 0, _T("����"));
					_stprintf(ss, _T("�� %d �غ�"), hhs);
					outtextxy(400, 5, ss);
				}

				settextcolor(RGB(255, 0, 0));
				settextstyle(16, 0, _T("����"));
				if (sbrl == 1)
					_stprintf(ss, _T("�з�%s�����ҷ�%s���з�������"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("�з�%s�����ҷ�%s������˺�%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���ҷ�����������˺�%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���з��񵲣�����˺�%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}

				Sleep(300);
			}
		}
	if (r == 1)
		while (++hhs)
		{
			if (hhs > 50)return 1;
			for (int ks = 0; ks <= 600; ks++)
				line(0, ks, 1000, ks);
			settextcolor(RGB(0, 0, 0));
			settextstyle(30, 0, _T("����"));
			_stprintf(ss, _T("�� %d �غ�"), hhs);
			outtextxy(400, 5, ss);
			xxs = 0;

			//����
			for (int i = f2; i <= tot; i++)
			{
				bool bjrl = 0, gdrl = 0, sbrl = 0;
				int gj = random(E[i].s_gj, E[i].s_gj * 6 / 5);
				int fy = random(P[f1].s_fy / 2, P[f1].s_fy * 7 / 10);
				if (random(1, 100) <= E[i].bjl)
				{
					gj *= 2;
					fy *= 2;
					bjrl = 1;
				}
				if (random(1, 100) <= P[f1].gdl)
				{
					gj /= 2;
					fy /= 2;
					gdrl = 1;
				}
				if (random(1, E[i].s_sd + P[f1].s_sd) <= P[f1].s_sd / 5) sbrl = 1;
				if (sbrl == 0)P[f1].s_hp = max(0, (P[f1].s_hp - max(1, gj - fy)));
				if (P[f1].s_hp == 0)f1++;
				if (f1 > tos)return 1;
				xxs %= 15;
				if (xxs == 0)
				{
					for (int ks = 0; ks <= 600; ks++)
						line(0, ks, 1000, ks);
					settextcolor(RGB(0, 0, 0));
					settextstyle(30, 0, _T("����"));
					_stprintf(ss, _T("�� %d �غ�"), hhs);
					outtextxy(400, 5, ss);
				}
				settextcolor(RGB(255, 0, 0));
				settextstyle(16, 0, _T("����"));
				if (sbrl == 1)
					_stprintf(ss, _T("�з�%s�����ҷ�%s���з�������"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("�з�%s�����ҷ�%s������˺�%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���ҷ�����������˺�%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���з��񵲣�����˺�%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}
				Sleep(300);
			}

			//���
			for (int i = f1; i <= tos; i++)
			{
				bool bjrl = 0, gdrl = 0, sbrl = 0;
				int gj = random(P[i].s_gj, P[i].s_gj * 6 / 5);
				int fy = random(E[f2].s_fy / 2, E[f2].s_fy * 7 / 10);
				if (random(1, 100) <= P[i].bjl)
				{
					gj *= 2;
					fy *= 2;
					bjrl = 1;
				}
				if (random(1, 100) <= E[f2].gdl)
				{
					gj /= 2;
					fy /= 2;
					gdrl = 1;
				}
				if (random(1, P[i].s_sd + E[f2].s_sd) <= E[f2].s_sd / 5) sbrl = 1;
				if (sbrl == 0)E[f2].s_hp = max(0, (E[f2].s_hp - max(1, gj - fy)));
				if (E[f2].s_hp == 0)f2++;
				if (f2 > tot)return 0;
				xxs %= 15;
				if (xxs == 0)
				{
					for (int ks = 0; ks <= 600; ks++)
						line(0, ks, 1000, ks);
					settextcolor(RGB(0, 0, 0));
					settextstyle(30, 0, _T("����"));
					_stprintf(ss, _T("�� %d �غ�"), hhs);
					outtextxy(400, 5, ss);
				}
				settextcolor(RGB(0, 0, 255));
				settextstyle(16, 0, _T("����"));
				if (sbrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���з�������"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("�ҷ�%s�����з�%s������˺�%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���ҷ�����������˺�%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("�ҷ�%s�����з�%s���з��񵲣�����˺�%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("����"));
					_stprintf(ss, _T("%s��%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}
				Sleep(300);
			}
		}
}

bool cs_page(int z, bool r)		//����ҳ��
{
	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//�ж����
	if (z == 1)		//����ս��
	{
		settextcolor(RGB(0, 0, 0));
		settextstyle(200, 0, _T("����"));
		if (r) outtextxy(100, 200, _T("ս��ʧ��"));
		else outtextxy(100, 200, _T("ս��ʤ��"));
		Sleep(1500);
	}
	if (z == 2)
	{
		settextcolor(RGB(0, 0, 0));
		settextstyle(200, 0, _T("����"));
		if (r) outtextxy(100, 200, _T("ʹ�óɹ�"));
		else outtextxy(100, 200, _T("ʹ��ʧ��"));
		Sleep(1500);
	}
	//����
	return r;
}

void cc_page()			//�ֿ�ҳ��
{
	int mps, ps = 1;
	while (1)
	{
		//����
		outs();

		//����
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(0, i, 1000, i);
		settextcolor(RGB(0, 0, 0));
		settextstyle(32, 0, _T("����"));
		outtextxy(50, 30, _T("����ҳ"));

		//���²ֿ���Ʒ
		vector<CK> x;
		for (int i = 0; i < cwp.size(); i++)
			if (cwp[i].sum > 0)
				x.push_back(cwp[i]);
		cwp.clear();
		for (int i = 0; i < x.size(); i++)
			cwp.push_back(x[i]);

		mps = ceil((double)cwp.size() / (double)20.0);

		//��Ʒͼ��
		for (int i = 1; i <= min(ceil(((double)cwp.size() - (ps - 1) * 20) / (double)5), 4); i++)
		{
			for (int j = 0; j < min(5, cwp.size() - (ps - 1) * 20 - (i - 1) * 5); j++)
			{
				setfillcolor(RGB(255, 250, 205));
				fillrectangle(50 + 180 * j, 100 * i, 220 + 180 * j, 80 + 100 * i);
				settextstyle(160 / thing[cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wz][cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wt].ns, 80 / thing[cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wz][cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wt].ns, _T("����"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(55 + 180 * j, 10 + 100 * i, thing[cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wz][cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wt].name);
				settextstyle(20, 0, _T("����"));
				TCHAR ss[50];
				_stprintf(ss, _T("X %d"), cwp[(ps - 1) * 20 + (i - 1) * 5 + j].sum);
				outtextxy(150 + 180 * j, 50 + 100 * i, ss);
			}
		}

		//������ҳ��
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(850, 500, 950, 550);
		settextstyle(30, 0, _T("����"));
		outtextxy(870, 510, _T("����"));

		//��һҳ/��һҳ
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(180, 540, 280, 570);
		settextstyle(16, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(182, 545, _T("��һҳ"));
		outtextxy(232, 545, _T("��һҳ"));
		if (ps <= 1)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(180, 540, 230, 570);
		}
		if (ps >= mps)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(230, 540, 280, 570);
		}
		setlinecolor(RGB(0, 0, 0));
		line(230, 541, 230, 569);

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (850 <= m.x && m.x <= 950 && 500 <= m.y && m.y <= 550)
					main_page();

				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && ps > 1)	//��һҳ
				{
					ps--;
					break;
				}
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && ps < mps)	//��һҳ
				{
					ps++;
					break;
				}

				for (int i = 1; i <= min(ceil(((double)cwp.size() - (ps - 1) * 20) / (double)5), 4); i++)
					for (int j = 0; j < min(5, cwp.size() - (ps - 1) * 20 - (i - 1) * 5); j++)
						if (50 + 180 * j <= m.x && m.x <= 220 + 180 * j && 100 * i <= m.y && m.y <= 80 + 100 * i)
							lor_wp(cwp[(ps - 1) * 20 + (i - 1) * 5 + j], 1);


			}
		}

	}
}

bool lor_mw(int f, TBOC k)			//�鿴̽��֮·��������
{
	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//�ٻ���ͼ
	IMAGE jpg;				//¼��ͼƬ��ָ��
	loadimage(&jpg, pmw[k.clan][k.race].tp, 400, 500);
	putimage(100, 50, 500, 550, &jpg, 0, 0);

	//��ֵ
	TCHAR ss[50];
	settextstyle(32, 0, _T("����"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(550, 60, _T("��:"));
	outtextxy(590, 60, pmw[k.clan][k.race].race);
	outtextxy(550, 100, _T("��:"));
	outtextxy(590, 100, CLAN[k.clan]);
	outtextxy(550, 140, _T("Ʒ��:"));
	outtextxy(630, 140, PJ[k.pj]);
	outtextxy(740, 140, _T("Ʒ��:"));
	outtextxy(820, 140, PZ[k.pz]);
	_stprintf(ss, _T("�ȼ�:%d"), k.dj);
	outtextxy(550, 180, ss);
	_stprintf(ss, _T("����:%d"), k.srd);
	outtextxy(670, 180, ss);
	_stprintf(ss, _T("����:%d"), k.s_hp);
	outtextxy(550, 250, ss);
	_stprintf(ss, _T("����:%d"), k.s_gj);
	outtextxy(550, 290, ss);
	_stprintf(ss, _T("����:%d"), k.s_fy);
	outtextxy(550, 330, ss);
	_stprintf(ss, _T("�ٶ�:%d"), k.s_sd);
	outtextxy(720, 250, ss);
	_stprintf(ss, _T("������:%d %%"), k.bjl);
	outtextxy(720, 290, ss);
	_stprintf(ss, _T("����:%d %%"), k.gdl);
	outtextxy(720, 330, ss);
	settextstyle(32, 0, _T("����"));
	settextcolor(RGB(255, 0, 0));
	_stprintf(ss, _T("ս��:%d"), k.s_zl);
	outtextxy(550, 400, ss);

	//����ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 500, 980, 550);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(910, 510, _T("����"));

	//����ͼ��
	setfillcolor(RGB(255, 0, 0));
	fillrectangle(600, 500, 700, 550);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(620, 510, _T("����"));

	//ѡ��
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 500 <= m.y && m.y <= 550)
				return 0;
			if (600 <= m.x&& m.x <= 700 && 500 <= m.y && m.y <= 550)
				return 1;
		}
	}
}

void cl_wp()		//��ʼ����Ʒͼ��
{
	//����
	wpls[1] = 58;
	thing[1][1].name = _T("�粼�־���"), thing[1][1].ns = 5, thing[1][1].bh_z = 1, thing[1][1].bh_j = 1, thing[1][1].b_jg = 30, thing[1][1].s_jg = 9;
	thing[1][2].name = _T("��粼�־���"), thing[1][2].ns = 6, thing[1][2].bh_z = 1, thing[1][2].bh_j = 2, thing[1][2].b_jg = 60, thing[1][2].s_jg = 18;
	thing[1][3].name = _T("�粼����ʿ����"), thing[1][3].ns = 7, thing[1][3].bh_z = 1, thing[1][3].bh_j = 3, thing[1][3].b_jg = 120, thing[1][3].s_jg = 36;
	thing[1][4].name = _T("�粼����������"), thing[1][4].ns = 7, thing[1][4].bh_z = 1, thing[1][4].bh_j = 4, thing[1][4].b_jg = 240, thing[1][4].s_jg = 72;
	thing[1][5].name = _T("�粼�ִ���������"), thing[1][5].ns = 8, thing[1][5].bh_z = 1, thing[1][5].bh_j = 5, thing[1][5].b_jg = 480, thing[1][5].s_jg = 144;
	thing[1][6].name = _T("�粼�ּ�ʦ����"), thing[1][6].ns = 7, thing[1][6].bh_z = 1, thing[1][6].bh_j = 6, thing[1][6].b_jg = 960, thing[1][6].s_jg = 288;
	thing[1][7].name = _T("�粼����������"), thing[1][7].ns = 7, thing[1][7].bh_z = 1, thing[1][7].bh_j = 7, thing[1][7].b_jg = 1920, thing[1][7].s_jg = 576;
	thing[1][8].name = _T("�粼�����쾫��"), thing[1][8].ns = 7, thing[1][8].bh_z = 1, thing[1][8].bh_j = 8, thing[1][8].b_jg = 3840, thing[1][8].s_jg = 1152;
	thing[1][9].name = _T("Ѫ�ڸ粼�־���"), thing[1][9].ns = 7, thing[1][9].bh_z = 1, thing[1][9].bh_j = 10, thing[1][9].b_jg = 7680, thing[1][9].s_jg = 2304;
	thing[1][10].name = _T("Ѫ�������粼�־���"), thing[1][10].ns = 9, thing[1][10].bh_z = 1, thing[1][10].bh_j = 11, thing[1][10].b_jg = 15360, thing[1][10].s_jg = 4608;
	thing[1][11].name = _T("ʯ�ӹ־���"), thing[1][11].ns = 5, thing[1][11].bh_z = 2, thing[1][11].bh_j = 1, thing[1][11].b_jg = 70, thing[1][11].s_jg = 21;
	thing[1][12].name = _T("Сʯ�˾���"), thing[1][12].ns = 5, thing[1][12].bh_z = 2, thing[1][12].bh_j = 2, thing[1][12].b_jg = 140, thing[1][12].s_jg = 42;
	thing[1][13].name = _T("ʯͷ�˾���"), thing[1][13].ns = 5, thing[1][13].bh_z = 2, thing[1][13].bh_j = 3, thing[1][13].b_jg = 280, thing[1][13].s_jg = 84;
	thing[1][14].name = _T("����ʯ�˾���"), thing[1][14].ns = 6, thing[1][14].bh_z = 2, thing[1][14].bh_j = 4, thing[1][14].b_jg = 560, thing[1][14].s_jg = 168;
	thing[1][15].name = _T("����ʯ�˾���"), thing[1][15].ns = 6, thing[1][15].bh_z = 2, thing[1][15].bh_j = 5, thing[1][15].b_jg = 1120, thing[1][15].s_jg = 336;
	thing[1][16].name = _T("�����Ҿ�����"), thing[1][16].ns = 6, thing[1][16].bh_z = 2, thing[1][16].bh_j = 6, thing[1][16].b_jg = 2240, thing[1][16].s_jg = 672;
	thing[1][17].name = _T("����ʯ�־���"), thing[1][17].ns = 6, thing[1][17].bh_z = 2, thing[1][17].bh_j = 9, thing[1][17].b_jg = 4480, thing[1][17].s_jg = 9216;
	thing[1][18].name = _T("�粼�ֿ�սħ����"), thing[1][18].ns = 8, thing[1][18].bh_z = 1, thing[1][18].bh_j = 9, thing[1][18].b_jg = 30720, thing[1][18].s_jg = 18432;
	thing[1][19].name = _T("�粼����ɱ�߾���"), thing[1][19].ns = 8, thing[1][19].bh_z = 1, thing[1][19].bh_j = 12, thing[1][19].b_jg = 61440, thing[1][19].s_jg = 36864;
	thing[1][20].name = _T("�����粼�־���"), thing[1][20].ns = 7, thing[1][20].bh_z = 1, thing[1][20].bh_j = 13, thing[1][20].b_jg = 122880, thing[1][20].s_jg = 73728;
	thing[1][21].name = _T("����.����粼�־���"), thing[1][21].ns = 9, thing[1][21].bh_z = 1, thing[1][21].bh_j = 14, thing[1][21].b_jg = 245760, thing[1][21].s_jg = 147456;
	thing[1][22].name = _T("��ȭ.ս�׸粼�־���"), thing[1][22].ns = 9, thing[1][22].bh_z = 1, thing[1][22].bh_j = 15, thing[1][22].b_jg = 491520, thing[1][22].s_jg = 294912;
	thing[1][23].name = _T("Ӱҹ.�粼��ɱ�־���"), thing[1][23].ns = 9, thing[1][23].bh_z = 1, thing[1][23].bh_j = 16, thing[1][23].b_jg = 983040, thing[1][23].s_jg = 1344;
	thing[1][24].name = _T("��ʯ�־���"), thing[1][24].ns = 5, thing[1][24].bh_z = 2, thing[1][24].bh_j = 7, thing[1][24].b_jg = 8960, thing[1][24].s_jg = 2688;
	thing[1][25].name = _T("����ʯ�龫��"), thing[1][25].ns = 6, thing[1][25].bh_z = 2, thing[1][25].bh_j = 8, thing[1][25].b_jg = 17920, thing[1][25].s_jg = 5376;
	thing[1][26].name = _T("�ͱ�ħ���龫��"), thing[1][26].ns = 7, thing[1][26].bh_z = 2, thing[1][26].bh_j = 10, thing[1][26].b_jg = 35840, thing[1][26].s_jg = 10752;
	thing[1][27].name = _T("����.���ְ�������"), thing[1][27].ns = 8, thing[1][27].bh_z = 2, thing[1][27].bh_j = 11, thing[1][27].b_jg = 71680, thing[1][27].s_jg = 21504;
	thing[1][28].name = _T("��ɫ���о���"), thing[1][28].ns = 6, thing[1][28].bh_z = 4, thing[1][28].bh_j = 1, thing[1][28].b_jg = 170, thing[1][28].s_jg = 51;
	thing[1][29].name = _T("��ɫ������"), thing[1][29].ns = 5, thing[1][29].bh_z = 4, thing[1][29].bh_j = 2, thing[1][29].b_jg = 340, thing[1][29].s_jg = 102;
	thing[1][30].name = _T("���漦����"), thing[1][30].ns = 5, thing[1][30].bh_z = 4, thing[1][30].bh_j = 3, thing[1][30].b_jg = 680, thing[1][30].s_jg = 204;
	thing[1][31].name = _T("��༦����"), thing[1][31].ns = 5, thing[1][31].bh_z = 4, thing[1][31].bh_j = 4, thing[1][31].b_jg = 1360, thing[1][31].s_jg = 408;
	thing[1][32].name = _T("���𼦾���"), thing[1][32].ns = 5, thing[1][32].bh_z = 4, thing[1][32].bh_j = 5, thing[1][32].b_jg = 2720, thing[1][32].s_jg = 816;
	thing[1][33].name = _T("����㼦����"), thing[1][33].ns = 6, thing[1][33].bh_z = 4, thing[1][33].bh_j = 6, thing[1][33].b_jg = 5440, thing[1][33].s_jg = 1632;
	thing[1][34].name = _T("���涷ս������"), thing[1][34].ns = 7, thing[1][34].bh_z = 4, thing[1][34].bh_j = 7, thing[1][34].b_jg = 10880, thing[1][34].s_jg = 3264;
	thing[1][35].name = _T("����.���㶷������"), thing[1][35].ns = 9, thing[1][35].bh_z = 4, thing[1][35].bh_j = 8, thing[1][35].b_jg = 21760, thing[1][35].s_jg = 6528;
	thing[1][36].name = _T("����.�ػ�ʼ�����"), thing[1][36].ns = 9, thing[1][36].bh_z = 4, thing[1][36].bh_j = 9, thing[1][36].b_jg = 43520, thing[1][36].s_jg = 13056;
	thing[1][37].name = _T("�׿���򼾫��"), thing[1][37].ns = 6, thing[1][37].bh_z = 5, thing[1][37].bh_j = 1, thing[1][37].b_jg = 70, thing[1][37].s_jg = 21;
	thing[1][38].name = _T("�߼���򼾫��"), thing[1][38].ns = 6, thing[1][38].bh_z = 5, thing[1][38].bh_j = 2, thing[1][38].b_jg = 140, thing[1][38].s_jg = 42;
	thing[1][39].name = _T("�߼׶���򼾫��"), thing[1][39].ns = 7, thing[1][39].bh_z = 5, thing[1][39].bh_j = 3, thing[1][39].b_jg = 280, thing[1][39].s_jg = 84;
	thing[1][40].name = _T("����߶��ھ���"), thing[1][40].ns = 7, thing[1][40].bh_z = 5, thing[1][40].bh_j = 4, thing[1][40].b_jg = 560, thing[1][40].s_jg = 168;
	thing[1][41].name = _T("ǧ���϶��ھ���"), thing[1][41].ns = 7, thing[1][41].bh_z = 5, thing[1][41].bh_j = 5, thing[1][41].b_jg = 1120, thing[1][41].s_jg = 336;
	thing[1][42].name = _T("�ж������ھ���"), thing[1][42].ns = 7, thing[1][42].bh_z = 5, thing[1][42].bh_j = 6, thing[1][42].b_jg = 2240, thing[1][42].s_jg = 672;
	thing[1][43].name = _T("�������ھ���"), thing[1][43].ns = 6, thing[1][43].bh_z = 5, thing[1][43].bh_j = 7, thing[1][43].b_jg = 4480, thing[1][43].s_jg = 1344;
	thing[1][44].name = _T("������򼾫��"), thing[1][44].ns = 6, thing[1][44].bh_z = 5, thing[1][44].bh_j = 8, thing[1][44].b_jg = 8960, thing[1][44].s_jg = 2688;
	thing[1][45].name = _T("�����ϵ��ھ���"), thing[1][45].ns = 7, thing[1][45].bh_z = 5, thing[1][45].bh_j = 9, thing[1][45].b_jg = 17920, thing[1][45].s_jg = 5376;
	thing[1][46].name = _T("��������������"), thing[1][46].ns = 7, thing[1][46].bh_z = 5, thing[1][46].bh_j = 10, thing[1][46].b_jg = 35840, thing[1][46].s_jg = 10752;
	thing[1][47].name = _T("��Ԫ������������"), thing[1][47].ns = 8, thing[1][47].bh_z = 5, thing[1][47].bh_j = 11, thing[1][47].b_jg = 71680, thing[1][47].s_jg = 21504;
	thing[1][48].name = _T("���.������������"), thing[1][48].ns = 9, thing[1][48].bh_z = 5, thing[1][48].bh_j = 12, thing[1][48].b_jg = 143360, thing[1][48].s_jg = 43008;
	thing[1][49].name = _T("ʯ��.���龫��"), thing[1][49].ns = 7, thing[1][49].bh_z = 2, thing[1][49].bh_j = 12, thing[1][49].b_jg = 143360, thing[1][49].s_jg = 43008;
	thing[1][50].name = _T("ˮ�־���"), thing[1][50].ns = 4, thing[1][50].bh_z = 6, thing[1][50].bh_j = 1, thing[1][50].b_jg = 25, thing[1][50].s_jg = 7;
	thing[1][51].name = _T("ˮ������"), thing[1][51].ns = 4, thing[1][51].bh_z = 6, thing[1][51].bh_j = 2, thing[1][51].b_jg = 50, thing[1][51].s_jg = 15;
	thing[1][52].name = _T("ˮ��ҹ�澫��"), thing[1][52].ns = 6, thing[1][52].bh_z = 6, thing[1][52].bh_j = 3, thing[1][52].b_jg = 100, thing[1][52].s_jg = 30;
	thing[1][53].name = _T("ˮ���龫��"), thing[1][53].ns = 5, thing[1][53].bh_z = 6, thing[1][53].bh_j = 4, thing[1][53].b_jg = 200, thing[1][53].s_jg = 60;
	thing[1][54].name = _T("Ϫ������.ˮ�龫��"), thing[1][54].ns = 9, thing[1][54].bh_z = 6, thing[1][54].bh_j = 5, thing[1][54].b_jg = 400, thing[1][54].s_jg = 120;
	thing[1][55].name = _T("��������.ˮ�龫��"), thing[1][55].ns = 9, thing[1][55].bh_z = 6, thing[1][55].bh_j = 6, thing[1][55].b_jg = 800, thing[1][55].s_jg = 240;
	thing[1][56].name = _T("Ϫ���������"), thing[1][56].ns = 7, thing[1][56].bh_z = 6, thing[1][56].bh_j = 7, thing[1][56].b_jg = 1600, thing[1][56].s_jg = 480;
	thing[1][57].name = _T("���·�߾���"), thing[1][57].ns = 7, thing[1][57].bh_z = 6, thing[1][57].bh_j = 8, thing[1][57].b_jg = 3200, thing[1][57].s_jg = 960;
	thing[1][58].name = _T("���������߾���"), thing[1][58].ns = 7, thing[1][58].bh_z = 6, thing[1][58].bh_j = 9, thing[1][58].b_jg = 6400, thing[1][58].s_jg = 1920;

	//��Ʒ
	wpls[2] = 12;
	thing[2][1].name = _T("��ͭ��ҳ"), thing[2][1].ns = 4, thing[2][1].bh_z = 0, thing[2][1].bh_j = 0, thing[2][1].b_jg = 100, thing[2][1].s_jg = 70;
	thing[2][2].name = _T("������ҳ"), thing[2][2].ns = 4, thing[2][2].bh_z = 0, thing[2][2].bh_j = 0, thing[2][2].b_jg = 9900, thing[2][2].s_jg = 7000;
	thing[2][3].name = _T("�ƽ���ҳ"), thing[2][3].ns = 4, thing[2][3].bh_z = 0, thing[2][3].bh_j = 0, thing[2][3].b_jg = 980000, thing[2][3].s_jg = 700000;
	thing[2][4].name = _T("ɭ��֮��"), thing[2][4].ns = 4, thing[2][4].bh_z = 0, thing[2][4].bh_j = 0, thing[2][4].b_jg = 1, thing[2][4].s_jg = 1;
	thing[2][5].name = _T("����֮��"), thing[2][5].ns = 4, thing[2][5].bh_z = 0, thing[2][5].bh_j = 0, thing[2][5].b_jg = 100, thing[2][5].s_jg = 50;
	thing[2][6].name = _T("���֮��"), thing[2][6].ns = 4, thing[2][6].bh_z = 0, thing[2][6].bh_j = 0, thing[2][6].b_jg = 10000, thing[2][6].s_jg = 5000;
	thing[2][7].name = _T("ɽ��֮��"), thing[2][7].ns = 4, thing[2][7].bh_z = 0, thing[2][7].bh_j = 0, thing[2][7].b_jg = 1000000, thing[2][7].s_jg = 500000;
	thing[2][8].name = _T("����֮��"), thing[2][8].ns = 4, thing[2][8].bh_z = 0, thing[2][8].bh_j = 0, thing[2][8].b_jg = 100000000, thing[2][8].s_jg = 50000000;
	thing[2][9].name = _T("�ͽ׻꾧"), thing[2][9].ns = 4, thing[2][9].bh_z = 0, thing[2][9].bh_j = 0, thing[2][9].b_jg = 100, thing[2][9].s_jg = 80;
	thing[2][10].name = _T("�н׻꾧"), thing[2][10].ns = 4, thing[2][10].bh_z = 0, thing[2][10].bh_j = 0, thing[2][10].b_jg = 1000, thing[2][10].s_jg = 800;
	thing[2][11].name = _T("�߽׻꾧"), thing[2][11].ns = 4, thing[2][11].bh_z = 0, thing[2][11].bh_j = 0, thing[2][11].b_jg = 10000, thing[2][11].s_jg = 8000;
	thing[2][12].name = _T("���׻꾧"), thing[2][12].ns = 4, thing[2][12].bh_z = 0, thing[2][12].bh_j = 0, thing[2][12].b_jg = 300000, thing[2][12].s_jg = 200000;
}

void cl()			//��ʼ������
{
	in_bbh();					//¼��浵�汾��
	pjj[1] = 1; for (int i = 2; i <= 21; i++)pjj[i] = pjj[i - 1] * 1.4;		//��ʼ��Ʒ���ӳɱ���
	dsj[0] = 1; for (int i = 1; i <= 170; i++)dsj[i] = dsj[i - 1] * 1.05;	//��ʼ���ȼ������ӳɱ���
	pzj[1] = 1; for (int i = 2; i <= 10; i++)pzj[i] = pzj[i - 1] * 1.5 * ((i + 1) / 3);		//��ʼ��Ʒ�ʼӳɱ���
	cl_tj();					//��ʼ��ħ��ͼ��
	cl_map();					//��ʼ����ͼ
	cl_wp();					//��ʼ����Ʒͼ��
	cl_rh();					//��ʼ����Ʒ�ں�ͼ��
	cl_dw();					//��ʼ��ħ��ɵ�����Ʒ
	in_bok();					//¼���ٻ�֮��
	in_map();					//¼��̽��֮·ħ��
	in_ck();					//¼��ֿ�
}

void in_map()				//¼��̽��֮·
{
	TCHAR s[50], ss[50];
	int dds;
	now_where = GetPrivateProfileInt(_T("ddzb"), _T("now_where"), 1, _T("data\\TSZL.ini"));
	dds = tsl;
	for (int i = 1; i <= dds; i++)
	{
		//��ҳħ������
		_stprintf(ss, _T("p%d"), i);
		int tf = GetPrivateProfileInt(ss, _T("tf"), 0, _T("data\\TSZL.ini"));

		for (int j = 0; j < tf; j++)
		{
			TBOC x;
			_stprintf(s, _T("s%d.race"), j);
			x.race = GetPrivateProfileInt(ss, s, 0, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.clan"), j);
			x.clan = GetPrivateProfileInt(ss, s, 0, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.pz"), j);
			x.pz = GetPrivateProfileInt(ss, s, 0, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.dj"), j);
			x.dj = GetPrivateProfileInt(ss, s, 0, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.srd"), j);
			x.srd = GetPrivateProfileInt(ss, s, 0, _T("data\\TSZL.ini"));
			x.pj = pmw[x.clan][x.race].pj;
			x.s_hp = mws[x.clan].s_hp * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
			x.s_gj = mws[x.clan].s_gj * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
			x.s_fy = mws[x.clan].s_fy * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
			x.s_sd = mws[x.clan].s_sd * dsj[x.dj + x.srd] * pzj[x.pz] * pjj[x.pj];
			x.bjl = mws[x.clan].bjl;
			x.gdl = mws[x.clan].gdl;
			x.s_zl = x.s_hp / 15 + x.s_gj * 6 / 5 + x.s_fy / 2;
			sob[i].push_back(x);
		}
	}
}

void out_map()				//����̽��֮·
{
	TCHAR s[50], ss[50], sss[50];
	_stprintf(s, _T("%d"), now_where);
	::WritePrivateProfileString(_T("ddzb"), _T("now_where"), s, _T("data\\TSZL.ini"));
	for (int i = 1; i <= tsl; i++)
	{
		_stprintf(s, _T("%d"), sob[i].size());
		_stprintf(ss, _T("p%d"), i);
		::WritePrivateProfileString(ss, _T("tf"), s, _T("data\\TSZL.ini"));
		for (int j = 0; j < sob[i].size(); j++)
		{
			_stprintf(s, _T("s%d.race"), j);
			_stprintf(sss, _T("%d"), sob[i][j].race);
			::WritePrivateProfileString(ss, s, sss, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.clan"), j);
			_stprintf(sss, _T("%d"), sob[i][j].clan);
			::WritePrivateProfileString(ss, s, sss, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.pz"), j);
			_stprintf(sss, _T("%d"), sob[i][j].pz);
			::WritePrivateProfileString(ss, s, sss, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.dj"), j);
			_stprintf(sss, _T("%d"), sob[i][j].dj);
			::WritePrivateProfileString(ss, s, sss, _T("data\\TSZL.ini"));
			_stprintf(s, _T("s%d.srd"), j);
			_stprintf(sss, _T("%d"), sob[i][j].srd);
			::WritePrivateProfileString(ss, s, sss, _T("data\\TSZL.ini"));
		}
	}
}

void outs()					//��������
{
	out_map();
	out_bok();
	out_ck();
	out_bbh();
}

void mw_lt(int c, int r, int z, int dj)		//ħ�������Ʒ
{
	for (int i = 0; i < dmw[c][r].size(); i++)
	{
		if (dmw[c][r][i].z != 0)	//��Ʒ
		{
			int k = find_wp(dmw[c][r][i].z, dmw[c][r][i].j);
			if (k == -1)
			{
				CK x;
				x.wz = dmw[c][r][i].z, x.wt = dmw[c][r][i].j, x.sum = random(dmw[c][r][i].suml, dmw[c][r][i].sumh);
				if (x.wz == 2 && 4 <= x.wt && x.wt <= 7)x.sum = x.sum * z * dj;
				cwp.push_back(x);
			}
			else
			{
				if (dmw[c][r][i].z == 2 && 4 <= dmw[c][r][i].j && dmw[c][r][i].j <= 7)cwp[k].sum += random(dmw[c][r][i].suml, dmw[c][r][i].sumh) * z * dj;
				else cwp[k].sum += random(dmw[c][r][i].suml, dmw[c][r][i].sumh);
			}
		}
		else    //��ʯ
		{
			int sum = random(dmw[c][r][i].suml, dmw[c][r][i].sumh);
			ys += sum;
		}

	}

	//����
	outs();
}

int find_wp(int z, int k)			//���Ҳֿ���Ʒ
{
	int r = -1;
	for (int i = 0; i < cwp.size(); i++)
		if (cwp[i].wz == z && cwp[i].wt == k)
		{
			r = i;
			break;
		}
	return r;
}

void out_bok()			//�����ٻ�֮��
{
	TCHAR s[50], ss[50];
	_stprintf(s, _T("%d"), bks);
	::WritePrivateProfileString(_T("sy"), _T("bks"), s, _T("data\\ZHZS.ini"));
	for (int i = 1; i <= bks; i++)
	{
		_stprintf(ss, _T("m%d"), i);
		if (pt[i].clan != 0 || pt[i].race != 0)
		{
			_stprintf(s, _T("%d"), 1);
			::WritePrivateProfileString(ss, _T("tf"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].race);
			::WritePrivateProfileString(ss, _T("race"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].clan);
			::WritePrivateProfileString(ss, _T("clan"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].pz);
			::WritePrivateProfileString(ss, _T("pz"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].pjz);
			::WritePrivateProfileString(ss, _T("pjz"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].dj);
			::WritePrivateProfileString(ss, _T("dj"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].srd);
			::WritePrivateProfileString(ss, _T("srd"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].ep);
			::WritePrivateProfileString(ss, _T("ep"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].hlm);
			::WritePrivateProfileString(ss, _T("hlm"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].hls);
			::WritePrivateProfileString(ss, _T("hls"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].hlz);
			::WritePrivateProfileString(ss, _T("hlz"), s, _T("data\\ZHZS.ini"));
			_stprintf(s, _T("%d"), pt[i].rsh);
			::WritePrivateProfileString(ss, _T("rsh"), s, _T("data\\ZHZS.ini"));
		}
		else
		{
			_stprintf(s, _T("%d"), 0);
			::WritePrivateProfileString(ss, _T("tf"), s, _T("data\\ZHZS.ini"));
		}
	}
	_stprintf(s, _T("%d"), zrbh[13]);
	::WritePrivateProfileString(_T("els"), _T("dt"), s, _T("data\\ZHZS.ini"));
	_stprintf(s, _T("%d"), ys);
	::WritePrivateProfileString(_T("els"), _T("ys"), s, _T("data\\ZHZS.ini"));
}

void out_ck()			//����ֿ�
{
	TCHAR s[50], ss[50];
	_stprintf(s, _T("%d"), cwp.size());
	::WritePrivateProfileString(_T("sl"), _T("wps"), s, _T("data\\CK.ini"));
	for (int i = 0; i < cwp.size(); i++)
	{
		_stprintf(ss, _T("wp%d"), i);
		_stprintf(s, _T("%d"), cwp[i].wz);
		::WritePrivateProfileString(ss, _T("wz"), s, _T("data\\CK.ini"));
		_stprintf(s, _T("%d"), cwp[i].wt);
		::WritePrivateProfileString(ss, _T("wt"), s, _T("data\\CK.ini"));
		_stprintf(s, _T("%d"), cwp[i].sum);
		::WritePrivateProfileString(ss, _T("sum"), s, _T("data\\CK.ini"));
	}
}

void in_ck()			//¼��ֿ�
{
	TCHAR ss[50];
	int wps;
	wps = GetPrivateProfileInt(_T("sl"), _T("wps"), 0, _T("data\\CK.ini"));
	for (int i = 0; i < wps; i++)
	{
		CK x;
		_stprintf(ss, _T("wp%d"), i);
		x.wz = GetPrivateProfileInt(ss, _T("wz"), 0, _T("data\\CK.ini"));
		x.wt = GetPrivateProfileInt(ss, _T("wt"), 0, _T("data\\CK.ini"));
		x.sum = GetPrivateProfileInt(ss, _T("sum"), 0, _T("data\\CK.ini"));
		cwp.push_back(x);
	}
}

void get_jy(int k, int f)
{
	//��þ���
	if (pt[k].clan != 0)pt[k].ep += f;
	while (pt[k].ep >= nep[pt[k].dj])pt[k].ep -= nep[pt[k].dj], pt[k].dj += 1;
	pt[k].s_hp = mws[pt[k].clan].s_hp * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
	pt[k].s_gj = mws[pt[k].clan].s_gj * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
	pt[k].s_fy = mws[pt[k].clan].s_fy * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
	pt[k].s_sd = mws[pt[k].clan].s_sd * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
	pt[k].bjl = mws[pt[k].clan].bjl;
	pt[k].gdl = mws[pt[k].clan].gdl;
	pt[k].s_zl = pt[k].s_hp / 15 + pt[k].s_gj * 6 / 5 + pt[k].s_fy / 2;
}

void rh_page(int k)				//�ں�ҳ��
{
	TCHAR ss[50];

	//����
	outs();

	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(450, i, 870, i);

	//���ҿ��ںϾ���
	vector<CK> x, y;
	for (int i = 0; i < cwp.size(); i++)
		if (cwp[i].sum > 0)
		{
			if (thing[cwp[i].wz][cwp[i].wt].bh_z == pt[k].clan && thing[cwp[i].wz][cwp[i].wt].bh_j <= pt[k].race)
				x.push_back(cwp[i]);			//���ںϾ���
			else y.push_back(cwp[i]);			//�����ںϾ���
		}

	//�ںϽ���
	settextstyle(20, 0, _T("����"));
	settextcolor(RGB(0, 0, 0));
	_stprintf(ss, _T("�ںϽ���: %d/%d"), pt[k].pjz, npj[pt[k].pj - mws[pt[k].clan].bs_pj + 1]);
	outtextxy(480, 10, ss);

	//��Ʒͼ��
	for (int i = 1; i <= ceil(x.size() / (double)2); i++)
	{
		for (int j = 0; j < min(2, x.size() - (i - 1) * 2); j++)
		{
			setfillcolor(RGB(255, 250, 205));
			fillrectangle(480 + 180 * j, 50 + 90 * (i - 1), 650 + 180 * j, 120 + 90 * (i - 1));
			settextstyle(160 / thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].ns, 80 / thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].ns, _T("����"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(485 + 180 * j, 60 + 90 * (i - 1), thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].name);
			settextstyle(20, 0, _T("����"));
			TCHAR ss[50];
			_stprintf(ss, _T("X %d"), x[(i - 1) * 2 + j].sum);
			outtextxy(535 + 180 * j, 90 + 90 * (i - 1), ss);
		}
	}

	//ѡ��
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//������ҳ��
				main_page();

			if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//��һҳ
				bok(k - 1, 3);

			if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//��һҳ
				bok(k + 1, 3);

			for (int i = 1; i <= 4; i++)		//��������ѡ��
				if (i != 3 && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
					bok(k, i);

			for (int i = 1; i <= ceil(x.size() / (double)2); i++)		//�ں�
				for (int j = 0; j < min(2, x.size() - (i - 1) * 2); j++)
					if (480 + 180 * j <= m.x && m.x <= 650 + 180 * j && 50 + 90 * (i - 1) <= m.y && m.y <= 120 + 90 * (i - 1))
					{
						x[(i - 1) * 2 + j].sum -= 1;
						pt[k].pjz += npj[thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].bh_j];
						while (pt[k].pjz >= npj[pt[k].pj - mws[pt[k].clan].bs_pj + 1] && pt[k].pj < mws[pt[k].clan].top)
						{
							pt[k].pjz -= npj[pt[k].pj - mws[pt[k].clan].bs_pj + 1];
							pt[k].race += 1;
							pt[k].pj = pmw[pt[k].clan][pt[k].race].pj;
							pt[k].s_hp = mws[pt[k].clan].s_hp * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
							pt[k].s_gj = mws[pt[k].clan].s_gj * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
							pt[k].s_fy = mws[pt[k].clan].s_fy * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
							pt[k].s_sd = mws[pt[k].clan].s_sd * dsj[pt[k].dj + pt[k].srd] * pzj[pt[k].pz] * pjj[pt[k].pj];
							pt[k].bjl = mws[pt[k].clan].bjl;
							pt[k].gdl = mws[pt[k].clan].gdl;
							pt[k].s_zl = pt[k].s_hp / 15 + pt[k].s_gj * 6 / 5 + pt[k].s_fy / 2;

							//�����ٻ���ͼ
							IMAGE jpg;				//¼��ͼƬ��ָ��
							loadimage(&jpg, pmw[pt[k].clan][pt[k].race].tp, 400, 500);
							putimage(30, 20, 430, 520, &jpg, 0, 0);
						}

						//���²ֿ���Ʒ
						vector<CK> xx;
						for (int ii = 0; ii < x.size(); ii++)
							if (x[ii].sum > 0)
								xx.push_back(x[ii]);
						cwp.clear();
						for (int ii = 0; ii < xx.size(); ii++)
							cwp.push_back(xx[ii]);
						for (int ii = 0; ii < y.size(); ii++)
							cwp.push_back(y[ii]);

						//���µ�ǰҳ��
						rh_page(k);
					}
		}
	}
}

void lor_wp(CK k, int f)
{
	TCHAR ss[50];

	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//��Ʒͼ
	setfillcolor(RGB(255, 250, 205));
	fillrectangle(100, 50, 500, 550);

	//��Ʒ��
	settextstyle(30, 0, _T("����"));
	_stprintf(ss, _T("��Ʒ��:%s"), thing[k.wz][k.wt].name);
	outtextxy(550, 60, ss);

	//��Ʒ����
	wp_ms(k.wz, k.wt);

	if (f == 1)
	{
		//ʹ��ͼ��
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(700, 500, 800, 550);
		settextstyle(30, 0, _T("����"));
		outtextxy(720, 510, _T("ʹ��"));

		//����ͼ��
		setfillcolor(RGB(0, 0, 255));
		fillrectangle(600, 500, 700, 550);
		settextstyle(30, 0, _T("����"));
		outtextxy(620, 510, _T("����"));

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//�ֿ�ҳ��
				if (600 <= m.x && m.x <= 700 && 500 <= m.y && m.y <= 550)cc_page();

				if (700 < m.x && m.x <= 800 && 500 <= m.y && m.y <= 550)
					if (cs_page(2, wp_ef(k.wz, k.wt)))	 //��Ʒʹ��Ч��
					{
						k.sum -= 1;
						vector<CK> x;
						for (int i = 0; i < cwp.size(); i++)
							if (cwp[i].sum > 0 && (cwp[i].wt != k.wt || cwp[i].wz != k.wz))
								x.push_back(cwp[i]);
							else if (k.sum > 0)
								x.push_back(k);
						cwp.clear();
						for (int i = 0; i < x.size(); i++)
							cwp.push_back(x[i]);
						cc_page();
					}
					else cc_page();
			}
		}

	}
	else if (f == 2)
	{
		int a = 0;		//��������

		//����ͼ��
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(900, 530, 980, 580);
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(910, 540, _T("����"));

		//����ͼ��
		if (ys >= a * thing[k.wz][k.wt].b_jg && a != 0) setfillcolor(RGB(100, 150, 200));
		else setfillcolor(RGB(192, 192, 192));
		fillrectangle(550, 500, 650, 550);
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(570, 510, _T("����"));

		//��ʯ����
		settextstyle(36, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("��ʯ��%d"), ys);
		outtextxy(100, 5, ss);

		//��������ͼ��
		setfillcolor(RGB(255, 255, 255));
		setlinecolor(RGB(0, 0, 0));
		fillrectangle(630, 417, 780, 447);
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(550, 420, _T("������"));
		_stprintf(ss, _T("%d"), a);
		outtextxy(635, 420, ss);

		//�۸�
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(550, 460, _T("�۸�"));
		outtextxy(635, 460, _T("0"));

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//����
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)sc_page(k.wz, 1);

				//����
				if (550 <= m.x && m.x <= 650 && 500 <= m.y && m.y <= 550 && ys >= a * thing[k.wz][k.wt].b_jg && a != 0)
				{
					int w = find_wp(k.wz, k.wt);
					ys -= a * thing[k.wz][k.wt].b_jg;
					if (w != -1)
						cwp[w].sum += a;
					else
					{
						CK x = k;
						x.sum = a;
						cwp.push_back(x);
					}
					lor_wp(k, f);
				}

				//��������
				if (630 <= m.x && m.x <= 780 && 417 <= m.y && m.y <= 447)
				{
					//����
					TCHAR as[100];
					InputBox(as, 100, _T("����"));
					a = _wtoi(as);
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(0, 0, 0));
					fillrectangle(630, 417, 780, 447);
					settextstyle(30, 0, _T("����"));
					settextcolor(RGB(0, 0, 0));
					_stprintf(ss, _T("%d"), a);
					outtextxy(635, 420, ss);

					//�۸�
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(255, 255, 255));
					fillrectangle(630, 455, 850, 490);
					settextstyle(30, 0, _T("����"));
					if (ys >= a * thing[k.wz][k.wt].b_jg)settextcolor(RGB(0, 0, 0));
					else settextcolor(RGB(255, 0, 0));
					_stprintf(ss, _T("%lld"), a * thing[k.wz][k.wt].b_jg);
					outtextxy(635, 460, ss);

					//����ͼ��
					if (ys >= a * thing[k.wz][k.wt].b_jg && a != 0) setfillcolor(RGB(100, 150, 200));
					else setfillcolor(RGB(192, 192, 192));
					fillrectangle(550, 500, 650, 550);
					settextstyle(30, 0, _T("����"));
					settextcolor(RGB(0, 0, 0));
					outtextxy(570, 510, _T("����"));
				}
			}
		}

	}
}

bool wp_ef(int z, int k)			//��Ʒʹ��Ч��
{
	if (z == 1)
	{
		if (pt[bks].clan != 0)return 0;
		int i;
		for (i = 1; i <= bks; i++)
			if (pt[i].clan == 0)break;
		pt[i].clan = thing[1][k].bh_z, pt[i].race = thing[1][k].bh_j, pt[i].pz = pmw[pt[i].clan][pt[i].race].pz, pt[i].pjz = 0, pt[i].dj = 0, pt[i].srd = 0, pt[i].ep = 0, pt[i].hlz = 0, pt[i].hls = 0, pt[i].hlm = 6;
		pt[i].pj = pmw[pt[i].clan][pt[i].race].pj;
		pt[i].s_hp = mws[pt[i].clan].s_hp * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].s_gj = mws[pt[i].clan].s_gj * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].s_fy = mws[pt[i].clan].s_fy * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].s_sd = mws[pt[i].clan].s_sd * dsj[pt[i].dj + pt[i].srd] * pzj[pt[i].pz] * pjj[pt[i].pj];
		pt[i].bjl = mws[pt[i].clan].bjl;
		pt[i].gdl = mws[pt[i].clan].gdl;
		pt[i].s_zl = pt[i].s_hp / 15 + pt[i].s_gj * 6 / 5 + pt[i].s_fy / 2;
	}
	if (z == 2)
	{
		if (k == 1)
			if (bks < 6)bks += 1;
			else return 0;
		if (k == 2)
			if (bks < 10)bks += 1;
			else return 0;
		if (k == 3)
			if (bks < 15)bks += 1;
			else return 0;
		if (k == 4 || k == 5 || k == 6 || k == 7 || k == 8)
			bok(1, 2);
		if (k == 9 || k == 10 || k == 11 || k == 12 || k == 13)
			bok(1, 4);
	}
	return 1;
}

void sg_page(int k)
{
	while (1)
	{
		TCHAR ss[50];

		//����
		outs();

		//����
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(450, i, 870, i);

		//���²ֿ���Ʒ
		vector<CK> x;
		for (int i = 0; i < cwp.size(); i++)
			if (cwp[i].sum > 0)
				x.push_back(cwp[i]);
		cwp.clear();
		for (int i = 0; i < x.size(); i++)
			cwp.push_back(x[i]);

		//�ȼ�������
		settextstyle(32, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("�ȼ�:%d"), pt[k].dj);
		outtextxy(480, 10, ss);
		settextstyle(16, 0, _T("����"));
		_stprintf(ss, _T("����:%llu/%llu"), pt[k].ep, nep[pt[k].dj]);
		outtextxy(480, 50, ss);

		//����ʯͼ��
		int f1, f2, f3, f4, f5;

		settextcolor(RGB(0, 0, 0));
		settextstyle(40, 0, _T("����"));

		setfillcolor(RGB(0, 255, 0));
		fillrectangle(480, 100, 650, 170);
		outtextxy(485, 110, _T("ɭ��֮��"));
		setfillcolor(RGB(0, 191, 255));
		fillrectangle(660, 100, 830, 170);
		outtextxy(665, 110, _T("����֮��"));
		setfillcolor(RGB(138, 43, 226));
		fillrectangle(480, 190, 650, 260);
		outtextxy(485, 200, _T("���֮��"));
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(660, 190, 830, 260);
		outtextxy(665, 200, _T("ɽ��֮��"));
		setfillcolor(RGB(255, 255, 0));
		fillrectangle(480, 280, 650, 350);
		outtextxy(485, 290, _T("����֮��"));

		settextstyle(20, 0, _T("����"));

		f1 = find_wp(2, 4);
		if (f1 == -1)_stprintf(ss, _T("X %d"), 0);
		else _stprintf(ss, _T("X %d"), cwp[f1].sum);
		outtextxy(535, 150, ss);
		f2 = find_wp(2, 5);
		if (f2 == -1)_stprintf(ss, _T("X %d"), 0);
		else _stprintf(ss, _T("X %d"), cwp[f2].sum);
		outtextxy(715, 150, ss);
		f3 = find_wp(2, 6);
		if (f3 == -1)_stprintf(ss, _T("X %d"), 0);
		else _stprintf(ss, _T("X %d"), cwp[f3].sum);
		outtextxy(535, 240, ss);
		f4 = find_wp(2, 7);
		if (f4 == -1)_stprintf(ss, _T("X %d"), 0);
		else _stprintf(ss, _T("X %d"), cwp[f4].sum);
		outtextxy(715, 240, ss);
		f5 = find_wp(2, 8);
		if (f5 == -1)_stprintf(ss, _T("X %d"), 0);
		else _stprintf(ss, _T("X %d"), cwp[f5].sum);
		outtextxy(535, 330, ss);

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//������ҳ��
					main_page();
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//��һҳ
					bok(k - 1, 2);
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//��һҳ
					bok(k + 1, 2);
				for (int i = 1; i <= 4; i++)		//��������ѡ��
					if (i != 2 && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
						bok(k, i);
				if (480 <= m.x&&m.x <= 650 && 100 <= m.y && m.y <= 170)//ɭ��֮��
					if (f1 != -1)
					{
						get_jy(k, 100);
						cwp[f1].sum -= 1;
						break;
					}
				if (660 <= m.x&&m.x <= 830 && 100 <= m.y && m.y <= 170)//����֮��
					if (f2 != -1 && cwp[f2].sum > 0)
					{
						get_jy(k, 10000);
						cwp[f2].sum -= 1;
						break;
					}
				if (480 <= m.x&&m.x <= 650 && 190 <= m.y && m.y <= 260)//���֮��
					if (f3 != -1)
					{
						get_jy(k, 1000000);
						cwp[f3].sum -= 1;
						break;
					}
				if (660 <= m.x&&m.x <= 830 && 190 <= m.y && m.y <= 260)//ɽ��֮��
					if (f4 != -1)
					{
						get_jy(k, 100000000);
						cwp[f4].sum -= 1;
						break;
					}
				if (480 <= m.x&&m.x <= 650 && 280 <= m.y && m.y <= 350)//����֮��
					if (f5 != -1)
					{
						get_jy(k, 10000000000);
						cwp[f5].sum -= 1;
						break;
					}
			}
		}
	}
}

bool ck_px(CK a, CK b)
{
	if (a.wz == b.wz)return a.wt < b.wt;
	return a.wz > b.wz;
}

void rl_page(int f, int k, int z)
{
	TCHAR ss[50];

	//����
	outs();

	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//������ҳ��ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextstyle(30, 0, _T("����"));
	outtextxy(910, 540, _T("����"));

	//�����ں�ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(300, 400, 400, 450);
	settextstyle(30, 0, _T("����"));
	outtextxy(320, 410, _T("�ں�"));
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(410, 400, 510, 450);
	settextstyle(20, 0, _T("����"));
	outtextxy(420, 420, _T("ȫ���ں�"));

	//�������
	setfillcolor(RGB(210, 105, 30));
	for (int i = 1; i <= 1; i++)
		fillrectangle(890, 10 + (i - 1) * 60, 990, 70 + (i - 1) * 60);
	setfillcolor(RGB(255, 0, 0));
	fillrectangle(890, 10 + (f - 1) * 60, 990, 70 + (f - 1) * 60);
	settextstyle(30, 0, _T("����"));
	outtextxy(910, 25, _T("�ں�"));

	//��Ʒͼ��
	int maxs;
	if (f == 1)maxs = rhsum;
	for (int i = 1; i <= min(9, maxs - (k - 1) * 9); i++)
	{
		if (i == z)setfillcolor(RGB(210, 105, 100));
		else setfillcolor(RGB(110, 205, 100));
		fillrectangle(790, 30 + (i - 1) * 60, 890, 80 + (i - 1) * 60);
		settextstyle(100 / thing[rhwp[9 * (k - 1) + i].mz][rhwp[9 * (k - 1) + i].mr].ns, 50 / thing[rhwp[9 * (k - 1) + i].mz][rhwp[9 * (k - 1) + i].mr].ns, _T("����"));
		outtextxy(792, 40 + (i - 1) * 60, thing[rhwp[9 * (k - 1) + i].mz][rhwp[9 * (k - 1) + i].mr].name);
	}

	//�ںͽ���
	setfillcolor(RGB(110, 205, 100));
	fillrectangle(350, 50, 450, 100);
	settextstyle(100 / thing[rhwp[9 * (k - 1) + z].mz][rhwp[9 * (k - 1) + z].mr].ns, 50 / thing[rhwp[9 * (k - 1) + z].mz][rhwp[9 * (k - 1) + z].mr].ns, _T("����"));
	outtextxy(352, 60, thing[rhwp[9 * (k - 1) + z].mz][rhwp[9 * (k - 1) + z].mr].name);
	IMAGE jpg;				//¼��ͼƬ��ָ��
	loadimage(&jpg, _T("res\\��ͷ.jpg"), 40, 80);
	putimage(380, 110, 40, 80, &jpg, 0, 0);
	for (int i = 0; i < rhwp[9 * (k - 1) + z].n; i++)
	{
		int w = find_wp(rhwp[9 * (k - 1) + z].nz[i], rhwp[9 * (k - 1) + z].nr[i]);
		if (w == -1 || cwp[w].sum < rhwp[9 * (k - 1) + z].ns[i])setfillcolor(RGB(192, 192, 192));
		else setfillcolor(RGB(110, 205, 100));
		fillrectangle(20 + i * 180, 210, 150 + i * 180, 280);
		settextstyle(120 / thing[rhwp[9 * (k - 1) + z].nz[i]][rhwp[9 * (k - 1) + z].nr[i]].ns, 60 / thing[rhwp[9 * (k - 1) + z].nz[i]][rhwp[9 * (k - 1) + z].nr[i]].ns, _T("����"));
		outtextxy(25 + i * 180, 220, thing[rhwp[9 * (k - 1) + z].nz[i]][rhwp[9 * (k - 1) + z].nr[i]].name);
		settextstyle(20, 0, _T("����"));
		if (w == -1)_stprintf(ss, _T("%d/%d"), 0, rhwp[9 * (k - 1) + z].ns[i]);
		else _stprintf(ss, _T("%d/%d"), cwp[w].sum, rhwp[9 * (k - 1) + z].ns[i]);
		outtextxy(30 + 180 * i, 260, ss);
	}

	//ѡ��
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580) main_page();			//������ҳ��

			if (300 <= m.x && m.x <= 400 && 400 <= m.y && m.y <= 450)	//�ں�
			{
				bool rl = 1;
				for (int i = 0; i < rhwp[9 * (k - 1) + z].n; i++)
				{
					int w = find_wp(rhwp[9 * (k - 1) + z].nz[i], rhwp[9 * (k - 1) + z].nr[i]);
					if (w == -1 || cwp[w].sum < rhwp[9 * (k - 1) + z].ns[i])
					{
						rl = 0;
						break;
					}
				}
				if (rl)
				{
					for (int i = 0; i < rhwp[9 * (k - 1) + z].n; i++)
					{
						int w = find_wp(rhwp[9 * (k - 1) + z].nz[i], rhwp[9 * (k - 1) + z].nr[i]);
						cwp[w].sum -= rhwp[9 * (k - 1) + z].ns[i];
					}
					int w = find_wp(rhwp[9 * (k - 1) + z].mz, rhwp[9 * (k - 1) + z].mr);
					if (w == -1)
					{
						CK x;
						x.wz = rhwp[9 * (k - 1) + z].mz, x.wt = rhwp[9 * (k - 1) + z].mr, x.sum = 1;
						cwp.push_back(x);
					}
					else cwp[w].sum++;
					rl_page(f, k, z);
				}
			}

			if (410 <= m.x && m.x <= 510 && 400 <= m.y && m.y <= 450)	//ȫ���ں�
			{
				int bs = 10000000000;
				bool rl = 1;
				for (int i = 0; i < rhwp[9 * (k - 1) + z].n; i++)
				{
					int w = find_wp(rhwp[9 * (k - 1) + z].nz[i], rhwp[9 * (k - 1) + z].nr[i]);
					if (w == -1 || cwp[w].sum < rhwp[9 * (k - 1) + z].ns[i])
					{
						rl = 0;
						break;
					}
					else bs = min(bs, cwp[w].sum / rhwp[9 * (k - 1) + z].ns[i]);
				}
				if (rl)
				{
					for (int i = 0; i < rhwp[9 * (k - 1) + z].n; i++)
					{
						int w = find_wp(rhwp[9 * (k - 1) + z].nz[i], rhwp[9 * (k - 1) + z].nr[i]);
						cwp[w].sum -= rhwp[9 * (k - 1) + z].ns[i] * bs;
					}
					int w = find_wp(rhwp[9 * (k - 1) + z].mz, rhwp[9 * (k - 1) + z].mr);
					if (w == -1)
					{
						CK x;
						x.wz = rhwp[9 * (k - 1) + z].mz, x.wt = rhwp[9 * (k - 1) + z].mr, x.sum = bs;
						cwp.push_back(x);
					}
					else cwp[w].sum += bs;
					rl_page(f, k, z);
				}
			}

			for (int i = 1; i <= 1; i++)		//��������ѡ��
				if (i != f && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
					rl_page(i, 1, 1);

			for (int i = 1; i <= min(9, maxs - (k - 1) * 9); i++)		//����������Ʒ
				if (i != z && 790 <= m.x && m.x <= 890 && 30 + (i - 1) * 60 <= m.y && m.y <= 80 + (i - 1) * 60)
					rl_page(f, k, i);

		}
	}
}

void cl_rh()
{
	rhsum = 6;

	//������ҳ
	rhwp[1].mz = 2, rhwp[1].mr = 2, rhwp[1].n = 1;
	rhwp[1].nz.push_back(2);
	rhwp[1].nr.push_back(1);
	rhwp[1].ns.push_back(10);

	//�ƽ���ҳ
	rhwp[2].mz = 2, rhwp[2].mr = 3, rhwp[2].n = 1;
	rhwp[2].nz.push_back(2);
	rhwp[2].nr.push_back(2);
	rhwp[2].ns.push_back(10);

	//����֮��
	rhwp[3].mz = 2, rhwp[3].mr = 5, rhwp[3].n = 1;
	rhwp[3].nz.push_back(2);
	rhwp[3].nr.push_back(4);
	rhwp[3].ns.push_back(100);

	//���֮��
	rhwp[4].mz = 2, rhwp[4].mr = 6, rhwp[4].n = 1;
	rhwp[4].nz.push_back(2);
	rhwp[4].nr.push_back(5);
	rhwp[4].ns.push_back(100);

	//ɽ��֮��
	rhwp[5].mz = 2, rhwp[5].mr = 7, rhwp[5].n = 1;
	rhwp[5].nz.push_back(2);
	rhwp[5].nr.push_back(6);
	rhwp[5].ns.push_back(100);

	//����֮��
	rhwp[6].mz = 2, rhwp[6].mr = 8, rhwp[6].n = 1;
	rhwp[6].nz.push_back(2);
	rhwp[6].nr.push_back(7);
	rhwp[6].ns.push_back(100);
}

void cl_dw()
{
	CDWP x;

	//�粼��
	x.z = 1, x.j = 1, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][1].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[1][1].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 5, x.sumh = 10, x.gl = 100; dmw[1][1].push_back(x);		//��ʯ

	//��粼��
	x.z = 1, x.j = 2, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][2].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[1][2].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 10, x.sumh = 20, x.gl = 100; dmw[1][2].push_back(x);		//��ʯ

	//�粼����ʿ
	x.z = 1, x.j = 3, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][3].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[1][3].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 20, x.sumh = 40, x.gl = 100; dmw[1][3].push_back(x);		//��ʯ

	//�粼������
	x.z = 1, x.j = 4, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][4].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[1][4].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 40, x.sumh = 80, x.gl = 100; dmw[1][4].push_back(x);		//��ʯ

	//�粼�ִ�����
	x.z = 1, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][5].push_back(x);			//����
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[1][5].push_back(x);			//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 80, x.sumh = 160, x.gl = 100; dmw[1][5].push_back(x);		//��ʯ

	//�粼�ּ�ʦ
	x.z = 1, x.j = 6, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][6].push_back(x);			//����
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[1][6].push_back(x);			//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 160, x.sumh = 320, x.gl = 100; dmw[1][6].push_back(x);		//��ʯ

	//�粼������
	x.z = 1, x.j = 7, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][7].push_back(x);			//����
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[1][7].push_back(x);			//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 320, x.sumh = 640, x.gl = 100; dmw[1][7].push_back(x);		//��ʯ

	//�粼������
	x.z = 1, x.j = 8, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][8].push_back(x);			//����
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[1][8].push_back(x);			//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][8].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 640, x.sumh = 1280, x.gl = 100; dmw[1][8].push_back(x);		//��ʯ

	//�粼�ֿ�սħ
	x.z = 1, x.j = 18, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][9].push_back(x);			//����
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[1][9].push_back(x);			//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][9].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 1280, x.sumh = 2560, x.gl = 100; dmw[1][9].push_back(x);		//��ʯ

	//Ѫ�ڸ粼��
	x.z = 1, x.j = 10, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][10].push_back(x);				//����
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[1][10].push_back(x);				//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][10].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 2560, x.sumh = 5120, x.gl = 100; dmw[1][10].push_back(x);		//��ʯ

	//Ѫ�������粼��
	x.z = 1, x.j = 11, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][11].push_back(x);				//����
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[1][11].push_back(x);				//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][11].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 5120, x.sumh = 10240, x.gl = 100; dmw[1][11].push_back(x);		//��ʯ

	//�粼����ɱ��
	x.z = 1, x.j = 19, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][12].push_back(x);				//����
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[1][12].push_back(x);				//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][12].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 10240, x.sumh = 20480, x.gl = 100; dmw[1][12].push_back(x);		//��ʯ

	//�����粼��
	x.z = 1, x.j = 20, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][13].push_back(x);				//����
	x.z = 2, x.j = 5, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[1][13].push_back(x);				//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][13].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 20480, x.sumh = 40960, x.gl = 100; dmw[1][13].push_back(x);		//��ʯ

	//����.����粼��
	x.z = 1, x.j = 21, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][14].push_back(x);				//����
	x.z = 2, x.j = 5, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[1][14].push_back(x);				//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][14].push_back(x);				//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 40960, x.sumh = 81920, x.gl = 100; dmw[1][14].push_back(x);		//��ʯ

	//��ȭ.ս�׸粼��
	x.z = 1, x.j = 22, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][15].push_back(x);				//����
	x.z = 2, x.j = 6, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[1][15].push_back(x);				//���֮��
	x.z = 2, x.j = 10, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][15].push_back(x);				//�н׻꾧
	x.z = 0, x.j = 0, x.suml = 81920, x.sumh = 163840, x.gl = 100; dmw[1][15].push_back(x);		//��ʯ

	//Ӱҹ.�粼��ɱ��
	x.z = 1, x.j = 23, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][16].push_back(x);				//����
	x.z = 2, x.j = 6, x.suml = 2, x.sumh = 4, x.gl = 50; dmw[1][16].push_back(x);				//���֮��
	x.z = 2, x.j = 10, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][16].push_back(x);				//�н׻꾧
	x.z = 0, x.j = 0, x.suml = 163840, x.sumh = 327680, x.gl = 100; dmw[1][16].push_back(x);	//��ʯ

	//ʯ�ӹ�
	x.z = 1, x.j = 11, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][1].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[2][1].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 8, x.sumh = 16, x.gl = 100; dmw[2][1].push_back(x);		//��ʯ

	//Сʯ��
	x.z = 1, x.j = 12, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][2].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[2][2].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 16, x.sumh = 32, x.gl = 100; dmw[2][2].push_back(x);		//��ʯ

	//ʯͷ��
	x.z = 1, x.j = 13, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][3].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[2][3].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 32, x.sumh = 64, x.gl = 100; dmw[2][3].push_back(x);		//��ʯ

	//����ʯ��
	x.z = 1, x.j = 14, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][4].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[2][4].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 64, x.sumh = 128, x.gl = 100; dmw[2][4].push_back(x);		//��ʯ

	//����ʯ��
	x.z = 1, x.j = 15, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][5].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[2][5].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 128, x.sumh = 256, x.gl = 100; dmw[2][5].push_back(x);		//��ʯ

	//�����Ҿ�
	x.z = 1, x.j = 16, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][6].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[2][6].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 256, x.sumh = 512, x.gl = 100; dmw[2][6].push_back(x);		//��ʯ

	//��ʯ��
	x.z = 1, x.j = 24, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][7].push_back(x);	//����
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[2][7].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][7].push_back(x);		//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 512, x.sumh = 1024, x.gl = 100; dmw[2][7].push_back(x);		//��ʯ

	//��������
	x.z = 1, x.j = 25, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][8].push_back(x);	//����
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[2][8].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][8].push_back(x);		//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 1024, x.sumh = 2048, x.gl = 100; dmw[2][8].push_back(x);		//��ʯ

	//����ʯ��
	x.z = 1, x.j = 17, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][9].push_back(x);	//����
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[2][9].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][9].push_back(x);		//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 2048, x.sumh = 4096, x.gl = 100; dmw[2][9].push_back(x);		//��ʯ

	//�ͱ�ħ����
	x.z = 1, x.j = 26, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][10].push_back(x);	//����
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[2][10].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][10].push_back(x);	//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 4096, x.sumh = 8192, x.gl = 100; dmw[2][10].push_back(x);		//��ʯ

	//����.���ְ���
	x.z = 1, x.j = 27, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][11].push_back(x);	//����
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[2][11].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][11].push_back(x);	//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 8192, x.sumh = 16284, x.gl = 100; dmw[2][11].push_back(x);		//��ʯ

	//ʯ��.����
	x.z = 1, x.j = 49, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][12].push_back(x);	//����
	x.z = 2, x.j = 5, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[2][12].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][12].push_back(x);	//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 16384, x.sumh = 32768, x.gl = 100; dmw[2][12].push_back(x);		//��ʯ

	//ѧ��
	x.z = 2, x.j = 1, x.suml = 1, x.sumh = 1, x.gl = 30; dmw[3][1].push_back(x);	//��ͭ��ҳ
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[3][1].push_back(x);	//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[3][1].push_back(x);	//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 10, x.sumh = 10, x.gl = 100; dmw[3][1].push_back(x);	//��ʯ

	//ѧ��
	x.z = 2, x.j = 2, x.suml = 1, x.sumh = 1, x.gl = 20; dmw[3][2].push_back(x);		//������ҳ
	x.z = 2, x.j = 6, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[3][2].push_back(x);		//���֮��
	x.z = 2, x.j = 9, x.suml = 4, x.sumh = 7, x.gl = 50; dmw[3][2].push_back(x);		//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 1000, x.sumh = 1000, x.gl = 100; dmw[3][2].push_back(x);	//��ʯ

	//ѧ��
	x.z = 2, x.j = 3, x.suml = 1, x.sumh = 1, x.gl = 10; dmw[3][3].push_back(x);			//�ƽ���ҳ
	x.z = 2, x.j = 7, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[3][3].push_back(x);			//ɽ��֮��
	x.z = 2, x.j = 10, x.suml = 1, x.sumh = 2, x.gl = 50; dmw[3][3].push_back(x);			//�н׻꾧
	x.z = 0, x.j = 0, x.suml = 100000, x.sumh = 100000, x.gl = 100; dmw[3][3].push_back(x);	//��ʯ

	//��ɫ����
	x.z = 1, x.j = 28, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][1].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[4][1].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 20, x.sumh = 40, x.gl = 100; dmw[4][1].push_back(x);		//��ʯ

	//��ɫ��
	x.z = 1, x.j = 29, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][2].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[4][2].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 40, x.sumh = 80, x.gl = 100; dmw[4][2].push_back(x);		//��ʯ

	//���漦
	x.z = 1, x.j = 30, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][3].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[4][3].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 80, x.sumh = 160, x.gl = 100; dmw[4][3].push_back(x);	//��ʯ

	//��༦
	x.z = 1, x.j = 31, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][4].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[4][4].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 160, x.sumh = 320, x.gl = 100; dmw[4][4].push_back(x);	//��ʯ

	//����
	x.z = 1, x.j = 32, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][5].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[4][5].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[4][5].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 320, x.sumh = 640, x.gl = 100; dmw[4][5].push_back(x);	//��ʯ

	//����㼦
	x.z = 1, x.j = 33, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][6].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[4][6].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2, dmw[4][6].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 640, x.sumh = 1280, x.gl = 100; dmw[4][6].push_back(x);	//��ʯ

	//���׶�ս��
	x.z = 1, x.j = 34, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][7].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[4][7].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[4][7].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 1280, x.sumh = 2560, x.gl = 100; dmw[4][7].push_back(x);	//��ʯ

	//����.���㶷��
	x.z = 1, x.j = 35, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][8].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[4][8].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[4][8].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 2560, x.sumh = 5120, x.gl = 100; dmw[4][8].push_back(x);	//��ʯ

	//����.�ػ�ʼ�
	x.z = 1, x.j = 36, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][9].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[4][9].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 5; dmw[4][9].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 5120, x.sumh = 10240, x.gl = 100; dmw[4][9].push_back(x);//��ʯ

	//�׿����
	x.z = 1, x.j = 37, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][1].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 4, x.gl = 50; dmw[5][1].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 16, x.sumh = 32, x.gl = 100; dmw[5][1].push_back(x);		//��ʯ

	//�߼����
	x.z = 1, x.j = 38, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][2].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[5][2].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 32, x.sumh = 64, x.gl = 100; dmw[5][2].push_back(x);		//��ʯ

	//�߼׶����
	x.z = 1, x.j = 39, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][3].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[5][3].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 64, x.sumh = 128, x.gl = 100; dmw[5][3].push_back(x);	//��ʯ

	//����߶���
	x.z = 1, x.j = 40, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][4].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[5][4].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 128, x.sumh = 256, x.gl = 100; dmw[5][4].push_back(x);	//��ʯ

	//ǧ���϶���	
	x.z = 1, x.j = 41, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][5].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[5][5].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 256, x.sumh = 512, x.gl = 100; dmw[5][5].push_back(x);	//��ʯ

	//�ж�������	
	x.z = 1, x.j = 42, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][6].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[5][6].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 512, x.sumh = 1024, x.gl = 100; dmw[5][6].push_back(x);	//��ʯ

	//��������
	x.z = 1, x.j = 43, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][7].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[5][7].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][7].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 1024, x.sumh = 2048, x.gl = 100; dmw[5][7].push_back(x);	//��ʯ

	//�������
	x.z = 1, x.j = 44, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][8].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[5][8].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][8].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 2048, x.sumh = 4096, x.gl = 100; dmw[5][8].push_back(x);	//��ʯ

	//�����ϵ���
	x.z = 1, x.j = 45, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][9].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[5][9].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][9].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 4096, x.sumh = 8192, x.gl = 100; dmw[5][9].push_back(x);	//��ʯ

	//����������
	x.z = 1, x.j = 46, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][10].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[5][10].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][10].push_back(x);		//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 8192, x.sumh = 16384, x.gl = 100; dmw[5][10].push_back(x);//��ʯ

	//��Ԫ��������
	x.z = 1, x.j = 47, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][11].push_back(x);			//����
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[5][11].push_back(x);			//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][11].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 16384, x.sumh = 32768, x.gl = 100; dmw[5][11].push_back(x);	//��ʯ

	//���.��������
	x.z = 1, x.j = 48, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][12].push_back(x);			//����
	x.z = 2, x.j = 5, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[5][12].push_back(x);			//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][12].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 32768, x.sumh = 65536, x.gl = 100; dmw[5][12].push_back(x);	//��ʯ

	//ˮ��
	x.z = 1, x.j = 50, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][1].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[6][1].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 4, x.sumh = 8, x.gl = 100; dmw[6][1].push_back(x);	//��ʯ

	//ˮ��
	x.z = 1, x.j = 51, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][2].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[6][2].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 8, x.sumh = 16, x.gl = 100; dmw[6][2].push_back(x);	//��ʯ

	//ˮ��ҹ��
	x.z = 1, x.j = 52, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][3].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[6][3].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 16, x.sumh = 32, x.gl = 100; dmw[6][3].push_back(x);	//��ʯ

	//ˮ����
	x.z = 1, x.j = 53, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][4].push_back(x);	//����
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[6][4].push_back(x);	//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 32, x.sumh = 64, x.gl = 100; dmw[6][4].push_back(x);	//��ʯ

	//Ϫ������.ˮ��
	x.z = 1, x.j = 54, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][5].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[6][5].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 64, x.sumh = 128, x.gl = 100; dmw[6][5].push_back(x);	//��ʯ

	//��������.ˮ��
	x.z = 1, x.j = 55, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][6].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[6][6].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 128, x.sumh = 256, x.gl = 100; dmw[6][6].push_back(x);	//��ʯ

	//Ϫ�������
	x.z = 1, x.j = 56, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][7].push_back(x);		//����
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[6][7].push_back(x);		//ɭ��֮��
	x.z = 0, x.j = 0, x.suml = 256, x.sumh = 512, x.gl = 100;  dmw[6][7].push_back(x);	//��ʯ

	//���·��
	x.z = 1, x.j = 57, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][8].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[6][8].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[6][8].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 512, x.sumh = 1024, x.gl = 100;  dmw[6][8].push_back(x);	//��ʯ

	//����������
	x.z = 1, x.j = 58, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][9].push_back(x);		//����
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[6][9].push_back(x);		//����֮��
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[6][9].push_back(x);			//�ͽ׻꾧
	x.z = 0, x.j = 0, x.suml = 1024, x.sumh = 2048, x.gl = 100;  dmw[6][9].push_back(x);//��ʯ

}

void zr_page()			//����ҳ��
{
	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//������ҳ��ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("����"));
	outtextxy(910, 540, _T("����"));

	//����ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(100, 530, 200, 580);
	settextstyle(30, 0, _T("����"));
	outtextxy(120, 540, _T("����"));

	//����Ծ�����
	settextstyle(20, 0, _T("����"));
	settextcolor(RGB(255, 0, 0));
	outtextxy(100, 70, _T("����Ծ�����"));

	//��������
	settextstyle(20, 0, _T("����"));
	settextcolor(RGB(255, 0, 0));
	outtextxy(110, 290, _T("��������"));

	//��ս��
	TCHAR ss[50];
	unsigned long long zl = 0;
	for (int i = 1; i <= 6; i++)zl += pt[zrbh[i]].s_zl;
	settextstyle(32, 0, _T("����"));
	settextcolor(RGB(255, 0, 0));
	_stprintf(ss, _T("��ս��:%llu"), zl);
	outtextxy(100, 210, ss);
	_stprintf(ss, _T("ս��:%llu"), pt[zrbh[13]].s_zl);
	outtextxy(100, 430, ss);

	int sums = 0;
	bool bl[10];
	memset(bl, 0, sizeof(bl));

	while (1)
	{
		//����
		outs();

		//����Ծ�����ͼ��
		for (int i = 1; i <= 6; i++)
		{
			if (!bl[i])setfillcolor(RGB(255, 250, 205));
			else setfillcolor(RGB(255, 99, 71));
			fillrectangle(100 + 120 * (i - 1), 100, 200 + 120 * (i - 1), 160);
			settextstyle(80 / pmw[pt[zrbh[i]].clan][pt[zrbh[i]].race].ns, 40 / pmw[pt[zrbh[i]].clan][pt[zrbh[i]].race].ns, _T("����"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(105 + 120 * (i - 1), 120, pmw[pt[zrbh[i]].clan][pt[zrbh[i]].race].race);
			setfillcolor(RGB(100, 150, 200));
			fillrectangle(120 + 120 * (i - 1), 170, 180 + 120 * (i - 1), 200);
			settextstyle(20, 0, _T("����"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(130 + 120 * (i - 1), 175, _T("����"));
		}

		//��������ͼ��
		setfillcolor(RGB(255, 250, 205));
		fillrectangle(100, 320, 200, 380);
		settextstyle(80 / pmw[pt[zrbh[13]].clan][pt[zrbh[13]].race].ns, 40 / pmw[pt[zrbh[13]].clan][pt[zrbh[13]].race].ns, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(105, 340, pmw[pt[zrbh[13]].clan][pt[zrbh[13]].race].race);
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(120, 390, 180, 420);
		settextstyle(20, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(130, 395, _T("����"));

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//������ҳ��
					main_page();

				//ѡ��Ҫ��λ��ħ��
				bool rl = 0;
				for (int i = 1; i <= 6; i++)
				{
					if (100 + 120 * (i - 1) <= m.x && m.x <= 200 + 120 * (i - 1) && 100 <= m.y && m.y <= 160)
					{
						if (bl[i] == 0 && sums < 2) bl[i] = 1, sums++;
						else if (bl[i] == 1) bl[i] = 0, sums--;
						rl = 1;
						break;
					}
					if (rl)break;
				}
				if (rl)break;

				//������Ծ��ٻ���
				for (int i = 1; i <= 6; i++)
				{
					if (120 + 120 * (i - 1) <= m.x && m.x <= 180 + 120 * (i - 1) && 170 <= m.y && m.y <= 200)
						sh_page(i);
				}

				//�������ٻ���
				if (120 <= m.x && m.x <= 180 && 390 <= m.y && m.y <= 420)
					sh_page(13);

				//����
				if (100 <= m.x && m.x <= 200 && 530 <= m.y && m.y <= 580)
				{
					int a1, a2;
					if (sums == 2)
					{
						for (int i = 1; i <= 6; i++)if (bl[i])a2 = i;
						for (int i = 6; i >= 1; i--)if (bl[i])a1 = i;
						if (zrbh[13] == a1 || zrbh[13] == a2)zrbh[13] = a1 + a2 - zrbh[13];
						swap(pt[a1].rsh, pt[a2].rsh);

						//����
						for (int i = 1; i <= bks; i++)
							for (int j = i + 1; j <= bks; j++)
								if (pt[i].rsh != 0 && pt[j].rsh != 0 && pt[i].rsh > pt[j].rsh)
									swap(pt[i], pt[j]);
								else if (pt[i].rsh == 0 && pt[j].rsh != 0)
									swap(pt[i], pt[j]);

						memset(bl, 0, sizeof(bl));
						sums = 0;
						break;
					}
				}

			}
		}

	}
}

void map_page()
{
	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//��ͼ
	IMAGE jpg;				//¼��ͼƬ��ָ��
	loadimage(&jpg, _T("res\\��ͼ.jpg "), 1000, 600);
	putimage(0, 0, 1000, 600, &jpg, 0, 0);

	//������ҳ��ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextstyle(30, 0, _T("����"));
	outtextxy(910, 540, _T("����"));

	//ps
	settextstyle(16, 0, _T("����"));
	outtextxy(700, 30, _T("ĳ���ʵص���ָ���ͳһ"));
	outtextxy(700, 50, _T("Ϊĳ���ʵص���ͳ��ָ���"));

	//ѡ��
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//����̽��֮·
				return;
		}
	}
}

void in_bbh()
{
	bbh = GetPrivateProfileInt(_T("bbn"), _T("bbh"), 1.5, _T("data\\BBH.ini"));
}

void out_bbh()
{
	::WritePrivateProfileString(_T("bbn"), _T("bbh"), _T("1.5"), _T("data\\BBH.ini"));/////////////////////////////�ص�ע��/////////////////////////////////�ص�ע��///////////////////////////////�ص�ע��/////////////////////////////////
}

void hl_page(int k)
{
	int mps, ps = 1;			//�׼�����ҳ��
	while (1)
	{
		//����
		outs();

		//����
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(450, i, 870, i);

		//���ҿ��ںϾ���
		vector<CK> x, y;
		for (int i = 0; i < cwp.size(); i++)
			if (cwp[i].sum > 0 && cwp[i].wz == 1 || (cwp[i].wz == 2 && 9 <= cwp[i].wt&&cwp[i].wt <= 12))
				x.push_back(cwp[i]);			//���׼���Ʒ
			else
				y.push_back(cwp[i]);			//�����׼���Ʒ

		mps = ceil((double)x.size() / (double)10.0);

		//����ֵ�������������ޡ��ѻ�������
		TCHAR ss[50];
		settextstyle(32, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("����: %d   �ȼ�: %d"), pt[k].srd, pt[k].dj);
		outtextxy(480, 10, ss);
		settextstyle(26, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("�׼�ֵ: %d/%d"), pt[k].hlz, hlz[pt[k].hls]);
		outtextxy(480, 50, ss);
		settextstyle(20, 0, _T("����"));
		_stprintf(ss, _T("��������: %d/%d"), pt[k].hls, pt[k].hlm);
		outtextxy(480, 85, ss);

		//����ͼ��
		setfillcolor(RGB(255, 160, 122));
		fillrectangle(750, 50, 820, 83);
		settextstyle(30, 0, _T("����"));
		settextcolor(RGB(138, 43, 226));
		outtextxy(757, 54, _T("����"));

		//��ҳͼ��
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(850, 270, 880, 370);
		settextstyle(16, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(857, 275, _T("��"));
		outtextxy(857, 288, _T("һ"));
		outtextxy(857, 301, _T("ҳ"));
		outtextxy(857, 324, _T("��"));
		outtextxy(857, 337, _T("һ"));
		outtextxy(857, 350, _T("ҳ"));
		if (ps <= 1)
		{
			setfillcolor(RGB(255, 0, 0));
			setlinecolor(RGB(255, 255, 255));
			fillrectangle(850, 270, 880, 320);
		}
		if (ps >= mps)
		{
			setfillcolor(RGB(255, 0, 0));
			setlinecolor(RGB(255, 255, 255));
			fillrectangle(850, 320, 880, 370);
		}
		setlinecolor(RGB(0, 0, 0));
		line(851, 320, 879, 320);

		//��Ʒͼ��
		for (int i = 1; i <= min(5, ceil((x.size() - (ps - 1) * 10) / (double)2)); i++)
		{
			for (int j = 0; j < min(2, x.size() - (ps - 1) * 10 - (i - 1) * 2); j++)
			{
				setfillcolor(RGB(255, 250, 205));
				fillrectangle(480 + 180 * j, 130 + 90 * (i - 1), 650 + 180 * j, 200 + 90 * (i - 1));
				settextstyle(160 / thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].ns, 80 / thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].ns, _T("����"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(485 + 180 * j, 140 + 90 * (i - 1), thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].name);
				settextstyle(20, 0, _T("����"));
				_stprintf(ss, _T("X %d"), x[(ps - 1) * 10 + (i - 1) * 2 + j].sum);
				outtextxy(535 + 180 * j, 170 + 90 * (i - 1), ss);
			}
		}

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//������ҳ��
					main_page();
				if (750 <= m.x && m.x <= 820 && 50 <= m.y && m.y <= 83 && pt[k].hls < pt[k].hlm && pt[k].hlz >= hlz[pt[k].hls])
				{
					pt[k].srd += pt[k].dj;
					pt[k].hlz -= hlz[pt[k].hls];
					pt[k].hls++;
					pt[k].dj = 0;
					pt[k].ep = 0;
					break;
				}
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//�ٻ�����һҳ
					bok(k - 1, 4);
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//�ٻ�����һҳ
					bok(k + 1, 4);
				if (850 <= m.x && m.x <= 880 && 270 <= m.y && m.y <= 320 && ps > 1)	//�׼���Ʒ��һҳ
				{
					ps--;
					break;
				}
				if (850 <= m.x && m.x <= 880 && 320 < m.y && m.y <= 370 && ps < mps)//�׼���Ʒ��һҳ
				{
					ps++;
					break;
				}
				for (int i = 1; i <= 4; i++)		//��������ѡ��
					if (i != 4 && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
						bok(k, i);

				bool rl = 0;
				for (int i = 1; i <= ceil(x.size() / (double)2); i++)		//�׼�
				{
					for (int j = 0; j < min(2, x.size() - (i - 1) * 2); j++)
						if (480 + 180 * j <= m.x && m.x <= 650 + 180 * j && 130 + 90 * (i - 1) <= m.y && m.y <= 200 + 90 * (i - 1))
						{
							x[(ps - 1) * 10 + (i - 1) * 2 + j].sum -= 1;
							if (x[(ps - 1) * 10 + (i - 1) * 2 + j].wz == 1)
								pt[k].hlz += pmw[thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].bh_z][thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].bh_j].pj;
							else
							{
								if (x[(ps - 1) * 10 + (i - 1) * 2 + j].wt == 9) pt[k].hlz += 10;
								if (x[(ps - 1) * 10 + (i - 1) * 2 + j].wt == 10)pt[k].hlz += 100;
								if (x[(ps - 1) * 10 + (i - 1) * 2 + j].wt == 11)pt[k].hlz += 1000;
								if (x[(ps - 1) * 10 + (i - 1) * 2 + j].wt == 12)pt[k].hlz += 10000;
							}
							//���²ֿ���Ʒ
							vector<CK> xx;
							for (int ii = 0; ii < x.size(); ii++)
								if (x[ii].sum > 0)
									xx.push_back(x[ii]);
							cwp.clear();
							for (int ii = 0; ii < xx.size(); ii++)
								cwp.push_back(xx[ii]);
							for (int ii = 0; ii < y.size(); ii++)
								cwp.push_back(y[ii]);
							rl = 1;
							break;
						}
					if (rl)break;
				}
				if (rl)break;
			}
		}
	}
}

void wp_ms(int z, int t)
{
	TCHAR ss[50];
	if (z == 1)
	{
		settextcolor(RGB(0, 0, 0));
		settextstyle(25, 0, _T("����"));
		_stprintf(ss, _T("ʹ�ú���%s"), pmw[thing[z][t].bh_z][thing[z][t].bh_j].race);
		outtextxy(550, 110, ss);
	}
	else if (z == 2)
	{
		if (t == 1)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("���ٻ���ҳС��6ʱ��ʹ�ÿ�����1ҳ�ٻ�"));
			outtextxy(550, 140, _T("��ҳ"));
		}
		if (t == 2)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("���ٻ���ҳС��10ʱ��ʹ�ÿ�����1ҳ�ٻ�"));
			outtextxy(550, 140, _T("��ҳ"));
		}
		if (t == 3)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("���ٻ���ҳС��15ʱ��ʹ�ÿ�����1ҳ�ٻ�"));
			outtextxy(550, 140, _T("��ҳ"));
		}
		if (t == 4)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ�ú���100����"));
		}
		if (t == 5)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ�ú���10000����"));
		}
		if (t == 6)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ�ú���1000000����"));
		}
		if (t == 7)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ�ú���100000000����"));
		}
		if (t == 8)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ�ú���10000000000����"));
		}
		if (t == 9)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ������10�����׼�ֵ"));
		}
		if (t == 10)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ������100�����׼�ֵ"));
		}
		if (t == 11)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ������1000�����׼�ֵ"));
		}
		if (t == 12)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("����"));
			outtextxy(550, 110, _T("ʹ������10000�����׼�ֵ"));
		}
	}
}

void sh_page(int k)
{
	int sums = 0;
	bool bl[30];
	memset(bl, 0, sizeof(bl));

	//����
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//����ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("����"));
	outtextxy(910, 540, _T("����"));

	//ȡ��ͼ��
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(800, 530, 880, 580);
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("����"));
	outtextxy(810, 540, _T("ȡ��"));

	while (1)
	{

		//�ٻ���ͼ��
		for (int i = 1; i <= ceil((double)bks / (double)7); i++)
		{
			for (int j = 1; j <= min(7, bks - (i - 1) * 7); j++)
			{
				if (pt[(i - 1) * 7 + j].rsh != 0 && pt[(i - 1) * 7 + j].rsh != 13 && k != 13)setfillcolor(RGB(192, 192, 192));
				else if (bl[(i - 1) * 7 + j])setfillcolor(RGB(255, 99, 71));
				else setfillcolor(RGB(255, 250, 205));
				fillrectangle(20 + 120 * (j - 1), 60 + 80 * (i - 1), 120 + 120 * (j - 1), 120 + 80 * (i - 1));
				settextstyle(80 / pmw[pt[(i - 1) * 7 + j].clan][pt[(i - 1) * 7 + j].race].ns, 40 / pmw[pt[(i - 1) * 7 + j].clan][pt[(i - 1) * 7 + j].race].ns, _T("����"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(25 + 120 * (j - 1), 80 + 80 * (i - 1), pmw[pt[(i - 1) * 7 + j].clan][pt[(i - 1) * 7 + j].race].race);
			}
		}

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//ѡ��Ҫ�����ħ��
				bool rl = 0;
				for (int i = 1; i <= ceil((double)bks / (double)7); i++)
				{
					for (int j = 1; j <= min(7, bks - (i - 1) * 7); j++)
					{
						if (20 + 120 * (j - 1) <= m.x && m.x <= 120 + 120 * (j - 1) && 60 + 80 * (i - 1) <= m.y && m.y <= 120 + 80 * (i - 1) && (pt[(i - 1) * 7 + j].rsh == 0 || k == 13 || pt[(i - 1) * 7 + j].rsh == 13))
						{
							if (bl[(i - 1) * 7 + j] == 0 && sums == 0)
								bl[(i - 1) * 7 + j] = 1, sums = 1;
							else if (bl[(i - 1) * 7 + j] == 1)
								bl[(i - 1) * 7 + j] = 0, sums = 0;
							rl = 1;
							break;
						}
					}
					if (rl)break;
				}
				if (rl)break;

				//����
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580 && sums == 1)
				{
					for (int i = 1; i <= bks; i++)
						if (bl[i] == 1 && k != 13)
						{
							pt[zrbh[k]].rsh = 0;
							pt[i].rsh = k;
							zrbh[k] = k;
						}
						else if (bl[i] == 1 && k == 13)
							zrbh[13] = i;
					//����
					for (int i = 1; i <= bks; i++)
						for (int j = i + 1; j <= bks; j++)
							if (pt[i].rsh != 0 && pt[j].rsh != 0 && pt[i].rsh > pt[j].rsh)
								swap(pt[i], pt[j]);
							else if (pt[i].rsh == 0 && pt[j].rsh != 0)
								swap(pt[i], pt[j]);

					zr_page();
				}

				//ȡ��
				if (800 <= m.x && m.x <= 880 && 530 <= m.y && m.y <= 580)
					zr_page();

			}
		}

	}

}

bool bok_px(TBOC a, TBOC b)
{
	if (a.rsh != 0 && b.rsh != 0)
		return a.rsh < b.rsh;
	return a.rsh > b.rsh;
}

void sc_page(int t, int z)
{
	while (1)
	{
		TCHAR ss[50];

		//����
		outs();

		//����
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(0, i, 1000, i);

		//����ͼ��
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(900, 530, 980, 580);
		settextcolor(RGB(0, 0, 0));
		settextstyle(30, 0, _T("����"));
		outtextxy(910, 540, _T("����"));

		//��һҳ/��һҳ
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(180, 540, 280, 570);
		settextstyle(16, 0, _T("����"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(182, 545, _T("��һҳ"));
		outtextxy(232, 545, _T("��һҳ"));
		if (z <= 1)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(180, 540, 230, 570);
		}
		if (z >= ceil((double)wpls[t] / (double)24))
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(230, 540, 280, 570);
		}
		setlinecolor(RGB(0, 0, 0));
		line(230, 541, 230, 569);

		//�����ͼ��
		setfillcolor(RGB(210, 105, 30));
		for (int i = 1; i <= 2; i++)
			fillrectangle(50 + 100 * (i - 1), 60, 150 + 100 * (i - 1), 120);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(50 + 100 * (t - 1), 60, 150 + 100 * (t - 1), 120);
		settextcolor(RGB(0, 0, 0));
		settextstyle(30, 0, _T("����"));
		outtextxy(70, 75, _T("����"));
		outtextxy(170, 75, _T("����"));

		//��ʯ����
		settextcolor(RGB(0, 0, 0));
		settextstyle(30, 0, _T("����"));
		_stprintf(ss, _T("��ʯ��%d"), ys);
		outtextxy(50, 20, ss);

		//��Ʒͼ��
		for (int i = 1; i <= min(ceil(((double)wpls[t] - (z - 1) * 24) / (double)5), 4); i++)
		{
			for (int j = 1; j <= min(6, wpls[t] - (z - 1) * 24 - (i - 1) * 6); j++)
			{
				if (thing[t][(z - 1) * 24 + (i - 1) * 6 + j].b_jg > 0)setfillcolor(RGB(255, 250, 205));
				else setfillcolor(RGB(192, 192, 192));
				fillrectangle(50 + 150 * (j - 1), 150 + 80 * (i - 1), 180 + 150 * (j - 1), 210 + 80 * (i - 1));
				settextstyle(120 / thing[t][(z - 1) * 24 + (i - 1) * 6 + j].ns, 0, _T("����"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(55 + 150 * (j - 1), 170 + 80 * (i - 1), thing[t][(z - 1) * 24 + (i - 1) * 6 + j].name);
			}
		}

		//ѡ��
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//������ҳ��
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)main_page();

				//��һҳ
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && z > 1)
				{
					z--;
					break;
				}

				//��һҳ
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && z < ceil((double)wpls[t] / (double)24))
				{
					z++;
					break;
				}

				//�������
				bool rl = 0;
				for (int i = 1; i <= 2; i++)
					if (50 + 100 * (i - 1) <= m.x && m.x <= 150 + 100 * (i - 1) && 60 <= m.y && m.y <= 120 && i != t)
					{
						t = i;
						z = 1;
						rl = 1;
						break;
					}
				if (rl)break;

				//�鿴��Ʒ
				for (int i = 1; i <= min(ceil(((double)wpls[t] - (z - 1) * 24) / (double)5), 4); i++)
					for (int j = 1; j <= min(6, wpls[t] - (z - 1) * 24 - (i - 1) * 6); j++)
						if (50 + 150 * (j - 1) <= m.x && m.x <= 180 + 150 * (j - 1) && 150 + 80 * (i - 1) <= m.y && m.y <= 210 + 80 * (i - 1) && thing[t][(z - 1) * 24 + (i - 1) * 6 + j].b_jg > 0)
						{
							CK x;
							x.wz = t;
							x.wt = (z - 1) * 24 + (i - 1) * 6 + j;
							lor_wp(x, 2);
						}

			}
		}

	}
}

void cl_jn()
{
	JN x;

	//�粼����
	//1��
	x.name = _T("ץ��"), x.cs = 1, x.lb = 1, x.bh = 1; pjn[1][1][1] = x;
	//2��
	//3��
	//4��
	x.name = _T("�Ǽ�"), x.cs = 4, x.lb = 1, x.bh = 2; pjn[1][4][1] = x;
	//5��

	//ʯ����
	//1��
	x.name = _T("ʯ��"), x.cs = 1, x.lb = 1, x.bh = 3; pjn[2][1][1] = x;
	//2��
	x.name = _T("ʯ��ǽ"), x.cs = 2, x.lb = 1, x.bh = 4; pjn[2][2][1] = x;
	x.name = _T("����"), x.cs = 2, x.lb = 1, x.bh = 5; pjn[2][2][2] = x;
	//3��
	//4��
	//5��

	//���漦��
	//1��
	x.name = _T("����"), x.cs = 1, x.lb = 1, x.bh = 6; pjn[3][1][1] = x;
	//2��
	//3��
	//4��
	//5��

	//ˮԪ����
	//1��
	//2��
	//3��
	//4��
	//5��
}

int main()
{
	srand((int)time(0));		//���������
	cl();

	initgraph(1000, 600);
	setbkmode(TRANSPARENT);

	open();
	main_page();

	closegraph();
	return 0;
}