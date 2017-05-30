#include <graphics.h>
#include <string.h>
#include <stdio.h>             //sprintf将整数转换为字符串      
#include <time.h>              //srand产生随机数
#define SQU_LONG 15            //正方形的长
#define SQU_NUMBER 30          //正方形个数
#pragma comment(lib,"Winmm.lib")               //导入音乐头文件

IMAGE img,right,stop,play,fail,change;         //定义背景，右边，游戏暂停，正在游戏，游戏失败，分数改变图片
int NUM=3;                                     //节点个数
char score[5];                                 //存储分数的字符串
int foodx,foody;                               //食物的坐标，用于批绘制

void food();                            //产生食物
void snakeMove();                       //蛇移动
int Direction(int savec);               //控制方向
void eat();                             //吃食物
void over();                            //蛇死亡

struct snake
{
	int x;                      //蛇头x坐标
	int y;                      //蛇头y坐标
	int dire;                   //蛇头方向
	struct snake *next;         //结构体指针
};
struct snake *head=(snake *)malloc(sizeof(snake));           //定义头指针
struct snake *p;                                             //用于遍历结构体
struct snake saveLast,saveBody;                              //saveLast用于保存前一个节点，saveBody用于保存后一个节点 

void main()//主方法
{
	initgraph(SQU_LONG*SQU_NUMBER+200,SQU_LONG*SQU_NUMBER);		    //创建画布
	loadimage(&img,"image/bk_picture.jpg");                         //读取背景图片
	putimage(0,0,&img);                                             //在坐标(0,0)处放置背景图片
	loadimage(&right,"image/right.jpg");                            
	putimage(495,0,&right);                                                                                     
	settextcolor(WHITE);											//文字颜色为白色
	setbkmode(TRANSPARENT);                                         //文字背景为透明
	settextstyle(20,0,"楷体");                                      //文字字号为20，正常宽度，字体为楷体
	outtextxy(530,40,"游戏规则：");                                 //在坐标(530,70)处输出“游戏规则”四个字，只能输出字符串格式
	outtextxy(502,70,"方向键控制方向");
	outtextxy(502,90,"  Space键暂停");
	outtextxy(502,110,"  Shift键加速");	
	loadimage(&play,"image/play.jpg");
	putimage(495,290,&play);
	mciSendString("open music/bk_audio.mp3 alias bk_audio",NULL,0,NULL);            //读取背景音乐文件并命名为bk_audio
	mciSendString("play bk_audio repeat",NULL,0,NULL);                              //repeat为循环播放

	int x,y;                                        //蛇头坐标        
	srand((unsigned)time(NULL));                    //产生随机数的语句，与rand()连用
	do
	{
		x=rand()%SQU_LONG*SQU_NUMBER;               //先算求余，后算乘法，随机产生蛇头的坐标
		y=rand()%SQU_LONG*SQU_NUMBER;
	}while(x>SQU_LONG*(SQU_NUMBER-3)||y>SQU_LONG*(SQU_NUMBER-3)||x<3*SQU_LONG||y<3*SQU_LONG);             //不能出现在四周靠边的位置
	struct snake *a=(snake *)malloc(sizeof(snake));             //用于存储蛇头
	struct snake *b=(snake *)malloc(sizeof(snake));             //一开始出现的第一节身子
	struct snake *c=(snake *)malloc(sizeof(snake));             //一开始出现的第二节身子
	p=head;                           //p指向head
	p->next=a;
	a->x=x;
	a->y=y;
	a->dire=rand()%4+1;               //a为蛇头，随机产生方向
	a->next=b;
	b->next=c;
	c->next=NULL;	                  //一开始只有一个蛇头两个身子，最后一个身子无指向
	p=p->next;                        //p指向蛇头
	setfillcolor(RED);                //设置填充颜色红色，表示蛇头
	bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);              //在(p->x,p->y)处画一个长度为SQU_LONG的填充红色的正方形	
	saveLast.x=p->x;                  //将移动前蛇头信息保存为上一个节点的信息
	saveLast.y=p->y;
	saveLast.dire=p->dire;
	saveLast.next=p->next;
	if(p->dire==1)
		p->x-=SQU_LONG;         //向左，p->x-1
	else if(p->dire==2)         
		p->y-=SQU_LONG;         //向上，p->y-1
	else if(p->dire==3)
		p->x+=SQU_LONG;         //向右，p->x+1
	else if(p->dire==4)
		p->y+=SQU_LONG;         //向下，p->y+1
	setfillcolor(RED);          //移动后重新画蛇头
	bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);              //在移动后坐标处画一个长度为SQU_LONG的填充红色的正方形
	p=p->next;                  //p指向第一个身子
	while(p)                           //p不为空就进入循环，一开始设置链表有三个节点，一共可进入两次
	{
		saveBody.x=p->x;               //将移动后的信息保存为现在节点的信息
		saveBody.y=p->y;
		saveBody.dire=p->dire;
		p->x=saveLast.x;               //重新将保存的移动前的信息读取出，赋给当前p指向的身子
		p->y=saveLast.y;
		p->dire=saveLast.dire;
		saveLast.x=saveBody.x;         //保存的移动前的失去作用，重新将移动后的再作为上一个节点，保证蛇每个身子记录前一个身子的信息
		saveLast.y=saveBody.y;
		saveLast.dire=saveBody.dire;
		setfillcolor(YELLOW);          //设置填充颜色黄色，表示蛇身子
		bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);		        //在读取到信息的坐标处画一个长度为SQU_LONG的填充黄色的正方形
		p=p->next;                     //p指向下一个身子
	}	
	food();                      //调用生成食物方法
	snakeMove();	             //调用蛇移动方法
}

