#include "NRenderer.h"

NRenderer::~NRenderer()
{
	renderDevice->Release();
	deviceContext->Release();
	swapChain->Release();
}

bool NRenderer::init(NWindowHandle& windowHadle, NRendererInit parameters)
{
	// First Create the swapchain system.
	// Second - Create the device and the swapchain (DONE)
	// Third - Setup the pipeline stages.
	//        - Only required for both OutputMerger and Rasterizer Stages.
	//        - For 3D OM stage requires Depth Stencil State.
	// Forth - Setup the renderloop.
	// Fifth - Clear the render target and present.

	bool result;
	result = setupDeviceAndSwapchain(windowHadle, parameters);
	result = setupRenderingPipelineRasterizer(parameters);

	return result;
}

bool NRenderer::setupDeviceAndSwapchain(NWindowHandle& windowHadle, NRendererInit parameters)
{
	HRESULT  hr = 0;
	UINT deviceFlags;

	const D3D_FEATURE_LEVEL d3dFeatures[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D_FEATURE_LEVEL*  actualfeatureLevels = nullptr;

	deviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED; // TODO - Check if needed.
	if (parameters.debugMode)
	{
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}

	DXGI_SWAP_CHAIN_DESC   swapchainDiscription;
	ZeroMemory(&swapchainDiscription, sizeof(swapchainDiscription));

	swapchainDiscription.BufferCount = 1; // single back buffer prior to render surface.
	swapchainDiscription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDiscription.OutputWindow = windowHadle;
	swapchainDiscription.Windowed = TRUE;

	// Swapchain Texture Sample settings.
	swapchainDiscription.SampleDesc.Count = 1;
	swapchainDiscription.SampleDesc.Quality = 0;

	// Swapchain output buffer discriptor
	swapchainDiscription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDiscription.BufferDesc.Width = parameters.width;
	swapchainDiscription.BufferDesc.Height = parameters.height;
	swapchainDiscription.BufferDesc.RefreshRate.Numerator = 60;
	swapchainDiscription.BufferDesc.RefreshRate.Denominator = 1;

	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		deviceFlags,
		d3dFeatures,
		3,
		D3D11_SDK_VERSION,
		&swapchainDiscription,
		&swapChain,
		&renderDevice,
		actualfeatureLevels,
		&deviceContext
	);

	if (FAILED(hr))
	{
		MessageBox(windowHadle, "Failed to create the device and swapchain.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}

bool NRenderer::setupRenderingPipelineRasterizer(NRendererInit& params)
{
	HRESULT hr;

	// Set the renderer viewport and scisor rectangle.
	D3D11_VIEWPORT         viewport;
	viewport.Width = (float)params.width;
	viewport.Height = (float)params.height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &viewport);

	D3D11_RECT  rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = params.height;
	rect.right = params.width;
	deviceContext->RSSetScissorRects(1, &rect);

	// Start by defining the rasterizer properties
	D3D11_RASTERIZER_DESC   rasterizerSetup;
	rasterizerSetup.FillMode = D3D11_FILL_SOLID;
	rasterizerSetup.CullMode = D3D11_CULL_FRONT;
	rasterizerSetup.FrontCounterClockwise = true;

	// Setup for Depth and stencil rendering stages.
	rasterizerSetup.DepthBias = false;
	rasterizerSetup.DepthBiasClamp = 0;
	rasterizerSetup.DepthClipEnable = true;
	rasterizerSetup.SlopeScaledDepthBias = 0;

	// Pipeline AntiAliasing and sampaling features
	rasterizerSetup.ScissorEnable = true;
	rasterizerSetup.MultisampleEnable = false;
	rasterizerSetup.AntialiasedLineEnable = false;

	hr = renderDevice->CreateRasterizerState(&rasterizerSetup, &rasterizerState);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to create the device and swapchain.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	deviceContext->RSSetState(rasterizerState);

	return true;
}
