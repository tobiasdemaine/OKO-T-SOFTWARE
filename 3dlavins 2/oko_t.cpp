#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>	
#include <gl\glaux.h>
											
#include <vfw.h>

#include <process.h>  

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>

#include "oko_t.h"												
#include "3dsloader.h"
#include "GLbase.h"
#include "math.h"
#include "bass.h"												// Header File For NeHeGL

#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glaux.lib" )								// Search For GLu32.lib While Linking
#pragma comment( lib, "vfw32.lib" )								// Search For VFW32.lib While Linking
#pragma comment( lib, "bass.lib" )
#pragma comment(lib, "wsock32.lib")

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

///////////////////
// config for clients
///////////////////
char key_one[20] = "htgkiloppaa4";
char key_two[20] = "hjthreooossa";
char co_name[20] ="oko t";
bool multisrver = true;
bool dynakey = false;
bool newblast = false;
bool widescreen_fov = false;
bool superanamorphic = true;
bool mlighting;
///////////////////

typedef struct {

  HANDLE		hExit;
  SOCKET		Socket;
  int			nMethod;
  DWORD			dwConnectTime;
  DWORD			dwRecv;
  DWORD			dwSend;
  
}REQUEST, *LPREQUEST;


char key1[20];
char key2[20];
void socketThread( void *dummy );

GL_Window*	g_window;
Keys*		g_keys;

// define class objects

obj_type object;
obj_type dynamesh;

/// starts up server
int t_connect=0;
bool srvwait;


// User Defined Variables
float		angle;												// Used For Rotation
int			next;												// Used For Animation
int			tframe=0;											// Frame Counter
int			effect;												// Current Effect
bool		bg=TRUE;											// Background (Default On)


///audio vars
float fft[1024];
float sound;
float slevel = 0.2;
bool beat;

/// FOV

GLfloat fov[4];

/// MESH VARS // FX vars
GLuint  overunder;
GLuint  overunder4;
GLuint	mesh;
GLuint	mesh_p[1000];
GLuint  mesh_c=0;

int effectC=0;
int frame=0;
char fxnames[1000];


/// camera Variables
const float piover180 = 0.0174532925f;

   
float heading;
float xpos;
float zpos;
float ypos;
GLfloat	yrot;				// Y Rotation
GLfloat lookupdown = 0.0f;
GLfloat	z=0.0f;				// Depth Into The Screen

int internal_camera_path;


AVISTREAMINFO		psi;										// Pointer To A Structure Containing Stream Info
PAVISTREAM			pavi;										// Handle To An Open Stream
PGETFRAME			pgf;										// Pointer To A GetFrame Object
BITMAPINFOHEADER	bmih;										// Header Information For DrawDibDraw Decoding
long				lastframe=24;									// Last Frame Of The Stream
int					width=720;										// Video Width
int					height=576;										// Video Height
int					awidth=512;										// Video Width
int					aheight=256;										// Video Height
char				*pdata;										// Pointer To Texture Data
int					mpf=41;										// Will Hold Rough Milliseconds Per Frame

//GLUquadricObj *quadratic;										// Storage For Our Quadratic Objects

HDRAWDIB hdd;													// Handle For Our Dib
HBITMAP hBitmap;												// Handle To A Device Dependant Bitmap
HDC hdc = CreateCompatibleDC(0);								// Creates A Compatible Device Context
unsigned char* data = 0;										// Pointer To Our Resized Image


//// config vars 
int		screens;
bool	bitblast;
bool   	dualdesk;
bool	multiserver;
int		serverid;
int		anti_theft[4];
char	owner[20];
char	appname[20];
int		infoshow=0;
/////// texture loading 
GLuint	texttexture[100];
GLuint	texture;
GLuint	t_texture[1000];
GLuint	v_texture[20][2280];
int		v_inf[10000][2];
int		v_current_frame[20];
int		v_vidset[20];
int		pingpong[20];
int		ppong[20];

int		t_textureC=0;
int		screenhack[] = {1,1,1,1};


SOCKET client;

char tmess[512];
/////////camera//////////////////////////////////////////////
int currentcam[1000];
int cambeat[1000];

/////////osciliscope variables//////////////////////////////

float os[26][26];

//// tscript arrays for fx and meshes
int beatscaled[1000];
int tblend[1000];
int applyvideo[1000];
int applyvideomesh[1000]; // todo
int meshwire[1000];
float tposition[1000][3];
float trotate[1000][4];
int cameralock[1000];
int meshfft[1000];
int meshbeat[1000];
int tmeshtype[1000];
int texttype[1000];
int textsize[1000];
int textfont[1000];
float tcolor[1000][4];
char tekst[10000];
int tekst_loc[1000][2];
int meshfxbeat[1000];
int	underlay[20];
int	overlay[20];
float cam_pos[4][3];
float cam_rot[4][4];
int blendtype[1000]; // todo
int cameralockrot[1000]; // todo
int fx_mesh[1000];
float scale[1000][3];


///// scene arrays
int currentscene;
int scenecount;
int scene[1000]; // scene on and off
char sc_names[100000];
int sc_meshc[1000];
int sc_mesh_index[1000][1000]; // [sceneid][meshid]
int sc_beatscaled[1000][1000]; // [sceneid][meshindexid]
int sc_blend[1000][1000];
int sc_applyvideo[1000][1000];
int sc_meshwire[1000][1000];
float sc_tposition[1000][1000][3];
float sc_trotate[1000][1000][4];
float sc_mrotate[1000][1000][4];
int sc_cameralock[1000][1000];
int sc_meshfft[1000][1000];
int sc_meshbeat[1000][1000];
int sc_tmeshtype[1000][1000];
int sc_texttype[1000][1000];
int sc_textsize[1000][1000];
int sc_textfont[1000][1000];
float sc_tcolor[1000][1000][4];
char sc_tekst[1000][10000]; ///????????
int sc_tekst_loc[1000][1000][2];
int sc_meshfxbeat[1000][1000];
int	sc_underlay[1000][20];
int	sc_overlay[1000][20];
int sc_fxonoff[1000][1000];
float sc_cam_pos[1000][4][3];
float sc_cam_rot[1000][4][4];
int sc_blendtype[1000][1000]; 
int sc_cameralockrot[1000][1000]; 
float sc_scale[1000][1000][3];
int sc_fx_vid[1000][1000][20];
int sc_mesh_vid[1000][1000][20];
int sc_fx_mesh[1000][1000];
float sc_position[1000][3];
float sc_rotation[1000][4];
float sc_onscreen[1000][1000];

float sc_camposition[1000][3];
float sc_camrotation[1000][4];


///////
int txc=10;
int mfxc[1000];
int mfx[1000];

int sysaviId=99;
int sysavi=0;

int rmode=0;// rendermode

/// beat detectstuff
int beatdetect =0;
int beatleft;
int beatright;
float beatclip;


// loading system
bool loadingSystem = TRUE;


int sport;// portid
int fcount = 0;

/// audio
BOOL CALLBACK DuffRecording(void *buffer, DWORD length, DWORD user)
{
	return TRUE; // continue recording
}

/////
void SaveBMP(char* filename, unsigned int width, unsigned int height, unsigned char* mdata)
	{
	FILE*			 file;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	
	//Open file in write binary mode
	file= fopen(filename, "wb");
	if(!file)
		return;

	//Define the bitmap file header
	bitmapFileHeader.bfSize		= sizeof(BITMAPFILEHEADER);
	bitmapFileHeader.bfType		= 0x4D42;
	bitmapFileHeader.bfReserved1= 0;
	bitmapFileHeader.bfReserved2= 0;
	bitmapFileHeader.bfOffBits  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	
	// define the bitmap information header
	bitmapInfoHeader.biSize			= sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biPlanes		= 1;
	bitmapInfoHeader.biBitCount		= 24;
	bitmapInfoHeader.biCompression	= BI_RGB;					//No compression
	bitmapInfoHeader.biSizeImage	= abs(width)*abs(height)*3;	//Absolute value of Width*absolute value of height*RGB bytes
	bitmapInfoHeader.biXPelsPerMeter= 0;
	bitmapInfoHeader.biYPelsPerMeter= 0;
	bitmapInfoHeader.biClrUsed		= 0;
	bitmapInfoHeader.biClrImportant = 0;
	bitmapInfoHeader.biWidth		= width;					//Bitmap width
	bitmapInfoHeader.biHeight		= height;					//Bitmap height

	
	//flipIt(data);
	

	//Write the .bmp file header to the file
	fwrite(&bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), file);

	//Write the .bmp file information header to the file
	fwrite(&bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), file);

	//Now write the actual image data
	fwrite(mdata, 1, bitmapInfoHeader.biSizeImage, file);

	fclose(file);
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


//////////////////////////////////////////
///// Dynamic Keying : only supports 1 screen @ the moment
/////////////////////////////////////////
GLuint		Keystoned;
GLuint		KeyTexture;
int	  dynaver;

void setupDynaKeyTexture(){
	unsigned int* data;											// Stored Data
	data = (unsigned int*)new GLuint[((512 * 512)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((512 * 512)* 4 * sizeof(unsigned int)));	// Clear Storage Memory
	glGenTextures(1, &KeyTexture);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, KeyTexture);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 512, 512, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;	

}

void setupDynaKeyMesh(char* name){
	Load3DS (&object,name);	
	Keystoned = glGenLists(1);
	glNewList(Keystoned,GL_COMPILE);
	for (int l_index=0;l_index<object.polygons_qty;l_index++)
		{
			glBegin(GL_POLYGON);
			//----------------- FIRST VERTEX -----------------
			// Texture coordinates of the first vertex
			glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
						  object.mapcoord[ object.polygon[l_index].a ].v);
			// Coordinates of the first vertex
			glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
						object.vertex[ object.polygon[l_index].a ].y,
						object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

			//----------------- SECOND VERTEX -----------------
			// Texture coordinates of the second vertex
			glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
						  object.mapcoord[ object.polygon[l_index].b ].v);
			// Coordinates of the second vertex
			glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
						object.vertex[ object.polygon[l_index].b ].y,
						object.vertex[ object.polygon[l_index].b ].z);
        
			//----------------- THIRD VERTEX -----------------
			// Texture coordinates of the third vertex
			glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
						  object.mapcoord[ object.polygon[l_index].c ].v);
			// Coordinates of the Third vertex
			glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
						object.vertex[ object.polygon[l_index].c ].y,
						object.vertex[ object.polygon[l_index].c ].z);
			glEnd();
		}
	glEndList();
}

// 2d mapping keying for screens

int xcoordz = 12;
int ycoordz = 12;
float coordz[10000][2];
int coordc;

void getvertexkeys(char *keystring, int vcount){

	char nstr[50];
	char nsts[50];
	
	int gfc = 0;
	int sl = strlen(keystring);
	for (int s=0;s<=sl;s++){
		if (s > strcspn(keystring, ":")){
		 	nstr[gfc] = keystring[s];	
			gfc++;
		}
	}
	
	coordz[vcount][0] = atof( nstr );
	
	sl = strlen(nstr);
	gfc = 0;
	for (s=0;s<=sl;s++){
		if (s > strcspn(nstr, ":")){
		 	nsts[gfc] = nstr[s];	
			gfc++;
		}
	}
	coordz[vcount][1] = atof( nsts );
	
}

void setkeystone(char *stonestring){
	char seps[] = ";";
	
	char *test;
	
	test = strtok( stonestring, seps );
	sscanf(test, "xcoordz: %d ycoordz: %d", &xcoordz, &ycoordz);
	coordc = xcoordz * ycoordz;
	//int test1, test2;
	int g=0;
	while(coordc > g){
		
		
		test = strtok(NULL, seps);
		getvertexkeys(test, g);
		g++;
		
	}


	
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
			coordz[cc][1] = 100 - ((yp * ypos) - ypos / 2);
			cc++;
		}
		//cout << "\r\n";
	}
//	socketsend();
}

///////////////////////////////////////
// LIVE FEED USING VFW 
///////////////////////////////////////

HWND				hwndCap; //access to the capture window
CAPSTATUS			gCapStatus ;
CAPDRIVERCAPS		gCapDriverCaps ;
CAPTUREPARMS		gCapParms ;
WORD				gwDeviceIndex ;
LPBITMAPINFOHEADER  lflpbi;
BITMAPINFOHEADER	lfbmih;
HDRAWDIB			lfhdd;													
HBITMAP				lfhBitmap;												
HDC					lfhdc = CreateCompatibleDC(0);								
unsigned char*		lfdata = 0;
int					feedisgo = 0;	

BOOL				gbHaveHardware;
BOOL				livefeed;
BOOL				enablefeed=FALSE;
int					feedtoslot;
BOOL				suppressfeedpopups;
GLuint				lftexture;
int					frameformat;

LPBYTE				tpoint;


void flipRGB(void* buffer)										
{
	void* b = buffer;											
	__asm														
	{
		mov ecx, 256*256										
		mov ebx, b												
		label:													
			mov al,[ebx+0]										
			mov ah,[ebx+2]										
			mov [ebx+2],al										
			mov [ebx+0],ah										
			add ebx,3											
			dec ecx												
			jnz label											
	}
}


