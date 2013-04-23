#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include </home/isha/Documents/CG/project/q.h>
#include </home/isha/Documents/CG/project/pro.h>

#define round(a) ((int)(a+0.5))
#define left 0
#define right 1
#define bottom 2
#define top 3
#define delay(x) usleep((x)*1000)

FILE *fp,*fp1;
int numseg=0;
void * font = GLUT_BITMAP_9_BY_15;
static int addingmenu;
static int menuid,score_total;
static int animationmenu;
static int xmin=600,xmax=3200;
static int ymin=700,ymax=2500;
static int mouse_val = 0;
static int win=0,win_no=0,zx=0,window_no=0,theta=15;
void createMenu(void);
static float tresx[10],tresy[10],xnew,ynew,sx=1.5,sy=1.5,tx=0,ty=300;
static added=0,u=0;
void Init()
 {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,4000,0,4000);
  
 }

struct segment{
	 int id;
	 int tx;
	 int ty;
	 int sx;
	 int sy;
	 int theta;
	 int start_add;
	 int end_add;
	 int visi;
	struct segment * next;
};

typedef struct segment node;
node *head=NULL;

void create_segment()							//creates the segment for display file 3
{
	int temp,opcode,line,vis;
	node *p;
	float x,y;
	fp = fopen("disp3.txt","r");

	while(!feof(fp))
	{
		if(numseg==0)
		{
			head=(node*)malloc(sizeof(node));
			p=head;
			numseg++;
		}
		fscanf(fp,"%d %d %d %e %e",&line,&opcode,&vis,&x,&y);
		if(opcode==0)
		{
			if(numseg!=1)
			{
				p->end_add=line;
				printf("%d %d\n",p->start_add,p->end_add);
			}
			p->next=(node*)malloc(sizeof(node));
			p=p->next;
			p->id=numseg;
			p->start_add=line;
			p->visi=vis;
			p->tx=0;
			p->ty=0;
			p->sx=0;
			p->sy=0;
			p->theta=0;
			p->next=NULL;
			numseg++;
		}
	}
	p->end_add=line;
	p->next=NULL;
	fclose(fp);
}	

void trans(float x,float y,float tx,float ty)			//code for translation
{
 float a[3][3],b[3][1],ans[3][1];
 int qa,j,k;
 for(qa=0;qa<3;qa++)
 {
  for(j=0;j<3;j++)
  {  
   if(qa==j)
    a[qa][j]=1;
   else
    a[qa][j]=0;
  }
 }
 a[0][2]=tx;
 a[1][2]=ty;
 b[0][0]=x;
 b[1][0]=y;
 b[2][0]=1;
 for(qa=0;qa<3;qa++)
 {
  for(j=0;j<3;j++)
  { 
   ans[qa][j]=0;
   for(k=0;k<3;k++)
    ans[qa][j]+=a[qa][k]*b[k][j];
  }
 }
 xnew=ans[0][0];
 ynew=ans[1][0];
}

void scale(float x,float y,float sx,float sy)
{
 float a[3][3],b[3][1],ans[3][1];
 int wi,j,k;
 for(wi=0;wi<3;wi++)
 {
  for(j=0;j<3;j++)
  {  
   if(wi==j && wi==0)
    a[wi][j]=sx;
   else if(wi==j && wi==1)
    a[wi][j]=sy;
   else
    a[wi][j]=0;
  }
 }
 a[2][2]=1;
 b[0][0]=x;
 b[1][0]=y;
 b[2][0]=1;
 for(wi=0;wi<3;wi++)
 {
  for(j=0;j<3;j++)
  { 
   ans[wi][j]=0;
   for(k=0;k<3;k++)
    ans[wi][j]+=a[wi][k]*b[k][j];
  }
 }
 xnew=ans[0][0];
 ynew=ans[1][0];
}

