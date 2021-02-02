// ���뻷����Visual C++ 6.0��EasyX 20190219(beta)
// http://www.easyx.cn
//
#include <graphics.h>
#include <conio.h>
#include <math.h>
void graph_4(int a,int b,int color,int yuan_x,int yuan_y){				//ʵ��1-4
	int xp,yp,d,x,y;
	xp=int(a*a/sqrt(a*a+b*b));
	yp=int(b*b/sqrt(a*a+b*b));
	x=0;
	y=b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x<xp){
		if(d<=0){
			d+=(2*x+3)*b*b;
			x++;
		}else{
			d+=(2*x+3)*b*b+(-2*y+2)*a*a;
			x++;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	d=int(b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b);
	while(y>0){
		if(d<=0){
			d+=(-2*y+3)*a*a+(2*x+2)*b*b;
			x++;
			y--;
		}else{
			d+=(-2*y+3)*a*a;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	/**/
	xp=int(-a*a/sqrt(a*a+b*b));
	yp=int(b*b/sqrt(a*a+b*b));
	x=0;
	y=b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x>xp){
		if(d<=0){
			d+=(-2*x+3)*b*b;
			x--;
		}else{
			d+=(-2*x+3)*b*b+(-2*y+2)*a*a;
			x--;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	} 
	d=int(b*b*(x-0.5)*(x-0.5)+a*a*(y-1)*(y-1)-a*a*b*b);
	while(y>0){
		if(d<=0){
			d+=(-2*y+3)*a*a+(-2*x+2)*b*b;
			x--;
			y--;
		}else{
			d+=(-2*y+3)*a*a;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	/*�����ǵ�������*/
	xp=int(a*a/sqrt(a*a+b*b));
	yp=int(-b*b/sqrt(a*a+b*b));
	x=0;
	y=-b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x<xp){
		if(d<=0){
			d+=(2*x+3)*b*b;
			x++;
		}else{
			d+=(2*x+3)*b*b+(2*y+2)*a*a;
			x++;
			y++;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	} 
	d=int(b*b*(x+0.5)*(x+0.5)+a*a*(y+1)*(y+1)-a*a*b*b);
	while(y<0){
		if(d<=0){
			d+=(2*y+3)*a*a+(2*x+2)*b*b;
			x++;
			y++;
		}else{
			d+=(2*y+3)*a*a;
			y++;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	/*�����ǵ�������*/
	xp=int(-a*a/sqrt(a*a+b*b));
	yp=int(-b*b/sqrt(a*a+b*b));
	x=0;
	y=-b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x>xp){
		if(d<=0){
			d+=(-2*x+3)*b*b;
			x--;
		}else{
			d+=(-2*x+3)*b*b+(2*y+2)*a*a;
			x--;
			y++;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	} 
	d=int(b*b*(x-0.5)*(x-0.5)+a*a*(y+1)*(y+1)-a*a*b*b);
	while(y<0){
		if(d<=0){
			d+=(2*y+3)*a*a+(-2*x+2)*b*b;
			x--;
			y++;
		}else{
			d+=(2*y+3)*a*a;
			y++;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
	}
}
int main()
{
	// ��ʼ��ͼ�δ���
	initgraph(640, 480);

	MOUSEMSG m;		// ���������Ϣ

	while(true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		int x1,y1,r;
		switch(m.uMsg)
		{
			/*case WM_MOUSEMOVE:
				// ����ƶ���ʱ�򻭺�ɫ��С��
				putpixel(m.x, m.y, RED);
				break;
			*/
			case WM_LBUTTONDOWN:
					// ��ס���
					x1=m.x;
					y1=m.y;
				break;

			case WM_LBUTTONUP:
				r=int(sqrt( (m.x-x1)*(m.x-x1) + (m.y-y1)*(m.y-y1) ));
				graph_4(r,int(r*2/3),YELLOW,x1,y1);

				// ����������,��ס�յ㲢��ԲȦ
				break;

			case WM_RBUTTONUP:
				cleardevice();	// ������Ҽ�����
				break;
				
				
			case WM_RBUTTONDBLCLK:
				return 0;	// ˫������Ҽ��˳�����
		}
	}

	// �ر�ͼ�δ���
	closegraph();
}

