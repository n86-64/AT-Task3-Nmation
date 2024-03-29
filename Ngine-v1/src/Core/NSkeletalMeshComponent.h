// File - NSkeletalMeshComponent
// Description - A component that allows a skeletal mesh to be rendered.

#pragma once

#include "Renderer/ShaderInput.h"
#include "NSkeletalMesh.h"
#include "NComponent.h"

class NMaterial;

class NSkeletalMeshComponent : public NComponent
{
public:
	NSkeletalMeshComponent() = default;

	void assignSkeletalMesh(NSkeletalMesh* newMesh, ID3D11Device* renderDevice);
	NSkeletalMesh* getMesh() { return skeletalMesh; }

	NMaterial* getMaterial();
	void setMaterial(NMaterial* newMaterial);

	// Inherited via NComponent
	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;
	virtual void Update(GameStateData & gameData) override;
	virtual void Render(NRenderer * renderer) override;

	ID3D11Buffer*  getSkeletonBuffer() { return skeletonBuffer; }

	ID3D11Buffer*  skeletonBuffer;

	std::vector<cBufferBones>		  bones;

	void updateBoneData();

private:
	void setupBoneMatrix(ID3D11Device* renderDevice);

private:
	NSkeletalMesh*				  skeletalMesh;
	NMaterial*						  material;
};
