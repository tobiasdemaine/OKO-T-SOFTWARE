#include "oko-t.h"

int        thr_id;   
int        thr_vid; 
int 	   thr_vid0; 
pthread_t  p_thread;

pthread_t  v_thread;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

pthread_t  v0_thread;
pthread_cond_t v0cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t v0mut = PTHREAD_MUTEX_INITIALIZER;

GLWindow GLWin;

int frame= 0;
int msec;
int width;                      // width and height of video stream
int height;
double stream_fps = 0;  // fps (for playback, since we don't use avi player)
avm::IReadStream *avistream = 0;  // represents the avi stream
StreamInfo *streaminfo = 0;       // represents the avi streaminfo
CImage *image = 0;                // an image (provided by avifile)
CImage* v0rgb;
int v0t=0;

int frame1= 0;
int msec1;
int width1;                      // width and height of video stream
int height1;
double stream_fps1 = 0;          // fps (for playback, since we don't use avi player)
avm::IReadStream *avistream1 = 0;  // represents the avi stream
StreamInfo *streaminfo1 = 0;       // represents the avi streaminfo
CImage *image1 = 0;                // an image (provided by avifile)

int bank0avi;
int bank0openavi;
int bank1avi;
int bank1openavi;

/*audio*/
short int audiobuf[2048];
short int fftdata[10000];
short int newfft[1024];
float sound=0;
int beat;

/*constants*/
const float piover180 = 0.0174532925f;

/*aspect ratio and screens*/
float aspectwidth = 720;
float aspectheight = 576;
int screens=1; // default is single screen
int dualdesk=0; // used for two windows on each output of AGP card
int fov[4]; //default field of view
int screen_width; // these are the defaults
int screen_height; // these are the defaults
int windowed;
int windowstylez;

/*Effects in structs create spazmodic segmentation faults during display phase: WHY???????????????
// this would a better way to handle effects rather than using horrible globals.
typedef struct{
	int  type;
	char text[255];
	int  texttype;
	int  size;
	int  font;
	int  attachedavi;
	int  feed;
	float  position[3];
	float  rotation[4];
	int  blend;
	float  color[4];
	int  fft;
	int  beatscaled;
	int  cameralock;
	int  islit;
	int  meshwire;
	int  applyvideo;
	GLuint	t_texture;
	L3DS scene;  //I am sure the seg faults come from here
	IAviReadFile* avi_file; // and here
} okoObject;

typedef struct{
	char name[255];
	int  objCount;
	int  onoff;
	okoObject object[100];
} okofx;

okofx fx[200];
*/

/*video*/
IAviReadFile* avi_file[1000];    

/*3ds files*/
L3DS scene[1000];
LMap diffuse[1000];
LMap specular[1000];

GLuint  overunder; ////////

GLuint	mesh;
GLuint	mesh_p[1000];
GLuint  mesh_c=0;

int meshonce[1000];
int fx_mesh[1000];
int fxonoff[1000];
int effectC=0;
int beatscaled[1000];
int tblend[1000];
int applyvideo[1000];
int meshwire[1000];
float tposition[1000][3];
float trotate[1000][4];
int cameralock[1000];
int meshfft[1000];
int meshbeat[1000]; /////////
int tmeshtype[1000];
float tcolor[1000][4];//
int mfxc[1000];
int mfx[1000];
int islit[1000];
int attachedavi[1000]; //
int feed[1000];


typedef struct{
	char string[255];
	char *fontpath;
	char type;
	char size;
}tekst;
tekst objtext[1000];
FTFont* fonts[1000];
FTFont* loadingfont;

int lc=0;
typedef struct{
	char thetext[255];
} lscreentext;
lscreentext ltext[1000];

bool bg=True;
float angle;
int txc=0;
int axc=0;
int vision=0;

int bank0; //switches for effect banks
int bank1; //switches for effect banks

/* texture pointers and counters*/
GLuint	texttexture[100];
GLuint	vidtexture0;
GLuint	vidtexture1;
GLuint	t_texture[1000];
///GLuint	v_texture[20][2280];
GLuint	KeyTexture;
GLuint	bootscreen;
GLuint	livefeed;
int t_textureC=0;

/* camera */
int currentcam=0;
int cambeat=0;
GLfloat updown;
GLfloat dblAngle1;
GLfloat dblAngle2;
GLfloat xtrans;
GLfloat ztrans;
GLfloat ytrans;
GLfloat sceneroty;
float cup = 1;
float cdist = 1;
float heading;
float xpos;
float zpos;
float ypos;
GLfloat	yrot;
GLfloat lookupdown = 0.0f;
GLfloat	z=0.0f;		
float cam_pos[4][3];
float cam_rot[4][4];

float os4[26][26];

/*rendering*/
int rmode=0;

/*timer*/
static struct timeval tnew;
static struct timeval told;
static struct timezone tz;
float timedifference;
int framenum=0;
float fps=0;
float Rfps=0;

/*video grabber*/
int 	fd = -1;
char 	*map;
struct 	video_mmap my_buf;
struct	video_capability  capability;
struct video_mbuf vid_buf;
struct video_channel vid_chnl;
struct video_picture vid_pict;
struct video_window vid_win;
char *feedbuf;
int mmaped; 
int mbufsize;

int yesframe=0;
int getyesframe=0;


int setuppbuffer(char **msg, int width, int height);
void destroypbuffer(void);
void showbootscreen(char* infotext);

/*///////////////////////LIVE VIDEO FEED//////////////////////////////*/

void initvideo4linux(void* a){
   char my_video_dev[100]  = "/dev/video";
   
   if (-1 == (fd = open(my_video_dev, O_RDWR))) {
	printf("Error opening device: %s\n", my_video_dev);
   }
   
   if (-1 == ioctl(fd,VIDIOCGCAP,&capability)) {
	printf("Error: ioctl(fd,VIDIOCGCAP,&capability)\n");
   }
   fcntl(fd,F_SETFD,FD_CLOEXEC);
   //printf("video channels : %d\n", capability.channels);
   for (int i = 0; i < capability.channels; i++) {
	    vid_chnl.channel = i;
	    if (ioctl(fd, VIDIOCGCHAN, &vid_chnl) == -1) {
		printf("ioctl (VIDIOCGCHAN)");
	    }
	    printf("The name of input channel #%d is \"%s\".\n", i, vid_chnl.name);
   }
   
   printf("Total %d input channel(s). Using channel #%d.\n", capability.channels, 2);
   printf("Supported resolution range: %dx%d => %dx%d\n", capability.minwidth, capability.minheight, capability.maxwidth, capability.maxheight);
    
   
   if (ioctl(fd, VIDIOCGPICT, &vid_pict) == -1) {
	printf("ioctl (VIDIOCGPICT)");
   }
   
   vid_pict.palette = VIDEO_PALETTE_RGB24;
   printf("brightness : %d\n", vid_pict.brightness);
   printf("contrast : %d\n", vid_pict.contrast);
   printf("palette : %d\n", vid_pict.palette);
   
   if (ioctl(fd, VIDIOCGPICT, &vid_pict) == -1) {
	printf("ioctl (VIDIOCGPICT)");
   }
   
   vid_chnl.channel = 1;
   vid_chnl.norm = 0;
   if (ioctl(fd, VIDIOCGCHAN, &vid_chnl) == -1) {
	printf("ioctl (VIDIOCGCHAN)");
   }
   
   my_buf.width = 640;
   my_buf.height = 480;
   my_buf.format = VIDEO_PALETTE_RGB24;
        
   if (ioctl(fd, VIDIOCGMBUF, &vid_buf) == -1) {
	printf("No mmap support, Use read instead.\n");
	//myvid->mmaped = 0;
	if (ioctl(fd, VIDIOCGWIN, &vid_win) != -1) {
	    vid_win.width = 640;
	    vid_win.height = 480;
	    if (ioctl(fd, VIDIOCSWIN, &vid_win) == -1) {
		printf("ioctl (VIDIOCSWIN)");
	    }
	}
    }
    else {
    	
	printf("Using mmap to capture.\n");
	mmaped = 1;
	mbufsize = vid_buf.size;
    }
   
    int forever=1;

    while(forever){
        yesframe=0;
	getyesframe=0;
	munmap(map, mbufsize);
	map =  (char *)mmap(0, mbufsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ((unsigned char *) -1 == (unsigned char *) map) {
	    perror("mmap()");
	}

	my_buf.format =  VIDEO_PALETTE_RGB24;
	my_buf.frame = 0;
	my_buf.width = 320;
	my_buf.height = 240;
	if (ioctl(fd, VIDIOCMCAPTURE, &my_buf) == -1) {
	    perror("VIDIOCMCAPTURE");
	    munmap(map, mbufsize);
	}
	if (ioctl(fd, VIDIOCSYNC, &my_buf) == -1) {
	    perror("VIDIOCSYNC");
	    munmap(map, mbufsize);
	}
	
	getyesframe=1;
	pthread_cond_wait(&cond, &mut);
	 
     
     }
   
}



void v4linux_grabframes(int meshid){
	if (fx_mesh[meshid] < 100){
	width = my_buf.width;
	height = my_buf.height;
	}else{
	width1 = my_buf.width;
	height1 = my_buf.height;
	}
	
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, livefeed);  
	if (getyesframe==1){
	
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, my_buf.width, my_buf.height, 0,  GL_BGR, GL_UNSIGNED_BYTE, map);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_YCBCR_MESA, my_buf.width, my_buf.height, 0, GL_YCBCR_MESA, GL_UNSIGNED_SHORT_8_8_MESA, map); 
	// a shame that Nvidia GL driver does not support YUV TEXTURES. we would have wikkedly fast live video then!
	
	pthread_cond_broadcast(&cond);
	}
	
}

/*////////////////////////////////////TIMER/////////////////////////////////////////////////////////*/
void gettime(){
	timedifference=(float)(tnew.tv_sec-told.tv_sec)+(float)(tnew.tv_usec-told.tv_usec)/1000000;
	if ((framenum % 4)==0) {
	gettimeofday(&tnew,&tz);
	timedifference=(float)(tnew.tv_sec-told.tv_sec)+(float)(tnew.tv_usec-told.tv_usec)/1000000;
	told=tnew;
	fps = 4/timedifference;
	framenum=1;
	}
	framenum++;
}

