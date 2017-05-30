#include <graphics.h>
#include <string.h>
#include <stdio.h>             //sprintf������ת��Ϊ�ַ���      
#include <time.h>              //srand���������
#define SQU_LONG 15            //�����εĳ�
#define SQU_NUMBER 30          //�����θ���
#pragma comment(lib,"Winmm.lib")               //��������ͷ�ļ�

IMAGE img,right,stop,play,fail,change;         //���屳�����ұߣ���Ϸ��ͣ��������Ϸ����Ϸʧ�ܣ������ı�ͼƬ
int NUM=3;                                     //�ڵ����
char score[5];                                 //�洢�������ַ���
int foodx,foody;                               //ʳ������꣬����������

void food();                            //����ʳ��
void snakeMove();                       //���ƶ�
int Direction(int savec);               //���Ʒ���
void eat();                             //��ʳ��
void over();                            //������

struct snake
{
	int x;                      //��ͷx����
	int y;                      //��ͷy����
	int dire;                   //��ͷ����
	struct snake *next;         //�ṹ��ָ��
};
struct snake *head=(snake *)malloc(sizeof(snake));           //����ͷָ��
struct snake *p;                                             //���ڱ����ṹ��
struct snake saveLast,saveBody;                              //saveLast���ڱ���ǰһ���ڵ㣬saveBody���ڱ����һ���ڵ� 

void main()//������
{
	initgraph(SQU_LONG*SQU_NUMBER+200,SQU_LONG*SQU_NUMBER);		    //��������
	loadimage(&img,"image/bk_picture.jpg");                         //��ȡ����ͼƬ
	putimage(0,0,&img);                                             //������(0,0)�����ñ���ͼƬ
	loadimage(&right,"image/right.jpg");                            
	putimage(495,0,&right);                                                                                     
	settextcolor(WHITE);											//������ɫΪ��ɫ
	setbkmode(TRANSPARENT);                                         //���ֱ���Ϊ͸��
	settextstyle(20,0,"����");                                      //�����ֺ�Ϊ20��������ȣ�����Ϊ����
	outtextxy(530,40,"��Ϸ����");                                 //������(530,70)���������Ϸ�����ĸ��֣�ֻ������ַ�����ʽ
	outtextxy(502,70,"��������Ʒ���");
	outtextxy(502,90,"  Space����ͣ");
	outtextxy(502,110,"  Shift������");	
	loadimage(&play,"image/play.jpg");
	putimage(495,290,&play);
	mciSendString("open music/bk_audio.mp3 alias bk_audio",NULL,0,NULL);            //��ȡ���������ļ�������Ϊbk_audio
	mciSendString("play bk_audio repeat",NULL,0,NULL);                              //repeatΪѭ������

	int x,y;                                        //��ͷ����        
	srand((unsigned)time(NULL));                    //�������������䣬��rand()����
	do
	{
		x=rand()%SQU_LONG*SQU_NUMBER;               //�������࣬����˷������������ͷ������
		y=rand()%SQU_LONG*SQU_NUMBER;
	}while(x>SQU_LONG*(SQU_NUMBER-3)||y>SQU_LONG*(SQU_NUMBER-3)||x<3*SQU_LONG||y<3*SQU_LONG);             //���ܳ��������ܿ��ߵ�λ��
	struct snake *a=(snake *)malloc(sizeof(snake));             //���ڴ洢��ͷ
	struct snake *b=(snake *)malloc(sizeof(snake));             //һ��ʼ���ֵĵ�һ������
	struct snake *c=(snake *)malloc(sizeof(snake));             //һ��ʼ���ֵĵڶ�������
	p=head;                           //pָ��head
	p->next=a;
	a->x=x;
	a->y=y;
	a->dire=rand()%4+1;               //aΪ��ͷ�������������
	a->next=b;
	b->next=c;
	c->next=NULL;	                  //һ��ʼֻ��һ����ͷ�������ӣ����һ��������ָ��
	p=p->next;                        //pָ����ͷ
	setfillcolor(RED);                //���������ɫ��ɫ����ʾ��ͷ
	bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);              //��(p->x,p->y)����һ������ΪSQU_LONG������ɫ��������	
	saveLast.x=p->x;                  //���ƶ�ǰ��ͷ��Ϣ����Ϊ��һ���ڵ����Ϣ
	saveLast.y=p->y;
	saveLast.dire=p->dire;
	saveLast.next=p->next;
	if(p->dire==1)
		p->x-=SQU_LONG;         //����p->x-1
	else if(p->dire==2)         
		p->y-=SQU_LONG;         //���ϣ�p->y-1
	else if(p->dire==3)
		p->x+=SQU_LONG;         //���ң�p->x+1
	else if(p->dire==4)
		p->y+=SQU_LONG;         //���£�p->y+1
	setfillcolor(RED);          //�ƶ������»���ͷ
	bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);              //���ƶ������괦��һ������ΪSQU_LONG������ɫ��������
	p=p->next;                  //pָ���һ������
	while(p)                           //p��Ϊ�վͽ���ѭ����һ��ʼ���������������ڵ㣬һ���ɽ�������
	{
		saveBody.x=p->x;               //���ƶ������Ϣ����Ϊ���ڽڵ����Ϣ
		saveBody.y=p->y;
		saveBody.dire=p->dire;
		p->x=saveLast.x;               //���½�������ƶ�ǰ����Ϣ��ȡ����������ǰpָ�������
		p->y=saveLast.y;
		p->dire=saveLast.dire;
		saveLast.x=saveBody.x;         //������ƶ�ǰ��ʧȥ���ã����½��ƶ��������Ϊ��һ���ڵ㣬��֤��ÿ�����Ӽ�¼ǰһ�����ӵ���Ϣ
		saveLast.y=saveBody.y;
		saveLast.dire=saveBody.dire;
		setfillcolor(YELLOW);          //���������ɫ��ɫ����ʾ������
		bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);		        //�ڶ�ȡ����Ϣ�����괦��һ������ΪSQU_LONG������ɫ��������
		p=p->next;                     //pָ����һ������
	}	
	food();                      //��������ʳ�﷽��
	snakeMove();	             //�������ƶ�����
}

