#define  _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include<vector>
#include"tools.h"
#pragma comment(lib,"winmm.lib")
using namespace std;
#define WIN_WIDTH 1012
#define WIN_HEIGHT 396
#define TUPIAN 5
#define WIN 30
#define ZHANGAI 6
IMAGE imgbgs[5];
IMAGE imghero[TUPIAN];
IMAGE imgheroy[TUPIAN];
IMAGE xiadun[2];
IMAGE xiaduny[2];
IMAGE shuzi[10];
IMAGE shuziy[10];
int bgx[3];
int bgspeed[3] = { 1,2,6 };
bool updata;
enum Ob
{
	wugui,  //0乌龟
	shizi,  //1狮子
	guiwu,
	xin,
	hook1,
	hook2,
	hook3,
	hook4,
};
vector<vector<IMAGE>>obstacleimgs; //存放障碍物图片
vector<vector<IMAGE>>obstacleimgsy;
typedef struct obstacle
{
	int type;
	int x, y, speed, power,index;
	bool exist;
	bool hited;
	bool pass;
}Obstacle;
Obstacle obstacle[ZHANGAI];
struct hero
{
	int x, y, index, vy,blood,score,last;
	bool jump, dun;
}hero;
void init()
{
	char name[20];
	char namey[20];
	initgraph(WIN_WIDTH, WIN_HEIGHT);

		loadimage(&imgbgs[0], "scr/0.png", 2*WIN_WIDTH,60);
		loadimage(&imgbgs[1], "scr/1.png",2*WIN_WIDTH,360);
		loadimage(&imgbgs[2], "scr/2.png", 2*WIN_WIDTH,320);
		loadimage(&imgbgs[3], "scr/3.png", 2 * WIN_WIDTH, 60);
		loadimage(&imgbgs[4], "scr/4.png", 2 * WIN_WIDTH, 360);

		for (int i = 0; i < 10; i++)
		{
			sprintf(name, "scr/shuzi/%d.png", i);
			sprintf(namey, "scr/shuzi/%dy.png", i);
			loadimage(&shuzi[i], name, 50, 100, true);
			loadimage(&shuziy[i], namey, 50, 100, true);
		}

		for (int i = 0; i < TUPIAN; i++)
		{
			sprintf(name,"scr/hero%d.png",i);
			sprintf(namey, "scr/heroy%d.png", i);
			loadimage(&imghero[i], name,150,150,true);
			loadimage(&imgheroy[i], namey,150,150,true);
		}

		hero.x = 410;
		hero.y = 230;
		hero.index = 0;
		hero.jump = false;
		hero.dun = false;
		hero.vy = -10;
		hero.blood = 100;
		hero.score = 0;
		hero.last = -1;
		updata = true;

		preLoadSound("scr/pika.mp3");
		mciSendString("play scr/bg.mp3 repeat", 0, 0, 0);

		IMAGE imgwugui;
		vector<IMAGE>imgwuguiarry;
		loadimage(&imgwugui, "scr/wugui0.png",80,80,true);
		imgwuguiarry.push_back(imgwugui);
		obstacleimgs.push_back(imgwuguiarry);

		IMAGE imgwuguiy;
		vector<IMAGE>imgwuguiyarry;
		loadimage(&imgwuguiy, "scr/wuguiy0.png", 80, 80, true);
		imgwuguiyarry.push_back(imgwuguiy);
		obstacleimgsy.push_back(imgwuguiyarry);

		IMAGE imgshizi;
		vector<IMAGE>imgshiziarry;
		for (int i = 0; i < 6; i++)
		{
			sprintf(name, "scr/shizi%d.png", i);
			loadimage(&imgshizi, name, 100, 100,true);
			imgshiziarry.push_back(imgshizi);

		}
		obstacleimgs.push_back(imgshiziarry);

		IMAGE imgshiziy;
		vector<IMAGE>imgshiziyarry;
		for (int i = 0; i < 6; i++)
		{
			sprintf(name, "scr/shiziy%d.png", i);
			loadimage(&imgshiziy, name, 100, 100, true);
			imgshiziyarry.push_back(imgshiziy);

		}
		obstacleimgsy.push_back(imgshiziyarry);

		IMAGE guiwu;
		vector<IMAGE>guiwuarry;
		for (int i = 1; i < 7; i++)
		{
			sprintf(name, "scr/wugui%d.png", i);
			loadimage(&guiwu, name, 80, 80, true);
			guiwuarry.push_back(guiwu);
		}
		obstacleimgs.push_back(guiwuarry);

		IMAGE guiwuy;
		vector<IMAGE>guiwuyarry;
		for (int i = 1; i < 7; i++)
		{
			sprintf(name, "scr/wuguiy%d.png", i);
			loadimage(&guiwuy, name, 80, 80, true);
			guiwuyarry.push_back(guiwuy);
		}
		obstacleimgsy.push_back(guiwuyarry);

		IMAGE xin;
		vector<IMAGE>xinarry;
		loadimage(&xin, "scr/xin.png", 80, 80, true);
		xinarry.push_back(xin);
		obstacleimgs.push_back(xinarry);

		IMAGE xiny;
		vector<IMAGE>xinyarry;
		loadimage(&xiny, "scr/xiny.png", 80, 80, true);
		xinyarry.push_back(xiny);
		obstacleimgsy.push_back(xinyarry);

		IMAGE zhuzi;	
		for (int i = 0; i < 4; i++)
		{
			vector<IMAGE>zhuziarry;
			sprintf(name, "scr/zhuzi%d.png", i);
			loadimage(&zhuzi, name, 90, 320,true);
			zhuziarry.push_back(zhuzi);
			obstacleimgs.push_back(zhuziarry);
		}

		IMAGE zhuziy;
		for (int i = 0; i < 4; i++)
		{
			vector<IMAGE>zhuziyarry;
			sprintf(name, "scr/zhuziy%d.png", i);
			loadimage(&zhuziy, name, 90, 320, true);
			zhuziyarry.push_back(zhuziy);
			obstacleimgsy.push_back(zhuziyarry);
		}

		for (int i = 0; i < ZHANGAI; i++)          //初始化障碍物
		{
			obstacle[i].exist = false;
		}

		loadimage(&xiadun[0], "scr/xiadun0.png",120,90,true);
		loadimage(&xiadun[1], "scr/xiadun1.png",120,90,true);
		loadimage(&xiaduny[0], "scr/xiaduny0.png", 120, 90, true);
		loadimage(&xiaduny[1], "scr/xiaduny1.png", 120, 90, true);
}

