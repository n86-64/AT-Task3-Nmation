#include "Renderer/NRenderer.h"
#include "N3DComponent.h"

void N3DComponent::Construct(EngineStateData engineState, NConstructorValues constructorData)
{
	return;
}

void N3DComponent::Update()
{
	return;
}

void N3DComponent::Render(NRenderer* renderer)
{
	renderer->DrawObject(this);
}

void N3DComponent::setMesh(N3DMesh* newMesh)
{
	meshObject = newMesh;
}

void N3DComponent::setMaterial(NMaterial* newMat)
{
	meshMaterial = newMat;
}

N3DMesh* N3DComponent::getMesh()
{
	return meshObject;
}

NMaterial* N3DComponent::getMaterial()
{
	return meshMaterial;
}
