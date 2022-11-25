#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <direct.h>
using namespace std;

struct JN					//技能图鉴
{
	LPCTSTR name;			//技能名称
	int cs;					//技能层数
	int lb;					//技能类别
	int bh;					//技能编号
};

struct mowu					//魔物图鉴
{
	LPCTSTR race;			//种
	int ns;					//"种"的字数
	int clan;				//族(代号)
	int pz;					//品质
	int pj;					//品级/阶
	LPCTSTR tp;				//图片
};

struct TBOC					//召唤之书(页内) / 野生魔物
{
	int race;				//种
	int clan;				//族(代号)
	int pz;					//品质
	int pj;					//品级/阶
	int pjz;				//已有进阶值
	int dj;					//等级
	int srd;				//魂炼等级
	unsigned long long ep;	//经验
	int hlm;				//最高魂炼次数
	int hls;				//已魂炼次数
	int hlz;				//魂炼献祭值
	long long s_gj;			//攻击力
	long long s_fy;			//防御力
	long long s_hp;			//生命值
	long long s_zl;			//战力
	long long s_sd;			//速度
	int bjl;				//暴击率
	int gdl;				//格挡率
	int rsh;				//上阵位置
	int js;					//拥有技能数量
	vector<JN> jns;			//具体拥有技能
};

struct PL					//探索之路地点
{
	LPCTSTR name;			//地点名
	int ns;					//地点名长
	int gl;					//可见概率
	LPCTSTR tp;				//图片
};

struct WP					//物品图鉴
{
	LPCTSTR name;			//物品名称
	int ns;					//物品名长
	int bh_j;				//精魄种编号	非精魄为0
	int bh_z;				//精魄族编号	非精魄为0
	long long b_jg;			//买入价格
	long long s_jg;			//售出价格
};

struct CK					//仓库物品
{
	int wz;					//物品种类
	int wt;					//在物品图鉴中编号
	int sum;				//数量
};

struct KMW					//探索之路可刷新魔物
{
	int clan;				//族
	int rl;					//最低种
	int rh;					//最高种
	int pzl;				//最低品质
	int pzh;				//最高品质
	int djl;				//最低等级
	int djh;				//最高等级
	int srl;				//最低魂炼
	int srh;				//最高魂炼
};

struct WRH					//物品融合图鉴
{
	int mz;					//融合后物品种类
	int mr;					//融合后物品编号
	int n;					//需要融合的物品种类
	vector<int> nz;			//需要融合的第i个物品种类
	vector<int> nr;			//需要融合的第i个物品编号
	vector<int> ns;			//需要融合的第i个物品数量
};

struct CDWP					//魔物可掉落物品
{
	int z;					//种类
	int j;					//编号
	int suml;				//最少数量
	int sumh;				//最多数量
	int gl;					//获得概率
};

struct MWZ					//图鉴魔物基础数值
{
	int top;				//最高品阶
	int bs_pj;				//基础品级
	long long s_gj;			//攻击力
	long long s_fy;			//防御力
	long long s_hp;			//生命值
	long long s_sd;			//速度
	int bjl;				//暴击率
	int gdl;				//格挡率
};

double bbh;					//录入版本号
int mn = 3;					//图鉴魔物数量
int tsl;					//探索之路地点数量
int bks;					//召唤之书总页数
int now_where;				//探险中当前位置
int rhsum;					//融合物品种类
int zrbh[20];				//阵容中召唤兽在召唤之书中编号
int wpls[10];				//各类物品种数
long long ys;				//玉石数量
long long nep[20] = { 1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15,1e16,1e17 };
long long npj[30] = { 0,1,4,16,16 * 4,64 * 4,256 * 4,1024 * 4,4096 * 4,16384 * 4,65536 * 4,262144 * 4,1048576 * 4,4194304 * 4,16777216 * 4,67108864 * 4,268435456 * 4 };
long long hlz[30] = { 100 * 5,200 * 5,400 * 5,800 * 5,1600 * 5,3200 * 5,6400 * 5,12800 * 5,25600 * 5,51200 * 5,102400 * 5,204800 * 5,409600 * 5,819200 * 5,819200 * 2 * 5 };
double dsj[160];			//等级魂炼加成倍数
double pzj[100];			//品质加成倍数
double pjj[100];			//品阶加成倍数
vector<CK> cwp;				//仓库物品
vector<int>	mp[100];		//探索之路路径
vector<TBOC>sob[100];		//探索之路魔物
vector<KMW> kmw[100];		//地点i可刷新魔物
vector<CDWP>dmw[20][20];	//魔物可掉落物品
MOUSEMSG m;
string buf;
LPCTSTR JNLB[10] = { _T("无"),_T("锁定技"),_T("转换技"),_T("普通技"),_T("限定技"),_T("觉醒技") };
LPCTSTR CLAN[20] = { _T("无"),_T("哥布林"),_T("石人"),_T("书页怪"),_T("火焰鸡"),_T("蜈蚣"),_T("水元素") };
LPCTSTR PJ[30] = { _T("无"),_T("普通*"),_T("普通**"),_T("普通***"),_T("稀有*"),_T("稀有**") ,_T("稀有***") ,_T("罕见*") ,_T("罕见**") ,_T("罕见***") ,_T("绝世*") ,_T("绝世**") ,_T("绝世***") ,_T("史诗*") ,_T("史诗**") ,_T("史诗***") ,_T("传说*") ,_T("传说**") ,_T("传说***") ,_T("神话*") ,_T("神话**") ,_T("神话***") ,_T("永恒*") ,_T("永恒**") ,_T("永恒***") };
LPCTSTR PZ[30] = { _T("无"),_T("常见"),_T("精锐"),_T("君主") ,_T("领主") ,_T("主宰") ,_T("帝皇") ,_T("圣灵") ,_T("位神") ,_T("神王") ,_T("祖神") };
mowu pmw[20][20];			//图鉴魔物
TBOC pt[20];				//召唤之书召唤兽
PL place[100];				//探索之路地点
WP thing[4][100];			//物品图鉴 thing[1]..魔物精魄  thing[2]..物品
WRH rhwp[20];				//物品融合图鉴
MWZ mws[20];				//各族魔物基本属性
JN pjn[20][10][10];			//各族魔物各层技能

long long random(int l, int r);				//随机数
void cl_tj();								//魔物图鉴初始化
void in_bok();								//录入召唤之书
void open();								//开始页面
void main_page();							//主页面
void bok(int k, int f);						//召唤之书页面
void ele(int k);							//探索
void cl_map();								//初始化地图
void cl_ts(int z);							//刷新探索之路召唤兽
bool PvE(TBOC E[], int tot, int tos);		//对战机器
bool cs_page(int z, bool r);					//结算页面
void cc_page();								//储存页面
bool lor_mw(int f, TBOC k);					//查看魔物详细属性
void cl_wp();								//初始化物品图鉴
void cl();									//初始化整合
void in_map();								//录入探索之路魔物
void out_map();								//保存探索之路魔物
void outs();								//保存整合
void mw_lt(int c, int r, int z, int dj);		//魔物掉落物品
int find_wp(int z, int k);					//查找仓库物品
void out_bok();								//保存召唤之书
void out_ck();								//保存仓库
void in_ck();								//录入仓库
void get_jy(int k, int f);					//获取经验
void rh_page(int k);						//融合页面
void lor_wp(CK k, int f);					//查看物品详细属性
bool wp_ef(int z, int k);					//物品使用效果
void sg_page(int k);						//升级页面
bool ck_px(CK a, CK b);						//仓库排序
void rl_page(int f, int k, int z);			//熔炼页面
void cl_rh();								//初始化物品融合图鉴
void cl_dw();								//初始化魔物可掉落物品
void zr_page();								//换位页面
void map_page();							//查看地图页面
void in_bbh();								//录入版本号
void out_bbh();								//保存版本号
void hl_page(int k);						//魂炼页面
void wp_ms(int z, int t);					//物品描述
void sh_page(int k);						//上阵页面
bool bok_px(TBOC a, TBOC b);				//召唤之书排序
void sc_page(int t, int z);					//商城页面
void cl_jn();								//技能图鉴


long long random(int l, int r)
{
	int x = rand() + rand() / rand() * (rand() + 1239) + rand();
	return x % (max(r - l + 1, 1)) + l;
}

