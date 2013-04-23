#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define delay(x) usleep(x*1000)
int a=1000,b=1500,c=3000,d=1500,e=2000,f=3000;
int xnew,ynew,x0new,y0new,x1new,y1new,x2new,y2new;
int diffx=1000,diffy=1000;
void init()
{
 glClearColor(0.0,0.0,0.0,0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0,4000,0,4000);
}
void setPixel(int x,int y)
{
 glColor3f(1,1,1);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
void line(int x0,int y0,int x1,int y1)
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
 glutSwapBuffers();
}
void trans(int x,int y)
{
 int a[3][3],b[3][1],ans[3][1];
 int i,j,k;
 for(i=0;i<3;i++)
 {
  for(j=0;j<3;j++)
  {  
   if(i==j)
    a[i][j]=1;
   else
    a[i][j]=0;
  }
 }
 a[0][2]=diffx;
 a[1][2]=diffy;
 b[0][0]=x;
 b[1][0]=y;
 b[2][0]=1;
 for(i=0;i<3;i++)
 {
  for(j=0;j<1;j++)
  { 
   ans[i][j]=0;
   for(k=0;k<3;k++)
    ans[i][j]+=a[i][k]*b[k][j];
  }
 }
 xnew=ans[0][0];
 ynew=ans[1][0];
}
void display()
{
 glClear(GL_COLOR_BUFFER_BIT);
 line(a,b,c,d);
 line(c,d,e,f);
 line(a,b,e,f);
 glutSwapBuffers();
 delay(1000);
 trans(a,b);
 x0new=xnew;
 y0new=ynew;
 trans(c,d);
 x1new=xnew;
 y1new=ynew;
 trans(e,f);
 x2new=xnew;
 y2new=ynew;
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
