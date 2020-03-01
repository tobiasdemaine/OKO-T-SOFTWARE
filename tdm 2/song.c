#include "song.h"

/* songs[id].layers[id].frames[id].property */
media_video video__library[1000];
media_mesh mesh__library[1000];
media_texture texture__library[1000];
media_audio audio__library[1000];
song *songs;
int videodb, texturedb, meshdb, audiodb, songdb; /* song media libraries */
int channel_1_song;
int channel_2_song;
int outputrender=1;
int beatblur;
int channel_1_pause, channel_2_pause;
void set_output_render(int renderit){
	if(renderit==1){
		outputrender=1;
		beatblur=0;
	}
	if(renderit==2){
		outputrender=2;
		beatblur=0;
	}
	if(renderit==3){
		outputrender=3;
		beatblur=0;
	}
	if(renderit==4){
		beatblur=1;
	}
	
}
int get_mesh_id(int meid){
	for(int i=0;i<db_get_row_count(meshdb);i++){
		if(mesh__library[i].id==meid){
			return i;
			break;
		}
	}
	return 0;
}
int get_video_id(int meid){
	for(int i=0;i<db_get_row_count(videodb);i++){
		if(video__library[i].id==meid){
			return i;
			break;
		}
	}
	return 0;
}
int get_texture_id(int meid){
	for(int i=0;i<db_get_row_count(texturedb);i++){
		if(texture__library[i].id==meid){
			return i;
			break;
		}
	}
	return 0;
}
int get_audio_id(int meid){
	for(int i=0;i<db_get_row_count(audiodb);i++){
		if(audio__library[i].id==meid){
			return i;
			break;
		}
	}
	return 0;
}

int song_get_video_lib_count(void){
	return db_get_row_count(videodb);
}

char *song_get_video_name_by_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(videodb);i++){
		if(i==slot_id){
			break;
		}
	}
	return video__library[i].title;
}

int song_get_vid_id_from_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(videodb);i++){
		if(i==slot_id){
			break;
		}
	}
	return video__library[i].id;
}

int song_get_mesh_lib_count(void){
	return db_get_row_count(meshdb);
}

char *song_get_mesh_name_by_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(meshdb);i++){
		if(i==slot_id){
			break;
		}
	}
	return mesh__library[i].title;
}

int song_get_mesh_id_from_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(meshdb);i++){
		if(i==slot_id){
			break;
		}
	}
	return mesh__library[i].id;
}

int song_get_texture_lib_count(void){
	return db_get_row_count(texturedb);
}

char *song_get_texture_name_by_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(texturedb);i++){
		if(i==slot_id){
			break;
		}
	}
	return texture__library[i].title;
}

int song_get_texture_id_from_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(texturedb);i++){
		if(i==slot_id){
			break;
		}
	}
	return texture__library[i].id;
}

int song_get_audio_lib_count(void){
	return db_get_row_count(audiodb);
}

char *song_get_audio_name_by_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(audiodb);i++){
		if(i==slot_id){
			break;
		}
	}
	return audio__library[i].title;
}

int song_get_audio_id_from_slot(int slot_id){
	int i;
	for(i=0;i<db_get_row_count(audiodb);i++){
		if(i==slot_id){
			break;
		}
	}
	return audio__library[i].id;
}


void song_load_media_libraries(void){
	int i;
	set_db_path("/home/instant/");
	videodb=db_open(".oko-t/db/videolib");
	for(i=0;i<db_get_row_count(videodb);i++){
		video__library[i].video = stream_create(db_get_row_item_by_slot(videodb, i, 1));
		video__library[i].title = db_get_row_item_by_slot(videodb, i, 2);
		video__library[i].id = db_get_row_id_from_slot(videodb, i);
	}
	meshdb=db_open(".oko-t/db/meshlib");
	for(i=0;i<db_get_row_count(meshdb);i++){
		mesh__library[i].mesh = create_mesh(db_get_row_item_by_slot(meshdb, i, 1));
		mesh__library[i].title = db_get_row_item_by_slot(meshdb, i, 2);
		mesh__library[i].id = db_get_row_id_from_slot(meshdb, i);
	}
	texturedb=db_open(".oko-t/db/texturelib");
	for(i=0;i<db_get_row_count(texturedb);i++){
		texture__library[i].texture = load_image(db_get_row_item_by_slot(texturedb, i, 1), 0);
		texture__library[i].title = db_get_row_item_by_slot(texturedb, i, 2);
		texture__library[i].id = db_get_row_id_from_slot(texturedb, i);
	}
	/*
	audiodb=db_open(".oko-t/db/audiolib");	
	for(i=0;i<db_get_row_count(audiodb);i++){
		audio__library[i].audio = stream_create(db_get_row_item_by_slot(audiodb, i, 1));
		audio__library[i].title = db_get_row_item_by_slot(audiodb, i, 2);
		audio__library[i].id = db_get_row_id_from_slot(audiodb, i);
	}
	*/
	/*load into song database*/
	
	songdb=db_open(".oko-t/db/songs");
	songs = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	
	for(i=0;i<db_get_row_count(songdb);i++){
		songs[i].id = db_get_row_id_from_slot(songdb, i);
		songs[i].title = db_get_row_item_by_slot(songdb, i, 2);
		songs[i].song_file = db_get_row_item_by_slot(songdb, i, 1);
		songs[i].currentframe=1;
		song_load(songs[i].id);
	}
//	printf("after here %i\n\n", i);
}

