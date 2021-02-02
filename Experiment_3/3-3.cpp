#include <iostream> 
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <windows.h>
using namespace std; 

int Mouse_event();										//����¼� 
void initializer();										//��ʼ��ͼ�δ��� 
void Matrix_mutiply(double a[5][5],int ar,int ac, double b[5][5],int br,int bc);		//����˷�������c 
void translation(double tx,double ty);					//ƽ��x+=tx,	y+=ty 
void rotate(double degree);								//��ԭ��תdegree��,��˳���� 
void paint_now();										//����points�����������ͼ�� 
void symmetry(int flag);								//0�������x�Գƣ�1�������y�Գ�
void any_symmetry(int x1,int y1,int x2,int y2);			//����ȷ��һ�ߣ���������ֱ�߶Գ� 

#define PI 3.1415927
int Dimension=3;				//ƽ��Ϊ3����άΪ4 
double points[4][2]={{150,150},{150,300},{300,300},{300,150}};
double points_backup[4][2]={{150,150},{150,300},{300,300},{300,150}};
int num=4;
int main()
{
	// ��ʼ��ͼ�δ���
	initializer();
	
	//��ͣ 
	Mouse_event();
	
	// �ر�ͼ�δ���
	closegraph();
	return 0;
}
void initializer(){
	initgraph(800, 640);
	
	setbkcolor(WHITE);
	setcolor(WHITE);
	fillrectangle(0,0,800,640);
	setcolor(BLACK);
	rectangle(0,0,799,639);
	setcolor(BLACK);
	line(0,80,800,80);

	RECT r = {0, 0, 800, 80};
	drawtext(_T("\n�ı��β��䣬��һ��ֱ���������ڸ�ֱ�ߵĶԳ�\n˫���Ҽ����˳�����"), &r, DT_CENTER | DT_VCENTER );

	HRGN rgn = CreateRectRgn(1, 81, 799, 639);
	// ���þ�����������Ϊ�ü���
	setcliprgn(rgn);

	rectangle(points[0][0],points[0][1],points[2][0],points[2][1]);
	setcolor(RED);
}
void any_symmetry(int x1,int y1,int x2,int y2){
	double k_tan_afa=0,b=0;
	if(x1==x2){
		translation(-x1,0);
		symmetry(1);
		translation(x1,0);
	}else if(y1==y2){
		translation(0,-y1);
		symmetry(0);
		translation(0,y1);
	}else{
		k_tan_afa=1.0*(y1-y2)/(x1-x2);
		b=y1-k_tan_afa*x1;
		
		translation(0,-b);
		rotate(-atan(k_tan_afa)*180*1.0/PI);
		symmetry(0);
		rotate(atan(k_tan_afa)*180*1.0/PI);
		translation(0,b);
	}
}
void symmetry(int flag){
	int i;
	if(flag==0){
		for(i=0 ; i<num ; i++){
			points[i][1]=-points[i][1];
		}
	}else if(flag==1){
		for(i=0 ; i<num ; i++){
			points[i][0]=-points[i][0];
		}
	}else{
		return;
	}
}
void paint_now(){
	for(int i=0 ; i<num ; i++){
		if(i==num-1){
			line(int(points[i][0]),int(points[i][1]),int(points[0][0]),int(points[0][1]));
			break;
		}
		line(int(points[i][0]),int(points[i][1]),int(points[i+1][0]),int(points[i+1][1]));
	}
}
void rotate(double degree){
	double sita=1.0*degree/180*PI;
	double R[5][5]={{cos(sita),-sin(sita),0},{sin(sita),cos(sita),0},{0,0,1.0}};
	double point[5][5];
	int i;
	for(i=0 ; i<num ; i++){
		point[0][0]=1.0*points[i][0];
		point[1][0]=1.0*points[i][1];
		point[2][0]=1;
		Matrix_mutiply(R, Dimension, Dimension, point, Dimension, 1);
		points[i][0]=point[0][0];
		points[i][1]=point[1][0];
	}
}
void translation(double tx,double ty){
	double T[5][5]={{1,0,tx},{0,1,ty},{0,0,1}};
	double point[5][5];
	int i;
	for(i=0 ; i<num ; i++){
		point[0][0]=1.0*points[i][0];
		point[1][0]=1.0*points[i][1];
		point[2][0]=1;
		Matrix_mutiply(T, Dimension, Dimension, point, Dimension, 1);
		points[i][0]=point[0][0];
		points[i][1]=point[1][0];
	}
}
void Matrix_mutiply(double a[5][5],int ar,int ac, double b[5][5],int br,int bc){
	if(ac!=br){
		cout<<"your matrix is invalid��";
		return;
	}
	int i,j,k;
	double c[5][5];
	for(i=0 ; i<ar ; i++)
		for(j=0 ; j<bc ; j++)
			c[i][j]=0;
			
	for(i=0 ; i<ar ; i++)
		for(j=0 ; j<bc ; j++)
			for(k=0 ; k<ac ; k++)
				c[i][j]+=1.0*a[i][k]*b[k][j];
	
	for(i=0 ; i<ar ; i++)
		for(j=0 ; j<bc ; j++)
			b[i][j]=c[i][j];
}
int Mouse_event(){
	MOUSEMSG m;		// ���������Ϣ
	bool LBUTTONDOWN=false;
	while(true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		int x1,y1;
		int i;
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				LBUTTONDOWN=true;
				x1=m.x;
				y1=m.y;
				circle(x1,y1,5);
				break;

			case WM_LBUTTONUP:
				LBUTTONDOWN=false;
				line(m.x,m.y,x1,y1);
				any_symmetry(m.x,m.y,x1,y1);
				paint_now();
				for(i=0 ; i<4 ; i++){
					points[0][0]=points_backup[0][0];points[0][1]=points_backup[0][1];
					points[1][0]=points_backup[1][0];points[1][1]=points_backup[1][1];
					points[2][0]=points_backup[2][0];points[2][1]=points_backup[2][1];
					points[3][0]=points_backup[3][0];points[3][1]=points_backup[3][1];
				}
				break;

			case WM_MOUSEMOVE:
				if(LBUTTONDOWN==true){
					BeginBatchDraw();
					clearcliprgn();
						setcolor(BLACK);
						rectangle(points_backup[0][0],points_backup[0][1],points_backup[2][0],points_backup[2][1]);
						setcolor(RED);
						circle(x1,y1,5);
						line(m.x,m.y,x1,y1);
						circle(m.x,m.y,5);
					FlushBatchDraw();
					EndBatchDraw();
				}
				break;
			
			case WM_RBUTTONDOWN:
				
				break;

			case WM_RBUTTONDBLCLK:
				return 0;	// ˫������Ҽ��˳�����
				
		}
	}
}