void cl_tj()		//魔物图鉴初始化
{
	pmw[0][0].race = _T("无"), pmw[0][0].ns = 3, pmw[0][0].clan = 0;
	mws[0].bs_pj = 1;
	//哥布林种族
	mws[1].top = 16, mws[1].bs_pj = 1, mws[1].s_gj = 15, mws[1].s_fy = 5, mws[1].s_hp = 100, mws[1].s_sd = 10, mws[1].bjl = 10, mws[1].gdl = 10;
	pmw[1][1].race = _T("哥布林"), pmw[1][1].ns = 3, pmw[1][1].clan = 1, pmw[1][1].pz = 1, pmw[1][1].pj = 1, pmw[1][1].tp = _T("res\\哥布林.jpg");
	pmw[1][2].race = _T("大哥布林"), pmw[1][2].ns = 4, pmw[1][2].clan = 1, pmw[1][2].pz = 1, pmw[1][2].pj = 2, pmw[1][2].tp = _T("res\\大哥布林.jpg");
	pmw[1][3].race = _T("哥布林勇士"), pmw[1][3].ns = 5, pmw[1][3].clan = 1, pmw[1][3].pz = 1, pmw[1][3].pj = 3, pmw[1][3].tp = _T("res\\哥布林勇士.jpg");
	pmw[1][4].race = _T("哥布林酋长"), pmw[1][4].ns = 5, pmw[1][4].clan = 1, pmw[1][4].pz = 1, pmw[1][4].pj = 4, pmw[1][4].tp = _T("res\\哥布林酋长.jpg");
	pmw[1][5].race = _T("哥布林大酋长"), pmw[1][5].ns = 6, pmw[1][5].clan = 1, pmw[1][5].pz = 1, pmw[1][5].pj = 5, pmw[1][5].tp = _T("res\\哥布林大酋长.jpg");
	pmw[1][6].race = _T("哥布林祭师"), pmw[1][6].ns = 5, pmw[1][6].clan = 1, pmw[1][6].pz = 1, pmw[1][6].pj = 6, pmw[1][6].tp = _T("res\\哥布林祭师.jpg");
	pmw[1][7].race = _T("哥布林主祭"), pmw[1][7].ns = 5, pmw[1][7].clan = 1, pmw[1][7].pz = 1, pmw[1][7].pj = 7, pmw[1][7].tp = _T("res\\哥布林主祭.jpg");
	pmw[1][8].race = _T("哥布林首领"), pmw[1][8].ns = 5, pmw[1][8].clan = 1, pmw[1][8].pz = 1, pmw[1][8].pj = 8, pmw[1][8].tp = _T("res\\哥布林首领.jpg");
	pmw[1][9].race = _T("哥布林狂战魔"), pmw[1][9].ns = 6, pmw[1][9].clan = 1, pmw[1][9].pz = 1, pmw[1][9].pj = 9, pmw[1][9].tp = _T("res\\哥布林狂战魔.jpg");
	pmw[1][10].race = _T("血冠哥布林"), pmw[1][10].ns = 5, pmw[1][10].clan = 1, pmw[1][10].pz = 1, pmw[1][10].pj = 10, pmw[1][10].tp = _T("res\\血冠哥布林.jpg");
	pmw[1][11].race = _T("血暗荆棘哥布林"), pmw[1][11].ns = 7, pmw[1][11].clan = 1, pmw[1][11].pz = 1, pmw[1][11].pj = 11, pmw[1][11].tp = _T("res\\血暗荆棘哥布林.jpg");
	pmw[1][12].race = _T("哥布林屠杀者"), pmw[1][12].ns = 6, pmw[1][12].clan = 1, pmw[1][12].pz = 1, pmw[1][12].pj = 12, pmw[1][12].tp = _T("res\\哥布林屠杀者.jpg");
	pmw[1][13].race = _T("炼狱哥布林"), pmw[1][13].ns = 5, pmw[1][13].clan = 1, pmw[1][13].pz = 1, pmw[1][13].pj = 13, pmw[1][13].tp = _T("res\\炼狱哥布林.jpg");
	pmw[1][14].race = _T("虫骑.烈焰哥布林"), pmw[1][14].ns = 7, pmw[1][14].clan = 1, pmw[1][14].pz = 1, pmw[1][14].pj = 14, pmw[1][14].tp = _T("res\\虫骑.烈焰哥布林.jpg");
	pmw[1][15].race = _T("铁拳.战甲哥布林"), pmw[1][15].ns = 7, pmw[1][15].clan = 1, pmw[1][15].pz = 1, pmw[1][15].pj = 15, pmw[1][15].tp = _T("res\\铁拳.战甲哥布林.jpg");
	pmw[1][16].race = _T("影夜.哥布林杀手"), pmw[1][16].ns = 7, pmw[1][16].clan = 1, pmw[1][16].pz = 1, pmw[1][16].pj = 16, pmw[1][16].tp = _T("res\\影夜.哥布林杀手.jpg");

	//石人种族
	mws[2].top = 13, mws[2].bs_pj = 2, mws[2].s_gj = 10, mws[2].s_fy = 18, mws[2].s_hp = 130, mws[2].s_sd = 3, mws[2].bjl = 5, mws[2].gdl = 15;
	pmw[2][1].race = _T("石子怪"), pmw[2][1].ns = 3, pmw[2][1].clan = 2, pmw[2][1].pz = 1, pmw[2][1].pj = 2, pmw[2][1].tp = _T("res\\石子怪.jpg");
	pmw[2][2].race = _T("小石人"), pmw[2][2].ns = 3, pmw[2][2].clan = 2, pmw[2][2].pz = 1, pmw[2][2].pj = 3, pmw[2][2].tp = _T("res\\小石人.jpg");
	pmw[2][3].race = _T("石头人"), pmw[2][3].ns = 3, pmw[2][3].clan = 2, pmw[2][3].pz = 1, pmw[2][3].pj = 4, pmw[2][3].tp = _T("res\\石头人.jpg");
	pmw[2][4].race = _T("巨岩石人"), pmw[2][4].ns = 4, pmw[2][4].clan = 2, pmw[2][4].pz = 1, pmw[2][4].pj = 5, pmw[2][4].tp = _T("res\\巨岩石人.jpg");
	pmw[2][5].race = _T("戈仑石人"), pmw[2][5].ns = 4, pmw[2][5].clan = 2, pmw[2][5].pz = 1, pmw[2][5].pj = 6, pmw[2][5].tp = _T("res\\戈仑石人.jpg");
	pmw[2][6].race = _T("戈仑岩晶"), pmw[2][6].ns = 4, pmw[2][6].clan = 2, pmw[2][6].pz = 1, pmw[2][6].pj = 7, pmw[2][6].tp = _T("res\\戈仑岩晶.jpg");
	pmw[2][7].race = _T("蛮石怪"), pmw[2][7].ns = 3, pmw[2][7].clan = 2, pmw[2][7].pz = 1, pmw[2][7].pj = 8, pmw[2][7].tp = _T("res\\蛮石怪.jpg");
	pmw[2][8].race = _T("擎天石灵"), pmw[2][8].ns = 4, pmw[2][8].clan = 2, pmw[2][8].pz = 1, pmw[2][8].pj = 9, pmw[2][8].tp = _T("res\\擎天石灵.jpg");
	pmw[2][9].race = _T("熔岩石怪"), pmw[2][9].ns = 4, pmw[2][9].clan = 2, pmw[2][9].pz = 1, pmw[2][9].pj = 10, pmw[2][9].tp = _T("res\\熔岩石怪.jpg");
	pmw[2][10].race = _T("焱冰魔岩灵"), pmw[2][10].ns = 5, pmw[2][10].clan = 2, pmw[2][10].pz = 1, pmw[2][10].pj = 11, pmw[2][10].tp = _T("res\\焱冰魔岩灵.jpg");
	pmw[2][11].race = _T("磐岩.丛林霸主"), pmw[2][11].ns = 7, pmw[2][11].clan = 2, pmw[2][11].pz = 1, pmw[2][11].pj = 12, pmw[2][11].tp = _T("res\\磐岩.丛林霸主.jpg");
	pmw[2][12].race = _T("石崖.岩灵"), pmw[2][12].ns = 4, pmw[2][12].clan = 2, pmw[2][12].pz = 1, pmw[2][12].pj = 13, pmw[2][12].tp = _T("res\\石崖.岩灵.jpg");

	//书页种族
	mws[3].top = 3, mws[3].bs_pj = 3, mws[3].s_gj = 25, mws[3].s_fy = 15, mws[3].s_hp = 90, mws[3].s_sd = 20, mws[3].bjl = 20, mws[3].gdl = 20;
	pmw[3][1].race = _T("学渣"), pmw[3][1].ns = 3, pmw[3][1].clan = 3, pmw[3][1].pz = 3, pmw[3][1].pj = 3, pmw[3][1].tp = _T("res\\学渣.jpg");
	pmw[3][2].race = _T("学霸"), pmw[3][2].ns = 3, pmw[3][2].clan = 3, pmw[3][2].pz = 5, pmw[3][2].pj = 5, pmw[3][2].tp = _T("res\\学霸.jpg");
	pmw[3][3].race = _T("学神"), pmw[3][3].ns = 3, pmw[3][3].clan = 3, pmw[3][3].pz = 7, pmw[3][3].pj = 7, pmw[3][3].tp = _T("res\\学神.jpg");

	//火焰鸡族
	mws[4].top = 12, mws[4].bs_pj = 4, mws[4].s_gj = 20, mws[4].s_fy = 6, mws[4].s_hp = 75, mws[4].s_sd = 12, mws[4].bjl = 15, mws[4].gdl = 5;
	pmw[4][1].race = _T("赤色鸡仔"), pmw[4][1].ns = 4, pmw[4][1].clan = 4, pmw[4][1].pz = 1, pmw[4][1].pj = 4, pmw[4][1].tp = _T("res\\赤色鸡仔.jpg");
	pmw[4][2].race = _T("赤色鸡"), pmw[4][2].ns = 3, pmw[4][2].clan = 4, pmw[4][2].pz = 1, pmw[4][2].pj = 5, pmw[4][2].tp = _T("res\\赤色鸡.jpg");
	pmw[4][3].race = _T("火焰鸡"), pmw[4][3].ns = 3, pmw[4][3].clan = 4, pmw[4][3].pz = 1, pmw[4][3].pj = 6, pmw[4][3].tp = _T("res\\火焰鸡.jpg");
	pmw[4][4].race = _T("火赤鸡"), pmw[4][4].ns = 3, pmw[4][4].clan = 4, pmw[4][4].pz = 1, pmw[4][4].pj = 7, pmw[4][4].tp = _T("res\\火赤鸡.jpg");
	pmw[4][5].race = _T("流火鸡"), pmw[4][5].ns = 3, pmw[4][5].clan = 4, pmw[4][5].pz = 1, pmw[4][5].pj = 8, pmw[4][5].tp = _T("res\\流火鸡.jpg");
	pmw[4][6].race = _T("流焰炽鸡"), pmw[4][6].ns = 4, pmw[4][6].clan = 4, pmw[4][6].pz = 1, pmw[4][6].pj = 9, pmw[4][6].tp = _T("res\\流焰炽鸡.jpg");
	pmw[4][7].race = _T("烈炎斗战鸡"), pmw[4][7].ns = 5, pmw[4][7].clan = 4, pmw[4][7].pz = 1, pmw[4][7].pj = 10, pmw[4][7].tp = _T("res\\烈炎斗战鸡.jpg");
	pmw[4][8].race = _T("狂炎.流炽斗鸡"), pmw[4][8].ns = 7, pmw[4][8].clan = 4, pmw[4][8].pz = 1, pmw[4][8].pj = 11, pmw[4][8].tp = _T("res\\狂炎.流炽斗鸡.jpg");
	pmw[4][9].race = _T("焱灭.地火皇鸡"), pmw[4][9].ns = 7, pmw[4][9].clan = 4, pmw[4][9].pz = 1, pmw[4][9].pj = 12, pmw[4][9].tp = _T("res\\焱灭.地火皇鸡.jpg");

	//蜈蚣族
	mws[5].top = 14, mws[5].bs_pj = 3, mws[5].s_gj = 15, mws[5].s_fy = 12, mws[5].s_hp = 105, mws[5].s_sd = 14, mws[5].bjl = 12, mws[5].gdl = 8;
	pmw[5][1].race = _T("甲壳蜈蚣"), pmw[5][1].ns = 4, pmw[5][1].clan = 5, pmw[5][1].pz = 1, pmw[5][1].pj = 3, pmw[5][1].tp = _T("res\\甲壳蜈蚣.jpg");
	pmw[5][2].race = _T("斑甲蜈蚣"), pmw[5][2].ns = 4, pmw[5][2].clan = 5, pmw[5][2].pz = 1, pmw[5][2].pj = 4, pmw[5][2].tp = _T("res\\斑甲蜈蚣.jpg");
	pmw[5][3].race = _T("斑甲毒蜈蚣"), pmw[5][3].ns = 5, pmw[5][3].clan = 5, pmw[5][3].pz = 1, pmw[5][3].pj = 5, pmw[5][3].tp = _T("res\\斑甲毒蜈蚣.jpg");
	pmw[5][4].race = _T("百足斑毒蜈"), pmw[5][4].ns = 5, pmw[5][4].clan = 5, pmw[5][4].pz = 1, pmw[5][4].pj = 6, pmw[5][4].tp = _T("res\\百足斑毒蜈.jpg");
	pmw[5][5].race = _T("千足紫毒蜈"), pmw[5][5].ns = 5, pmw[5][5].clan = 5, pmw[5][5].pz = 1, pmw[5][5].pj = 7, pmw[5][5].tp = _T("res\\千足紫毒蜈.jpg");
	pmw[5][6].race = _T("残毒戾紫蜈"), pmw[5][6].ns = 5, pmw[5][6].clan = 5, pmw[5][6].pz = 1, pmw[5][6].pj = 8, pmw[5][6].tp = _T("res\\残毒戾紫蜈.jpg");
	pmw[5][7].race = _T("腐毒电蜈"), pmw[5][7].ns = 4, pmw[5][7].clan = 5, pmw[5][7].pz = 1, pmw[5][7].pj = 9, pmw[5][7].tp = _T("res\\腐毒电蜈.jpg");
	pmw[5][8].race = _T("电闪蜈蚣"), pmw[5][8].ns = 4, pmw[5][8].clan = 5, pmw[5][8].pz = 1, pmw[5][8].pj = 10, pmw[5][8].tp = _T("res\\电闪蜈蚣.jpg");
	pmw[5][9].race = _T("雷霆紫电蜈"), pmw[5][9].ns = 5, pmw[5][9].clan = 5, pmw[5][9].pz = 1, pmw[5][9].pj = 11, pmw[5][9].tp = _T("res\\雷霆紫电蜈.jpg");
	pmw[5][10].race = _T("青玄雷蜈龙"), pmw[5][10].ns = 5, pmw[5][10].clan = 5, pmw[5][10].pz = 1, pmw[5][10].pj = 12, pmw[5][10].tp = _T("res\\青玄雷蜈龙.jpg");
	pmw[5][11].race = _T("紫元翼雷蜈龙"), pmw[5][11].ns = 6, pmw[5][11].clan = 5, pmw[5][11].pz = 1, pmw[5][11].pj = 13, pmw[5][11].tp = _T("res\\紫元翼雷蜈龙.jpg");
	pmw[5][12].race = _T("天苍.狂雷蜈龙"), pmw[5][12].ns = 6, pmw[5][12].clan = 5, pmw[5][12].pz = 1, pmw[5][12].pj = 14, pmw[5][12].tp = _T("res\\天苍.狂雷蜈龙.jpg");

	//水元素族
	mws[6].top = 9, mws[6].bs_pj = 1, mws[6].s_gj = 9, mws[6].s_fy = 9, mws[6].s_hp = 120, mws[6].s_sd = 15, mws[6].bjl = 3, mws[6].gdl = 12;
	pmw[6][1].race = _T("水怪"), pmw[6][1].ns = 3, pmw[6][1].clan = 6, pmw[6][1].pz = 1, pmw[6][1].pj = 1, pmw[6][1].tp = _T("res\\水怪.jpg");
	pmw[6][2].race = _T("水精"), pmw[6][2].ns = 3, pmw[6][2].clan = 6, pmw[6][2].pz = 1, pmw[6][2].pj = 2, pmw[6][2].tp = _T("res\\水精.jpg");
	pmw[6][3].race = _T("水中夜叉"), pmw[6][3].ns = 4, pmw[6][3].clan = 6, pmw[6][3].pz = 1, pmw[6][3].pj = 3, pmw[6][3].tp = _T("res\\水中夜叉.jpg");
	pmw[6][4].race = _T("水精灵"), pmw[6][4].ns = 3, pmw[6][4].clan = 6, pmw[6][4].pz = 1, pmw[6][4].pj = 4, pmw[6][4].tp = _T("res\\水精灵.jpg");
	pmw[6][5].race = _T("溪底守卫.水灵"), pmw[6][5].ns = 6, pmw[6][5].clan = 6, pmw[6][5].pz = 1, pmw[6][5].pj = 5, pmw[6][5].tp = _T("res\\溪底守卫.水灵.jpg");
	pmw[6][6].race = _T("湖塔护卫.水灵"), pmw[6][6].ns = 6, pmw[6][6].clan = 6, pmw[6][6].pz = 1, pmw[6][6].pj = 6, pmw[6][6].tp = _T("res\\湖塔护卫.水灵.jpg");
	pmw[6][7].race = _T("溪河清道夫"), pmw[6][7].ns = 5, pmw[6][7].clan = 6, pmw[6][7].pz = 1, pmw[6][7].pj = 7, pmw[6][7].tp = _T("res\\溪河清道夫.jpg");
	pmw[6][8].race = _T("深海领路者"), pmw[6][8].ns = 5, pmw[6][8].clan = 6, pmw[6][8].pz = 1, pmw[6][8].pj = 8, pmw[6][8].tp = _T("res\\深海领路者.jpg");
	pmw[6][9].race = _T("忘川吞噬者"), pmw[6][9].ns = 5, pmw[6][9].clan = 6, pmw[6][9].pz = 1, pmw[6][9].pj = 9, pmw[6][9].tp = _T("res\\忘川吞噬者.jpg");

}


void in_bok()		//录入召唤之书
{
	TCHAR ss[50];
	bks = GetPrivateProfileInt(_T("sy"), _T("bks"), 3, _T("data\\ZHZS.ini"));
	for (int i = 1; i <= bks; i++)
	{

		bool tf;	//本页是否有召唤兽
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

void open()			//开始页面
{
	loadimage(NULL, _T("res\\初始页面.jpg"), 1000, 600);
	settextcolor(RGB(0, 0, 0));
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)break;
	}
}

void main_page()	//主页面
{
	TCHAR ss[50];
	//保存
	outs();
	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);
	//总图标
	IMAGE jpg;				//录入图片的指针
	loadimage(&jpg, _T("res\\开始.jpg"), 1000, 600);
	putimage(0, 0, 1000, 600, &jpg, 0, 0);

	//玉石图标
	setfillcolor(RGB(60, 179, 113));
	fillrectangle(50, 10, 250, 40);
	settextcolor(RGB(0, 0, 0));
	settextstyle(26, 0, _T("楷体"));
	_stprintf(ss, _T("玉石：%d"), ys);
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