float tickz(float tick){
	float retick;
	retick = tick*(timedifference*10);
	if (retick > 8000.00){
		retick = 0.0;
	}
	return retick;
}

/*/////////////////////////////////AUDIO THREAD////////////////////////////////////////////////////////////////////////////////////////////*/
//
snd_pcm_t *pcm_handle;
snd_pcm_hw_params_t *params;
#define FREQ_SAMPLES 8192

int db2sy( float db )
{
  return (int)( ( db - 10.0 ) / ( 110.0 ) * (float)(256) );
}

inline float sqr( float arg )
{
  return arg * arg;
}
float value_e[8192];
void envelope(float alphaValue)
{
  // normalised to 1
  
  float sum = 0.0;
  for( int i = 0; i < FREQ_SAMPLES; i++ ) {
    float x = (float)( i - FREQ_SAMPLES/2 ) / FREQ_SAMPLES;
    value_e[i] = exp( - alphaValue * sqr( x ) );
    sum += value_e[i];
  }
  sum /= FREQ_SAMPLES;
  
  for( int i = 0; i < FREQ_SAMPLES; i++ )
    value_e[i] /= sum;
}

// this all very FUDGED i am not very good at DSP. BUT IT WORKS a lot better than 3DLAVINS DID!!!!!!!
void audiothread(void* a){ 	
	int chunk_size;
	size_t chunk_bytes;
	snd_pcm_open( &pcm_handle,"default", SND_PCM_STREAM_CAPTURE, 0);
	snd_pcm_hw_params_alloca( &params);
	snd_pcm_hw_params_any( pcm_handle, params);
	snd_pcm_hw_params_set_access( pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format( pcm_handle, params, SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_rate_near( pcm_handle, params, 44100, 0);
	snd_pcm_hw_params_set_channels( pcm_handle, params, 2);
	snd_pcm_hw_params( pcm_handle, params);
	
	chunk_size = snd_pcm_hw_params_get_period_size(params, 0);
	chunk_bytes = chunk_size *4;
	snd_pcm_prepare (pcm_handle);
	int stop=1;
		
	envelope(-1);	
	    	
	float freqInBuffer[10000];
	float value_db[8192];
	
	int num_fft = 8192/2+1;
	float norm = - 27.1;

	while(stop==1){
		int freqCpt=0;
		snd_pcm_readi(pcm_handle, audiobuf, 1024); 
		int i;
		for(i=0;i<num_fft;i++){
  			freqInBuffer[freqCpt] = value_e[freqCpt++]*((float)audiobuf[i++]+(float)audiobuf[i++])/(float)2/norm;
			//freqInBuffer[i] = ((float)audiobuf[i++]+(float)audiobuf[i++])/(float)2/norm;
		}
		
		rfft(freqInBuffer, FREQ_SAMPLES, 1);      
				
		for( int i = 0; i < num_fft; i++ ){
		
			float db, p;
			
			if( i != 0 && i != num_fft - 1 )
				p = sqr( freqInBuffer[2*i+0] ) + sqr( freqInBuffer[2*i+1] );
			else 
				p = sqr( freqInBuffer[ i == 0 ? 0 : 1 ] );
			
			db = 10.0 * log10( p ) + norm; // gauge ( 990.5273 Hz, 0 dB )	  	
			value_db[i] = db;
			
			fftdata[i] = db2sy( value_db[i] );	  
			if (fftdata[i] < 0){
				fftdata[i]=0;
			}
			
	    	}
		
		
	}
}






/*///////////////////////////////////////HELPERS/////////////////////////////////////////////////////////////////////////////////////*/
void settcolor(int mId, float tR, float tG, float tB){
	tcolor[mId][0]=(tR/2.56)/100;
	tcolor[mId][1]=(tG/2.56)/100;
	tcolor[mId][2]=(tB/2.56)/100;
	tcolor[mId][3]=1;
}
	
/*///////////////////////////////////MESH LOADERS, CONFIG LOADERS AND TEXTURE ALLOCATORS//////////////////////////////////////////////////////////////////*/
/* config file loader 1 */
void rereadstr(FILE *f,char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}

void loadconf (int part){
	FILE *filein;
	char oneline[255];
	printf("LOADING: lib/config.okot\n");
	if ((filein=fopen ("lib/config.okot", "rb"))== NULL) {
		
	}else{
	
	while( !feof( filein ) ){   
	
	if (part == 0){
		rereadstr(filein,oneline);
		sscanf(oneline, "width= %d", &screen_width);
		sscanf(oneline, "height=%d", &screen_height);
		sscanf(oneline, "fullscreen= %d\n", &windowed);
		sscanf(oneline, "windowframe= %d\n", &windowstylez);
	}else{
		rereadstr(filein,oneline);
		sscanf(oneline, "screens= %d\n", &screens);
		//sscanf(oneline, "serverid= %d\n", &serverid);
		sscanf(oneline, "dualdesktop= %d\n", &dualdesk);
		sscanf(oneline, "camera1_pos= %f %f %f", &cam_pos[0][0], &cam_pos[0][1], &cam_pos[0][2]);
		sscanf(oneline, "camera1_rot= %f %f %f %f", &cam_rot[0][0], &cam_rot[0][1], &cam_rot[0][2], &cam_rot[0][3]);
		sscanf(oneline, "camera1_fov= %f", &fov[0]);
		sscanf(oneline, "camera2_pos= %f %f %f", &cam_pos[1][0], &cam_pos[1][1], &cam_pos[1][2]);
		sscanf(oneline, "camera2_rot= %f %f %f %f", &cam_rot[1][0], &cam_rot[1][1], &cam_rot[1][2], &cam_rot[1][3]);
	
	}
	}
	fclose(filein);
	return;
	}

}

/* texture setup functions */
void setupTexture(GLuint *textureid, int ah, int aw){
	unsigned int* data;											
	data = (unsigned int*)malloc(sizeof(unsigned int) * 4 * ah * aw);
	
	glGenTextures(1, textureid);					
	glBindTexture(GL_TEXTURE_2D, *textureid);			
	glTexImage2D(GL_TEXTURE_2D, 0, 4, ah, aw, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);			
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;	
}

int loadBMP(char *filename, textureImage *texture)
{
    FILE *file;
    unsigned short int bfType;
    long int bfOffBits;
    short int biPlanes;
    short int biBitCount;
    long int biSizeImage;
    if ((file = fopen(filename, "rb")) == NULL)
    {
    //    printf("File not found : %s\n", filename);
        return 0;
    }
    if(!fread(&bfType, sizeof(short int), 1, file))
    {
    //    printf("Error reading file!\n");
        return 0;
    }
    
    if (bfType != 19778)
    {
    //    printf("Not a Bitmap-File!\n");
        return 0;
    }        
    fseek(file, 8, SEEK_CUR);
    if (!fread(&bfOffBits, sizeof(long int), 1, file))
    {
     //   printf("Error reading file!\n");
        return 0;
    }
   // printf("Data at Offset: %ld\n", bfOffBits);
    fseek(file, 4, SEEK_CUR);
    fread(&texture->width, sizeof(int), 1, file);
   // printf("Width of Bitmap: %d\n", texture->width);
    fread(&texture->height, sizeof(int), 1, file);
    //printf("Height of Bitmap: %d\n", texture->height);
    fread(&biPlanes, sizeof(short int), 1, file);
    if (biPlanes != 1)
    {
      //  printf("Error: number of Planes not 1!\n");
        return 0;
    }
    if (!fread(&biBitCount, sizeof(short int), 1, file))
    {
     //   printf("Error reading file!\n");
        return 0;
    }
    //printf("Bits per Pixel: %d\n", biBitCount);
    if (biBitCount != 24)
    {
      //  printf("Bits per Pixel not 24\n");
        return 0;
    }
    biSizeImage = texture->width * texture->height * 3;
    //printf("Size of the image data: %ld\n", biSizeImage);
    texture->data = (unsigned char*)malloc(biSizeImage);
    fseek(file, bfOffBits, SEEK_SET);
    if (!fread(texture->data, biSizeImage, 1, file))
    {
        printf("Error loading file!\n");
        return 0;
    }
      // use GL_BGR_EXT instead
 //   for (i = 0; i < biSizeImage; i += 3)
  //  {
   //     temp = texture->data[i];
    //    texture->data[i] = texture->data[i + 2];
    //    texture->data[i + 2] = temp;
    //}
    return 1;
}

BOOL LoadGLTexture(GLuint *texPntr, char* name){
    Bool status;
    textureImage *texti;
    
    status = False;
    texti = (textureImage*)malloc(sizeof(textureImage));
    if (loadBMP(name, texti))
    {
        status = True;
        glGenTextures(1, texPntr);
        glBindTexture(GL_TEXTURE_2D, *texPntr);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, texti->width, texti->height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texti->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    /* free the ram we used in our texture generation process */
    if (texti)
    {
        if (texti->data)
            free(texti->data);
        free(texti);
    }    
    return status;
}

void initializevideos(int meshid, char* filename){
	avi_file[meshid] = avm::CreateReadFile(filename); // get the file and load it
}



void tscripterror(char *terrorstring){ // will make this appear on the screen via GL
	
}


void loadfx(char *scriptfile, int bankid){
	FILE *stream;
	char tline[255];
	
	char *t_obj;
	char *test;
	char tmp[255];
	
	char seps[] = "()";
	char tmes[200];
	int lineerror;
	
	int meshtype;
	int result;
	
	if (bankid == 1){
		effectC = 100;
	}
	if((stream = fopen(scriptfile, "rt" )) != NULL ){
		int loop = 0;
		int fxmeshc;
		
		
		sprintf(tmp, "LOADING : %s", scriptfile);
		showbootscreen(tmp);
		
		while( !feof( stream ) ){   
			char etmp[255];
			loop++;
			lineerror=2;
			rereadstr(stream, tline);
			t_obj = strstr(tline, "effect(" );
			
			if( t_obj != NULL )	{
				//now we read out the tscript object
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
   				sprintf(etmp,"loading FX : %s", test);
				showbootscreen(etmp);
				
				lineerror = 1;
				fxmeshc = 0;
				
				effectC++;
			}
			
			t_obj = strstr(tline, "mesh(" );
			if( t_obj != NULL )	{
				
				mfx[mesh_c]=fxmeshc;  /////////////////////
				
				
				test = strtok( tline, seps );  
				test = strtok( NULL, seps );
				result = strcmp( test, "3ds" );
 				if( result == 0 ){
      					meshtype = 1; /////////
					tmeshtype[mesh_c]=1; /////////////
					lineerror = 1;
					
				}
				result = strcmp( test, "text" );
				if( result == 0 ){
      				meshtype = 2; /////////////////////////
					tmeshtype[mesh_c]= 2; //////////////////
					lineerror = 1; 
				}
				
				result = strcmp( test, "oscilloscope" );
				if( result == 0 ){
      				meshtype = 2; /////////////////////////
					tmeshtype[mesh_c]= 3; //////////////////////////////
					lineerror = 1;
				}
				
				result = strcmp( test, "video" );
				if( result == 0 ){
      				meshtype = 2; ///////////////////////////
					tmeshtype[mesh_c]= 4; ///////////////////////////////
					lineerror = 1;
				}
				result = strcmp( test, "oscillquad" );
				if( result == 0 ){
      					meshtype = 2; /////////////////////////
					tmeshtype[mesh_c]= 5; //////////////////////////////////
					lineerror = 1;
				}

				fx_mesh[mesh_c] = effectC-1; ///////////////////
				mesh_c++;  ////////////
				fxmeshc++;  
			}
			
			t_obj = strstr(tline, "location(" );
			if( t_obj != NULL )	{
				if (meshtype == 1){
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				scene[mesh_c-1].LoadFile(test); //////////////
				meshtype = 0;
				
				}else{
				//printf(tmes,"error on line %i : a mesh cannot be loaded from a file unless the mesh type is 3ds: %s",loop, tline);
					tscripterror(tmes);
				}
				lineerror = 1;
			}
			t_obj = strstr(tline, "bindtexture(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				LoadGLTexture(&t_texture[mesh_c-1], test);
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

			t_obj = strstr(tline, "attachlight()" );
			if( t_obj != NULL )	{
				islit[mesh_c-1]=1;
				lineerror = 1;
			}

			t_obj = strstr(tline, "texttype(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				result = strcmp( test, "3d" );
				if( result == 0 ){
				
				objtext[mesh_c-1].type = 1;
					lineerror = 1;
				}
				result = strcmp( test, "2d" );
				if( result == 0 ){
				
				objtext[mesh_c-1].type = 2;
					lineerror = 1;
				}
				if (lineerror == 2){
					sprintf(tmes,"error on line %i : Not a valid text type",loop);
					tscripterror(tmes);
				}
			}
			
			t_obj = strstr(tline, "fontpath(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				
				if (objtext[mesh_c-1].type==1){
					fonts[mesh_c-1] = new FTGLExtrdFont(test);
				}else{
					fonts[mesh_c-1] = new FTGLBitmapFont(test);	
				}
				if( fonts[mesh_c-1]->Error()){
					printf("\n\n Failed to open font %s \n\n", test);
				}
				
				lineerror = 1;
			}
			t_obj = strstr(tline, "fontsize(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				
				sscanf(test, "%d", &objtext[mesh_c-1].size);
				fonts[mesh_c-1]->FaceSize(objtext[mesh_c-1].size);
				fonts[mesh_c-1]->Depth(0.2*objtext[mesh_c-1].size);
				fonts[mesh_c-1]->CharMap(ft_encoding_unicode);	
				lineerror = 1;
			}

			t_obj = strstr(tline, "text(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				strncpy(objtext[mesh_c-1].string, test, strlen(test));
				lineerror = 1;
			}

			t_obj = strstr(tline, "attachavi(" );
			if( t_obj != NULL )	{
				test = strtok( tline, seps );
				test = strtok( NULL, seps );
				
				attachedavi[mesh_c-1] = 1;
				initializevideos(mesh_c-1, test);
				lineerror = 1;
				
			}
			
			t_obj = strstr(tline, "usefeed(" );
			if( t_obj != NULL )	{
				feed[mesh_c-1] = 1;
				
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

			if (lineerror == 2){
			//	sprintf(tmes,"error on line %i : can not comprehend: %s",loop, tline);
			//	tscripterror(tmes);
      			}
				
		}
	fclose(stream);
		
			
	}else{
		//tscripterror( "tscript file could not be found\n" );
	}
}



int v0grab = 0;
int forever0;
void videothread0(void* a){
	forever0=1;
	while(forever0){
		image = avistream->GetFrame(true);
		if (!avistream->Eof() && image ) {
			v0rgb = new CImage(image, 24);
			v0grab=0;
			pthread_cond_wait(&v0cond, &v0mut);
			v0rgb->Release();
			image->Release();
		} else {
			avistream->Seek(0);  // back to start to stream
		}
	}
	pthread_exit(NULL);
}
void startvideo(int meshid, int vidchannel){
	if (vidchannel==1){
		
		avistream1 = avi_file[meshid]->GetStream(0, avm::IReadStream::Video );
		avistream1->StartStreaming();
		streaminfo1 = avistream1->GetStreamInfo();
		width1      = streaminfo1->GetVideoWidth();
		height1     = streaminfo1->GetVideoHeight();
		stream_fps1 = streaminfo1->GetFps();
	
	}else{
		
		avistream = avi_file[meshid]->GetStream(0, avm::IReadStream::Video );
		avistream->StartStreaming();
		streaminfo = avistream->GetStreamInfo();
		width      = streaminfo->GetVideoWidth();
		height     = streaminfo->GetVideoHeight();
		stream_fps = streaminfo->GetFps();
		forever0=0;
		//pthread_cond_broadcast(&v0cond);
		//thr_vid0 = pthread_create(&v0_thread, NULL, (void*(*)(void*))videothread0, (void*)meshid);
	}
}
int vidid = 1;

void getvideoframethread(int vidchannel){
glEnable(GL_TEXTURE_RECTANGLE_NV);
	if (vidchannel==1){
		image1 = avistream1->GetFrame(true);
		if (!avistream1->Eof() && image1 ) {
			CImage* rgbci = new CImage(image1, 24);
			
			glBindTexture(GL_TEXTURE_RECTANGLE_NV, vidtexture1);  
			glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, width1, height1, 0,  GL_BGR, GL_UNSIGNED_BYTE,  rgbci->At(0,0));
			rgbci->Release();
			image1->Release();
		} else {
			avistream1->Seek(0);  // back to start to stream
		}
	}else{
		image = avistream->GetFrame(true);
		if (!avistream->Eof() && image) {
			CImage* rgbci = new CImage(image, 24);
					
			glBindTexture(GL_TEXTURE_RECTANGLE_NV, vidtexture0);  
			glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, width, height, 0,  GL_BGR, GL_UNSIGNED_BYTE, rgbci->At(0,0));
			image->Release();
			rgbci->Release();
		} else {
		
		avistream->Seek(0);  // back to start to stream
		}
		/*
		if (v0grab==1){
			glBindTexture(GL_TEXTURE_RECTANGLE_NV, vidtexture0);  
			glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, width, height, 0,  GL_BGR, GL_UNSIGNED_BYTE, v0rgb->At(0,0));
			v0grab=0;
			pthread_cond_broadcast(&v0cond);
		}
		*/
		
	}
}


/*//////////////////////////////////////////////////// camera routines ////////////////////////////////////////////////////////////////*/
void camerarotate(int direction, float amount){
	if(direction==0){
		if(currentcam == 0){
		lookupdown-= amount;
		}else{
		updown-= amount;
		}
	}
	if(direction==1){
		if(currentcam == 0){
		lookupdown+= amount;
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
	xpos -= (float)sin(heading*piover180) * amount;
	zpos -= (float)cos(heading*piover180) * amount;
	}
	if (direction == 1){
	xpos += (float)sin(heading*piover180) * amount;
	zpos += (float)cos(heading*piover180) * amount;
	}
}

void oko_camera(void){
	if (cambeat == 1){
        if (beat == 1){
			if (currentcam < 8) currentcam++;
			else currentcam=1;
		}
        }
	
	if (currentcam == 0){
		cambeat = 1;

	}
	
	if (currentcam == 1){
		//cambeat == 0;
		float mspin=(25);
		dblAngle1 = dblAngle1 + tickz(0.3f);
		dblAngle2 = dblAngle2 + tickz(0.3f);
        	xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}
	
	if (currentcam == 2){
	//	cambeat == 0;
		float mspin=(25);
		dblAngle1 = dblAngle1 - tickz(0.9f);
        	dblAngle2 = dblAngle2 - tickz(0.03f);
		xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam == 3){
	//	cambeat == 0;
	float mspin=(10);
	dblAngle1 = dblAngle1 - tickz(0.01f);
        dblAngle2 = tickz(0.01);//dblAngle2 - 0.01;
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam == 4){
	//	cambeat == 0;
		if (cup == 1) cdist+=1;
		else cdist-=0.7;
		if (cdist>300) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - tickz(0.01f);
        dblAngle2 = dblAngle2 + tickz(0.1f);
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam == 5){
	//	cambeat == 0;
		if (cup == 1) cdist+=0.2;
		else cdist-=1;
		if (cdist>100) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - tickz(0.1f);
        dblAngle2 = dblAngle2 + tickz(0.001f);
        xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}

	if (currentcam == 6){
	//	cambeat == 0;
		if (cup == 1) cdist+=1;
		else cdist-=1;
		if (cdist>300) cup=0;
		if (cdist<5) cup=1;
		float mspin=cdist;
		dblAngle1 = dblAngle1 - tickz(0.01f);
        	dblAngle2 = dblAngle2 + tickz(0.06f);
        	xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}
	if (currentcam == 7){
	//	cambeat == 0;
		if (cup == 1) cdist+=3;
		
		else cdist-=3;
		
		if (cdist>500) cup=0;
		
		if (cdist<5) cup=1;
		
		float mspin=cdist;
		dblAngle1 = dblAngle1 - tickz(0.01f);
        	dblAngle2 = dblAngle2 + tickz(0.3f);
        	xtrans = mspin * cos(dblAngle1) * cos(dblAngle2);
		ztrans = mspin * sin(dblAngle2);
		ytrans = mspin * sin(dblAngle1) * cos(dblAngle2);
		gluLookAt(xtrans, ytrans, ztrans, 0,0,0, 0,1,0);
	}
}


/*//////////////////////////////////////////////////////////////////////////// render routines////////////////////////////////////////*/
void rendermode(void){
	if (rmode==0){
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			bg = true;
	}
	if (rmode==1){
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
			bg = false;
	}
	if (rmode==2){
		if (beat==1){
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
			bg = false;
		}else{
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			bg = true;
		}
	}
	if (rmode==3){
		if (beat==1){
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			bg = true;
		}else{
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
			bg = false;
		}
	}
}



/* function called when our window is resized (should only happen in window mode) */
void resizeGLScene(unsigned int width, unsigned int height)
{
    if (height == 0)    /* Prevent A Divide By Zero If The Window Is Too Small */
        height = 1;
    glViewport(0, 0, width, height);    /* Reset The Current Viewport And Perspective Transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}



void showbootscreen(char* infotext){
	strncpy(ltext[lc].thetext, infotext, 255);
	glClearColor (0.0f, 0.0f, 1.0f, 1.0f);
	glClearDepth (1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	glViewport(0,0,GLWin.width,GLWin.height);
	glMatrixMode(GL_PROJECTION);	
	glPushMatrix();			
	glLoadIdentity();
	glOrtho(0,640,0,480,-1,5000);	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();	
	glLoadIdentity();		
	
	glDisable(GL_TEXTURE_2D);
	for (int g=0;g<lc+1;g++){
		glRasterPos2i(20 , 460-(g*12));
		glColor4f(1,1,1,0.3);
		loadingfont->Render( ltext[g].thetext);
	}
	
	glLoadIdentity();		
	//glTranslatef(0,0,1);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, bootscreen);  
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(640,480);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0,480);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0,0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(640,0);
	glEnd();
					
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();			
	glMatrixMode(GL_MODELVIEW);	
	glPopMatrix();
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);	
	if (GLWin.doubleBuffered)
	{
		glXSwapBuffers(GLWin.dpy, GLWin.win);
	}
	lc++;	
}



/* general OpenGL initialization function intialize all of the sound and video and setup the textures we will use for video */
int initGL(GLvoid)
{	
	loadingfont = new FTGLBitmapFont("/mnt/win_c/windows/fonts/arial.ttf");
	loadingfont->CharMap(ft_encoding_unicode);
	loadingfont->FaceSize(15);
	LoadGLTexture(&bootscreen,"lib/oko-t/splash.bmp");
	showbootscreen("oko t : tedium video synth 0.01");
	
	thr_id = pthread_create(&p_thread, NULL, (void*(*)(void*))audiothread, (void*)0);
	loadconf(1);
	showbootscreen("starting audio thread");
	
	showbootscreen("setting up OPEN GL environment");	
        glShadeModel(GL_SMOOTH);									// Select Smooth Shading
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);						// Black Background
	glClearDepth (1.0f);	
	glDepthFunc (GL_LEQUAL);	
	glEnable(GL_DEPTH_TEST);	
	glShadeModel (GL_SMOOTH);	
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	overunder = glGenLists(1);
	glNewList(overunder,GL_COMPILE);
	glBegin(GL_QUADS);										
			glTexCoord2f(1.0f, 1.0f); glVertex2d(640,480);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(0,480);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(0,0);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(640,0);
	glEnd();
	glEndList();
	
	
	setupTexture(&KeyTexture, 512, 512);
		
	showbootscreen("creating bank 1 video texture");
	glGenTextures(1, &vidtexture0);
        glBindTexture(GL_TEXTURE_RECTANGLE_NV, vidtexture0);
	
	showbootscreen("creating bank 2 video texture");
	glGenTextures(1, &vidtexture1);
        glBindTexture(GL_TEXTURE_RECTANGLE_NV, vidtexture1);

	showbootscreen("creating bank live video feed texture");
	glGenTextures(1, &livefeed);
        glBindTexture(GL_TEXTURE_RECTANGLE_NV, vidtexture1);
	
	showbootscreen("starting video 4 linux device");		
	thr_vid = pthread_create(&v_thread, NULL, (void*(*)(void*))initvideo4linux, (void*)0);
	
	showbootscreen("loading FX bank 1");	
	loadfx("banks/bank0.okot", 0);
	
	showbootscreen("loading FX bank 2");	
	loadfx("banks/bank1.okot", 1);
	
		
	glEnableClientState(GL_VERTEX_ARRAY);
  	glEnableClientState(GL_NORMAL_ARRAY);
    	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	vision=0;
    glFlush();
    return True;
}

/* Here goes our drawing code */
void DrawClean(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, KeyTexture);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);		
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();				
	glLoadIdentity();
	glOrtho(0,100,0,100,-1,5000);		
	glMatrixMode(GL_MODELVIEW);		
	glPushMatrix();	
	glLoadIdentity();			
	glTranslated(0,0,1);
	glDisable(GL_BLEND);			
	int grid = 2;
	int y;
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	for (int x = 0; x < grid+1 ; x++){
		for (y = 0; y < grid+1 ; y++){
			
			glBegin(GL_QUADS);
			if (vision == 3){
				if (((y == 2) || (y == 4)) &&  ((x==2) || (x==4))){
				
					glTexCoord2f(0,1);						
					glVertex2f((x-1)*(100/grid),(100/grid)*y);
					glTexCoord2f(0,0);						
					glVertex2f((x-1)*(100/grid),(y-1)*(100/grid));
					glTexCoord2f(1,0);						
					glVertex2f((100/grid)*x,(y-1)*(100/grid));
					glTexCoord2f(1,1);				
					glVertex2f((100/grid)*x,(100/grid)*y);
				}else if(((x==1) || (x==3)) && ((y == 2) || (y == 4))){
					glTexCoord2f(0,0);						
					glVertex2f((100/grid)*x,(y-1)*(100/grid));
					glTexCoord2f(0,1);						
					glVertex2f((100/grid)*x,(100/grid)*y);	
					glTexCoord2f(1,1);						
					glVertex2f((x-1)*(100/grid),(100/grid)*y);
					glTexCoord2f(1,0);				
					glVertex2f((x-1)*(100/grid),(y-1)*(100/grid));

				}else if(((x==2) || (x==4)) && ((y == 1) || (y == 3))){
					glTexCoord2f(0,0);						
					glVertex2f((x-1)*(100/grid),(100/grid)*y);
					glTexCoord2f(0,1);						
					glVertex2f((x-1)*(100/grid),(y-1)*(100/grid));
					glTexCoord2f(1,1);						
					glVertex2f((100/grid)*x,(y-1)*(100/grid));
					glTexCoord2f(1,0);				
					glVertex2f((100/grid)*x,(100/grid)*y);
				}else{
					glTexCoord2f(1,0);						
					glVertex2f((x-1)*(100/grid),(100/grid)*y);
					glTexCoord2f(1,1);						
					glVertex2f((x-1)*(100/grid),(y-1)*(100/grid));
					glTexCoord2f(0,1);						
					glVertex2f((100/grid)*x,(y-1)*(100/grid));
					glTexCoord2f(0,0);				
					glVertex2f((100/grid)*x,(100/grid)*y);			
				
				}
			}else{
				glTexCoord2f(0,1);						
				glVertex2f((x-1)*(100/grid),(100/grid)*y);
				glTexCoord2f(0,0);						
				glVertex2f((x-1)*(100/grid),(y-1)*(100/grid));
				glTexCoord2f(1,0);						
				glVertex2f((100/grid)*x,(y-1)*(100/grid));
				glTexCoord2f(1,1);				
				glVertex2f((100/grid)*x,(100/grid)*y);		
			}
		glEnd();
		}
		
	}
	glMatrixMode( GL_PROJECTION );	
	glPopMatrix();			
	glMatrixMode( GL_MODELVIEW );	
	glPopMatrix();	
	glEnable(GL_DEPTH_TEST);	
	glDisable(GL_TEXTURE_2D);	
	glDisable(GL_BLEND);		
	glBindTexture(GL_TEXTURE_2D,0);	
	
}

void DrawBlur(int times, float inc){
	// this will be replace with a CG Blur
	float spost = 0.0f;		
	float alphainc = 0.9f / times;	
	float alpha = 0.25f;		
	// Disable AutoTexture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D);	
	glDisable(GL_DEPTH_TEST);	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);		
	glEnable(GL_BLEND);			
	glBindTexture(GL_TEXTURE_2D, KeyTexture);	
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
	alphainc = alpha / times;
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	for (int num = 0;num < times;num++)		
		{
		//glTranslatef(((num*5)),(num*-5),0);
	        // glRotatef(num, 0, 0, 1);
		glBegin(GL_QUADS);			
			glColor4f(1.0f, 1.0f, 1.0f, alpha);	
			glTexCoord2f(0+spost,1-spost);	
			glVertex2f(0,480);

			glTexCoord2f(0+spost,0+spost);		
			glVertex2f(0,0);			

			glTexCoord2f(1-spost,0+spost);		
			glVertex2f(640,0);
								

			glTexCoord2f(1-spost,1-spost);		
			glVertex2f(640,480);

			spost += inc;		
			alpha = alpha - alphainc;
		glEnd();			
	}
	glMatrixMode( GL_PROJECTION );	
	glPopMatrix();			
	glMatrixMode( GL_MODELVIEW );	
	glPopMatrix();	
	glEnable(GL_DEPTH_TEST);	
	glDisable(GL_TEXTURE_2D);	
	glDisable(GL_BLEND);		
	glBindTexture(GL_TEXTURE_2D,0);	
}

void audiotester(void){ // osccilisocpe 2d used to test audio input
	/*glDisable(GL_DEPTH_TEST);			
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);						
	glPushMatrix();										
	glLoadIdentity();
	glOrtho(0,1024,0,100,-1,5000);						
	glMatrixMode(GL_MODELVIEW);							
	glPushMatrix();	
	glLoadIdentity();									
	glTranslated(0,0,1);
	*/
	int step;
	glLineWidth(1);
	for (step=0;step<1024; step++){
		//glColor4f(0.5f, 0.9f, 0.3f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(step-512, (audiobuf[step-1]/327.68), 0);	
		glVertex3f(step-512, (audiobuf[step]/327.68), 0);
		glEnd();
	}
	
	
	/*glMatrixMode( GL_PROJECTION );								
	glPopMatrix();										
	glMatrixMode( GL_MODELVIEW );								
	glPopMatrix();	
	
	*/
}

void callfx (int cam, float t_fov){
	glMatrixMode(GL_MODELVIEW);	
	glDisable(GL_BLEND);
	rendermode();
	glLoadIdentity ();	
	if (cam == 1){
		glRotatef(cam_rot[0][0],cam_rot[0][1],cam_rot[0][2],cam_rot[0][3]);
	}
	if (cam == 2){
		glRotatef(cam_rot[1][0],cam_rot[1][1],cam_rot[1][2],cam_rot[1][3]);
	}
	
	oko_camera();
	float LightPos1[] = { -xtrans, -ytrans, -ztrans, 1.0f};	
	float LightAmb1[] = { 0.5f, 0.5f, 0.5f, 1.0f};		// Ambient Light Values
	float LightDif1[] = { 1.0f, 1.0f, 1.0f, 1.0f};		// Diffuse Light Values
	float LightSpc1[] = {0.2f, 0.2f, 0.1f, 1.0f};		// Specular Light Values
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);		
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb1);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif1);		
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc1);		
	glEnable(GL_LIGHT1);
	
	float rw = 600;
	float myfft;
	
	for(uint tmesh=0;tmesh<mesh_c;tmesh++){
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f,1.0f,1.0f);
		
		if (fxonoff[fx_mesh[tmesh]] == 1){
			if (islit[tmesh]){
					glEnable(GL_LIGHTING);
			}else{
					glDisable(GL_LIGHTING);
			}
				glPushMatrix();
				if (cameralock[tmesh] == 1) glTranslatef(xtrans, ytrans, ztrans);
					glBindTexture(GL_TEXTURE_2D, t_texture[tmesh]);
				if (applyvideo[tmesh] == 1){
					// this where the mesh object get wrapped with a video that loaded into ram
					//for(unsigned int vloop=0;vloop<20;vloop++){
					//	if(fx_vid[fx_mesh[tmesh]][vloop] == 1){
					//		tstext=0;
					//		glBindTexture(GL_TEXTURE_2D, v_texture[vloop][v_current_frame[vloop]]);
					//	}
					//}
					
					
					
				}else{
					glBindTexture(GL_TEXTURE_2D, t_texture[tmesh]);
				}


				if (attachedavi[tmesh] == 1){
					if (fx_mesh[tmesh] < 100){
						if(bank0avi == 1){					
							if (bank0openavi == 1){
							avistream->StopStreaming();
							}
						bank0avi = 0;
						bank0openavi = 1;
						startvideo(tmesh, 0);
						}
						getvideoframethread(0);
						
					}
					if ((fx_mesh[tmesh] > 99) && (fx_mesh[tmesh] < 200)){
						if(bank1avi == 1){					
							if (bank1openavi == 1){
							avistream1->StopStreaming();
							}
						bank1avi = 0;
						bank1openavi = 1;
						startvideo(tmesh, 1);
						}
						getvideoframethread(1);
					}
					
				}
				
				if (feed[tmesh] == 1){
					v4linux_grabframes(tmesh);
				}

				//blendtype will go here
				glBlendFunc(GL_SRC_COLOR,GL_DST_ALPHA);				
							
				if (tblend[tmesh] == 1){
					glEnable(GL_BLEND);
				}else{
					glDisable(GL_BLEND);
				}
				if (meshfft[tmesh] > 0){
					myfft = fftdata[meshfft[tmesh]]/70;
					glScaled(myfft, myfft, myfft);
				}
				if (beatscaled[tmesh] == 1){
					glScaled(sound/40, sound/40, sound/40);
				}
				if (meshwire[tmesh] == 1){
					glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
					glPolygonMode(GL_FRONT, GL_LINE);
					glPolygonMode(GL_BACK, GL_LINE);
				}else{
					if (bg){
					glPolygonMode(GL_FRONT, GL_FILL);
					glPolygonMode(GL_BACK, GL_FILL);
					}
				}
				
				glTranslatef(tposition[tmesh][0],tposition[tmesh][1],tposition[tmesh][2]);
				
				glRotatef(angle*trotate[tmesh][0],trotate[tmesh][1],trotate[tmesh][2],trotate[tmesh][3]);			
				
				
				if (tcolor[tmesh][3] == 1){
					glColor3f(tcolor[tmesh][0], tcolor[tmesh][1], tcolor[tmesh][2]) ;
				}

				

				if (tmeshtype[tmesh] == 1){
					for (uint i= 0; i<scene[tmesh].GetMeshCount(); i++){
						LMesh &mesh = scene[tmesh].GetMesh(i);
						if (applyvideo[tmesh] == 1){
							if (meshonce[tmesh] != 1){
								meshonce[tmesh]=1;
								for(uint mcc=0; mcc<mesh.GetTriangleCount()*3;mcc++){
									LVector2 tv;
									
									tv = mesh.GetUV(mcc);  //to tempvector
									if (fx_mesh[tmesh] < 100){
									tv.x = width*tv.x;
									tv.y = height*tv.y;
									}else{
									tv.x = width1*tv.x;
									tv.y = height1*tv.y;
									}
									mesh.SetUV(tv, mcc);
								}
							}
							
						}
						glVertexPointer(4, GL_FLOAT, 0, &mesh.GetVertex(0));
						glNormalPointer(GL_FLOAT, 0, &mesh.GetNormal(0));
						glColor3f(1.0f,1.0f,1.0f);
						glTexCoordPointer(2, GL_FLOAT, 0, &mesh.GetUV(0));
						glDrawElements(GL_TRIANGLES, mesh.GetTriangleCount()*3, GL_UNSIGNED_SHORT, &mesh.GetTriangle(0));
					}
					
					
					
				}
										
				if (tmeshtype[tmesh] == 2){
					if (objtext[tmesh].type == 1){
						fonts[tmesh]->Render(objtext[tmesh].string);
					}
				}

				if (tmeshtype[tmesh] == 3){
					audiotester();
				}
	
				if ((tmeshtype[tmesh] == 4)||((tmeshtype[tmesh] == 2)&(objtext[tmesh].type == 2))){
				
					if (bg == true)
					{
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
					
					if (tblend[tmesh] == 1){
						glEnable(GL_BLEND);
					}else{
						glDisable(GL_BLEND);
					}
					
					glTranslated(0,480,0); // faster than flipping video images on the CPU
					glRotatef(180,1,0,0); // faster than flipping video images on the CPU
					
					if ((tmeshtype[tmesh] == 2)&(objtext[tmesh].type == 2)){
						glTranslatef(tposition[tmesh][0],tposition[tmesh][1],tposition[tmesh][2]);
						//glRasterPos2f(tposition[tmesh][0],tposition[tmesh][1]);
						fonts[tmesh]->Render(objtext[tmesh].string);
					}else{
						float stretch;
						if (feed[tmesh] == 1)stretch = 10;
						else stretch=0;
						if (fx_mesh[tmesh] < 100){
							glBegin(GL_QUADS);
							glTexCoord2f(width, height);  glVertex2f( 640, 480+stretch);
							glTexCoord2f(0, height);  glVertex2f(0, 480+stretch);
							glTexCoord2f(0, 0);  glVertex2f(0,-5);
							glTexCoord2f(width, -1);  glVertex2f( 640,-5);
							glEnd();
						}else{
							glBegin(GL_QUADS);
							glTexCoord2f(width1, height1);  glVertex2f( 640, 480+stretch);
							glTexCoord2f(0, height1);  glVertex2f(0, 480+stretch);
							glTexCoord2f(0, 0);  glVertex2f(0,-5);
							glTexCoord2f(width1, 0);  glVertex2f( 640,-5);
							glEnd();
						}
					}
					
					glMatrixMode(GL_PROJECTION);
					glPopMatrix();			
					glMatrixMode(GL_MODELVIEW);	
					glPopMatrix();
					glLoadIdentity();
					glEnable(GL_DEPTH_TEST);	
					}
				}
				
				if (tmeshtype[tmesh] == 5){
					glDisable(GL_BLEND);
						for(int mstep=0;mstep<26;mstep++){
							for(int ss=18; ss>0; ss--){
								os4[ss][mstep] = os4[ss - 1][mstep];
								
								glBegin(GL_LINES);
									glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os4[ss][mstep]), ss * 20);	
									glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * 20));
								glEnd();
								
								glBegin(GL_LINES);
									glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os4[ss][mstep]), ss * -20);					
									glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * -20));
								glEnd();

								glBegin(GL_LINES);
								glVertex3f((-mstep * (100 / 25) * (rw / 100)) - 150, os4[ss][mstep], ss * 20);					
									glVertex3f((((-mstep - 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * 20));
								glEnd();
								
								glBegin(GL_LINES);
								glVertex3f((-mstep * (100 / 25) * (rw / 100)) - 150, os4[ss][mstep], ss * -20);					
									glVertex3f((((-mstep - 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * -20));
								glEnd();


								//glDisable(GL_BLEND);
							}
							os4[0][mstep] = fftdata[mstep];
						}
					
				}
				
				
				glColor3f(1.0f,1.0f,1.0f);
				
				glPopMatrix();
			
			}	
		glDisable(GL_TEXTURE_RECTANGLE_NV);
		glDisable(GL_TEXTURE_2D);
	}
	glColor3f(1.0f,1.0f,1.0f);	
}

