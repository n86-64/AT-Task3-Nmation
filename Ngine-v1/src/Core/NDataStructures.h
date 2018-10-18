// File - NDataStructuresh
// Description - Describes a set of useful data structures/containers etc which can be used to create

#pragma once

#include <map>

class NRenderer;

class NTimer;
class NInputHandler;

class NConstructorValues 
{
public:
	NConstructorValues() = default;

	void AddIntProperty(std::string name, int value);
	void AddFloatProperty(std::string name, float value);
	void AddStringProperty(std::string name, std::string value);

private:
	std::map<std::string, std::string>  propeties;
};

struct EngineStateData 
{
	NRenderer*  renderer;
};

struct GameStateData 
{
	NTimer* timeData;
	NInputHandler*  input;
};
