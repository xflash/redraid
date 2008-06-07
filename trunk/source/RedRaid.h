#ifndef __RedRaid_h__
#define __RedRaid_h__

#include <ulib/ulib.h>
#include "Game.h"
#include "ActorPool.h"
#include "Bullet.h"
#include "Creep.h"
#include "Selector.h"

#define MAX_BULLET_POOL 500
#define MAX_CREEP_POOL 50
#define MAX_CREEP_START 6

class RedRaid : public Game {
private:
	Selector selector;
	ActorPool<Bullet> bulletsPool;
	ActorPool<Creep> creepsPool;
		
public:
	RedRaid() {
		InitActorArgs args;
		args.push_back(&selector);
		bulletsPool.createActors(MAX_BULLET_POOL, &args);
		
		args.push_back(&bulletsPool);
		creepsPool.createActors(MAX_CREEP_POOL, &args);
	}
	
private:
	void beforeRun() {
		int midScreenX = SCREEN_WIDTH>>1;
		int midScreenY = SCREEN_HEIGHT>>1;
		int sep=20;
		Creep* c;
		
		selector.init();
		
		for(int i=0; i<MAX_CREEP_START; i++) {
			c = creepsPool.getInstance();
			u16 angle = i * 512 / MAX_CREEP_START;
			c->initMove(midScreenX + ulCos(angle, sep),
									midScreenY + ulSin(angle, sep),
									angle, 0);
		}
	}
	
/*
	void spray() {
		if (ul_keys.held.touch) {
			Bullet* b = bulletsPool.getInstance();
			if(b!=NULL) {
				b->initMove(ul_keys.touch.x, ul_keys.touch.y, rand() % (2 * UL_PI), 1 + rand() % 1);
			}
		}
	}
*/
	
	void update() {
		selector.update();
		creepsPool.move();
		bulletsPool.move();
	}
	
	void drawTop() {
		//ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 24), RGB15(0, 16, 31), RGB15(0, 16, 31));
	}
	
	void drawBottom() {
//		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 16, 31), RGB15(0, 16, 31), RGB15(16, 24, 31), RGB15(16, 24, 31));
		//ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 24), RGB15(0, 16, 31), RGB15(0, 16, 31));
		ulDrawGradientRect(0, 0, UL_SCREEN_WIDTH, UL_SCREEN_HEIGHT, 
					RGB15(0, 24, 0), RGB15(0, 24, 0), 
					RGB15(0, 31, 16), RGB15(0, 31, 16));
		
		selector.draw();
		creepsPool.draw();
		bulletsPool.draw();

		ulPrintf_xy(0, 0, 
			"Bullets %d/%d %d", bulletsPool.getNum(), bulletsPool.getNumMax(), bulletsPool.getIndex());
		ulPrintf_xy(0, 8, 
			"Current time %f", currentTime);
	}
};

#endif
