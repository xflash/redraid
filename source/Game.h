#ifndef __GAME_h__
#define __GAME_h__

#include <ulib/ulib.h>
#include "ResourceLoader.h"
#define timers2ms(tlow,thigh) ((tlow>>5)+(thigh<<11))

#define ONE_SCREEN

class Game {
protected:
	double currentTime;
	double timeThreshold;
	double elapsedFrameTime;
	int frameCount;
		
private:
	void init() {
		ulInit(UL_INIT_ALL);
		ulInitGfx();
		ulInitText();
		
#ifdef ONE_SCREEN
		ulSetMainLcd(0);
#else
			ulInitDualScreenMode();
#endif

		ulSetTransparentColor(RGB15(31, 0, 31));
		
		timeThreshold = 0.02;
		
		TIMER0_DATA=0;
		TIMER1_DATA=0;
		TIMER0_CR=TIMER_DIV_1024| TIMER_ENABLE;
		TIMER1_CR=TIMER_CASCADE| TIMER_ENABLE;
		currentTime = getTime();
		frameCount=0;
	}	

protected:
	virtual void beforeRun()=0;
	virtual void update()=0;
	virtual void drawTop()=0;
	virtual void drawBottom()=0;

public:
	Game() {
		init();
	}
	virtual ~Game() {}
	
	void run() {
		
		ulStartDrawing2D();
			ulDrawGradientRect(0, 0, 256, 192, 
				RGB15(0, 16, 31), RGB15(0, 16, 31),
				RGB15(0, 0, 24), RGB15(0, 0, 24) );
			ulPrintf_xy(0, 0, "Loading %d resources... ",getImagesSize());
			ResourceLoader::Get()->loadAll();
			ResourceLoader::Get()->dumpLoaded(0,0);
		ulEndDrawing();
		ulSyncFrame();

		beforeRun();

		while(1) {
			frameCount++;
			//elapsedFrameTime = advance();
			
			ulReadKeys(0);
			update();

	
			ulStartDrawing2D();
#ifdef ONE_SCREEN
			drawBottom();
#else
			if (!ulGetMainLcd())		{
				//We're on the top screen
				drawTop();
			} else {
				drawBottom();
			}
#endif
			ulEndDrawing();
			ulSyncFrame();
		}
	}
	
private:
	double advance() {
	  double now, elapsed;
		while (true) {
			now = getTime();
			elapsed = now - currentTime;
	
			if (elapsed < timeThreshold)
				pause ((int)((timeThreshold - elapsed) * 1000));
			else
				break;
		}
		currentTime += elapsed;
		return elapsed;
	}

	void pause(u32 ms){
	   u32 now;
	   now = timers2ms (TIMER0_DATA, TIMER1_DATA);
	   while ((u32) timers2ms (TIMER0_DATA, TIMER1_DATA) < now + ms);
	}
	
	double getTime() {
	  double res;
	
	  u16  v2ms = timers2ms (TIMER0_DATA, TIMER1_DATA);
	  res = ((double)v2ms)/1000;
	  
	  return res;
	}
};

#endif