void readstr(FILE *f,char *string){
	do{
		fgets(string, 1024, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}
void song_load_frame_elements(char *song_file, int slayer, int songid){
	FILE *stream;
	char *str;
	int mlayercount=0;
	int mframecount=0;
	char oneline[1024];
	int myframe;
	if((stream = fopen(song_file, "rt" )) != NULL){
		while(!feof( stream )){   
			readstr(stream, oneline);
			str = strstr(oneline, "<layer=" );
			if(str != NULL ){
				mlayercount++;
			}
			if(mlayercount == (slayer+1)){
				/* new we get the attributes of each frame */
				sscanf(oneline, "<frame=\"%i\">", &myframe);
				str = strstr(oneline, "<master>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=8;
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;	
				}
				str = strstr(oneline, "<video=" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=1;
					sscanf(oneline, "<video=\"%i\">", &songs[songid].layers[slayer].frames[mframecount].db_id);
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					songs[songid].layers[slayer].frames[mframecount].current_vid_frame=1;
					mframecount++;
				}
				str = strstr(oneline, "<mesh=" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=2;
					sscanf(oneline, "<mesh=\"%i\">", &songs[songid].layers[slayer].frames[mframecount].db_id);
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;
				}
				str = strstr(oneline, "<texture=" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=3;
					sscanf(oneline, "<texture=\"%i\">", &songs[songid].layers[slayer].frames[mframecount].db_id);
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;
				}
				str = strstr(oneline, "<audio=" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=4;
					sscanf(oneline, "<audio=\"%i\">", &songs[songid].layers[mlayercount].frames[mframecount].db_id);
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;
				}
				str = strstr(oneline, "<camera>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=5;
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;
				}
				str = strstr(oneline, "<midi>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=6;
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;
				}
				str = strstr(oneline, "<dmx>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount].type=7;
					songs[songid].layers[slayer].frames[mframecount].frameno = myframe;
					mframecount++;
				}
				str = strstr(oneline, "<tween_to_next_frame>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].tween_to_next_frame=1;
				}
				
				sscanf(oneline, "<seek_frame=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].seek_frame);
				sscanf(oneline, "<colour=\"%f %f %f %f\">", &songs[songid].layers[slayer].frames[mframecount-1].colour_r, &songs[songid].layers[slayer].frames[mframecount-1].colour_g, &songs[songid].layers[slayer].frames[mframecount-1].colour_b, &songs[songid].layers[slayer].frames[mframecount-1].colour_a);
				sscanf(oneline, "<position=\"%f %f %f\">", &songs[songid].layers[slayer].frames[mframecount-1].x, &songs[songid].layers[slayer].frames[mframecount-1].y, &songs[songid].layers[slayer].frames[mframecount-1].z);
				sscanf(oneline, "<scale=\"%f %f %f\">", &songs[songid].layers[slayer].frames[mframecount-1].scalex, &songs[songid].layers[slayer].frames[mframecount-1].scaley, &songs[songid].layers[slayer].frames[mframecount-1].scalez);
				str = strstr(oneline, "<width_fullscreen>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].width = getwinwidth();
				}
				str = strstr(oneline, "<height_fullscreen>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].height = getwinheight();
				}
				sscanf(oneline, "<width=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].width);
				sscanf(oneline, "<height=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].height);
				str = strstr(oneline, "<rotation_auto_animation>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].rotation_auto_animation=1;
				}
				sscanf(oneline, "<rotate=\"%f %f %f %f\">", &songs[songid].layers[slayer].frames[mframecount-1].rotation_degree, &songs[songid].layers[slayer].frames[mframecount-1].rotation_x, &songs[songid].layers[slayer].frames[mframecount-1].rotation_y, &songs[songid].layers[slayer].frames[mframecount-1].rotation_z);
				str = strstr(oneline, "<rotate=" );
				if(str != NULL ){
					printf("<rotation=\"%f %f %f %f\">\n", songs[songid].layers[slayer].frames[mframecount-1].rotation_degree, songs[songid].layers[slayer].frames[mframecount-1].rotation_x, songs[songid].layers[slayer].frames[mframecount-1].rotation_y, songs[songid].layers[slayer].frames[mframecount-1].rotation_z);
				}
				str = strstr(oneline, "<set_alpha_from_audio_level>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].set_alpha_from_audio_level=1;
				}
				str = strstr(oneline, "<set_alpha_from_audio_beat>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].set_alpha_from_audio_beat=1;
				}
				sscanf(oneline, "<audio_scale_type=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].audio_scale_type);
				str = strstr(oneline, "<use_inbuilt_beat_detection>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].use_inbuilt_beat_detection=1;
				}
				sscanf(oneline, "<BPM=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].BPM);
				sscanf(oneline, "<beat_render=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].beat_render);
				sscanf(oneline, "<scale_from_fft=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].scale_from_fft);
				sscanf(oneline, "<audio_multiplier=\"%f\">", &songs[songid].layers[slayer].frames[mframecount-1].audio_multiplier);
				sscanf(oneline, "<audioclip=\"%f %i %i\">", &songs[songid].layers[slayer].frames[mframecount-1].clip_top, &songs[songid].layers[slayer].frames[mframecount-1].clip_left, &songs[songid].layers[slayer].frames[mframecount-1].clip_right);
				str = strstr(oneline, "<solid_render>" );
				if(str != NULL ){
					songs[songid].layers[slayer].frames[mframecount-1].solid_render=1;
				}
				sscanf(oneline, "<current_frame=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].current_frame);
				sscanf(oneline, "<playback_speed=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].playback_speed);
				sscanf(oneline, "<playback_direction=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].playback_direction);
				sscanf(oneline, "<use_texture=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].use_texture);
				sscanf(oneline, "<use_video_as_texture=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].use_video_as_texture);
				sscanf(oneline, "<inbuilt_camera=\"%i\">", &songs[songid].layers[slayer].frames[mframecount-1].inbuilt_camera);
				
			}
		}
	}
	fclose(stream);
}

int song_load_layer_attributes(char *song_file, int slayer, int songid){
	FILE *stream;
	char *str;
	int mlayercount=0;
	int mframecount=0;
	char oneline[1024];
	if((stream = fopen(song_file, "rt" )) != NULL){
		while(!feof( stream )){   
			readstr(stream, oneline);
			str = strstr(oneline, "<layer=" );
			if(str != NULL ){
				char cha = '"';
			        char *p = strchr(oneline, cha);
				int p1 = oneline - p;
				if(p1<0) {
     					p1 *= -1;  
    				}
				p = strrchr(oneline, cha);
				int p2 = oneline - p;
				if(p2<0) {
     					p2 *= -1;  
    				}
				songs[songid].layers[mlayercount].layer_name = (char *)calloc(p2-p1, sizeof(char));
				strncat(songs[songid].layers[mlayercount].layer_name, oneline+p1+1, p2-p1-1);	
				mlayercount++;
			}
			if(mlayercount == (slayer+1)){
				sscanf(oneline, "<zindex=\"%i\">", &songs[songid].layers[slayer].zindex);
				str = strstr(oneline, "<master>" );
				if(str != NULL ){
					mframecount++;		
				}
				str = strstr(oneline, "<video=" );
				if(str != NULL ){
					mframecount++;
				}
				str = strstr(oneline, "<mesh=" );
				if(str != NULL ){
					mframecount++;
				}
				str = strstr(oneline, "<texture=" );
				if(str != NULL ){
					mframecount++;
				}
				str = strstr(oneline, "<audio=" );
				if(str != NULL ){
					mframecount++;
				}
				str = strstr(oneline, "<camera>" );
				if(str != NULL ){
					mframecount++;
				}
				str = strstr(oneline, "<midi>" );
				if(str != NULL ){
					mframecount++;
				}
				str = strstr(oneline, "<dmx>" );
				if(str != NULL ){
					mframecount++;
				}
			}
		}
	}
	fclose(stream);
	return mframecount;
}
int song_count_layers(char *song_file){
	FILE *stream;
	char *str;
	int mlayercount=0;
	char oneline[1024];
	if((stream = fopen(song_file, "rt" )) != NULL){
		while(!feof( stream )){   
			readstr(stream, oneline);
			str = strstr(oneline, "<layer=" );
			if(str != NULL ){
				mlayercount++;
			}
		}
	}
	fclose(stream);
	return mlayercount;
}
void song_delete_layer(int songid, int layerslot){
	song *tmpsong;
	int csong = get_song_slot_from_id(songid);
	int si, i;
	tmpsong = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		if(si==csong){
			tmpsong[si].layers = (song_layer *)calloc((songs[csong].layercount-1), sizeof(song_layer));
			for(i=0;i<(songs[csong].layercount-1);i++){
				if(i!=layerslot){
					if(i>layerslot){
						tmpsong[si].layers[i-1].frames = (layer_frame *)calloc((songs[csong].layers[i].framecount), sizeof(layer_frame));
						tmpsong[si].layers[i-1] = songs[csong].layers[i];
					}else{
						tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[csong].layers[i].framecount), sizeof(layer_frame));
						tmpsong[si].layers[i] = songs[csong].layers[i];
					}
				}
			}
			tmpsong[si].id = songs[csong].id;
			tmpsong[si].title = songs[csong].title;
			tmpsong[si].song_file = songs[csong].song_file;
			tmpsong[si].layercount = songs[csong].layercount-1;
			tmpsong[si].masterseekto = songs[csong].masterseekto;
			tmpsong[si].externalseekto = songs[csong].externalseekto;
			tmpsong[si].currentframe = songs[csong].currentframe;
		}else{
			tmpsong[si].layers = (song_layer *)calloc((songs[csong].layercount), sizeof(song_layer));
			tmpsong[si] = songs[si];
		}
	}
	songs = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		songs[si].layers = (song_layer *)calloc((tmpsong[si].layercount), sizeof(song_layer));
		for(i=0;i<tmpsong[si].layercount;i++){
				songs[si].layers[i].frames = (layer_frame *)calloc((tmpsong[si].layers[i].framecount), sizeof(layer_frame));
		}
		songs[si] = tmpsong[si];
	}
	free(tmpsong);
}

void song_new_layer(int songid){
	song *tmpsong;
	int i,si;
	int csong = get_song_slot_from_id(songid);
	tmpsong = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		if(si==csong){
			tmpsong[si].layers = (song_layer *)calloc((songs[csong].layercount+1), sizeof(song_layer));
			for(i=0;i<(songs[csong].layercount+1);i++){
				if(i<(songs[csong].layercount)){
					tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[csong].layers[i].framecount), sizeof(layer_frame));
					tmpsong[si].layers[i] = songs[csong].layers[i];
				}else{
					tmpsong[si].layers[i].layer_name = "New Layer";
					tmpsong[si].layers[i].framecount = 0;
					tmpsong[si].layers[i].zindex = i;
				}
			}
			tmpsong[si].id = songs[csong].id;
			tmpsong[si].title = songs[csong].title;
			tmpsong[si].song_file = songs[csong].song_file;
			tmpsong[si].layercount = songs[csong].layercount+1;
			tmpsong[si].masterseekto = songs[csong].masterseekto;
			tmpsong[si].externalseekto = songs[csong].externalseekto;
			tmpsong[si].currentframe = songs[csong].currentframe;
			
		}else{
			tmpsong[si].layers = (song_layer *)calloc((songs[csong].layercount), sizeof(song_layer));
			tmpsong[si] = songs[si];
		}
	}	
	free(songs);
	songs = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		songs[si].layers = (song_layer *)calloc((tmpsong[si].layercount), sizeof(song_layer));
		for(i=0;i<tmpsong[si].layercount;i++){
				songs[si].layers[i].frames = (layer_frame *)calloc((tmpsong[si].layers[i].framecount), sizeof(layer_frame));
		}
		songs[si] = tmpsong[si];
	}
	free(tmpsong);
}

void song_delete_frame_object(int songid, int layer_slot, int frame_number, int obj_slot){
	song *tmpsong;
	int i,si, fi;
	int deleteitem = song_get_object_frame_from_obj_slot(songid, layer_slot, frame_number, obj_slot);
	int csong = get_song_slot_from_id(songid);
	tmpsong = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		tmpsong[si].layers = (song_layer *)calloc((songs[si].layercount), sizeof(song_layer));
		for(i=0;i<songs[si].layercount;i++){
			if((si==csong)&&(layer_slot==i)){
				tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[si].layers[i].framecount-1), sizeof(layer_frame));
 				tmpsong[si].layers[i].framecount = songs[si].layers[i].framecount;
			}else{
				tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[si].layers[i].framecount), sizeof(layer_frame));
				tmpsong[si].layers[i].framecount = songs[si].layers[i].framecount;
			}
			for(fi=0;fi<songs[si].layers[i].framecount;fi++){
				if((si==csong)&&(layer_slot==i)){
					if(fi!=deleteitem){
						if(fi<deleteitem){
							tmpsong[si].layers[i].frames[fi] = songs[si].layers[i].frames[fi];
						}else{
							tmpsong[si].layers[i].frames[fi-1] = songs[si].layers[i].frames[fi];
						}
					}else{
						printf("i deleted frames[%i]\n\n", deleteitem);
					}
				}else{
					tmpsong[si].layers[i].frames[fi] = songs[si].layers[i].frames[fi];
				}
			}
			tmpsong[si].layers[i].layer_name = songs[si].layers[i].layer_name;
			tmpsong[si].layers[i].zindex = songs[si].layers[i].zindex;	
		}
		tmpsong[si].id = songs[si].id;
		tmpsong[si].title = songs[si].title;
		tmpsong[si].song_file = songs[si].song_file;
		tmpsong[si].layercount = songs[si].layercount;
		tmpsong[si].masterseekto = songs[si].masterseekto;
		tmpsong[si].externalseekto = songs[si].externalseekto;
		tmpsong[si].currentframe = songs[si].currentframe;	
		
	}
	free(songs);
	songs = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		songs[si].layers = (song_layer *)calloc((tmpsong[si].layercount), sizeof(song_layer));
		for(i=0;i<tmpsong[si].layercount;i++){
				songs[si].layers[i].frames = (layer_frame *)calloc((tmpsong[si].layers[i].framecount), sizeof(layer_frame));
		}
		songs[si] = tmpsong[si];
	}
	free(tmpsong);
}

