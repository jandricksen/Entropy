#pragma once
#include <string>

class Level;

class Layer
{

public:

	virtual void render() = 0;
	virtual void update(Level* pLevel, double delta) = 0;
	virtual std::string type() { return "LayerType"; };
	virtual ~Layer() {};

};