LRESULT PASCAL fpFrameCallback(HWND hhWnd, LPVIDEOHDR vdata) 
{ 
    if (!hhWnd) return FALSE; 
	SelectObject (lfhdc, lfhBitmap);
	lfhdd = DrawDibOpen();
	DrawDibDraw (lfhdd, lfhdc, 0, 0, 256, 256, lflpbi, vdata->lpData, 0, 0, lflpbi->biWidth, lflpbi->biHeight, 0);
	//flipRGB(lfdata);
	//glBindTexture(GL_TEXTURE_2D, lftexture);
	//GL_RGB4
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB4, GL_UNSIGNED_BYTE, vdata->lpData);
	DrawDibClose(lfhdd);
	return (LRESULT) TRUE ; 
} 

void initilizeVidCap(void){
	UINT    uError;
	DWORD   dwSize;
	int uIndex = 0; 
	HWND hTempWnd = GetDesktopWindow();
	char tmpw[20];
	hwndCap = capCreateCaptureWindow("OKO T livefeed", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hTempWnd, 1);
	capSetCallbackOnVideoStream(hwndCap, fpFrameCallback);
	capCaptureGetSetup(hwndCap, &gCapParms, sizeof(CAPTUREPARMS));
	if (uError = capDriverConnect(hwndCap, uIndex)) {
        gbHaveHardware = TRUE;
        gwDeviceIndex = uIndex;
		livefeed = TRUE;
    }
    else {
        gbHaveHardware = FALSE;
        MessageBox(g_window->hWnd, "running without a live feed", "OKO T livefeed", MB_OK | MB_ICONEXCLAMATION) ;
		livefeed = FALSE;
		loadingSystem = FALSE;
    }
	if (livefeed){
	    capDriverGetCaps(hwndCap, &gCapDriverCaps, sizeof (CAPDRIVERCAPS)); 
		if (!suppressfeedpopups){
			capDlgVideoSource(hwndCap); 
			Sleep(10);
			capDlgVideoFormat(hwndCap); 
		}
		dwSize = capGetVideoFormatSize(hwndCap);
		lflpbi = (LPBITMAPINFOHEADER)LocalAlloc(LPTR, dwSize);
		capGetVideoFormat(hwndCap, lflpbi, dwSize);
		
		lfbmih.biSize = sizeof (BITMAPINFOHEADER);					
		lfbmih.biPlanes = 1;											
		lfbmih.biBitCount = 24;										
		lfbmih.biWidth = 256;											
		lfbmih.biHeight = 256	;										
		lfbmih.biCompression = BI_RGB;
		lfhBitmap = CreateDIBSection (lfhdc, (BITMAPINFO*)(&lfbmih), DIB_RGB_COLORS, (void**)(&lfdata), NULL, NULL);
		capOverlay(hwndCap, TRUE);

		capCaptureGetSetup(hwndCap, &gCapParms, sizeof(CAPTUREPARMS));
 		gCapParms.fYield=true;
		gCapParms.fAbortLeftMouse=false;
		gCapParms.fAbortRightMouse=false;
		gCapParms.fLimitEnabled=false;
		gCapParms.fCaptureAudio=false;
		gCapParms.dwRequestMicroSecPerFrame=(DWORD) (1.0e6 / 20);
		gCapParms.wNumVideoRequested=5;
		gCapParms.wStepCaptureAverageFrames=0;
		capCaptureSetSetup(hwndCap, &gCapParms, sizeof(CAPTUREPARMS)); 
		loadingSystem = false;
		capCaptureSequenceNoFile(hwndCap);
		
	}
}



void frametotexture(void){
	if (enablefeed){
		glBindTexture(GL_TEXTURE_2D, lftexture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, lfdata);
	}
}

///////////////////////////////////////////
// END OF LIVE FEED FUNCTIONS
///////////////////////////////////////////
bool LoadTGA(GLuint *txrptr, char *filename)				// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};		// Uncompressed TGA Header
	GLubyte		TGAcompare[12];									// Used To Compare TGA Header
	GLubyte		header[6];										// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;									// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;										// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;											// Temporary Variable
	GLuint		type=GL_RGBA;									// Set The Default GL Mode To RBGA (32 BPP)
	GLubyte	*fimageData;											// Image Data (Up To 32 Bits)
	GLuint	fbpp;												// Image Color Depth In Bits Per Pixel.
	GLuint	fwidth;												// Image Width
	GLuint	fheight;												// Image Height

	FILE *file = fopen(filename, "rb");							// Open The TGA File

	if(	file==NULL ||											// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)										// Did The File Even Exist? *Added Jim Strong*
			return FALSE;										// Return False
		else													// Otherwise
		{
			fclose(file);										// If Anything Failed, Close The File
			return FALSE;										// Return False
		}
	}

	fwidth  = header[1] * 256 + header[0];				// Determine The TGA Width	(highbyte*256+lowbyte)
	fheight = header[3] * 256 + header[2];				// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	fwidth	<=0	||									// Is The Width Less Than Or Equal To Zero
		fheight	<=0	||									// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))						// Is The TGA 24 or 32 Bit?
	{
		fclose(file);											// If Anything Failed, Close The File
		return FALSE;											// Return False
	}

	fbpp	= header[4];								// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= fbpp/8;							// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= fwidth*fheight*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	fimageData=(GLubyte *)malloc(imageSize);			// Reserve Memory To Hold The TGA Data

	if(	fimageData==NULL ||								// Does The Storage Memory Exist?
		fread(fimageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(fimageData!=NULL)							// Was Image Data Loaded
			free(fimageData);							// If So, Release The Image Data

		fclose(file);											// Close The File
		return FALSE;											// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)			// Loop Through The Image Data
	{															// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=fimageData[i];								// Temporarily Store The Value At Image Data 'i'
		fimageData[i] = fimageData[i + 2];		// Set The 1st Byte To The Value Of The 3rd Byte
		fimageData[i + 2] = temp;						// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);												// Close The File

	// Build A Texture From The Data
	glGenTextures(1, txrptr);						// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, *txrptr);				// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (fbpp==24)										// Was The TGA 24 Bits
	{
		type=GL_RGB;											// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, fwidth, fheight, 0, type, GL_UNSIGNED_BYTE, fimageData);
	free(fimageData);	
	return true;												// Texture Building Went Ok, Return True
}

/////////////////fontZ
/////////////////

GLuint	base[10];				// Base Display List For The Font

GLYPHMETRICSFLOAT gmf[256];

GLvoid BuildFont(int font_id, char *ttype)								// Build Our Bitmap Font
{
							// Address Buffer For Font Storage
	HFONT	font;										// Windows Font ID

	base[font_id] = glGenLists(256);								// Storage For 256 Characters


	HDC myDC = GetWindowDC(g_window->hWnd);
	font = CreateFont(	-24, 
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_NORMAL,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						ttype);		

	SelectObject(myDC, font);							// Selects The Font We Created

	wglUseFontOutlines(myDC,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						base[font_id],							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);							// Address Of Buffer To Recieve Data
}


GLvoid gl3dPrint(char *text, int font_id)								// Custom GL "Print" Routine
{
  if (text == NULL)										// If There's No Text
    return;												// Do Nothing

  glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
    glListBase(base[font_id]);									// Sets The Base Character to 32
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
  glPopAttrib();										// Pops The Display List Bits
}

///////////// file string
void rereadstr(FILE *f,char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}


void reloadconf (void){
	// loads the config filei
	
	FILE *filein;
	char oneline[255];
	if ((filein=fopen ("config.okot", "rb"))== NULL) {
		
	}
	for (int loop = 0; loop < 1000; loop++)
	{

	rereadstr(filein,oneline);
	sscanf(oneline, "screens= %d\n", &screens);
	sscanf(oneline, "bitblast= %d\n", &bitblast);
	sscanf(oneline, "serverid= %d\n", &serverid);
	sscanf(oneline, "multiserver= %d\n", &multiserver);
	sscanf(oneline, "dualdesktop= %d\n", &dualdesk);
	sscanf(oneline, "camera1_pos= %f %f %f", &cam_pos[0][0], &cam_pos[0][1], &cam_pos[0][2]);
	sscanf(oneline, "camera1_rot= %f %f %f %f", &cam_rot[0][0], &cam_rot[0][1], &cam_rot[0][2], &cam_rot[0][3]);
	sscanf(oneline, "camera1_fov= %f", &fov[0]);
	sscanf(oneline, "camera2_pos= %f %f %f", &cam_pos[1][0], &cam_pos[1][1], &cam_pos[1][2]);
	sscanf(oneline, "camera2_rot= %f %f %f %f", &cam_rot[1][0], &cam_rot[1][1], &cam_rot[1][2], &cam_rot[1][3]);
	sscanf(oneline, "camera2_fov= %f", &fov[1]);
	sscanf(oneline, "camera3_pos= %f %f %f", &cam_pos[2][0], &cam_pos[2][1], &cam_pos[2][2]);
	sscanf(oneline, "camera3_rot= %f %f %f %f", &cam_rot[2][0], &cam_rot[2][1], &cam_rot[2][2], &cam_rot[2][3]);
	sscanf(oneline, "camera3_fov= %f", &fov[2]);
	sscanf(oneline, "camera4_pos= %f %f %f", &cam_pos[3][0], &cam_pos[3][1], &cam_pos[3][2]);
	sscanf(oneline, "camera4_rot= %f %f %f %f", &cam_rot[3][0], &cam_rot[3][1], &cam_rot[3][2], &cam_rot[3][3]);
	sscanf(oneline, "camera4_fov= %f", &fov[3]);
	sscanf(oneline, "key1= %s", &key1);
	sscanf(oneline, "key2= %s", &key2);
	sscanf(oneline, "owner= %s", &owner);
	sscanf(oneline, "app_name= %s", &appname);
	sscanf(oneline, "port= %d", &sport);
	sscanf(oneline, "enablelivefeed= %d", &feedisgo);
	sscanf(oneline, "suppressfeedpopups= %d", &suppressfeedpopups);
	}
	fclose(filein);
	return;
	
}




void flipIt(void* buffer)										// Flips The Red And Blue Bytes (256x256)
{
	void* b = buffer;											// Pointer To The Buffer
	__asm														// Assembler Code To Follow
	{
		mov ecx, 256*256										// Counter Set To Dimensions Of Our Memory Block
		mov ebx, b												// Points ebx To Our Data (b)
		label:													// Label Used For Looping
			mov al,[ebx+0]										// Loads Value At ebx Into al
			mov ah,[ebx+2]										// Loads Value At ebx+2 Into ah
			mov [ebx+2],al										// Stores Value In al At ebx+2
			mov [ebx+0],ah										// Stores Value In ah At ebx
			
			add ebx,3											// Moves Through The Data By 3 Bytes
			dec ecx												// Decreases Our Loop Counter
			jnz label											// If Not Zero Jump Back To Label
	}
}

void OpenAVI(LPCSTR szFile)										// Opens An AVI File (szFile)
{
	hdd = DrawDibOpen();										// Grab A Device Context For Our Dib
	AVIFileInit();												// Opens The AVIFile Library
	if (AVIStreamOpenFromFile(&pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL) !=0)
	{		// An Error Occurred Opening The Stream
		MessageBox (HWND_DESKTOP, "Failed To Open The AVI Stream", "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	AVIStreamInfo(pavi, &psi, sizeof(psi));						// Reads Information About The Stream Into psi
	awidth=psi.rcFrame.right-psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
	aheight=psi.rcFrame.bottom-psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top
	lastframe=AVIStreamLength(pavi);							// The Last Frame Of The Stream
	mpf=AVIStreamSampleToTime(pavi,lastframe)/lastframe;		// Calculate Rough Milliseconds Per Frame
	bmih.biSize = sizeof (BITMAPINFOHEADER);					// Size Of The BitmapInfoHeader
	bmih.biPlanes = 1;											// Bitplanes	
	bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
	bmih.biWidth = 512;											// Width We Want (256 Pixels)
	bmih.biHeight = 256;										// Height We Want (256 Pixels)
	bmih.biCompression = BI_RGB;								// Requested Mode = RGB
	hBitmap = CreateDIBSection (hdc, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&data), NULL, NULL);
	//SelectObject (hdc, hBitmap);								// Select hBitmap Into Our Device Context (hdc)
	pgf=AVIStreamGetFrameOpen(pavi, NULL);						// Create The PGETFRAME	Using Our Request Mode
	if (pgf==NULL)
	{
		// An Error Occurred Opening The Frame
		MessageBox (HWND_DESKTOP, "Failed To Open The AVI Frame 2 ", "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	
}

unsigned __stdcall  getavidata(void *pvoid){
	LPBITMAPINFOHEADER lpbi;								
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);	
	pdata=(char *)lpbi+lpbi->biSize+lpbi->biClrUsed * sizeof(RGBQUAD);

	// Convert Data To Requested Bitmap Format
	SelectObject (hdc, hBitmap);
	DrawDibDraw (hdd, hdc, 0, 0, 512, 256, lpbi, pdata, 0, 0, awidth, aheight, 0);
	return 0;
}

void GrabAVIFrame(int frame)
{
//	unsigned	ThreadAddr;
//	DWORD		dwClientThread;
//	dwClientThread = _beginthreadex(NULL, 0, getavidata, NULL,  0, &ThreadAddr);
	LPBITMAPINFOHEADER lpbi;								
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);	
	pdata=(char *)lpbi+lpbi->biSize+lpbi->biClrUsed * sizeof(RGBQUAD);

	// Convert Data To Requested Bitmap Format
	SelectObject (hdc, hBitmap);
	DrawDibDraw (hdd, hdc, 0, 0, 512, 256, lpbi, pdata, 0, 0, awidth, aheight, 0);
	
	
	//flipRGB(data);												
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
}

void CloseAVI(void)												// Properly Closes The Avi File
{
	//
	//Sleep(10);
//	DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
//	DrawDibClose(hdd);											// Closes The DrawDib Device Context
//	AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
//	AVIStreamRelease(pavi);										// Release The Stream
//	AVIFileExit();
	//MessageBox (HWND_DESKTOP, "closed avi", "Error", MB_OK | MB_ICONEXCLAMATION);	
	// Release The File
}


void buildlists (void){

	mesh_p[mesh_c-1] = glGenLists(1);

	glNewList(mesh_p[mesh_c-1],GL_COMPILE);	
	
	int l_index;
		 // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
		for (l_index=0;l_index<object.polygons_qty;l_index++)
		{
			glBegin(GL_POLYGON);
			//----------------- FIRST VERTEX -----------------
			// Texture coordinates of the first vertex
			glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
						  object.mapcoord[ object.polygon[l_index].a ].v);
			// Coordinates of the first vertex
			glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
						object.vertex[ object.polygon[l_index].a ].y,
						object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

			//----------------- SECOND VERTEX -----------------
			// Texture coordinates of the second vertex
			glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
						  object.mapcoord[ object.polygon[l_index].b ].v);
			// Coordinates of the second vertex
			glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
						object.vertex[ object.polygon[l_index].b ].y,
						object.vertex[ object.polygon[l_index].b ].z);
        
			//----------------- THIRD VERTEX -----------------
			// Texture coordinates of the third vertex
			glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
						  object.mapcoord[ object.polygon[l_index].c ].v);
			// Coordinates of the Third vertex
			glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
						object.vertex[ object.polygon[l_index].c ].y,
						object.vertex[ object.polygon[l_index].c ].z);
			glEnd();
		}

	glEndList();
	
}

