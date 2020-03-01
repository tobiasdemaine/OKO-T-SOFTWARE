#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library


/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/


#define MAX_VERTICES 60000 // Max number of vertices (for each object)
#define MAX_POLYGONS 60000 // Max number of polygons (for each object)

// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
	char name[20];
    
	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES]; 
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture;
} obj_type, *obj_type_ptr;


