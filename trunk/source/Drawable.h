#ifndef Drawable_h
#define Drawable_h

#include <ulib/ulib.h>
#include "ResourceLoader.h"

// Base class for Drawable objects
class Drawable {
private:
	UL_IMAGE *img;
private:
	int width, height;
protected:
	u16 color;

public:
	Drawable():img(NULL) { }
	virtual ~Drawable() { }
	
	void initDraw(int imageID) {
		img = (UL_IMAGE*)ResourceLoader::Get()->getResource(imageID);
		//White by default
		color = 0x7fff;
	}
	   
	void draw(){
		//Set the ball color
		ulSetImageTint(img, getColor());
		
		//rotate the image
		img->angle = getDrawAngle();
	
		// move the image center and the rotation center 
//		img->centerX = getDrawFrameX() + getDrawFrameW()>>1;
//		img->centerY = getDrawFrameY() + getDrawFrameH()>>1;
		img->centerX = getDrawFrameW()>>1;
		img->centerY = getDrawFrameH()>>1;
		
		//draw only the frame in the sprite sheet
		ulSetImageTileSize(img, 
												getDrawFrameX(), getDrawFrameY(), 
												getDrawFrameW(), getDrawFrameH());
		
		//Draw the image
/*
		ulDrawFillRect(getDrawUpX(), getDrawUpY(),
									 getDrawLowX(), getDrawLowY(),
									 RGB15(16, 0, 0));
*/		
		ulDrawImageXY(img, getDrawCenterX(), getDrawCenterY());
		//ulPrintf_xy(getDrawCenterX(), getDrawCenterY(), "%d", getDrawAngle());

	}


	
public:
	inline void setColor(u16 c) { color=c; }
	inline u16 getColor() { return color; }
	
	virtual int getDrawUpX()  { return getDrawCenterX()-(getDrawFrameW()>>1); }
	virtual int getDrawUpY()  { return getDrawCenterY()-(getDrawFrameH()>>1); }
	virtual int getDrawLowX() { return getDrawCenterX()+(getDrawFrameW()>>1); }
	virtual int getDrawLowY() { return getDrawCenterY()+(getDrawFrameH()>>1); }

protected:
	//override those to position the drawing
	virtual int getDrawFrameX() { return 0; }
	virtual int getDrawFrameY() { return 0; }
	// implement those to position the image center
	virtual int getDrawCenterX()=0;
	virtual int getDrawCenterY()=0;
	virtual int getDrawAngle()=0;

	// Default dimensions are determined with the image size
	// may be overriden
	virtual int getDrawFrameW() { return getDrawW(); }
	virtual int getDrawFrameH() { return getDrawH(); }

private:
	int getDrawW() { return img->sizeX; }
	int getDrawH() { return img->sizeY; }

};



#endif