void createobstacle()
{
	int i;
	for (i = 0; i < ZHANGAI; i++)
	{
		if (obstacle[i].exist == false)
		{
			break;
		}
	}
	if (i >= ZHANGAI)
	{
		return;
	}
	obstacle[i].exist = true;
	obstacle[i].hited = false;
	obstacle[i].pass = false;
	obstacle[i].index = 0;
	obstacle[i].type = rand() % 5;
	if (hero.last>=0&&
		obstacle[hero.last].type >= hook1 &&
		obstacle[hero.last].type <= hook4 &&
		(obstacle[i].type==guiwu||obstacle[i].type == shizi)&&
		obstacle[hero.last].x>(WIN_WIDTH-200))
	{
		obstacle[i].type = wugui;
	}
	if (hero.last >= 0 &&
		obstacle[hero.last].type == xin &&
		obstacle[i].type == xin)
	{
		obstacle[i].type = wugui;
	}
	hero.last = i;
	if (obstacle[i].type == hook1)
	{
		obstacle[i].type += rand() % 4;
	}
	obstacle[i].x = WIN_WIDTH;
	obstacle[i].y = 380 - obstacleimgs[obstacle[i].type][0].getheight();
	if (obstacle[i].type == wugui)
	{
		obstacle[i].speed = 0;
		obstacle[i].power = 10;
	}
	else if (obstacle[i].type == shizi)
	{
		obstacle[i].speed = 4;
		obstacle[i].power = 15;
	}
	else if (obstacle[i].type == guiwu)
	{
		obstacle[i].speed = 8;
		obstacle[i].power = 20;
	}
	else if (obstacle[i].type == xin)
	{
		obstacle[i].speed = 0;
		obstacle[i].power = -5;
		obstacle[i].y = 180;
		if (hero.blood-obstacle[i].power >= 100 )
		{
			obstacle[i].power = -(100-hero.blood);
		}
	}
	else if(obstacle[i].type >= hook1|| obstacle[i].type <= hook4)
	{
		obstacle[i].speed = 4;
		obstacle[i].power = 15;
		obstacle[i].y = 0;
	}
}

