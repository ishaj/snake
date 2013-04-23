#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define delay(x) usleep(x*1000)
float x0new,y0new,x1new,y1new,x2new,y2new;
float xnew,ynew;
int sx=2,sy=2;
void init()
{
 glClearColor(0.0,0.0,0.0,0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-1000,1000,-1000,1000);
}
void setPixel(float x,float y)
{
 glColor3f(1,1,1);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
void line(float x0,float y0,float x1,float y1)
{
 int dx,dy,steps,k;
 float xinc,yinc,x,y;
 dx=x1-x0;
 dy=y1-y0;
 x=x0,y=y0;
 if(abs(dx)>abs(dy))
  steps=abs(dx);
 else
  steps=abs(dy);
 xinc=(float)dx/(float)steps;
 yinc=(float)dy/(float)steps;
 for(k=0;k<steps;k++)
 {
  x+=xinc;
  y+=yinc;
  setPixel(round(x),round(y));
 }
 //glutSwapBuffers();
}
void scale(float x,float y)
{
 float a[3][3],b[3][1],ans[3][1];
 int i,j,k,theta=-30;
float thi,s;
thi=(3.14*theta/180);
 for(i=0;i<3;i++)
 {
  for(j=0;j<3;j++)
  {  
   if(i==j && i==0)
    a[i][j]=cos(thi);
   else
    a[i][j]=0;
   }
 }
 a[1][0]=sin(thi);
 a[0][1]=(-sin(thi));
 a[1][1]=(cos(thi));
 a[2][2]=1;
 b[0][0]=x;
 b[1][0]=y;
 b[2][0]=1;
 for(i=0;i<3;i++)
 {
  for(j=0;j<1;j++)
  { 
   s=0;
   for(k=0;k<3;k++)
    {
	s+=a[i][k]*b[k][j];
    }
  ans[i][j]=s;
  }
 }
 xnew=ans[0][0];
 ynew=ans[1][0];
}
void display()
{
 glClear(GL_COLOR_BUFFER_BIT);
 line(100,100,100,200);
 line(100,100,200,100);
 line(100,200,200,100);
 glutSwapBuffers();
 scale(100,100);
 x0new=xnew;
 y0new=ynew;
 scale(100,200);
 x1new=xnew;
 y1new=ynew;
 scale(200,100);
 x2new=xnew;
 y2new=ynew;
sleep(1);
 glClear(GL_COLOR_BUFFER_BIT);
 line(x0new,y0new,x1new,y1new);
 line(x1new,y1new,x2new,y2new);
 line(x2new,y2new,x0new,y0new);
 glutSwapBuffers();
}
int main(int argc,char **argv)
{ 
 glutInit(&argc,argv);
 glutCreateWindow("Translation");
 init();
 glutDisplayFunc(display);
 glutMainLoop();
}
