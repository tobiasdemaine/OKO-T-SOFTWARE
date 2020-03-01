#include "glx_base.h"
BOOL initGLScene(void)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glFlush();
	/* load alsa audio thread/s */
	start_audio();
	/* load the media libraries */	
	song_load_media_libraries();
	printf("after the media libs");
	/* setup the interface */
	setup_interface();
	
	return True;
}

void drawGLScene(void)
{
	/* process sound */
	sound_process();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	/*execute channel 1 song*/
	exec_channel_1_song();
	/*execute channel 2 song*/
	exec_channel_2_song();
	/*execute MIX */
	exec_channel_mix();
	/*draw canvases*/
	draw_canvases();
	/*draw the GUI*/
	gui_exec();

	//draw_canvases();
}

void updateGLScene(void)
{
}

void cleanGLScene(void)
{
}

int main(void)
{
	createGLWindow("OKO T", getwinwidth(), getwinheight(), 24, false);
	initGLScene();
	runGLScene();
	cleanGLScene();
	killGLWindow();
	return 0;
}