int song_create_new_frame_obj(int songid, int layer_slot, int frame_number, int obj_type, int mdb_id){
	song *tmpsong;
	int i,si, fi;
	int getitem=0;
	int csong = get_song_slot_from_id(songid);
	
	tmpsong = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		tmpsong[si].layers = (song_layer *)calloc((songs[si].layercount), sizeof(song_layer));
		for(i=0;i<songs[si].layercount;i++){
			if((layer_slot==i)&&(si==csong)){
				tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[si].layers[i].framecount+1), sizeof(layer_frame));
				for(fi=0;fi<songs[si].layers[i].framecount;fi++){
					tmpsong[si].layers[i].frames[fi] = songs[si].layers[i].frames[fi];
				}
				tmpsong[si].layers[i].framecount = songs[si].layers[i].framecount+1;
				tmpsong[si].layers[i].frames[songs[si].layers[i].framecount].type = obj_type;
				tmpsong[si].layers[i].frames[songs[si].layers[i].framecount].db_id = mdb_id;
				tmpsong[si].layers[i].frames[songs[si].layers[i].framecount].frameno = frame_number;
				getitem=songs[si].layers[i].framecount;
			}else{
				
				tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[si].layers[i].framecount), sizeof(layer_frame));
				tmpsong[si].layers[i].framecount = songs[si].layers[i].framecount;
				for(fi=0;fi<songs[si].layers[i].framecount;fi++){
					tmpsong[si].layers[i].frames[fi] = songs[si].layers[i].frames[fi];
				}
			}
			tmpsong[si].layers[i].layer_name = songs[si].layers[i].layer_name;
			tmpsong[si].layers[i].zindex = songs[si].layers[i].zindex;
		}
		tmpsong[si].id = songs[si].id;
		tmpsong[si].title = songs[si].title;
		tmpsong[si].song_file = songs[si].song_file;
		tmpsong[si].layercount = songs[si].layercount;
		tmpsong[si].masterseekto = songs[si].masterseekto;
		tmpsong[si].externalseekto = songs[si].externalseekto;
		tmpsong[si].currentframe = songs[si].currentframe;	
	}

	free(songs);
	songs = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		songs[si].layers = (song_layer *)calloc((tmpsong[si].layercount), sizeof(song_layer));
		for(i=0;i<tmpsong[si].layercount;i++){
				songs[si].layers[i].frames = (layer_frame *)calloc((tmpsong[si].layers[i].framecount), sizeof(layer_frame));
		}
		songs[si] = tmpsong[si];
	}
	free(tmpsong);
	return getitem;
}

