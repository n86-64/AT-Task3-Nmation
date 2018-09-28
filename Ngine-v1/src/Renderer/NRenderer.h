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

	// Initialise the renderer.
	bool init(NWindowHandle& windowHadle, NRendererInit parameters);

private:
	// Device Functions



	// Represents the selected graphics adapter.
	// NRenderDevice				graphicsAdapter;

	// Direct3D core pipeline objects. 
	std::unique_ptr<ID3D11Device>		  renderDevice;
	std::unique_ptr<ID3D11DeviceContext> deviceContext;

	D3D_FEATURE_LEVEL	 requestedFeatureLevels;

	std::unique_ptr<ID3D11RenderTargetView>  renderTarget;


	// Swapchain rendering mechanism
	std::unique_ptr<IDXGISwapChain>			swapChain;

	// Buffer Views (Allows access to the Swapchain for rendering the window.)
	ID3D11Texture2D*		swapchain_backBuffer = nullptr;

	// Depth-Stencil Objects for rendering 3D objects (Attach to Output-merger stage)
	
};