void tscripterror(char *terrorstring){
	// writes to file all errors
	MessageBox(HWND_DESKTOP,terrorstring,"Error",0);
}

void settcolor(int mId, float tR, float tG, float tB){
	
	tcolor[mId][0]=(tR/2.56)/100;
	tcolor[mId][1]=(tG/2.56)/100;
	tcolor[mId][2]=(tB/2.56)/100;
	tcolor[mId][3]=1;
	
}
void loadtscript(void){
	// tscriptloader
	// T will load all tscript in the tscript dir 
	// 3DLAVINS only loads one called "tscript.okot" 
	// open the file then and stick it in one large char variable
	FILE *stream;
	char tline[255];
	
	char *t_obj;
	char *test;
	char seps[] = "()";
	char tmes[200];
	char fxn[100];
	int lineerror;
	
	int meshtype;
	int result;
	
	if((stream = fopen( "tscript/tscript.okot", "rt" )) != NULL ){
		// process the file load and fill up the vars and halt on errors to display
		int loop = 0;
		int fxmeshc;
		while(!feof( stream )){   //for (int loop = 0; loop < 1000; loop++){
			loop++;
			lineerror=2;
			rereadstr(stream, tline);
				t_obj = strstr(tline, "effect(" );
			if( t_obj != NULL )	{
				//now we read out the tscript object
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
   				effectC++;
				sprintf(fxn,"%s#", test);
				strcat(fxnames, fxn);
   				lineerror = 1;
				fxmeshc = 0;
				//tscripterror( fxn );
			}
			t_obj = strstr(tline, "mesh(" );
			if( t_obj != NULL )	{
				meshfxbeat[effectC-1]=fxmeshc;
				mfx[mesh_c]=fxmeshc;
				fxmeshc++;
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				result = _stricmp( test, "3ds" );
				if( result == 0 ){
      				meshtype = 1;
					tmeshtype[mesh_c]=1;
					lineerror = 1;
					
				}
				result = _stricmp( test, "text" );
				if( result == 0 ){
      				meshtype = 2;
					tmeshtype[mesh_c]= 2;
					lineerror = 1;
					
				}
				result = _stricmp( test, "oscilloscope" );
				if( result == 0 ){
      				meshtype = 2;
					tmeshtype[mesh_c]= 3;
					lineerror = 1;
				}

				fx_mesh[mesh_c] = effectC-1;
				mesh_c++;
					
				if (lineerror == 3){
					sprintf(tmes,"error on line %i : mesh type not supported: %s",loop, test);
					tscripterror(tmes);
				}
			}
			t_obj = strstr(tline, "location(" );
			if( t_obj != NULL )	{
				//now we read out the tscript object
				if (meshtype == 1){
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				// load the mesh
				Load3DS (&object,test);
				buildlists ();
				
				meshtype = 0;
				}else{
					sprintf(tmes,"error on line %i : a mesh cannot be loaded from a file unless the mesh type is 3ds: %s",loop, tline);
					tscripterror(tmes);
				}
				lineerror = 1;
			}
			t_obj = strstr(tline, "bindtexture(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				LoadGLTexture(&t_texture[mesh_c-1],test);
				
				lineerror = 1;
			}
			t_obj = strstr(tline, "applyvideomap()" );
			if( t_obj != NULL )	{
				applyvideo[mesh_c-1]=1;
				lineerror = 1;
			}
			t_obj = strstr(tline, "beatscale()" );
			if( t_obj != NULL )	{
				beatscaled[mesh_c-1]=1;
				lineerror = 1;
			}
			t_obj = strstr(tline, "locktocamera(" );
			if( t_obj != NULL )	{
				cameralock[mesh_c-1]=1;
				lineerror = 1;
			}
			t_obj = strstr(tline, "blend(" );
			if( t_obj != NULL )	{
				tblend[mesh_c-1]=1;
				lineerror = 1;
			}
			t_obj = strstr(tline, "position(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				sscanf(test, "%f %f %f", &tposition[mesh_c-1][0], &tposition[mesh_c-1][1], &tposition[mesh_c-1][2]);
				lineerror = 1;
			}

			t_obj = strstr(tline, "rotation(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				sscanf(test, "%f %f %f %f", &trotate[mesh_c-1][0], &trotate[mesh_c-1][1], &trotate[mesh_c-1][2], &trotate[mesh_c-1][3]);
				lineerror = 1;
			}
			t_obj = strstr(tline, "fftscale(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				sscanf(test, "%d", &meshfft[mesh_c-1]);
				lineerror = 1;
			}

			t_obj = strstr(tline, "forcewireframe()" );
			if( t_obj != NULL )	{
				meshwire[mesh_c-1]=1;
				lineerror = 1;
			}
			t_obj = strstr(tline, "meshtype(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				result = _stricmp( test, "3d" );
				if( result == 0 ){
      				texttype[mesh_c-1] = 1;
					lineerror = 1;
				}
				result = _stricmp( test, "2d" );
				if( result == 0 ){
      				texttype[mesh_c-1] = 2;
					lineerror = 1;
				}
				if (lineerror == 2){
					sprintf(tmes,"error on line %i : Not a valid mesh type",loop);
					tscripterror(tmes);
				}
			}
			
			t_obj = strstr(tline, "font(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				sscanf(test, "%d", &textfont[mesh_c-1]);
				lineerror = 1;
			}
			t_obj = strstr(tline, "fontsize(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				sscanf(test, "%d", &textsize[mesh_c-1]);
				lineerror = 1;
			}

			t_obj = strstr(tline, "text(" );
			if( t_obj != NULL )	{
				//now we read out the tscript object
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				tekst_loc[mesh_c-1][0] = strlen(test);
				tekst_loc[mesh_c-1][1] = txc;
				txc = txc+tekst_loc[mesh_c-1][0];
				sprintf(fxn,"%s", test);
				strcat(tekst, fxn);
				lineerror = 1;
			}

			t_obj = strstr(tline, "colour(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				tcolor[mesh_c-1][3] = 1;
				sscanf(test, "%f %f %f", &tcolor[mesh_c-1][0], &tcolor[mesh_c-1][1], &tcolor[mesh_c-1][2]);
				settcolor(mesh_c-1, tcolor[mesh_c-1][0], tcolor[mesh_c-1][1], tcolor[mesh_c-1][2]);
				lineerror = 1;
			}


			t_obj = strstr(tline, "scale(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				tcolor[mesh_c-1][3] = 1;
				sscanf(test, "%f %f %f", &scale[mesh_c-1][0], &scale[mesh_c-1][1], &scale[mesh_c-1][2]);
				
				lineerror = 1;
			}

			//////// this is the clean up so if ther is an error we can not interpret it
			if (lineerror == 2){
				sprintf(tmes,"error on line %i : can not comprehend: %s",loop, tline);
				tscripterror(tmes);
      		}
				
		}
	fclose(stream);
		
				
	}else{
		tscripterror( "tscript file could not be found\n" );
	}
}

void get_vidlib(){
	char seps[]= ";";
	char *test;
	char tline[255];
	FILE *stream;
	if((stream = fopen( "lib/vidlib.okot", "rt" )) != NULL ){
		int loop = 0;
		while( !feof( stream ) ){
			rereadstr(stream, tline);
			// get name of file and do nothing with it
			test = strtok(tline, seps);
			// get location of file 
			test = strtok(NULL, seps);
			if( test != NULL ) sscanf(test, "%d", &v_inf[loop][0]);
			// get frame count 
			test = strtok(NULL, seps);
			if( test != NULL ) sscanf(test, "%d", &v_inf[loop][1]);
		loop++;
		}
	}
	fclose(stream);
}

void loadfonts(){
	char seps[]= ";";
	char *test;
	char tline[255];
	FILE *stream;
	if((stream = fopen( "lib/fonts.okot", "rt" )) != NULL ){
		int loop = 0;
		while( !feof( stream ) ){
			rereadstr(stream, tline);
			test = strtok(tline, seps);
			
			if( test != NULL ) BuildFont(loop, test);
		loop++;
		}
	}
	fclose(stream);
}



void savescenes(void){
	for(int ssc=0; ssc<scenecount; ssc++){
		if(ssc != 0){
			// now we can save a scene

		}
	}
}

void loadscene(int sloop, char *stest){
	//loads the scene into the scene arrays
	
}

void loadscenes(void){
/*	char seps[]= ";";
	char *test;
	char tline[255];
	FILE *stream;
	if((stream = fopen( "lib/scenes.okot", "rt" )) != NULL ){
		int loop = 0;
		while( !feof( stream ) ){
			rereadstr(stream, tline);
			test = strtok(tline, seps);
			if (loop != 0){
				if( test != NULL ) loadscene(loop, test);
			}
		loop++;
		scenecount = loop;
		}
	}
	fclose(stream);
*/
}


// populates scene0
void populatescenezero(void){
	currentscene = 0;
	scene[0] = 1;
	sprintf(sc_names ,"%s", "default;");
	sc_meshc[0] = mesh_c;
	currentcam[0] = 0;
	// force scene to be shown
	scene[0]=1;
	// force scene count if there are no scenes loaded into the system
	scenecount=1;
	for(int cl=0; cl<3; cl++){ 
		sc_position[0][cl] = 0;
	}
	for(cl=0; cl<4; cl++){ 
		sc_rotation[0][cl] = 0;
	}
	for(unsigned int cloop=0;cloop<mesh_c; cloop++){
		sc_fx_mesh[0][cloop] = fx_mesh[cloop];
		sc_mesh_index[0][cloop] = cloop; 
		sc_beatscaled[0][cloop] = beatscaled[cloop]; 
		sc_blend[0][cloop] = tblend[cloop];
		sc_applyvideo[0][cloop] = applyvideo[cloop];
		sc_meshwire[0][cloop] = meshwire[cloop];
		sc_cameralock[0][cloop] = cameralock[cloop];
		sc_meshfft[0][cloop] = meshfft[cloop];
		sc_meshbeat[0][cloop] = meshbeat[cloop];
		sc_tmeshtype[0][cloop] = tmeshtype[cloop];
		sc_texttype[0][cloop] = texttype[cloop];
		sc_textsize[0][cloop] = textsize[cloop];
		sc_textfont[0][cloop] = textfont[cloop];
		sc_meshfxbeat[0][cloop] = meshfxbeat[cloop];
		sc_blendtype[0][cloop] = blendtype[cloop]; 
		sc_cameralockrot[0][cloop] = cameralockrot[cloop]; 
		for(cl=0; cl<2; cl++){ 
			sc_tekst_loc[0][cloop][cl] = tekst_loc[cloop][cl];
		}
		for(cl=0; cl<3; cl++){ 
			sc_scale[0][cloop][cl] = scale[cloop][cl]; 
			sc_tposition[0][cloop][cl] = tposition[cloop][cl];
			sc_scale[0][cloop][cl] = 1;
		}
		for(cl=0; cl<4; cl++){ 
			sc_trotate[0][cloop][cl] = trotate[cloop][cl];
			sc_tcolor[0][cloop][cl] = tcolor[cloop][cl];
			sc_mrotate[0][cloop][cl] = 0;
		
		}

		sc_onscreen[0][cloop] = 0;
		
	}
	
	sprintf(sc_tekst[0] ,"%s", tekst);
}


BITMAPINFOHEADER  pixbi;
HDRAWDIB			pixhdd;	
void setupblt(){
		/// test new blit features
							// Stored Data
	//ZeroMemory(data,((640 * 480)* 3 * sizeof(unsigned int)));	// Clear Storage Memory
}




BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	/// this is where we test to see if we can initialize the system


	if (widescreen_fov == true){
		width=32;										
		height=9;
	}
	//setupblt();

	char *k1;
	char *k2;
	char *k3;
	reloadconf();
	k1 = strstr(key_one, key1 );
	k2 = strstr(key_two, key2 );
	k3 = strstr(co_name, owner );
	if((k1 != NULL)&&(k2 != NULL)&&(k3 != NULL)){	
	
	}else{
		MessageBox(HWND_DESKTOP,"Invalid Keys : shutting down \n contact support@okot.net for help","Error",0);
		exit(0);
		return TRUE;
	}
	if ((!multisrver) && (multiserver == 1)){
		MessageBox(HWND_DESKTOP,"THIS IS NOT A MULTISERVER VERSION \n contact support@okot.net for help","Error",0);
		exit(0);
		return TRUE;
	}
	_beginthread( socketThread, 0, NULL );
	///
	strcat(tekst, "1234567890");
	
	/// sets up audio
	g_window	= window;
	g_keys		= keys;

	//_beginthread( vidcapture, 0, NULL );
	//initilizeVidCap();
	if (BASS_GetVersion()!=MAKELONG(1,5)) {
		MessageBox(HWND_DESKTOP,"connection to audio driver failed","Error",0);
	}
	if (!BASS_RecordInit(-1)) {
		MessageBox(HWND_DESKTOP,"connection to audio driver failed","Error",0);
		
	}
	// start recording (44100hz mono 16-bit)
	if (!BASS_RecordStart(44100,BASS_SAMPLE_MONO,&DuffRecording,0)) {
		MessageBox(HWND_DESKTOP,"cant start recording","Error",0);
	}
	

	
	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero
	
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);						// Black Background
	
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LESS);									// The Type Of Depth Testing (Less Or Equal)
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate


	
	// setup alot of stuff here
	
	get_vidlib();
	
	//opens avi file this will be moved elsewhere

	// Open The AVI File
    
	// loads font texture
	loadfonts();
		
	// this parses the tscript
	loadtscript();
	populatescenezero();
	
	loadscenes();
	
	if(dynakey){
		setupDynaKeyTexture();
		//setupDynaKeyMesh("./lib/keystone/key.3ds");
		setupmapping();
	}

	overunder = glGenLists(1);
	glNewList(overunder,GL_COMPILE);
	glBegin(GL_QUADS);										
			// Front Face
			glTexCoord2f(1.0f, 1.0f); glVertex2d(640,480);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(0,480);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(0,0);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(640,0);
	glEnd();
	glEndList();

	overunder4 = glGenLists(1);
	glNewList(overunder,GL_COMPILE);
	glBegin(GL_QUADS);										
			// Front Face
			glTexCoord2f(1.0f, 1.0f); glVertex2d(640,480);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(0,480);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(0,0);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(640,0);
	glEnd();
	glEndList();
	// some test stuff here
	LoadGLTexture(&texture,"lib/oko-t/oko-t-big.oko");
	if(feedisgo==1){
		LoadGLTexture(&lftexture,"lib/oko-t/oko-t.oko");
		initilizeVidCap();
	    loadingSystem = FALSE;
		//_beginthread( captureit, 0, NULL );
	}else{
		loadingSystem = false;
	}
	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	//free up the meshes
	glDeleteLists(mesh, mesh_c); 
	BASS_Free();
}


void fxswitch(int refnum){
	if (sc_fxonoff[currentscene][refnum]==1){
		sc_fxonoff[currentscene][refnum]=0;
	}else{
		sc_fxonoff[currentscene][refnum]=1;
	}
}

int loadvid=0;
int vidset;
int vidslot;
int framein=0;
int vidloaded=0;
void loadvideolib(){
	char tmes[256];
	if (loadvid==1){
		sprintf(tmes,"lib/vid/%d/%d.oko",v_inf[vidset][0], framein);
		LoadGLTexture(&v_texture[vidslot][framein], tmes);
		framein++;
		if(framein==(v_inf[vidset][1])){
			loadvid=0;
			framein=0;
			v_current_frame[vidslot]=0;
			vidloaded = 1;
		}
	}
}

void setsysavi(int sId,char *mavi){
	char Tavi[100];
	if (sysavi == 1){
		if(sysaviId == sId){
			// we allow it to deactivate
			sysavi = 0;
			CloseAVI();
		}
	}else{
		sprintf(Tavi, "lib/avi/%s", mavi);
		OpenAVI(Tavi);
		sysavi = 1;
		sysaviId = sId;
	}
}

void loadvidlib(int vid_set, int vid_slot){
	loadvid=1;
	v_vidset[vid_slot] = vid_set;
	vidset=vid_set;
	vidslot=vid_slot;
}

void deletevidlib(int vid_set, int vid_slot){
	glDeleteTextures(v_inf[vid_set][1], &v_texture[vid_slot][0]);
}

void underlayon(int layer){
	if (sc_underlay[currentscene][layer]==1){
		sc_underlay[currentscene][layer]=0;
	}else{
		sc_underlay[currentscene][layer]=1;
	}
}

void overlayon(int layer){
	if (sc_overlay[currentscene][layer]==1){
		sc_overlay[currentscene][layer]=0;
	}else{
		sc_overlay[currentscene][layer]=1;
	}
}


void setvidtoeffect(int effect_id, int vid_id){
	if (sc_fx_vid[currentscene][effect_id][vid_id]==0){
		sc_fx_vid[currentscene][effect_id][vid_id]=1;
	}else{
		sc_fx_vid[currentscene][effect_id][vid_id]=0;
	}
}

void setvidtomesh(int mId, int vid_id){
	if (sc_mesh_vid[currentscene][mId][vid_id]==0){
		sc_mesh_vid[currentscene][mId][vid_id]=1;
	}else{
		sc_mesh_vid[currentscene][mId][vid_id]=0;
	}
}

void setcamera(int camid){
	currentcam[currentscene] = camid;
}

void camerabeat(void){
	if (cambeat[currentscene]==1)cambeat[currentscene]=0;
	else cambeat[currentscene]=1;
}

void setcameraposition(float X, float Y, float Z){
	sc_camposition[currentscene][0] = X;
	sc_camposition[currentscene][1] = Y;
	sc_camposition[currentscene][2] = Z;
}

void setcamerarotation(float Speed, float X, float Y, float Z){
	sc_camrotation[currentscene][0] = Speed;
	sc_camrotation[currentscene][1] = X;
	sc_camrotation[currentscene][2] = Y;
	sc_camrotation[currentscene][3] = Z;
}

void setrender(int renmode){
	rmode = renmode;
}

void setposition(int mId, float X, float Y, float Z){
	sc_tposition[currentscene][mId][0] = X;
	sc_tposition[currentscene][mId][1] = Y;
	sc_tposition[currentscene][mId][2] = Z;
}
void setmeshscale(int mId, float X, float Y, float Z){
	sc_scale[currentscene][mId][0] = X;
	sc_scale[currentscene][mId][1] = Y;
	sc_scale[currentscene][mId][2] = Z;
}
void setrotation(int mId, float Speed, float X, float Y, float Z){
	sc_trotate[currentscene][mId][0] = Speed;
	sc_trotate[currentscene][mId][1] = X;
	sc_trotate[currentscene][mId][2] = Y;
	sc_trotate[currentscene][mId][3] = Z;
}

void setmrotate(int mId, float Speed, float X, float Y, float Z){
	sc_mrotate[currentscene][mId][0] = Speed;
	sc_mrotate[currentscene][mId][1] = X;
	sc_mrotate[currentscene][mId][2] = Y;
	sc_mrotate[currentscene][mId][3] = Z;
}

void beatdetection(float bclip, int bleft, int bright){
	beatclip = bclip;
	beatleft = bleft;
	beatright = bright;
}
void setvidmap(int mId){
	if (sc_applyvideo[currentscene][mId] == 1){
		sc_applyvideo[currentscene][mId] = 0;
	}else{
		sc_applyvideo[currentscene][mId] = 1;
	}
}
void setwireframe(int mId){
	if (sc_meshwire[currentscene][mId] == 1){
		sc_meshwire[currentscene][mId] = 0;
	}else{
		sc_meshwire[currentscene][mId] = 1;
	}
}
void setblend(int mId){
	if (sc_blend[currentscene][mId] == 1){
		sc_blend[currentscene][mId] = 0;
	}else{
		sc_blend[currentscene][mId] = 1;
	}
}

void setblendtype(int mId, int blendID){
	sc_blendtype[currentscene][mId] = blendID;
}

void showinfo(){
	if (infoshow==1) {
		infoshow=0;
	}else{
		infoshow=1;
	}
}
void setpingpong(int v_set, int tping){
	pingpong[v_set]=tping;
}

int sframe=0;
void setframe(){
	//if (sframe==1){
	//sframe=0;
	for(unsigned int vloop=0;vloop<20;vloop++){
			if(pingpong[vloop]==2){
				//pingpong
				if (ppong[vloop]==1){
					if (v_current_frame[vloop]>0){
						v_current_frame[vloop]--;
					}else{
						v_current_frame[vloop]=0;
						ppong[vloop]==0;
					}
				}else{
					if (v_current_frame[vloop]<(v_inf[v_vidset[vloop]][1]-2)){
						v_current_frame[vloop]++;
					}else{
						v_current_frame[vloop]=(v_inf[v_vidset[vloop]][1]-2);
						ppong[vloop]==1;
					}
				}
			}else if(pingpong[vloop]==1){
				// ping
				if (v_current_frame[vloop]>-1){
					v_current_frame[vloop]--;
				}else{
					v_current_frame[vloop]=(v_inf[v_vidset[vloop]][1]-2);
				}
			}
			else{
				//pong
				if (v_current_frame[vloop]<(v_inf[v_vidset[vloop]][1]-1)){
					v_current_frame[vloop]++;
				}else{
					v_current_frame[vloop]=0;
				}
			}
		}
	//}
	//sframe++;
	
}

void resetframe(int vid_set){
	v_current_frame[vid_set]=0;
	// if it is a n vio the we set it back this 
	if (vid_set == sysaviId){
	frame = 0;
	}
}

void setbeatscale(int mId){
	if (sc_beatscaled[currentscene][mId] == 1){
		sc_beatscaled[currentscene][mId] = 0;
	}else{
		sc_beatscaled[currentscene][mId] = 1;
	}
}





void setfont(int mId, int defont){
	sc_textfont[currentscene][mId] = defont;
}


void settextsize(int mId, float tsize){
	sc_textsize[currentscene][mId] = tsize;
}

void setmeshbeat(int eId){
	if (sc_meshbeat[currentscene][eId] == 1) sc_meshbeat[currentscene][eId] = 0;
	else sc_meshbeat[currentscene][eId] = 1;
}



void replacetext(int mId, char *mText){
	unsigned int mlen;
	// tekst_loc[tmesh][1] pos
	// tekst_loc[tmesh][0] length
	mlen = strlen(mText) - tekst_loc[mId][0];
	// now we add the newstring into tekst
	char tekza[10000]="";
	char tekzt[10000]="";
	char tektz[10000]="";
	char mmt[10]="";
	
	// 1st take the beginning of the string t
	// why does this not work
	
	strncpy(tekzt, tekst+0, tekst_loc[mId][1]);
	strcat(tekzt, mText);
	strncpy(tektz, tekst + tekst_loc[mId][1] + tekst_loc[mId][0], strlen(tekst) - (tekst_loc[mId][1] + tekst_loc[mId][0]));
	strcat(tekzt, tektz);
	strcpy(tekst, tekzt);
	// now fix up the length
	
	tekst_loc[mId][0]+= mlen;
	for(unsigned int tmesh=0;tmesh<mesh_c;tmesh++){
		if (tmeshtype[tmesh] == 2){
			if (tmesh > mId){
				tekst_loc[tmesh][1]+= mlen;
			}
		}
	}
	sprintf(sc_tekst[currentscene] ,"%s", tekst);
	for(unsigned int cloop=0;cloop<mesh_c; cloop++){
		for(int cl=0; cl<2; cl++){ 
			sc_tekst_loc[currentscene][cloop][cl] = tekst_loc[cloop][cl];
		}
	}

}
/*
void replacetext(int mId, char *mText){
	unsigned int mlen;
	// tekst_loc[tmesh][1] pos
	// tekst_loc[tmesh][0] length
	mlen = strlen(mText) - sc_tekst_loc[currentscene][mId][0];
	// now we add the newstring into tekst
	char tekza[10000]="";
	char tekzt[10000]="";
	char tektz[10000]="";
	char mmt[10]="";
	
	// 1st take the beginning of the string t

	strncpy(tekzt, sc_tekst[currentscene]+0, sc_tekst_loc[currentscene][mId][1]);
	strcat(tekzt, mText);
	strncpy(tektz, tekst + sc_tekst_loc[currentscene][mId][1] + sc_tekst_loc[currentscene][mId][0], strlen(sc_tekst[currentscene]) - (sc_tekst_loc[currentscene][mId][1] + sc_tekst_loc[currentscene][mId][0]));
	strcat(tekzt, tektz);
	strcpy(sc_tekst[currentscene], tekzt);
	// now fix up the length
	
	sc_tekst_loc[currentscene][mId][0]= sc_tekst_loc[currentscene][mId][0] + mlen;
	for(unsigned int tmesh=0;tmesh<mesh_c;tmesh++){
		if (sc_tmeshtype[currentscene][tmesh] == 2){
			if (tmesh > mId){
				sc_tekst_loc[currentscene][tmesh][1]=  sc_tekst_loc[currentscene][tmesh][1] + mlen;
			}
		}
	}
}
*/
void setlocktocamerapos(int mID){
	if(sc_cameralock[currentscene][mID] = 1) sc_cameralock[currentscene][mID] = 0;
	sc_cameralock[currentscene][mID] = 1;
}
void setlocktocamerarot(int mID){
	if(sc_cameralockrot[currentscene][mID] = 1) sc_cameralockrot[currentscene][mID] = 0;
	sc_cameralockrot[currentscene][mID] = 1;
}