/*
void callfx (int cam, float t_fov){
	char Tavi[100];
	glMatrixMode(GL_MODELVIEW);	
	glDisable(GL_BLEND);
	rendermode();
	glLoadIdentity ();	
	if (cam == 1){
		glRotatef(cam_rot[0][0],cam_rot[0][1],cam_rot[0][2],cam_rot[0][3]);
	}
	if (cam == 2){
		glRotatef(cam_rot[1][0],cam_rot[1][1],cam_rot[1][2],cam_rot[1][3]);
	}
	
	oko_camera();
	float LightPos1[] = { -xtrans, -ytrans, -ztrans, 1.0f};	
	float LightAmb1[] = { 0.5f, 0.5f, 0.5f, 1.0f};		// Ambient Light Values
	float LightDif1[] = { 1.0f, 1.0f, 1.0f, 1.0f};		// Diffuse Light Values
	float LightSpc1[] = {0.2f, 0.2f, 0.1f, 1.0f};		// Specular Light Values
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);		
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb1);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif1);		
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc1);		
	glEnable(GL_LIGHT1);
	
	float rw = 600;
	int tstext=1;
	float myfft;
	int tmesh;
	
	for (int fxc=0; fxc<effectC; fxc++){
		if (fx[fxc].onoff == 1){
			glEnable(GL_TEXTURE_2D);
			glColor3f(1.0f,1.0f,1.0f);
		
			for (int obc=0; obc<=fx[fxc].objCount; obc++){
				if (fx[fxc].object[obc].islit == 1){
					glEnable(GL_LIGHTING);
				}else{
					glDisable(GL_LIGHTING);
				}
				glPushMatrix();
				if (fx[fxc].object[obc].cameralock == 1) glTranslatef(xtrans, ytrans, ztrans);
				glBindTexture(GL_TEXTURE_2D, fx[fxc].object[obc].t_texture);
				if (fx[fxc].object[obc].attachedavi == 1){
					if (fxc < 100){
						if(bank0avi == 1){					
							if (bank0openavi == 1){
							avistream->StopStreaming();
							}
						bank0avi = 0;
						bank0openavi = 1;
						avistream = fx[fxc].object[obc].avi_file->GetStream(0, avm::IReadStream::Video );
						avistream->SetDirection(True);
						avistream->StartStreaming();
						streaminfo = avistream->GetStreamInfo();
						width      = streaminfo->GetVideoWidth();
						height     = streaminfo->GetVideoHeight();
						stream_fps = streaminfo->GetFps();
						}
						getvideoframethread(0);
						
					}
					if ((fxc > 99) && (fxc < 200)){
						if(bank1avi == 1){					
							if (bank1openavi == 1){
							avistream1->StopStreaming();
							}
						bank1avi = 0;
						bank1openavi = 1;
						avistream1 = fx[fxc].object[obc].avi_file->GetStream(0, avm::IReadStream::Video );
						avistream1->SetDirection(True);
						avistream1->StartStreaming();
						streaminfo1 = avistream1->GetStreamInfo();
						width1      = streaminfo1->GetVideoWidth();
						height1     = streaminfo1->GetVideoHeight();
						stream_fps1 = streaminfo1->GetFps();
						}
						getvideoframethread(1);
					}
					
				}
				if (fx[fxc].object[obc].feed == 1){
					v4linux_grabframes(tmesh);
				}
				glBlendFunc(GL_SRC_COLOR,GL_DST_ALPHA); /// blend function wil go here
				if (fx[fxc].object[obc].blend == 1){
					glEnable(GL_BLEND);
				}else{
					glDisable(GL_BLEND);
				}
				if (fx[fxc].object[obc].fft > 0){
					//myfft = fftdata[fx[fxc].object[obc].fft]/70;
					//glScaled(myfft, myfft, myfft);
				}
				if (fx[fxc].object[obc].beatscaled == 1){
					glScaled(sound/40, sound/40, sound/40);
				}
				if (fx[fxc].object[obc].meshwire == 1){
					glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
					glPolygonMode(GL_FRONT, GL_LINE);
					glPolygonMode(GL_BACK, GL_LINE);
				}else{
					if (bg){
					glPolygonMode(GL_FRONT, GL_FILL);
					glPolygonMode(GL_BACK, GL_FILL);
					}
				}
				glTranslatef(fx[fxc].object[obc].position[0],fx[fxc].object[obc].position[1],fx[fxc].object[obc].position[2]);
				glRotatef(angle*fx[fxc].object[obc].rotation[0],fx[fxc].object[obc].rotation[1],fx[fxc].object[obc].rotation[2],fx[fxc].object[obc].rotation[3]);			
				if (tcolor[tmesh][3] == 1){GLXFBConfigSGIX conf;
	GLXContext ctx;
	GLXPbufferSGIX pbuffer
					glColor3f(fx[fxc].object[obc].color[0], fx[fxc].object[obc].color[1], fx[fxc].object[obc].color[2]) ;
				}
			
				if (fx[fxc].object[obc].type == 1){
					for (uint i= 0; i<fx[fxc].object[obc].scene.GetMeshCount(); i++){
						printf("%d : %d : %d \n", fxc,obc,i);
						LMesh &mesh = fx[fxc].object[obc].scene.GetMesh(i);
						glVertexPointer(4, GL_FLOAT, 0, &mesh.GetVertex(0));
						glNormalPointer(GL_FLOAT, 0, &mesh.GetNormal(0));
						glColor3f(1.0f,1.0f,1.0f);
						glTexCoordPointer(2, GL_FLOAT, 0, &mesh.GetUV(0));
						glDrawElements(GL_TRIANGLES, mesh.GetTriangleCount()*3, GL_UNSIGNED_SHORT, &mesh.GetTriangle(0));
					}
				}

				if (fx[fxc].object[obc].type == 2){
					if (fx[fxc].object[obc].texttype == 1){
					// this is the text to be done yet
					}GLXFBConfigSGIX conf;
	GLXContext ctx;
	GLXPbufferSGIX pbuffer
				}
				
				if (fx[fxc].object[obc].type == 3){
					audiotester();
				}
				
				if (fx[fxc].object[obc].type == 4){
					if (bg == true){
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
					
						if (fx[fxc].object[obc].blend == 1){
							glEnable(GL_BLEND);
						}else{
							glDisable(GL_BLEND);
						}
						if (fx[fxc].object[obc].feed == 1){
						// got flip and move the image
						glTranslated(0,480,0);
						glRotatef(180,1,0,0);
						
						}
						if (fxc < 100){
						glBegin(GL_QUADS);
							glTexCoord2f(width, height);  glVertex2f( 640, 480);
							glTexCoord2f(0, height);  glVertex2f(0, 480);
							glTexCoord2f(0, 0);  glVertex2f(0,0);
							glTexCoord2f(width, 0);  glVertex2f( 640,0);
						glEnd();
						}else{
						glBegin(GL_QUADS);
							glTexCoord2f(width1, height1);  glVertex2f( 640, 480);
							glTexCoord2f(0, height1);  glVertex2f(0, 480);
							glTexCoord2f(0, 0);  glVertex2f(0,0);
							glTexCoord2f(width1, 0);  glVertex2f( 640,0);
						glEnd();
						}
						glMatrixMode(GL_PROJECTION);
						glPopMatrix();			
						glMatrixMode(GL_MODELVIEW);	
						glPopMatrix();
						glLoadIdentity();
						glEnable(GL_DEPTH_TEST);	
					}
				}
				if (fx[fxc].object[obc].type == 5){
					glDisable(GL_BLEND);
					for(int mstep=0;mstep<26;mstep++){
						for(int ss=18; ss>0; ss--){
							os4[ss][mstep] = os4[ss - 1][mstep];
							
							glBegin(GL_LINES);
								glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os4[ss][mstep]), ss * 20);	
								glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * 20));
							glEnd();
							
							glBegin(GL_LINES);
								glVertex3f((mstep * (100 / 25) * (rw / 100)) - 150, (os4[ss][mstep]), ss * -20);
								glVertex3f((((mstep + 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * -20));
							glEnd();

							glBegin(GL_LINES);
								glVertex3f((-mstep * (100 / 25) * (rw / 100)) - 150, os4[ss][mstep], ss * 20);	
								glVertex3f((((-mstep - 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * 20));
							glEnd();
							
							glBegin(GL_LINES);
								glVertex3f((-mstep * (100 / 25) * (rw / 100)) - 150, os4[ss][mstep], ss * -20);	
								glVertex3f((((-mstep - 1) * (100 / 25)) * (rw / 100)) - 150, os4[ss][mstep], (ss * -20));
							glEnd();
						}
						os4[0][mstep] = fftdata[mstep];
					}
				}
				glColor3f(1.0f,1.0f,1.0f);
				glPopMatrix();
			}
		}
		glDisable(GL_TEXTURE_RECTANGLE_NV);
		glDisable(GL_TEXTURE_2D);
	}
	glColor3f(1.0f,1.0f,1.0f);	
}

*/