void food()//生成食物       
{
	int x,y;                             //食物坐标
	do
	{
		x=rand()%SQU_LONG*SQU_NUMBER+SQU_LONG;
		y=rand()%SQU_LONG*SQU_NUMBER+SQU_LONG;
	}while(getpixel(x,y)==RED||getpixel(x,y)==YELLOW||x>SQU_LONG*(SQU_NUMBER-1)||y>SQU_LONG*(SQU_NUMBER-1));        //不能出现在蛇头和蛇身上还有边框右边和下边
	foodx=x;                             //将坐标保存为全局变量，用于其他方法批绘制
	foody=y;
}

void snakeMove()//蛇移动
{	
	int i,savec;                //savec用于在选择方向是临时保存     
	while(1)
	{			
		p=head->next;                              //p指向蛇头
		saveLast.x=p->x;                           //依然是将移动前蛇头信息保存为上一节点信息
		saveLast.y=p->y;
		saveLast.dire=p->dire;
		if(p->dire==1)
			p->x-=SQU_LONG;                        //向左，p->x-1
		else if(p->dire==2)
			p->y-=SQU_LONG;                        //向上，p->y-1
		else if(p->dire==3)
			p->x+=SQU_LONG;                        //向右，p->x+1
		else if(p->dire==4)
			p->y+=SQU_LONG;                        //向下，p->y+1
		p=p->next;                                 //p指向第一个身子
		while(p)
		{
			saveBody.x=p->x;                       //依然是将移动后信息保存为现在节点的信息
			saveBody.y=p->y;
			saveBody.dire=p->dire;
			p->x=saveLast.x;
			p->y=saveLast.y;
			p->dire=saveLast.dire;
			saveLast.x=saveBody.x;
			saveLast.y=saveBody.y;
			saveLast.dire=saveBody.dire;
			p=p->next;                             //p指向第二个身子
		}
		p=head->next;                                         //p重新指向蛇头
		if(getpixel(p->x,p->y)==YELLOW||p->x<0||p->y<0||p->x>(SQU_LONG*(SQU_NUMBER-1)+45)||p->y>SQU_LONG*(SQU_NUMBER-1))       //如果获取到蛇头坐标的颜色为黄色（蛇头覆盖在身子上）活着蛇头碰到边缘
			over();	                                          //调用失败方法
		else if(getpixel(p->x,p->y)==GREEN)                   //如果蛇头坐标的颜色为绿色（蛇头覆盖在食物上，代表吃掉食物）
		{
			mciSendString("open music/eat_food.mp3 alias eat_food",NULL,0,NULL);           //调用吃掉食物的音乐
			mciSendString("play eat_food from 0",NULL,0,NULL);                             //from 0为播放一次
			eat();                                            //调用吃食物方法
			food();                                           //调用生成食物方法
		}
		BeginBatchDraw();                                                 //开始批绘制
		putimage(0,0,&img);                                               //每一次绘制都需要刷新，所以每次都需要调用背景图片
		p=head->next;
		setfillcolor(RED);                                    //移动后重新画蛇头
		bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);	  
		p=p->next;
		while(p)
		{
			setfillcolor(YELLOW);                             //移动后重新画身子
			bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);
			p=p->next;					
		}
		setfillcolor(GREEN);                                              //设置填充颜色为绿色，表示食物
		bar(foodx,foody,foodx+SQU_LONG-1,foody+SQU_LONG-1);               //绿色代表食物		
		outtextxy(540,200,"得分：");
		sprintf(score,"%d",(NUM-3)*10);                                   //将整数(NUM-3)*10转换为字符串保存在score中
		loadimage(&change,"image/score.jpg");
		putimage(495,220,&change);
		outtextxy(546,220,score);
		FlushBatchDraw();                                                 //每更新一次绘制一次
		p=head->next;
		for(i=0;i<5;i++)
		{
			Sleep(NUM<20?(200-4*NUM):100);	                              //蛇移动停顿的时间，随着吃的食物个数的增多停顿时间减少，减少到0.1秒后保持不变
			savec=p->dire;                                                //将蛇头原来的方向保存到savec中
			p->dire=Direction(savec);                                     //调用按键方法并传递savec参数
			if(p->dire==5)                                                //如果选择了加速按键
			{
				p->dire=savec;                                            //方向仍然是原方向
				break;                                                    //跳出循环，不停顿
			}
		}		
		EndBatchDraw();                                                   //关闭批量绘图
	}
}