int song_new(void){
	song *tmpsong;
	int i,si;
	
	tmpsong = (song *)calloc(db_get_row_count(songdb), sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		tmpsong[si].layers = (song_layer *)calloc((songs[si].layercount), sizeof(song_layer));
		for(i=0;i<songs[si].layercount;i++){
				tmpsong[si].layers[i].frames = (layer_frame *)calloc((songs[si].layers[i].framecount), sizeof(layer_frame));
		}
		tmpsong[si] = songs[si];
	}
	free(songs);
	songs = (song *)calloc(db_get_row_count(songdb)+1, sizeof(song));
	for(si=0;si<db_get_row_count(songdb);si++){
		songs[si].layers = (song_layer *)calloc((tmpsong[si].layercount), sizeof(song_layer));
		for(i=0;i<tmpsong[si].layercount;i++){
				songs[si].layers[i].frames = (layer_frame *)calloc((tmpsong[si].layers[i].framecount), sizeof(layer_frame));
		}
		songs[si] = tmpsong[si];
	}
	free(tmpsong);
	db_new_row(songdb);
	int t = db_get_row_count(songdb)-1;
	songs[t].id = songs[t-1].id+1;//db_new_row(songdb); 
	db_insert_row_item(songdb, songs[t].id, 2, "New Song");
	songs[t].title = "New Song";
	/*char *tmpch = (char *)calloc(255, sizeof(char));
	sprintf(tmpch, "/home/instant/.oko-t/songs/%i", tmpsong[t].id);
	db_insert_row_item(songdb, tmpsong[t].id, 1, tmpch);
	tmpsong[t].song_file = tmpch;
	*/
	songs[t].layercount = 0;
	/*
	songs[t].layers = (song_layer *)calloc((songs[t].layercount), sizeof(song_layer));
	songs[t].layers[0].framecount=1;
	songs[t].layers[0].frames = (layer_frame *)calloc((songs[t].layers[0].framecount), sizeof(layer_frame));
	songs[t].layers[0].frames[0].type = 8;
	songs[t].layers[0].frames[0].frameno=1;
	songs[t].layers[0].frames[0].seek_frame=1;
	*/
	songs[t].masterseekto = 1;
	songs[t].externalseekto = 0;
	songs[t].currentframe = 0;	
	printf("done building new song step 1 : %i , %i\n\n", t, songs[t].id);
	
	printf("done building new song");
	return songs[t].id;
}

void song_load(int songid){
	/*open song file*/
	int li, i;
	for(i=0;i<db_get_row_count(songdb);i++){
		if(songs[i].id==songid){
			/*setup the layers*/
			songs[i].layercount = song_count_layers(songs[i].song_file);
			if(songs[i].layercount>0){
				songs[i].layers = (song_layer *)calloc((songs[i].layercount), sizeof(song_layer));
				/* load each layer elements*/
				for(li=0;li<songs[i].layercount;li++){
					songs[i].layers[li].framecount = song_load_layer_attributes(songs[i].song_file, li, i);
					songs[i].layers[li].frames = (layer_frame *)calloc((songs[i].layers[li].framecount), sizeof(layer_frame));
					/*load each frame element*/
					song_load_frame_elements(songs[i].song_file, li, i);
				}
				//break;
			}else{
				//break;
			}
		}
	}
}


