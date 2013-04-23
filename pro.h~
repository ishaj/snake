int x1,y,x2,y2;
static int winheight,winwidth,edgelength=100;

void reshape(int newwidth,int newheight)
{
glViewport(0,0,newwidth,newheight);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,newwidth,0.0,newheight);
winwidth=newwidth;
winheight=newheight;
}

void fillsquare(int button,int action,int xmouse,int ymouse)
{
if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN)
{
	glClear (GL_COLOR_BUFFER_BIT);
	x1=xmouse;
	y=winheight-ymouse;
	x2=x1+edgelength;
	y2=y+edgelength;
	glColor3f(0.0,1.0,1.0);
	glRecti(x1,y,x2,y2);
}
else
	if(button==GLUT_RIGHT_BUTTON)
	exit(0);
glFlush();
}

void enlargesquare(unsigned char sizefactor,int xmouse,int ymouse)
{
switch(sizefactor)
{
case 'a':
     	edgelength *= 2;
	x2=x1+edgelength;
	y2=y+edgelength;
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1,y);
	glVertex2f(x2,y);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
	glFlush();
     break;
case 'b':
	edgelength *= 3;
	x2=x1+edgelength;
	y2=y+edgelength;
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1,y);
	glVertex2f(x2,y);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
	glFlush();
     break;
case 'c':
	edgelength *= 2;
	x2=x1+edgelength;
	y2=y+edgelength;
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1,y);
	glVertex2f(x2,y);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
	glFlush();
     break;
default:
     break;
}
}

void reducesquare(int reductionkey,int xmouse,int ymouse)
{
switch(reductionkey)
{
case GLUT_KEY_F2:
	glClear (GL_COLOR_BUFFER_BIT);
	edgelength /= 2;
	x2=x1+edgelength;
	y2=y+edgelength;
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1,y);
	glVertex2f(x2,y);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
	glFlush();
	
     break;
case GLUT_KEY_F3:
	glClear (GL_COLOR_BUFFER_BIT);
	edgelength /= 4;
	x2=x1+edgelength;
	y2=y+edgelength;
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1,y);
	glVertex2f(x2,y);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
	glFlush();
     break;
default:
     break;
}
}