static GLXFBConfig fbconfig;
static GLXPbuffer glxpbuffer;
static GLXContext pbuffercontext;
static int allocatedpbuffer = 0;

int drawGLScene(GLvoid){
	gettime();
	int num_scr=0;
	
	
	//The worlds dodgiest Beat Detection >> Works great with Drum and Bass
	sound = ((fftdata[10] + fftdata[20] + fftdata[5] + fftdata[15] + fftdata[25] + fftdata[30]) / 6)/10;
	if (sound >= 7){
		beat=1;
	}else{
		beat=0;
	}
		
	//offscreen rendering to texture : all done on the card GPU and ram!!!!!!
	
	if ((vision == 1) || (vision == 3) || (vision == 4)  || ((vision == 2) & (beat==1))){
		
	   	glXMakeCurrent(GLWin.dpy, glxpbuffer, pbuffercontext);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glViewport(0,0,512,512);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective( fov[0], (GLfloat)(aspectwidth)/(GLfloat)(aspectheight), 1, 5000 );
		callfx(1, fov[0]);
		glBindTexture(GL_TEXTURE_2D,KeyTexture);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 512, 512);
		
		
		glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
	}
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    
	if (num_scr<screens){
		if (screens==1){
				glViewport (0, 0, GLWin.width, GLWin.height);
			}else if(dualdesk==1){
				glViewport (0, 0, GLWin.width/2, GLWin.height);
			}else {
				glViewport (0, GLWin.height/2, GLWin.width/2, GLWin.height/2);
			}
			if ((vision == 1) || ((vision == 2) & (beat==1))){
				DrawBlur(15,0.02f);	
			}else{
			glMatrixMode (GL_PROJECTION);
			glLoadIdentity ();
			gluPerspective( fov[0], (GLfloat)(aspectwidth)/(GLfloat)(aspectheight), 1, 5000  );
			if ((vision == 3) || (vision == 4)){
				DrawClean(); 
			}else{
				
				callfx(1, fov[0]);	
			}
		}
		num_scr++;
	}

	if (num_scr<screens){
		if(dualdesk==1){
			glViewport (GLWin.width/2, 0, GLWin.width/2, GLWin.height);
		}else{
			glViewport (GLWin.width/2, GLWin.height/2, GLWin.width/2, GLWin.height/2);
		}
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(fov[1], (GLfloat)(aspectwidth)/(GLfloat)(aspectheight), 1, 5000  ); 
	   callfx(2, fov[1]);
	num_scr++;
	}
	
    float tic;
    tic = (float)tickz(0.6);
    angle = tic + angle;    
    
    if (GLWin.doubleBuffered)
    {
        glXSwapBuffers(GLWin.dpy, GLWin.win);
    }
    return True;    
}

