#include <graphics.h>
#include <conio.h>
void Putpixel(int x,int y,int color,int wheel){
	if(wheel==0){
		putpixel(x,y,color);
	}
	int i,j; 
	for(i=0 ; i<2*wheel+1 ; i++){
		for(j=int(wheel/2) ; j<2*wheel ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
	for(i=int(wheel/2) ; i<2*wheel ; i++){
		for(j=0 ; j<2*wheel+1 ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
}
void Any_slope_Put_pixel(int x0,int y0,int x1,int y1,int color,int wheel=0){
	int a,b,delta1,delta2,d,x,y;		/*	delta1����d>0	delta2����d<0	*/
	a=y0-y1;
	b=x1-x0;
	
	x=x0;
	y=y0;
	Putpixel(x,y,color,wheel);
	
	if(-a==0){
		while(x<x1){
			x++;
			Putpixel(x,y,color,wheel);
		}
		while(x>x1){
			x--;
			Putpixel(x,y,color,wheel);
		}
	}else if(b==0){
		while(y<y1){
			y++;
			Putpixel(x,y,color,wheel);
		}
		while(y>y1){
			y--;
			Putpixel(x,y,color,wheel);
		}
	}
	
	if(-a>0 && b>0){					/*��һ����*/
		if(-a-b>=0){					/*б�ʴ��ڵ���1*/
			d=a+2*b;
			delta1=2*(a+b);
			delta2=2*b;
			while(y<y1){
				if(d<0){
					y++;
					d+=delta2;
				}else{
					x++;
					y++;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}else{							/*б��С��1����0*/ 
			d=2*a+b;
			delta1=2*a;
			delta2=2*(a+b);
			while(x<x1){
				if(d<0){
					x++;
					y++;
					d+=delta2;
				}else{
					x++;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}
	}else if(-a<0 && b>0){				/*��������*/
		if(-a+b<=0){					/*б��С�ڵ���-1*/
			d=a-2*b;
			delta1=-2*b;
			delta2=2*a-2*b;
			while(y>y1){
				if(d<0){
					x++;
					y--;
					d+=delta2;
				}else{
					y--;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}else{							/*б�ʴ���-1С��0*/ 
			d=2*a-b;
			delta1=2*a-2*b;
			delta2=2*a;
			while(x<x1){
				if(d<0){
					x++;
					d+=delta2;
				}else{
					x++;
					y--;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}
	}
	
}
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
int XL,XR,YB,YT;
int encode(int x, int y, int *code){
	int c; 
	c=0;
	if(x<XL){
		c=c|LEFT;
	}else if(x>XR){
		c=c|RIGHT;
	}
	if(y<YB){
		c=c|BOTTOM;
	}else if(y>YT){
		c=c|TOP;
	}
	
	*code=c;
	return 0;
}
int Cohen_Sutherla(int x1,int y1,int x2,int y2){
	int code1,code2,code;
	int x,y;
	encode(x1,y1,&code1);
	encode(x2,y2,&code2);
	while(code1!=0 || code2!=0){
		if( (code1 & code2)!=0 ){
			return 0;
		}
		code=code1;
		if(code1==0){
			code=code2;
		}
		if( (LEFT & code)!=0 ){
			x=XL;
 			y=y1+(y2-y1)*(XL-x1)/(x2-x1);
		}else if( (RIGHT & code)!=0 ){
			x=XR;
			y=y1+(y2 -y1)*(XR-x1)/(x2-x1);
		}else if ((BOTTOM & code) != 0){
			y=YB;
			x=x1+(x2-x1)*(YB-y1)/(y2-y1);
		}else if ((TOP & code) != 0){
			y=YT;
			x=x1+(x2-x1)*(YT-y1)/(y2-y1);
		}
		if (code==code1){
			x1=x; y1=y; encode(x1,y1, &code1);
		}else{
			x2=x; y2=y; encode(x2,y2, &code2);
		}
	}
	Any_slope_Put_pixel(x1,y1,x2,y2,RED);
	return 0; 
}
void Repaint(int LINE[50][4],int LINE_NUM){
	setcolor(BLACK);
	rectangle(LINE[0][0],LINE[0][1],LINE[0][2],LINE[0][3]);
	setcolor(RED);

	for(int i=1 ; i<LINE_NUM ; i++){
		Cohen_Sutherla(LINE[i][0],LINE[i][1],LINE[i][2],LINE[i][3]);
	}
}
int main()
{
	// ��ʼ��ͼ�δ���
	initgraph(800, 640);
	setbkcolor(WHITE);
	setcolor(WHITE);
	fillrectangle(0,0,800,640);
	setcolor(BLACK);
	rectangle(0,0,799,639);
	setcolor(BLACK);
	line(0,80,800,80);

	RECT r = {0, 0, 800, 80};
	drawtext(_T("\n��ΪCohen_Sutherla�ü��㷨\n�����Ҽ����������ػ��ü���\n˫���Ҽ��˳�����"), &r, DT_CENTER | DT_VCENTER);

	HRGN rgn = CreateRectRgn(1, 81, 799, 639);
	// ���þ�����������Ϊ�ü���
	setcliprgn(rgn);

	MOUSEMSG m;		// ���������Ϣ
	int wheel=0;
	int mount=0;	//��һ�λ�һ�����飬��Ϊ�ü��߽� 
	int LINE[300][4]; 
	int LINE_NUM=0;
	bool LBUTTONDOWN=false;
	while(true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		int x1,y1;
		
		switch(m.uMsg)
		{
			/*case WM_MOUSEMOVE:
				// ����ƶ���ʱ�򻭺�ɫ��С��
				putpixel(m.x, m.y, RED);
				break;
			*/
				
			case WM_LBUTTONDOWN:
				// ����������ͬʱ������ Ctrl ��
				LBUTTONDOWN=true;
				if (m.mkCtrl)
					// ���
					wheel++;
				else
					// ��ס���
					x1=m.x;
					y1=m.y;
					circle(x1,y1,5);
				break;

			case WM_LBUTTONUP:
				LBUTTONDOWN=false;
				if(mount==0){
					if(x1<m.x){
						XL=x1;
						XR=m.x;
					}else{
						XL=m.x;
						XR=x1;
					}
					if(y1<m.y){
						YT=m.y;
						YB=y1;
					}else{
						YT=y1;
						YB=m.y;
					}
					
					setcolor(BLACK);
					if(YT<=81){
						YT=81;
					}
					if(YB<=81){
						YB=81;
					}
					
					rectangle(XL,YT,XR,YB);
					setcolor(RED);
					LINE[0][0]=XL;
					LINE[0][1]=YT;
					LINE[0][2]=XR;
					LINE[0][3]=YB;
					LINE_NUM++;
					mount++;
				}else{
					if(x1>m.x){
						LINE[LINE_NUM][0]=m.x;
						LINE[LINE_NUM][1]=m.y;
						LINE[LINE_NUM][2]=x1;
						LINE[LINE_NUM][3]=y1;
					/*	Cohen_Sutherla(m.x,m.y,x1,y1);*/
						LINE_NUM++;
					}else{
						LINE[LINE_NUM][0]=x1;
						LINE[LINE_NUM][1]=y1;
						LINE[LINE_NUM][2]=m.x;
						LINE[LINE_NUM][3]=m.y;
					/*	Cohen_Sutherla(x1,y1,m.x,m.y);*/
						LINE_NUM++;
					}
				}
				
				// ����������,��ס�յ㲢����
				break;
			case WM_MOUSEMOVE:
				if(LBUTTONDOWN==true){
					if(LINE_NUM!=0){
						BeginBatchDraw();
						clearcliprgn();
						Repaint(LINE,LINE_NUM);
						if(x1>m.x){
							circle(x1,y1,5);
							Cohen_Sutherla(m.x,m.y,x1,y1);
							circle(m.x,m.y,5);
						}else{
							circle(x1,y1,5);
							Cohen_Sutherla(x1,y1,m.x,m.y);
							circle(m.x,m.y,5);
						}
						FlushBatchDraw();
						EndBatchDraw();
					}else{
						clearcliprgn();
						if(x1<m.x){
							XL=x1;
							XR=m.x;
						}else{
							XL=m.x;
							XR=x1;
						}
						if(y1<m.y){
							YT=m.y;
							YB=y1;
						}else{
							YT=y1;
							YB=m.y;
						}
						setcolor(BLACK);
						if(YT<=81){
							YT=81;
						}
						if(YB<=81){
							YB=81;
						}
						rectangle(XL,YT,XR,YB);
						setcolor(RED);
					}
				}
				break;
			
			case WM_RBUTTONDOWN:
				clearcliprgn();	// ������Ҽ�����
				LINE_NUM=0;
				mount=0; 
				break;
				
				
			case WM_RBUTTONDBLCLK:
				return 0;	// ˫������Ҽ��˳�����
				
		}
	}

	// �ر�ͼ�δ���
	closegraph();
}