void draw_layer_frame(int s, int l, int channel){
	int tmpobj0, tmpobj1;
	float tmpfft;
	layer_frame thisframe;
	for(int i=0;i<songs[s].layers[l].framecount;i++){
		if(songs[s].currentframe==songs[s].layers[l].frames[i].frameno){
			/* draw a key frame*/
			thisframe = songs[s].layers[l].frames[i];
			if(songs[s].layers[l].frames[i].type==1){
				tmpobj0 = video__library[get_video_id(thisframe.db_id)].video;
				if(channel==1){
					if(channel_1_pause==1){
						thisframe.current_vid_frame = thisframe.current_vid_frame-1;
						printf("pause %i\n", thisframe.current_vid_frame);
					}
					//printf("play %i\n", stream_get_position(tmpobj0));
				}
				if(channel==2){
					if(channel_2_pause==1){
						thisframe.current_vid_frame = thisframe.current_vid_frame-1;
					}
				}
				stream_set_rgba(tmpobj0, thisframe.colour_r, thisframe.colour_g, thisframe.colour_b, thisframe.colour_a);
				if(thisframe.rotation_auto_animation){
						//video_set_rotation(tmpobj0, thisframe.rotation_degree, thisframe.rotation_x, thisframe.rotation_y, thisframe.rotation_z, 1);
				}else{
					if(thisframe.rotation_degree){
						//video_set_rotation(tmpobj0, thisframe.rotation_degree, thisframe.rotation_x, thisframe.rotation_y, thisframe.rotation_z, 0);
					}
				}
				if(thisframe.audio_scale_type==1){
					tmpfft = get_fft_value((int)thisframe.scale_from_fft)/thisframe.audio_multiplier;
					//video_set_scale(tmpobj0, tmpfft, tmpfft, tmpfft);
				}else if(thisframe.audio_scale_type==2){
					tmpfft = get_level()/thisframe.audio_multiplier;
					//video_set_scale(tmpobj0, tmpfft, tmpfft, tmpfft);
				}else{
					//video_set_scale(tmpobj0, thisframe.scalex, thisframe.scaley, thisframe.scalez);
				}
				stream_seek(tmpobj0, thisframe.current_vid_frame);
				if(stream_is_streaming(tmpobj0)!=1){
					stream_play(tmpobj0);
				}
				stream_display(tmpobj0, thisframe.width, thisframe.height, (int)thisframe.x, (int)thisframe.y);
				if(stream_get_position(tmpobj0)!=thisframe.current_vid_frame){
					songs[s].layers[l].frames[i].current_vid_frame = stream_get_position(tmpobj0);
				}
				/* do video */
			}
			if(thisframe.type==2){
				/* draw mesh */
				tmpobj0 = mesh__library[get_mesh_id(thisframe.db_id)].mesh;
				mesh_set_rgba(tmpobj0, thisframe.colour_r, thisframe.colour_g, thisframe.colour_b, thisframe.colour_a);
				tmpobj1 = texture__library[get_texture_id(thisframe.use_texture)].texture;
				if(thisframe.rotation_auto_animation){
					//((float)getMS())/mesh_library[mesh].rotation;
					songs[s].layers[l].frames[i].tmprot+=thisframe.rotation_degree;
					mesh_set_rotation(tmpobj0, songs[s].layers[l].frames[i].tmprot, thisframe.rotation_x, thisframe.rotation_y, thisframe.rotation_z, 1);
					
				}else{
					mesh_set_rotation(tmpobj0, thisframe.rotation_degree, thisframe.rotation_x, thisframe.rotation_y, thisframe.rotation_z, 0);
				}
				mesh_set_postion(tmpobj0 , thisframe.x, thisframe.y, thisframe.z);
				if(thisframe.beat_render==1){
					if(get_beat()==2){
						glPolygonMode(GL_FRONT, GL_FILL);
						glPolygonMode(GL_BACK, GL_FILL);
					}else{
						glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
						glPolygonMode(GL_FRONT, GL_LINE);
						glPolygonMode(GL_BACK, GL_LINE);
					
					}
				}else if(thisframe.beat_render==2){
					if(get_beat()==1){
						glPolygonMode(GL_FRONT, GL_FILL);
						glPolygonMode(GL_BACK, GL_FILL);
					}else{
						glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
						glPolygonMode(GL_FRONT, GL_LINE);
						glPolygonMode(GL_BACK, GL_LINE);
					
					}
				}else{
					if(thisframe.solid_render==1){
						glPolygonMode(GL_FRONT, GL_FILL);
						glPolygonMode(GL_BACK, GL_FILL);
					}else{
						glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
						glPolygonMode(GL_FRONT, GL_LINE);
						glPolygonMode(GL_BACK, GL_LINE);
					}
				}
				if(thisframe.audio_scale_type==1){
					tmpfft = get_fft_value((int)thisframe.scale_from_fft)/thisframe.audio_multiplier;
					mesh_set_scale(tmpobj0, tmpfft, tmpfft, tmpfft);
				}else if(thisframe.audio_scale_type==2){
					tmpfft = get_level()/thisframe.audio_multiplier;
					mesh_set_scale(tmpobj0, tmpfft, tmpfft, tmpfft);
				}else{
					mesh_set_scale(tmpobj0, thisframe.scalex, thisframe.scaley, thisframe.scalez);
				}
				
				use_external_texture(tmpobj0, tmpobj1);
				draw_mesh(tmpobj0);
				glPolygonMode(GL_FRONT, GL_FILL);
				glPolygonMode(GL_BACK, GL_FILL);
				
			}
			if(thisframe.type==3){
				/* do texture-image */
			}
			if(thisframe.type==4){
				/* do audio */
			}
			
			if(thisframe.type==5){
				/* do camera */
				if(thisframe.inbuilt_camera==0){
					if(get_beat()==1){
						if(thisframe.last_camera<8){
							songs[s].layers[l].frames[i].last_camera++;
						}else{
							songs[s].layers[l].frames[i].last_camera=1;
						}
					}
					use_inbuilt_camera_path(songs[s].layers[l].frames[i].last_camera);
				}else{	
					use_inbuilt_camera_path(thisframe.inbuilt_camera);
				}
			}
			if(thisframe.type==6){
				/* do midi */
			}
			if(thisframe.type==7){
				/* do dmx */
			}
			if(thisframe.type==8){
				/* do master */
				if(thisframe.seek_frame){
					songs[s].masterseekto = 1;/*thisframe.seek_frame;*/
				}
			}			
		}else{
			/*tweening draw*/
			
		}
	}
}

void song_play_frame(int mysong, int channel){
	/* select song by id*/
	int i, li;
	for(i=0;i<db_get_row_count(songdb);i++){
		if(songs[i].id==mysong){
			/*TODO draw the layers via zindex*/
			songs[i].masterseekto=0;
			for(li=0;li<songs[i].layercount;li++){
				draw_layer_frame(i, li, channel);
			}
			/*TODO time 24 / fps frame to msec*/
			songs[i].currentframe=1;
			if(songs[i].masterseekto!=0){
				songs[i].currentframe=songs[i].masterseekto;
			}
		break;
		}
	}
}

int song_get_object_count(int songid, int layer_slot, int frame_id){
	int objcount=0;
	for (int i=0;i<songs[get_song_slot_from_id(songid)].layers[layer_slot].framecount; i++){
		if(songs[get_song_slot_from_id(songid)].layers[layer_slot].frames[i].frameno==frame_id){
			objcount++;
		}
	}
	return objcount;
}
int song_get_object_slot_from_frame_id(int songid, int layer_slot, int frame_id){
	int i;
	int objcount=0;
	for (i=0;i<songs[get_song_slot_from_id(songid)].layers[layer_slot].framecount; i++){
		if(songs[get_song_slot_from_id(songid)].layers[layer_slot].frames[i].frameno==songs[get_song_slot_from_id(songid)].layers[layer_slot].frames[frame_id].frameno){
			if(i==frame_id){
				break;
			}
			objcount++;
		}
	}
	return objcount;
}

int song_get_object_frame_from_obj_slot(int songid, int layer_slot, int frame_id, int obj_slot){
	int objcount=0;
	int song_slot = get_song_slot_from_id(songid);
	int i;
	for (i=0;i<songs[song_slot].layers[layer_slot].framecount; i++){
		if(songs[song_slot].layers[layer_slot].frames[i].frameno==frame_id){
			if(objcount==obj_slot){
				break;
			}
			objcount++;
		}
	}
	return i;
}

int song_get_object_type(int songid, int layer_slot, int frame_id, int obj_slot){
	int objcount=0;
	int song_slot = get_song_slot_from_id(songid);
	int objtype=0;
	for (int i=0;i<songs[song_slot].layers[layer_slot].framecount; i++){
		if(songs[song_slot].layers[layer_slot].frames[i].frameno==frame_id){
			if(objcount==obj_slot){
				/* 1=video 2=mesh 3=texture 4=audio 5=camera 6=midi 7=dmx 8=master*/
				objtype =songs[song_slot].layers[layer_slot].frames[i].type;
			}
			objcount++;
		}
	}
	return objtype;
}
char *song_get_object_title(int songid, int layer_slot, int frame_id, int obj_slot){
	char *obj_lib_name="nothing";
	int objcount=0;
	int song_slot = get_song_slot_from_id(songid);
	for (int i=0;i<songs[song_slot].layers[layer_slot].framecount; i++){
		if(songs[song_slot].layers[layer_slot].frames[i].frameno==frame_id){
			if(objcount==obj_slot){
				/* 1=video 2=mesh 3=texture 4=audio 5=camera 6=midi 7=dmx 8=master*/
				if(songs[song_slot].layers[layer_slot].frames[i].type==1){
					obj_lib_name = "video";//video__library[songs[song_slot].layers[layer_slot].frames[i].db_id].title;
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==2){
					obj_lib_name = "mesh";//mesh__library[songs[song_slot].layers[layer_slot].frames[i].db_id].title;
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==3){
					obj_lib_name = "image";//texture__library[songs[song_slot].layers[layer_slot].frames[i].db_id].title;
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==4){
					obj_lib_name = "audio"; //audio__library[songs[song_slot].layers[layer_slot].frames[i].db_id].title;
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==5){
					obj_lib_name = "camera";
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==6){
					obj_lib_name = "midi";
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==7){
					obj_lib_name = "dmx";
				}
				if(songs[song_slot].layers[layer_slot].frames[i].type==8){
					obj_lib_name = "master";
				}
			}
			objcount++;
		}
	}
	return obj_lib_name;
}

