#include"musicPlayer.h"

/**************************************************************************************************************
*  MusiMusicMCI method                                                                                        *
***************************************************************************************************************/

MusicMCI::MusicMCI()
{
	nDeviceID = -1;
}

// 打开文件
// 成功返回非零值，失败返回0
BOOL MusicMCI::open(LPCWSTR strSongPath)
{
	MCI_OPEN_PARMS mciOP;

	mciOP.lpstrDeviceType = nullptr;
	mciOP.lpstrElementName = strSongPath;
	const DWORD dwReturn = mciSendCommand(0, MCI_OPEN,
		MCI_OPEN_ELEMENT | MCI_WAIT | MCI_OPEN_SHAREABLE, (DWORD)static_cast<LPVOID>(&mciOP));
	if (dwReturn == 0)
	{
		nDeviceID = mciOP.wDeviceID;
		return TRUE;
	}
	else
	{
		nDeviceID = -1;
		return FALSE;
	}
}

// 播放
// 成功返回非零值，失败返回0
BOOL MusicMCI::play()
{
	MCI_PLAY_PARMS mciPP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PLAY,
		MCI_NOTIFY, (DWORD)static_cast<LPVOID>(&mciPP));
	if (dwReturn == 0)
		return TRUE;
	else
		return FALSE;
}

// 暂停播放
// 成功返回非零值，失败返回0
BOOL MusicMCI::pause()
{
	MCI_GENERIC_PARMS mciGP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PAUSE,
		MCI_NOTIFY | MCI_WAIT, (DWORD)static_cast<LPVOID>(&mciGP));
	if (dwReturn == 0)
		return TRUE;
	else
		return FALSE;
}

// 停止播放并使进度返回到开头
// 成功返回非零值，失败返回0
BOOL MusicMCI::stop()
{
	MCI_SEEK_PARMS mciSP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_SEEK,
		MCI_WAIT | MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)static_cast<LPVOID>(&mciSP));
	if (dwReturn == 0)
		return TRUE;
	else
		return FALSE;
}

// 关闭MCI设备
// 成功返回非零值，失败返回0
BOOL MusicMCI::close()
{
	MCI_GENERIC_PARMS mciGP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_CLOSE,
		MCI_NOTIFY | MCI_WAIT, (DWORD)static_cast<LPVOID>(&mciGP));
	if (dwReturn == 0)
		return TRUE;
	else
		return FALSE;
}

// 获得当前播放进度，pos以ms为单位
// 成功返回非零值，失败返回0
BOOL MusicMCI::getPlayBackTime(DWORD& pos)
{
	MCI_STATUS_PARMS mciSP{};

	mciSP.dwItem = MCI_STATUS_POSITION;
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_STATUS,
		MCI_STATUS_ITEM, (DWORD)static_cast<LPVOID>(&mciSP));
	if (dwReturn == 0)
	{
		pos = mciSP.dwReturn;
		return TRUE;
	}
	else
	{
		pos = 0;
		return FALSE;
	}
}

// 获取音乐总时长，time以ms为单位
// 成功返回TRUE，失败返回FALSE
BOOL MusicMCI::getMusicTime(DWORD& time)
{
	MCI_STATUS_PARMS mciSP{};

	mciSP.dwItem = MCI_STATUS_LENGTH;
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_STATUS,
		MCI_WAIT | MCI_STATUS_ITEM, (DWORD)static_cast<LPVOID>(&mciSP));		// 关键,取得长度
	if (dwReturn == 0)
	{
		time = mciSP.dwReturn;
		return TRUE;
	}
	else
	{
		time = 0;
		return FALSE;
	}
}

// 音量设定，音量值范围在0到1000
// 成功返回非零值，失败返回0
BOOL MusicMCI::setVolume(size_t nVolumeValue)
{
	if (nVolumeValue > 1000)
	{
		nVolumeValue = 1000;
	}
	else if (nVolumeValue < 0)
	{
		nVolumeValue = 0;
	}

	MCI_DGV_SETAUDIO_PARMS mciDSP;
	mciDSP.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciDSP.dwValue = nVolumeValue;
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_SETAUDIO,
		MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)static_cast<LPVOID>(&mciDSP));
	if (dwReturn == 0)
		return TRUE;
	else
		return FALSE;
}



/**************************************************************************************************************
* MusicData method                                                                                          *
**************************************************************************************************************/

