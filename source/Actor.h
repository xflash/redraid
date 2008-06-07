#ifndef ACTOR_H
#define ACTOR_H

#include <vector>

typedef std::vector<void*> InitActorArgs;
	
class Actor {
private:
  bool _exists;

public:
	Actor():_exists(false) { }
	virtual ~Actor() { }
	inline bool exists() { return _exists; }
	inline void exists(bool value) { 
		(value)?activate():desactivate();
		_exists = value; 
	}
   
protected:
	virtual void activate() {}
	virtual void desactivate() {}
public:
	virtual void init(InitActorArgs* args)=0;
	virtual void move()=0;
	virtual void draw()=0;
};

#endif