void set_channel_song(int mychannel, int mysong){
	if(mychannel==1){
		channel_1_song = mysong;
	}
	if(mychannel==2){
		channel_2_song = mysong;
	}
}
int get_song_id_from_slot(int slotid){
	return songs[slotid].id;
}
char *song_get_name_by_slot(int slotid){
	return songs[slotid].title;
}
char *song_get_name_by_id(int songid){
	return songs[get_song_slot_from_id(songid)].title;
}
int song_get_count(void){
	/* this will have to be modified eventually to songs not from db */
	return db_get_row_count(songdb);
}

int song_get_from_channel(int mychannel){
	if(mychannel==1){
		return channel_1_song;
	}else if(mychannel==2){
		return channel_2_song;
	}else{
		return 0;
	}
}
int get_song_slot_from_id(int songid){
	int i;
	for(i=0;i<db_get_row_count(songdb);i++){
		if(songs[i].id==songid){
			break;
		}
	}
	return i;
}
int song_get_layercount(int songid){
	return songs[get_song_slot_from_id(songid)].layercount;
}

char *song_get_layer_name(int songid, int layer_slot){
	return songs[get_song_slot_from_id(songid)].layers[layer_slot].layer_name;
	
}
void exec_channel_1_song(void){
	open_channel_canvas(1);
		if(channel_1_song){
			song_play_frame(channel_1_song, 1);
		}else{
			/* this eventually  will be a user set fall back*/
			use_inbuilt_camera_path(1);
			draw_oscilliscope_4_3d();
		}
	close_channel_canvas(1);
}

void exec_channel_2_song(void){
	open_channel_canvas(2);
		if(channel_2_song){
			song_play_frame(channel_2_song, 2);
		}else{
			/* this eventually  will be a user set fall back*/
			use_inbuilt_camera_path(1);
			draw_oscilliscope_4_3d();
		}
	close_channel_canvas(2);
}
float warp=0.01;
void exec_channel_mix(void){
	/* maybe the audio has to be mixed seperately here */
	int chwidth, chheight;
	open_channel_canvas(3);
		/*this will have wipes/disolves and possibly become mix.h/mix.c*/
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);	
		glMatrixMode(GL_PROJECTION);	
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, getwinwidth(), 0, getwinheight(),-1,5000);
		glMatrixMode(GL_MODELVIEW);	
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glPushMatrix();	
		glLoadIdentity();
		glEnable(GL_TEXTURE_RECTANGLE_NV);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_RECTANGLE_NV, get_channel_texture(1));
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_NV, 0,  GL_TEXTURE_WIDTH, &chwidth);
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_NV, 0,  GL_TEXTURE_HEIGHT, &chheight);
		/*draw canvas 1*/
		glBegin(GL_QUADS);
			glTexCoord2f(chwidth, chheight);  
			glVertex2f(getwinwidth(), getwinheight());
			glTexCoord2f(0, chheight);  
			glVertex2f(0, getwinheight());
			glTexCoord2f(0, 0);  
			glVertex2f(0,0);
			glTexCoord2f(chwidth, 0); 
			glVertex2f(getwinwidth(),0);
		glEnd();	
		/*set alpha per main slider*/
		glColor4f(1.0, 1.0, 1.0, 1.0-get_video_mix_slide());
		glBindTexture(GL_TEXTURE_RECTANGLE_NV, get_channel_texture(2));
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_NV, 0,  GL_TEXTURE_WIDTH, &chwidth);
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_NV, 0,  GL_TEXTURE_HEIGHT, &chheight);
		/*draw canvas 2*/
		glBegin(GL_QUADS);
			glTexCoord2f(chwidth, chheight);  
			glVertex2f(getwinwidth(), getwinheight());
			glTexCoord2f(0, chheight);  
			glVertex2f(0, getwinheight());
			glTexCoord2f(0, 0);  
			glVertex2f(0,0);
			glTexCoord2f(chwidth, 0); 
			glVertex2f(getwinwidth(),0);
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
		
	close_channel_canvas(3);
	if(beatblur==1){
		if(get_beat()==1){
			outputrender=2;
		}else{	
			outputrender=1;
		}
	}
	if(outputrender!=1){
		open_channel_canvas(3);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);	
		glMatrixMode(GL_PROJECTION);	
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, geteditorwidth(), 0, getwinheight(),-1,5000);
		glMatrixMode(GL_MODELVIEW);	
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glPushMatrix();	
		glLoadIdentity();
		glEnable(GL_TEXTURE_RECTANGLE_NV);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_RECTANGLE_NV, get_channel_texture(3));
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_NV, 0,  GL_TEXTURE_WIDTH, &chwidth);
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_NV, 0,  GL_TEXTURE_HEIGHT, &chheight);
		
		if(outputrender==2){
			int times=10;
			float spost = 0.0f;		
			float alphainc = 0.9f / times;	
			float alpha = 0.25f;	
			alphainc = alpha / times;
			for (int num = 0;num < times;num++){
				glBegin(GL_QUADS);			
				glColor4f(1.0f, 1.0f, 1.0f, alpha);	
				glTexCoord2f(0+spost,chheight-spost);	
				glVertex2f(0,getwinheight());

				glTexCoord2f(0+spost,0+spost);		
				glVertex2f(0,0);			

				glTexCoord2f(chwidth-spost,0+spost);		
				glVertex2f(geteditorwidth(),0);
			
				glTexCoord2f(chwidth-spost,chheight-spost);		
				glVertex2f(geteditorwidth(),getwinheight());
	
				spost += 5;		
				alpha = alpha - alphainc;
				glEnd();	
			}		
		}
		
		if(outputrender==3){
		glBegin(GL_QUADS);
			glTexCoord2f(0, chheight);  
			glVertex2f(geteditorwidth()/2, getwinheight()/2);
			glTexCoord2f(chwidth, chheight);  
			glVertex2f(0, getwinheight()/2);
			glTexCoord2f(chwidth, 0);  
			glVertex2f(0,0);
			glTexCoord2f(0, 0); 
			glVertex2f(geteditorwidth()/2,0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(chwidth, 0);  
			
			glVertex2f(0, getwinheight());
			glTexCoord2f(0, 0); 			
			glVertex2f(geteditorwidth()/2, getwinheight());
			glTexCoord2f(0, chheight);  
			glVertex2f(geteditorwidth()/2,getwinheight()/2);

			glTexCoord2f(chwidth, chheight);  
			glVertex2f(0,getwinheight()/2);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(chwidth, chheight);  
			glVertex2f(geteditorwidth(), getwinheight()/2);
			glTexCoord2f(0, chheight);  
			glVertex2f(geteditorwidth()/2, getwinheight()/2);
			glTexCoord2f(0, 0);  
			glVertex2f(geteditorwidth()/2,0);
			glTexCoord2f(chwidth, 0); 
			glVertex2f(geteditorwidth(),0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(chwidth, chheight);  
			glVertex2f(geteditorwidth(), getwinheight()/2);
			glTexCoord2f(0, chheight);  
			glVertex2f(geteditorwidth()/2, getwinheight()/2);
			glTexCoord2f(0, 0);  
			glVertex2f(geteditorwidth()/2, getwinheight());
			glTexCoord2f(chwidth, 0); 
			glVertex2f(geteditorwidth(), getwinheight());
		glEnd();
		}


		glColor4f(1.0, 1.0, 1.0, 1.0);
		glDisable(GL_TEXTURE_RECTANGLE_NV);
		glDisable(GL_BLEND);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();			
		glMatrixMode(GL_MODELVIEW);	
		glPopMatrix();
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
			
	close_channel_canvas(3);
	}
}	

