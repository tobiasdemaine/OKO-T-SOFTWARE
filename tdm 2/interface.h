#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include "glx_base.h"

void setup_interface(void);
void draw_canvases(void);
void open_channel_canvas(int mychannel);
void close_channel_canvas(int mychannel);
GLuint get_channel_texture(int mychannel);
float get_video_mix_slide();
#endif
