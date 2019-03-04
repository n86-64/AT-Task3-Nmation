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
		elapsedTicks += gameData.timeData->getDeltaTimeInSeconds() / selectedAnimation->getTickrate();
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

		//position = DirectX::XMMatrixTranspose(position);
		//rotation = DirectX::XMMatrixTranspose(rotation);
		//scale = DirectX::XMMatrixTranspose(scale);

		// Apply the frame. 
		nodeTransform = position * rotation * scale;
		nodeTransform = DirectX::XMMatrixTranspose(nodeTransform);
		bone->setBoneTransform(node->getModelMatrix() * nodeTransform * bone->getBoneOffset());
	} 

	skeletalMeshComp->updateBoneData();
}
