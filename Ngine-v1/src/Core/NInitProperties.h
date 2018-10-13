// File - NInitProperties.h
// Description - Allows an arbatry set of properties to be specified. All properties stored as a string then converted. 

#pragma once

#include <map>

class NRenderer;

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