static int i=50,xb=2000,ya=2025,xa=2200,yb=2025,xf,yf,outx=3900,outy=100,inx=3800,iny=200,w,p,r,t,key1=1000;
int static start=0;
int score=0,score1;
void * font1 = GLUT_BITMAP_HELVETICA_18;
void specialKeys( int key, int x, int y); 
void show();
char ar1[10],*array;
void rt(int score);

void SetPixel(int px,int py)
{

	glBegin(GL_POINTS);
	glVertex2f(px,py);
	glEnd();
}


void dda(float x0,float y0,float x1,float y1)
{
  int steps,k=0;
  float xinc,dx,dy,yinc,x,y;
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
char* int_char()
{
	int c=0,j=0,ai;
	char ar[10];
	score1=score;
	if(score==0)
	ar1[j++]=48;
	else
	{
	while(score1!=0)
	{
		ar[c++]=((score1%10)+48);
		score1=score1/10;
	}
	}
	for(ai=c-1;ai>=0;ai--)
	ar1[j++]=ar[ai];
	ar1[j]='\0';
	return ar1;
}

void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void call3()
{
	renderBitmapString(1600,3500,(void *)font1,"YOUR TOTAL SCORE IS : ");
	array=int_char();
	renderBitmapString(2400,3500,(void *)font1,array);
	renderBitmapString(1600,3000,(void *)font1,"THANK YOU :)");
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
  pointsz(6.0);
  xf = rand() % 3500;
  yf = rand() % 3500;//random food
 while((f!=0) && (g!=0))
  {
  if(!(xf>iny-50 && xf<3800))
     {
       xf = rand() % 3500;
       f=1;
      }
  else
     f=0;
  if(!(yf>iny && yf<inx))
    {
     yf = rand() % 3500;
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
void tailgrow(int foodx, int foody, int headx, int heady, int tailx, int taily)
{ 
	if(headx == tailx)
	{
		if(heady > taily)
		{ 
			yb = yb -i;
		}
		else
		{
			yb = yb + i;
		}
	}

	else if(heady == taily)
	{
		if( headx > tailx)
		{
			xb = xb-i;
		}
		else
		{
			xb = xb + i;
		}
	}
	else 
	{
		if(heady >= taily)
			yb=yb-i;
		else if(heady < taily)
			yb=yb+i;
		else if(headx > tailx)
			xb = xb - i;
		else if(headx < tailx)
			xb = xb + i;
	}
		start=0;
	
}

void setup()
{
	//sleep(1);
	glColor3f(0.0,0.0,1.0);
        pointsz(1.0);
	view();
  	pointsz(6.0);
	glColor3f(1.0,1.0,1.0);
  	glBegin(GL_POINTS);
  	SetPixel(xf,yf);
  	glFlush();
	pointsz(4.0);
	glBegin(GL_POINTS);
}

void motion()
{
if(key1==0)
{
   while(t>r)
   {
	 setup();
	xa=xa+i;
	dda(xa,ya,w,p);
	if(p>yb)
	{
		yb=yb+i;
		r=yb;
	}
	else
	{
		yb=yb-i;
		t=yb;
	}
	dda(w,p,xb,yb);
	if((((xf-20) <= xa) && ((xf +20) >= xa) && ((yf-20) <= ya) && ((yf +20) >= ya)))
	{
	score++;
	tailgrow(xf,yf,xa,ya,xb,yb);
	} 
	glEnd();
	glFlush();
   }
	pointsz(1.0);
}
if( key1 == 3)
{
  while(t>r)
  {
	setup();
	ya=ya-i;
	dda(xa,ya,w,p);
	if(w>xb)
	{
		xb=xb+i;
		r=xb;
	}
	else
	{
		xb=xb-i;
		t=xb;
	}
	dda(w,p,xb,yb);
	if((((xf-20) <= xa) && ((xf +20) >= xa) && ((yf-20) <= ya) && ((yf +20) >= ya)))
		{
	score++;
		printf("%d\n",score);
	tailgrow(xf,yf,xa,ya,xb,yb);
	} 
	glEnd();
	glFlush();
  }
	pointsz(1.0);
}
if(key1==1)
{
   while(t>r)
  {
	setup();
	xa=xa-i;
	dda(xa,ya,w,p);
	if(p>yb)
	{
		yb=yb+i;
		r=yb;
	}
	else
	{
		yb=yb-i;
		t=yb;
	}
	dda(w,p,xb,yb);
	if((((xf-20) <= xa) && ((xf +20) >= xa) && ((yf-20) <= ya) && ((yf +20) >= ya)))
		{
	score++;
		printf("%d\n",score);
	tailgrow(xf,yf,xa,ya,xb,yb);
	} 
	glEnd();
	glFlush();
  }
	pointsz(1.0);
}
if(key1==2)
{
   while(t>r)
  {
	setup();
	ya=ya+i;
	dda(xa,ya,w,p);
	if(w>xb)
	{
		xb=xb+i;
		r=xb;
	}
	else
	{
		xb=xb-i;
		t=xb;
	}
	dda(w,p,xb,yb);
	if((((xf-20) <= xa) && ((xf +20) >= xa) && ((yf-20) <= ya) && ((yf +20) >= ya)))
		{
	score++;
		printf("%d\n",score);
	tailgrow(xf,yf,xa,ya,xb,yb);
	} 
	glEnd();
	glFlush();
  }
	pointsz(1.0);
}
}
void specialKeys( int key, int x, int y) {
  //  Right arrow 
  if (key == GLUT_KEY_RIGHT){
   w=xa;
   p=ya;
  if(p>yb)
  {
	 t=p;
	 r=yb;
  }
  else
  {
  	t=yb;
  	r=p;
  }
  key1=0;
  motion();
}
  //  Left arrow 
  else if (key == GLUT_KEY_LEFT){
   w=xa;
   p=ya;
 if(p>yb)
 {
	 t=p;
	 r=yb;
 }
  else
  {
	  t=yb;
	  r=p;
  }
 key1=1;
 motion();
}
  //up arrow
  else if (key == GLUT_KEY_UP)
 {
   w=xa;
   p=ya;
    if(w>xb)
 {
	 t=w;
	 r=xb;
 }
  else
  {
  t=xb;
  r=w;
  }
  key1=2;
  motion();
}
  //down arrow
  else if (key == GLUT_KEY_DOWN){
   w=xa;
   p=ya;
  key1 =3;
    if(w>xb)
 { 
	t=w;
	r=xb;
 }
  else
  {
  	t=xb;
  	r=w;
  }
 motion();
}
}


void display2()
{/*
  if((xa>=inx+50) ||(xa<=iny-50)||(ya>=inx) ||(ya<=iny))
  	{	
		glClear(GL_COLOR_BUFFER_BIT);
		pointsz(1.0);
		glBegin(GL_POINTS);
		//show();
		glColor3f(0.0,0.0,0.0);
		view();
		//call3();
		glutSwapBuffers();
		glEnd();
       	        glFlush();	
	}
  else
 {*/
  glColor3f(0.0,0.0,1.0);
  pointsz(1.0);
  view();
  pointsz(4.0);
  glBegin(GL_POINTS);
  dda(xa,ya,xb,yb);//snake
	  if(start == 0) 
	  {
		   glColor3f(1.0,1.0,1.0);
		   food();
		   start++;
	  }
	if((((xf-20) <= xa) && ((xf +20) >= xa) && ((yf-20) <= ya) && ((yf +20) >= ya)))
		 {
	score++;
		printf("%d\n",score);
	tailgrow(xf,yf,xa,ya,xb,yb);
	} 
  glutSpecialFunc(specialKeys);
  //sleep(1);
  pointsz(4.0);
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
  	glBegin(GL_POINTS);
  	dda(xa,ya,xb,yb);
  	glEnd();
  	glFlush();
  	glutPostRedisplay();
  	pointsz(6.0);
	glColor3f(1.0,1.0,1.0);
  	glBegin(GL_POINTS);
  	SetPixel(xf,yf);
	pointsz(1.0);
  	glFlush();
	//}
}

