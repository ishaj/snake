#include <GL/glut.h>
#include <stdio.h>
//int w=4000, h=4000;
void * font = GLUT_BITMAP_9_BY_15;
void * font1 = GLUT_BITMAP_TIMES_ROMAN_24;
double t;
static void resize(int width,int height)
{
    //w = 4000;
    //h = 4000;
    //glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity() ;
}

void Init()
 {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,4000,0,4000);
 }

/*void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);
}*/

void resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void callstring()
{
    //setOrthographicProjection();
    //glPushMatrix();
    //glLoadIdentity();
    renderBitmapString(1000,1000,(void *)font,"Welcome to the game! :)");
    renderBitmapString(3000,1500,(void *)font,"Instructions:");
    renderBitmapString(3000,2000,(void *)font,"-The goal of this game is to eat the food which is displayed on the screen at random points and make the snake grow longer.");
    renderBitmapString(3000,2500,(void *)font,"-Use the arrow keys to move the snake left,right,up and down.");
    renderBitmapString(3000,3000,(void *)font,"-The game will be over once the snake hits the boundary.");
    renderBitmapString(1000,3500,(void *)font,"All the best!!");
    //glPopMatrix();
    //resetPerspectiveProjection();
}

/*void call1()
{
    setOrthographicProjection();
    //glPushMatrix();
    //glLoadIdentity();
    //glPointsz(5.0);
    renderBitmapString(550,50,(void *)font1,"WELCOME :)");
    //glPopMatrix();
    resetPerspectiveProjection();
}*/

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0, 0.0, 1.0);
    callstring();
    glutSwapBuffers();
 }


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    //glutInitWindowSize(640,480);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     
    glutCreateWindow("Instructions page");
    Init();     
    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
