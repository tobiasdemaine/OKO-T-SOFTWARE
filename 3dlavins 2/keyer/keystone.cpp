/*

  KEYSTONE NETWORK CLIENT DEVELOPED FOR 3ldavins 2.5
  COPYRIGHT OKO T PTY LTD 2003
  AUTHOR : TDM

*/

#include <winsock2.h> 
#include <process.h>

#include <GL\glut.h>
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>	
#include <gl\glaux.h>	
#include <iostream>
#include <string>
using namespace std;

#pragma comment(lib, "wsock32.lib")
#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glaux.lib" )	

/// SETUP THE GLOBAL VARIABLES
int screen_width=640;
int screen_height=480;
bool leftButton = false;
bool middleButton = false;
int downX;
int downY;
GLuint	 keytexture;
float xcoordz = 3;
float ycoordz = 3;
float coordz[1000][2];
float coordc;
char mapname[255];
char coordstring[10000];

void *mVoid;
char sendstring[255];
///////////////////////////
/// NETWORK FUNCTIONS
///////////////////////////
unsigned __stdcall ClientThread(void *pVoid){  // the thread
	SOCKET tssck = (SOCKET)pVoid;
	int rVal;
	rVal = send(tssck, sendstring, strlen(sendstring), 0);
	if(rVal==SOCKET_ERROR)
	{
		//cout << tssck;
	}
	return(0);
}

