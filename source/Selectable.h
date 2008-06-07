#ifndef __Selectable_h__
#define __Selectable_h__


class Selectable {
protected:
	bool selected;
public:
	Selectable():selected(false) {}
	virtual ~Selectable() {}

	bool intersects(int x0, int y0, int x1, int y1) {
		int x,y;
		if(x0>x1) { x=x1; x1=x0; x0=x; }
		if(y0>y1) { y=y1; y1=y0; y0=y; }
		return (getSelectableX() < x1 && 
						getSelectableLowX() > x0  && 
						getSelectableY() < y1 && 
						getSelectableLowY() > y0);
	}

	bool contains(int x, int y) {
		return (getSelectableX() < x && 
						getSelectableLowX() > x  && 
						getSelectableY() < y && 
						getSelectableLowY() > y);
	}

	void select() {
		selected=true;
		handleSelection();
	}

	void unSelect() {
		selected=false;
		handleUnSelection();
	}

	virtual void handleMove(int angle)=0;
	virtual void handleStop() =0;

protected:
	void draw() { 
		ulDrawFillRect (getSelectableX(), getSelectableY(), getSelectableLowX(), getSelectableLowY(), RGB15(0, 16, 31));
	}
	virtual void handleSelection() {}
	virtual void handleUnSelection() {}
	
protected:
	virtual int getSelectableX()=0;
	virtual int getSelectableY()=0;
	virtual int getSelectableW()=0;
	virtual int getSelectableH()=0;

public:
	int getSelectableLowX() { return getSelectableX() + getSelectableW(); }
	int getSelectableLowY() { return getSelectableY() + getSelectableH(); }

	int getSelectableCenterX() { return getSelectableX() + (getSelectableW()>>1); }
	int getSelectableCenterY() { return getSelectableY() + (getSelectableH()>>1); }
	
};

#endif
