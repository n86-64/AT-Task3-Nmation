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
	// Forth - Setup the renderloop.
	// Fifth - Clear the render target and present.

	bool result;
	result = setupDeviceAndSwapchain(windowHadle, parameters);

	return result;
}

bool NRenderer::setupDeviceAndSwapchain(NWindowHandle& windowHadle, NRendererInit parameters)
{
	HRESULT  hr = 0;
	UINT deviceFlags;

	const D3D_FEATURE_LEVEL d3dFeatures[] = {
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
