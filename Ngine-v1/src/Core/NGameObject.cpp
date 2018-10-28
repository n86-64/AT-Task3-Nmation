#include "NGameObject.h"

void NGameObject::Update(GameStateData& gameData)
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

void NGameObject::setPosition(NMath::Vector3 newPos)
{
	position = newPos;
}

NMath::Vector3 NGameObject::getRotation()
{
	return rotation;
}

void NGameObject::setRotation(NMath::Vector3 newPos)
{
	rotation = newPos;
	//rotation = NMath::Vector3(DirectX::XMQuaternionRotationRollPitchYawFromVector(newPos.getRawVector()));
}

NMath::Vector3 NGameObject::getScale()
{
	return scale;
}

void NGameObject::setScale(NMath::Vector3 newScale)
{
	scale = newScale;
}

void NGameObject::addComponent(NComponent* newComp)
{
	newComp->setGameObject(this);
	objectComponents.push_back(std::unique_ptr<NComponent>(newComp));
}

NMath::Vector3 NGameObject::getTransformValue()
{
	return position;
}

NComponent* NGameObject::getComponent(int i)
{
	if (i < objectComponents.size()) 
	{
		return objectComponents[i].get();
	}
	else 
	{
		return nullptr;
	}
}

int NGameObject::getComponentCount()
{
	return objectComponents.size();
}