/* the attribute set functions */
void song_set_title(int song_real, char * title){
	songs[song_real].title = title;
}

void song_set_object_camera_id(int song_real, int layer_slot, int obj_real, int camera_id){
	songs[song_real].layers[layer_slot].frames[obj_real].inbuilt_camera = camera_id;
}

void song_set_object_render(int song_real, int layer_slot, int obj_real, int solid){
	if(solid==0){
		songs[song_real].layers[layer_slot].frames[obj_real].solid_render=1;
	}else{
		songs[song_real].layers[layer_slot].frames[obj_real].solid_render=0;
	}	
}
void song_set_object_width_height(int song_real, int layer_slot, int obj_real, int width, int height){
	songs[song_real].layers[layer_slot].frames[obj_real].height=height;
	songs[song_real].layers[layer_slot].frames[obj_real].width=width;
}
void song_set_object_texture(int song_real, int layer_slot, int obj_real, int textdbid){
	songs[song_real].layers[layer_slot].frames[obj_real].use_texture=textdbid;
}

void song_set_object_colour(int song_real, int layer_slot, int obj_real, float r, float g, float b, float a){
	songs[song_real].layers[layer_slot].frames[obj_real].colour_r = r;
	songs[song_real].layers[layer_slot].frames[obj_real].colour_g = g;
	songs[song_real].layers[layer_slot].frames[obj_real].colour_b = b;
	songs[song_real].layers[layer_slot].frames[obj_real].colour_a = a;
}

void song_set_object_postion(int song_real, int layer_slot, int obj_real,  float x, float y, float z){
	songs[song_real].layers[layer_slot].frames[obj_real].x = x;
	songs[song_real].layers[layer_slot].frames[obj_real].y = y;
	songs[song_real].layers[layer_slot].frames[obj_real].z = z;
}
void song_set_object_rotation(int song_real, int layer_slot, int obj_real,  float x, float y, float z, float degree, int rauto){
	songs[song_real].layers[layer_slot].frames[obj_real].rotation_x= x;
	songs[song_real].layers[layer_slot].frames[obj_real].rotation_y = y;
	songs[song_real].layers[layer_slot].frames[obj_real].rotation_z = z;
	songs[song_real].layers[layer_slot].frames[obj_real].rotation_degree = degree;
	songs[song_real].layers[layer_slot].frames[obj_real].rotation_auto_animation = rauto;
}
void song_set_object_scale(int song_real, int layer_slot, int obj_real,  float sx, float sy, float sz){
	songs[song_real].layers[layer_slot].frames[obj_real].scalex = sx;
	songs[song_real].layers[layer_slot].frames[obj_real].scaley = sy;
	songs[song_real].layers[layer_slot].frames[obj_real].scalez = sz;
}
void set_scale_from_fft(int song_real, int layer_slot, int obj_real, int myfft){
	songs[song_real].layers[layer_slot].frames[obj_real].scale_from_fft = myfft;
}
void set_scale_audio_multiplier(int song_real, int layer_slot, int obj_real, float multiplier){
	songs[song_real].layers[layer_slot].frames[obj_real].audio_multiplier = multiplier;
}
void set_audio_scale_type(int song_real, int layer_slot, int obj_real, int sclip){
	songs[song_real].layers[layer_slot].frames[obj_real].audio_scale_type=sclip;
}
void set_beat_render(int song_real, int layer_slot, int obj_real, int beatrend){
	songs[song_real].layers[layer_slot].frames[obj_real].beat_render=beatrend;
}
/* attribute get functions */
int song_get_object_camera_id(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].inbuilt_camera;
}
int song_get_object_render(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].solid_render;
}
float song_get_object_colour_r(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].colour_r;
}
float song_get_object_colour_g(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].colour_g;
}
float song_get_object_colour_b(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].colour_b;
}
float song_get_object_colour_a(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].colour_a;
}
float song_get_object_position_x(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].x;
}
float song_get_object_position_y(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].y;
}
float song_get_object_position_z(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].z;
}
float song_get_object_rotation_x(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].rotation_x;
}
float song_get_object_rotation_y(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].rotation_y;
}
float song_get_object_rotation_z(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].rotation_z;
}
int song_get_object_rotation_auto(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].rotation_auto_animation;
}
float song_get_object_rotation_degree(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].rotation_degree;
}
float song_get_object_scale_x(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].scalex;
}
float song_get_object_scale_y(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].scaley;
}
float song_get_object_scale_z(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].scalez;
}

int get_audio_scale_type(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].audio_scale_type;
}
int get_scale_from_fft(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].scale_from_fft;
}
float get_scale_audio_multiplier(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].audio_multiplier;
}
int get_beat_render(int song_real, int layer_slot, int obj_real){
	return songs[song_real].layers[layer_slot].frames[obj_real].beat_render;
}


/* some song controls */
void song_play(int channel){
	if(channel==1){
		channel_1_pause=0;
	}else{
		channel_2_pause=0;
	}
}
void song_rewind(int channel){

}
void song_pause(int channel){
	if(channel==1){
		channel_1_pause=1;
	}else{
		channel_2_pause=1;
	}
}

/* song save function */

