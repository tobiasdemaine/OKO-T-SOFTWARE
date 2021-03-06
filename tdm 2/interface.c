#include "interface.h"
int default_font;
int canvas_channel_1, canvas_channel_2, canvas_channel_mix;
int bottom_left_video_container, bottom_left_video_shadow;
int bottom_right_video_container, bottom_right_video_shadow;
int mix_controls_container, mix_controls_video_slider, mix_channel_1_button, mix_channel_2_button;
int left_edit_button, right_edit_button, left_rewind, left_pause, left_play, right_rewind, right_pause, right_play;;
int right_open_button, right_save_button, right_new_button;
int left_open_button, left_save_button, left_new_button;
int select_song_container, select_song_dialogue, select_song_close;
int select_song[60];
int current_channel;
int editing_song;
int editing_layer;
int editing_frame;
int editing_object;
int editing_object_real;
int editing_song_real;
int layer_container, layer_top, layer_label, layer_new, layer_delete;
int layer_view[20];
int layer_view_label[20];
int layer_view_spanner[20];
int fc_container, fc_back, fc_frame, fc_object, fc_frame_new, fc_frame_delete, fc_obj_new, fc_obj_delete, fc_frame_drop, fc_obj_drop;
int fc_obj_select[30];
int fc_obj_container, fc_obj_dia, fc_obj_close;
int new_obj_container, new_obj_back, new_obj_close, new_obj_1, new_obj_2, new_obj_3, new_obj_4, new_obj_5, new_obj_6, new_obj_7, new_obj_8;
int error_container, error_back;
int vlib_container, vlib_back, vlib_close;
int vlib_select[30];
int mlib_container, mlib_back, mlib_close;
int mlib_select[30];
int tlib_container, tlib_back, tlib_close;
int tlib_select[30];
int alib_container, alib_back, alib_close;
int alib_select[30];
int colour_container, colour_back, red, green, blue, alpha;
int posrot_container, posrot_back, posrot_x, posrot_y, posrot_z, posrot_rx, posrot_ry, posrot_rz, posrot_degree, posrot_auto, posrot_sx, posrot_sy, posrot_sz;
int audio_container, audio_back, audio_fft_switch, audio_fft_slot, audio_fft_multiply, audio_volume_switch, audio_volume_multiply, audio_beat_render_switch, audio_beat_render_minus, audio_beat_render_plus, audio_scale;
int texture_container, texture_back, texture_button, texture_label, render_solid, render_wire;
int texuselib=0;
int obslected=0;
int camera_container, camera_back;
int camerasel[8];
int sc_container, sc_1, sc_2, sc_3, sc_4;

void open_editors(void);
void close_editors(void){
	/*closes all editor windows*/
	set_object_visible(colour_container, 0);
	set_object_visible(posrot_container, 0);
	set_object_visible(audio_container, 0);	
	set_object_visible(texture_container, 0);	
	set_object_visible(camera_container, 0);
}
/* interface auto build functions */
void build_song_list(void){
	int scount = song_get_count();
	for(int i=0;i<60;i++){
		if(i<scount){
			set_label_text(select_song[i], song_get_name_by_slot(i));
			set_object_visible(select_song[i], 1);
		}else{
			set_object_visible(select_song[i], 0);
		}
	}
}

void save_all(void){
	song_system_save();
}

void sc_push(void){
	if(get_last_object_depress()==sc_1){
		set_output_render(1);
	}
	if(get_last_object_depress()==sc_2){
		set_output_render(2);
	}
	if(get_last_object_depress()==sc_3){
		set_output_render(4);
	}
	if(get_last_object_depress()==sc_4){
		set_output_render(3);
	}
}


void build_object_list(void){
	int object_count = song_get_object_count(song_get_from_channel(current_channel), editing_layer, editing_frame);
	for(int i=0;i<30;i++){
		if(i<object_count){	
			set_label_text(fc_obj_select[i], song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, i));
			set_object_visible(fc_obj_select[i], 1);	
		}else{
			set_object_visible(fc_obj_select[i], 0);	
		}
	}
} 

void rewind_song_channel_1(void){
	song_rewind(1);
}

void pause_song_channel_1(void){
	song_pause(1);
}

void play_song_channel_1(void){
	song_play(1);
}

void cue_song_channel_1(void){

}
void set_title(void){
	song_set_title(get_song_slot_from_id(song_get_from_channel(current_channel)), get_label_text(layer_label));
}
void rewind_song_channel_2(void){
	song_rewind(2);
}

void pause_song_channel_2(void){
	song_pause(2);
}

void play_song_channel_2(void){
	song_play(2);
}

void cue_song_channel_2(void){

}

void do_render_solid(void){
	if(get_object_state(render_solid)==3){
		song_set_object_render(editing_song_real, editing_layer, editing_object_real, 0);
	}
	open_editors();
}

void do_render_wire(void){
	if(get_object_state(render_wire)==3){
		song_set_object_render(editing_song_real, editing_layer, editing_object_real, 1);
	}
	open_editors();
}

void do_camera(void){
	int set_camera = get_last_object_release()-camerasel[0];
	song_set_object_camera_id(editing_song_real, editing_layer, editing_object_real, set_camera);
	open_editors();
}
void get_texture(void){
	texuselib=1;
	int scount = song_get_texture_lib_count();
	for(int i=0;i<30;i++){
		if(i<scount){
			set_label_text(tlib_select[i], song_get_texture_name_by_slot(i));
			set_object_visible(tlib_select[i], 1);
		}else{
			set_object_visible(tlib_select[i], 0);
		}
	}
	set_object_visible(tlib_container, 1);
	close_editors();
}

void set_colour(void){
	song_set_object_colour(editing_song_real, editing_layer, editing_object_real, get_slider_value(red), get_slider_value(green), get_slider_value(blue), get_slider_value(alpha));
}