/**************************************************************
* MusicData private method                                    *
**************************************************************/

// 打开并播放音乐
void MusicData::openMusic(size_t num)
{
	if (num >= musicPathName.size())
	{
		cout << "参数不符合要求，请重试！" << endl;
		status = 0;
		return;
	}

	wstring musci_name = stringTowstring(musicPathName.at(num));
	nowMusicName.assign(musicName.at(num));							// 设置正在操作的音乐名
	number = num;													// 设置正在操作的音乐名编号
	if (musicMci.open(musci_name.c_str()))
	{
		cout << "音乐打开成功！" << endl;

		playMusic();
		musicMci.setVolume(volume);
	}
	else
		cout << "音乐打开失败，请稍后重试！" << endl;
}

// 播放音乐
void MusicData::playMusic()
{
	if (musicMci.play())
	{
		cout << "音乐" << nowMusicName << "播放成功！" << endl;
		status = 1;
	}
	else
	{
		cout << "音乐" << nowMusicName << "播放失败！" << endl;
		status = 0;
	}
}

// 暂停播放
void MusicData::pauseMusic()
{
	if (status)
	{
		if (musicMci.pause())
		{
			cout << "音乐已暂停！" << endl;
			status = 2;
		}
		else
			cout << "音乐暂停失败！" << endl;
	}
}

// 停止播放
void MusicData::stopMusic()
{
	if (musicMci.stop())
	{
		cout << "音乐已停止！" << endl;
		status = 0;
	}
	else
		cout << "音乐停止失败！" << endl;
}

// 关闭音乐
void MusicData::closeMusic()
{
	if (musicMci.close())
	{
		cout << "音乐已关闭！" << endl;
		status = 0;
	}
	else
		cout << "音乐关闭失败！" << endl;
}

// 获取音乐当前播放时间
int MusicData::getPlayerBackTimeMusic()
{
	if (status)
	{
		DWORD playTime = 0;
		if (!musicMci.getPlayBackTime(playTime))
		{
			cout << "获取播放时长失败！" << endl;
			return 0;
		}
		return playTime / 1000;
	}
}

// 获取音乐总播放时间
int MusicData::getTotalTime()
{
	if (status)
	{
		DWORD totalTime = 0;
		if (!musicMci.getMusicTime(totalTime))
		{
			cout << "获取总时长失败！" << endl;
			return 0;
		}
		return totalTime / 1000;
	}
}


// string转wstring
wstring MusicData::stringTowstring(const string& str)
{
	wstring result;
	// 获取缓冲区大小，并申请空间，缓冲区大小按字符计算
	const size_t len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), nullptr, 0);
	vector<TCHAR> buffer(len + 1u);
	// 多字节编码转换成宽字节编码
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), &buffer.at(0), len);
	buffer.at(len) = '\0';			// 添加字符串结尾
	result.append(&buffer.at(0));
	return result;
}

// 从文件filePath.ad中读取搜索路径
void MusicData::getFilePath()
{
	fstream fPath("filePath.ad", ios_base::in);
	if (!fPath.is_open())
	{
		cerr << "文件filePath.ad打开失败，此文件可能不存在！" << endl;
		cerr << "程序将尝试新建此文件!" << endl;

		fPath.open("filePath.ad", ios_base::in | ios_base::out | ios_base::trunc);
		if (!fPath.is_open())
		{
			cerr << "文件filePath.ad创建失败！，程序可能遇到了一些问题！" << endl;
			cerr << "请稍后重试！" << endl;
		}
		else
		{
			cout << "文件filePath.ad创建成功！" << endl;
		}
	}
	else
	{
		wFilePath(fPath);
	}
}

