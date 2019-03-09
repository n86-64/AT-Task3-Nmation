// NAnimationComponent.h
// Discription - Manages animations for the selected skeleton.


#pragma once

#include "NComponent.h"

class NAnimation;
class NSkeletalMeshComponent;

class aiScene;

class NAnimationComponent : public NComponent 
{
public:
	NAnimationComponent() = default;


	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update(GameStateData& gameData) override;
	virtual void Render(NRenderer * renderer) override;

	void setAnimation(NAnimation* newAnim); 
	bool hasAnimation() { return (selectedAnimation != nullptr); }

	void updateBoneData(NSkeletalMeshComponent* skeletalMeshComp);

private:
	DirectX::XMVECTOR getInterpolatedPosition(NAnimationNode* node);
	DirectX::XMVECTOR getInterpolatedRotation(NAnimationNode* node);
	DirectX::XMVECTOR getInterpolatedScale(NAnimationNode* node);


	int getAnimKeyIndex(std::vector<NAnimationKey>& nodeKeys);

private:
	NAnimation* selectedAnimation = nullptr;
	bool loop = true;
	float elapsedTime = 0.0f; 
	float elapsedTicks;
};