void food()//����ʳ��       
{
	int x,y;                             //ʳ������
	do
	{
		x=rand()%SQU_LONG*SQU_NUMBER+SQU_LONG;
		y=rand()%SQU_LONG*SQU_NUMBER+SQU_LONG;
	}while(getpixel(x,y)==RED||getpixel(x,y)==YELLOW||x>SQU_LONG*(SQU_NUMBER-1)||y>SQU_LONG*(SQU_NUMBER-1));        //���ܳ�������ͷ�������ϻ��б߿��ұߺ��±�
	foodx=x;                             //�����걣��Ϊȫ�ֱ�����������������������
	foody=y;
}

void snakeMove()//���ƶ�
{	
	int i,savec;                //savec������ѡ��������ʱ����     
	while(1)
	{			
		p=head->next;                              //pָ����ͷ
		saveLast.x=p->x;                           //��Ȼ�ǽ��ƶ�ǰ��ͷ��Ϣ����Ϊ��һ�ڵ���Ϣ
		saveLast.y=p->y;
		saveLast.dire=p->dire;
		if(p->dire==1)
			p->x-=SQU_LONG;                        //����p->x-1
		else if(p->dire==2)
			p->y-=SQU_LONG;                        //���ϣ�p->y-1
		else if(p->dire==3)
			p->x+=SQU_LONG;                        //���ң�p->x+1
		else if(p->dire==4)
			p->y+=SQU_LONG;                        //���£�p->y+1
		p=p->next;                                 //pָ���һ������
		while(p)
		{
			saveBody.x=p->x;                       //��Ȼ�ǽ��ƶ�����Ϣ����Ϊ���ڽڵ����Ϣ
			saveBody.y=p->y;
			saveBody.dire=p->dire;
			p->x=saveLast.x;
			p->y=saveLast.y;
			p->dire=saveLast.dire;
			saveLast.x=saveBody.x;
			saveLast.y=saveBody.y;
			saveLast.dire=saveBody.dire;
			p=p->next;                             //pָ��ڶ�������
		}
		p=head->next;                                         //p����ָ����ͷ
		if(getpixel(p->x,p->y)==YELLOW||p->x<0||p->y<0||p->x>(SQU_LONG*(SQU_NUMBER-1)+45)||p->y>SQU_LONG*(SQU_NUMBER-1))       //�����ȡ����ͷ�������ɫΪ��ɫ����ͷ�����������ϣ�������ͷ������Ե
			over();	                                          //����ʧ�ܷ���
		else if(getpixel(p->x,p->y)==GREEN)                   //�����ͷ�������ɫΪ��ɫ����ͷ������ʳ���ϣ�����Ե�ʳ�
		{
			mciSendString("open music/eat_food.mp3 alias eat_food",NULL,0,NULL);           //���óԵ�ʳ�������
			mciSendString("play eat_food from 0",NULL,0,NULL);                             //from 0Ϊ����һ��
			eat();                                            //���ó�ʳ�﷽��
			food();                                           //��������ʳ�﷽��
		}
		BeginBatchDraw();                                                 //��ʼ������
		putimage(0,0,&img);                                               //ÿһ�λ��ƶ���Ҫˢ�£�����ÿ�ζ���Ҫ���ñ���ͼƬ
		p=head->next;
		setfillcolor(RED);                                    //�ƶ������»���ͷ
		bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);	  
		p=p->next;
		while(p)
		{
			setfillcolor(YELLOW);                             //�ƶ������»�����
			bar(p->x,p->y,p->x+SQU_LONG-1,p->y+SQU_LONG-1);
			p=p->next;					
		}
		setfillcolor(GREEN);                                              //���������ɫΪ��ɫ����ʾʳ��
		bar(foodx,foody,foodx+SQU_LONG-1,foody+SQU_LONG-1);               //��ɫ����ʳ��		
		outtextxy(540,200,"�÷֣�");
		sprintf(score,"%d",(NUM-3)*10);                                   //������(NUM-3)*10ת��Ϊ�ַ���������score��
		loadimage(&change,"image/score.jpg");
		putimage(495,220,&change);
		outtextxy(546,220,score);
		FlushBatchDraw();                                                 //ÿ����һ�λ���һ��
		p=head->next;
		for(i=0;i<5;i++)
		{
			Sleep(NUM<20?(200-4*NUM):100);	                              //���ƶ�ͣ�ٵ�ʱ�䣬���ųԵ�ʳ�����������ͣ��ʱ����٣����ٵ�0.1��󱣳ֲ���
			savec=p->dire;                                                //����ͷԭ���ķ��򱣴浽savec��
			p->dire=Direction(savec);                                     //���ð�������������savec����
			if(p->dire==5)                                                //���ѡ���˼��ٰ���
			{
				p->dire=savec;                                            //������Ȼ��ԭ����
				break;                                                    //����ѭ������ͣ��
			}
		}		
		EndBatchDraw();                                                   //�ر�������ͼ
	}
}