void socketsend(){
	DWORD dwClientThread;
	unsigned ThreadAddr;
	
	sprintf(sendstring, "keystone(%s)", coordstring);
	cout << sendstring << "\n";
	dwClientThread = _beginthreadex(NULL, 0, ClientThread, mVoid, 0, &ThreadAddr);
}

	SOCKET startupSocket(){
	SOCKET theSocket;
	WORD version;
	WSADATA wsaData;
	int rVal=0;
	version = MAKEWORD(1,1);
	WSAStartup(version,(LPWSADATA)&wsaData);

	LPHOSTENT hostEntry;
	
	hostEntry = gethostbyname("192.168.0.10");
	theSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(!hostEntry)
	{
		WSACleanup();
		cout << "HOST IS NOT AVAILABLE. EXITING\n";
	}

	if(theSocket == SOCKET_ERROR)
	{
		cout << "\nFAILED TO CREATE A SOCKET" << endl;
	}

	SOCKADDR_IN serverInfo;
	
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(1009);

	rVal=connect(theSocket,(LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if(rVal==SOCKET_ERROR)
	{
		cout << "FAILED TO CONNECT TO 3DLAVINS SERVER" << endl;

	}

    return theSocket;
}


////////////////////////////////////////////////////////////////////
/// END SOCKET SHIT
//////////////////////////////////////////////////////////////////


void ascii_logo(void){
cout << "\r\n";
cout << "OKO T :  KEYSTONER 1.0  : for 3dlavins 2.5    " << "\r\n\r\n";
}




BOOL LoadGLTexture(GLuint *texPntr, char* name)
{
	BOOL success = FALSE;
	AUX_RGBImageRec *TextureImage = NULL;

	glGenTextures(1, texPntr);						// Generate 1 texture

	FILE* test=NULL;
	TextureImage = NULL;

	test = fopen(name, "r");						// test to see if the file exists
	if (test != NULL) {								// if it does
		fclose(test);									// close the file
		TextureImage = auxDIBImageLoad(name);			// and load the texture
	}

	if (TextureImage != NULL) {						// if it loaded
		success = TRUE;

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, *texPntr);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	if (TextureImage->data)
		free(TextureImage->data);

	return success;
}


void rereadstr(FILE *f,char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}




void savemapping(){
	FILE* libfile;
	libfile = fopen(mapname, "w+");
		fprintf(libfile, "%s", coordstring);
   	fclose(libfile);
	cout << "Keystone Map Saved as " << mapname << "\r\n";
}

void buildcoordstring(){
	// xcoordz:  ycoordz:
	char mess[256];
	char costr[10000] = "";
	sprintf(costr, "xcoordz:%d ycoordz:%d ;\n", (int)xcoordz, (int)ycoordz);
	for (int xf=0; xf<coordc; xf++){
		//sprintf(coordstring+bc, "x:%f y:%f ;", coordz[xf][0], coordz[xf][1]);
		sprintf(mess, "x:%f y:%f ;\n", coordz[xf][0], coordz[xf][1]);
		strcat(costr, mess);
	}
	sprintf(coordstring, "%s ", costr);
}

void loadmapping(char *name){
		sprintf(mapname, "%s", name);
		FILE *stream; 
		char oneline[255];
		if((stream = fopen(name, "rt" )) != NULL ){
		rereadstr(stream,oneline);
		sscanf(oneline, "xcoordz: %f ycoordz: %f", &xcoordz, &ycoordz);
		coordc = xcoordz * ycoordz;
			for (int xf=0; xf<coordc; xf++){
				rereadstr(stream,oneline);
				sscanf(oneline, "x:%f y:%f", &coordz[xf][0], &coordz[xf][1]);				
			}
		}else{
			cout << "could not open map : " << name << "\r\n";
			exit( 0 );		
		}
		buildcoordstring();
		socketsend();
}

void setupmapping(){
	coordc = xcoordz * ycoordz;

	float xpos = 100 / xcoordz;
	float ypos = 100 / ycoordz;

	 // coordz move in rows
	int cc = 0;
	for(float yp=0; yp<ycoordz; yp++){
		for(float xp=0; xp<xcoordz; xp++){
			coordz[cc][0] = (xp * xpos) + xpos / 2;
			coordz[cc][1] = 100 - (yp * ypos) - ypos / 2;
			cout << coordz[cc][0] << ":" << coordz[cc][1] ;
			cc++;
		}
		//cout << "\r\n";
	}
}

void newmapconfig(void){
/// new mapping
int result;
printf( "Enter a name for this new keystone map : \r\n");
result = scanf( "%s", mapname );


printf( "Enter the number of mapping points on the X axis >> \r\n");
result = scanf( "%f", &xcoordz );


printf( "Enter the number of mapping points on the Y axis >> \r\n");
result = scanf( "%f", &ycoordz );

printf( "\r\nPRESS SPACE TO SAVE MAP \r\n");
setupmapping();
}

void displaymapping(){
	// lets do all the cubes

	glPushMatrix();
		glTranslated(0,0,-45);
		
		glDisable(GL_TEXTURE_2D);
			glColor3f(0.1f,0.3f,0.0f);
		
		
		int cc=0;
		
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
		for(float yp=1; yp<ycoordz; yp++){
			if (yp == ycoordz)break;
			for(float xp=0; xp<xcoordz; xp++){
				if (xp != xcoordz-1){
				glBegin(GL_QUADS);										
					glTexCoord2f(((xp+1) / ((xcoordz-1)/100))/100, 1-(((yp-1) / ((ycoordz-1)/100))/100)); 
					glVertex2f(coordz[cc+1][0],coordz[cc+1][1]);
					glTexCoord2f((xp / ((xcoordz-1)/100))/100, 1-(((yp-1) / ((ycoordz-1)/100))/100));
					glVertex2f(coordz[cc][0],coordz[cc][1]);
					glTexCoord2f((xp / ((xcoordz-1)/100))/100, (100 - (yp / ((ycoordz-1)/100)))/100);
					glVertex2f(coordz[cc+(int)xcoordz][0],coordz[cc+(int)xcoordz][1]);
					glTexCoord2f(((xp+1) / ((xcoordz-1)/100))/100, (100 - (yp / ((ycoordz-1)/100)))/100);
					glVertex2f(coordz[cc+(int)xcoordz+1][0],coordz[cc+(int)xcoordz+1][1]);
					glEnd();
				}
			cc++;
			}
		}

		glDisable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,keytexture);
		glEnable(GL_TEXTURE_2D);
		
		glColor3f(1.0f,1.0f,1.0f);	
		glEnable(GL_TEXTURE_2D);
		
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
		glTranslated(0,0,-50);
		 cc=0;
		for(yp=1; yp<ycoordz; yp++){
			if (yp == ycoordz)break;
			for(float xp=0; xp<xcoordz; xp++){
				if (xp != xcoordz-1){
				glBegin(GL_QUADS);										
					glTexCoord2f(((xp+1) / ((xcoordz-1)/100))/100, 1-(((yp-1) / ((ycoordz-1)/100))/100)); 
					
					glVertex2f(coordz[cc+1][0],coordz[cc+1][1]);
					
					glTexCoord2f((xp / ((xcoordz-1)/100))/100, 1-(((yp-1) / ((ycoordz-1)/100))/100));
					
					glVertex2f(coordz[cc][0],coordz[cc][1]);
					
					glTexCoord2f((xp / ((xcoordz-1)/100))/100, (100 - (yp / ((ycoordz-1)/100)))/100);
					
					glVertex2f(coordz[cc+(int)xcoordz][0],coordz[cc+(int)xcoordz][1]);
					
					glTexCoord2f(((xp+1) / ((xcoordz-1)/100))/100, (100 - (yp / ((ycoordz-1)/100)))/100);
					
					glVertex2f(coordz[cc+(int)xcoordz+1][0],coordz[cc+(int)xcoordz+1][1]);
				
				glEnd();
				}
			cc++;
			}
		}
		
	glPopMatrix();
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	for (int xf=0; xf<coordc; xf++){
			glDisable(GL_TEXTURE_2D);
			glColor3f(1.0f,0.0f,0.0f);

			glPushMatrix();
			
			glTranslated(coordz[xf][0],coordz[xf][1],-2);
			glutSolidCube(1);
		glPopMatrix();
	}
}


void init(void){
	LoadGLTexture(&keytexture, "./lib/key.bmp");
	glClearColor(0.0, 0.0, 0.0, 0.0); 
    glShadeModel(GL_SMOOTH); 
   	glViewport(0,0,screen_width,screen_height);  
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f);
	glEnable(GL_DEPTH_TEST); 
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	
    glEnable(GL_TEXTURE_2D); 

}