void checkhit()
{
	for (int i = 0; i < ZHANGAI; i++)
	{
		if (obstacle[i].exist && obstacle[i].hited==false)
		{
			int a1x, a1y, a2x, a2y;
			int b1x, b1y, b2x, b2y;
			int off = 20;
			if (!hero.dun)
			{
				a1x = hero.x + 2 * off;
				a1y = hero.y + 2 * off;
				a2x = hero.x + imghero[hero.index].getwidth() - 2*off;
				a2y = hero.y + imghero[hero.index].getheight() - 2*off;
			}
			else
			{
				a1x = hero.x + 2 * off;
				a1y = hero.y + 100 + 5 * off;
				a2x = hero.x + xiadun[1].getwidth() - off;
				a2y = hero.y + xiadun[1].getheight() - off;
			}
			IMAGE img = obstacleimgs[obstacle[i].type][obstacle[i].index];
			b1x = obstacle[i].x + off;
			b1y = obstacle[i].y + off;
			b2x = obstacle[i].x + img.getwidth() - off;
			b2y = obstacle[i].y + img.getheight() - off;
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y))
			{
				hero.blood -= obstacle[i].power;
				obstacle[i].hited = true;
				if (obstacle[i].type != xin)
				{
					playSound("scr/pika.mp3");
				}
				else
				{
					obstacle[i].exist = false;
				}
			}
		}
	}
}

void run()
{
	for (int i = 0; i < 3; i++)
	{
		bgx[i] -= bgspeed[i];
		if (bgx[i] < -WIN_WIDTH)
		{
			bgx[i] = 0;
		}
	}
	if (hero.jump)
	{
		if (hero.y < 150)
		{
			hero.vy += 2;
		}
		if (hero.y >= 150 && hero.y < 230)
		{
			hero.vy -= 1;
		}
		hero.y += hero.vy;
		if (hero.y > 230)
		{
			hero.jump = false;
			hero.vy = -10;
		}
	}
	else if (hero.dun)
	{
		static int count = 0;
		//int delays[2] = { 8,30};
		count++;
		if (count >= 30)
		{
			//hero.index++;
			count = 0;
			//if (hero.index >= 2)
			//{
			//	hero.index = 0;
				hero.dun = false;
			//}
		}
	}
	else
	{
		static int count = 0;
		count++;
		if (count >= 3)
		{
			count = 0;
			hero.index = (hero.index + 1) % TUPIAN;
		}
		
	}
	static int framecount = 0;             //创建障碍物
	static int enemyfre = 50;
	framecount++;
	if (framecount > enemyfre)
	{
		framecount = 0;
		enemyfre = 40 + rand() % 60;
		createobstacle();
	}

	for (int i = 0; i < ZHANGAI; i++)
	{
		if (obstacle[i].exist)
		{
			obstacle[i].x -= obstacle[i].speed+bgspeed[2];
			if (obstacle[i].x < -2 * obstacleimgs[obstacle[i].type][0].getwidth())
			{
				obstacle[i].exist = false;
			}
			int len = obstacleimgs[obstacle[i].type].size();    //求一维数组长度
			obstacle[i].index = (obstacle[i].index + 1) % len;
		}
	}
	checkhit();
}

void updatabloodbar()
{
	drawBloodBar(10, 10, 200, 10, 2, WHITE, DARKGRAY, RED,hero.blood/100.0);
}

void updatamap()
{
	putimage(bgx[0], 0, &imgbgs[2]);
	putimage(bgx[1], 150, &imgbgs[4], SRCAND);
	putimage(bgx[1], 150, &imgbgs[1], SRCPAINT);
	putimage(bgx[2], 350, &imgbgs[3], SRCAND);
	putimage(bgx[2], 350, &imgbgs[0], SRCPAINT);
}

