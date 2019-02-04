// File - NSkeletalMeshComponent
// Description - A component that allows a skeletal mesh to be rendered.

#pragma once


#include "NSkeletalMesh.h"
#include "NComponent.h"

class NSkeletalMeshComponent : public NComponent
{
public:
	NSkeletalMeshComponent() = default;

	void assignSkeletalMesh(NSkeletalMesh* newMesh) { skeletalMesh = std::unique_ptr<NSkeletalMesh>(newMesh); }
	NSkeletalMesh* getMesh() { return skeletalMesh.get(); }

	NMaterial* getMaterial();
	void setMaterial(NMaterial* newMaterial);

	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update(GameStateData & gameData) override;
	virtual void Render(NRenderer * renderer) override;

private:
	std::unique_ptr<NSkeletalMesh>    skeletalMesh;
	NMaterial*							  material;

};
