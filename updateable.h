#ifndef UPDATEABLE_H
#define UPDATEABLE_H

class Updateable{
public:
	//virtual Updateable();
	virtual void tick() = 0;
	//~Updateable() = default;
	virtual ~Updateable() = default;
};

//Updateable::~Updateable(){}

#endif