void rot(float x,float y)				//code for rotation
{
 float a[3][3],b[3][1],ans[3][1];
 int i,j,k;
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




void translate(float transx,float transy){		//move cursor to some point
}

void circle(int r,int ch,int xc,int yc)			//code for drawing circle
{
  int x0,y0,p,x,y,t;
  x0=0;
  y0=r;
  p=1-r;
  x=0;
  y=r;
  t=p;
  while(x<y)
 {
   x0=x;
   y0=y;
   x=(x0+1);
   if(p<0)
    {
     y=y0;
	if(ch == 2 )				//ch==2 implies full circle
     {
	SetPixel(round(x+xc),round(y+yc));
	SetPixel(round(-x+xc),round(y+yc));
     	SetPixel(round(-y+xc),round(x+yc));
      	SetPixel(round(y+xc),round(x+yc));
     }
	if(ch == 2 || ch ==1)			//ch==1 implies half circle in the third fourth quadrant
    {
	 SetPixel(round(x+xc),round(-y+yc));
	 SetPixel(round(-x+xc),round(-y+yc));
	 SetPixel(round(y+xc),round(-x+yc));
	 SetPixel(round(-y+xc),round(-x+yc));
    }
     p=(p+(2*x)+1);
    }
   else
    {
      y=(y0-1);
      if(ch == 2 )
     {
	SetPixel(round(x+xc),round(y+yc));
	SetPixel(round(-x+xc),round(y+yc));
     	SetPixel(round(-y+xc),round(x+yc));
      	SetPixel(round(y+xc),round(x+yc));
     }
	if(ch == 2 || ch ==1)
    {
	 SetPixel(round(x+xc),round(-y+yc));
	 SetPixel(round(-x+xc),round(-y+yc));
	 SetPixel(round(y+xc),round(-x+yc));
	 SetPixel(round(-y+xc),round(-x+yc));
    }
      p=(p+(2*x)+1-(2*y));
    }
 }

}

void show()						//for display file 1
{
	int n1=1,line=1,opcode,last_op,x,y,x1,y1,vis,arrx[100],arry[100],temp;
	float q=1.0,r=0.0,v=0.0;
	fp = fopen("disp1.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d %d",&opcode,&x,&y,&vis);
		if(opcode==0)
		{
			i=0;
			line++;
		}
		if(i<4 && line!=2)
		{	
			arrx[i]=x;
			arry[i]=y;
			i++;
		}
		if(i==4 && line!=2)
		{	
			t=q;
			q=r;
			r=v;
			v=t;
			glBegin(GL_POLYGON);
			glColor3f(q,r,v);
			glVertex2f(arrx[0],arry[0]);
			glVertex2f(arrx[1],arry[1]);
			glVertex2f(arrx[2],arry[2]);
			glVertex2f(arrx[3],arry[3]);
			glEnd();
			glFlush();
		}
	}
	fclose(fp);
}



void show1()						//for display file 3
{
	int n1=1,line,opcode,last_op,vis,i,t,line1;
	float x,y,x1,y1,q=1.0,r=0.0,v=0.0,arry[100],arrx[100];
	fp = fopen("disp3.txt","r");
			
	while(!feof(fp))
		{
		fscanf(fp,"%d %d %d %e %e",&line,&opcode,&vis,&x,&y);
		if(vis ==1)
		{
		if(opcode==0)
		{
			i=0;
			line1++;
		}
		if(i<4 && line1!=2)
		{	
			arrx[i]=x;
			arry[i]=y;
			i++;
		}
		if(i==4 && line1!=2)
		{
			t=q;
			q=r;
			r=v;
			v=t;
			glBegin(GL_POLYGON);
			glColor3f(q,r,v);
			glVertex2f(arrx[0],arry[0]);
			glVertex2f(arrx[1],arry[1]);
			glVertex2f(arrx[2],arry[2]);
			glVertex2f(arrx[3],arry[3]);
			glEnd();
			glFlush();
		}
		}
	}
			fclose(fp);
}

int outcode(int x,int y)				//creates region code for clipping(cohen sutherland's line clipping algo)
{
	int out=0,i,l;
	int code[5];
	for(i=0;i<4;i++)
	code[i]=0;

	if(x < xmin)
	code[left]=1;
	if(x > xmax)
	code[right]=1;
	if(y < ymin)
	code[bottom]=1;
	if(y > ymax)
	code[top]=1;

	l=3;

	for(i=0;i<4;i++)
	{
		if(code[i]==1)
		{
			out=out+pow(2,l-i);
		}	
	}
return out;
}

