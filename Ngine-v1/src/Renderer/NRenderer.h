#pragma once

// File - NRenderer.h
// Discription - Defines the renderer that the engine will use.

#include "Core/NWindow.h"
#include "Helpers/Direct3D.h"
#include "Renderer/NRendererDevice.h"
#include "Helpers/NMaths.h"

// Renderer initialiser info
// Defines a set of constants for rendering the images.
struct NRendererConfig 
{
public:
	NRendererConfig() {};
	NRendererConfig(NInitSettings launchSettings) {}; // TODO - Impliment Renderer Setup based on launch parameters.

	int width = 0;
	int height = 0;

	bool debugMode = true;
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

private:
	// Setup functions.
	bool setupDeviceAndSwapchain(NWindowHandle& windowHadle, NRendererConfig parameters);
	bool setupRenderingPipelineRasterizer(NRendererConfig& params);
	bool setupRenderingPipelineOutputMerger(NRendererConfig& params);
	bool setupRenderingPipelineDepthStencil(NRendererConfig& params);

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
};