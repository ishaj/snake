#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
void createMenu(void);
static int win;
static int addingmenu;
static int menuid;
static int animationmenu;
static int val = 0;
void menubar(){
	if(val == 1){		
	}
	else if(val == 2){
	}
		
	else if(val == 3){
		
	}
	else if(val == 4){
		
	}
	else if(val == 5){
	glVertex2f(0.25,0.25);
	glVertex2f(0.5,0.25);	
		
	}
	else if(val == 6){
		
	}
	else if(val == 7)
	{
	glVertex2f(0.25,0.5);
	glVertex2f(0.5,0.5);
	}
}

void disp(void){
	// Just clean the screen
        glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINES);
        menubar();
        glEnd();
	glFlush();
}

void menu(int value){
	if(value == 0){
		glutDestroyWindow(win);
		//exit(0);
	}
	else{
		val=value;
	}
       /* if(val == 1){
        }
	else if(val == 2){

}
		
	else if(val == 3){
		
	}
	else if(val == 4){
		
	}
	else if(val == 5){
		
	}
	else if(val == 6){
        exit(0);
		
	}
	
	// you would want to redraw now*/
	glutPostRedisplay();
}



void createMenu(void){
	//menu
 
	// Create a submenu
	animationmenu = glutCreateMenu(menu);
        
	// Add sub menu entry
	glutAddMenuEntry("Translation", 1);
	glutAddMenuEntry("Rotation", 2);
	glutAddMenuEntry("Scaling", 3);
	glutAddMenuEntry("Rubber band", 4);
	

 
	// Create the menu, this menu becomes the current menu
	menuid = glutCreateMenu(menu);
 
	// Create an entry
glutAddMenuEntry("Add shapes",5);

	glutAddSubMenu("Transformations", animationmenu);


	// Create an entry
	glutAddMenuEntry("Clipping",6);
        glutAddMenuEntry("continue", 7); 
	glutAddMenuEntry("quit", 0); 
 
	// Let the menu respond on the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
 
 
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA );
	//glutInitWindowSize(500,500);
	//glutInitWindowPosition(100,100);
 
	glutCreateWindow("Snake Game");
 
	// put all the menu functions in one nice procedure
	createMenu();
 
	// set the clearcolor and the callback
	//glClearColor(0.0,0.0,0.0,0.0);
 
	glutDisplayFunc(disp);
 
	// enter the main loop
	glutMainLoop();
 
}