void cohen(float x1,float y1,float x2,float y2)				//line clipping implemented here
{
	float temp;
	int rc1,rc2,done=0,accept=0; 
	float m;
	m=(y2-y1)/(x2-x1);
	
	while(!done)
	{
		rc1=outcode(x1,y1);
		rc2=outcode(x2,y2);

		if((rc1|rc2)==0)		//trivial accept
		{
			done=1;
			accept=1;
		}
		else if(rc1 & rc2)	//trivial reject
		done=1;
		else
			{
				if(rc1==0)			
				{
					//swap(&x1,&x2);
					temp = x1;
					x1=x2;
					x2=temp;
	
					 //swap(&y1,&y2);
					temp = y1;
					y1=y2;
					y2=temp;
					
					 //swap(&rc1,&rc2);
					temp = rc1;
					rc1=rc2;
					rc2=temp;
				}
				if(((rc1==8)||(rc1==9)||(rc1==10)))		//1xxx
				{
					
					y1 = y1 + m*(xmin-x1);
					x1=xmin;
					
				}
				else if(((rc1==4)||(rc1==5)||(rc1==6)))	//x1xx
					{
						
						y1 = y1 + (y2 - y1) * (xmax - x1)/(x2 - x1);
						x1 = xmax;
						
					}
				else if(((rc1==2)||(rc1==6)||(rc1==10)))		//xx1x
						{
							
							x1 = x1 + (x2 - x1) * (ymin - y1)/(y2 - y1);
							y1 = ymin;
							
						}
				else									//xxx1
						{
							
							x1 = x1 + (x2 - x1) * (ymax - y1)/(y2 - y1); 
							y1 = ymax;							
				}
		}
	}
		if(accept)
		dda(x1,y1,x2,y2);
}


void change_1()					//after transformation new coordinate values are written to the file 3 and being displayed
{
	int line,vis,opcode;
	float x,y,x1,y1;
	int a=0,c=0;
	fp = fopen("disp3.txt","r+");
			while(c!=4)
			{
				fscanf(fp,"%d %d ",&line,&opcode);
				fscanf(fp,"%d ",&vis);
				x=tresx[a];
				y=tresy[a];
				fprintf(fp,"%e %e\n",tresx[a],tresy[a]);
				a++;
				if(a==3)
				a=0;
				switch(opcode)
				{
					case 0: translate(x,y);
						x1=x;y1=y;
					        break;
					case 1: dda(x1,y1,x,y);
						x1=x;y1=y;
						break;
					case 2: circle(x,y,x1,y1);
						break;
					case 3: SetPixel(x,y);
						break;
				}
			c++;
			}
			fclose(fp);
}

