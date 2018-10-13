#include <Windows.h>
#include "TestComp.h"

void TestComp::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
	return;
}

void TestComp::Update()
{
	OutputDebugString("LOL im updating \n");
}

void TestComp::Render(NRenderer* renderer)
{
	return;
}