void resize (int width, int height)
{
    screen_width=width; 
    screen_height=height;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,screen_width,screen_height); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f);
    glutPostRedisplay (); 
}


void display(void){
	

	glLoadIdentity ();											// Reset The Projection Matrix
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();						
	glLoadIdentity();
	//gluPerspective(50, (GLfloat)(width)/(GLfloat)(height), 1, 5000 );
	glOrtho(0,100,0,100,-1,5000);		
	glMatrixMode(GL_MODELVIEW);			
	glPushMatrix();	
	glLoadIdentity();					
		
	displaymapping();

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();
				
	glFlush();
	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
        
    switch (key)
    {
        case ' ':
            savemapping();
        break;
		case 's': case 'S':
            buildcoordstring();
			socketsend();

        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    downX = x;
    downY = y;
	//cout << x << ":" << y << "\r\n";
    leftButton = ((button == GLUT_LEFT_BUTTON) && 
                  (state == GLUT_DOWN));
    middleButton = ((button == GLUT_MIDDLE_BUTTON) && 
                    (state == GLUT_DOWN));
}

bool movecoord;
int coordid;

void motion(int x, int y)
{
    float xper = (float)x / ((float)screen_width/100);
	float yper = 100 - ((float)y / ((float)screen_height/100));
	if (leftButton)
    {
        for (int xf=0; xf<coordc; xf++){
			if ((xper <= (coordz[xf][0]+1)) && (xper >= (coordz[xf][0]-1))){
				if ((yper <= (coordz[xf][1]+1)) && (yper >= (coordz[xf][1]-1))){
					// now we can move the vertex point
					// cout << "got point: " << xf ;  
					movecoord=true;
					coordid=xf;
				}
			}
		}
		if (movecoord){
			coordz[coordid][0] = xper;
			coordz[coordid][1] = yper;
		}
		
    }
    downX = x;
    downY = y;

    glutPostRedisplay();
	resize(screen_width, screen_height);
}

void pasmotion(int x, int y)
{
   movecoord=false; 
   
	resize(screen_width, screen_height);
}

int main(int argc, char **argv)
{
    ascii_logo();
	SOCKET theSocket;
	theSocket = startupSocket();
	mVoid = (void*)theSocket;

	if( argc == 2){
        loadmapping(argv[1]);
	}else{
		newmapconfig();
	}



	glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("OKO T : 3DLAVINS KEYSTONE NETWORK CLIENT");    
    
	glutReshapeFunc (resize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(pasmotion);
    glutKeyboardFunc (keyboard);
    //glutSpecialFunc (keyboard_s);
    init();
	glutDisplayFunc(display);
    glutMainLoop();

    return(0);    
}

