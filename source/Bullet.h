#ifndef __BULLET_h__
#define __BULLET_h__

#include <ulib/ulib.h>
#include "Actor.h"
#include "Movable.h"
#include "Drawable.h"
#include "Collidable.h"
#include "Selectable.h"
#include "Selector.h"

class Bullet : public Actor, public Movable, public Drawable, public Collidable{
private:
	Selector* selector;
public:
	
	void init(InitActorArgs* args) {
		selector = (Selector*) (*args)[0];
		initDraw(ID_BULLET);
	}
	
	void draw() {
		Drawable::draw();
		ulDrawFillRect(getDrawUpX(), getDrawUpY(),
									 getDrawLowX(), getDrawLowY(),
									 RGB15(16, 0, 0));
	}
	
	void move() { 
		Collidable::checkCollision();
		Movable::move();
		//bounce();
		hitDeath();
	}
	
	void doCollide(Collidable* target) { }
	
private:
	void hitDeath() {
		if ( getY() < 0 || getDrawLowY() > UL_SCREEN_HEIGHT
			|| getX() < 0 || getDrawLowX() > UL_SCREEN_WIDTH) {
				exists(false);
		}
	}
	
	void bounce() {
		//Handle collisions with the screen borders
		if (getY() < 0) {
			setAngle(2*UL_PI - getAngle());
      setY(0);
   }   
   else if (getDrawLowY() > UL_SCREEN_HEIGHT)			{
			setAngle(2*UL_PI - getAngle());
      setY(UL_SCREEN_HEIGHT - getDrawFrameH());
   }   
	
		if (getX() < 0)			{
			setAngle(UL_PI - getAngle());
      setX(0);
   }   
   else if (getDrawLowX() > UL_SCREEN_WIDTH)			{
			setAngle(UL_PI - getAngle());
      setX(UL_SCREEN_WIDTH - getDrawFrameW());
	 }   
	}

protected:
	int getDrawCenterX()    { return getX(); }
	int getDrawCenterY()    { return getY(); }
	int getDrawAngle()			{ return getAngle();}
	
	int getCollideX() { return getDrawUpX()-1; }
	int getCollideY() { return getDrawUpY()-1; }
	int getCollideW() { return getDrawFrameW()-2; }
	int getCollideH() { return getDrawFrameH()-2; }
	
};

#endif
