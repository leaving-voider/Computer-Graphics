// ���뻷����Visual C++ 6.0��EasyX 20190219(beta)
// http://www.easyx.cn
//
#include <graphics.h>
#include <conio.h>
void Putpixel(int x,int y,int color,int wheel){
	
	for(int i=0 ; i<2*wheel+1 ; i++){
		for(int j=0 ; j<2*wheel+1 ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
	
}
void Any_slope_Put_pixel(int x0,int y0,int x1,int y1,int color,int wheel){
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
int main()
{
	// ��ʼ��ͼ�δ���
	initgraph(640, 480);

	MOUSEMSG m;		// ���������Ϣ

	while(true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		int x1,y1;
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
					// ��ס���
					x1=m.x;
					y1=m.y;
				break;

			case WM_LBUTTONUP:
				if(x1>m.x){
					Any_slope_Put_pixel(m.x,m.y,x1,y1,RED,m.wheel);
				}else{
					Any_slope_Put_pixel(x1,y1,m.x,m.y,RED,m.wheel);
				}
				// ����������,��ס�յ㲢����
				break;

			case WM_RBUTTONUP:
				cleardevice();	// ������Ҽ�����
				break;
				
			case WM_RBUTTONDBLCLK:
				return 0;	// ˫������Ҽ��˳�����
				
			case WM_MOUSEWHEEL:
				m.wheel++;
		}
	}

	// �ر�ͼ�δ���
	closegraph();
}

