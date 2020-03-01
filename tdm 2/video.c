#include "video.h"

mediastream av_library[10000]; /* 10000 possible media clips*/
int media_count=0;

int stream_create(char *file){  /* we will start a thread here */
	media_count++;
	av_library[media_count].id = avm::CreateReadFile(file);
	av_library[media_count].current_frame=0;
	av_library[media_count].speed=1;
	av_library[media_count].avistream = av_library[media_count].id->GetStream(0, avm::IReadStream::Video );
	glGenTextures(1, &av_library[media_count].frame_texture);
        return media_count; 
}
void stream_play(int stream){
	av_library[stream].avistream->StartStreaming();
	av_library[stream].avistream->Seek(av_library[stream].current_frame);
	av_library[stream].streaminfo = av_library[stream].avistream->GetStreamInfo();
	av_library[stream].width = av_library[stream].streaminfo->GetVideoWidth();
	av_library[stream].height = av_library[stream].streaminfo->GetVideoHeight();
	av_library[stream].stream_fps = av_library[stream].streaminfo->GetFps();
}

void stream_stop(int stream){
	av_library[stream].avistream->StopStreaming();
}

void stream_seek(int stream, int frame){
	av_library[stream].current_frame = frame;
}

void stream_rewind(int stream){
	/*av_library[stream].avistream->Seek(0);*/
	av_library[stream].next=0;
	stream_get_frame(stream);
	/*stream_play(stream);*/
}

void stream_rewind_stop(int stream){
	/*av_library[stream].avistream->Seek(0);*/
	av_library[stream].next=0;
	stream_get_frame(stream);
	av_library[stream].avistream->StopStreaming();
}

void stream_set_speed(int stream,int speed){
	av_library[stream].speed = speed;
}

int stream_is_streaming(int stream){
	if(av_library[stream].avistream->IsStreaming()){
		return 1;
	}else{
		return 0;
	}
}
int stream_get_position(int stream){
	return av_library[stream].current_frame;
}
int stream_get_speed(int stream){
	return av_library[stream].speed;
}

void stream_get_frame(int stream){
	/* we do some fancy timer stuff here */
	if(av_library[stream].avistream->IsStreaming()){
		av_library[stream].next+= getMS();	
		av_library[stream].current_frame=int(av_library[stream].next/((int)(1000/av_library[stream].speed)*av_library[stream].avistream->GetFrameTime()));
		av_library[stream].avistream->Seek(av_library[stream].current_frame);
		CImage* vimage = av_library[stream].avistream->GetFrame(true);
		if (!av_library[stream].avistream->Eof() && vimage) {
			av_library[stream].current_frame = av_library[stream].avistream->GetPos();
			CImage* rgbci = new CImage(vimage, 24);
			glBindTexture(GL_TEXTURE_RECTANGLE_NV, av_library[stream].frame_texture);  
			glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, av_library[stream].width, av_library[stream].height, 0,  GL_BGR, GL_UNSIGNED_BYTE,  rgbci->At(0,0));
			rgbci->Release();
			vimage->Release();
		} else {
			av_library[stream].avistream->Seek(0);  /* back to start to stream */
			av_library[stream].next=0;
		}
	}
}

void stream_set_rgba(int stream, float r, float g, float b, float a){
	av_library[stream].r = r;
	av_library[stream].g = g;
	av_library[stream].b = b;
	av_library[stream].a = a;
}

void stream_display(int stream, int swidth, int sheight, int sx, int sy){
	stream_get_frame(stream);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);	
	glMatrixMode(GL_PROJECTION);	
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, getwinwidth(), 0, getwinheight(),-1,5000);
	glMatrixMode(GL_MODELVIEW);
	glColor4f(av_library[stream].r, av_library[stream].g, av_library[stream].b, av_library[stream].a);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   /* will have to make sure the blend is set externally */
	glEnable(GL_BLEND);
	glPushMatrix();	
	glLoadIdentity();
	glTranslatef(sx, getwinheight()-sy-sheight,0);
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, av_library[stream].frame_texture);
	glBegin(GL_QUADS);
		glTexCoord2f(av_library[stream].width, av_library[stream].height);  
		glVertex2f(swidth,0);
		glTexCoord2f(0, av_library[stream].height);  
		glVertex2f(0,0);		
		glTexCoord2f(0, 0);  
		glVertex2f(0, sheight);
		glTexCoord2f(av_library[stream].width, 0);
		glVertex2f(swidth, sheight); 
		
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);		
	glDisable(GL_TEXTURE_RECTANGLE_NV);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();			
	glMatrixMode(GL_MODELVIEW);	
	glPopMatrix();
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}
