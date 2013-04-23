#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#define delay(x) usleep(x*1000)
int i=40,x2=150,xb=2000,ya=2025,xa=2200,yb=2025,xf,yf,outx=3900,outy=100,inx=3800,iny=200;
void Init()
 {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,4000,0,4000);
 }
void SetPixel(int px,int py)
{
glBegin(GL_POINTS);
glColor3f(1,1,1);
glVertex2f(px,py);
glEnd();
}
void dda(float x0,float y0,float x1,float y1)
{
  float dy,dx,k=0,steps,xinc,yinc,x,y;
  dx=x1-x0;
  dy=y1-y0;
  x=x0;
  y=y0;
 if(abs(dx)>abs(dy))
   steps=abs(dx);
 else
   steps=abs(dy);
  xinc=(dx/steps);
  yinc=(dy/steps);
  SetPixel(round(x),round(y));
 for(k=0;k<steps;k++)
 {
  x+=xinc;
  y+=yinc;
  SetPixel(round(x),round(y));
 }
}
void pointsz(float size)
{
    glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glPointSize(size);
}
void food()
{
  int f=1,g=1;
  pointsz(4.0);
  xf = rand() % 4000;
  yf = rand() % 4000;//random food
 while((f!=0) && (g!=0))
  {
  if(!(xf>iny-50 && xf<3850))
     {
       xf = rand() % 4000;
       f=1;
      }
  else
     f=0;
  if(!(yf>iny && yf<inx))
    {
     yf = rand() % 4000;
     g=1;
     }
   else
     g=0; 
   }
  SetPixel(xf,yf);
  glEnd();
  glFlush();
}

void view()
{
  glClear(GL_COLOR_BUFFER_BIT);
  pointsz(1.0);
  glBegin(GL_POINTS);
  dda(outx,outy,outx,outx);
  dda(outy,outy,outy,outx);
  dda(outy,outy,outx,outy);
  dda(outy,outx,outx,outx);//outer border
  dda(inx+50,inx,inx+50,iny);
  dda(iny-50,inx,inx+50,inx);
  dda(iny-50,iny,iny-50,inx);
  dda(iny-50,iny,inx+50,iny);//inner border
  glEnd();
}

void specialKeys( int key, int x, int y) {
  int w,p,r,t;
  //  Right arrow 
  if (key == GLUT_KEY_RIGHT){
   w=xa;
   p=ya;
  if(p>yb)
 { t=p;
   r=yb;
 }
  else
  {
  t=yb;
  r=p;
  }
   while(t>r)
{
  sleep(1);
  pointsz(1.0);
  view();
  pointsz(4.0);
  glBegin(GL_POINTS);
  SetPixel(xf,yf);
  glFlush();
pointsz(4.0);
glBegin(GL_POINTS);
xa=xa+i;
dda(xa,ya,w,p);
if(p>yb)
{yb=yb+i;
r=yb;}
else
{yb=yb-i;
t=yb;}
dda(w,p,xb,yb);
glEnd();
 glFlush();
}
}
  //  Left arrow 
  else if (key == GLUT_KEY_LEFT){
   w=xa;
   p=ya;
 if(p>yb)
 { t=p;
   r=yb;
 }
  else
  {
  t=yb;
  r=p;
  }
   while(t>r)
{
sleep(1);
pointsz(1.0);
view();
pointsz(4.0);
  glBegin(GL_POINTS);
  SetPixel(xf,yf);
  glFlush();
pointsz(4.0);
glBegin(GL_POINTS);
xa=xa-i;
dda(xa,ya,w,p);
if(p>yb)
{yb=yb+i;
r=yb;}
else
{yb=yb-i;
t=yb;
}
dda(w,p,xb,yb);
glEnd();
 glFlush();
}
}
  //up arrow
  else if (key == GLUT_KEY_UP)
 {
   w=xa;
   p=ya;
    if(w>xb)
 { t=w;
   r=xb;
 }
  else
  {
  t=xb;
  r=w;
  }
   while(t>r)
{
sleep(1);
pointsz(1.0);
view();
  pointsz(4.0);
  glBegin(GL_POINTS);
  SetPixel(xf,yf);
  glFlush();
pointsz(4.0);
glBegin(GL_POINTS);
ya=ya+i;
dda(xa,ya,w,p);
if(w>xb)
{xb=xb+i;
r=xb;}
else
{
xb=xb-i;
t=xb;
}
dda(w,p,xb,yb);
glEnd();
 glFlush();
}
}
  //down arrow
  else if (key == GLUT_KEY_DOWN){
   w=xa;
   p=ya;
    if(w>xb)
 { t=w;
   r=xb;
 }
  else
  {
  t=xb;
  r=w;
  }
   while(t>r)
{
sleep(1);
pointsz(1.0);
view();
pointsz(4.0);
  glBegin(GL_POINTS);
  SetPixel(xf,yf);
  glFlush();
pointsz(4.0);
glBegin(GL_POINTS);
ya=ya-i;
dda(xa,ya,w,p);
if(w>xb)
{xb=xb+i;
r=xb;}
else
{xb=xb-i;
t=xb;}
dda(w,p,xb,yb);
glEnd();
glFlush();
}
}
}
void display()
{
  int static start=0;
  pointsz(1.0);
  view();
  pointsz(4.0);
  glBegin(GL_POINTS);
  dda(xa,ya,xb,yb);//snake
  pointsz(4.0);
  glBegin(GL_POINTS);
  if(start == 0) 
  {
   food();
   start++;
   }
glutSpecialFunc(specialKeys);
sleep(1);
if(xa==xb)
{
if(ya>yb)
{
ya=ya+i;
yb=yb+i;
}
else
{
ya=ya-i;
yb=yb-i;
}
}
else if(ya==yb)
{
if(xa>xb)
{
xa=xa+i;
xb=xb+i;
}
else
{
xa=xa-i;
xb=xb-i;
}
}
if((xa>=inx+50) ||(xa<=iny-50)||(ya>=inx) ||( ya<=iny))
exit(0);
pointsz(4.0);
glBegin(GL_POINTS);
dda(xa,ya,xb,yb);
glEnd();
glFlush();
glutPostRedisplay();


//view();
//sleep(1);
/*xa=xa+i;
if(xb>=3800 && xa<=3800)
{
 x2=x2+i;
 pointsz(4.0);
 dda(xa,ya,3800,yb);
 dda(x2,ya,150,yb);
 glEnd();
 glFlush();
if(xa==3800)
{
 xa=100;
 xb=x2;
 x2=100;
}
}
if(xa>=3800 && xb<=3800)
{
 x2=x2+i;
 pointsz(4.0);
 dda(xa,ya,3800,yb);
 dda(x2,ya,150,yb);
 glEnd();
 glFlush();
if(xa==3800)
{
 xa=100;
 xb=x2;
 x2=100;
}
}
else{
 xb=xb+i;
 view();
 pointsz(4.0);
 dda(xa,ya,xb,yb);//snake
 glEnd();
 glFlush();
}*/
  pointsz(4.0);
  glBegin(GL_POINTS);
  SetPixel(xf,yf);
  glFlush();
//}
}
/*int main(int argc,char **argv)
{
 glutInit(&argc,argv);
 glutInitWindowSize(750,750);
 glutInitWindowPosition(0,750);
 glutCreateWindow("line");
 Init();
 glutDisplayFunc(display);
 glutMainLoop();
}*/