void set_position(void){
	song_set_object_postion(editing_song_real, editing_layer, editing_object_real, get_label_text_as_float(posrot_x), get_label_text_as_float(posrot_y), get_label_text_as_float(posrot_z));
	open_editors();
}
void set_rotation(void){
	int rauto=0;
	float rx=0;
	float ry=0;
	float rz=0;
	if(get_object_state(posrot_rx)==3){
		rx=1;
	}
	if(get_object_state(posrot_ry)==3){
		ry=1;
	}
	if(get_object_state(posrot_rz)==3){
		rz=1;
	}
	if(get_object_state(posrot_auto)==3){
		rauto=1;
		
	}
	song_set_object_rotation(editing_song_real, editing_layer, editing_object_real,  rx, ry, rz, get_label_text_as_float(posrot_degree), rauto);
	printf("%f -- %f -- %f -- %f -- %i\n", rx, ry, rz, get_label_text_as_float(posrot_degree), rauto);
	open_editors();
}
void set_scale(void){
	song_set_object_scale(editing_song_real, editing_layer, editing_object_real, get_label_text_as_float(posrot_sx), get_label_text_as_float(posrot_sy), get_label_text_as_float(posrot_sz));
	open_editors();
}

void set_audio(void){
	if(get_object_state(audio_scale)!=3){
		set_audio_scale_type(editing_song_real, editing_layer, editing_object_real, 0);
	}else{
		set_audio_scale_type(editing_song_real, editing_layer, editing_object_real, 2);
	}
	open_editors();
}
void set_audio_fft(void){
	if(get_object_state(audio_scale)==3){
		set_audio_scale_type(editing_song_real, editing_layer, editing_object_real, 1);
		set_scale_from_fft(editing_song_real, editing_layer, editing_object_real,get_label_text_as_int(audio_fft_slot));
		set_scale_audio_multiplier(editing_song_real, editing_layer, editing_object_real, get_label_text_as_float(audio_fft_multiply));
	}
	open_editors();
}
void set_audio_volume(void){
	if(get_object_state(audio_scale)==3){
		set_audio_scale_type(editing_song_real, editing_layer, editing_object_real, 2);
		set_scale_audio_multiplier(editing_song_real, editing_layer, editing_object_real, get_label_text_as_float(audio_volume_multiply));
		open_editors();
	}
	open_editors();
}
void set_audio_render(void){
	if(get_object_state(audio_beat_render_switch)==3){
		set_beat_render(editing_song_real, editing_layer, editing_object_real, 2);
	}else{
		set_beat_render(editing_song_real, editing_layer, editing_object_real, 0);
	}
	open_editors();
}
void set_audio_render_plus(void){
	if(get_object_state(audio_beat_render_plus)==3){
			set_beat_render(editing_song_real, editing_layer, editing_object_real, 2);
	}
	open_editors();
}
void set_audio_render_minus(void){
	if(get_object_state(audio_beat_render_minus)==3){
			set_beat_render(editing_song_real, editing_layer, editing_object_real, 1);
	}
	open_editors();
}