// 获取特定格式的文件名    
void MusicData::findMusicName(const string& path)
{
	long  hFile = 0;																					// 文件句柄  64位下long 改为 intptr_t
	struct _finddata_t fileinfo;																		//	文件信息 
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)					// 查找所有文件
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))															// 判断是否为文件夹
			{
				if (strcmp(&fileinfo.name[0], ".") != 0 && strcmp(&fileinfo.name[0], "..") != 0)		// 文件夹名中不含"."和".."
				{
					findMusicName(p.assign(path).append("\\").append(&fileinfo.name[0]));				// 递归遍历文件夹
				}
			}
			else
			{
				string suffix(&fileinfo.name[0]);
				if (suffix.size() > musicFormat.size())
					suffix = suffix.substr(suffix.size() - musicFormat.size());
				if (suffix == musicFormat)
				{
					musicPathName.push_back(p.assign(path).append("\\").append(&fileinfo.name[0]));				// 是改革是文件，储存文件名

					string temp(&fileinfo.name[0]);
					musicName.push_back(temp.substr(0, temp.size() - musicFormat.size() - 1));					// 截取出音乐名
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

// 将filePath写入文件filePath.ad
void MusicData::wFilePath(fstream& file)
{
	file << filePath << endl;
}

// 将文件filePath.ad读取到filePath
void MusicData::rFilePath(fstream& file)
{
	string temp;
	getline(file, temp);
	if (temp.empty() || temp.at(0) == '\n')
	{
		cout << "文件内容为空！" << endl;
		cout << "文件路径设置为默认！" << endl;
	}
	else
		filePath = std::move(temp);
}


// 将musicPathName写入文件music.mn中
void MusicData::wFileMusic(fstream& file)
{
	if (!musicPathName.empty())
		for (auto& x : musicPathName)
			file << x << endl;
	cout << "文件music.mn写入完毕！" << endl;
}

// 从music.mn读取到musicPathName和musicName中
void MusicData::rFileMusic(fstream& file)
{
	string s;
	do
	{
		getline(file, s);
		musicPathName.push_back(s);

		musicName.push_back(s.substr(s.rfind("\\") + 1, s.size() - s.rfind("\\") - 1 - musicFormat.size() - 1));									// 截取出音乐名			// 截取出音乐名

	} while (!file.eof());
	cout << "文件musci.mn读取完毕！" << endl;
}

// 设置音乐音量
void MusicData::setMusicVolume(size_t vol)
{
	if (status)
	{
		if (musicMci.setVolume(vol))
			volume = vol;
		else
			cout << "音量设置失败！" << endl;
	}
	else
	{
		volume = vol;
	}
}

// 删除歌曲
void MusicData::deleteMusicData(vector<int>& vec)		
{
	sort(vec.begin(), vec.end());										// 对其进行排序，方便下面修正
	for (decltype(vec.size()) i = 0; i < vec.size(); ++i)
	{
		vec.at(i) -= i;													// 修正要删除的下标信息

		musicName.erase(musicName.begin() + vec.at(i));					// 删除对应下标的数据
		musicPathName.erase(musicPathName.begin() + vec.at(i));
	}
}

/**************************************************************
*  MusicData public method                                    *
**************************************************************/

// 默认构造函数
MusicData::MusicData()
{
	srand(time(nullptr) & 0xffffffff);
	getFilePath();																// 初始化搜索的文件路径

	cout << "文件搜索路径为：" << filePath << endl;
	fstream file("music.mn", ios_base::in);
	if (!file.is_open())
	{
		cerr << "文件music.mn打开失败，此文件可能不存在" << endl;
		cerr << "程序将尝试新建此文件，并初始化文件内容" << endl;

		file.open("music.mn", ios_base::out);
		if (!file.is_open())
		{
			cerr << "文件music.mn创建失败！" << endl;
			cerr << "程序可能遇到了一些问题！" << endl;
			cerr << "程序即将退出！" << endl;
			system("pause");
			exit(0);
		}

		cout << "文件music.mn创建成功！" << endl;
		findMusicName(filePath);
		wFileMusic(file);
	}

	rFileMusic(file);
	file.close();
	nowMusicName = "";

	if (!musicPathName.empty())
		musicPathName.pop_back();																		// 删除最后一个空白行

	if (!musicName.empty())
		musicName.pop_back();
}

// 析构函数
MusicData::~MusicData()
{
	closeMusic();
}



/**********************************************************************************************************************
*  class MusicPlayer                                                                                                  *
**********************************************************************************************************************/

/**************************************************************
* MusicPlayer private method                                  *
**************************************************************/

// 设置光标位置
void MusicPlayer::pos(short x, short y)
{
	COORD pos{ x,y };
	HANDLE hOutput = nullptr;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

// 设置音乐音量
void MusicPlayer::setMusicVolume()
{
	size_t vol = 0;
	cout << "当前音量：" << musicData.volume << endl;
	cout << "请输入音量值（0-1000）：";
	cin >> vol;
	if (vol <= 1000)
		musicData.setMusicVolume(vol);
	else
	{
		cout << "输入错误！" << endl;
		Sleep(1000);
	}
}

// 设置搜索路径并写入filePath.ad中
void MusicPlayer::setFilePath()
{
	string temp;
	cout << "当前搜索路径为：" << musicData.filePath << endl;
	cout << "请输入新的搜索路径(请输入绝对路径！)：";
	cin >> temp;
	cout << "新的搜索路径为：" << temp << endl;
	cout << "是否修改？（y/n）:";
	char ch = 0;
	cin >> ch;
	if ('y' == ch || 'Y' == ch)
	{
		musicData.filePath = temp;
		fstream fp("filePath.ad", ios_base::out);
		if (!fp.is_open())
		{
			cerr << "文件filePath.ad打开失败，请稍后重试！" << endl;
		}
		else
		{
			musicData.wFilePath(fp);										
			fp.close();
			cout << "搜索路径写入完毕！" << endl;

			musicData.findMusicName(musicData.filePath);					// 寻找音乐文件
			fstream file("music.mn", ios_base::out);						// 截断打开，重新写入
			if (!file.is_open())
			{
				cerr << "文件music.mn打开失败，请稍后重试此功能！" << endl;
				Sleep(1000);
			}
			else
			{
				musicData.wFileMusic(file);									// 写入音乐全路径名
				file.close();
				cout << "写入新歌曲名成功！" << endl;
			}
			cout << "以搜索完毕新路径下的歌曲！" << endl;
		}
	}
	else
	{
		cout << "已取消修改！" << endl;
	}
}

// 设置播放模式
void MusicPlayer::setPlayMode()
{
	size_t cho = 0;
	cout << "0.单曲循环" << endl;
	cout << "1.顺序播放" << endl;
	cout << "2.随机播放" << endl;
	cout << "当前播放模式：";
	if (musicData.mode == 0)
		cout << "单曲循环" << endl;
	else if (musicData.mode == 1)
		cout << "顺序播放" << endl;
	else if (musicData.mode == 2)
		cout << "随机播放" << endl;

	cout << "请选择你要选择的播放模式：";
	cin >> cho;
	if (cho <= 2)
		musicData.mode = cho;
}

// 删除音乐
void MusicPlayer::deleteMusic()
{
	system("cls");
	showMusicName();
	cout << "（提示：输入想删除音乐的序号并回车，若输入完毕，输入非数字即可！）" << endl;
	cout << "请输入你想删除的音乐：";
	vector<int> tvec;
	int it = 0;
	while (cin >> it)
	{
		tvec.push_back(it);
		cout << "请输入你想删除的音乐：";
	}
	cin.clear();
	while (cin.get() != '\n');											// 清空输入缓冲区
	cout << "将要删除以下歌曲：" << endl;
	for (auto x : tvec)
		cout << x << "  " << musicData.musicName.at(x) << endl;
	cout << "是否删除?（y/n）:";
	char ch = 0;
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
	{
		cout << "删除音乐中，请稍后..." << endl;
		musicData.deleteMusicData(tvec);								// 删除其中的音乐
		cout << "音乐列表删除完成！" << endl;
		cout << "文件music.mn内容更新中..." << endl;

		fstream ft("music.mn", ios_base::out);
		if (!ft.is_open())
		{
			cerr << "文件music.mn打开失败了，请稍后重试！" << endl;
		}
		else
		{
			musicData.wFileMusic(ft);
			ft.close();
			cout << "文件music.mn内容更新完成！" << endl;
		}
	}
	else
	{
		cout << "已取消音乐删除！" << endl;
	}
	Sleep(2000);
}

// 选择音乐播放
void MusicPlayer::chooseMusicPlay()
{
	system("cls");
	size_t choose = 0;
	showMusicName();
	cout << "（提示：输入超出范围的值将退出选择！）" << endl;
	cout << "请选择你想播放的歌曲：";
	cin >> choose;
	if (choose < musicData.musicName.size())
	{
		musicData.number = choose;
		if (musicData.status)
			musicData.closeMusic();
		musicData.openMusic(choose);
	}
	else
	{
		cout << "已退出选择！" << endl;
		Sleep(1000);
	}
	system("cls");
}

// 显示音乐播放列表
void MusicPlayer::showMusicName()
{
	if (musicData.musicName.empty())
	{
		cout << "无播放列表！" << endl;
		return;
	}

	size_t i = 0;
	cout << "播放列表：" << endl;
	for (auto& x : musicData.musicName)
		cout << i++ << "  " << x << endl;
}

// 显示播放信息
void MusicPlayer::showPlayInformation()
{
	int t = 0, t0 = 0;
	if (musicData.status)
	{
		t = musicData.getPlayerBackTimeMusic();
		t0 = musicData.getTotalTime();
	}
	auto chonum = [](size_t a, size_t b) {return a > b ? 0 : a; };		// lamdom表达式
	if (musicData.status && t == t0)											// 播放是否结束
	{
		musicData.status = 3;
		musicData.closeMusic();
		if (musicData.mode == 0)
		{
			musicData.openMusic(musicData.number);
			system("cls");
		}
		else if (musicData.mode == 1)
		{
			musicData.openMusic(chonum(musicData.number + 1, musicData.musicName.size() - 1));
			system("cls");
			if (!musicData.status)
			{
				cout << "音乐" << musicData.nowMusicName << "播放失败！" << endl;
				cout << "即将播放下一首音乐：" << musicData.musicName.at(chonum(musicData.number + 1,
					musicData.musicName.size() - 1)) << endl;
				Sleep(2000);
				musicData.openMusic(chonum(musicData.number + 1, musicData.musicName.size()));
			}
			system("cls");
		}
		else if (musicData.mode == 2)
		{
			musicData.openMusic(rand() % musicData.musicName.size());
			system("cls");
			if (!musicData.status)
			{
				const size_t stemp = rand() % musicData.musicName.size();
				cout << "音乐：" << musicData.nowMusicName << "  播放失败！" << endl;
				cout << "即将播放下一首音乐：" << musicData.musicName.at(stemp) << endl;
				Sleep(2000);
				musicData.openMusic(stemp);
			}
			system("cls");
		}
	}
	static short x = 120 / 2;
	if (musicData.status == 1)
		x = --x < 0 ? 120 : --x;
	pos(0, 27);
	cout << "                                                                                                                            ";
	pos(x, 27);
	if (musicData.status == 0)
		cout << "暂无播放！" << endl;
	else if (musicData.status == 1)
		cout << "正在播放：" << musicData.nowMusicName << endl;
	else if (musicData.status == 2)
		cout << "已暂停播放：" << musicData.nowMusicName << endl;
	else if (musicData.status == 3)
		cout << "播放结束：" << musicData.nowMusicName << endl;

	pos(0, 28);
	cout << "                                                                                                                            ";
	pos(0, 28);
	cout << "已播放：" << t / 60 << "分" << t % 60 << "秒" << "			"
		<< "总时长：" << t0 / 60 << "分" << t0 % 60 << "秒" << "		"
		<< "音量：" << musicData.volume << "		"
		<< "播放模式：";
	if (musicData.mode == 0)
		cout << "单曲循环" << endl;
	else if (musicData.mode == 1)
		cout << "顺序播放" << endl;
	else if (musicData.mode == 2)
		cout << "随机播放" << endl;
}


/**************************************************************
* MusicPlayer public method                                   *
**************************************************************/

// 功能选择
int MusicPlayer::chooseFunction()
{
	system("cls");
	do
	{
		showPlayInformation();

		pos(0, 0);
		cout << "0.退出" << endl;
		cout << "1.暂停" << endl;
		cout << "2.继续" << endl;
		cout << "3.音量调节" << endl;
		cout << "4.删除音乐" << endl;
		cout << "5.选择音乐播放" << endl;
		cout << "6.设置播放模式" << endl;
		cout << "7.设置搜索路径" << endl;
		cout << "请输入你想选择的功能：";
		Sleep(500);
	} while (!_kbhit());

	size_t n = 0;
	cin >> n;
	switch (n)
	{
	case 0:cout << "已退出播放！" << endl; Sleep(1000); return 0;
	case 1:musicData.pauseMusic(); break;
	case 2:musicData.playMusic(); break;
	case 3:setMusicVolume(); break;
	case 4:deleteMusic(); break;
	case 5:chooseMusicPlay(); break;
	case 6:setPlayMode(); break;
	case 7:setFilePath(); break;
	default:cout << "选择错误！" << endl; break;
	}
	return 1;
}