void menu2(int value2){					//menus for the 2nd window
	if(value2 == 12)
	{	
		glutDestroyWindow(win);
	}
	else if (value2 == 11)
	{	
		pointsz(1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		xb=2000;
		ya=2025;
		xa=2200;
		yb=2025;
		display2();		
		glEnd();
		glFlush();
		window_no=3;
	}
}

void createMenu2(void){
	menuid = glutCreateMenu(menu2);
	glutAddMenuEntry("START GAME",11);
	glutAddMenuEntry("QUIT", 12); 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void call1()
{
    renderBitmapString(1800,3500,(void *)font1,"WELCOME!!!");
    renderBitmapString(1500,3350,(void *)font1,"..RIGHT CLICK FOR THE POP UP MENU..");
}

void call2()
{
    renderBitmapString(500,3500,(void *)font,"Welcome to the game!");
    renderBitmapString(500,3000,(void *)font,"Instructions:");
    renderBitmapString(600,2500,(void *)font,"-The goal of this game is to eat the food which is displayed on the screen at random points and make the snake grow longer.");
    renderBitmapString(600,2000,(void *)font,"-Use the arrow keys to move the snake left,right,up and down.");
    renderBitmapString(600,1500,(void *)font,"-The game will be over once the snake hits the boundary.");
    renderBitmapString(2000,1000,(void *)font,"All the best!!");
	createMenu2();	
}

void edgedetect(float x1,float y,float x2,float y2,int *le,int *re)
{
    float temp,x,mx;
    int i;

    if(y>y2)
    {
        temp=x1,x1=x2,x2=temp;
        temp=y,y=y2,y2=temp;
    }

    if(y==y2)
        mx=x2-x1;
    else
        mx=(x2-x1)/(y2-y);

    x=x1;
   for(i=((int)y);i<=((int)y2);i++)
    {
        if(x<(float)le[i] )
           le[i]=((int)x);
        if( x>(float)re[i])
           re[i]=((int)x);
        x+=mx;
    }
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    int le[500],re[500],i,j;

    for(i=0;i<500;i++)
        le[i]=500,re[i]=0;

    edgedetect(x1,y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,y1,le,re);

    for(j=0;j<500;j++)
    {
          if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                SetPixel(i,j);
    }
}

void show3()					//reading from the added segment
{
	int n1=1,s,line,opcode,last_op,vis,o,ip=0,la1,m=0;
	float x,y,arx[10],ary[10];	
	node *p;
	p=head;
	while(p!=NULL)
	{
			if(m<added)
			p=p->next;
			fp = fopen("disp3.txt","r");
			while(n1!=p->start_add)
			{
				fscanf(fp,"%d %d %d %e %e",&line,&opcode,&vis,&x,&y);
				last_op=opcode;
                                n1++;
			}
			o=0;
			while(n1!=p->end_add)
			{
				fscanf(fp,"%d %d %d %e %e",&line,&opcode,&vis,&x,&y);
				arx[o]=x;
				ary[o++]=y;
				n1++;
			}
			fscanf(fp,"%d %d %d %e %e",&line,&opcode,&vis,&x,&y);
			arx[o]=x;
			ary[o++]=y;
			fclose(fp);
			p=p->next;
	}
	s=u;
	switch(mouse_val)
	{
		case 1:
			while(s<=(u+3))
			{
				trans(arx[s],ary[s],tx,ty);
				tresx[s]=xnew;
				tresy[s]=ynew;
				s++;
			}
			break;
		case 2:
			while(ip<=1)
			{
			if(arx[ip]>arx[ip+1])
				la1=ip+1;
			else
				la1=ip;
			ip++;
			}
			while(s<=(u+3))
			{	
				rot(arx[s],ary[s]);
				tresx[s]=xnew;
				tresy[s]=ynew;
				s++;
			}
			break;
		case 3:
			while(s<=(3+u))
			{	
				scale(arx[s],ary[s],sx,sy);
				tresx[s]=xnew;
				tresy[s]=ynew;
				s++;
			}
			break;
	}
}

void change_tra()			//setting segment's tx ty values
{
	node *p=head;
	while(p!=NULL)
	{
		p->tx=tx;
		p->ty=ty;
		p=p->next;
	}
}

void change_sca()
{
	node *p=head;
	while(p!=NULL)
	{
		p->sx=sx;
		p->sy=sy;
		p=p->next;
	}
}

void change_rot()
{
	node *p=head;
	while(p!=NULL)
	{
		p->theta=theta;
		p=p->next;
	}
}

void for_disp1(){				//calling clipping for disp file 1
	int line,opcode,x,y,x1,y1,vis;
	fp = fopen("disp1.txt","r");
	while(!feof(fp))
	{
	fscanf(fp,"%d %d %d %d",&opcode,&x,&y,&vis);
	switch(opcode)
	{
		case 0: translate(x,y);
		        x1=x;y1=y;
		        break;
		case 1: cohen(x1,y1,x,y);
			x1=x;y1=y;
			break;
	}
	}
	fclose(fp);
}

void for_disp3(){				//calling clipping for display file 3
	int line,opcode,vis;
	float x,y,x1,y1;
	fp = fopen("disp3.txt","r");
	while(!feof(fp))
	{
	fscanf(fp,"%d %d %d %e %e",&line,&opcode,&vis,&x,&y);
	switch(opcode)
	{
		case 0: translate(x,y);
		        x1=x;y1=y;
		        break;
		case 1: cohen(x1,y1,x,y);
			x1=x;y1=y;
			break;
	}
	}
	fclose(fp);
}

void change_14()				//after transformation new coordinate values are written to the file 3 and being displayed
{
	int line,vis,opcode;
	float x,y;
	fp = fopen("disp3.txt","r+");
			while(!feof(fp))
			{
				fscanf(fp,"%d %d ",&line,&opcode);
				fprintf(fp,"%d ",0);
				fscanf(fp,"%e %e\n",&x,&y);
			}
			fclose(fp);
}

void menu1(int value){				//calls menus
	if(value == 10)
	{	
		glutDestroyWindow(win);
	}
	else
	{
		mouse_val=value;
	}
	if(mouse_val == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		change_tra();
		show();
		call1();
		show1();
		show3();
		change_1();
		zx++;
	}
	else if(mouse_val == 2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		change_rot();
		show();
		call1();
		show1();
		show3();
		change_1();
		zx++;
	}		
	else if(mouse_val == 3)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		change_sca();
		show();
		call1();
		show1();
		show3();
		change_1();
		zx++;
	}
	else if(mouse_val == 4)
	{
		 glutReshapeFunc(reshape);
		 glutMouseFunc(fillsquare);
		 glutKeyboardFunc(enlargesquare);
		 glutSpecialFunc(reducesquare);
	}
	else if(mouse_val == 5)
	{
		int vis,opcode,line;
		float x,y;
			fp = fopen("disp2.txt","r+");
			fp1 = fopen("disp3.txt","a+");
			line =1;
			u=(added*4);
			printf("%d",added);
			while(line !=5)
			{
			fscanf(fp,"%d %d ",&line,&opcode);
			fscanf(fp,"%d ",&vis);
			fscanf(fp,"%e %e",&x,&y);
			fprintf(fp1,"%d %d ",u+line,opcode);
			fprintf(fp1,"%d ",1);
			fprintf(fp1,"%e %e\n",x,y);
			line++;
			}
			added++;
	fclose(fp);
	fclose(fp1);
	show1();
	create_segment();	
	}
	else if(mouse_val == 6)
	{
		dda(xmin,ymin,xmax,ymin);
		dda(xmin,ymax,xmax,ymax);
		dda(xmax,ymin,xmax,ymax);
		dda(xmin,ymin,xmin,ymax);
		
		glEnd();
		glFlush();
	
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0,1.0,1.0);
		for_disp1();
		for_disp3();
		glEnd();
		glFlush();		
	}
	else if(mouse_val == 7)
	{
	win_no++;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,1.0);
	call2();
	}
	else if(mouse_val==24)
	{
		change_14();
		show1();
	}
}

