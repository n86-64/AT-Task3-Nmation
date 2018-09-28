#pragma once

// File - NRenderer.h
// Discription - Defines the renderer that the engine will use.

#include "Core/NWindow.h"

#include "Helpers/Direct3D.h"
#include "Renderer/NRendererDevice.h"
#include "Helpers/NMaths.h"

// Renderer initialiser info
struct NRendererInit 
{
public:
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
	bool init(NWindowHandle& windowHadle, NRendererInit parameters);



private:
	// Setup functions.
	bool setupDeviceAndSwapchain(NWindowHandle& windowHadle, NRendererInit parameters);
	bool setupRenderingPipelineRasterizer(NRendererInit& params);


	// Represents the selected graphics adapter.
	// NRenderDevice				graphicsAdapter;

	// Direct3D core pipeline objects. 
	ID3D11Device*		   renderDevice;
	ID3D11DeviceContext*   deviceContext;
	D3D_FEATURE_LEVEL	   requestedFeatureLevels;

	ID3D11RenderTargetView* renderTarget;

	// Swapchain rendering mechanism
	IDXGISwapChain*			swapChain;

	// Rasterizer State and related objects.
	ID3D11RasterizerState*  rasterizerState;

	// Buffer Views (Allows access to the Swapchain for rendering the window.)
	ID3D11Texture2D*		swapchain_backBuffer = nullptr;

	// Depth-Stencil Objects for rendering 3D objects (Attach to Output-merger stage)
	ID3D11Texture2D*		  depthStencilTextureBuffer;
	ID3D11DepthStencilView*   depthStencilConfiguration;
	ID3D11DepthStencilState*   depthStencilState;
};