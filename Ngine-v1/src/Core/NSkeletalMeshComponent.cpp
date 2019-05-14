#include "Renderer/NRenderer.h"
#include "NSkeletalMeshComponent.h"

constexpr int MAX_NUMBER_OF_BONES = 100;

void NSkeletalMeshComponent::assignSkeletalMesh(NSkeletalMesh * newMesh, ID3D11Device * renderDevice)
{
	skeletalMesh = newMesh; 
	setupBoneMatrix(renderDevice);
}

NMaterial * NSkeletalMeshComponent::getMaterial()
{
	return material;
}

void NSkeletalMeshComponent::setMaterial(NMaterial * newMaterial)
{
	material = newMaterial;
}

void NSkeletalMeshComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
}

void NSkeletalMeshComponent::Update(GameStateData& gameData)
{
	return;
}

void NSkeletalMeshComponent::Render(NRenderer* renderer)
{
	renderer->DrawObject(this);
}

void NSkeletalMeshComponent::updateBoneData()
{
	for (int i = 0; i < skeletalMesh->getNumberOfBones(); i++)
	{
		bones[i].boneOffsets = skeletalMesh->getBoneByID(i)->getBoneTransform();
	}
}

// Load the skeleton bones onto the GPU.
void NSkeletalMeshComponent::setupBoneMatrix(ID3D11Device* renderDevice)
{
	cBufferBones boneObject;
	HRESULT  hr = S_OK;

	for (int i = 0; i < skeletalMesh->getNumberOfBones(); i++) 
	{
		boneObject.boneOffsets = skeletalMesh->getBoneByID(i)->getBoneTransform();
		bones.emplace_back(boneObject);
	}

	if (skeletalMesh->getNumberOfBones() > 0) 
	{
		D3D11_BUFFER_DESC   skeletonBufferDesc = { 0 };
		skeletonBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		skeletonBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		skeletonBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX) * bones.size();
		skeletonBufferDesc.CPUAccessFlags = 0;
		skeletonBufferDesc.StructureByteStride = 0;
		skeletonBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA skeletonData = { };
		skeletonData.pSysMem = bones.data();
		skeletonData.SysMemPitch = 0;
		skeletonData.SysMemSlicePitch = 0;

		hr = renderDevice->CreateBuffer(&skeletonBufferDesc, &skeletonData, &skeletonBuffer);

		if (FAILED(hr)) { throw; }

		//return FAILED(hr);
	}
	
}