void createMenu1(void){
	animationmenu = glutCreateMenu(menu1);        
	glutAddMenuEntry("Translation", 1);
	glutAddMenuEntry("Rotation", 2);
	glutAddMenuEntry("Scaling", 3);
	glutAddMenuEntry("Rubber band", 4);

	menuid = glutCreateMenu(menu1);
	glutAddMenuEntry("Add shapes",5);
	glutAddSubMenu("Transformations", animationmenu);
	glutAddMenuEntry("Clipping",6);
	glutAddMenuEntry("Remove object",24);
        glutAddMenuEntry("continue", 7); 
	glutAddMenuEntry("quit", 10); 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void display()
{
	if(win_no==0)
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		show();
		createMenu1();
		glColor3f(0.0,1.0,0.0);
		show1();
		glColor3f(0.0,0.0,1.0);
		call1();
	}
	else if (window_no==3)				//opens third window -> snake game
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		glColor3f(0.0,0.0,1.0);
		display2();
		if((xa>=inx+50) ||(xa<=iny-50)||(ya>=inx) ||(ya<=iny))
  		{
		//call3();
		glutSwapBuffers();	
		}		
		glEnd();
		glFlush();
	}
	else
	{
		createMenu2();
		call2();
	}
	glEnd();
       	glFlush();	
}

int main(int argc,char **argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_RGB );
 win=glutCreateWindow("welcome window");
 Init();
 glutDisplayFunc(display);
 glutMainLoop();
}