int Direction(int savec)//按键
{
	p=head->next;                                              //p指向蛇头                                                   
	if(p->dire!=3&&GetAsyncKeyState(VK_LEFT)&0x8000)           //如果原来方向不向右并且按下左键
		p->dire=1;
	else if(p->dire!=4&&GetAsyncKeyState(VK_UP)&0x8000)        //如果原来方向不向下并且按下上键
		p->dire=2;
	else if(p->dire!=1&&GetAsyncKeyState(VK_RIGHT)&0x8000)     //如果原来方向不向左并且按下右键
		p->dire=3;
	else if(p->dire!=2&&GetAsyncKeyState(VK_DOWN)&0x8000)      //如果原来方向不向上并且按下下键
		p->dire=4;
	else if(GetAsyncKeyState(VK_SHIFT)&0x8000)                 //按shift键
		p->dire=5;
	else if(GetAsyncKeyState(VK_SPACE)&0x8000)                 //按空格键
	{
		loadimage(&stop,"image/stop.jpg");
		putimage(495,290,&stop);                               //更新游戏暂停图片
		FlushBatchDraw();                                      //批绘制
		mciSendString("stop bk_audio",NULL,0,NULL);            //暂停，音乐停止
		system("pause");                                       //暂停，按任意键继续
		loadimage(&play,"image/play.jpg");
		putimage(495,290,&play);                               //更新正在游戏图片
		FlushBatchDraw();                                      //批绘制
		mciSendString("play bk_audio",NULL,0,NULL);            //音乐重新从上一次结束的地方播放
		p->dire=savec;                   //暂停结束继续向同一个方向走
	}		
	else
		p->dire=savec;                   // 若是没有选择依然是原先的方向
	return p->dire;
}

void over()//结束
{
	loadimage(&fail,"image/fail.jpg");
	putimage(495,290,&fail);                              //更新游戏失败图片
	FlushBatchDraw();                                     //批绘制
	mciSendString("stop bk_audio",NULL,0,NULL);	          //结束，音乐停止
	system("pause");
	exit(0);                                              //退出到控制台
}

void eat()//吃食物
{
	p=head;
	while(p->next!=NULL)                                  //若p不是尾节点，则继续进入循环遍历
		p=p->next;
	struct snake *a=(snake *)malloc(sizeof(snake));       //重新声明一个节点，用于添加身子
	a->x=saveLast.x;                                      //将最后保存的节点信息赋给新节点
	a->y=saveLast.y;
	a->dire=saveLast.dire;
	a->next=NULL;
	p->next=a;                                            //连接到链表中
	p=p->next;
	NUM+=1;                                               //节点个数加1
}