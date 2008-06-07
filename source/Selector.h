#ifndef __Selector_h__
#define __Selector_h__

#include <ulib/ulib.h>
#include "Selectable.h"
#include "ResourceLoader.h"
#include <list>

class Selector {
private:
	int startSelX,startSelY;
	int endSelX,endSelY;
	int orderX, orderY;
	int centerX, centerY;
	std::list<Selectable*> selectableObjects;
	std::list<Selectable*> selectedObjects;
	bool selectionMode;
	bool order;
	UL_IMAGE* imageselected;
	int frame;
	
public:
	Selector() {
		order=selectionMode=false;
		frame=0;
	}
	
	void init() {
		imageselected = (UL_IMAGE*)ResourceLoader::Get()->getResource(ID_SELECTOR);
	}
	
	void update() {
		frame++;
		if (ul_keys.touch.click) {
			if(ul_keys.held.L || ul_keys.held.R) {
				selectionMode=false;
				order = true;
				orderX=ul_keys.touch.x;
				orderY=ul_keys.touch.y;
			} else if(!selectionMode) {
				selectionMode=true;
				startSelX=ul_keys.touch.x;
				startSelY=ul_keys.touch.y;
			}
		}
		if (ul_keys.touch.released) {
			if(selectionMode) {
				selectionMode=false;
			}
		}
		if (ul_keys.touch.held) {
			if(selectionMode) {
				endSelX=ul_keys.touch.x;
				endSelY=ul_keys.touch.y;
			}
		}
		
		std::list<Selectable*>::const_iterator iter;
		if(selectionMode) {
			for(iter=selectableObjects.begin(); iter!=selectableObjects.end(); ++iter) {
				Selectable* sel = (*iter);
				if(sel->contains(startSelX, startSelY)) {
					unSelectAll();
					addSelectedObject(sel);
					selectionMode=false; 
					break;
				} else if(sel->intersects(startSelX, startSelY, endSelX, endSelY)) {
					addSelectedObject(sel);
				} else {
					removeSelectedObject(sel);
				}
			}
		}
		
		calcCentroid(&centerX, &centerY);
		
		if(order) {
			order=false;
			int newAngle = PA_GetAngle(centerX, centerY, orderX, orderY);
			orderMove(newAngle);
		}
		
		//if(PA_Distance(centerX, centerY, orderX, orderY)<=16) {
		//if(abs(centerX-orderX)<=3 && abs(centerY-orderY)<=3) {
		//if(centerX>=orderX || centerY>=orderY) {
		//if(abs(centerX-orderX)<=3 || abs(centerY-orderY)<=3) {
		if(abs(centerX-orderX)<=4 && abs(centerY-orderY)<=4) {
			orderStop();
		}
	}
	
	void orderStop() {
		std::list<Selectable*>::const_iterator iter;
		for(iter=selectedObjects.begin(); iter!=selectedObjects.end(); ++iter) {
			Selectable* sel = (*iter);
			sel->handleStop();
		}
	}
	
	void orderMove(int newAngle) {
		std::list<Selectable*>::const_iterator iter;
		for(iter=selectedObjects.begin(); iter!=selectedObjects.end(); ++iter) {
			Selectable* sel = (*iter);
			sel->handleMove(newAngle);
		}
	}
	
	//Calculate the centroid for every selected unit 
	void calcCentroid(int* x, int* y) {
		*x=0;
		*y=0;
		std::list<Selectable*>::const_iterator iter;
		for(iter=selectedObjects.begin(); iter!=selectedObjects.end(); ++iter) {
			Selectable* sel = (*iter);
			*x+=sel->getSelectableCenterX();
			*y+=sel->getSelectableCenterY();
		}
		*x/=selectedObjects.size();
		*y/=selectedObjects.size();
	}

	void unSelectAll() {
		std::list<Selectable*>::const_iterator iter;
		for(iter=selectedObjects.begin(); iter!=selectedObjects.end(); ++iter) {
			(*iter)->unSelect();
		}
		selectedObjects.clear();
	}
	
	void addSelectedObject(Selectable* sel) {
		selectedObjects.remove(sel);
		selectedObjects.push_back(sel);
		sel->select();
	}

	void removeSelectedObject(Selectable* sel) {
		selectedObjects.remove(sel);
		sel->unSelect();
	}
	
	void draw() {
		if(selectionMode) {
			ulDrawFillRect (startSelX, startSelY, endSelX, endSelY, RGB15(8, 8, 16));
//			ulDrawGradientRect(startSelX, startSelY, endSelX, endSelY
//				, RGB15(0, 16, 31), RGB15(0, 16, 31), RGB15(0, 0, 24), RGB15(0, 0, 24));
		}

		std::list<Selectable*>::const_iterator iter;
		for(iter=selectedObjects.begin(); iter!=selectedObjects.end(); ++iter) {
			Selectable* sel = (*iter);
			//sel->draw();
			ulSetImageTileSize(imageselected, 
												24*(frame%1), 0, 
												24, 24);
			imageselected->centerX = 12;
			imageselected->centerY = 12;
			ulDrawImageXY(imageselected, 
				sel->getSelectableCenterX() ,
				sel->getSelectableCenterY() );
		}
		
		drawCross (centerX, centerY);
		drawCross (orderX, orderY);
		
		ulPrintf_xy(0, 16, 
			"Select %d/%d", selectedObjects.size(), selectableObjects.size());
		ulPrintf_xy(0, 24, 
			"Select Mode %s - order %s", (selectionMode)?"On":"Off", (order)?"On":"Off");
	}

	void drawCross(int x, int y) {
		ulDrawLine (x-3, y-3, x+3, y+3,   RGB15(32,0,0));
		ulDrawLine (x-3, y+3, x+3, y-3, RGB15(32,0,0));
	}
	
	void addSelectable(Selectable* sel) {
		selectableObjects.push_back(sel);
	}
	
	void removeSelectable(Selectable* sel) {
		selectableObjects.remove(sel);
	}

};

#endif