void updataenemy()
{
	for (int i = 0; i < ZHANGAI; i++)
	{
		if (obstacle[i].exist)
		{
			putimage(obstacle[i].x, obstacle[i].y, &obstacleimgsy[obstacle[i].type][obstacle[i].index],SRCAND);
			putimage(obstacle[i].x, obstacle[i].y, &obstacleimgs[obstacle[i].type][obstacle[i].index],SRCPAINT);
		}
	}
}

void updatahero()
{
	if (!hero.dun)
	{
		putimage(hero.x, hero.y, &imgheroy[hero.index], SRCAND);
		putimage(hero.x, hero.y, &imghero[hero.index], SRCPAINT);
	}
	else
	{
		putimage(hero.x, hero.y+60, &xiaduny[1], SRCAND);
		putimage(hero.x, hero.y+60, &xiadun[1],SRCPAINT);
	}
}

void updatasocre()
{
	char str[8];
	int x = 450;
	int y = 5;
	sprintf(str, "%d", hero.score);
	for (int i = 0; str[i]; i++)
	{
		int sz = str[i] - '0';
		putimage(x, y, &shuziy[sz], SRCAND);
		putimage(x, y, &shuzi[sz],SRCPAINT);
		x += shuzi[sz].getheight()-30;
	}
}

void jump()
{
	hero.jump = true;
	//updata = true;
}

void dun()
{
	hero.dun = true;
	//updata = true;
}

void keyevent()
{
	if (GetAsyncKeyState(VK_LBUTTON)|| GetAsyncKeyState(VK_SPACE)|| GetAsyncKeyState(VK_UP))
	{
		jump();
	}
	else if (GetAsyncKeyState(VK_RBUTTON)|| GetAsyncKeyState(VK_DOWN))
	{
		dun();
	}
}

void checkover()
{
	if (hero.blood <= 0)
	{
		loadimage(0, "scr/over.png",WIN_WIDTH,WIN_HEIGHT,true);
		FlushBatchDraw();
		mciSendString("stop scr/bg.mp3", 0, 0, 0);
		int ret = MessageBox(GetHWnd(), "充值可以立即复活哦~", "斌の小提示", MB_OKCANCEL);
		if (ret == IDOK)
		{
			hero.blood = 100;
			hero.score = 0;
			mciSendString("play scr/bg.mp3 repeat", 0, 0, 0);
		}
		else
		{
			exit;
		}
	}
}

void checksocre()
{
	for (int i = 0; i < ZHANGAI; i++)
	{
		if (obstacle[i].exist &&
			obstacle[i].pass == false &&
			obstacle[i].hited == false &&
			obstacle[i].x+obstacleimgs[obstacle[i].type][0].getwidth()<hero.x)
		{
			hero.score++;
			obstacle[i].pass = true;
			printf("%d\n", hero.score);
		}
	}
}

void checkwin()
{
	if (hero.score >= WIN)
	{
		FlushBatchDraw();
		mciSendString("play scr/win.mp3", 0, 0, 0);
		Sleep(2000);
		loadimage(0, "scr/win.png", WIN_WIDTH, WIN_HEIGHT, true);
		FlushBatchDraw();
		mciSendString("stop scr/bg.mp3", 0, 0, 0);
		int ret = MessageBox(GetHWnd(), "真棒，还要再来一局吗？", "斌の小提示", MB_OKCANCEL);
		if (ret == IDOK)
		{
			hero.blood = 100;
			hero.score = 0;
			mciSendString("play scr/bg.mp3 repeat", 0, 0, 0);
		}
		else
		{
			closegraph();
			return;
		}
	}
}

int main()
{
	init();
	int timer = 0;
	loadimage(0, "scr/start.png", WIN_WIDTH, WIN_HEIGHT, true);
	system("pause");
	while (true)
	{
		keyevent();
		timer += getDelay();
		if (timer > 15)
		{
			timer = 0;
			updata = true;
		}
		if (updata)
		{
			updata = false;
			BeginBatchDraw();
			updatamap();
			updatahero();
			updataenemy();
			updatabloodbar();
			updatasocre();
			checkwin();
			EndBatchDraw();
			checkover();
			checksocre();
			run();
		}
	}
	return 0;
}