void open_editors(void){
	obslected=1;
	editing_song_real = get_song_slot_from_id(song_get_from_channel(current_channel));
	editing_object_real = song_get_object_frame_from_obj_slot(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object);
	int objtypetest = song_get_object_type(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object);
	if(objtypetest<4){ /*video editors*/
		/* set colour widget */
		set_object_visible(colour_container, 1);
		set_slider_value(red, song_get_object_colour_r(editing_song_real, editing_layer, editing_object_real));
		set_slider_value(green, song_get_object_colour_g(editing_song_real, editing_layer, editing_object_real));
		set_slider_value(blue, song_get_object_colour_b(editing_song_real, editing_layer, editing_object_real));
		set_slider_value(alpha, song_get_object_colour_a(editing_song_real, editing_layer, editing_object_real));
		/* set pos_spin_scale */
		set_object_visible(posrot_container, 1);
		char *buf0=(char *)calloc(5 , sizeof(char));
		sprintf(buf0, "%f", song_get_object_position_x(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_x, buf0);
		char *buf1=(char *)calloc(5 , sizeof(char));
		sprintf(buf1, "%f", song_get_object_position_y(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_y, buf1);
		char *buf2=(char *)calloc(5 , sizeof(char));
		sprintf(buf2, "%f", song_get_object_position_z(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_z, buf2);
		
		if( song_get_object_rotation_x(editing_song_real, editing_layer, editing_object_real)>0){
			set_object_state(posrot_rx, 3);
		}else{
			set_object_state(posrot_rx, 0);
		}
		if( song_get_object_rotation_y(editing_song_real, editing_layer, editing_object_real)>0){
			set_object_state(posrot_ry, 3);
		}else{
			set_object_state(posrot_ry, 0);
		}
		if( song_get_object_rotation_z(editing_song_real, editing_layer, editing_object_real)>0){
			set_object_state(posrot_rz, 3);
		}else{
			set_object_state(posrot_rz, 0);
		}
		if( song_get_object_rotation_auto(editing_song_real, editing_layer, editing_object_real)==1){
			set_object_state(posrot_auto, 3);
		}else{
			set_object_state(posrot_auto, 0);
		}
		char *buf3=(char *)calloc(5 , sizeof(char));
		sprintf(buf3, "%f", song_get_object_rotation_degree(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_degree, buf3);
		char *buf4=(char *)calloc(5 , sizeof(char));
		sprintf(buf4, "%f", song_get_object_scale_x(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_sx, buf4);
		char *buf5=(char *)calloc(5 , sizeof(char));
		sprintf(buf5, "%f", song_get_object_scale_y(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_sy, buf5);
		char *buf6=(char *)calloc(5 , sizeof(char));
		sprintf(buf6, "%f", song_get_object_scale_z(editing_song_real, editing_layer, editing_object_real));
		set_label_text(posrot_sz, buf6);
		
		set_object_visible(audio_container, 1);
		if(get_audio_scale_type(editing_song_real, editing_layer, editing_object_real)==1){
			set_object_state(audio_scale, 3);
			set_object_state(audio_fft_switch, 3);
			set_object_state(audio_volume_switch, 0);
			set_label_text(audio_volume_multiply, "");
			char *buf7=(char *)calloc(5 , sizeof(char));
			sprintf(buf7, "%d", get_scale_from_fft(editing_song_real, editing_layer, editing_object_real));
			set_label_text(audio_fft_slot, buf7);
			char *buf8=(char *)calloc(5 , sizeof(char));
			sprintf(buf8, "%f", get_scale_audio_multiplier(editing_song_real, editing_layer, editing_object_real));
			set_label_text(audio_fft_multiply, buf8);
		}else if(get_audio_scale_type(editing_song_real, editing_layer, editing_object_real)==2){
			set_object_state(audio_scale, 3);
			set_object_state(audio_fft_switch, 0);
			set_object_state(audio_volume_switch, 3);
			set_label_text(audio_fft_slot, "");
			set_label_text(audio_fft_multiply, "");
			char *buf7=(char *)calloc(5, sizeof(char));
			sprintf(buf7, "%f", get_scale_audio_multiplier(editing_song_real, editing_layer, editing_object_real));
			set_label_text(audio_volume_multiply, buf7);
		}else{
			set_object_state(audio_scale, 0);
			set_object_state(audio_fft_switch, 0);
			set_object_state(audio_volume_switch, 0);
			set_label_text(audio_fft_slot, "");
			set_label_text(audio_fft_multiply, "");
			set_label_text(audio_volume_multiply, "");
		}
		if(get_beat_render(editing_song_real, editing_layer, editing_object_real)==2){
			set_object_state(audio_beat_render_switch, 3);
			set_object_state(audio_beat_render_minus, 0);
			set_object_state(audio_beat_render_plus, 3);
		}else if(get_beat_render(editing_song_real, editing_layer, editing_object_real)==1){
			set_object_state(audio_beat_render_switch, 3);
			set_object_state(audio_beat_render_minus, 3);
			set_object_state(audio_beat_render_plus, 0);
		}else{
			set_object_state(audio_beat_render_switch, 0);
			set_object_state(audio_beat_render_minus, 0);
			set_object_state(audio_beat_render_plus, 0);
		}
	}
	if(objtypetest==2){
		set_object_visible(texture_container, 1);
		if(song_get_object_render(editing_song_real, editing_layer, editing_object_real)==1){
			set_object_state(render_wire, 0);
			set_object_state(render_solid, 3);
		}else{
			set_object_state(render_wire, 3);
			set_object_state(render_solid, 0);
		}
	}
	if(objtypetest==5){
		set_object_visible(camera_container, 1);
		for(int i=0;i<8;i++){
			if(song_get_object_camera_id(editing_song_real, editing_layer, editing_object_real)==i){
				set_object_state(camerasel[i], 3);
			}else{
				set_object_state(camerasel[i], 0);
			}
		}
	}
}

void lib_close(void){
	if(texuselib==1){
		open_editors();
	}
	set_object_visible(vlib_container, 0);
	set_object_visible(mlib_container, 0);
	set_object_visible(tlib_container, 0);
	set_object_visible(alib_container, 0);
	texuselib=0;
}

void alib_selecta(void){
	set_object_visible(alib_container, 0);
	int mydb_id = song_get_audio_id_from_slot(get_last_object_depress()-alib_select[0]);	
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 4, mydb_id);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	build_object_list();
}

void tlib_selecta(void){
	int mydb_id;
	if(texuselib==1){
		set_object_visible(tlib_container, 0);
		mydb_id = song_get_texture_id_from_slot(get_last_object_depress()-tlib_select[0]);
		/* set the texture of the mesh to this lib*/
		song_set_object_texture(editing_song_real, editing_layer, editing_object_real, mydb_id);
		texuselib=0;
		open_editors();
	}else{
		set_object_visible(tlib_container, 0);
		mydb_id = song_get_texture_id_from_slot(get_last_object_depress()-tlib_select[0]);	
		int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 3, mydb_id);
		editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
		set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
		build_object_list();
		open_editors();
	}
}

void mlib_selecta(void){
	set_object_visible(mlib_container, 0);
	int mydb_id = song_get_mesh_id_from_slot(get_last_object_depress()-mlib_select[0]);	
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 2, mydb_id);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	build_object_list();
	editing_song_real = get_song_slot_from_id(song_get_from_channel(current_channel));
	editing_object_real = song_get_object_frame_from_obj_slot(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object);
	song_set_object_colour(editing_song_real, editing_layer, editing_object_real, 1, 1, 1, 1);
	song_set_object_scale(editing_song_real, editing_layer, editing_object_real, 1, 1, 1);
	open_editors();
}

void vlib_selecta(void){
	set_object_visible(vlib_container, 0);
	int mydb_id = song_get_vid_id_from_slot(get_last_object_depress()-vlib_select[0]);	
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 1, mydb_id);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	build_object_list();
	editing_song_real = get_song_slot_from_id(song_get_from_channel(current_channel));
	editing_object_real = song_get_object_frame_from_obj_slot(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object);
	song_set_object_colour(editing_song_real, editing_layer, editing_object_real, 1, 1, 1, 1);
	song_set_object_width_height(editing_song_real, editing_layer, editing_object_real, getwinwidth(), getwinheight());
	open_editors();

}

void open_new_obj_1(void){
	set_object_visible(new_obj_container, 0);
	set_object_visible(vlib_container, 1);
	int scount = song_get_video_lib_count();
	for(int i=0;i<30;i++){
		if(i<scount){
			set_label_text(vlib_select[i], song_get_video_name_by_slot(i));
			set_object_visible(vlib_select[i], 1);
		}else{
			set_object_visible(vlib_select[i], 0);
		}
	}
}

void open_new_obj_2(void){
	set_object_visible(new_obj_container, 0);
	set_object_visible(mlib_container, 1);
	int scount = song_get_mesh_lib_count();
	for(int i=0;i<30;i++){
		if(i<scount){
			set_label_text(mlib_select[i], song_get_mesh_name_by_slot(i));
			set_object_visible(mlib_select[i], 1);
		}else{
			set_object_visible(mlib_select[i], 0);
		}
	}
}

void open_new_obj_3(void){
	set_object_visible(new_obj_container, 0);
	set_object_visible(alib_container, 1);
	int scount = song_get_audio_lib_count();
	for(int i=0;i<30;i++){
		if(i<scount){
			set_label_text(alib_select[i], song_get_audio_name_by_slot(i));
			set_object_visible(alib_select[i], 1);
		}else{
			set_object_visible(alib_select[i], 0);
		}
	}
}

void open_new_obj_4(void){
	set_object_visible(new_obj_container, 0);
	set_object_visible(tlib_container, 1);
	int scount = song_get_texture_lib_count();
	for(int i=0;i<30;i++){
		if(i<scount){
			set_label_text(tlib_select[i], song_get_texture_name_by_slot(i));
			set_object_visible(tlib_select[i], 1);
		}else{
			set_object_visible(tlib_select[i], 0);
		}
	}
}

void open_new_obj_5(void){
	set_object_visible(new_obj_container, 0);
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 5, 0);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	build_object_list();
}

void open_new_obj_6(void){
	set_object_visible(new_obj_container, 0);
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 6, 0);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	build_object_list();
}

