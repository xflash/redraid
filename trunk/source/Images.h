#ifndef __Images_h__
#define __Images_h__

typedef struct {
	int ID;
	const char* bytes;
	int size;
	int frameW;
	int frameH;
	int duration;
} T_IMAGE;

extern const T_IMAGE images[];
extern unsigned int getImagesSize();


enum {
	ID_CREEP    = 0,
	ID_HEALTH   = 1,
	ID_BULLET   = 2,
	ID_SELECTOR = 3,
	
	ID_MAX
};

#endif