typedef struct {
	BOOL KeyDown [256];
} Keyz;	

Keyz Keys;
Bool done;



void bank0switch(int bid){
	if (Keys.KeyDown[XK_z] == True){
	 	bid=bid+10;
	}
	if (Keys.KeyDown[XK_x] == True){
	 	bid=bid+20;
	}
	if (Keys.KeyDown[XK_c] == True){
	 	bid=bid+30;
	}
	if (Keys.KeyDown[XK_v] == True){
	 	bid=bid+40;
	}
	if (Keys.KeyDown[XK_b] == True){
	 	bid=bid+50;
	}
	if (Keys.KeyDown[XK_n] == True){
	 	bid=bid+60;
	}
	if (Keys.KeyDown[XK_m] == True){
	 	bid=bid+70;
	}
	
	if (bank0 != bid){
		fxonoff[bank0]=0;
		//fx[bank0].onoff = 0;
	}
	bank0 = bid;
	bank0avi = 1;
	fxonoff[bid]=1;
	//fx[bid].onoff = 1;
}

void bank1switch(int bid){
	if (Keys.KeyDown[XK_z] == True){
	 	bid=bid+10;
	}
	if (Keys.KeyDown[XK_x] == True){
	 	bid=bid+20;
	}
	if (Keys.KeyDown[XK_c] == True){
	 	bid=bid+30;
	}
	if (Keys.KeyDown[XK_v] == True){
	 	bid=bid+40;
	}
	if (Keys.KeyDown[XK_b] == True){
	 	bid=bid+50;
	}
	if (Keys.KeyDown[XK_n] == True){
	 	bid=bid+60;
	}
	if (Keys.KeyDown[XK_m] == True){
	 	bid=bid+70;
	}
	
	if (bank1 != bid){
		fxonoff[bank1]=0;
		//fx[bank1].onoff = 0;
	}
	bank1 = bid+100;
	bank1avi = 1;
	fxonoff[bid+100]=1;
	//fx[bid+100].onoff = 1;
}