void song_system_save(){
	/* go through each song and save it as a new file || there is heaps more to do on this */
	FILE * pFile;
	char fname[2];
	chdir("/home/instant/.oko-t/");
	if(chdir("/home/tobias/.oko-t/songs")!=0){
		for(int si=0;si<db_get_row_count(songdb);si++){
			/*open file*/
			sprintf(fname, "%i", songs[si].id);
			pFile = fopen (fname,"wt");
			fprintf (pFile, "<song=\"%s\">\n", songs[si].title);
			for(int i=0;i<songs[si].layercount;i++){
				fprintf (pFile, "<layer=\"%s\">\n", songs[si].layers[i].layer_name);
				fprintf (pFile, "<zindex=\"%s\">\n", songs[si].layers[i].layer_name);
				for(int fi=0;fi<songs[si].layers[i].framecount;fi++){
					fprintf (pFile, "<frame=\"%i\">\n", songs[si].layers[i].frames[fi].frameno);
					if(songs[si].layers[i].frames[fi].type==1){
						fprintf (pFile, "<video=\"%i\">\n", songs[si].layers[i].frames[fi].db_id);
						if(songs[si].layers[i].frames[fi].audio_scale_type==1){
							fprintf (pFile, "<audio_scale_type=\"1\">\n");
							fprintf (pFile, "<audio_multiplier=\"%f\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
							fprintf (pFile, "<scale_from_fft=\"%i\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
						}
						if(songs[si].layers[i].frames[fi].audio_scale_type==2){
							fprintf (pFile, "<audio_scale_type=\"1\">\n");
							fprintf (pFile, "<audio_multiplier=\"%f\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
						}
						if(songs[si].layers[i].frames[fi].beat_render==1){
							fprintf (pFile, "<beat_render=\"1\">\n");
						}
						if(songs[si].layers[i].frames[fi].beat_render==2){
							fprintf (pFile, "<beat_render=\"2\">\n");
						}
						fprintf (pFile, "<colour=\"%f %f %f %f\">\n", songs[si].layers[i].frames[fi].colour_r, songs[si].layers[i].frames[fi].colour_g,  songs[si].layers[i].frames[fi].colour_b,  songs[si].layers[i].frames[fi].colour_a);
						fprintf (pFile, "<position=\"%f %f %f\">\n", songs[si].layers[i].frames[fi].x, songs[si].layers[i].frames[fi].y, songs[si].layers[i].frames[fi].z);
						fprintf (pFile, "<rotate=\"%f %f %f %f\">\n", songs[si].layers[i].frames[fi].rotation_degree, songs[si].layers[i].frames[fi].rotation_x, songs[si].layers[i].frames[fi].rotation_y, songs[si].layers[i].frames[fi].rotation_z);
						if(songs[si].layers[i].frames[fi].rotation_auto_animation==1){
							fprintf (pFile, "<rotation_auto_animation>\n");
						}
						fprintf (pFile, "<width_fullscreen>");
						fprintf (pFile, "<height_fullscreen>");
					}
					if(songs[si].layers[i].frames[fi].type==2){
						fprintf (pFile, "<mesh=\"%i\">\n", songs[si].layers[i].frames[fi].db_id);
						fprintf (pFile, "<use_texture=\"%i\">\n", songs[si].layers[i].frames[fi].use_texture);
						if(songs[si].layers[i].frames[fi].solid_render==1){
							fprintf (pFile, "<solid_render>\n");
						}
						if(songs[si].layers[i].frames[fi].audio_scale_type==1){
							fprintf (pFile, "<audio_scale_type=\"1\">\n");
							fprintf (pFile, "<audio_multiplier=\"%f\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
							fprintf (pFile, "<scale_from_fft=\"%i\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
						}
						if(songs[si].layers[i].frames[fi].audio_scale_type==2){
							fprintf (pFile, "<audio_scale_type=\"1\">\n");
							fprintf (pFile, "<audio_multiplier=\"%f\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
						}
						if(songs[si].layers[i].frames[fi].beat_render==1){
							fprintf (pFile, "<beat_render=\"1\">\n");
						}
						if(songs[si].layers[i].frames[fi].beat_render==2){
							fprintf (pFile, "<beat_render=\"2\">\n");
						}
						fprintf (pFile, "<colour=\"%f %f %f %f\">\n", songs[si].layers[i].frames[fi].colour_r, songs[si].layers[i].frames[fi].colour_g,  songs[si].layers[i].frames[fi].colour_b,  songs[si].layers[i].frames[fi].colour_a);
						fprintf (pFile, "<position=\"%f %f %f\">\n", songs[si].layers[i].frames[fi].x, songs[si].layers[i].frames[fi].y, songs[si].layers[i].frames[fi].z);
						fprintf (pFile, "<rotate=\"%f %f %f %f\">\n", songs[si].layers[i].frames[fi].rotation_degree, songs[si].layers[i].frames[fi].rotation_x, songs[si].layers[i].frames[fi].rotation_y, songs[si].layers[i].frames[fi].rotation_z);
						fprintf (pFile, "<scale=\"%f %f %f\">\n", songs[si].layers[i].frames[fi].scalex, songs[si].layers[i].frames[fi].scaley, songs[si].layers[i].frames[fi].scalez);
						if(songs[si].layers[i].frames[fi].rotation_auto_animation==1){
							fprintf (pFile, "<rotation_auto_animation>\n");
						}
					}	
					if(songs[si].layers[i].frames[fi].type==3){
						fprintf (pFile, "<texture=\"%i\">\n", songs[si].layers[i].frames[fi].db_id);
						if(songs[si].layers[i].frames[fi].audio_scale_type==1){
							fprintf (pFile, "<audio_scale_type=\"1\">\n");
							fprintf (pFile, "<audio_multiplier=\"%f\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
							fprintf (pFile, "<scale_from_fft=\"%i\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
						}
						if(songs[si].layers[i].frames[fi].audio_scale_type==2){
							fprintf (pFile, "<audio_scale_type=\"1\">\n");
							fprintf (pFile, "<audio_multiplier=\"%f\">\n", songs[si].layers[i].frames[fi].audio_multiplier);
						}
						if(songs[si].layers[i].frames[fi].beat_render==1){
							fprintf (pFile, "<beat_render=\"1\">\n");
						}
						if(songs[si].layers[i].frames[fi].beat_render==2){
							fprintf (pFile, "<beat_render=\"2\">\n");
						}
						fprintf (pFile, "<colour=\"%f %f %f %f\">\n", songs[si].layers[i].frames[fi].colour_r, songs[si].layers[i].frames[fi].colour_g,  songs[si].layers[i].frames[fi].colour_b,  songs[si].layers[i].frames[fi].colour_a);
						fprintf (pFile, "<position=\"%f %f %f\">\n", songs[si].layers[i].frames[fi].x, songs[si].layers[i].frames[fi].y, songs[si].layers[i].frames[fi].z);
						fprintf (pFile, "<rotate=\"%f %f %f %f\">\n", songs[si].layers[i].frames[fi].rotation_degree, songs[si].layers[i].frames[fi].rotation_x, songs[si].layers[i].frames[fi].rotation_y, songs[si].layers[i].frames[fi].rotation_z);
						if(songs[si].layers[i].frames[fi].rotation_auto_animation==1){
							fprintf (pFile, "<rotation_auto_animation>\n");
						}
					}
					if(songs[si].layers[i].frames[fi].type==4){
						fprintf (pFile, "<audio=\"%i\">\n", songs[si].layers[i].frames[fi].db_id);
					}
					if(songs[si].layers[i].frames[fi].type==5){
						fprintf (pFile, "<camera>\n");
						if(songs[si].layers[i].frames[fi].inbuilt_camera>0){
							fprintf (pFile, "<inbuilt_camera=\"%i\">\n", songs[si].layers[i].frames[fi].inbuilt_camera);
						}
					}
					if(songs[si].layers[i].frames[fi].type==8){
						fprintf (pFile, "<master>\n");
						fprintf (pFile, "<seek_frame=\"%i\">\n", songs[si].layers[i].frames[fi].seek_frame);
					}

				}
			}
			/*close file*/
			fclose (pFile);
			printf("wrote song file::\n");
		}	
	}
	// save the song database
	if(chdir("/home/instant/.oko-t/db")==0){
		pFile = fopen("songs","wt");
		//if (pFile!=NULL){
		for(int si=0;si<db_get_row_count(songdb);si++){
			fprintf(pFile, "%i#%s%i#%s\n", songs[si].id, "/home/instant/.oko-t/", songs[si].id, songs[si].title);
		}
		fclose (pFile);
		printf("wrote database file::\n");
		//}
	}
}