void setbeatmode(void){
	if (beatdetect==1) beatdetect=0;
	else beatdetect=1;
}

void setonscreen(int mID, int ScreenID){
	sc_onscreen[currentscene][mID] = ScreenID;
}

void setfeedtovidslot(int slotID){
	if (enablefeed==TRUE){
		//if (feedtoslot == slotID){
			enablefeed=FALSE;
		//}
	}
	else{
		enablefeed=TRUE;
	}
	feedtoslot = slotID;
}



//////////////////////////////
///// SCENE TSCRIPT FUNCTIONS
//////////////////////////////

void sceneswitch(int sID){
	if(scene[sID] == 1) scene[sID] = 0; 
	else scene[sID] = 1;
}

void setcurrentscene(int sID){
	currentscene = sID;
}

void setcreatescene(int sID, char *sname){
	setcurrentscene(sID);
	strcat(sc_names, sname);
	strcat(sc_names, ";");
	for(int cl=0; cl<3; cl++){ 
		sc_position[sID][cl] = 0;
	}
	for(cl=0; cl<4; cl++){ 
		sc_rotation[sID][cl] = 0;
	}
}
void setaddfxscene(int fxId){
	for(int cloop=0; cloop<mesh_c;cloop++){
		if (fxId == fx_mesh[cloop]){
			sc_meshc[currentscene] = cloop + 1;
			sc_fx_mesh[currentscene][cloop] = fx_mesh[cloop];
			sc_mesh_index[currentscene][cloop] = cloop; 
			sc_beatscaled[currentscene][cloop] = beatscaled[cloop]; 
			sc_blend[currentscene][cloop] = tblend[cloop];
			sc_applyvideo[currentscene][cloop] = applyvideo[cloop];
			sc_meshwire[currentscene][cloop] = meshwire[cloop];
			sc_cameralock[currentscene][cloop] = cameralock[cloop];
			sc_meshfft[currentscene][cloop] = meshfft[cloop];
			sc_meshbeat[currentscene][cloop] = meshbeat[cloop];
			sc_tmeshtype[currentscene][cloop] = tmeshtype[cloop];
			sc_texttype[currentscene][cloop] = texttype[cloop];
			sc_textsize[currentscene][cloop] = textsize[cloop];
			sc_textfont[currentscene][cloop] = textfont[cloop];
			sc_meshfxbeat[currentscene][cloop] = meshfxbeat[cloop];
			sc_blendtype[currentscene][cloop] = blendtype[cloop]; 
			sc_cameralockrot[currentscene][cloop] = cameralockrot[cloop]; 
			for(int cl=0; cl<2; cl++){ 
				sc_tekst_loc[currentscene][cloop][cl] = tekst_loc[cloop][cl];
			}
			for(cl=0; cl<3; cl++){ 
				sc_scale[currentscene][cloop][cl] = scale[cloop][cl]; 
				sc_tposition[currentscene][cloop][cl] = tposition[cloop][cl];
			}
			for(cl=0; cl<4; cl++){ 
				sc_trotate[currentscene][cloop][cl] = trotate[cloop][cl];
				sc_tcolor[currentscene][cloop][cl] = tcolor[cloop][cl];
				sc_mrotate[currentscene][cloop][cl] = 0;
				sc_scale[currentscene][cloop][cl] = 1;
			}
			sc_onscreen[currentscene][cl] = 0;
			
		}
	}
}
void setdeletefxscene(int fxId){
	// count every mesh with the scene fx id then step back every mesh - the count after the 
	int fxct=0;
	int lmf;
	for(int cloop=0; cloop<sc_meshc[currentscene];cloop++){
		if (fxId == sc_fx_mesh[currentscene][cloop]){
			fxct++;
			lmf = cloop;
		}
	}
	sc_meshc[currentscene] = sc_meshc[currentscene]-fxct;
	for(cloop=0; cloop<sc_meshc[currentscene];cloop++){
		if (cloop > lmf){
			sc_fx_mesh[currentscene][cloop] = sc_fx_mesh[currentscene][cloop+fxct];
			sc_mesh_index[currentscene][cloop] = sc_mesh_index[currentscene][cloop+fxct]; 
			sc_beatscaled[currentscene][cloop] = sc_beatscaled[currentscene][cloop+fxct];
			sc_blend[currentscene][cloop] = sc_blend[currentscene][cloop+fxct];
			sc_applyvideo[currentscene][cloop] = sc_applyvideo[currentscene][cloop+fxct];
			sc_meshwire[currentscene][cloop] = sc_meshwire[currentscene][cloop+fxct];
			sc_cameralock[currentscene][cloop] = sc_cameralock[currentscene][cloop+fxct];
			sc_meshfft[currentscene][cloop] = sc_meshfft[currentscene][cloop+fxct];
			sc_meshbeat[currentscene][cloop] = sc_meshbeat[currentscene][cloop+fxct];
			sc_tmeshtype[currentscene][cloop] = sc_tmeshtype[currentscene][cloop+fxct];
			sc_texttype[currentscene][cloop] = sc_texttype[currentscene][cloop+fxct];
			sc_textsize[currentscene][cloop] = sc_textsize[currentscene][cloop+fxct];
			sc_textfont[currentscene][cloop] = sc_textfont[currentscene][cloop+fxct];
			sc_meshfxbeat[currentscene][cloop] = meshfxbeat[cloop+fxct];
			sc_blendtype[currentscene][cloop] = sc_blendtype[currentscene][cloop+fxct]; 
			sc_cameralockrot[currentscene][cloop] = sc_cameralockrot[currentscene][cloop+fxct]; 
			for(int cl=0; cl<2; cl++){ 
				sc_tekst_loc[currentscene][cloop][cl] = sc_tekst_loc[currentscene][cloop+fxct][cl];
			}
			for(cl=0; cl<3; cl++){ 
				sc_scale[currentscene][cloop][cl] = sc_scale[currentscene][cloop+fxct][cl]; 
				sc_tposition[currentscene][cloop][cl] = sc_tposition[currentscene][cloop+fxct][cl];
				sc_scale[currentscene][cloop][cl] = sc_scale[currentscene][cloop+fxct][cl];
			}
			for(cl=0; cl<4; cl++){ 
				sc_trotate[currentscene][cloop][cl] = sc_trotate[currentscene][cloop+fxct][cl];
				sc_tcolor[currentscene][cloop][cl] = sc_tcolor[currentscene][cloop+fxct][cl];
				sc_mrotate[currentscene][cloop][cl] = sc_mrotate[currentscene][cloop+fxct][cl];
				
			}
		}
	}
	
}

void setsceneposition(float X, float Y, float Z){
	sc_position[currentscene][0]=X;
	sc_position[currentscene][1]=Y;
	sc_position[currentscene][2]=Z;
}

void setscenerotation(int ang, float X, float Y, float Z){
	sc_rotation[currentscene][0]=ang;
	sc_rotation[currentscene][1]=X;
	sc_rotation[currentscene][2]=Y;
	sc_rotation[currentscene][3]=Z;
}

/////// ///////
/////// camera 
/////// ///////
float updown;
void camerarotate(int direction, float amount){
	if(direction==0){
		if(currentcam[currentscene] == 0){
		sc_camrotation[currentscene][2]-= amount;
		}else{
		updown-= amount;
		}
	}
	if(direction==1){
		if(currentcam[currentscene] == 0){
		sc_camrotation[currentscene][2]+= amount;
		}else{
		updown+= amount;
		}
	}
	if(direction==2){
		heading += amount;	
		yrot = heading;	
	}
	if(direction==3){
		heading -= amount;	
		yrot = heading;
	}
}

void cameramove(int direction, float amount){
	if (direction == 0){
	sc_camposition[currentscene][0] -= (float)sin(heading*piover180) * amount;
	sc_camposition[currentscene][2] -= (float)cos(heading*piover180) * amount;
	}
	if (direction == 1){
	sc_camposition[currentscene][0] += (float)sin(heading*piover180) * amount;
	sc_camposition[currentscene][2] += (float)cos(heading*piover180) * amount;
	}
}



float dblAngle1;
float dblAngle2;
GLfloat xtrans;
GLfloat ztrans;
GLfloat ytrans;

GLfloat scenerotx;
GLfloat sceneroty;
GLfloat scenerotz;
int cup = 1;
int cdist = 1;
void oko_camera(void){
	if (cambeat[currentscene] == 1){
        if (beat == 1){
			if (currentcam[currentscene] < 7) currentcam[currentscene]++;
			else currentcam[currentscene]=0;
		}
    }
	
	if (currentcam[currentscene] == 0){
		xtrans = -sc_camposition[currentscene][0];
		ztrans = -sc_camposition[currentscene][2];
		ytrans = -sc_camposition[currentscene][1];
		sc_rotation[currentscene][1] = 360.0f - yrot;
		glRotatef(sc_camrotation[currentscene][0],1.0f,0,0);
		glRotatef(sc_camrotation[currentscene][1],0,1.0f,0);
		glRotatef(sc_camrotation[currentscene][2],0,0,1.0f);
		glTranslatef(xtrans, ytrans, ztrans);
		xtrans = sc_camposition[currentscene][0];
		ztrans = -sc_camposition[currentscene][2];
		ytrans = -sc_camposition[currentscene][1];
	}
	
	if (currentcam[currentscene] == 1){
		float mspin=80;
		dblAngle1 = dblAngle1 + 0.03f;
        dblAngle2 = dblAngle2 + 0.03f;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}
	
	if (currentcam[currentscene] == 2){
		float mspin=80;
		dblAngle1 = dblAngle1 - 0.03f;
        dblAngle2 = dblAngle2 - 0.03f;
		xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam[currentscene] == 3){
		float mspin=120;
		dblAngle1 = dblAngle1 - 0.01f;
        dblAngle2 = updown / 100;//dblAngle2 - 0.01;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam[currentscene] == 4){
		if (cup == 1) cdist+=1;
		else cdist-=3;
		if (cdist>300) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - 0.001f;
        dblAngle2 = dblAngle2 + 0.001f;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam[currentscene] == 5){
		if (cup == 1) cdist+=6;
		else cdist-=6;
		if (cdist>100) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - 0.001f;
        dblAngle2 = dblAngle2 + 0.001f;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam[currentscene] == 6){
		if (cup == 1) cdist+=1;
		else cdist-=3;
		if (cdist>300) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - 0.001f;
        dblAngle2 = dblAngle2 + 0.001f;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}
	if (currentcam[currentscene] == 7){
		if (cup == 1) cdist+=15;
		else cdist-=15;
		if (cdist>1000) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - 0.001f;
        dblAngle2 = dblAngle2 + 0.01f;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

}


////////////////render mode/////////
void rendermode(void){
	if (rmode==0){
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
			bg = true;
	}
	if (rmode==1){
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			bg = false;
	}
	if (rmode==2){
		if (beat==1){
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glPolygonMode(GL_FRONT_AND_BACK,  GL_LINE);
			bg = false;
		}else{
			glPolygonMode(GL_FRONT_AND_BACK,  GL_FILL);
			bg = true;
		}
	}
	if (rmode==3){
		if (beat==1){
			glPolygonMode(GL_FRONT_AND_BACK,  GL_FILL);
			bg = true;
		}else{
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glPolygonMode(GL_FRONT_AND_BACK,  GL_LINE);
			bg = false;
		}
	}
}
////////////// action stations
void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	////camera keys
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}
	if (!multiserver){
		if (g_keys->keyDown [VK_PRIOR] == TRUE)
		{
			camerarotate(0, 1.0);
		}

		if (g_keys->keyDown [VK_NEXT] == TRUE)
		{
			camerarotate(1, 1.0);
		}
		if(g_keys->keyDown [VK_UP] == TRUE)
		{	
			cameramove(0, 1.0);
		}

		if(g_keys->keyDown [VK_DOWN] == TRUE)
		{
			cameramove(1, 1.0);
		}

		if(g_keys->keyDown [VK_LEFT] == TRUE)
		{	
			camerarotate(2, 1.0);
		}

		if(g_keys->keyDown [VK_RIGHT] == TRUE)
		{
			camerarotate(3, 1.0);
		}

		//rendermode keys
		
		if (g_keys->keyDown ['Q'] == TRUE)						
		{
			rmode=0;
		}
		if (g_keys->keyDown ['W'] == TRUE)						
		{
			rmode=1;
		}
		if (g_keys->keyDown ['E'] == TRUE)						
		{
			rmode=2;
		}
		if (g_keys->keyDown ['R'] == TRUE)						
		{
			rmode=3;
		}

		// camera keys
		if (g_keys->keyDown ['1'] == TRUE)						
		{
			currentcam[currentscene]=0;
		}
		if (g_keys->keyDown ['2'] == TRUE)						
		{
			currentcam[currentscene]=1;
		}
		if (g_keys->keyDown ['3'] == TRUE)						
		{
			currentcam[currentscene]=2;
		}
		if (g_keys->keyDown ['4'] == TRUE)						
		{
			currentcam[currentscene]=3;
		}
		if (g_keys->keyDown ['5'] == TRUE)						
		{
			currentcam[currentscene]=4;
		}
		if (g_keys->keyDown ['6'] == TRUE)						
		{
			currentcam[currentscene]=5;
		}
		if (g_keys->keyDown ['7'] == TRUE)						
		{
			currentcam[currentscene]=6;
		}
		if (g_keys->keyDown ['8'] == TRUE)						
		{
			currentcam[currentscene]=7;
		}
		if (g_keys->keyDown ['9'] == TRUE)						
		{
			currentcam[currentscene]=8;
		}
		if (g_keys->keyDown ['0'] == TRUE)						
		{
			currentcam[currentscene]=9;
		}

		if (g_keys->keyDown ['L'] == TRUE)						
		{
			mlighting= true;
		} 
		if (g_keys->keyDown ['K'] == TRUE)						
		{
			mlighting= false;
		}

		if (angle > 360){ angle=0;}
		else{ angle ++;}// (float)(milliseconds) / 60.0f;					// Update angle Based On The Timer

		//next+=milliseconds;											// Increase next Based On The Timer
		//frame++;//next/mpf;												// Calculate The Current Frame
		next+=milliseconds;											// Increase next Based On The Timer
		frame=next/mpf;	
		
		if (frame>=lastframe)										// Are We At Or Past The Last Frame?
		{
			frame=0;												// Reset The Frame Back To Zero (Start Of Video)
			next=0;													// Reset The Animation Timer (next)
		}
	}
}


