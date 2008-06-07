#ifndef __CREEP_h__
#define __CREEP_h__

#include <ulib/ulib.h>
#include "Game.h"
#include "Actor.h"
#include "Movable.h"
#include "Drawable.h"
#include "Selector.h"
#include "Health.h"
#include "ActorPool.h"
#include "Bullet.h"

#define MAX_SHOOT_TIME 10
#define MAX_HEALTH_CREEP 100
#define MOVING_SPEED 2

class Game;

//512 = 2Pi  = 360°
//256 = 1Pi  = 180°
//128 = Pi/2 = 90°
//85  = Pi/3 = 60°
//64  = Pi/4 = 45°
//42  = Pi/6 = 30°

int angleDelta[] = { 0, -42, 42, -64, 64 } ;
int speeds[]     = { 2, 4,   4,  3,   3} ;
int maxAngleDelta = sizeof(angleDelta) / sizeof(angleDelta[0]);

class Creep : public Actor, public Movable, public Drawable, public Selectable  {
private:
	Health health;
	Selector* selector;

	bool shooting;
	int shootCompteur;
	ActorPool<Bullet>* pool;
	int frame;
	int live;
	bool moving;
	int move2X, move2Y;

public:
	void init(InitActorArgs* args) {
		selector = (Selector*) (*args)[0];
		pool = (ActorPool<Bullet>*) (*args)[1];
		shooting=false;
	}
	
	void activate() {
		selector->addSelectable(this);
		shooting=false;
		live=MAX_HEALTH_CREEP;
		initDraw(ID_CREEP);
		health.init(live);
		frame=0;
		moving=false;
		move2X=getX();
		move2Y=getY();

		shootCompteur=MAX_SHOOT_TIME;
	}

	void deactivate() {
		selector->removeSelectable(this);
	}
	
	void move() { 
		Movable::move();
		health.update(getX(), getDrawLowY(), live);
		++frame;
		bounce();
		
		if(moving) {
			//
		}
		
		
		if(selected) {
			shootCompteur--;
			if(shootCompteur<=0) {
				shooting=true;
				shootCompteur=MAX_SHOOT_TIME;
			}
		}
			
		if(shooting) {
			shooting=false;
			for (int i=0;i<maxAngleDelta; i++) {
				Bullet* b = pool->getInstance();
				if (b!=NULL) {
					int a = getAngle() + angleDelta[i];
					b->initMove(getX(), getY(), a, speeds[i]);
				}
			}
		}
		
		if(getX()==move2X && getY()==move2Y) {
			setSpeed(0);
		}
		
	}
	
	void draw() { 
		Drawable::draw(); 
		if(selected)
			health.draw();
			
		//ulDrawLine (getX(), getY(), move2X, move2Y, RGB15(32,0,0));
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
	
	void handleStop() {
		moving=false;
		setSpeed(0);
	}
	
	void handleMove(int angle) {
		moving=true;
		//move2X=x, move2Y=y;
		
		setAngleSpeed(angle, MOVING_SPEED);
// 		setAngleSpeed(PA_GetAngle(getX(), getY(), move2X, move2Y), MOVING_SPEED);
		//setPolarCoord(move2X, move2Y);
		//setAngleSpeed(getAngle(move2X, move2Y), MOVING_SPEED);
	}
	
protected:
	virtual int getDrawFrameW() { return 16; }
	
	virtual int getDrawFrameX() { return getDrawFrameW()*(frame%8); }

	int getDrawCenterX()    { return getX(); }
	int getDrawCenterY()    { return getY(); }
	int getDrawAngle(){ return getAngle();}
	
	int getCollideX() { return getDrawUpX()-1; }
	int getCollideY() { return getDrawUpY()-1; }
	int getCollideW() { return getDrawFrameW()-2; }
	int getCollideH() { return getDrawFrameH()-2; }

	int getSelectableX() { return getDrawUpX(); }
	int getSelectableY() { return getDrawUpY(); }
	int getSelectableW() { return getDrawFrameW(); }
	int getSelectableH() { return getDrawFrameH(); }

};

#endif
