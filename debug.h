#ifndef DEBUG_H
#define DEBUG_H

#include <map>

class Debug{
public:
	Debug();

	void setValue(std::string key, float val);
	void draw();

private:
	std::map<std::string, float> values;
};

#endif