void bok(int k, int f)		//召唤之书页面
{
	while (1)
	{
		//保存
		outs();

		//排序
		for (int i = 1; i <= bks; i++)
			for (int j = i + 1; j <= bks; j++)
				if (pt[i].rsh != 0 && pt[j].rsh != 0 && pt[i].rsh > pt[j].rsh)
					swap(pt[i], pt[j]);
				else if (pt[i].rsh == 0 && pt[j].rsh != 0)
					swap(pt[i], pt[j]);

		//背景
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(0, i, 1000, i);

		//召唤兽图
		IMAGE jpg;				//录入图片的指针
		loadimage(&jpg, pmw[pt[k].clan][pt[k].race].tp, 400, 500);
		putimage(30, 20, 430, 520, &jpg, 0, 0);

		//是否上阵
		if (pt[k].rsh != 0)
		{
			loadimage(&jpg, _T("res\\已上阵.jpg"), 200, 120);
			putimage(680, 10, 200, 120, &jpg, 0, 0);
		}

		//当前页数
		TCHAR ss[50];
		_stprintf(ss, _T("page %d"), k);
		settextstyle(25, 0, _T("黑体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, 540, ss);

		//上一页/下一页
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(180, 540, 280, 570);
		settextstyle(16, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(182, 545, _T("上一页"));
		outtextxy(232, 545, _T("下一页"));
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

		//返回主页面图标
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(900, 530, 980, 580);
		settextstyle(30, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(910, 540, _T("返回"));

		//操作面板
		setfillcolor(RGB(210, 105, 30));
		for (int i = 1; i <= 6; i++)
			fillrectangle(890, 10 + (i - 1) * 60, 990, 70 + (i - 1) * 60);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(890, 10 + (f - 1) * 60, 990, 70 + (f - 1) * 60);
		setfillcolor(RGB(192, 192, 192));
		fillrectangle(890, 250, 990, 310);
		fillrectangle(890, 310, 990, 370);
		settextstyle(30, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(910, 25, _T("属性"));
		outtextxy(910, 85, _T("升级"));
		outtextxy(910, 145, _T("升阶"));
		outtextxy(910, 205, _T("魂炼"));
		outtextxy(910, 265, _T("培质"));
		outtextxy(910, 325, _T("羁绊"));

		if (f == 1)
		{
			TCHAR ss[50];
			settextstyle(32, 0, _T("楷体"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(500, 60, _T("种:"));
			outtextxy(545, 60, pmw[pt[k].clan][pt[k].race].race);
			outtextxy(500, 100, _T("族:"));
			outtextxy(545, 100, CLAN[pt[k].clan]);
			outtextxy(500, 140, _T("品级:"));
			outtextxy(580, 140, PJ[pt[k].pj]);
			outtextxy(690, 140, _T("品质:"));
			outtextxy(770, 140, PZ[pt[k].pz]);
			_stprintf(ss, _T("等级:%d"), pt[k].dj);
			outtextxy(500, 180, ss);
			_stprintf(ss, _T("魂炼:%d"), pt[k].srd);
			outtextxy(620, 180, ss);
			_stprintf(ss, _T("生命:%d"), pt[k].s_hp);
			outtextxy(500, 250, ss);
			_stprintf(ss, _T("攻击:%d"), pt[k].s_gj);
			outtextxy(500, 290, ss);
			_stprintf(ss, _T("防御:%d"), pt[k].s_fy);
			outtextxy(500, 330, ss);
			_stprintf(ss, _T("速度:%d"), pt[k].s_sd);
			outtextxy(670, 250, ss);
			_stprintf(ss, _T("暴击率:%d %%"), pt[k].bjl);
			outtextxy(670, 290, ss);
			_stprintf(ss, _T("格挡率:%d %%"), pt[k].gdl);
			outtextxy(670, 330, ss);
			settextstyle(32, 0, _T("楷体"));
			settextcolor(RGB(255, 0, 0));
			_stprintf(ss, _T("战力:%d"), pt[k].s_zl);
			outtextxy(500, 460, ss);
		}
		if (f == 2 && pt[k].clan != 0) sg_page(k);
		if (f == 3 && pt[k].clan != 0) rh_page(k);
		if (f == 4 && pt[k].clan != 0) hl_page(k);

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//返回主页面
					main_page();
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//上一页
				{
					k--;
					break;
				}
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//下一页
				{
					k++;
					break;
				}
				bool rl = 0;
				for (int i = 1; i <= 4; i++)		//更换培养选项
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

void ele(int k)		//探索
{
	//保存
	outs();

	//更新位置
	now_where = k;

	//背景
	IMAGE jpg;				//录入图片的指针
	loadimage(&jpg, place[k].tp, 1000, 600);
	putimage(0, 0, 1000, 600, &jpg, 0, 0);

	//主页面
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(600, 520, 700, 570);
	settextstyle(30, 0, _T("宋体"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(620, 530, _T("返回"));

	//地图
	loadimage(&jpg, _T("res\\地图.jpg"), 150, 120);
	putimage(800, 20, 150, 120, &jpg, 0, 0);
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, _T("黑体"));
	outtextxy(860, 150, _T("地图"));

	//当前可见地点
	vector<int> x;
	for (int i = 0; i < mp[k].size(); i++)
		if (random(1, 100) <= place[mp[k][i]].gl)
			x.push_back(mp[k][i]);

	//地点图标
	settextcolor(RGB(0, 0, 0));
	settextstyle(32, 0, _T("宋体"));
	outtextxy(50, 30, place[k].name);
	for (int i = 0; i < x.size(); i++)
	{
		if (place[x[i]].gl == 100) setfillcolor(RGB(0, 255, 0));
		else setfillcolor(RGB(147, 112, 219));
		fillrectangle(100 + 120 * i, 80, 200 + 120 * i, 130);
		settextstyle(80 / place[x[i]].ns, 40 / place[x[i]].ns, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(105 + 120 * i, 90, place[x[i]].name);
	}

	//战斗图标
	setfillcolor(RGB(210, 105, 30));
	fillrectangle(100, 200, 200, 250);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(120, 210, _T("战斗"));

	//刷怪图标
	setfillcolor(RGB(210, 105, 30));
	fillrectangle(230, 200, 330, 250);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(250, 210, _T("刷怪"));

	//野生魔物图标
	for (int i = 1; i <= ceil((double)sob[k].size() / (double)7); i++)
	{
		for (int j = 0; j < min(7, sob[k].size() - (i - 1) * 7); j++)
		{
			setfillcolor(RGB(255, 0, 0));
			fillrectangle(100 + 120 * j, 200 + i * 80, 200 + 120 * j, 260 + i * 80);
			settextstyle(80 / pmw[sob[k][(i - 1) * 7 + j].clan][sob[k][(i - 1) * 7 + j].race].ns, 40 / pmw[sob[k][(i - 1) * 7 + j].clan][sob[k][(i - 1) * 7 + j].race].ns, _T("宋体"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(105 + 120 * j, 220 + i * 80, pmw[sob[k][(i - 1) * 7 + j].clan][sob[k][(i - 1) * 7 + j].race].race);
		}
	}

	//选择
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

			//单挑
			for (int i = 1; i <= ceil((double)sob[k].size() / (double)7); i++)
				for (int j = 0; j < min(7, sob[k].size() - (i - 1) * 7); j++)
					if (100 + 120 * j <= m.x && m.x <= 200 + 120 * j && 200 + 80 * i <= m.y && m.y <= 260 + 80 * i)
						if (lor_mw(k, sob[k][j + (i - 1) * 7]))
						{
							TBOC R[3];
							R[1] = sob[k][j + (i - 1) * 7];
							if (!cs_page(1, PvE(R, 1, 1)))
							{
								//魔物掉落物品
								mw_lt(sob[k][j + (i - 1) * 7].clan, sob[k][j + (i - 1) * 7].race, sob[k][j + (i - 1) * 7].pz, sob[k][j + (i - 1) * 7].dj);

								//更新魔物
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

			//集体对决
			if (100 <= m.x && m.x <= 200 && 200 <= m.y && m.y <= 250 && sob[k].size() > 0)
			{
				TBOC R[30];
				for (int i = 1; i <= min(6, sob[k].size()); i++)
					R[i] = sob[k][i - 1];
				if (!cs_page(1, PvE(R, min(6, sob[k].size()), 6)))
				{
					//魔物掉落物品
					for (int i = 1; i <= min(6, sob[k].size()); i++)
						mw_lt(sob[k][i - 1].clan, sob[k][i - 1].race, sob[k][i - 1].pz, sob[k][i - 1].dj);

					//更新魔物
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

void cl_map()		//初始化探索之路
{
	tsl = 36;
	place[1].name = _T("家园"), place[1].ns = 3, place[1].gl = 100, place[1].tp = _T("res\\家园.jpg");
	place[2].name = _T("城市东郊"), place[2].ns = 4, place[2].gl = 100, place[2].tp = _T("res\\城市东郊.jpg");
	place[3].name = _T("城市南郊"), place[3].ns = 4, place[3].gl = 100, place[3].tp = _T("res\\城市南郊.jpg");
	place[4].name = _T("城市西郊"), place[4].ns = 4, place[4].gl = 100, place[4].tp = _T("res\\城市西郊.jpg");
	place[5].name = _T("城市北郊"), place[5].ns = 4, place[5].gl = 100, place[5].tp = _T("res\\城市北郊.jpg");
	place[6].name = _T("林幽径"), place[6].ns = 3, place[6].gl = 100, place[6].tp = _T("res\\林幽径.jpg");
	place[7].name = _T("阳湖"), place[7].ns = 3, place[7].gl = 15, place[7].tp = _T("res\\阳湖.jpg");
	place[8].name = _T("铜腰山脚"), place[8].ns = 4, place[8].gl = 100, place[8].tp = _T("res\\铜腰山脚.jpg");
	place[9].name = _T("铜腰山南山腰"), place[9].ns = 6, place[9].gl = 100, place[9].tp = _T("res\\铜腰山南山腰.jpg");
	place[10].name = _T("狗头山洞"), place[10].ns = 4, place[10].gl = 10, place[10].tp = _T("res\\狗头山洞.jpg");
	place[11].name = _T("云岭山"), place[11].ns = 3, place[11].gl = 100, place[11].tp = _T("res\\云岭山.jpg");
	place[12].name = _T("灵石洞"), place[12].ns = 3, place[12].gl = 100, place[12].tp = _T("res\\灵石洞.jpg");
	place[13].name = _T("熔岩禁区"), place[13].ns = 4, place[13].gl = 100, place[13].tp = _T("res\\熔岩禁区.jpg");
	place[14].name = _T("地狱火山"), place[14].ns = 4, place[14].gl = 100, place[14].tp = _T("res\\地狱火山.jpg");
	place[15].name = _T("地狱火山口"), place[15].ns = 5, place[15].gl = 100, place[15].tp = _T("res\\地狱火山口.jpg");
	place[16].name = _T("参天五指山"), place[16].ns = 5, place[16].gl = 10, place[16].tp = _T("res\\参天五指山.jpg");
	place[17].name = _T("晨希湖"), place[17].ns = 3, place[17].gl = 100, place[17].tp = _T("res\\晨希湖.jpg");
	place[18].name = _T("草海"), place[18].ns = 3, place[18].gl = 100, place[18].tp = _T("res\\草海.jpg");
	place[19].name = _T("湖底"), place[19].ns = 3, place[19].gl = 100, place[19].tp = _T("res\\湖底.jpg");
	place[20].name = _T("芦苇丛"), place[20].ns = 3, place[20].gl = 100, place[20].tp = _T("res\\芦苇丛.jpg");
	place[21].name = _T("芦花荡"), place[21].ns = 3, place[21].gl = 5, place[21].tp = _T("res\\芦花荡.jpg");
	place[22].name = _T("十三里桥"), place[22].ns = 4, place[22].gl = 100, place[22].tp = _T("res\\十三里桥.jpg");
	place[23].name = _T("暗溪"), place[23].ns = 3, place[23].gl = 15, place[23].tp = _T("res\\暗溪.jpg");
	place[24].name = _T("湖底金字塔"), place[24].ns = 5, place[24].gl = 100, place[24].tp = _T("res\\湖底金字塔.jpg");
	place[25].name = _T("湖底密洞"), place[25].ns = 4, place[25].gl = 10, place[25].tp = _T("res\\湖底密洞.jpg");
	place[26].name = _T("密道"), place[26].ns = 3, place[26].gl = 100, place[26].tp = _T("res\\密道.jpg");
	place[27].name = _T("烟雨村"), place[27].ns = 3, place[27].gl = 30, place[27].tp = _T("res\\烟雨村.jpg");
	place[28].name = _T("竹影村"), place[28].ns = 3, place[28].gl = 25, place[28].tp = _T("res\\竹影村.jpg");
	place[29].name = _T("蔓林道"), place[29].ns = 3, place[29].gl = 20, place[29].tp = _T("res\\蔓林道.jpg");
	place[30].name = _T("烟雨山"), place[30].ns = 3, place[30].gl = 100, place[30].tp = _T("res\\烟雨山.jpg");
	place[31].name = _T("霜雪坡"), place[31].ns = 3, place[31].gl = 100, place[31].tp = _T("res\\霜雪坡.jpg");
	place[32].name = _T("冰雨村"), place[32].ns = 3, place[32].gl = 10, place[32].tp = _T("res\\冰雨村.jpg");
	place[33].name = _T("极地圣山"), place[33].ns = 4, place[33].gl = 100, place[33].tp = _T("res\\极地圣山.jpg");
	place[34].name = _T("冰与火双极"), place[34].ns = 5, place[34].gl = 10, place[34].tp = _T("res\\冰与火双极.jpg");
	place[35].name = _T("岩浆涌源地"), place[35].ns = 5, place[35].gl = 15, place[35].tp = _T("res\\岩浆涌源地.jpg");
	place[36].name = _T("狗头山岭"), place[36].ns = 4, place[36].gl = 100, place[36].tp = _T("res\\狗头山岭.jpg");

	KMW x;

	x.clan = 1, x.rl = 1, x.rh = 1, x.pzl = 1, x.pzh = 1, x.djl = 0, x.djh = 0, x.srl = 0, x.srh = 0, kmw[1].push_back(x);//家园

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[2].push_back(x);//东郊
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[2].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[2].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[3].push_back(x);//南郊
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[3].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[3].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[4].push_back(x);//西郊
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[4].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[4].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[5].push_back(x);//北郊
	x.clan = 2, x.rl = 1, x.rh = 3, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[5].push_back(x);
	x.clan = 5, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 2, x.djl = 1, x.djh = 10, x.srl = 0, x.srh = 0, kmw[5].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[6].push_back(x);//林幽径
	x.clan = 5, x.rl = 3, x.rh = 6, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[6].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[7].push_back(x);//阳湖
	x.clan = 3, x.rl = 1, x.rh = 1, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[7].push_back(x);
	x.clan = 5, x.rl = 3, x.rh = 6, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[7].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[8].push_back(x);//铜腰山脚
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[8].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[9].push_back(x);//铜腰山南山腰
	x.clan = 2, x.rl = 4, x.rh = 8, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[9].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[10].push_back(x);//狗头山洞
	x.clan = 2, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[10].push_back(x);
	x.clan = 5, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[10].push_back(x);

	x.clan = 1, x.rl = 4, x.rh = 6, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[11].push_back(x);//云岭山
	x.clan = 2, x.rl = 1, x.rh = 4, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[11].push_back(x);

	x.clan = 1, x.rl = 4, x.rh = 6, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[12].push_back(x);//灵石洞
	x.clan = 2, x.rl = 2, x.rh = 6, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[12].push_back(x);

	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[13].push_back(x);//熔岩禁区
	x.clan = 4, x.rl = 1, x.rh = 4, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[13].push_back(x);

	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[14].push_back(x);//地狱火山
	x.clan = 4, x.rl = 3, x.rh = 6, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[14].push_back(x);

	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[15].push_back(x);//地狱火山口

	x.clan = 1, x.rl = 8, x.rh = 14, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);//参天五指山
	x.clan = 2, x.rl = 8, x.rh = 12, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);
	x.clan = 3, x.rl = 2, x.rh = 2, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);
	x.clan = 4, x.rl = 6, x.rh = 9, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[16].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[17].push_back(x);//晨希湖
	x.clan = 4, x.rl = 2, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[17].push_back(x);
	x.clan = 6, x.rl = 1, x.rh = 6, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[17].push_back(x);

	x.clan = 1, x.rl = 5, x.rh = 8, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[18].push_back(x);//草海
	x.clan = 6, x.rl = 3, x.rh = 8, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[18].push_back(x);

	x.clan = 6, x.rl = 4, x.rh = 8, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[19].push_back(x);//湖底

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[20].push_back(x);//芦苇丛

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[21].push_back(x);//芦花荡
	x.clan = 6, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[21].push_back(x);

	x.clan = 1, x.rl = 4, x.rh = 9, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[22].push_back(x);//十三里桥

	x.clan = 6, x.rl = 5, x.rh = 9, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[23].push_back(x);//暗溪

	x.clan = 6, x.rl = 6, x.rh = 9, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[24].push_back(x);//湖底金字塔

	x.clan = 3, x.rl = 1, x.rh = 1, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[25].push_back(x);//湖底密洞
	x.clan = 5, x.rl = 4, x.rh = 8, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[25].push_back(x);
	x.clan = 6, x.rl = 4, x.rh = 9, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[25].push_back(x);

	x.clan = 2, x.rl = 1, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[26].push_back(x);//密道

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[27].push_back(x);//烟雨村
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[27].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[28].push_back(x);//竹影村
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[28].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 8, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[29].push_back(x);//蔓林道
	x.clan = 5, x.rl = 3, x.rh = 7, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[29].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 5, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[30].push_back(x);//烟雨山
	x.clan = 2, x.rl = 3, x.rh = 7, x.pzl = 1, x.pzh = 3, x.djl = 5, x.djh = 10, x.srl = 6, x.srh = 10, kmw[30].push_back(x);

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 2, x.pzh = 4, x.djl = 5, x.djh = 10, x.srl = 16, x.srh = 20, kmw[31].push_back(x);//霜雪坡

	x.clan = 1, x.rl = 1, x.rh = 5, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[32].push_back(x);//冰雨村

	x.clan = 2, x.rl = 5, x.rh = 6, x.pzl = 4, x.pzh = 6, x.djl = 5, x.djh = 10, x.srl = 36, x.srh = 40, kmw[33].push_back(x);//极地圣山

	x.clan = 1, x.rl = 10, x.rh = 16, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);//冰与火双极
	x.clan = 2, x.rl = 5, x.rh = 8, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);
	x.clan = 3, x.rl = 3, x.rh = 3, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);
	x.clan = 4, x.rl = 5, x.rh = 8, x.pzl = 6, x.pzh = 8, x.djl = 5, x.djh = 10, x.srl = 56, x.srh = 60, kmw[34].push_back(x);

	x.clan = 2, x.rl = 5, x.rh = 7, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[35].push_back(x);//岩浆涌源地
	x.clan = 4, x.rl = 3, x.rh = 6, x.pzl = 5, x.pzh = 7, x.djl = 5, x.djh = 10, x.srl = 46, x.srh = 50, kmw[35].push_back(x);

	x.clan = 1, x.rl = 3, x.rh = 8, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[36].push_back(x);//狗头山岭
	x.clan = 4, x.rl = 1, x.rh = 3, x.pzl = 3, x.pzh = 5, x.djl = 5, x.djh = 10, x.srl = 26, x.srh = 30, kmw[36].push_back(x);


	mp[1].push_back(2);			//家->城市东郊
	mp[1].push_back(3);			//家->城市南郊
	mp[1].push_back(4);			//家->城市西郊
	mp[1].push_back(5);			//家->城市北郊

	mp[2].push_back(1);			//城市东郊->家
	mp[2].push_back(27);		//城市东郊->烟雨村

	mp[3].push_back(1);			//城市南郊->家
	mp[3].push_back(11);		//城市南郊->云岭山

	mp[4].push_back(1);			//城市西郊->家
	mp[4].push_back(17);		//城市西郊->晨希湖

	mp[5].push_back(1);			//城市北郊->家
	mp[5].push_back(6);			//城市北郊->林幽径
	mp[5].push_back(8);			//城市北郊->铜腰山脚

	mp[6].push_back(5);			//林幽径->城市北郊
	mp[6].push_back(7);			//林幽径->阳湖
	mp[6].push_back(8);			//林幽径->铜腰山脚
	mp[6].push_back(29);		//林幽径->蔓林道

	mp[7].push_back(6);			//阳湖->林幽径
	mp[7].push_back(23);		//阳湖->暗溪

	mp[8].push_back(5);			//铜腰山脚->城市北郊
	mp[8].push_back(6);			//铜腰山脚->林幽径
	mp[8].push_back(9);			//铜腰山脚->铜腰山南山腰

	mp[9].push_back(8);			//铜腰山南山腰->铜腰山脚
	mp[9].push_back(36);		//铜腰山南山腰->狗头山岭

	mp[10].push_back(36);		//狗头山洞->狗头山岭

	mp[11].push_back(3);		//云岭山->城市南郊
	mp[11].push_back(12);		//云岭山->灵石洞
	mp[11].push_back(15);		//云岭山->地狱火山口

	mp[12].push_back(11);		//灵石洞->云岭山
	mp[12].push_back(13);		//灵石洞->熔岩禁区
	mp[12].push_back(15);		//灵石洞->地狱火山口
	mp[12].push_back(16);		//灵石洞->参天五指山

	mp[13].push_back(12);		//熔岩禁区->灵石洞
	mp[13].push_back(14);		//熔岩禁区->地狱火山口

	mp[14].push_back(13);		//地狱火山口->熔岩禁区
	mp[14].push_back(15);		//地狱火山口->地狱火山
	mp[14].push_back(35);		//地狱火山口->岩浆涌源地

	mp[15].push_back(11);		//地狱火山->云岭山
	mp[15].push_back(12);		//地狱火山->灵石洞
	mp[15].push_back(14);		//地狱火山->地狱火山口

	mp[16].push_back(12);		//参天五指山->灵石洞
	mp[16].push_back(26);		//参天五指山->密道

	mp[17].push_back(4);		//晨希湖->西郊
	mp[17].push_back(18);		//晨希湖->草海
	mp[17].push_back(19);		//晨希湖->湖底
	mp[17].push_back(20);		//晨希湖->芦苇丛

	mp[18].push_back(17);		//草海->晨希湖
	mp[18].push_back(19);		//草海->湖底
	mp[18].push_back(20);		//草海->芦苇丛

	mp[19].push_back(17);		//湖底->晨希湖
	mp[19].push_back(18);		//湖底->草海
	mp[19].push_back(20);		//湖底->芦苇丛
	mp[19].push_back(24);		//湖底->湖底金字塔

	mp[20].push_back(17);		//芦苇丛->晨希湖
	mp[20].push_back(18);		//芦苇丛->草海
	mp[20].push_back(19);		//芦苇丛->湖底
	mp[20].push_back(21);		//芦苇丛->芦花荡

	mp[21].push_back(20);		//芦花荡->芦苇丛
	mp[21].push_back(22);		//芦花荡->十三里桥

	mp[22].push_back(21);		//十三里桥->芦花荡
	mp[22].push_back(23);		//十三里桥->暗溪

	mp[23].push_back(7);		//暗溪->阳湖
	mp[23].push_back(22);		//暗溪->十三里桥

	mp[24].push_back(19);		//湖底金字塔->湖底
	mp[24].push_back(25);		//湖底金字塔->湖底密洞

	mp[25].push_back(24);		//湖底密洞->湖底金字塔
	mp[25].push_back(26);		//湖底密洞->密道

	mp[26].push_back(16);		//密道->参天五指山
	mp[26].push_back(25);		//密道->湖底密洞

	mp[27].push_back(2);		//烟雨村->东郊
	mp[27].push_back(28);		//烟雨村->竹影村
	mp[27].push_back(30);		//烟雨村->烟雨山

	mp[28].push_back(27);		//竹影村->烟雨村
	mp[28].push_back(29);		//竹影村->蔓林道
	mp[28].push_back(30);		//竹影村->烟雨山

	mp[29].push_back(6);		//蔓林道->林幽径
	mp[29].push_back(28);		//蔓林道->竹影村

	mp[30].push_back(27);		//烟雨山->烟雨村
	mp[30].push_back(28);		//烟雨山->竹影村
	mp[30].push_back(31);		//烟雨山->霜雪坡

	mp[31].push_back(30);		//霜雪坡->烟雨山
	mp[31].push_back(32);		//霜雪坡->冰雨村

	mp[32].push_back(31);		//冰雨村->霜雪坡
	mp[32].push_back(33);		//冰雨村->极地圣山

	mp[33].push_back(32);		//极地圣山->冰雨村
	mp[33].push_back(34);		//极地圣山->火与冰双极

	mp[34].push_back(33);		//火与冰双极->极地圣山
	mp[34].push_back(35);		//火与冰双极->岩浆涌源地

	mp[35].push_back(14);		//岩浆涌源地->地狱火山
	mp[35].push_back(34);		//岩浆涌源地->火与冰双极

	mp[36].push_back(9);		//铜腰山南山腰
	mp[36].push_back(10);		//狗头山洞

}

void cl_ts(int z)				//刷新探索之路魔物
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

	//保存
	outs();
}

bool PvE(TBOC E[], int tot, int tos)		//对战机器
{
	int r = random(0, 1);		//判断先手
	int pd;						//判断结果
	int xxs = 0;				//消息数量
	int f1 = 1, f2 = 1;			//我方、敌方首只存活位置
	int hhs = 0;					//回合数
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
			settextstyle(30, 0, _T("黑体"));
			_stprintf(ss, _T("第 %d 回合"), hhs);
			outtextxy(400, 5, ss);
			xxs = 0;

			//玩家
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
					settextstyle(30, 0, _T("黑体"));
					_stprintf(ss, _T("第 %d 回合"), hhs);
					outtextxy(400, 5, ss);
				}
				settextcolor(RGB(0, 0, 255));
				settextstyle(16, 0, _T("宋体"));
				if (sbrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，敌方闪避了"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("我方%s攻击敌方%s，造成伤害%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，我方暴击，造成伤害%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，敌方格挡，造成伤害%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}

				Sleep(300);
			}

			//电脑
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
					settextstyle(30, 0, _T("黑体"));
					_stprintf(ss, _T("第 %d 回合"), hhs);
					outtextxy(400, 5, ss);
				}

				settextcolor(RGB(255, 0, 0));
				settextstyle(16, 0, _T("宋体"));
				if (sbrl == 1)
					_stprintf(ss, _T("敌方%s攻击我方%s，敌方闪避了"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("敌方%s攻击我方%s，造成伤害%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，我方暴击，造成伤害%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，敌方格挡，造成伤害%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
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
			settextstyle(30, 0, _T("黑体"));
			_stprintf(ss, _T("第 %d 回合"), hhs);
			outtextxy(400, 5, ss);
			xxs = 0;

			//电脑
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
					settextstyle(30, 0, _T("黑体"));
					_stprintf(ss, _T("第 %d 回合"), hhs);
					outtextxy(400, 5, ss);
				}
				settextcolor(RGB(255, 0, 0));
				settextstyle(16, 0, _T("宋体"));
				if (sbrl == 1)
					_stprintf(ss, _T("敌方%s攻击我方%s，敌方闪避了"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("敌方%s攻击我方%s，造成伤害%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，我方暴击，造成伤害%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，敌方格挡，造成伤害%d"), pmw[E[i].clan][E[i].race].race, pmw[P[f1].clan][P[f1].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}
				Sleep(300);
			}

			//玩家
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
					settextstyle(30, 0, _T("黑体"));
					_stprintf(ss, _T("第 %d 回合"), hhs);
					outtextxy(400, 5, ss);
				}
				settextcolor(RGB(0, 0, 255));
				settextstyle(16, 0, _T("宋体"));
				if (sbrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，敌方闪避了"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race);
				else if (bjrl == gdrl)
					_stprintf(ss, _T("我方%s攻击敌方%s，造成伤害%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (bjrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，我方暴击，造成伤害%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				else if (gdrl == 1)
					_stprintf(ss, _T("我方%s攻击敌方%s，敌方格挡，造成伤害%d"), pmw[P[i].clan][P[i].race].race, pmw[E[f2].clan][E[f2].race].race, max(1, gj - fy));
				outtextxy(280, 50 + 30 * xxs, ss);
				xxs++;
				for (int ks = 0; ks <= 600; ks++)
					line(0, ks, 270, ks), line(750, ks, 1000, ks);
				for (int ks = 1; ks <= tos; ks++)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[P[ks].clan][P[ks].race].race, P[ks].s_hp);
					outtextxy(20, 15 + ks * 30, ss);
				}
				for (int ks = 1; ks <= tot; ks++)
				{
					settextcolor(RGB(255, 0, 0));
					settextstyle(25, 0, _T("楷体"));
					_stprintf(ss, _T("%s：%d"), pmw[E[ks].clan][E[ks].race].race, E[ks].s_hp);
					outtextxy(770, 15 + ks * 30, ss);
				}
				Sleep(300);
			}
		}
}

bool cs_page(int z, bool r)		//结算页面
{
	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//判断输出
	if (z == 1)		//结算战斗
	{
		settextcolor(RGB(0, 0, 0));
		settextstyle(200, 0, _T("宋体"));
		if (r) outtextxy(100, 200, _T("战斗失败"));
		else outtextxy(100, 200, _T("战斗胜利"));
		Sleep(1500);
	}
	if (z == 2)
	{
		settextcolor(RGB(0, 0, 0));
		settextstyle(200, 0, _T("宋体"));
		if (r) outtextxy(100, 200, _T("使用成功"));
		else outtextxy(100, 200, _T("使用失败"));
		Sleep(1500);
	}
	//返回
	return r;
}

void cc_page()			//仓库页面
{
	int mps, ps = 1;
	while (1)
	{
		//保存
		outs();

		//背景
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(0, i, 1000, i);
		settextcolor(RGB(0, 0, 0));
		settextstyle(32, 0, _T("宋体"));
		outtextxy(50, 30, _T("背包页"));

		//更新仓库物品
		vector<CK> x;
		for (int i = 0; i < cwp.size(); i++)
			if (cwp[i].sum > 0)
				x.push_back(cwp[i]);
		cwp.clear();
		for (int i = 0; i < x.size(); i++)
			cwp.push_back(x[i]);

		mps = ceil((double)cwp.size() / (double)20.0);

		//物品图标
		for (int i = 1; i <= min(ceil(((double)cwp.size() - (ps - 1) * 20) / (double)5), 4); i++)
		{
			for (int j = 0; j < min(5, cwp.size() - (ps - 1) * 20 - (i - 1) * 5); j++)
			{
				setfillcolor(RGB(255, 250, 205));
				fillrectangle(50 + 180 * j, 100 * i, 220 + 180 * j, 80 + 100 * i);
				settextstyle(160 / thing[cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wz][cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wt].ns, 80 / thing[cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wz][cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wt].ns, _T("宋体"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(55 + 180 * j, 10 + 100 * i, thing[cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wz][cwp[(ps - 1) * 20 + (i - 1) * 5 + j].wt].name);
				settextstyle(20, 0, _T("宋体"));
				TCHAR ss[50];
				_stprintf(ss, _T("X %d"), cwp[(ps - 1) * 20 + (i - 1) * 5 + j].sum);
				outtextxy(150 + 180 * j, 50 + 100 * i, ss);
			}
		}

		//返回主页面
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(850, 500, 950, 550);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(870, 510, _T("返回"));

		//上一页/下一页
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(180, 540, 280, 570);
		settextstyle(16, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(182, 545, _T("上一页"));
		outtextxy(232, 545, _T("下一页"));
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

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (850 <= m.x && m.x <= 950 && 500 <= m.y && m.y <= 550)
					main_page();

				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && ps > 1)	//上一页
				{
					ps--;
					break;
				}
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && ps < mps)	//下一页
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

bool lor_mw(int f, TBOC k)			//查看探索之路怪物属性
{
	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//召唤兽图
	IMAGE jpg;				//录入图片的指针
	loadimage(&jpg, pmw[k.clan][k.race].tp, 400, 500);
	putimage(100, 50, 500, 550, &jpg, 0, 0);

	//数值
	TCHAR ss[50];
	settextstyle(32, 0, _T("楷体"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(550, 60, _T("种:"));
	outtextxy(590, 60, pmw[k.clan][k.race].race);
	outtextxy(550, 100, _T("族:"));
	outtextxy(590, 100, CLAN[k.clan]);
	outtextxy(550, 140, _T("品级:"));
	outtextxy(630, 140, PJ[k.pj]);
	outtextxy(740, 140, _T("品质:"));
	outtextxy(820, 140, PZ[k.pz]);
	_stprintf(ss, _T("等级:%d"), k.dj);
	outtextxy(550, 180, ss);
	_stprintf(ss, _T("魂炼:%d"), k.srd);
	outtextxy(670, 180, ss);
	_stprintf(ss, _T("生命:%d"), k.s_hp);
	outtextxy(550, 250, ss);
	_stprintf(ss, _T("攻击:%d"), k.s_gj);
	outtextxy(550, 290, ss);
	_stprintf(ss, _T("防御:%d"), k.s_fy);
	outtextxy(550, 330, ss);
	_stprintf(ss, _T("速度:%d"), k.s_sd);
	outtextxy(720, 250, ss);
	_stprintf(ss, _T("暴击率:%d %%"), k.bjl);
	outtextxy(720, 290, ss);
	_stprintf(ss, _T("格挡率:%d %%"), k.gdl);
	outtextxy(720, 330, ss);
	settextstyle(32, 0, _T("楷体"));
	settextcolor(RGB(255, 0, 0));
	_stprintf(ss, _T("战力:%d"), k.s_zl);
	outtextxy(550, 400, ss);

	//返回图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 500, 980, 550);
	settextstyle(30, 0, _T("宋体"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(910, 510, _T("返回"));

	//单挑图标
	setfillcolor(RGB(255, 0, 0));
	fillrectangle(600, 500, 700, 550);
	settextstyle(30, 0, _T("宋体"));
	settextcolor(RGB(0, 0, 0));
	outtextxy(620, 510, _T("单挑"));

	//选择
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

void cl_wp()		//初始化物品图鉴
{
	//精魄
	wpls[1] = 58;
	thing[1][1].name = _T("哥布林精魄"), thing[1][1].ns = 5, thing[1][1].bh_z = 1, thing[1][1].bh_j = 1, thing[1][1].b_jg = 30, thing[1][1].s_jg = 9;
	thing[1][2].name = _T("大哥布林精魄"), thing[1][2].ns = 6, thing[1][2].bh_z = 1, thing[1][2].bh_j = 2, thing[1][2].b_jg = 60, thing[1][2].s_jg = 18;
	thing[1][3].name = _T("哥布林勇士精魄"), thing[1][3].ns = 7, thing[1][3].bh_z = 1, thing[1][3].bh_j = 3, thing[1][3].b_jg = 120, thing[1][3].s_jg = 36;
	thing[1][4].name = _T("哥布林酋长精魄"), thing[1][4].ns = 7, thing[1][4].bh_z = 1, thing[1][4].bh_j = 4, thing[1][4].b_jg = 240, thing[1][4].s_jg = 72;
	thing[1][5].name = _T("哥布林大酋长精魄"), thing[1][5].ns = 8, thing[1][5].bh_z = 1, thing[1][5].bh_j = 5, thing[1][5].b_jg = 480, thing[1][5].s_jg = 144;
	thing[1][6].name = _T("哥布林祭师精魄"), thing[1][6].ns = 7, thing[1][6].bh_z = 1, thing[1][6].bh_j = 6, thing[1][6].b_jg = 960, thing[1][6].s_jg = 288;
	thing[1][7].name = _T("哥布林主祭精魄"), thing[1][7].ns = 7, thing[1][7].bh_z = 1, thing[1][7].bh_j = 7, thing[1][7].b_jg = 1920, thing[1][7].s_jg = 576;
	thing[1][8].name = _T("哥布林首领精魄"), thing[1][8].ns = 7, thing[1][8].bh_z = 1, thing[1][8].bh_j = 8, thing[1][8].b_jg = 3840, thing[1][8].s_jg = 1152;
	thing[1][9].name = _T("血冠哥布林精魄"), thing[1][9].ns = 7, thing[1][9].bh_z = 1, thing[1][9].bh_j = 10, thing[1][9].b_jg = 7680, thing[1][9].s_jg = 2304;
	thing[1][10].name = _T("血暗荆棘哥布林精魄"), thing[1][10].ns = 9, thing[1][10].bh_z = 1, thing[1][10].bh_j = 11, thing[1][10].b_jg = 15360, thing[1][10].s_jg = 4608;
	thing[1][11].name = _T("石子怪精魄"), thing[1][11].ns = 5, thing[1][11].bh_z = 2, thing[1][11].bh_j = 1, thing[1][11].b_jg = 70, thing[1][11].s_jg = 21;
	thing[1][12].name = _T("小石人精魄"), thing[1][12].ns = 5, thing[1][12].bh_z = 2, thing[1][12].bh_j = 2, thing[1][12].b_jg = 140, thing[1][12].s_jg = 42;
	thing[1][13].name = _T("石头人精魄"), thing[1][13].ns = 5, thing[1][13].bh_z = 2, thing[1][13].bh_j = 3, thing[1][13].b_jg = 280, thing[1][13].s_jg = 84;
	thing[1][14].name = _T("巨岩石人精魄"), thing[1][14].ns = 6, thing[1][14].bh_z = 2, thing[1][14].bh_j = 4, thing[1][14].b_jg = 560, thing[1][14].s_jg = 168;
	thing[1][15].name = _T("戈仑石人精魄"), thing[1][15].ns = 6, thing[1][15].bh_z = 2, thing[1][15].bh_j = 5, thing[1][15].b_jg = 1120, thing[1][15].s_jg = 336;
	thing[1][16].name = _T("戈仑岩晶精魄"), thing[1][16].ns = 6, thing[1][16].bh_z = 2, thing[1][16].bh_j = 6, thing[1][16].b_jg = 2240, thing[1][16].s_jg = 672;
	thing[1][17].name = _T("熔岩石怪精魄"), thing[1][17].ns = 6, thing[1][17].bh_z = 2, thing[1][17].bh_j = 9, thing[1][17].b_jg = 4480, thing[1][17].s_jg = 9216;
	thing[1][18].name = _T("哥布林狂战魔精魄"), thing[1][18].ns = 8, thing[1][18].bh_z = 1, thing[1][18].bh_j = 9, thing[1][18].b_jg = 30720, thing[1][18].s_jg = 18432;
	thing[1][19].name = _T("哥布林屠杀者精魄"), thing[1][19].ns = 8, thing[1][19].bh_z = 1, thing[1][19].bh_j = 12, thing[1][19].b_jg = 61440, thing[1][19].s_jg = 36864;
	thing[1][20].name = _T("炼狱哥布林精魄"), thing[1][20].ns = 7, thing[1][20].bh_z = 1, thing[1][20].bh_j = 13, thing[1][20].b_jg = 122880, thing[1][20].s_jg = 73728;
	thing[1][21].name = _T("虫骑.烈焰哥布林精魄"), thing[1][21].ns = 9, thing[1][21].bh_z = 1, thing[1][21].bh_j = 14, thing[1][21].b_jg = 245760, thing[1][21].s_jg = 147456;
	thing[1][22].name = _T("铁拳.战甲哥布林精魄"), thing[1][22].ns = 9, thing[1][22].bh_z = 1, thing[1][22].bh_j = 15, thing[1][22].b_jg = 491520, thing[1][22].s_jg = 294912;
	thing[1][23].name = _T("影夜.哥布林杀手精魄"), thing[1][23].ns = 9, thing[1][23].bh_z = 1, thing[1][23].bh_j = 16, thing[1][23].b_jg = 983040, thing[1][23].s_jg = 1344;
	thing[1][24].name = _T("蛮石怪精魄"), thing[1][24].ns = 5, thing[1][24].bh_z = 2, thing[1][24].bh_j = 7, thing[1][24].b_jg = 8960, thing[1][24].s_jg = 2688;
	thing[1][25].name = _T("擎天石灵精魄"), thing[1][25].ns = 6, thing[1][25].bh_z = 2, thing[1][25].bh_j = 8, thing[1][25].b_jg = 17920, thing[1][25].s_jg = 5376;
	thing[1][26].name = _T("焱冰魔岩灵精魄"), thing[1][26].ns = 7, thing[1][26].bh_z = 2, thing[1][26].bh_j = 10, thing[1][26].b_jg = 35840, thing[1][26].s_jg = 10752;
	thing[1][27].name = _T("磐岩.丛林霸主精魄"), thing[1][27].ns = 8, thing[1][27].bh_z = 2, thing[1][27].bh_j = 11, thing[1][27].b_jg = 71680, thing[1][27].s_jg = 21504;
	thing[1][28].name = _T("赤色鸡仔精魄"), thing[1][28].ns = 6, thing[1][28].bh_z = 4, thing[1][28].bh_j = 1, thing[1][28].b_jg = 170, thing[1][28].s_jg = 51;
	thing[1][29].name = _T("赤色鸡精魄"), thing[1][29].ns = 5, thing[1][29].bh_z = 4, thing[1][29].bh_j = 2, thing[1][29].b_jg = 340, thing[1][29].s_jg = 102;
	thing[1][30].name = _T("火焰鸡精魄"), thing[1][30].ns = 5, thing[1][30].bh_z = 4, thing[1][30].bh_j = 3, thing[1][30].b_jg = 680, thing[1][30].s_jg = 204;
	thing[1][31].name = _T("火赤鸡精魄"), thing[1][31].ns = 5, thing[1][31].bh_z = 4, thing[1][31].bh_j = 4, thing[1][31].b_jg = 1360, thing[1][31].s_jg = 408;
	thing[1][32].name = _T("流火鸡精魄"), thing[1][32].ns = 5, thing[1][32].bh_z = 4, thing[1][32].bh_j = 5, thing[1][32].b_jg = 2720, thing[1][32].s_jg = 816;
	thing[1][33].name = _T("流焰炽鸡精魄"), thing[1][33].ns = 6, thing[1][33].bh_z = 4, thing[1][33].bh_j = 6, thing[1][33].b_jg = 5440, thing[1][33].s_jg = 1632;
	thing[1][34].name = _T("烈焰斗战鸡精魄"), thing[1][34].ns = 7, thing[1][34].bh_z = 4, thing[1][34].bh_j = 7, thing[1][34].b_jg = 10880, thing[1][34].s_jg = 3264;
	thing[1][35].name = _T("狂炎.流炽斗鸡精魄"), thing[1][35].ns = 9, thing[1][35].bh_z = 4, thing[1][35].bh_j = 8, thing[1][35].b_jg = 21760, thing[1][35].s_jg = 6528;
	thing[1][36].name = _T("焱灭.地火皇鸡精魄"), thing[1][36].ns = 9, thing[1][36].bh_z = 4, thing[1][36].bh_j = 9, thing[1][36].b_jg = 43520, thing[1][36].s_jg = 13056;
	thing[1][37].name = _T("甲壳蜈蚣精魄"), thing[1][37].ns = 6, thing[1][37].bh_z = 5, thing[1][37].bh_j = 1, thing[1][37].b_jg = 70, thing[1][37].s_jg = 21;
	thing[1][38].name = _T("斑甲蜈蚣精魄"), thing[1][38].ns = 6, thing[1][38].bh_z = 5, thing[1][38].bh_j = 2, thing[1][38].b_jg = 140, thing[1][38].s_jg = 42;
	thing[1][39].name = _T("斑甲毒蜈蚣精魄"), thing[1][39].ns = 7, thing[1][39].bh_z = 5, thing[1][39].bh_j = 3, thing[1][39].b_jg = 280, thing[1][39].s_jg = 84;
	thing[1][40].name = _T("百足斑毒蜈精魄"), thing[1][40].ns = 7, thing[1][40].bh_z = 5, thing[1][40].bh_j = 4, thing[1][40].b_jg = 560, thing[1][40].s_jg = 168;
	thing[1][41].name = _T("千足紫毒蜈精魄"), thing[1][41].ns = 7, thing[1][41].bh_z = 5, thing[1][41].bh_j = 5, thing[1][41].b_jg = 1120, thing[1][41].s_jg = 336;
	thing[1][42].name = _T("残毒戾紫蜈精魄"), thing[1][42].ns = 7, thing[1][42].bh_z = 5, thing[1][42].bh_j = 6, thing[1][42].b_jg = 2240, thing[1][42].s_jg = 672;
	thing[1][43].name = _T("腐毒电蜈精魄"), thing[1][43].ns = 6, thing[1][43].bh_z = 5, thing[1][43].bh_j = 7, thing[1][43].b_jg = 4480, thing[1][43].s_jg = 1344;
	thing[1][44].name = _T("电闪蜈蚣精魄"), thing[1][44].ns = 6, thing[1][44].bh_z = 5, thing[1][44].bh_j = 8, thing[1][44].b_jg = 8960, thing[1][44].s_jg = 2688;
	thing[1][45].name = _T("雷霆紫电蜈精魄"), thing[1][45].ns = 7, thing[1][45].bh_z = 5, thing[1][45].bh_j = 9, thing[1][45].b_jg = 17920, thing[1][45].s_jg = 5376;
	thing[1][46].name = _T("青玄雷蜈龙精魄"), thing[1][46].ns = 7, thing[1][46].bh_z = 5, thing[1][46].bh_j = 10, thing[1][46].b_jg = 35840, thing[1][46].s_jg = 10752;
	thing[1][47].name = _T("紫元翼雷蜈龙精魄"), thing[1][47].ns = 8, thing[1][47].bh_z = 5, thing[1][47].bh_j = 11, thing[1][47].b_jg = 71680, thing[1][47].s_jg = 21504;
	thing[1][48].name = _T("天苍.狂雷蜈龙精魄"), thing[1][48].ns = 9, thing[1][48].bh_z = 5, thing[1][48].bh_j = 12, thing[1][48].b_jg = 143360, thing[1][48].s_jg = 43008;
	thing[1][49].name = _T("石崖.岩灵精魄"), thing[1][49].ns = 7, thing[1][49].bh_z = 2, thing[1][49].bh_j = 12, thing[1][49].b_jg = 143360, thing[1][49].s_jg = 43008;
	thing[1][50].name = _T("水怪精魄"), thing[1][50].ns = 4, thing[1][50].bh_z = 6, thing[1][50].bh_j = 1, thing[1][50].b_jg = 25, thing[1][50].s_jg = 7;
	thing[1][51].name = _T("水精精魄"), thing[1][51].ns = 4, thing[1][51].bh_z = 6, thing[1][51].bh_j = 2, thing[1][51].b_jg = 50, thing[1][51].s_jg = 15;
	thing[1][52].name = _T("水中夜叉精魄"), thing[1][52].ns = 6, thing[1][52].bh_z = 6, thing[1][52].bh_j = 3, thing[1][52].b_jg = 100, thing[1][52].s_jg = 30;
	thing[1][53].name = _T("水精灵精魄"), thing[1][53].ns = 5, thing[1][53].bh_z = 6, thing[1][53].bh_j = 4, thing[1][53].b_jg = 200, thing[1][53].s_jg = 60;
	thing[1][54].name = _T("溪底守卫.水灵精魄"), thing[1][54].ns = 9, thing[1][54].bh_z = 6, thing[1][54].bh_j = 5, thing[1][54].b_jg = 400, thing[1][54].s_jg = 120;
	thing[1][55].name = _T("湖塔护卫.水灵精魄"), thing[1][55].ns = 9, thing[1][55].bh_z = 6, thing[1][55].bh_j = 6, thing[1][55].b_jg = 800, thing[1][55].s_jg = 240;
	thing[1][56].name = _T("溪河清道夫精魄"), thing[1][56].ns = 7, thing[1][56].bh_z = 6, thing[1][56].bh_j = 7, thing[1][56].b_jg = 1600, thing[1][56].s_jg = 480;
	thing[1][57].name = _T("深海领路者精魄"), thing[1][57].ns = 7, thing[1][57].bh_z = 6, thing[1][57].bh_j = 8, thing[1][57].b_jg = 3200, thing[1][57].s_jg = 960;
	thing[1][58].name = _T("忘川吞噬者精魄"), thing[1][58].ns = 7, thing[1][58].bh_z = 6, thing[1][58].bh_j = 9, thing[1][58].b_jg = 6400, thing[1][58].s_jg = 1920;

	//物品
	wpls[2] = 12;
	thing[2][1].name = _T("青铜书页"), thing[2][1].ns = 4, thing[2][1].bh_z = 0, thing[2][1].bh_j = 0, thing[2][1].b_jg = 100, thing[2][1].s_jg = 70;
	thing[2][2].name = _T("白银书页"), thing[2][2].ns = 4, thing[2][2].bh_z = 0, thing[2][2].bh_j = 0, thing[2][2].b_jg = 9900, thing[2][2].s_jg = 7000;
	thing[2][3].name = _T("黄金书页"), thing[2][3].ns = 4, thing[2][3].bh_z = 0, thing[2][3].bh_j = 0, thing[2][3].b_jg = 980000, thing[2][3].s_jg = 700000;
	thing[2][4].name = _T("森林之心"), thing[2][4].ns = 4, thing[2][4].bh_z = 0, thing[2][4].bh_j = 0, thing[2][4].b_jg = 1, thing[2][4].s_jg = 1;
	thing[2][5].name = _T("海洋之心"), thing[2][5].ns = 4, thing[2][5].bh_z = 0, thing[2][5].bh_j = 0, thing[2][5].b_jg = 100, thing[2][5].s_jg = 50;
	thing[2][6].name = _T("大地之心"), thing[2][6].ns = 4, thing[2][6].bh_z = 0, thing[2][6].bh_j = 0, thing[2][6].b_jg = 10000, thing[2][6].s_jg = 5000;
	thing[2][7].name = _T("山川之心"), thing[2][7].ns = 4, thing[2][7].bh_z = 0, thing[2][7].bh_j = 0, thing[2][7].b_jg = 1000000, thing[2][7].s_jg = 500000;
	thing[2][8].name = _T("生灵之心"), thing[2][8].ns = 4, thing[2][8].bh_z = 0, thing[2][8].bh_j = 0, thing[2][8].b_jg = 100000000, thing[2][8].s_jg = 50000000;
	thing[2][9].name = _T("低阶魂晶"), thing[2][9].ns = 4, thing[2][9].bh_z = 0, thing[2][9].bh_j = 0, thing[2][9].b_jg = 100, thing[2][9].s_jg = 80;
	thing[2][10].name = _T("中阶魂晶"), thing[2][10].ns = 4, thing[2][10].bh_z = 0, thing[2][10].bh_j = 0, thing[2][10].b_jg = 1000, thing[2][10].s_jg = 800;
	thing[2][11].name = _T("高阶魂晶"), thing[2][11].ns = 4, thing[2][11].bh_z = 0, thing[2][11].bh_j = 0, thing[2][11].b_jg = 10000, thing[2][11].s_jg = 8000;
	thing[2][12].name = _T("超阶魂晶"), thing[2][12].ns = 4, thing[2][12].bh_z = 0, thing[2][12].bh_j = 0, thing[2][12].b_jg = 300000, thing[2][12].s_jg = 200000;
}

void cl()			//初始化整合
{
	in_bbh();					//录入存档版本号
	pjj[1] = 1; for (int i = 2; i <= 21; i++)pjj[i] = pjj[i - 1] * 1.4;		//初始化品级加成倍数
	dsj[0] = 1; for (int i = 1; i <= 170; i++)dsj[i] = dsj[i - 1] * 1.05;	//初始化等级魂炼加成倍数
	pzj[1] = 1; for (int i = 2; i <= 10; i++)pzj[i] = pzj[i - 1] * 1.5 * ((i + 1) / 3);		//初始化品质加成倍数
	cl_tj();					//初始化魔物图鉴
	cl_map();					//初始化地图
	cl_wp();					//初始化物品图鉴
	cl_rh();					//初始化物品融合图鉴
	cl_dw();					//初始化魔物可掉落物品
	in_bok();					//录入召唤之书
	in_map();					//录入探索之路魔物
	in_ck();					//录入仓库
}

void in_map()				//录入探索之路
{
	TCHAR s[50], ss[50];
	int dds;
	now_where = GetPrivateProfileInt(_T("ddzb"), _T("now_where"), 1, _T("data\\TSZL.ini"));
	dds = tsl;
	for (int i = 1; i <= dds; i++)
	{
		//本页魔物数量
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

void out_map()				//保存探索之路
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

void outs()					//保存整合
{
	out_map();
	out_bok();
	out_ck();
	out_bbh();
}

void mw_lt(int c, int r, int z, int dj)		//魔物掉落物品
{
	for (int i = 0; i < dmw[c][r].size(); i++)
	{
		if (dmw[c][r][i].z != 0)	//物品
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
		else    //玉石
		{
			int sum = random(dmw[c][r][i].suml, dmw[c][r][i].sumh);
			ys += sum;
		}

	}

	//保存
	outs();
}

int find_wp(int z, int k)			//查找仓库物品
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

void out_bok()			//保存召唤之书
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

void out_ck()			//保存仓库
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

void in_ck()			//录入仓库
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
	//获得经验
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

void rh_page(int k)				//融合页面
{
	TCHAR ss[50];

	//保存
	outs();

	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(450, i, 870, i);

	//查找可融合精魄
	vector<CK> x, y;
	for (int i = 0; i < cwp.size(); i++)
		if (cwp[i].sum > 0)
		{
			if (thing[cwp[i].wz][cwp[i].wt].bh_z == pt[k].clan && thing[cwp[i].wz][cwp[i].wt].bh_j <= pt[k].race)
				x.push_back(cwp[i]);			//可融合精魄
			else y.push_back(cwp[i]);			//不可融合精魄
		}

	//融合进度
	settextstyle(20, 0, _T("宋体"));
	settextcolor(RGB(0, 0, 0));
	_stprintf(ss, _T("融合进度: %d/%d"), pt[k].pjz, npj[pt[k].pj - mws[pt[k].clan].bs_pj + 1]);
	outtextxy(480, 10, ss);

	//物品图标
	for (int i = 1; i <= ceil(x.size() / (double)2); i++)
	{
		for (int j = 0; j < min(2, x.size() - (i - 1) * 2); j++)
		{
			setfillcolor(RGB(255, 250, 205));
			fillrectangle(480 + 180 * j, 50 + 90 * (i - 1), 650 + 180 * j, 120 + 90 * (i - 1));
			settextstyle(160 / thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].ns, 80 / thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].ns, _T("宋体"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(485 + 180 * j, 60 + 90 * (i - 1), thing[x[(i - 1) * 2 + j].wz][x[(i - 1) * 2 + j].wt].name);
			settextstyle(20, 0, _T("宋体"));
			TCHAR ss[50];
			_stprintf(ss, _T("X %d"), x[(i - 1) * 2 + j].sum);
			outtextxy(535 + 180 * j, 90 + 90 * (i - 1), ss);
		}
	}

	//选择
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//返回主页面
				main_page();

			if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//上一页
				bok(k - 1, 3);

			if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//下一页
				bok(k + 1, 3);

			for (int i = 1; i <= 4; i++)		//更换培养选项
				if (i != 3 && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
					bok(k, i);

			for (int i = 1; i <= ceil(x.size() / (double)2); i++)		//融合
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

							//更新召唤兽图
							IMAGE jpg;				//录入图片的指针
							loadimage(&jpg, pmw[pt[k].clan][pt[k].race].tp, 400, 500);
							putimage(30, 20, 430, 520, &jpg, 0, 0);
						}

						//更新仓库物品
						vector<CK> xx;
						for (int ii = 0; ii < x.size(); ii++)
							if (x[ii].sum > 0)
								xx.push_back(x[ii]);
						cwp.clear();
						for (int ii = 0; ii < xx.size(); ii++)
							cwp.push_back(xx[ii]);
						for (int ii = 0; ii < y.size(); ii++)
							cwp.push_back(y[ii]);

						//更新当前页面
						rh_page(k);
					}
		}
	}
}

void lor_wp(CK k, int f)
{
	TCHAR ss[50];

	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//物品图
	setfillcolor(RGB(255, 250, 205));
	fillrectangle(100, 50, 500, 550);

	//物品名
	settextstyle(30, 0, _T("宋体"));
	_stprintf(ss, _T("物品名:%s"), thing[k.wz][k.wt].name);
	outtextxy(550, 60, ss);

	//物品描述
	wp_ms(k.wz, k.wt);

	if (f == 1)
	{
		//使用图标
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(700, 500, 800, 550);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(720, 510, _T("使用"));

		//返回图标
		setfillcolor(RGB(0, 0, 255));
		fillrectangle(600, 500, 700, 550);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(620, 510, _T("返回"));

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//仓库页面
				if (600 <= m.x && m.x <= 700 && 500 <= m.y && m.y <= 550)cc_page();

				if (700 < m.x && m.x <= 800 && 500 <= m.y && m.y <= 550)
					if (cs_page(2, wp_ef(k.wz, k.wt)))	 //物品使用效果
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
		int a = 0;		//购买数量

		//返回图标
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(900, 530, 980, 580);
		settextstyle(30, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(910, 540, _T("返回"));

		//购买图标
		if (ys >= a * thing[k.wz][k.wt].b_jg && a != 0) setfillcolor(RGB(100, 150, 200));
		else setfillcolor(RGB(192, 192, 192));
		fillrectangle(550, 500, 650, 550);
		settextstyle(30, 0, _T("黑体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(570, 510, _T("购买"));

		//玉石数量
		settextstyle(36, 0, _T("楷体"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("玉石：%d"), ys);
		outtextxy(100, 5, ss);

		//购买数量图标
		setfillcolor(RGB(255, 255, 255));
		setlinecolor(RGB(0, 0, 0));
		fillrectangle(630, 417, 780, 447);
		settextstyle(30, 0, _T("楷体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(550, 420, _T("数量："));
		_stprintf(ss, _T("%d"), a);
		outtextxy(635, 420, ss);

		//价格
		settextstyle(30, 0, _T("楷体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(550, 460, _T("价格："));
		outtextxy(635, 460, _T("0"));

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//返回
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)sc_page(k.wz, 1);

				//购买
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

				//更改数量
				if (630 <= m.x && m.x <= 780 && 417 <= m.y && m.y <= 447)
				{
					//数量
					TCHAR as[100];
					InputBox(as, 100, _T("数量"));
					a = _wtoi(as);
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(0, 0, 0));
					fillrectangle(630, 417, 780, 447);
					settextstyle(30, 0, _T("楷体"));
					settextcolor(RGB(0, 0, 0));
					_stprintf(ss, _T("%d"), a);
					outtextxy(635, 420, ss);

					//价格
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(255, 255, 255));
					fillrectangle(630, 455, 850, 490);
					settextstyle(30, 0, _T("楷体"));
					if (ys >= a * thing[k.wz][k.wt].b_jg)settextcolor(RGB(0, 0, 0));
					else settextcolor(RGB(255, 0, 0));
					_stprintf(ss, _T("%lld"), a * thing[k.wz][k.wt].b_jg);
					outtextxy(635, 460, ss);

					//购买图标
					if (ys >= a * thing[k.wz][k.wt].b_jg && a != 0) setfillcolor(RGB(100, 150, 200));
					else setfillcolor(RGB(192, 192, 192));
					fillrectangle(550, 500, 650, 550);
					settextstyle(30, 0, _T("黑体"));
					settextcolor(RGB(0, 0, 0));
					outtextxy(570, 510, _T("购买"));
				}
			}
		}

	}
}

bool wp_ef(int z, int k)			//物品使用效果
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

		//保存
		outs();

		//背景
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(450, i, 870, i);

		//更新仓库物品
		vector<CK> x;
		for (int i = 0; i < cwp.size(); i++)
			if (cwp[i].sum > 0)
				x.push_back(cwp[i]);
		cwp.clear();
		for (int i = 0; i < x.size(); i++)
			cwp.push_back(x[i]);

		//等级、经验
		settextstyle(32, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("等级:%d"), pt[k].dj);
		outtextxy(480, 10, ss);
		settextstyle(16, 0, _T("宋体"));
		_stprintf(ss, _T("经验:%llu/%llu"), pt[k].ep, nep[pt[k].dj]);
		outtextxy(480, 50, ss);

		//经验石图标
		int f1, f2, f3, f4, f5;

		settextcolor(RGB(0, 0, 0));
		settextstyle(40, 0, _T("宋体"));

		setfillcolor(RGB(0, 255, 0));
		fillrectangle(480, 100, 650, 170);
		outtextxy(485, 110, _T("森林之心"));
		setfillcolor(RGB(0, 191, 255));
		fillrectangle(660, 100, 830, 170);
		outtextxy(665, 110, _T("海洋之心"));
		setfillcolor(RGB(138, 43, 226));
		fillrectangle(480, 190, 650, 260);
		outtextxy(485, 200, _T("大地之心"));
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(660, 190, 830, 260);
		outtextxy(665, 200, _T("山川之心"));
		setfillcolor(RGB(255, 255, 0));
		fillrectangle(480, 280, 650, 350);
		outtextxy(485, 290, _T("生灵之心"));

		settextstyle(20, 0, _T("宋体"));

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

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//返回主页面
					main_page();
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//上一页
					bok(k - 1, 2);
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//下一页
					bok(k + 1, 2);
				for (int i = 1; i <= 4; i++)		//更换培养选项
					if (i != 2 && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
						bok(k, i);
				if (480 <= m.x&&m.x <= 650 && 100 <= m.y && m.y <= 170)//森林之心
					if (f1 != -1)
					{
						get_jy(k, 100);
						cwp[f1].sum -= 1;
						break;
					}
				if (660 <= m.x&&m.x <= 830 && 100 <= m.y && m.y <= 170)//海洋之心
					if (f2 != -1 && cwp[f2].sum > 0)
					{
						get_jy(k, 10000);
						cwp[f2].sum -= 1;
						break;
					}
				if (480 <= m.x&&m.x <= 650 && 190 <= m.y && m.y <= 260)//大地之心
					if (f3 != -1)
					{
						get_jy(k, 1000000);
						cwp[f3].sum -= 1;
						break;
					}
				if (660 <= m.x&&m.x <= 830 && 190 <= m.y && m.y <= 260)//山川之心
					if (f4 != -1)
					{
						get_jy(k, 100000000);
						cwp[f4].sum -= 1;
						break;
					}
				if (480 <= m.x&&m.x <= 650 && 280 <= m.y && m.y <= 350)//生灵之心
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

	//保存
	outs();

	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//返回主页面图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(910, 540, _T("返回"));

	//进行融和图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(300, 400, 400, 450);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(320, 410, _T("融和"));
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(410, 400, 510, 450);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(420, 420, _T("全部融和"));

	//操作面板
	setfillcolor(RGB(210, 105, 30));
	for (int i = 1; i <= 1; i++)
		fillrectangle(890, 10 + (i - 1) * 60, 990, 70 + (i - 1) * 60);
	setfillcolor(RGB(255, 0, 0));
	fillrectangle(890, 10 + (f - 1) * 60, 990, 70 + (f - 1) * 60);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(910, 25, _T("融合"));

	//物品图标
	int maxs;
	if (f == 1)maxs = rhsum;
	for (int i = 1; i <= min(9, maxs - (k - 1) * 9); i++)
	{
		if (i == z)setfillcolor(RGB(210, 105, 100));
		else setfillcolor(RGB(110, 205, 100));
		fillrectangle(790, 30 + (i - 1) * 60, 890, 80 + (i - 1) * 60);
		settextstyle(100 / thing[rhwp[9 * (k - 1) + i].mz][rhwp[9 * (k - 1) + i].mr].ns, 50 / thing[rhwp[9 * (k - 1) + i].mz][rhwp[9 * (k - 1) + i].mr].ns, _T("宋体"));
		outtextxy(792, 40 + (i - 1) * 60, thing[rhwp[9 * (k - 1) + i].mz][rhwp[9 * (k - 1) + i].mr].name);
	}

	//融和界面
	setfillcolor(RGB(110, 205, 100));
	fillrectangle(350, 50, 450, 100);
	settextstyle(100 / thing[rhwp[9 * (k - 1) + z].mz][rhwp[9 * (k - 1) + z].mr].ns, 50 / thing[rhwp[9 * (k - 1) + z].mz][rhwp[9 * (k - 1) + z].mr].ns, _T("宋体"));
	outtextxy(352, 60, thing[rhwp[9 * (k - 1) + z].mz][rhwp[9 * (k - 1) + z].mr].name);
	IMAGE jpg;				//录入图片的指针
	loadimage(&jpg, _T("res\\箭头.jpg"), 40, 80);
	putimage(380, 110, 40, 80, &jpg, 0, 0);
	for (int i = 0; i < rhwp[9 * (k - 1) + z].n; i++)
	{
		int w = find_wp(rhwp[9 * (k - 1) + z].nz[i], rhwp[9 * (k - 1) + z].nr[i]);
		if (w == -1 || cwp[w].sum < rhwp[9 * (k - 1) + z].ns[i])setfillcolor(RGB(192, 192, 192));
		else setfillcolor(RGB(110, 205, 100));
		fillrectangle(20 + i * 180, 210, 150 + i * 180, 280);
		settextstyle(120 / thing[rhwp[9 * (k - 1) + z].nz[i]][rhwp[9 * (k - 1) + z].nr[i]].ns, 60 / thing[rhwp[9 * (k - 1) + z].nz[i]][rhwp[9 * (k - 1) + z].nr[i]].ns, _T("宋体"));
		outtextxy(25 + i * 180, 220, thing[rhwp[9 * (k - 1) + z].nz[i]][rhwp[9 * (k - 1) + z].nr[i]].name);
		settextstyle(20, 0, _T("宋体"));
		if (w == -1)_stprintf(ss, _T("%d/%d"), 0, rhwp[9 * (k - 1) + z].ns[i]);
		else _stprintf(ss, _T("%d/%d"), cwp[w].sum, rhwp[9 * (k - 1) + z].ns[i]);
		outtextxy(30 + 180 * i, 260, ss);
	}

	//选择
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580) main_page();			//返回主页面

			if (300 <= m.x && m.x <= 400 && 400 <= m.y && m.y <= 450)	//融合
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

			if (410 <= m.x && m.x <= 510 && 400 <= m.y && m.y <= 450)	//全部融和
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

			for (int i = 1; i <= 1; i++)		//更换熔炼选项
				if (i != f && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
					rl_page(i, 1, 1);

			for (int i = 1; i <= min(9, maxs - (k - 1) * 9); i++)		//更换熔炼物品
				if (i != z && 790 <= m.x && m.x <= 890 && 30 + (i - 1) * 60 <= m.y && m.y <= 80 + (i - 1) * 60)
					rl_page(f, k, i);

		}
	}
}

void cl_rh()
{
	rhsum = 6;

	//白银书页
	rhwp[1].mz = 2, rhwp[1].mr = 2, rhwp[1].n = 1;
	rhwp[1].nz.push_back(2);
	rhwp[1].nr.push_back(1);
	rhwp[1].ns.push_back(10);

	//黄金书页
	rhwp[2].mz = 2, rhwp[2].mr = 3, rhwp[2].n = 1;
	rhwp[2].nz.push_back(2);
	rhwp[2].nr.push_back(2);
	rhwp[2].ns.push_back(10);

	//海洋之心
	rhwp[3].mz = 2, rhwp[3].mr = 5, rhwp[3].n = 1;
	rhwp[3].nz.push_back(2);
	rhwp[3].nr.push_back(4);
	rhwp[3].ns.push_back(100);

	//大地之心
	rhwp[4].mz = 2, rhwp[4].mr = 6, rhwp[4].n = 1;
	rhwp[4].nz.push_back(2);
	rhwp[4].nr.push_back(5);
	rhwp[4].ns.push_back(100);

	//山川之心
	rhwp[5].mz = 2, rhwp[5].mr = 7, rhwp[5].n = 1;
	rhwp[5].nz.push_back(2);
	rhwp[5].nr.push_back(6);
	rhwp[5].ns.push_back(100);

	//生灵之心
	rhwp[6].mz = 2, rhwp[6].mr = 8, rhwp[6].n = 1;
	rhwp[6].nz.push_back(2);
	rhwp[6].nr.push_back(7);
	rhwp[6].ns.push_back(100);
}

void cl_dw()
{
	CDWP x;

	//哥布林
	x.z = 1, x.j = 1, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][1].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[1][1].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 5, x.sumh = 10, x.gl = 100; dmw[1][1].push_back(x);		//玉石

	//大哥布林
	x.z = 1, x.j = 2, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][2].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[1][2].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 10, x.sumh = 20, x.gl = 100; dmw[1][2].push_back(x);		//玉石

	//哥布林勇士
	x.z = 1, x.j = 3, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][3].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[1][3].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 20, x.sumh = 40, x.gl = 100; dmw[1][3].push_back(x);		//玉石

	//哥布林酋长
	x.z = 1, x.j = 4, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][4].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[1][4].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 40, x.sumh = 80, x.gl = 100; dmw[1][4].push_back(x);		//玉石

	//哥布林大酋长
	x.z = 1, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][5].push_back(x);			//精魄
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[1][5].push_back(x);			//森林之心
	x.z = 0, x.j = 0, x.suml = 80, x.sumh = 160, x.gl = 100; dmw[1][5].push_back(x);		//玉石

	//哥布林祭师
	x.z = 1, x.j = 6, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][6].push_back(x);			//精魄
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[1][6].push_back(x);			//森林之心
	x.z = 0, x.j = 0, x.suml = 160, x.sumh = 320, x.gl = 100; dmw[1][6].push_back(x);		//玉石

	//哥布林主祭
	x.z = 1, x.j = 7, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][7].push_back(x);			//精魄
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[1][7].push_back(x);			//森林之心
	x.z = 0, x.j = 0, x.suml = 320, x.sumh = 640, x.gl = 100; dmw[1][7].push_back(x);		//玉石

	//哥布林首领
	x.z = 1, x.j = 8, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][8].push_back(x);			//精魄
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[1][8].push_back(x);			//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][8].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 640, x.sumh = 1280, x.gl = 100; dmw[1][8].push_back(x);		//玉石

	//哥布林狂战魔
	x.z = 1, x.j = 18, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][9].push_back(x);			//精魄
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[1][9].push_back(x);			//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][9].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 1280, x.sumh = 2560, x.gl = 100; dmw[1][9].push_back(x);		//玉石

	//血冠哥布林
	x.z = 1, x.j = 10, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][10].push_back(x);				//精魄
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[1][10].push_back(x);				//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][10].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 2560, x.sumh = 5120, x.gl = 100; dmw[1][10].push_back(x);		//玉石

	//血暗荆棘哥布林
	x.z = 1, x.j = 11, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][11].push_back(x);				//精魄
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[1][11].push_back(x);				//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][11].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 5120, x.sumh = 10240, x.gl = 100; dmw[1][11].push_back(x);		//玉石

	//哥布林屠杀者
	x.z = 1, x.j = 19, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][12].push_back(x);				//精魄
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[1][12].push_back(x);				//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][12].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 10240, x.sumh = 20480, x.gl = 100; dmw[1][12].push_back(x);		//玉石

	//炼狱哥布林
	x.z = 1, x.j = 20, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][13].push_back(x);				//精魄
	x.z = 2, x.j = 5, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[1][13].push_back(x);				//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][13].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 20480, x.sumh = 40960, x.gl = 100; dmw[1][13].push_back(x);		//玉石

	//虫骑.烈焰哥布林
	x.z = 1, x.j = 21, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][14].push_back(x);				//精魄
	x.z = 2, x.j = 5, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[1][14].push_back(x);				//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][14].push_back(x);				//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 40960, x.sumh = 81920, x.gl = 100; dmw[1][14].push_back(x);		//玉石

	//铁拳.战甲哥布林
	x.z = 1, x.j = 22, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][15].push_back(x);				//精魄
	x.z = 2, x.j = 6, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[1][15].push_back(x);				//大地之心
	x.z = 2, x.j = 10, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][15].push_back(x);				//中阶魂晶
	x.z = 0, x.j = 0, x.suml = 81920, x.sumh = 163840, x.gl = 100; dmw[1][15].push_back(x);		//玉石

	//影夜.哥布林杀手
	x.z = 1, x.j = 23, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[1][16].push_back(x);				//精魄
	x.z = 2, x.j = 6, x.suml = 2, x.sumh = 4, x.gl = 50; dmw[1][16].push_back(x);				//大地之心
	x.z = 2, x.j = 10, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[1][16].push_back(x);				//中阶魂晶
	x.z = 0, x.j = 0, x.suml = 163840, x.sumh = 327680, x.gl = 100; dmw[1][16].push_back(x);	//玉石

	//石子怪
	x.z = 1, x.j = 11, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][1].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[2][1].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 8, x.sumh = 16, x.gl = 100; dmw[2][1].push_back(x);		//玉石

	//小石人
	x.z = 1, x.j = 12, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][2].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[2][2].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 16, x.sumh = 32, x.gl = 100; dmw[2][2].push_back(x);		//玉石

	//石头人
	x.z = 1, x.j = 13, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][3].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[2][3].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 32, x.sumh = 64, x.gl = 100; dmw[2][3].push_back(x);		//玉石

	//巨岩石人
	x.z = 1, x.j = 14, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][4].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[2][4].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 64, x.sumh = 128, x.gl = 100; dmw[2][4].push_back(x);		//玉石

	//戈仑石人
	x.z = 1, x.j = 15, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][5].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[2][5].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 128, x.sumh = 256, x.gl = 100; dmw[2][5].push_back(x);		//玉石

	//戈仑岩晶
	x.z = 1, x.j = 16, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][6].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[2][6].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 256, x.sumh = 512, x.gl = 100; dmw[2][6].push_back(x);		//玉石

	//蛮石怪
	x.z = 1, x.j = 24, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][7].push_back(x);	//精魄
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[2][7].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][7].push_back(x);		//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 512, x.sumh = 1024, x.gl = 100; dmw[2][7].push_back(x);		//玉石

	//擎天岩灵
	x.z = 1, x.j = 25, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][8].push_back(x);	//精魄
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[2][8].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][8].push_back(x);		//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 1024, x.sumh = 2048, x.gl = 100; dmw[2][8].push_back(x);		//玉石

	//熔岩石怪
	x.z = 1, x.j = 17, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][9].push_back(x);	//精魄
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[2][9].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][9].push_back(x);		//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 2048, x.sumh = 4096, x.gl = 100; dmw[2][9].push_back(x);		//玉石

	//焱冰魔岩灵
	x.z = 1, x.j = 26, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][10].push_back(x);	//精魄
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[2][10].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][10].push_back(x);	//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 4096, x.sumh = 8192, x.gl = 100; dmw[2][10].push_back(x);		//玉石

	//磐岩.丛林霸主
	x.z = 1, x.j = 27, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][11].push_back(x);	//精魄
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[2][11].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][11].push_back(x);	//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 8192, x.sumh = 16284, x.gl = 100; dmw[2][11].push_back(x);		//玉石

	//石崖.岩灵
	x.z = 1, x.j = 49, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[2][12].push_back(x);	//精魄
	x.z = 2, x.j = 5, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[2][12].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[2][12].push_back(x);	//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 16384, x.sumh = 32768, x.gl = 100; dmw[2][12].push_back(x);		//玉石

	//学渣
	x.z = 2, x.j = 1, x.suml = 1, x.sumh = 1, x.gl = 30; dmw[3][1].push_back(x);	//青铜书页
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[3][1].push_back(x);	//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[3][1].push_back(x);	//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 10, x.sumh = 10, x.gl = 100; dmw[3][1].push_back(x);	//玉石

	//学霸
	x.z = 2, x.j = 2, x.suml = 1, x.sumh = 1, x.gl = 20; dmw[3][2].push_back(x);		//白银书页
	x.z = 2, x.j = 6, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[3][2].push_back(x);		//大地之心
	x.z = 2, x.j = 9, x.suml = 4, x.sumh = 7, x.gl = 50; dmw[3][2].push_back(x);		//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 1000, x.sumh = 1000, x.gl = 100; dmw[3][2].push_back(x);	//玉石

	//学神
	x.z = 2, x.j = 3, x.suml = 1, x.sumh = 1, x.gl = 10; dmw[3][3].push_back(x);			//黄金书页
	x.z = 2, x.j = 7, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[3][3].push_back(x);			//山川之心
	x.z = 2, x.j = 10, x.suml = 1, x.sumh = 2, x.gl = 50; dmw[3][3].push_back(x);			//中阶魂晶
	x.z = 0, x.j = 0, x.suml = 100000, x.sumh = 100000, x.gl = 100; dmw[3][3].push_back(x);	//玉石

	//赤色鸡仔
	x.z = 1, x.j = 28, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][1].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[4][1].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 20, x.sumh = 40, x.gl = 100; dmw[4][1].push_back(x);		//玉石

	//赤色鸡
	x.z = 1, x.j = 29, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][2].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[4][2].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 40, x.sumh = 80, x.gl = 100; dmw[4][2].push_back(x);		//玉石

	//火焰鸡
	x.z = 1, x.j = 30, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][3].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[4][3].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 80, x.sumh = 160, x.gl = 100; dmw[4][3].push_back(x);	//玉石

	//火赤鸡
	x.z = 1, x.j = 31, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][4].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[4][4].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 160, x.sumh = 320, x.gl = 100; dmw[4][4].push_back(x);	//玉石

	//流火鸡
	x.z = 1, x.j = 32, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][5].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[4][5].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[4][5].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 320, x.sumh = 640, x.gl = 100; dmw[4][5].push_back(x);	//玉石

	//流焰炽鸡
	x.z = 1, x.j = 33, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][6].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[4][6].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2, dmw[4][6].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 640, x.sumh = 1280, x.gl = 100; dmw[4][6].push_back(x);	//玉石

	//烈炎斗战鸡
	x.z = 1, x.j = 34, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][7].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[4][7].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[4][7].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 1280, x.sumh = 2560, x.gl = 100; dmw[4][7].push_back(x);	//玉石

	//狂炎.流炽斗鸡
	x.z = 1, x.j = 35, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][8].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[4][8].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[4][8].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 2560, x.sumh = 5120, x.gl = 100; dmw[4][8].push_back(x);	//玉石

	//焱灭.地火皇鸡
	x.z = 1, x.j = 36, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[4][9].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[4][9].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 5; dmw[4][9].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 5120, x.sumh = 10240, x.gl = 100; dmw[4][9].push_back(x);//玉石

	//甲壳蜈蚣
	x.z = 1, x.j = 37, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][1].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 4, x.gl = 50; dmw[5][1].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 16, x.sumh = 32, x.gl = 100; dmw[5][1].push_back(x);		//玉石

	//斑甲蜈蚣
	x.z = 1, x.j = 38, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][2].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[5][2].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 32, x.sumh = 64, x.gl = 100; dmw[5][2].push_back(x);		//玉石

	//斑甲毒蜈蚣
	x.z = 1, x.j = 39, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][3].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[5][3].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 64, x.sumh = 128, x.gl = 100; dmw[5][3].push_back(x);	//玉石

	//百足斑毒蜈
	x.z = 1, x.j = 40, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][4].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[5][4].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 128, x.sumh = 256, x.gl = 100; dmw[5][4].push_back(x);	//玉石

	//千足紫毒蜈	
	x.z = 1, x.j = 41, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][5].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[5][5].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 256, x.sumh = 512, x.gl = 100; dmw[5][5].push_back(x);	//玉石

	//残毒戾紫蜈	
	x.z = 1, x.j = 42, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][6].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[5][6].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 512, x.sumh = 1024, x.gl = 100; dmw[5][6].push_back(x);	//玉石

	//腐毒电蜈
	x.z = 1, x.j = 43, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][7].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[5][7].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][7].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 1024, x.sumh = 2048, x.gl = 100; dmw[5][7].push_back(x);	//玉石

	//电闪蜈蚣
	x.z = 1, x.j = 44, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][8].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[5][8].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][8].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 2048, x.sumh = 4096, x.gl = 100; dmw[5][8].push_back(x);	//玉石

	//雷霆紫电蜈
	x.z = 1, x.j = 45, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][9].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[5][9].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][9].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 4096, x.sumh = 8192, x.gl = 100; dmw[5][9].push_back(x);	//玉石

	//青玄雷蜈龙
	x.z = 1, x.j = 46, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][10].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[5][10].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][10].push_back(x);		//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 8192, x.sumh = 16384, x.gl = 100; dmw[5][10].push_back(x);//玉石

	//紫元翼雷蜈龙
	x.z = 1, x.j = 47, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][11].push_back(x);			//精魄
	x.z = 2, x.j = 5, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[5][11].push_back(x);			//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][11].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 16384, x.sumh = 32768, x.gl = 100; dmw[5][11].push_back(x);	//玉石

	//天苍.狂雷蜈龙
	x.z = 1, x.j = 48, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[5][12].push_back(x);			//精魄
	x.z = 2, x.j = 5, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[5][12].push_back(x);			//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[5][12].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 32768, x.sumh = 65536, x.gl = 100; dmw[5][12].push_back(x);	//玉石

	//水怪
	x.z = 1, x.j = 50, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][1].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[6][1].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 4, x.sumh = 8, x.gl = 100; dmw[6][1].push_back(x);	//玉石

	//水精
	x.z = 1, x.j = 51, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][2].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[6][2].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 8, x.sumh = 16, x.gl = 100; dmw[6][2].push_back(x);	//玉石

	//水中夜叉
	x.z = 1, x.j = 52, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][3].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 4, x.sumh = 6, x.gl = 50; dmw[6][3].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 16, x.sumh = 32, x.gl = 100; dmw[6][3].push_back(x);	//玉石

	//水精灵
	x.z = 1, x.j = 53, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][4].push_back(x);	//精魄
	x.z = 2, x.j = 4, x.suml = 8, x.sumh = 12, x.gl = 50; dmw[6][4].push_back(x);	//森林之心
	x.z = 0, x.j = 0, x.suml = 32, x.sumh = 64, x.gl = 100; dmw[6][4].push_back(x);	//玉石

	//溪底守卫.水灵
	x.z = 1, x.j = 54, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][5].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 16, x.sumh = 24, x.gl = 50; dmw[6][5].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 64, x.sumh = 128, x.gl = 100; dmw[6][5].push_back(x);	//玉石

	//湖塔护卫.水灵
	x.z = 1, x.j = 55, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][6].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 32, x.sumh = 48, x.gl = 50; dmw[6][6].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 128, x.sumh = 256, x.gl = 100; dmw[6][6].push_back(x);	//玉石

	//溪河清道夫
	x.z = 1, x.j = 56, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][7].push_back(x);		//精魄
	x.z = 2, x.j = 4, x.suml = 64, x.sumh = 96, x.gl = 50; dmw[6][7].push_back(x);		//森林之心
	x.z = 0, x.j = 0, x.suml = 256, x.sumh = 512, x.gl = 100;  dmw[6][7].push_back(x);	//玉石

	//深海领路者
	x.z = 1, x.j = 57, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][8].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 1, x.sumh = 1, x.gl = 50; dmw[6][8].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[6][8].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 512, x.sumh = 1024, x.gl = 100;  dmw[6][8].push_back(x);	//玉石

	//忘川吞噬者
	x.z = 1, x.j = 58, x.suml = 1, x.sumh = 1, x.gl = 100; dmw[6][9].push_back(x);		//精魄
	x.z = 2, x.j = 5, x.suml = 2, x.sumh = 3, x.gl = 50; dmw[6][9].push_back(x);		//海洋之心
	x.z = 2, x.j = 9, x.suml = 1, x.sumh = 1, x.gl = 2; dmw[6][9].push_back(x);			//低阶魂晶
	x.z = 0, x.j = 0, x.suml = 1024, x.sumh = 2048, x.gl = 100;  dmw[6][9].push_back(x);//玉石

}

