#include "time.h"
#include "NAnimation.h"
#include "NSkeletalMeshComponent.h"
#include "NAnimationComponent.h"

void NAnimationComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{

}

void NAnimationComponent::Update(GameStateData & gameData)
{
	if (selectedAnimation) 
	{
		// Track the time and ensure the correct data is moved. 
		elapsedTicks += gameData.timeData->getDeltaTimeInSeconds() * selectedAnimation->getTickrate();

		if (elapsedTicks >= selectedAnimation->getDuration()) 
		{
			elapsedTicks = 0.0f;
		}
	}
}

void NAnimationComponent::Render(NRenderer * renderer)
{

}

void NAnimationComponent::setAnimation(NAnimation* newAnim)
{
	selectedAnimation = newAnim;
}

void NAnimationComponent::updateBoneData(NSkeletalMeshComponent* skeletalMeshComp)
{
	DirectX::XMMATRIX   position;
	DirectX::XMMATRIX   rotation;
	DirectX::XMMATRIX   scale;

	DirectX::XMMATRIX   nodeTransform = DirectX::XMMatrixIdentity();
	NSkeletalMesh* mesh = skeletalMeshComp->getMesh();
	NSkeletalNode* node = nullptr;
	NSkeletalBone* bone = nullptr;
	NAnimationNode* animNode = nullptr;

	// We have an animation so go throgh each node and update the bone position based on current frame time.
	for (int i = 0; i < selectedAnimation->getAnimCount(); i++) 
	{
		animNode = selectedAnimation->getNode(i);
		node = mesh->retrieveNodeByName(animNode->name);
		bone = mesh->getBoneByID(mesh->getBoneByName(animNode->name));
		
		position = DirectX::XMMatrixTranslation(animNode->translation[0].value.x(), animNode->translation[0].value.y(), animNode->translation[0].value.z());
		rotation = DirectX::XMMatrixRotationQuaternion(animNode->rotation[0].value.getRawVector());
		scale = DirectX::XMMatrixScaling(animNode->scale[0].value.x(), animNode->scale[0].value.y(), animNode->scale[0].value.z());

		position = DirectX::XMMatrixTranslationFromVector(getInterpolatedPosition(animNode));
		rotation = DirectX::XMMatrixRotationQuaternion(getInterpolatedRotation(animNode));
		scale = DirectX::XMMatrixScalingFromVector(getInterpolatedScale(animNode));

		// Apply the frame. 
		nodeTransform = position * rotation * scale;
		nodeTransform = DirectX::XMMatrixTranspose(nodeTransform);
	
		bone->setBoneTransform(node->getModelMatrix() * nodeTransform * bone->getBoneOffset());
	} 

	skeletalMeshComp->updateBoneData();
}

DirectX::XMVECTOR NAnimationComponent::getInterpolatedPosition(NAnimationNode* node)
{
	int nodeIndex = getAnimKeyIndex(node->translation);

	if (nodeIndex <= -1 && (nodeIndex - 1) <= -1) 
	{
		return DirectX::XMVECTOR();
	}

	DirectX::XMVECTOR interpolatedValue;
	float tickRatio = node->translation[nodeIndex].time - elapsedTicks / selectedAnimation->getTickrate();
	interpolatedValue = DirectX::XMVectorLerp(node->translation[nodeIndex - 1].value.getRawVector(), node->translation[nodeIndex].value.getRawVector(), tickRatio);

	return interpolatedValue;
}

DirectX::XMVECTOR NAnimationComponent::getInterpolatedRotation(NAnimationNode * node)
{
	int nodeIndex = getAnimKeyIndex(node->rotation);

	if (nodeIndex <= -1 && (nodeIndex - 1) <= -1)
	{
		return DirectX::XMVECTOR();
	}

	DirectX::XMVECTOR interpolatedValue;
	float tickRatio = node->rotation[nodeIndex].time - elapsedTicks / selectedAnimation->getTickrate();
	interpolatedValue = DirectX::XMVectorLerp(node->rotation[nodeIndex - 1].value.getRawVector(), node->rotation[nodeIndex].value.getRawVector(), tickRatio);

	return interpolatedValue;
}

DirectX::XMVECTOR NAnimationComponent::getInterpolatedScale(NAnimationNode * node)
{
	int nodeIndex = getAnimKeyIndex(node->scale);

	if (nodeIndex <= -1 && (nodeIndex - 1) <= -1)
	{
		return DirectX::XMVECTOR();
	}

	DirectX::XMVECTOR interpolatedValue;
	float tickRatio = node->scale[nodeIndex].time - elapsedTicks / selectedAnimation->getTickrate();
	interpolatedValue = DirectX::XMVectorLerp(node->scale[nodeIndex - 1].value.getRawVector(), node->scale[nodeIndex].value.getRawVector(), tickRatio);

	return interpolatedValue;
}

int NAnimationComponent::getAnimKeyIndex(std::vector<NAnimationKey>& nodeKeys)
{
	for (int i = 0; i < nodeKeys.size(); i++)
	{
		if (elapsedTicks < nodeKeys[i].time)
		{
			return i;
		}
	}

	return -1;
}
