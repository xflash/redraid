#ifndef __HEALTH_h__
#define __HEALTH_h__

#include <ulib/ulib.h>
#include "Drawable.h"

class Health : public Drawable {
private:
	int x;
	int y;
	int level;
	int lifeMax;
	
public:
	Health() {
	}
	
	void init(int lm) {
		lifeMax=lm;
		initDraw(ID_HEALTH);
	}
	
	void update(int px, int py, int plevel) { 
		x=px;
		y=py+getDrawFrameH();
		level=plevel;
	}

	void draw() { 
		//ulDrawFillRect (getSelectableX(), getSelectableY(), getSelectableLowX(), getSelectableLowY(), RGB15(0, 16, 31));
		Drawable::draw(); 
	}
	
protected:
	virtual int getDrawFrameW() { return 31; }
	virtual int getDrawFrameH() { return 4; }
	
	virtual int getDrawFrameY() { return getDrawFrameH()*(level%11); }
	
	int getDrawCenterX() { return x; }
	int getDrawCenterY() { return y; }
	int getDrawAngle()   { return 0;}
	
};

#endif
