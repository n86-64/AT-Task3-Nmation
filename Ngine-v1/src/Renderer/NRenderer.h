#pragma once

// File - NRenderer.h
// Discription - Defines the renderer that the engine will use.
#include <vector>

#include "Core/NWindow.h"
#include "Helpers/Direct3D.h"
#include "Renderer/NRendererDevice.h"
#include "Helpers/NMaths.h"

#include "ShaderInput.h"

// Resource Objects
#include "NMaterial.h"
#include "Core/N3DMesh.h"
#include "Core/NAssetManager.h"

class NSkeletalMeshComponent;
class N3DComponent;
class NCamera;
class Triangle;

// Renderer initialiser info
// Defines a set of constants for rendering the images.
struct NRendererConfig 
{
public:
	NRendererConfig() {};
	NRendererConfig(NInitSettings launchSettings) {}; // TODO - Impliment Renderer Setup based on launch parameters.

	int width = 0;
	int height = 0;

	bool debugMode = false;
};


// Defines a Direct3D interface.
class NRenderer 
{
public:
	NRenderer() {};
	~NRenderer();

	// Initialise the renderer.
	bool init(NWindowHandle& windowHadle, NRendererConfig parameters);

	// Clears the render target (i.e. the backbuffer) ready for drawing. 
	void Clear();

	// Activate the swapchain and present the backbuffer frame to the screen. 
	void Present();

	NMaterial* createMaterial(std::string name);
	N3DMesh*   createMesh(std::string name);

	// Retrieves mesh from new manager.
	N3DMesh*   aquireMeshAsset(std::string name);

	// Renderer Interfacing
	void setMainCamera(NCamera* camera);

	// TODO - Create DrawTriangle afunction
	bool setupTriangle(Triangle* resource);

	void DrawObject(N3DComponent* component);
	void DrawObject(NSkeletalMeshComponent *mesh);

	NSkeletalMesh* aquireSkeletalMesh(std::string meshName);

public:
	// Here are the public drawing functions.
	void setMaterial();


private:
	NMath::Colour    clearColour = NMath::Colour(1.0f, 1.0f, 1.0f, 1.0f);

	// Setup functions.
	bool setupDeviceAndSwapchain(NWindowHandle& windowHadle, NRendererConfig parameters);
	bool setupRenderingPipelineRasterizer(NRendererConfig& params);
	bool setupRenderingPipelineOutputMerger(NRendererConfig& params);
	bool setupRenderingPipelineDepthStencil(NRendererConfig& params);
	bool setupRenderingMatrix();

	// Represents the selected graphics adapter.
	// NRenderDevice				graphicsAdapter;

	// Direct3D core pipeline objects. 
	ID3D11Device*		   renderDevice = nullptr; // Manages resources and provides access to the GPU.
	ID3D11DeviceContext*   deviceContext = nullptr; // Manages the pipeline and settings

	ID3D11RenderTargetView* gameFrame = nullptr;

	// Swapchain rendering mechanism
	IDXGISwapChain*			swapChain = nullptr;

	// Rasterizer State and related objects.
	ID3D11RasterizerState*  rasterizerState = nullptr;

	// Buffer Views (Allows access to the Swapchain for rendering the window.)
	ID3D11Texture2D*		swapchain_backBuffer = nullptr;

	// Depth-Stencil Objects for rendering 3D objects (Attach to Output-merger stage)
	ID3D11Texture2D*		  depthStencilTextureBuffer = nullptr;
	ID3D11DepthStencilView*   depthStencilConfiguration = nullptr;
	ID3D11DepthStencilState*   depthStencilState = nullptr;

private:
	NCamera*				  mainCamera = nullptr;

private:
	// Rendering constants
	ID3D11Buffer*			  constBuffer = nullptr;

	// The MVP Matrix.
	cBufferMatrix			  mvpMatracies;
	DirectX::XMMATRIX		  view;

private:
	void UpdateRenderState();

private:
	std::vector<std::unique_ptr<NMaterial>>  materialBuffer; // Allows Materials of a set name to be loaded from a cache. 
	std::vector<std::unique_ptr<N3DMesh>>   meshBuffer;

	NAssetManager							assetBuffer;

	NMaterial*   searchMaterials(std::string name);
	N3DMesh*	 searchMesh(std::string name);
};