#ifndef Collidable_h
#define Collidable_h

// Base class for Collidable objects
class Collidable {
protected:
	Collidable* target;
public:
	Collidable():target(NULL) { }
	virtual ~Collidable() { }
	
	void checkCollision() {
		if(target) {
			if(intersects(target)) {
				target->doCollide(this);
				doCollide(target);
			}
		}
	}
	
	bool intersects(Collidable* other) {
		return (getCollideX() < other->getCollideLowX() && 
						getCollideLowX() > other->getCollideX()  && 
						getCollideY() < other->getCollideLowY() && 
						getCollideLowY() > other->getCollideY());
	}
	
	void setTarget(Collidable* t) { target=t; }
	Collidable* getTarget() { return target; }

	virtual void doCollide(Collidable* target)=0;
	virtual int getCollideX()=0;
	virtual int getCollideY()=0;
	virtual int getCollideW()=0;
	virtual int getCollideH()=0;

	virtual int getCollideLowX() { return getCollideX() + getCollideW(); }
	virtual int getCollideLowY() { return getCollideY() + getCollideH(); }

	virtual int getCollideCenterX() { return getCollideX() + (getCollideW()>>1); }
	virtual int getCollideCenterY() { return getCollideY() + (getCollideH()>>1); }
	
};

#endif