void open_new_obj_7(void){
	set_object_visible(new_obj_container, 0);
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 7, 0);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	build_object_list();
}

void open_new_obj_8(void){
	set_object_visible(new_obj_container, 0);
	int new_obj = song_create_new_frame_obj(song_get_from_channel(current_channel), editing_layer, editing_frame, 8, 0);
	editing_object = song_get_object_slot_from_frame_id(song_get_from_channel(current_channel), editing_layer, new_obj);
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	/* set the master the automatically to temporarily */
	build_object_list();
}

void close_error(void){
	set_object_visible(error_container, 0);
}

void obj_delete(void){
	if(obslected==1){
		song_delete_frame_object(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object);
		set_label_text(fc_object, "");
		build_object_list();
		close_editors();
		obslected=0;
	}else{
		set_object_visible(error_container, 1);
	}
}

void obj_select_new(void){
	set_object_visible(new_obj_container, 1);
	close_editors();
}

void close_new_obj(void){
	set_object_visible(new_obj_container, 0);
}

void switch_to_channel_1(void){
	set_slider_value(mix_controls_video_slider , 0.0);
}
void switch_to_channel_2(void){
	set_slider_value(mix_controls_video_slider , 1.0);
}
void close_song_select(void){
	set_object_visible(select_song_container, 0);
}

void close_obj_select(void){
	set_object_visible(fc_obj_container, 0);
}

void select_object(void){
	set_object_visible(fc_obj_container, 0);
	editing_object = get_last_object_depress()-fc_obj_select[0];
	set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, editing_object));
	open_editors();
}

void obj_select(void){
	set_object_visible(fc_obj_container, 1);
	close_editors();
}


void show_frame_editor(int frame){
	set_object_visible(fc_container, 1);
	editing_frame = 1;
	/* todo populate frame list */
	
	char *buf=(char *)calloc(5, sizeof(char));
	sprintf(buf, "%i", editing_frame);

	set_label_text(fc_frame, buf);
	int object_count = song_get_object_count(song_get_from_channel(current_channel), editing_layer, editing_frame);
	if (object_count>0){
		set_label_text(fc_object, song_get_object_title(song_get_from_channel(current_channel), editing_layer, editing_frame, 0));
	}
	build_object_list();
}

void select_layer(void){
	printf("%i editing layer \n",get_last_object_depress()-layer_view[0]);
	editing_layer = get_last_object_depress()-layer_view[0];
	for(int i=0;i<15;i++){
		if(i==editing_layer){
			set_object_visible(layer_view_spanner[i], 1);
		}else{
			set_object_visible(layer_view_spanner[i], 0);
		}
	}
	show_frame_editor(1);
	close_editors();
}

void load_layer_info(int mychannel){
	editing_song = song_get_from_channel(mychannel);
	set_label_text(layer_label, song_get_name_by_id(song_get_from_channel(mychannel)));
	int layercount = song_get_layercount(song_get_from_channel(mychannel));
	for(int i=0;i<15;i++){
		if(i<layercount){
			set_label_text(layer_view_label[i], song_get_layer_name(song_get_from_channel(mychannel),i));
			set_object_visible(layer_view[i], 1);
			set_object_visible(layer_view_label[i], 1);
		}else{
			set_object_visible(layer_view[i], 0);
			set_object_visible(layer_view_label[i], 0);
		}
		set_object_visible(layer_view_spanner[i], 0);

	}
	
}
int edit_channel=0;

void new_layer(void){
	song_new_layer(editing_song);
	if(get_object_visible(right_save_button)==1){
		load_layer_info(2);
	}else{
		load_layer_info(1);
	}
	close_editors();
}


void delete_layer(void){
	if(get_object_visible(layer_view_spanner[editing_layer])==1){
		song_delete_layer(editing_song, editing_layer);
		if(get_object_visible(right_save_button)==1){
			load_layer_info(2);
		}else{
			load_layer_info(1);
		}
		set_object_visible(layer_view_spanner[editing_layer], 0);
	}
	close_editors();
}
void new_song_channel_1(void){
	set_channel_song(1, song_new());
	edit_channel=1;
	current_channel=1;
	set_object_visible(layer_container, 1);
	set_object_visible(right_open_button, 0);
	set_object_visible(left_open_button, 0);
	set_object_visible(right_save_button, 0);
	set_object_visible(right_new_button, 0);
	set_object_visible(left_new_button, 0);
	set_object_visible(right_edit_button, 0);
	/*load layer editor configs*/
	load_layer_info(1);
}
void new_song_channel_2(void){


}
void edit_song_channel_1(void){
	/* test if song exists to do*/
	if(song_get_from_channel(1)!=0){
		if(edit_channel==0){
			edit_channel=1;
			current_channel=1;
			set_object_visible(layer_container, 1);
			set_object_visible(right_open_button, 0);
			set_object_visible(left_open_button, 0);
			set_object_visible(right_save_button, 0);
			set_object_visible(right_new_button, 0);
			set_object_visible(left_new_button, 0);
			set_object_visible(right_edit_button, 0);
			/*load layer editor configs*/
			load_layer_info(1);
		}else{
			edit_channel=0;
			set_object_visible(right_open_button, 1);
			set_object_visible(left_open_button, 1);
			set_object_visible(right_save_button, 1);
			set_object_visible(right_new_button, 1);
			set_object_visible(left_new_button, 1);
			set_object_visible(right_edit_button, 1);
			set_object_visible(layer_container, 0);
			set_object_visible(fc_container, 0);
			close_editors();
		}
	}
}

void edit_song_channel_2(void){
	if(song_get_from_channel(2)!=0){
		if(edit_channel==0){
			edit_channel=1;
			current_channel=2;
			set_object_visible(left_open_button, 0);
			set_object_visible(right_open_button, 0);
			set_object_visible(right_new_button, 0);
			set_object_visible(left_save_button, 0);
			set_object_visible(left_new_button, 0);
			set_object_visible(left_edit_button, 0);
			set_object_visible(layer_container, 1);
			/*load layer editor configs*/
			load_layer_info(2);
		}else{
			edit_channel=0;
			set_object_visible(right_open_button, 1);
			set_object_visible(right_new_button, 1);
			set_object_visible(left_open_button, 1);
			set_object_visible(left_save_button, 1);
			set_object_visible(left_new_button, 1);
			set_object_visible(left_edit_button, 1);
			set_object_visible(layer_container, 0);
			set_object_visible(fc_container, 0);
		}
	}
}

