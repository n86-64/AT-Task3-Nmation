#pragma once

// File - NRenderer.h
// Discription - Defines the renderer that the engine will use.

#include "Core/NWindow.h"

#include "Helpers/Direct3D.h"
#include "Helpers/NMaths.h"

// Defines a Direct3D interface.
class NRenderer 
{
public:
	NRenderer();

	// Initialise the renderer.
	void init(NWindowHandle& windowHadle);

private:
	// Direct3D core pipeline objects. 
	ID3D11Device* renderDevice;
	ID3D11DeviceContext* deviceContext;

	D3D_FEATURE_LEVEL	 supportedFeatureLevels;
	D3D_FEATURE_LEVEL	 requestedFeatureLevels;

	ID3D11RenderTargetView*  renderTarget;


	// Swapchain rendering mechanism
	IDXGISwapChain*			swapChain;
	DXGI_SWAP_CHAIN_DESC	swapChainDescription;

	// Buffer Views (Allows access to the Swapchain for rendering the window.)
	ID3D11Texture2D*		swapchain_backBuffer = nullptr;

};