int Direction(int savec)//����
{
	p=head->next;                                              //pָ����ͷ                                                   
	if(p->dire!=3&&GetAsyncKeyState(VK_LEFT)&0x8000)           //���ԭ���������Ҳ��Ұ������
		p->dire=1;
	else if(p->dire!=4&&GetAsyncKeyState(VK_UP)&0x8000)        //���ԭ���������²��Ұ����ϼ�
		p->dire=2;
	else if(p->dire!=1&&GetAsyncKeyState(VK_RIGHT)&0x8000)     //���ԭ�����������Ұ����Ҽ�
		p->dire=3;
	else if(p->dire!=2&&GetAsyncKeyState(VK_DOWN)&0x8000)      //���ԭ���������ϲ��Ұ����¼�
		p->dire=4;
	else if(GetAsyncKeyState(VK_SHIFT)&0x8000)                 //��shift��
		p->dire=5;
	else if(GetAsyncKeyState(VK_SPACE)&0x8000)                 //���ո��
	{
		loadimage(&stop,"image/stop.jpg");
		putimage(495,290,&stop);                               //������Ϸ��ͣͼƬ
		FlushBatchDraw();                                      //������
		mciSendString("stop bk_audio",NULL,0,NULL);            //��ͣ������ֹͣ
		system("pause");                                       //��ͣ�������������
		loadimage(&play,"image/play.jpg");
		putimage(495,290,&play);                               //����������ϷͼƬ
		FlushBatchDraw();                                      //������
		mciSendString("play bk_audio",NULL,0,NULL);            //�������´���һ�ν����ĵط�����
		p->dire=savec;                   //��ͣ����������ͬһ��������
	}		
	else
		p->dire=savec;                   // ����û��ѡ����Ȼ��ԭ�ȵķ���
	return p->dire;
}

void over()//����
{
	loadimage(&fail,"image/fail.jpg");
	putimage(495,290,&fail);                              //������Ϸʧ��ͼƬ
	FlushBatchDraw();                                     //������
	mciSendString("stop bk_audio",NULL,0,NULL);	          //����������ֹͣ
	system("pause");
	exit(0);                                              //�˳�������̨
}

void eat()//��ʳ��
{
	p=head;
	while(p->next!=NULL)                                  //��p����β�ڵ㣬���������ѭ������
		p=p->next;
	struct snake *a=(snake *)malloc(sizeof(snake));       //��������һ���ڵ㣬�����������
	a->x=saveLast.x;                                      //����󱣴�Ľڵ���Ϣ�����½ڵ�
	a->y=saveLast.y;
	a->dire=saveLast.dire;
	a->next=NULL;
	p->next=a;                                            //���ӵ�������
	p=p->next;
	NUM+=1;                                               //�ڵ������1
}