void zr_page()			//阵容页面
{
	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//返回主页面图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("宋体"));
	outtextxy(910, 540, _T("返回"));

	//交换图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(100, 530, 200, 580);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(120, 540, _T("交换"));

	//集体对决阵容
	settextstyle(20, 0, _T("黑体"));
	settextcolor(RGB(255, 0, 0));
	outtextxy(100, 70, _T("集体对决阵容"));

	//单挑阵容
	settextstyle(20, 0, _T("黑体"));
	settextcolor(RGB(255, 0, 0));
	outtextxy(110, 290, _T("单挑阵容"));

	//总战力
	TCHAR ss[50];
	unsigned long long zl = 0;
	for (int i = 1; i <= 6; i++)zl += pt[zrbh[i]].s_zl;
	settextstyle(32, 0, _T("楷体"));
	settextcolor(RGB(255, 0, 0));
	_stprintf(ss, _T("总战力:%llu"), zl);
	outtextxy(100, 210, ss);
	_stprintf(ss, _T("战力:%llu"), pt[zrbh[13]].s_zl);
	outtextxy(100, 430, ss);

	int sums = 0;
	bool bl[10];
	memset(bl, 0, sizeof(bl));

	while (1)
	{
		//保存
		outs();

		//集体对决阵容图标
		for (int i = 1; i <= 6; i++)
		{
			if (!bl[i])setfillcolor(RGB(255, 250, 205));
			else setfillcolor(RGB(255, 99, 71));
			fillrectangle(100 + 120 * (i - 1), 100, 200 + 120 * (i - 1), 160);
			settextstyle(80 / pmw[pt[zrbh[i]].clan][pt[zrbh[i]].race].ns, 40 / pmw[pt[zrbh[i]].clan][pt[zrbh[i]].race].ns, _T("宋体"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(105 + 120 * (i - 1), 120, pmw[pt[zrbh[i]].clan][pt[zrbh[i]].race].race);
			setfillcolor(RGB(100, 150, 200));
			fillrectangle(120 + 120 * (i - 1), 170, 180 + 120 * (i - 1), 200);
			settextstyle(20, 0, _T("黑体"));
			settextcolor(RGB(0, 0, 0));
			outtextxy(130 + 120 * (i - 1), 175, _T("上阵"));
		}

		//单挑阵容图标
		setfillcolor(RGB(255, 250, 205));
		fillrectangle(100, 320, 200, 380);
		settextstyle(80 / pmw[pt[zrbh[13]].clan][pt[zrbh[13]].race].ns, 40 / pmw[pt[zrbh[13]].clan][pt[zrbh[13]].race].ns, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(105, 340, pmw[pt[zrbh[13]].clan][pt[zrbh[13]].race].race);
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(120, 390, 180, 420);
		settextstyle(20, 0, _T("黑体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(130, 395, _T("上阵"));

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//返回主页面
					main_page();

				//选择要换位的魔物
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

				//上阵集体对决召唤兽
				for (int i = 1; i <= 6; i++)
				{
					if (120 + 120 * (i - 1) <= m.x && m.x <= 180 + 120 * (i - 1) && 170 <= m.y && m.y <= 200)
						sh_page(i);
				}

				//上阵单挑召唤兽
				if (120 <= m.x && m.x <= 180 && 390 <= m.y && m.y <= 420)
					sh_page(13);

				//交换
				if (100 <= m.x && m.x <= 200 && 530 <= m.y && m.y <= 580)
				{
					int a1, a2;
					if (sums == 2)
					{
						for (int i = 1; i <= 6; i++)if (bl[i])a2 = i;
						for (int i = 6; i >= 1; i--)if (bl[i])a1 = i;
						if (zrbh[13] == a1 || zrbh[13] == a2)zrbh[13] = a1 + a2 - zrbh[13];
						swap(pt[a1].rsh, pt[a2].rsh);

						//排序
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
	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//地图
	IMAGE jpg;				//录入图片的指针
	loadimage(&jpg, _T("res\\地图.jpg "), 1000, 600);
	putimage(0, 0, 1000, 600, &jpg, 0, 0);

	//返回主页面图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(910, 540, _T("返回"));

	//ps
	settextstyle(16, 0, _T("宋体"));
	outtextxy(700, 30, _T("某概率地点出现概率统一"));
	outtextxy(700, 50, _T("为某概率地点最低出现概率"));

	//选择
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//返回探索之路
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
	::WritePrivateProfileString(_T("bbn"), _T("bbh"), _T("1.5"), _T("data\\BBH.ini"));/////////////////////////////重点注意/////////////////////////////////重点注意///////////////////////////////重点注意/////////////////////////////////
}

void hl_page(int k)
{
	int mps, ps = 1;			//献祭道具页数
	while (1)
	{
		//保存
		outs();

		//背景
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(450, i, 870, i);

		//查找可融合精魄
		vector<CK> x, y;
		for (int i = 0; i < cwp.size(); i++)
			if (cwp[i].sum > 0 && cwp[i].wz == 1 || (cwp[i].wz == 2 && 9 <= cwp[i].wt&&cwp[i].wt <= 12))
				x.push_back(cwp[i]);			//可献祭物品
			else
				y.push_back(cwp[i]);			//不可献祭物品

		mps = ceil((double)x.size() / (double)10.0);

		//魂炼值、魂炼次数上限、已魂炼次数
		TCHAR ss[50];
		settextstyle(32, 0, _T("黑体"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("魂炼: %d   等级: %d"), pt[k].srd, pt[k].dj);
		outtextxy(480, 10, ss);
		settextstyle(26, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		_stprintf(ss, _T("献祭值: %d/%d"), pt[k].hlz, hlz[pt[k].hls]);
		outtextxy(480, 50, ss);
		settextstyle(20, 0, _T("宋体"));
		_stprintf(ss, _T("魂炼次数: %d/%d"), pt[k].hls, pt[k].hlm);
		outtextxy(480, 85, ss);

		//魂炼图标
		setfillcolor(RGB(255, 160, 122));
		fillrectangle(750, 50, 820, 83);
		settextstyle(30, 0, _T("楷体"));
		settextcolor(RGB(138, 43, 226));
		outtextxy(757, 54, _T("魂炼"));

		//换页图标
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(850, 270, 880, 370);
		settextstyle(16, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(857, 275, _T("上"));
		outtextxy(857, 288, _T("一"));
		outtextxy(857, 301, _T("页"));
		outtextxy(857, 324, _T("下"));
		outtextxy(857, 337, _T("一"));
		outtextxy(857, 350, _T("页"));
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

		//物品图标
		for (int i = 1; i <= min(5, ceil((x.size() - (ps - 1) * 10) / (double)2)); i++)
		{
			for (int j = 0; j < min(2, x.size() - (ps - 1) * 10 - (i - 1) * 2); j++)
			{
				setfillcolor(RGB(255, 250, 205));
				fillrectangle(480 + 180 * j, 130 + 90 * (i - 1), 650 + 180 * j, 200 + 90 * (i - 1));
				settextstyle(160 / thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].ns, 80 / thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].ns, _T("宋体"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(485 + 180 * j, 140 + 90 * (i - 1), thing[x[(ps - 1) * 10 + (i - 1) * 2 + j].wz][x[(ps - 1) * 10 + (i - 1) * 2 + j].wt].name);
				settextstyle(20, 0, _T("宋体"));
				_stprintf(ss, _T("X %d"), x[(ps - 1) * 10 + (i - 1) * 2 + j].sum);
				outtextxy(535 + 180 * j, 170 + 90 * (i - 1), ss);
			}
		}

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)			//返回主页面
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
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && k > 1)	//召唤兽上一页
					bok(k - 1, 4);
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && k < bks)	//召唤兽下一页
					bok(k + 1, 4);
				if (850 <= m.x && m.x <= 880 && 270 <= m.y && m.y <= 320 && ps > 1)	//献祭物品上一页
				{
					ps--;
					break;
				}
				if (850 <= m.x && m.x <= 880 && 320 < m.y && m.y <= 370 && ps < mps)//献祭物品下一页
				{
					ps++;
					break;
				}
				for (int i = 1; i <= 4; i++)		//更换培养选项
					if (i != 4 && 890 <= m.x && m.x <= 990 && 10 + (i - 1) * 60 <= m.y && m.y <= 70 + (i - 1) * 60)
						bok(k, i);

				bool rl = 0;
				for (int i = 1; i <= ceil(x.size() / (double)2); i++)		//献祭
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
							//更新仓库物品
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
		settextstyle(25, 0, _T("楷体"));
		_stprintf(ss, _T("使用后获得%s"), pmw[thing[z][t].bh_z][thing[z][t].bh_j].race);
		outtextxy(550, 110, ss);
	}
	else if (z == 2)
	{
		if (t == 1)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("当召唤书页小于6时，使用可增加1页召唤"));
			outtextxy(550, 140, _T("书页"));
		}
		if (t == 2)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("当召唤书页小于10时，使用可增加1页召唤"));
			outtextxy(550, 140, _T("书页"));
		}
		if (t == 3)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("当召唤书页小于15时，使用可增加1页召唤"));
			outtextxy(550, 140, _T("书页"));
		}
		if (t == 4)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用后获得100经验"));
		}
		if (t == 5)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用后获得10000经验"));
		}
		if (t == 6)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用后获得1000000经验"));
		}
		if (t == 7)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用后获得100000000经验"));
		}
		if (t == 8)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用后获得10000000000经验"));
		}
		if (t == 9)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用增加10魂炼献祭值"));
		}
		if (t == 10)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用增加100魂炼献祭值"));
		}
		if (t == 11)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用增加1000魂炼献祭值"));
		}
		if (t == 12)
		{
			settextcolor(RGB(0, 0, 0));
			settextstyle(25, 0, _T("楷体"));
			outtextxy(550, 110, _T("使用增加10000魂炼献祭值"));
		}
	}
}