int meshshow[1000];
void tmeshshow(void){
	for(unsigned int tmesh=0;tmesh<mesh_c;tmesh++){
		if (meshbeat[fx_mesh[tmesh]]==1){
			if (beat == 1){
				if (mfxc[fx_mesh[tmesh]] < (meshfxbeat[fx_mesh[tmesh]]+1)) mfxc[fx_mesh[tmesh]]++;
				else mfxc[fx_mesh[tmesh]]=0;
			}
			if (mfxc[fx_mesh[tmesh]] == mfx[tmesh]){
				meshshow[tmesh]=1;						
			}else{
				meshshow[tmesh]=0;
			}
			
		}else{
			meshshow[tmesh]=1;
		}
	}
}

void hackscreen(int screenId){


}

////////////////////////
////////////////////////
///FX AND SCENES
////////////////////////
// define all the scene vars

void thescene(int sc_type, int mycameraid){
	float rw = 600;
	int tstext=1;
	float myfft;
	int displaymesh;
	
	/// test lighting stuff
    
	/// this is main loop for displaying all tscript 3d objects and videos
	for(int scloop=0;scloop<scenecount;scloop++){
		if (scene[scloop]==1){	
		// this will change a wee bit
			for(int tmesh=0;tmesh<sc_meshc[scloop];tmesh++){
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0f,1.0f,1.0f);
				if(sc_onscreen[scloop][tmesh]==0){
					displaymesh = 0;
				}else{
				 displaymesh = serverid * mycameraid;
				}
				if(sc_onscreen[scloop][tmesh]==displaymesh){
					if (sc_fxonoff[scloop][sc_fx_mesh[scloop][tmesh]] == 1){
							glPushMatrix();
							glDepthMask(TRUE);
							glDepthRange(0.001,1);
							glEnable(GL_DEPTH_TEST);
							if (sc_cameralock[scloop][tmesh] == 1) glTranslatef(xtrans, ytrans, ztrans);
							if (sc_cameralockrot[scloop][tmesh] == 1){
								glRotatef(scenerotx,1.0f,0,0);
								glRotatef(sceneroty,0,1.0f,0);
								glRotatef(scenerotz,0,0,1.0f);
							}
							glBindTexture(GL_TEXTURE_2D, t_texture[tmesh]);
							if (sc_applyvideo[scloop][tmesh] == 1){
								// this where the mesh object gets wrapped with a video
								for(unsigned int vloop=0;vloop<20;vloop++){
									if(sc_fx_vid[scloop][sc_fx_mesh[scloop][tmesh]][vloop] == 1){
										if((vloop == feedtoslot) && (enablefeed==TRUE)){
											glBindTexture(GL_TEXTURE_2D, lftexture);
										}else if((vloop == sysaviId) && (sysavi == 1)){
											glBindTexture(GL_TEXTURE_2D, texture);
										}
										else{
											glBindTexture(GL_TEXTURE_2D, v_texture[vloop][v_current_frame[vloop]]);
										}
									}
									if(sc_mesh_vid[scloop][tmesh][vloop] == 1){
										if((vloop == feedtoslot) && (enablefeed==TRUE)){
											glBindTexture(GL_TEXTURE_2D, lftexture);
										}else if((vloop == sysaviId) && (sysavi == 1)){
											glBindTexture(GL_TEXTURE_2D, texture);
										}
										else{
											glBindTexture(GL_TEXTURE_2D, v_texture[vloop][v_current_frame[vloop]]);
										}
									}
									
								}
							}else{
								glBindTexture(GL_TEXTURE_2D, t_texture[sc_mesh_index[scloop][tmesh]]); 
							}
							//blendtype will go here
							if (sc_blendtype[scloop][tmesh]==0)glBlendFunc(GL_SRC_COLOR,GL_ONE);
							else if (sc_blendtype[scloop][tmesh]==1)glBlendFunc(GL_DST_COLOR,GL_ONE);
							else if (sc_blendtype[scloop][tmesh]==2)glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
							else if (sc_blendtype[scloop][tmesh]==3)glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_DST_ALPHA);
							else if (sc_blendtype[scloop][tmesh]==4)glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);
							else if (sc_blendtype[scloop][tmesh]==5)glBlendFunc(GL_SRC_ALPHA_SATURATE,GL_SRC_COLOR);
							else if (sc_blendtype[scloop][tmesh]==6)glBlendFunc(GL_SRC_ALPHA,GL_DST_COLOR);
							else if (sc_blendtype[scloop][tmesh]==7)glBlendFunc(GL_DST_ALPHA,GL_ONE);
							else if (sc_blendtype[scloop][tmesh]==8)glBlendFunc(GL_SRC_COLOR,GL_DST_ALPHA);
							else glBlendFunc(GL_SRC_ALPHA, GL_ONE);
							

							glTranslatef(sc_tposition[scloop][tmesh][0],sc_tposition[scloop][tmesh][1],sc_tposition[scloop][tmesh][2]);
							glTranslatef(sc_position[scloop][0],sc_position[scloop][1],sc_position[scloop][2]);
							
							glRotatef(sc_mrotate[scloop][tmesh][0], sc_mrotate[scloop][tmesh][1], sc_mrotate[scloop][tmesh][2], sc_mrotate[scloop][tmesh][3]);
							glRotatef(angle*sc_trotate[scloop][tmesh][0],sc_trotate[scloop][tmesh][1],sc_trotate[scloop][tmesh][2],sc_trotate[scloop][tmesh][3]);
							glRotatef(sc_rotation[scloop][0], sc_rotation[scloop][1], sc_rotation[scloop][2], sc_rotation[scloop][3]); 
							
							glScalef(sc_scale[scloop][tmesh][0], sc_scale[scloop][tmesh][1], sc_scale[scloop][tmesh][2]);

							if (sc_blend[scloop][tmesh] == 1){
								glEnable(GL_BLEND);
							}else{
								glDisable(GL_BLEND);
							}
							if (sc_meshfft[scloop][tmesh] > 0){
								myfft = fft[meshfft[tmesh]]/1.1;
								glScaled(myfft, myfft, myfft);
							}
							if (sc_beatscaled[scloop][tmesh] == 1){
								glScaled(sound, sound, sound);
							}
							

							if (sc_meshwire[scloop][tmesh] == 1){
								glDisable(GL_LIGHTING);
								glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
								glPolygonMode(GL_FRONT, GL_LINE);
								glPolygonMode(GL_BACK, GL_LINE);
								glDisable(GL_DEPTH_TEST);
							
							}else{
								if (bg){
									if (mlighting == true) glEnable(GL_LIGHTING);
									glPolygonMode(GL_FRONT, GL_FILL);
									glPolygonMode(GL_BACK, GL_FILL);
								}
								else {
								glDisable(GL_LIGHTING);
								}

							}
							if (sc_tcolor[scloop][tmesh][3] == 1){
								glColor3f(tcolor[tmesh][0], tcolor[tmesh][1], tcolor[tmesh][2]) ;
							}

							if (sc_tmeshtype[scloop][tmesh] == 1){
								
								if (sc_texttype[scloop][tmesh] == sc_type){
									glCallList(mesh_p[sc_mesh_index[scloop][tmesh]]);
										
								}
								
							}
							glDisable(GL_LIGHTING);
							if (sc_tmeshtype[scloop][tmesh] == 2){
								// we can do the nasty font stuff here
								if (sc_texttype[scloop][tmesh] == sc_type){
									if (sc_type==2)glDisable(GL_LIGHTING);
									glScalef(sc_textsize[scloop][tmesh], sc_textsize[scloop][tmesh], sc_textsize[scloop][tmesh]);
									char test[120] = "";
									// clear str test
									strncpy(test, sc_tekst[scloop] + sc_tekst_loc[scloop][tmesh][1], sc_tekst_loc[scloop][tmesh][0]);
									glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
									glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
									glEnable(GL_TEXTURE_GEN_S);
									glEnable(GL_TEXTURE_GEN_T);
									gl3dPrint(test, sc_textfont[scloop][tmesh]);
									glDisable(GL_TEXTURE_GEN_S);
									glDisable(GL_TEXTURE_GEN_T);
									
								}
							}

							if (sc_type != 2){
								if (sc_tmeshtype[scloop][tmesh] == 3){
									glDisable(GL_BLEND);
									
									for(int mstep=0;mstep<26;mstep++){
										for(int ss=18; ss>0; ss--){
										   os[ss][mstep] = os[ss - 1][mstep];
										   //glEnable(GL_BLEND);
										   //glDisable(GL_TEXTURE_2D);
										   // glBegin(GL_LINES);
										   // 	glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os[ss][mstep] * 100), ss * 20);					
										   //	glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os[ss][mstep + 1] * 100, (ss * 20));
										   //	glEnd();
											//
											glBegin(GL_LINES);
										    	glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os[ss][mstep] * 100), ss * 20);					
												glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os[ss][mstep] * 100, (ss * 20));
											glEnd();
											
											glBegin(GL_LINES);
										    	glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os[ss][mstep] * 100), ss * -20);					
												glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os[ss][mstep] * 100, (ss * -20));
											glEnd();

											glBegin(GL_LINES);
										    	glVertex3f((-mstep * (100 / 25) * (rw / 100)) - 150, (os[ss][mstep] * 100), ss * 20);					
												glVertex3f((((-mstep - 1) * (100 / 25)) * (rw / 100)) - 150, os[ss][mstep] * 100, (ss * 20));
											glEnd();
											
											glBegin(GL_LINES);
										    	glVertex3f((-mstep * (100 / 25) * (rw / 100)) - 150, (os[ss][mstep] * 100), ss * -20);					
												glVertex3f((((-mstep - 1) * (100 / 25)) * (rw / 100)) - 150, os[ss][mstep] * 100, (ss * -20));
											glEnd();


											//glDisable(GL_BLEND);
										}
										os[0][mstep] = fft[mstep];
									}
									//if (mlighting == true) glEnable(GL_LIGHTING);
								}
							}
				
							
							glColor3f(1.0f,1.0f,1.0f);
							
							glPopMatrix();
						}
							
					}
					glDisable(GL_TEXTURE_2D);
				//}
			}
		}
	}
	glDisable(GL_LIGHTING);

}

