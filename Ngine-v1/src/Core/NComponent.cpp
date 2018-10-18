#include "NComponent.h"

NGameObject* NComponent::getGameObject()
{
	return parentObject;
}

void NComponent::setGameObject(NGameObject* obj)
{
	parentObject = obj;
}
