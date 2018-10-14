// File - N3DComponent.h
// Description - A component that provides 3D rendering support.

#pragma once

#include "N3DMesh.h"
#include "Renderer/NMaterial.h"

#include "NComponent.h"

class N3DComponent : public NComponent 
{
public:
	N3DComponent() = default;
	~N3DComponent() = default; 

	virtual void Construct(EngineStateData engineState, NConstructorValues constructorData) override;

	// Update and render the components.
	virtual void Update() override;
	virtual void Render(NRenderer* renderer) override;

private:
	N3DMesh*    meshObject;
	NMaterial*  meshMaterial;
};