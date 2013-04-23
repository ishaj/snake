#include <GL/glut.h>
#include <stdlib.h>
 
void createMenu(void);
static int win;
static int addingmenu;
static int menuid;
static int animationmenu;
static int val = 0;

int main(int argc, char **argv){
 
	// normal initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	//glutInitWindowSize(500,500);
	//glutInitWindowPosition(100,100);
 
	win = glutCreateWindow("Snake Game");
 
	// put all the menu functions in one nice procedure
	createMenu();
 
	// set the clearcolor and the callback
	//glClearColor(0.0,0.0,0.0,0.0);
 
	glutDisplayFunc(disp);
 
	// enter the main loop
	glutMainLoop();
 
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
        glutAddMenuEntry("continue", 0); 
	glutAddMenuEntry("quit", 0); 
 
	// Let the menu respond on the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
 
 
}

void disp(void){
	// Just clean the screen
	glClear(GL_COLOR_BUFFER_BIT); 
	if(val == 1){

		
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
		
	}
	glFlush();
}
 
void menu(int value){
	if(value == 0){
		glutDestroyWindow(win);
		exit(0);
	}else{
		val=value;
	}
if(val == 1){


	}
	else if(val == 2){

}
		
	else if(val == 3){
		
	}
	else if(val == 4){
		
	}
	else if(val == 5){
	test();
		
	}
	else if(val == 6){
		
	}
	
	// you would want to redraw now
	glutPostRedisplay();
}




