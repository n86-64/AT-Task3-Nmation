#include "NGameObject.h"

void NGameObject::Update(NInputHandler* input)
{
	for (int i = 0; i < objectComponents.size(); i++) 
	{
		objectComponents[i]->Update();
	}
}

void NGameObject::Render(NRenderer * renderer)
{
	for (int i = 0; i < objectComponents.size(); i++)
	{
		objectComponents[i]->Render(renderer);
	}
}

NMath::Vector3 NGameObject::getPosition()
{
	return position;
}

void NGameObject::addComponent(NComponent* newComp)
{
	objectComponents.push_back(std::unique_ptr<NComponent>(newComp));
}