void sh_page(int k)
{
	int sums = 0;
	bool bl[30];
	memset(bl, 0, sizeof(bl));

	//背景
	setlinecolor(RGB(255, 255, 255));
	for (int i = 0; i <= 600; i++)
		line(0, i, 1000, i);

	//上阵图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(900, 530, 980, 580);
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("宋体"));
	outtextxy(910, 540, _T("上阵"));

	//取消图标
	setfillcolor(RGB(100, 150, 200));
	fillrectangle(800, 530, 880, 580);
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("宋体"));
	outtextxy(810, 540, _T("取消"));

	while (1)
	{

		//召唤兽图标
		for (int i = 1; i <= ceil((double)bks / (double)7); i++)
		{
			for (int j = 1; j <= min(7, bks - (i - 1) * 7); j++)
			{
				if (pt[(i - 1) * 7 + j].rsh != 0 && pt[(i - 1) * 7 + j].rsh != 13 && k != 13)setfillcolor(RGB(192, 192, 192));
				else if (bl[(i - 1) * 7 + j])setfillcolor(RGB(255, 99, 71));
				else setfillcolor(RGB(255, 250, 205));
				fillrectangle(20 + 120 * (j - 1), 60 + 80 * (i - 1), 120 + 120 * (j - 1), 120 + 80 * (i - 1));
				settextstyle(80 / pmw[pt[(i - 1) * 7 + j].clan][pt[(i - 1) * 7 + j].race].ns, 40 / pmw[pt[(i - 1) * 7 + j].clan][pt[(i - 1) * 7 + j].race].ns, _T("宋体"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(25 + 120 * (j - 1), 80 + 80 * (i - 1), pmw[pt[(i - 1) * 7 + j].clan][pt[(i - 1) * 7 + j].race].race);
			}
		}

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//选择要上阵的魔物
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

				//上阵
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
					//排序
					for (int i = 1; i <= bks; i++)
						for (int j = i + 1; j <= bks; j++)
							if (pt[i].rsh != 0 && pt[j].rsh != 0 && pt[i].rsh > pt[j].rsh)
								swap(pt[i], pt[j]);
							else if (pt[i].rsh == 0 && pt[j].rsh != 0)
								swap(pt[i], pt[j]);

					zr_page();
				}

				//取消
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

		//保存
		outs();

		//背景
		setlinecolor(RGB(255, 255, 255));
		for (int i = 0; i <= 600; i++)
			line(0, i, 1000, i);

		//返回图标
		setfillcolor(RGB(100, 150, 200));
		fillrectangle(900, 530, 980, 580);
		settextcolor(RGB(0, 0, 0));
		settextstyle(30, 0, _T("宋体"));
		outtextxy(910, 540, _T("返回"));

		//上一页/下一页
		setfillcolor(RGB(200, 150, 100));
		fillrectangle(180, 540, 280, 570);
		settextstyle(16, 0, _T("宋体"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(182, 545, _T("上一页"));
		outtextxy(232, 545, _T("下一页"));
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

		//大类别图标
		setfillcolor(RGB(210, 105, 30));
		for (int i = 1; i <= 2; i++)
			fillrectangle(50 + 100 * (i - 1), 60, 150 + 100 * (i - 1), 120);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(50 + 100 * (t - 1), 60, 150 + 100 * (t - 1), 120);
		settextcolor(RGB(0, 0, 0));
		settextstyle(30, 0, _T("宋体"));
		outtextxy(70, 75, _T("精魄"));
		outtextxy(170, 75, _T("道具"));

		//玉石数量
		settextcolor(RGB(0, 0, 0));
		settextstyle(30, 0, _T("楷体"));
		_stprintf(ss, _T("玉石：%d"), ys);
		outtextxy(50, 20, ss);

		//商品图标
		for (int i = 1; i <= min(ceil(((double)wpls[t] - (z - 1) * 24) / (double)5), 4); i++)
		{
			for (int j = 1; j <= min(6, wpls[t] - (z - 1) * 24 - (i - 1) * 6); j++)
			{
				if (thing[t][(z - 1) * 24 + (i - 1) * 6 + j].b_jg > 0)setfillcolor(RGB(255, 250, 205));
				else setfillcolor(RGB(192, 192, 192));
				fillrectangle(50 + 150 * (j - 1), 150 + 80 * (i - 1), 180 + 150 * (j - 1), 210 + 80 * (i - 1));
				settextstyle(120 / thing[t][(z - 1) * 24 + (i - 1) * 6 + j].ns, 0, _T("宋体"));
				settextcolor(RGB(0, 0, 0));
				outtextxy(55 + 150 * (j - 1), 170 + 80 * (i - 1), thing[t][(z - 1) * 24 + (i - 1) * 6 + j].name);
			}
		}

		//选择
		while (1)
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				//返回主页面
				if (900 <= m.x && m.x <= 980 && 530 <= m.y && m.y <= 580)main_page();

				//上一页
				if (180 <= m.x && m.x <= 230 && 540 <= m.y && m.y <= 570 && z > 1)
				{
					z--;
					break;
				}

				//下一页
				if (230 < m.x && m.x <= 280 && 540 <= m.y && m.y <= 570 && z < ceil((double)wpls[t] / (double)24))
				{
					z++;
					break;
				}

				//换大类别
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

				//查看商品
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

	//哥布林族
	//1层
	x.name = _T("抓狂"), x.cs = 1, x.lb = 1, x.bh = 1; pjn[1][1][1] = x;
	//2层
	//3层
	//4层
	x.name = _T("智集"), x.cs = 4, x.lb = 1, x.bh = 2; pjn[1][4][1] = x;
	//5层

	//石人族
	//1层
	x.name = _T("石盾"), x.cs = 1, x.lb = 1, x.bh = 3; pjn[2][1][1] = x;
	//2层
	x.name = _T("石岩墙"), x.cs = 2, x.lb = 1, x.bh = 4; pjn[2][2][1] = x;
	x.name = _T("晶灵"), x.cs = 2, x.lb = 1, x.bh = 5; pjn[2][2][2] = x;
	//3层
	//4层
	//5层

	//火焰鸡族
	//1层
	x.name = _T("炽心"), x.cs = 1, x.lb = 1, x.bh = 6; pjn[3][1][1] = x;
	//2层
	//3层
	//4层
	//5层

	//水元素族
	//1层
	//2层
	//3层
	//4层
	//5层
}

int main()
{
	srand((int)time(0));		//随机数种子
	cl();

	initgraph(1000, 600);
	setbkmode(TRANSPARENT);

	open();
	main_page();

	closegraph();
	return 0;
}