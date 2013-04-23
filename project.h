int i=40,x2=150,xb=2000,ya=2025,xa=2200,yb=2025,xf,yf,outx=3900,outy=100,inx=3800,iny=200;

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
void setup()
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
}



void specialKeys( int key, int x, int y) {
   int w,p,r,t;
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
	glEnd();
        glFlush();
  }
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
   { 
	t=w;
	r=xb;
   }
   else
  {
	t=xb;
	r=w;
  }
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
	glEnd();
	 glFlush();
   }
}
  //down arrow
  else if (key == GLUT_KEY_DOWN){
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
	glEnd();
	glFlush();
   }
}
}
void display2()
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
  {
	glClear(GL_COLOR_BUFFER_BIT);
	call3();	   	
  }
  pointsz(4.0);
  glBegin(GL_POINTS);
  dda(xa,ya,xb,yb);
  glEnd();
  glFlush();
  glutPostRedisplay();
  pointsz(4.0);
  glBegin(GL_POINTS);
  SetPixel(xf,yf);
  glFlush();
}