void callscenes(int cam, float t_fov){
	glMatrixMode(GL_MODELVIEW);	

	///disable all blending
	glDisable(GL_BLEND);
	glClear (GL_DEPTH_BUFFER_BIT);
	
	/// work around for the left behind buffers
	glLoadIdentity();
	glTranslatef (0.0f, 0.0f, -5001.00f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	glBegin(GL_QUADS);										
		// Front Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 53000.0*5,  43000.0*5, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-53000.0*5,  43000.0*5, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-53000.0*5, -43000.0*5, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 53000.0*5, -43000.0*5, 0.0);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f,1.0f,1.0f);

	rendermode();


	if (bg == true)														
	{
	glLoadIdentity();
	glBlendFunc(GL_SRC_COLOR,GL_ONE);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();
	glOrtho(0,640,0,480,-1,5000);						// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();	
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslated(0,0,1);
	glEnable(GL_BLEND);
	
	for(int scloop=0;scloop<scenecount;scloop++){
		if (scene[scloop]==1){
			for(int uloop=0;uloop<20;uloop++){
				if(sc_underlay[scloop][uloop] == 1){ 
					if((uloop == feedtoslot) && (enablefeed==TRUE)){
					glBindTexture(GL_TEXTURE_2D, lftexture);
					}else if((uloop == sysaviId) && (sysavi == 1)){
						glBindTexture(GL_TEXTURE_2D, texture);
					}
					else{
						glBindTexture(GL_TEXTURE_2D, v_texture[uloop][v_current_frame[uloop]]);
					}
					glCallList(overunder);
				}
			}
		}
	}
	glMatrixMode(GL_PROJECTION);		
	glPopMatrix();						
	glMatrixMode(GL_MODELVIEW);			
	glPopMatrix();
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);		

	}
	
	glLoadIdentity ();

	if (cam == 1){
		glRotatef(cam_rot[0][0],cam_rot[0][1],cam_rot[0][2],cam_rot[0][3]);
		glTranslatef(cam_pos[0][0],cam_pos[0][1],cam_pos[0][2]);
	}
	if (cam == 2){
		glRotatef(cam_rot[1][0],cam_rot[1][1],cam_rot[1][2],cam_rot[1][3]);
		glTranslatef(cam_pos[1][0],cam_pos[1][1],cam_pos[1][2]);
	}
	if (cam == 3){
		glRotatef(cam_rot[2][0],cam_rot[2][1],cam_rot[2][2],cam_rot[2][3]);
		glTranslatef(cam_pos[2][0],cam_pos[2][1],cam_pos[2][2]);
	}
	if (cam == 4){
		glRotatef(cam_rot[3][0],cam_rot[3][1],cam_rot[3][2],cam_rot[3][3]);
		glTranslatef(cam_pos[3][0],cam_pos[3][1],cam_pos[3][2]);
	}
	
	// call camera
	oko_camera();
	float LightPos1[] = { -xtrans, -ytrans, -ztrans, 1.0f};	
	float LightAmb1[] = { 0.5f, 0.5f, 0.5f, 1.0f};		// Ambient Light Values
	float LightDif1[] = { 1.0f, 1.0f, 1.0f, 1.0f};		// Diffuse Light Values
	float LightSpc1[] = {0.2f, 0.2f, 0.1f, 1.0f};		// Specular Light Values
	
	
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);		// Set Light1 Position
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb1);			// Set Light1 Ambience
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif1);			// Set Light1 Diffuse
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc1);		// Set Light1 Specular

	float MatEmi[] = {0,0,0,1};				// Material - Diffuse Values
    float MatSpc[] = {0.2,0.2,0.2,1};				// Material - Specular Values
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpc);		// Set Material Specular
	glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi);		// Set Material Shininess
	//glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT1);
	
	//glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
	//glEnable (GL_COLOR_MATERIAL ) ;
	//glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;


	// 3d scene
	thescene(1, cam);
	if (bg == true){
	glBlendFunc(GL_SRC_COLOR,GL_ONE);									
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);			
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();						
	glLoadIdentity();
	glOrtho(0,640,0,480,-1,5000);		
	glMatrixMode(GL_MODELVIEW);			
	glPushMatrix();	
	glLoadIdentity();					
	glTranslated(0,0,1);
	
	glEnable(GL_BLEND);
	for(int scloop=0;scloop<scenecount;scloop++){
		if (scene[scloop]==1){
			for(unsigned int oloop=0;oloop<20;oloop++){
				if(sc_overlay[currentscene][oloop] == 1){   
					if((oloop == feedtoslot) && (enablefeed==TRUE)){
						glBindTexture(GL_TEXTURE_2D, lftexture);
					}else if((oloop == sysaviId) && (sysavi == 1)){
						glBindTexture(GL_TEXTURE_2D, texture);
					}
					else{
						glBindTexture(GL_TEXTURE_2D, v_texture[oloop][v_current_frame[oloop]]);
					}
					//glCallList(overunder);
					
					if (oloop == 0){							
						if (superanamorphic == true){
						glBegin(GL_QUADS);										
						if (cam == 1){
							glTexCoord2f(0.25f, 1.0f); glVertex2d(640,480);
							glTexCoord2f(0.0f, 1.0f); glVertex2d(0,480);
							glTexCoord2f(0.0f, 0.0f); glVertex2d(0,0);
							glTexCoord2f(0.25f, 0.0f); glVertex2d(640,0);
						}
						if (cam == 2){
							glTexCoord2f(0.50f, 1.0f); glVertex2d(640,480);
							glTexCoord2f(0.25f, 1.0f); glVertex2d(0,480);
							glTexCoord2f(0.25f, 0.0f); glVertex2d(0,0);
							glTexCoord2f(0.50f, 0.0f); glVertex2d(640,0);
						}
						if (cam == 3){
							glTexCoord2f(0.75f, 1.0f); glVertex2d(640,480);
							glTexCoord2f(0.50f, 1.0f); glVertex2d(0,480);
							glTexCoord2f(0.50f, 0.0f); glVertex2d(0,0);
							glTexCoord2f(0.75f, 0.0f); glVertex2d(640,0);
						}
						if (cam == 4){
							glTexCoord2f(1.0f, 1.0f); glVertex2d(640,480);
							glTexCoord2f(0.75f, 1.0f); glVertex2d(0,480);
							glTexCoord2f(0.75f, 0.0f); glVertex2d(0,0);
							glTexCoord2f(1.0f, 0.0f); glVertex2d(640,0);
						}
							glEnd();
						}else{
							glCallList(overunder);
						}
					}else{
						glCallList(overunder);
					}
				}
			}
		}
	}
	
	


	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);		
	glDisable(GL_TEXTURE_2D);
}

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	char mes[200];
	
	glDisable(GL_BLEND);									
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();
	glOrtho(0,100,0,100,-500,500);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();			

	thescene(2, cam);



	if (infoshow==1){
		glPushMatrix();	
			glTranslated(5,5,0);
			glColor4f(1.0f,1.0f,1.0f,1.0f);	
			glScalef(5, 5, 5);	
			sprintf(mes,"ANGLE : %f",angle);
			gl3dPrint(mes, 0);
		glPopMatrix();
		
		glPushMatrix();	
			glTranslated(5,10,0);
			glColor4f(1.0f,1.0f,1.0f,1.0f);	
			glScalef(3, 3, 3);	
			sprintf(mes,"owner: %s",owner);
			gl3dPrint(mes, 0);
		glPopMatrix();

		glPushMatrix();	
			glTranslated(5,13,0);
			glColor4f(1.0f,1.0f,1.0f,1.0f);	
			glScalef(3, 3, 3);		
			sprintf(mes,"sound: %f",sound);
			gl3dPrint(mes, 0);
		glPopMatrix();

		glPushMatrix();	
			glTranslated(5,16,0);
			glColor4f(1.0f,1.0f,1.0f,1.0f);	
			glScalef(3, 3, 3);		
			sprintf(mes,"fov: %f",t_fov);
			gl3dPrint(mes, 0);
		glPopMatrix();
		
		glPushMatrix();	
			glTranslated(5,19,0);
			glColor3f(1.0f,1.0f,1.0f);	
			glScalef(3, 3, 3);		
			sprintf(mes,"tscript calls: %s",tmess);
			gl3dPrint(mes, 0);
		glPopMatrix();
		
		glPushMatrix();	
				glTranslated(5,22,0);
				glColor3f(1.0f,1.0f,1.0f);	
				glScalef(3, 3, 3);		
				sprintf(mes,"scene id: %d",currentscene);
				gl3dPrint(mes, 0);
		glPopMatrix();
	}
	
	if (loadingSystem){
		glPushMatrix();	
			glTranslated(5,5,0);
			glColor4f(1.0f,1.0f,1.0f,1.0f);	
			glScalef(5, 5, 5);	
			//sprintf(mes,"oko t : %s",appname);
			gl3dPrint("wait : live feed setup", 0);
		glPopMatrix();
	}

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();

	glColor3f(1.0f,1.0f,1.0f);	
}


void drawkeystone(){
	
	glLoadIdentity ();											// Reset The Projection Matrix
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();						
	glLoadIdentity();
	//gluPerspective(50, (GLfloat)(width)/(GLfloat)(height), 1, 5000 );
	glOrtho(0,100,0,100,-1,5000);		
	glMatrixMode(GL_MODELVIEW);			
	glPushMatrix();	
	glLoadIdentity();					
		
	
	/*glLoadIdentity ();											
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();						
	glLoadIdentity();
	
	//gluPerspective(50, (GLfloat)(width)/(GLfloat)(height), 1, 5000 );
	glOrtho(0,640,0,480,-1,5000);		
	
	glMatrixMode(GL_MODELVIEW);			
	glPushMatrix();	
	glLoadIdentity();					
	*/

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,KeyTexture);
	glColor3f(1.0f,1.0f,1.0f);	
	glTranslated(0,0,-4);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	
	glTranslated(0,0,-50);
	//glCallList(Keystoned);

		int cc=0;
		for(float yp=1; yp<ycoordz; yp++){
			if ( yp == ycoordz)break;
			for(float xp=0; xp<xcoordz; xp++){
				if (xp != xcoordz-1){
				glBegin(GL_QUADS);										
					glTexCoord2f(((xp+1) / (((float)xcoordz-1)/100))/100, 1-(((yp-1) / (((float)ycoordz-1)/100))/100)); 
					//glTexCoord2f(1,1);
					glVertex2f(coordz[cc+1][0],coordz[cc+1][1]);
					
					glTexCoord2f((xp / (((float)xcoordz-1)/100))/100, 1-(((yp-1) / (((float)ycoordz-1)/100))/100));
					//glTexCoord2f(0,1);
					glVertex2f(coordz[cc][0],coordz[cc][1]);
					
					glTexCoord2f((xp / (((float)xcoordz-1)/100))/100, (100 - (yp / (((float)ycoordz-1)/100)))/100);
				//	glTexCoord2f(0,0);
					glVertex2f(coordz[cc+(int)xcoordz][0],coordz[cc+(int)xcoordz][1]);
					
					glTexCoord2f(((xp+1) / (((float)xcoordz-1)/100))/100, (100 - (yp / (((float)ycoordz-1)/100)))/100);
					//glTexCoord2f(1,0);
					glVertex2f(coordz[cc+(int)xcoordz+1][0],coordz[cc+(int)xcoordz+1][1]);
				
				glEnd();
				}
			cc++;
			}
		}
		
	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();										
	glMatrixMode(GL_MODELVIEW);							
	glPopMatrix();

}

///////////////////////
//////////////////////
void drawgl(void){
	frametotexture();
	if (sysavi==1){
		GrabAVIFrame(frame);
	}
		// Clear Screen And Depth Buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	RECT	rect;														// Holds Coordinates Of A Rectangle

	GetClientRect(g_window->hWnd, &rect);								// Get Window Dimensions
	int window_width=rect.right-rect.left;								// Calculate The Width (Right Side-Left Side)
	int window_height=rect.bottom-rect.top;								// Calculate The Height (Bottom-Top)
	
	loadvideolib();
	
	int num_scr=0;
	
	// test for texture loading
	// audio engine
	// get the audio data and setup the beat engine
	BASS_ChannelGetData(RECORDCHAN,fft,BASS_DATA_FFT2048);
	
	
	if (beatdetect == 1){
		beat=0;
		for(int bc=beatleft; bc <= beatright; bc++){
			if (fft[bc] >= beatclip){
				beat=1;
			}
		}
	}else{
		sound = ((fft[5] + fft[7] + fft[10] + fft[12] + fft[15] + fft[17] + fft[20] + fft[22]) / 8);
		if (sound > slevel){
			beat=1;
		}else{
			beat=0;
		}
	}

	// 
	tmeshshow();
	if (bitblast){
		HWND hTempWnd = GetDesktopWindow(); 
		HDC dsDC = GetWindowDC(hTempWnd);
		HDC myDC = GetWindowDC(g_window->hWnd);
	//	int num_scr=0;
		if (num_scr<screens){
			BitBlt (dsDC, 800, 0, 800, 600, myDC, 0, 0, SRCCOPY);
			num_scr++;
		}
		if (num_scr<screens){
			BitBlt (dsDC, 1920, 0, 640, 480, myDC, 640, 0, SRCCOPY);
			num_scr++;
		}
		if (num_scr<screens){
			BitBlt (dsDC, 1280, 480, 640, 480, myDC, 0, 480, SRCCOPY);
			num_scr++;
		}
		if (num_scr<screens){
			BitBlt (dsDC, 1920, 480, 640, 480, myDC, 640, 480, SRCCOPY);
		}
		num_scr=0;
		ReleaseDC(hTempWnd, dsDC);
		ReleaseDC(g_window->hWnd, myDC);
	}



	if (num_scr<screens){
		if (dynakey){
			glViewport(0,0,512,512);
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			gluPerspective( fov[0], (GLfloat)(width)/(GLfloat)(height), 1, 5000 );
			callscenes(1, fov[0]);
			glBindTexture(GL_TEXTURE_2D,KeyTexture);					
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB4, 0, 0, 512, 512, 0);
			glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Medium Blue
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And Depth Buffer
		}
		if (screens==1){
			glViewport (0, 0, window_width, window_height);
		}else if(dualdesk==1){
			glViewport (0, 0, window_width/2, window_height);
		}else{
			glViewport (0, window_height/2, window_width/2, window_height/2);
		}
		if (dynakey){
			drawkeystone();
		}else{
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			gluPerspective( fov[0], (GLfloat)(width)/(GLfloat)(height), 1, 5000 );
			if (screenhack[0] == 1){
				callscenes(1, fov[0]);
			}
		}
	num_scr++;
	}

	if (num_scr<screens){
		if(dualdesk==1){
			glViewport (window_width/2, 0, window_width/2, window_height);
		}else{
			glViewport (window_width/2, window_height/2, window_width/2, window_height/2);
		}
	glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
	glLoadIdentity ();											// Reset The Projection Matrix
	gluPerspective(fov[1], (GLfloat)(width)/(GLfloat)(height), 1, 5000.0 ); 
	if (screenhack[1] == 1){
		callscenes(2, fov[1]);
	}
	num_scr++;
	}
	
	if (num_scr<screens){
		glViewport (0, 0, window_width/2, window_height/2);
		glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
		glLoadIdentity ();											// Reset The Projection Matrix
		gluPerspective( fov[2], (GLfloat)(width)/(GLfloat)(height), 1, 5000.0 ); 
	if (screenhack[2] == 1){
		callscenes(3, fov[2]);
	}
		num_scr++;
	}

	if (num_scr<screens){
		glViewport (window_width/2, 0, window_width/2, window_height/2);
		glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
		glLoadIdentity ();											// Reset The Projection Matrix
		gluPerspective( fov[3], (GLfloat)(width)/(GLfloat)(height), 1, 5000 ); 
	if (screenhack[3] == 1){
		callscenes(4, fov[3]);
	}
		num_scr++;
	}

	if (newblast){
		pixbi.biSize = sizeof (BITMAPINFOHEADER);					
		pixbi.biPlanes = 1;											
		pixbi.biBitCount = 24;										
		pixbi.biWidth = 640;											
		pixbi.biHeight = 480;										
		pixbi.biCompression = BI_RGB;
		pixbi.biSizeImage = 640*480*3;
		HWND hTempWnd = GetDesktopWindow(); 
		HDC dsDC = GetWindowDC(hTempWnd);
		pixhdd = DrawDibOpen();
		unsigned char* pixdata;
		pixdata = new unsigned char [640*480*3];
			glReadPixels(640, 480, 640, 480, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixdata);
			DrawDibDraw (pixhdd, dsDC, 1920, 0, 640, 480, &pixbi, pixdata, 0, 0, pixbi.biWidth, pixbi.biHeight, 0);
			glReadPixels(0, 480, 640, 480, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixdata);
			DrawDibDraw (pixhdd, dsDC, 1280, 0, 640, 480, &pixbi, pixdata, 0, 0, pixbi.biWidth, pixbi.biHeight, 0);
		
		//	glReadPixels(640, 0, 640, 480, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixdata);
		//	DrawDibDraw (pixhdd, dsDC, 1920, 480, 640, 480, &pixbi, pixdata, 0, 0, pixbi.biWidth, pixbi.biHeight, 0);
		//	glReadPixels(0, 0, 640, 480, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixdata);
		//	DrawDibDraw (pixhdd, dsDC, 1280, 480, 640, 480, &pixbi, pixdata, 0, 0, pixbi.biWidth, pixbi.biHeight, 0);
		
		delete pixdata;
		ReleaseDC(hTempWnd, dsDC);
		DrawDibClose(pixhdd);
	}
  glFlush ();	
	// push all the video frames forward 1
	
		setframe();
	
}
void Draw (void)												// Draw Our Scene
{
	
	if (multiserver){
		if (tframe == 1){
			drawgl();
			tframe=0;
			fcount++;
			angle ++;
			frame++;
		}
	}else{
		drawgl();
	}

}


