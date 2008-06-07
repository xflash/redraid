#ifndef Movable_H
#define Movable_H

#include <ulib/ulib.h>
#include "MathUtils.h"

//Make it a fixed point value (1 = 256, 0.5 = 128, etc.)
#define FIX(x)		((x) << 8)
//Return the real value of a fixed point
#define UNFIX(x)	((x) >> 8)


class Movable {
private:
  int _x, _y;
  int _sx, _sy;
  int _angle;
  int _speed;

public:
  Movable() { }
  virtual ~Movable() {}

  /**
   * Main contract of this abstract class
   */
  virtual void move() {
    _x+=_sx;
    _y+=_sy;
  }
  
  //angle should be in [0, 511]
  virtual void initMove(int px, int py, int pangle, int pspeed) {
    _x=FIX(px);
    _y=FIX(py);
    _angle=pangle;
    _speed=FIX(pspeed);
    setCartesian();
  }
 
  void setCartesian() {
    _sx = ulCos(_angle, _speed);
    _sy = ulSin(_angle, _speed);
  }

  void setPolar() {
    _angle = PA_GetAngle(0, 0, _sx, _sy);
		_speed = PA_TrueDistance(0, 0, _sx, _sy);
  }
  
  void setAngleSpeed(int angle, int speed) {
		_angle=angle;
		_speed=FIX(speed);
		setCartesian();
  }
 
	int getX() { return UNFIX(_x); }
	int getY() { return UNFIX(_y); }
	int getAngle() { return _angle; }

	void setX(int x) { _x=FIX(x); }
	void setY(int y) { _y=FIX(y); }
	
	void setPolarCoord(int tx, int ty) {
		_sx=FIX(tx);
		_sy=FIX(ty);
		setPolar();
	}

	void setAngle(int a) { 
		_angle=a;
		setCartesian();
 	}
	void setSpeed(int s) { 
		_speed=FIX(s);
		setCartesian();
 	}
	

  
};

#endif