/*keyboard controller*/
void update(void){
 // render keys
 
 if (Keys.KeyDown[XK_Escape]){ 
 	if (Keys.KeyDown[XK_BackSpace] == True){
		done=true;
	}
 }
 
 
 
 if (Keys.KeyDown[XK_F1] == True){
 	rmode=0;
//	Keys.KeyDown[XK_F1] = false;
 }
 if (Keys.KeyDown[XK_F2] == True){
 	rmode=1;
//	Keys.KeyDown[XK_F2] = false;
 }
 if (Keys.KeyDown[XK_F3] == True){
 	rmode=2;
//	Keys.KeyDown[XK_F3] = false;
 }
 if (Keys.KeyDown[XK_F4] == True){
 	rmode=3;
//	Keys.KeyDown[XK_F4] = false;
 }
 
 if (Keys.KeyDown[XK_F8] == True){
 	vision=0;
//	Keys.KeyDown[XK_F8] = false;
 }
 if (Keys.KeyDown[XK_F9] == True){
 	vision=1;
//	Keys.KeyDown[XK_F9] = false;
 }
 if (Keys.KeyDown[XK_F10] == True){
 	vision=2;
//	Keys.KeyDown[XK_F10] = false;
 }
 if (Keys.KeyDown[XK_F11] == True){
 	vision=3;
//	Keys.KeyDown[XK_F11] = false;
 }
 if (Keys.KeyDown[XK_F12] == True){
 	vision=4;
//	Keys.KeyDown[XK_F12] = false;
 }
 
 // camera
 
 if (Keys.KeyDown[XK_1] == True)
 {
	currentcam=0;
	cambeat=1;
//	Keys.KeyDown[XK_1] = false;
 }
  if (Keys.KeyDown[XK_2] == True)
 {
	currentcam=1;
	cambeat=0;
//	Keys.KeyDown[XK_2] = false;
 }
  if (Keys.KeyDown[XK_3] == True)
 {
	currentcam=2;
	cambeat=0;
//	Keys.KeyDown[XK_3] = false;
 }
  if (Keys.KeyDown[XK_4] == True)
 {
	currentcam=3;
	cambeat=0;
//	Keys.KeyDown[XK_4] = false;
 }
  if (Keys.KeyDown[XK_5] == True)
 {
	currentcam=4;
	cambeat=0;
//	Keys.KeyDown[XK_5] = false;
 }
  if (Keys.KeyDown[XK_6] == True)
 {
	currentcam=5;
	cambeat=0;
//	Keys.KeyDown[XK_6] = false;
 }
  if (Keys.KeyDown[XK_7] == True)			
 {
	currentcam=6;
	cambeat=0;
//	Keys.KeyDown[XK_7] = false;
 }
  if (Keys.KeyDown[XK_8] == True)				
 {
	currentcam=7;
	cambeat=0;
//	Keys.KeyDown[XK_8] = false;
 }
  if (Keys.KeyDown[XK_9] == True)
 {
	currentcam=8;
	cambeat=0;
//	Keys.KeyDown[XK_9] = false;
 }
  if (Keys.KeyDown[XK_0] == True)				
 {
	currentcam=9;
	cambeat=0;
//	Keys.KeyDown[XK_0] = false;
 }
 
 /// effect switches
 if (Keys.KeyDown[XK_q] == True){
 	bank0switch(0);
//	Keys.KeyDown[XK_q] = false;
 }
 if (Keys.KeyDown[XK_w] == True){
 	bank0switch(1);
//	Keys.KeyDown[XK_w] = false;
 }
 if (Keys.KeyDown[XK_e] == True){
 	bank0switch(2);
//	Keys.KeyDown[XK_e] = false;
 }
 if (Keys.KeyDown[XK_r] == True){
 	bank0switch(3);
//	Keys.KeyDown[XK_r] = false;
 }
 if (Keys.KeyDown[XK_t] == True){
 	bank0switch(4);
//	Keys.KeyDown[XK_t] = false;
 }
 if (Keys.KeyDown[XK_y] == True){
 	bank0switch(5);
//	Keys.KeyDown[XK_y] = false;
 }
 if (Keys.KeyDown[XK_u] == True){
 	bank0switch(6);
//	Keys.KeyDown[XK_u] = false;
 }
 if (Keys.KeyDown[XK_i] == True){
 	bank0switch(7);
//	Keys.KeyDown[XK_i] = false;
 }
 if (Keys.KeyDown[XK_o] == True){
 	bank0switch(8);
//	Keys.KeyDown[XK_o] = false;
 }
 if (Keys.KeyDown[XK_p] == True){
 	bank0switch(9);
//	Keys.KeyDown[XK_p] = false;
 }
 
 if (Keys.KeyDown[XK_a] == True){
 	bank1switch(0);
//	Keys.KeyDown[XK_a] = false;
 }
 if (Keys.KeyDown[XK_s] == True){
 	bank1switch(1);
//	Keys.KeyDown[XK_s] = false;
 }
 if (Keys.KeyDown[XK_d] == True){
 	bank1switch(2);
//	Keys.KeyDown[XK_d] = false;
 }
 if (Keys.KeyDown[XK_f] == True){
 	bank1switch(3);
//	Keys.KeyDown[XK_f] = false;
 }
 if (Keys.KeyDown[XK_g] == True){
 	bank1switch(4);
//	Keys.KeyDown[XK_g] = false;
 }
 if (Keys.KeyDown[XK_h] == True){
 	bank1switch(5);
//	Keys.KeyDown[XK_h] = false;
 }
 if (Keys.KeyDown[XK_j] == True){
 	bank1switch(6);
//	Keys.KeyDown[XK_j] = false;
 }
 if (Keys.KeyDown[XK_k] == True){
 	bank1switch(7);
//	Keys.KeyDown[XK_k] = false;
 }
 if (Keys.KeyDown[XK_l] == True){
 	bank1switch(8);
//	Keys.KeyDown[XK_l] = false;
 }
 if (Keys.KeyDown[XK_semicolon] == True){
 	bank1switch(9);
//	Keys.KeyDown[XK_semicolon] = false;
 }
 
  // 
 if (Keys.KeyDown[XK_space] == True){
 	
 }
 
}