////////////////////////////////
////////////////////////////////
/////// socket interpretor
///////////////////////////////
///////////////////////////////

void interpretsocket(char buffy[5012]){
//like the tscript parser we interpret the socket data
// we ignore all other shit
	char *t_obj;
	char *test;
	int testa[10];
	float testf[10];
	char seps[] = "()";
	char sepz[] = "{}";
	sprintf(tmess, "%s", buffy);
	t_obj = strstr(buffy, "frame[" );
	if(t_obj != NULL){
		// ok this is a frame
		tframe=1;
	}

	t_obj = strstr(buffy, "connect(" );
	if(t_obj != NULL){
		t_connect=1;			
	}

	t_obj = strstr(buffy, "scene(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		sceneswitch(testa[0]);
	}
	
	t_obj = strstr(buffy, "scenefocus(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setcurrentscene(testa[0]);
	}

	t_obj = strstr(buffy, "scenecreate(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		test = strtok( NULL, seps );
		setcreatescene(testa[0], test);
	}
	
	t_obj = strstr(buffy, "sceneaddfx(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setaddfxscene(testa[0]);
	}
	
	t_obj = strstr(buffy, "scenedeletefx(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setdeletefxscene(testa[0]);
	}
	t_obj = strstr(buffy, "sceneposition(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%f %f %f", &testf[0], &testf[1], &testf[2]);
		setsceneposition(testf[0], testf[1], testf[2]);
	}
	t_obj = strstr(buffy, "scenerotation(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%f %f %f %f", &testf[0], &testf[1], &testf[2], &testf[3]);
		setscenerotation(testf[0], testf[1], testf[2], testf[3]);
	}



	t_obj = strstr(buffy, "effect(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		fxswitch(testa[0]);
	}
	//load video
	t_obj = strstr(buffy, "loadvid(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		loadvidlib(testa[0],testa[1]);
	}
	// delete video
	t_obj = strstr(buffy, "deletevid(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		deletevidlib(testa[0], testa[1]);
	}
	// overlay on off
	t_obj = strstr(buffy, "overlay(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		overlayon(testa[0]);
		resetframe(testa[0]);
	}
	// underlay on off
	t_obj = strstr(buffy, "underlay(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		underlayon(testa[0]);
		resetframe(testa[0]);
	}
	// set video to effect
	t_obj = strstr(buffy, "vidtofx(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		setvidtoeffect(testa[0],testa[1]);
	}
	t_obj = strstr(buffy, "vidtomesh(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		setvidtomesh(testa[0],testa[1]);
	}
	// set camera
	t_obj = strstr(buffy, "camera(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d ", &testa[0]);
		setcamera(testa[0]);
	}
	// render mode wireframe etc
	t_obj = strstr(buffy, "render(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d ", &testa[0]);
		setrender(testa[0]);
	}
	// reset frame
	t_obj = strstr(buffy, "resetframe(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d ", &testa[0]);
		resetframe(testa[0]);;
	}
	// pingpong
	t_obj = strstr(buffy, "pingpong(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		setpingpong(testa[0], testa[1]);
	}

	t_obj = strstr(buffy, "beatdetect(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%f %d %d", &testf[0], &testa[0], &testa[1]);
		beatdetection(testf[0], testa[0], testa[1]);
	}
	t_obj = strstr(buffy, "text(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		test = strtok( NULL, seps );
		replacetext(testa[0], test);
	
	}
	//textsize(MeshID size)
	t_obj = strstr(buffy, "textsize(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %f", &testa[0], &testf[0]);
		settextsize(testa[0], testf[0]);
	}
	t_obj = strstr(buffy, "font(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		setfont(testa[0], testa[1]);
	}
	t_obj = strstr(buffy, "colour(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %f %f %f", &testa[0], &testf[0], &testf[1], &testf[2]);
		settcolor(testa[0], testf[0], testf[1], testf[2]);
	}
	
	//blend(MeshID)
	
	t_obj = strstr(buffy, "blend(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
	//	tscripterror(test);
		test = strtok( NULL, seps );
	//	tscripterror(test);
		sscanf(test, "%d", &testa[0]);
		setblend(testa[0]);
	}
	
	// blendtype(meshId blendtype)
	t_obj = strstr(buffy, "blendtype(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		setblendtype(testa[0], testa[1]);
	}

	t_obj = strstr(buffy, "onscreen(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %d", &testa[0], &testa[1]);
		setonscreen(testa[0], testa[1]);
	}

	//beatscale(meshID)
	t_obj = strstr(buffy, "beatscale(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setbeatscale(testa[0]);
	}
	
	//videomapped(meshID)
	t_obj = strstr(buffy, "videomapped(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setvidmap(testa[0]);
	}
	
	//forewireframe(meshID)
	t_obj = strstr(buffy, "forcewireframe(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setwireframe(testa[0]);
	}
	//meshpostion(MeshId X Y Z) 
	t_obj = strstr(buffy, "meshposition(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %f %f %f", &testa[0], &testf[0], &testf[1], &testf[2]);
		setposition(testa[0], testf[0], testf[1], testf[2]);
	}
	t_obj = strstr(buffy, "meshscale(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %f %f %f", &testa[0], &testf[0], &testf[1], &testf[2]);
		setmeshscale(testa[0], testf[0], testf[1], testf[2]);
	}
	
	//meshrotation(MeshId Speed X Y Z) 
	t_obj = strstr(buffy, "meshrotation(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %f %f %f %f", &testa[0], &testf[0], &testf[1], &testf[2], &testf[3]);
		setrotation(testa[0], testf[0], testf[1], testf[2], testf[3]);
	}
	// camerabeat()
	t_obj = strstr(buffy, "camerabeat(" );
	if( t_obj != NULL )	{
		camerabeat();
	}


	// meshrotate(MeshId ANGLE X Y Z) 
	t_obj = strstr(buffy, "meshrotate(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d %f %f %f %f", &testa[0], &testf[0], &testf[1], &testf[2], &testf[3]);
		setmrotate(testa[0], testf[0], testf[1], testf[2], testf[3]);
		MessageBox(g_window->hWnd, "buffy", "keystone", MB_OK | MB_ICONEXCLAMATION) ;
	}
	t_obj = strstr(buffy, "rotatecamera(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%f %f %f %f",  &testf[0], &testf[1], &testf[2], &testf[3]);
		setcamerarotation(testf[0], testf[1], testf[2], testf[3]);

	}

	t_obj = strstr(buffy, "positioncamera(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%f %f %f", &testf[0], &testf[1], &testf[2]);
		setcameraposition(testf[0], testf[1], testf[2]);
	}

	t_obj = strstr(buffy, "meshbeat(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setmeshbeat(testa[0]);
		
	}
	// 
	t_obj = strstr(buffy, "beatmode()" );
	if( t_obj != NULL )	{
		setbeatmode();
	}

	t_obj = strstr(buffy, "loadfeed(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setfeedtovidslot(testa[0]);
		
	}

	t_obj = strstr(buffy, "sysavi(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		test = strtok( NULL, seps );
		setsysavi(testa[0], test);
	}


	t_obj = strstr(buffy, "locktocamerapos(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setlocktocamerapos(testa[0]);
	}

	t_obj = strstr(buffy, "locktocamerarot(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		sscanf(test, "%d", &testa[0]);
		setlocktocamerarot(testa[0]);
	}

	t_obj = strstr(buffy, "info(" );
	if( t_obj != NULL )	{
		showinfo();
	}

///////////////////////
/// 2.5 functions
/// 
///////////////////////
	t_obj = strstr(buffy, "keystone(" );
	if( t_obj != NULL )	{
		test = strtok( buffy, seps );
		test = strtok( NULL, seps );
		//MessageBox(g_window->hWnd, "buffy", "keystone", MB_OK | MB_ICONEXCLAMATION) ;
		
		setkeystone(test);
		
	}
}


//////////////////////////////
//////////////////////////////
////// socket server this will be heavily modified
//////////////////////////////
//////////////////////////////
unsigned __stdcall Interpretor(void *pvoid){
	interpretsocket((char*)pvoid);
	return 0;
}

unsigned __stdcall ClientThread(void *pVoid)
{
	int rVal;
	char buffer[5012];
	char *mybuff;
	char *t_obj;
	char *test;
	unsigned	ThreadAddr;
	DWORD		dwClientThread;
	char seps[] = ";";
	SOCKET mSocket = (SOCKET)pVoid;
	while(true){
	rVal = recv(mSocket, buffer, 5012, 0);
		
	if(rVal==SOCKET_ERROR ){	
		break;
	}else{
		t_obj = strstr(buffer, "group->" );
		if( t_obj != NULL )	{
		
		test = strtok( buffer, seps );
			while( test != NULL )
			{
		 		dwClientThread = _beginthreadex(NULL, 0, Interpretor, (void*)test,  0, &ThreadAddr);
				test = strtok( NULL, seps );
			}

		}	else{
			interpretsocket(buffer);
		}
	}
	char memtemp[12];
	t_obj = strstr(buffer, "frame[" );
	if( t_obj != NULL )	{
			sprintf(memtemp, "frame [ %d ]", fcount);
			send(mSocket, memtemp, strlen(memtemp),0);	
	}else{
		if (vidloaded == 1){
			mybuff = "vidloaded";
			send(mSocket, mybuff, strlen(mybuff),0);
			vidloaded = 0;
		}else{
			MEMORYSTATUS  m;
			GlobalMemoryStatus(&m);
			sprintf(memtemp,"%d %d ", (100-(m.dwAvailPhys/(m.dwTotalPhys/100))), (100-(m.dwAvailVirtual/(m.dwTotalVirtual/100))));
			send(mSocket, memtemp, strlen(memtemp),0);
		}
	}
	
	}
	closesocket(mSocket);
	return 0;
}


void socketThread( void *dummy )
{
    	
    //cout << "Starting up TCP server\r\n";
    beginagain:	
 
	SOCKET server;
    WSADATA wsaData;
    sockaddr_in local;
    int wsaret=WSAStartup(0x101,&wsaData);
    if(wsaret!=0)
    {
       // return 0;
    }

    local.sin_family=AF_INET; //Address family
    local.sin_addr.s_addr=INADDR_ANY; //Wild card IP address
    local.sin_port=htons((u_short)1009); //port to use
    server=socket(AF_INET,SOCK_STREAM,0);

    if(server==INVALID_SOCKET)
    {
        //return 0;
    }
 
    if(bind(server,(sockaddr*)&local,sizeof(local))!=0)
    {
        //return 0;
    }

    if(listen(server,SOMAXCONN)!=0)
    {
       // return 0;
    }

    SOCKET		socketClient;
	unsigned	ThreadAddr;
	DWORD		dwClientThread;
	SOCKADDR_IN	SockAddr;
	int			nLen;

	while(true)//we are looping endlessly
    {
     	nLen = sizeof(SOCKADDR_IN);
		socketClient = accept(server, (LPSOCKADDR)&SockAddr, &nLen);
		dwClientThread = _beginthreadex(NULL, 0, ClientThread, (void*)socketClient,  0, &ThreadAddr);
	}
	
    closesocket(server);
    WSACleanup();
	goto beginagain;
}