void open_channel_1_song_select(void){
	current_channel=1;
	build_song_list();
	set_object_visible(select_song_container, 1);
}

void open_channel_2_song_select(void){
	current_channel=2;
	build_song_list();
	set_object_visible(select_song_container, 1);
}


void select_song_for_channel(void){
	if((get_last_object_depress()>=select_song[0])&&(get_last_object_depress()<=select_song[29])){
		set_channel_song(current_channel, get_song_id_from_slot(get_last_object_depress()-select_song[0]));
		set_object_visible(select_song_container, 0);
	}
}
/*end ui button functions*/

void setup_interface(void){
	canvas_channel_1 = create_canvas(800, 600, 16, 9, 80);

	canvas_channel_2 = create_canvas(800, 600, 16, 9, 80);

	canvas_channel_mix = create_canvas(800, 600, 16, 9, 80);

	default_font = font_create("interface/font.tga");
	/*create background for bottom controls*/

	/*create channel 1 song controls*/
	bottom_left_video_container = container_create(0, getwinheight()-215, 350, 215, 1);
	bottom_left_video_shadow = image_create(bottom_left_video_container, 0,39, 234, 176, 1, "interface/video_drop_shadow.tga");
	left_open_button = button_create(bottom_left_video_container, "interface/open_button_hover.tga", "interface/open_button.tga", "interface/open_button_hover.tga",80, 8, 49, 16, 0, 1, "open 1", 0);
	set_depress_function(left_open_button, &open_channel_1_song_select);
	left_save_button = button_create(bottom_left_video_container, "interface/save_button_hover.tga", "interface/save_button.tga", "interface/save_button_hover.tga",129, 8, 47, 16, 0, 1, "save 1", 0);
	set_depress_function(left_save_button, &save_all);
	left_new_button = button_create(bottom_left_video_container, "interface/new_button_hover.tga", "interface/new_button.tga", "interface/new_button_hover.tga",176, 8, 49, 16, 0, 1, "open 1", 0);
	set_depress_function(left_new_button, &new_song_channel_1);
	left_edit_button = button_create(bottom_left_video_container, "interface/edit_button_hover.tga", "interface/edit_button.tga", "interface/edit_button_hover.tga",8, 0, 30, 30, 0, 1, "open 1", 0);
	set_depress_function(left_edit_button, &edit_song_channel_1);
	left_rewind = button_create(bottom_left_video_container, "interface/rewind_over.tga", "interface/rewind.tga", "interface/rewind_over.tga",135, 24, 30, 30, 0, 1, "open 1", 0);
	set_depress_function(left_rewind, &rewind_song_channel_1);
	left_pause = button_create(bottom_left_video_container, "interface/pause_over.tga", "interface/pause.tga", "interface/pause_over.tga",165, 24, 30, 30, 0, 1, "open 1", 0);
	set_depress_function(left_pause, &pause_song_channel_1);
	left_play = button_create(bottom_left_video_container, "interface/play_over.tga", "interface/play.tga", "interface/play_over.tga",196, 24, 29, 30, 0, 1, "open 1", 0);
	set_depress_function(left_play, &play_song_channel_1);

	/*create channel 2 song controls*/
	bottom_right_video_container = container_create((geteditorwidth()-350), getwinheight()-215, 350, 215, 1);
	bottom_right_video_shadow = image_create(bottom_right_video_container, 116,39, 234, 176, 1, "interface/video_drop_shadow.tga");
	right_open_button = button_create(bottom_right_video_container, "interface/open_button_hover.tga", "interface/open_button.tga", "interface/open_button_hover.tga",124, 8, 49, 16, 0, 1, "open 1", 0);
	set_depress_function(right_open_button, &open_channel_2_song_select);
	right_save_button = button_create(bottom_right_video_container, "interface/save_button_hover.tga", "interface/save_button.tga", "interface/save_button_hover.tga",173, 8, 47, 16, 0, 1, "save 1", 0);
	set_depress_function(right_save_button, &save_all);
	right_new_button = button_create(bottom_right_video_container, "interface/new_button_hover.tga", "interface/new_button.tga", "interface/new_button_hover.tga",220, 8, 49, 16, 0, 1, "open 1", 0);
	set_depress_function(right_new_button, &new_song_channel_2);
	right_edit_button = button_create(bottom_right_video_container, "interface/edit_button_hover.tga", "interface/edit_button.tga", "interface/edit_button_hover.tga",312, 0, 30, 30, 0, 1, "open 1", 0);
	set_depress_function(right_edit_button, &edit_song_channel_2);
	

	/*create centre controller*/
	mix_controls_container = container_create((geteditorwidth()/2)-150, getwinheight()-42, 300, 43, 1);
	mix_controls_video_slider = horizontal_slider_create(mix_controls_container, "interface/mix_slide_button.tga", "interface/mix_slide_button_hover.tga", 30, 42,"interface/mix_slide_base.tga", 200, 42, 50, 0, 0, 1, 1);
	mix_channel_1_button = button_create(mix_controls_container, "interface/default_button_hover.tga", "interface/default_button.tga", "interface/default_button_hover.tga",0, 8, 46, 21, 0, 1, "channel 1", 0);
	set_depress_function( mix_channel_1_button, &switch_to_channel_1);
	mix_channel_2_button = button_create(mix_controls_container, "interface/default_button_hover.tga", "interface/default_button.tga", "interface/default_button_hover.tga",254, 8, 46, 21, 0, 1, "channel 2", 0);
	set_depress_function( mix_channel_2_button, &switch_to_channel_2);
	
	sc_container = container_create((geteditorwidth()/2)-145, getwinheight()-102, 250, 500, 1);
	sc_1 = button_create(sc_container, "interface/screen1_over.tga", "interface/screen1.tga", "interface/screen1_over.tga",0, 0, 66, 60, 0, 1, "channel 1", 1);
	set_depress_function(sc_1, &sc_push);
	sc_2 = button_create(sc_container, "interface/screen2_over.tga", "interface/screen2.tga", "interface/screen2_over.tga",66, 0, 74, 60, 0, 1, "channel 1", 1);
	set_depress_function(sc_2, &sc_push);
	sc_3 = button_create(sc_container, "interface/screen3_over.tga", "interface/screen3.tga", "interface/screen3_over.tga",140, 0, 71, 60, 0, 1, "channel 1", 1);
	set_depress_function(sc_3, &sc_push);
	sc_4 = button_create(sc_container, "interface/screen4_over.tga", "interface/screen4.tga", "interface/screen4_over.tga",211, 0, 64, 60, 0, 1, "channel 1", 1);
	set_depress_function(sc_4, &sc_push);
	/*create song selector*/	

	select_song_container = container_create((geteditorwidth()/2)-125, 50, 250, 550, 0);
	select_song_dialogue = image_create(select_song_container, 0,0, 250, 550, 1, "interface/song_dialogue.tga");
	select_song_close = button_create(select_song_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",8, 5, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(select_song_close, &close_song_select);
	int left=0;
	for(int i=0;i<60;i++){
		if(i>29){
			left=250;
		}
		select_song[i] = label_create(select_song_container, "This is a Test Label", default_font, 0, 10+left, i*17+34, 1, 0);
		set_depress_function(select_song[i], &select_song_for_channel);
	} 

	/* create layer editor */
	layer_container = container_create(10, 10, 250, 550, 0);
	layer_top = image_create(layer_container, 0,0, 250, 34, 1, "interface/layer_top.tga");
	layer_label = label_create(layer_container, "Test Layer Name", default_font, 0, 10, 10, 1, 1);
	set_deselect_function(layer_label, &set_title);
	layer_new = button_create(layer_container, "interface/layer_new.tga", "interface/layer_new.tga", "interface/layer_new.tga",0, 34, 124, 16, 0, 1, "new", 0);
	set_depress_function(layer_new, &new_layer);
	layer_delete = button_create(layer_container, "interface/layer_delete.tga", "interface/layer_delete.tga", "interface/layer_delete.tga",124, 34, 126, 16, 0, 1, "new", 0);
	set_depress_function(layer_delete, &delete_layer);
	for(int i=0;i<15;i++){
		layer_view[i] = button_create(layer_container, "interface/layer_on.tga", "interface/layer_off.tga", "interface/layer_on.tga",0, i*30+50, 250, 30, 0, 1, "new", 0);
		set_depress_function(layer_view[i], &select_layer);
	}
	for(int i=0;i<15;i++){		
		layer_view_label[i] = label_create(layer_container, "layer title", default_font, 0, 10, i*30+55, 1, 1);
		layer_view_spanner[i] = image_create(layer_container, 205, i*30+52, 30, 30, 1, "interface/edit_button.tga");
		
	} 
	/* create frame editor */
	fc_container = container_create(270, 10, 250, 550, 0);
	fc_back = image_create(fc_container, 0,0, 533, 33, 1, "interface/fc_back.tga");
	fc_frame = label_create(fc_container, "null", default_font, 0, 82, 8, 1, 0);
	fc_object = label_create(fc_container, "object type", default_font, 0, 305, 8, 1, 0);
	set_depress_function(fc_object, &open_editors);
	fc_frame_new = button_create(fc_container, "interface/new_icon_hover.tga", "interface/new_icon.tga", "interface/new_icon_hover.tga", 150, 0, 23, 33, 0, 1, "new", 0);
	fc_frame_delete = button_create(fc_container, "interface/delete_icon_hover.tga", "interface/delete_icon.tga", "interface/delete_icon_hover.tga", 175, 0, 23, 33, 0, 1, "delete", 0);
	fc_frame_drop = button_create(fc_container, "interface/drop_down_hover.tga", "interface/drop_down_button.tga", "interface/drop_down_hover.tga", 65, 9, 20, 20, 0, 1, "drop", 0);
	fc_obj_new = button_create(fc_container, "interface/new_icon_hover.tga", "interface/new_icon.tga", "interface/new_icon_hover.tga",485, 0, 23, 33, 0, 1, "new", 0);
	set_depress_function(fc_obj_new, &obj_select_new);
	fc_obj_delete = button_create(fc_container, "interface/delete_icon_hover.tga", "interface/delete_icon.tga", "interface/delete_icon_hover.tga", 508, 0, 23, 33, 0, 1, "delete", 0);
	set_depress_function(fc_obj_delete, &obj_delete);
	fc_obj_drop = button_create(fc_container, "interface/drop_down_hover.tga", "interface/drop_down_button.tga", "interface/drop_down_hover.tga", 286, 9, 20, 20, 0, 1, "drop", 0);
	set_depress_function(fc_obj_drop, &obj_select);
	/* object editor */

	/* create frame select */
		

	/* object select */
	fc_obj_container = container_create((geteditorwidth()/2)-125, 50, 250, 550, 0);
	fc_obj_dia = image_create(fc_obj_container, 0,0, 250, 550, 1, "interface/obj_dialogue.tga");
	fc_obj_close = button_create(fc_obj_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",8, 5, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(fc_obj_close, &close_obj_select);
	for(int i=0;i<30;i++){
		fc_obj_select[i] = label_create(fc_obj_container, "test_object", default_font, 0, 10, i*17+34, 1, 0);
		set_depress_function(fc_obj_select[i], &select_object);
	} 
	/* object editor widgets */
	colour_container = container_create(270, 53, 104, 157, 0);
	colour_back = image_create(colour_container, 0,0, 104, 157, 1, "interface/colour_widget.tga");
	
	red = verticle_slider_create(colour_container, "interface/slider_button.tga", "interface/slider_button.tga", 22, 31,"interface/slider_back.tga", 22, 119, 11, 11, 0, 1, 1);
	set_hover_function(red, &set_colour);
	green = verticle_slider_create(colour_container, "interface/slider_button.tga", "interface/slider_button.tga", 22, 31,"interface/slider_back.tga", 22, 119, 33, 11, 0, 1, 1);
	set_hover_function(green, &set_colour);
	blue = verticle_slider_create(colour_container, "interface/slider_button.tga", "interface/slider_button.tga", 22, 31,"interface/slider_back.tga", 22, 119, 55, 11, 0, 1, 1);
	set_hover_function(blue, &set_colour);
	alpha = verticle_slider_create(colour_container, "interface/slider_button.tga", "interface/slider_button.tga", 22, 31,"interface/slider_back.tga", 22, 119, 77, 11, 0, 1, 1);
	set_hover_function(alpha, &set_colour);
	


	posrot_container = container_create(384, 53, 104, 157, 0);
	posrot_back = image_create(posrot_container, 0,0, 376, 111, 1, "interface/posrot_back.tga");
	posrot_x = label_create(posrot_container, "0", default_font, 0, 98, 16, 1, 1);
	label_display_chars(posrot_x, 5);
	label_only_numeric(posrot_x);
	set_deselect_function(posrot_x, &set_position);
	posrot_y = label_create(posrot_container, "0", default_font, 0, 178, 16, 1, 1);
	label_display_chars(posrot_y, 5);
	label_only_numeric(posrot_y);
	set_deselect_function(posrot_y, &set_position);
	posrot_z = label_create(posrot_container, "0", default_font, 0, 258, 16, 1, 1);
	label_display_chars(posrot_z, 5);
	label_only_numeric(posrot_z);
	set_deselect_function(posrot_z, &set_position);


	posrot_rx = button_create(posrot_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga",100, 51, 14, 14, 0, 1, "x", 1);
	set_release_function(posrot_rx, &set_rotation);
	posrot_ry = button_create(posrot_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga",157, 51, 14, 14, 0, 1, "x", 1);
	set_release_function(posrot_ry, &set_rotation);
	posrot_rz = button_create(posrot_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga",214, 51, 14, 14, 0, 1, "x", 1);
	set_release_function(posrot_rz, &set_rotation);
	posrot_degree = label_create(posrot_container, "0", default_font, 0, 258, 51, 1, 1);
	label_display_chars(posrot_degree, 5);
	label_only_numeric(posrot_degree);
	set_deselect_function(posrot_degree, &set_rotation);
	posrot_auto = button_create(posrot_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 343, 51, 14, 14, 0, 1, "x", 1);
	set_release_function(posrot_auto, &set_rotation);

	
	posrot_sx = label_create(posrot_container, "0", default_font, 0, 98, 86, 1, 1);
	label_display_chars(posrot_sx, 5);
	label_only_numeric(posrot_sx);
	set_deselect_function(posrot_sx, &set_scale);
	
	posrot_sy = label_create(posrot_container, "0", default_font, 0, 178, 86, 1, 1);
	label_display_chars(posrot_sy, 5);
	label_only_numeric(posrot_sy);
	set_deselect_function(posrot_sy, &set_scale);
	
	posrot_sz = label_create(posrot_container, "0", default_font, 0, 258, 86, 1, 1);
	label_display_chars(posrot_sz, 5);
	label_only_numeric(posrot_sz);
	set_deselect_function(posrot_sz, &set_scale);

	audio_container = container_create(384, 174, 376, 111, 0);
	audio_back = image_create(audio_container, 0,0, 376, 111, 1, "interface/audio_back.tga");
	audio_fft_switch = button_create(audio_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 12, 27, 14, 14, 0, 1, "x", 1);
	set_release_function(audio_fft_switch, &set_audio_fft);
	audio_scale = button_create(audio_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 351, 27, 14, 14, 0, 1, "x", 1);
	set_release_function(audio_scale, &set_audio);
	audio_fft_slot = label_create(audio_container, "0", default_font, 0, 55, 26, 1, 1);
	set_deselect_function(audio_fft_slot, &set_audio_fft);
	label_display_chars(audio_fft_slot, 5);
	label_only_numeric(audio_fft_slot);
	audio_fft_multiply = label_create(audio_container, "0", default_font, 0, 135, 27, 1, 1);
	label_display_chars(audio_fft_multiply, 5);
	label_only_numeric(audio_fft_multiply);
	set_deselect_function(audio_fft_multiply, &set_audio_fft);
	audio_volume_switch = button_create(audio_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 222, 27, 14, 14, 0, 1, "x", 1);
	set_release_function(audio_volume_switch, &set_audio_volume);
	audio_volume_multiply = label_create(audio_container, "0", default_font, 0, 265, 27, 1, 1);
	label_display_chars(audio_volume_multiply, 5);
	label_only_numeric(audio_volume_multiply);
	set_deselect_function(audio_volume_multiply, &set_audio_volume);
	audio_beat_render_switch = button_create(audio_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 12, 76, 14, 14, 0, 1, "x", 1);
	set_release_function(audio_beat_render_switch, &set_audio_render);
	audio_beat_render_minus = button_create(audio_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 56, 76, 14, 14, 0, 1, "x", 1);
	set_release_function(audio_beat_render_minus, &set_audio_render_minus);
	audio_beat_render_plus = button_create(audio_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 93, 76, 14, 14, 0, 1, "x", 1);
	set_release_function(audio_beat_render_plus, &set_audio_render_plus);

	texture_container = container_create(270, 220, 104, 157, 0);
	texture_back = image_create(texture_container, 0,0, 104, 157, 1, "interface/texture_back.tga");
	texture_button = button_create(texture_container, "interface/texture_over.tga", "interface/texture.tga", "interface/texture_over.tga", 0, 0, 104, 87, 0, 1, "new texture", 0);
	set_release_function(texture_button, &get_texture);
	texture_label = label_create(texture_container, "name here", default_font, 0, 7, 95, 1, 0);
	render_solid = button_create(texture_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 10, 128, 14, 14, 0, 1, "x", 1);
	set_release_function(render_solid, &do_render_solid);
	render_wire = button_create(texture_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", 81, 128, 14, 14, 0, 1, "x", 1);
	set_release_function(render_wire, &do_render_wire);
	
	camera_container = container_create(270, 120, 104, 157, 0);
	camera_back = image_create(camera_container, 0,0, 342, 123, 1, "interface/camera_back.tga");
	for(int i=0;i<8;i++){
		camerasel[i] = button_create(camera_container, "interface/check_on.tga", "interface/check_off.tga", "interface/check_on.tga", (i*30)+107, 10, 14, 14, 0, 1, "x", 1);
		set_release_function(camerasel[i], &do_camera);	
	}

	/* new object selector */
	new_obj_container = container_create((geteditorwidth()/2)-375, (getwinheight()/2)-127, 750, 255, 0);
	new_obj_back = image_create(new_obj_container, 0,0, 750, 255, 1, "interface/new_obj.tga");
	new_obj_close = button_create(new_obj_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",438, 43, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(new_obj_close, &close_new_obj);
	new_obj_1 = button_create(new_obj_container, "interface/new_obj_1_over.tga", "interface/new_obj_1.tga", "interface/new_obj_1_over.tga",0, 125, 116, 136, 0, 1, "", 0);
	set_depress_function(new_obj_1, &open_new_obj_1);
	
	new_obj_2 = button_create(new_obj_container, "interface/new_obj_2_over.tga", "interface/new_obj_2.tga", "interface/new_obj_2_over.tga",116, 125, 127, 136, 0, 1, "", 0);
	set_depress_function(new_obj_2, &open_new_obj_2);	
	
	new_obj_3 = button_create(new_obj_container, "interface/new_obj_3_over.tga", "interface/new_obj_3.tga", "interface/new_obj_3_over.tga",243, 125, 119, 135, 0, 1, "", 0);
	set_depress_function(new_obj_3, &open_new_obj_3);
	
	new_obj_4 = button_create(new_obj_container, "interface/new_obj_4_over.tga", "interface/new_obj_4.tga", "interface/new_obj_4_over.tga",362, 125, 132, 136, 0, 1, "", 0);
	set_depress_function(new_obj_4, &open_new_obj_4);
	
	new_obj_5 = button_create(new_obj_container, "interface/new_obj_8_over.tga", "interface/new_obj_8.tga", "interface/new_obj_5_over.tga",494, 128, 128, 135, 0, 1, "", 0);
	set_depress_function(new_obj_5, &open_new_obj_5);
	
	new_obj_6 = button_create(new_obj_container, "interface/new_obj_5_over.tga", "interface/new_obj_5.tga", "interface/new_obj_5_over.tga",626, 125, 124, 136, 0, 1, "", 0);
	set_depress_function(new_obj_6, &open_new_obj_6);
	
	/*new_obj_7 = button_create(new_obj_container, "interface/new_obj_6_over.tga", "interface/new_obj_6.tga", "interface/new_obj_6_over.tga",316, 0, 107, 125, 0, 1, "", 0);
	set_depress_function(new_obj_7, &open_new_obj_7);*/

	new_obj_8 = button_create(new_obj_container, "interface/new_obj_7_over.tga", "interface/new_obj_7.tga", "interface/new_obj_7_over.tga",316, 0, 107, 125, 0, 1, "", 0);
	set_depress_function(new_obj_8, &open_new_obj_8);

	
	
	/*libraries selectors*/
	vlib_container = container_create((geteditorwidth()/2)-125, 50, 250, 550, 0);
	vlib_back = image_create(vlib_container, 0,0, 250, 550, 1, "interface/video_dialogue.tga");
	vlib_close = button_create(vlib_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",8, 5, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(vlib_close, &lib_close);	
	for(int i=0;i<30;i++){
		vlib_select[i] = label_create(vlib_container, "test_object", default_font, 0, 10, i*17+34, 1, 0);
		set_depress_function(vlib_select[i], &vlib_selecta);
	} 

	alib_container = container_create((geteditorwidth()/2)-125, 50, 250, 550, 0);
	alib_back = image_create(alib_container, 0,0, 250, 550, 1, "interface/audio_dialogue.tga");
	alib_close = button_create(alib_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",8, 5, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(alib_close, &lib_close);	
	for(int i=0;i<30;i++){
		alib_select[i] = label_create(alib_container, "test_object", default_font, 0, 10, i*17+34, 1, 0);
		set_depress_function(alib_select[i], &alib_selecta);
	}

	tlib_container = container_create((geteditorwidth()/2)-125, 50, 250, 550, 0);
	tlib_back = image_create(tlib_container, 0,0, 250, 550, 1, "interface/texture_dialogue.tga");
	tlib_close = button_create(tlib_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",8, 5, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(tlib_close, &lib_close);	
	for(int i=0;i<30;i++){
		tlib_select[i] = label_create(tlib_container, "test_object", default_font, 0, 10, i*17+34, 1, 0);
		set_depress_function(tlib_select[i], &tlib_selecta);
	} 

	mlib_container = container_create((geteditorwidth()/2)-125, 50, 250, 550, 0);
	mlib_back = image_create(mlib_container, 0,0, 250, 550, 1, "interface/3d_dialogue.tga");
	mlib_close = button_create(mlib_container, "interface/dialogue_close_button_hover.tga", "interface/dialogue_close_button.tga", "interface/dialogue_close_button_hover.tga",8, 5, 16, 16, 0, 1, "close dialogue", 0);
	set_depress_function(mlib_close, &lib_close);	
	for(int i=0;i<30;i++){
		mlib_select[i] = label_create(mlib_container, "test_object", default_font, 0, 10, i*17+34, 1, 0);
		set_depress_function(mlib_select[i], &mlib_selecta);
	}


	/* error popup */
	error_container = container_create((geteditorwidth()/2)-145, (getwinheight()/2)-84, 750, 255, 0);
	error_back = image_create(error_container, 0,0, 290, 168, 1, "interface/error.tga");
	set_depress_function(error_back, &close_error);



}

void draw_canvases(void){
	draw_canvas(canvas_channel_mix, 0, 0, geteditorwidth(), getwinheight());
	draw_canvas(canvas_channel_1, 6, getwinheight()-173, 220, 165);
	draw_canvas(canvas_channel_2, (geteditorwidth()-228), getwinheight()-173, 220, 165);
	draw_canvas(canvas_channel_mix, geteditorwidth(), 0, geteditorwidth(), getwinheight());
}

void open_channel_canvas(int mychannel){
	if(mychannel==1){
		open_canvas(canvas_channel_1);
	}
	if(mychannel==2){
		open_canvas(canvas_channel_2);
	}
	if(mychannel==3){
		open_canvas(canvas_channel_mix);
	}
}

void close_channel_canvas(int mychannel){
	if(mychannel==1){
		close_canvas(canvas_channel_1);
	}
	if(mychannel==2){
		close_canvas(canvas_channel_2);
	}
	if(mychannel==3){
		close_canvas(canvas_channel_mix);
	}
}

GLuint get_channel_texture(int mychannel){
	if(mychannel==1){
		return get_canvas_texture(canvas_channel_1);
	}else if(mychannel==2){
		return get_canvas_texture(canvas_channel_2);
	}else if(mychannel==3){
		return get_canvas_texture(canvas_channel_mix);
	}else{
		return 0;
	}
}

float get_video_mix_slide(){
	return get_slider_value(mix_controls_video_slider);
}