/* function to release/destroy our resources and restoring the old desktop */
GLvoid killGLWindow(GLvoid)
{
    if (GLWin.ctx)
    {
        if (!glXMakeCurrent(GLWin.dpy, None, NULL))
        {
            printf("Could not release drawing context.\n");
        }
        glXDestroyContext(GLWin.dpy, GLWin.ctx);
        GLWin.ctx = NULL;
    }
    /* switch back to original desktop resolution if we were in fs */
    if (GLWin.fs)
    {
        XF86VidModeSwitchToMode(GLWin.dpy, GLWin.screen, &GLWin.deskMode);
        XF86VidModeSetViewPort(GLWin.dpy, GLWin.screen, 0, 0);
    }
    XCloseDisplay(GLWin.dpy);
}

void destroypbuffer(void)
{
    if (allocatedpbuffer) {
	glXDestroyContext(GLWin.dpy, pbuffercontext);
	glXDestroyPbuffer(GLWin.dpy, glxpbuffer);
    }
}
XVisualInfo *vi;
int setuppbuffer(char **msg, int pwidth, int pheight)
{
    /* off-screen pbuffers have DRAWABLE_TYPE=PBUFFER_BIT,
       X_RENDERABLE=False, GLX_PRESERVED_CONTENTS? */
    
   
    
    int pbconfig[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT,
        GLX_RED_SIZE, 4,
        GLX_GREEN_SIZE, 4,
        GLX_BLUE_SIZE, 4,
        GLX_ALPHA_SIZE, 0, /* XXX Sun Creator3D does not support dst alpha :*/
        GLX_DEPTH_SIZE, 0,
        GLX_STENCIL_SIZE, 0,
        None
    };
    GLXFBConfig *fbconfigs = NULL;
    int nconfigs = 0;
    int i;
    int value;
    int pbattriblist[] = {
	GLX_PBUFFER_WIDTH, pwidth,
	GLX_PBUFFER_HEIGHT, pheight,
	GLX_PRESERVED_CONTENTS, True,
	None
    };

    fbconfigs = glXChooseFBConfig(GLWin.dpy, GLWin.screen, pbconfig, &nconfigs);

    if (fbconfigs == NULL || nconfigs < 1) {
        *msg = "no fbconfigs";
        return -1;
    }

    /* loop through, until we find one that succeeds */
    for(i = 0; i < nconfigs; i++) {
        //printf("fbconfig %d of %d\n", i, nconfigs);
        if (glXGetFBConfigAttrib(GLWin.dpy, fbconfigs[i],
                                 GLX_MAX_PBUFFER_PIXELS, &value) == Success) {
            if (value < width * height) {
                printf("not enough pixels: %d, need %d\n",
                       value, width*height);
                continue;
            }
        }
        if (glXGetFBConfigAttrib(GLWin.dpy, fbconfigs[i],
                                 GLX_MAX_PBUFFER_WIDTH, &value) == Success) {
            if (value < width) {
                printf("width too small: %d, need %d\n", value, width);
                continue;
            }
        }
        if (glXGetFBConfigAttrib(GLWin.dpy, fbconfigs[i],
                                 GLX_MAX_PBUFFER_HEIGHT, &value) == Success) {
            if (value < height) {
                printf("height too small: %d, need %d\n", value, height);
                continue;
            }
        }

        /* if ok, pick this one */
        break;
    }

    if (i >= nconfigs) {
        XFree(fbconfigs);
        *msg = "could not find a suitable fbconfig for pbuffer";
        return -1;
    }

    fbconfig = fbconfigs[i]; /* XXX memory... */
    XFree(fbconfigs);

    /* make window glx drawable */
    glxpbuffer = glXCreatePbuffer(GLWin.dpy, fbconfig, pbattriblist);
    if (glxpbuffer == None) {
	*msg = "glXCreatePbuffer";
	return -1;
    }

    /* create direct-rendering GLX context */
    pbuffercontext = glXCreateContext (GLWin.dpy, vi, GLWin.ctx, True);
    //pbuffercontext = glXCreateNewContext(GLWin.dpy, fbconfig, GLX_RGBA_TYPE, NULL, True);
    if (pbuffercontext == NULL) {
	*msg = "glXCreateNewContext failed";
        return -1;
    }

    if (!glXIsDirect(GLWin.dpy, pbuffercontext))
        printf("falling back to indirect rendering (remote server?)\n");

    /* bind context to glx pbuffer drawable */
   

    allocatedpbuffer = 1;
    return 0;
}



/* this function creates our window and sets it up properly */
Bool createGLWindow(char* title, int width, int height, int bits, Bool fullscreenflag)
{
    
    Colormap cmap;
    int dpyWidth, dpyHeight;
    int i;
    int glxMajorVersion, glxMinorVersion;
    int vidModeMajorVersion, vidModeMinorVersion;
    XF86VidModeModeInfo **modes;
    int modeNum;
    int bestMode;
    Atom wmDelete;
    Window winDummy;
    unsigned int borderDummy;
    
    GLWin.fs = fullscreenflag;
    /* set best mode to current */
    bestMode = 0;
    /* get a connection */
    GLWin.dpy = XOpenDisplay(0);
    GLWin.screen = DefaultScreen(GLWin.dpy);
    XF86VidModeQueryVersion(GLWin.dpy, &vidModeMajorVersion,
        &vidModeMinorVersion);
    printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion,
        vidModeMinorVersion);
    XF86VidModeGetAllModeLines(GLWin.dpy, GLWin.screen, &modeNum, &modes);
    /* save desktop-resolution before switching modes */
    GLWin.deskMode = *modes[0];
    /* look for mode with requested resolution */
    for (i = 0; i < modeNum; i++)
    {
        if ((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height))
        {
            bestMode = i;
        }
    }
    /* get an appropriate visual */
    vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListDbl);
    if (vi == NULL)
    {
        vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListSgl);
        GLWin.doubleBuffered = False;
        printf("[ Singlebuffered ");
    }
    else
    {
        GLWin.doubleBuffered = True;
        printf("[ Doublebuffered ");
    }
    glXQueryVersion(GLWin.dpy, &glxMajorVersion, &glxMinorVersion);
    printf("| glX-Version %d.%d |", glxMajorVersion, glxMinorVersion);
    /* create a GLX context */
    GLWin.ctx = glXCreateContext(GLWin.dpy, vi, 0, GL_TRUE);
    /* create a color map */
    cmap = XCreateColormap(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
        vi->visual, AllocNone);
    GLWin.attr.colormap = cmap;
    GLWin.attr.border_pixel = 0;

    if (GLWin.fs)
    {
        XF86VidModeSwitchToMode(GLWin.dpy, GLWin.screen, modes[bestMode]);
        XF86VidModeSetViewPort(GLWin.dpy, GLWin.screen, 0, 0);
        dpyWidth = modes[bestMode]->hdisplay;
        dpyHeight = modes[bestMode]->vdisplay;
        printf("Res : %dx%d ", dpyWidth, dpyHeight);
        XFree(modes);
    
        /* create a fullscreen window */
        GLWin.attr.override_redirect = True;
        GLWin.attr.event_mask = ExposureMask | ButtonPressMask| ButtonReleaseMask | ButtonMotionMask | KeyReleaseMask | KeyPressMask |         StructureNotifyMask;
        GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
            0, 0, dpyWidth, dpyHeight, 0, vi->depth, InputOutput, vi->visual,
            CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
            &GLWin.attr);
        XWarpPointer(GLWin.dpy, None, GLWin.win, 0, 0, 0, 0, 0, 0);
		XMapRaised(GLWin.dpy, GLWin.win);
        XGrabKeyboard(GLWin.dpy, GLWin.win, True, GrabModeAsync,
            GrabModeAsync, CurrentTime);glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
        XGrabPointer(GLWin.dpy, GLWin.win, True, ButtonPressMask,
            GrabModeAsync, GrabModeAsync, GLWin.win, None, CurrentTime);
    }
    else
    {
        /* create a window in window mode*/
        GLWin.attr.event_mask = ExposureMask | ButtonPressMask| ButtonReleaseMask | ButtonMotionMask | KeyReleaseMask | KeyPressMask |         StructureNotifyMask;
        GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
            0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
            CWBorderPixel | CWColormap | CWEventMask, &GLWin.attr);
        /* only set window title and handle wm_delete_events if in windowed mode */
        wmDelete = XInternAtom(GLWin.dpy, "WM_DELETE_WINDOW", True);
        XSetWMProtocols(GLWin.dpy, GLWin.win, &wmDelete, 1);
        XSetStandardProperties(GLWin.dpy, GLWin.win, title,
            title, None, NULL, 0, NULL);
        XMapRaised(GLWin.dpy, GLWin.win);
    }       
    /* connect the glx-context to the window */
    glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
    XGetGeometry(GLWin.dpy, GLWin.win, &winDummy, &GLWin.x, &GLWin.y,
        &GLWin.width, &GLWin.height, &borderDummy, &GLWin.depth);
    printf(" Depth %d ", GLWin.depth);
    if (glXIsDirect(GLWin.dpy, GLWin.ctx)) 
        printf("| Direct Rendering ]\n");
    else 
        printf("| no Direct Rendering ]\n");
    initGL();
    return True;    
}

// call back for key events

int main(int argc, char **argv)
{
    XEvent event;
    
    loadconf(0);
    done = False;
    if (windowed == 1){
    GLWin.fs = True;
    }else{
    GLWin.fs = False;
    }
    
    
    createGLWindow("OKO T BASE GL", screen_width, screen_height, 24, GLWin.fs);
    char *errmsg;
    if (setuppbuffer(&errmsg, 512, 512) != 0) printf("\\\n failed to create pbuffer: %s\n", errmsg);
    /* wait for events*/ 
    while (!done)
    {
        /* handle the events in the queue */
        while (XPending(GLWin.dpy) > 0)
        {
            XNextEvent(GLWin.dpy, &event);
           
	    switch (event.type)
            {
                case Expose:
	                if (event.xexpose.count != 0)
	                    break;
                    drawGLScene();
         	        break;
	            case ConfigureNotify:
	                    if (((uint)event.xconfigure.width != GLWin.width) || ((uint)event.xconfigure.height != GLWin.height))
	                {
	                    GLWin.width = event.xconfigure.width;
	                    GLWin.height = event.xconfigure.height;
                            resizeGLScene(event.xconfigure.width,
	                        event.xconfigure.height);
	                }
	                break;
                 //this will be for using the mouse as scratcher
                case ButtonPress:
                    
		break;
		case ButtonRelease:
		    
		break;
		case KeyPress :
		{
		   Keys.KeyDown[XLookupKeysym(&event.xkey, 0)] = true;
		  break;
		                	
		}
		
		case KeyRelease :
		{
		//    printf("key released\n");
		    Keys.KeyDown[XLookupKeysym(&event.xkey, 0)] = false;
			break;
		}    
		    
		case ClientMessage:
                    if (*XGetAtomName(GLWin.dpy, event.xclient.message_type) == *"WM_PROTOCOLS")
                    {
                        
                        done = True;
                    }
                    break;
               default:
                    break;
            }
        }
	update();
        drawGLScene();
	
    }
    //pthread_cancel(thr_id);
    //pthread_kill (thr_id, 1);
    killGLWindow();
    exit (0);
}
