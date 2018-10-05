#include "NRenderer.h"

#include <fstream>

#include "Helpers/NMath_Colour.h"

constexpr unsigned int SWAP_CHAIN_BACK_BUFFER = 0;

#pragma region TEST DATA PLEASE REMOVE LATER
// Test Verticies for the cube.
VertexInput   verticies[] =
{
	  { DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },

};

unsigned int indicies[] =
{
	    3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
};

D3D11_INPUT_ELEMENT_DESC layout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

#pragma endregion


NRenderer::~NRenderer()
{
	depthStencilTextureBuffer->Release();
	depthStencilConfiguration->Release();
	depthStencilState->Release();

	swapchain_backBuffer->Release();
	
	gameFrame->Release();
	rasterizerState->Release();
	swapChain->Release(); // TODO - Ensure swapchain changes are handled correctly to prevent errors upon closing the game.
	renderDevice->Release();
	deviceContext->Release();

	// TODO - Clean up the pipeline stuff.
}

bool NRenderer::init(NWindowHandle& windowHadle, NRendererConfig parameters)
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
	result = setupRenderingPipelineOutputMerger(parameters);
	result = setupRenderingPipelineDepthStencil(parameters);

	TestDrawSetup();

	return result;
}

void NRenderer::Clear()
{
	NMath::Colour  clearColour(0.0f, 0.0f, 0.0f, 1.0f);
	deviceContext->ClearRenderTargetView(gameFrame, clearColour.getColourArray());
	deviceContext->ClearDepthStencilView(depthStencilConfiguration, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0f, 0);
}

void NRenderer::Present()
{

	DirectX::XMMATRIX newView = worldInput.view * DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f), 30.0f);


	deviceContext->DrawIndexed(ARRAYSIZE(indicies), 0, 0);
	swapChain->Present(0, 0); // Draw The Screen.
}

bool NRenderer::setupDeviceAndSwapchain(NWindowHandle& windowHadle, NRendererConfig parameters)
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

bool NRenderer::setupRenderingPipelineRasterizer(NRendererConfig& params)
{
	HRESULT hr = S_OK;

	// Set the renderer viewport and scisor rectangle.
	D3D11_VIEWPORT  viewport;
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
	ZeroMemory(&rasterizerSetup, sizeof(rasterizerSetup));
	rasterizerSetup.FillMode = D3D11_FILL_SOLID;
	rasterizerSetup.CullMode = D3D11_CULL_NONE;
	rasterizerSetup.FrontCounterClockwise = true;

	// Setup for Depth and stencil rendering stages.
	rasterizerSetup.DepthBias = false;
	rasterizerSetup.DepthBiasClamp = 0;
	rasterizerSetup.DepthClipEnable = false;
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

bool NRenderer::setupRenderingPipelineOutputMerger(NRendererConfig& params)
{
	HRESULT hr;
	hr = swapChain->GetBuffer(SWAP_CHAIN_BACK_BUFFER, __uuidof(ID3D11Texture2D), (LPVOID*)&swapchain_backBuffer);

	if (FAILED(hr)) 
	{
		MessageBox(NULL, "Failed to fetch render target.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	D3D11_RENDER_TARGET_VIEW_DESC   rtvDiscription;
	ZeroMemory(&rtvDiscription, sizeof(rtvDiscription));
	rtvDiscription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDiscription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = renderDevice->CreateRenderTargetView(swapchain_backBuffer, NULL, &gameFrame);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to bind render target to pipeline. Exiting.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}

bool NRenderer::setupRenderingPipelineDepthStencil(NRendererConfig& params)
{
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC  backbufferDesc;
	D3D11_TEXTURE2D_DESC  dsTexDescription;
	swapchain_backBuffer->GetDesc(&backbufferDesc);

	ZeroMemory(&dsTexDescription, sizeof(dsTexDescription));
	dsTexDescription.Width = backbufferDesc.Width;
	dsTexDescription.Height = backbufferDesc.Height;
	dsTexDescription.MipLevels = 1;
	dsTexDescription.ArraySize = 1;
	dsTexDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsTexDescription.SampleDesc.Count = 1;
	dsTexDescription.SampleDesc.Quality = 0;
	dsTexDescription.Usage = D3D11_USAGE_DEFAULT;
	dsTexDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsTexDescription.CPUAccessFlags = 0;
	dsTexDescription.MiscFlags = 0;

	hr = renderDevice->CreateTexture2D(&dsTexDescription, NULL, &depthStencilTextureBuffer);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to create valid DepthStencil Texture.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	// Now we have a texture to render the depth buffer to. 
	// We can create and setup the depth-stencil state.
	D3D11_DEPTH_STENCIL_DESC  dsDescription = {};
	
	// Depth Test Settings.
	dsDescription.DepthEnable = true;
	dsDescription.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
	dsDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	// Stencil Test Settings
	dsDescription.StencilEnable = true;
	dsDescription.StencilReadMask = 0xFF;
	dsDescription.StencilWriteMask = 0xFF;

	// Configure operations in the test passes or fails.
	// Applies to ppixels from polygons facing the camera.
	dsDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Now the settings for backfacing pixels.
	dsDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	renderDevice->CreateDepthStencilState(&dsDescription, &depthStencilState);
	deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC  DepthStencilViewDesc = {};
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = renderDevice->CreateDepthStencilView(depthStencilTextureBuffer, &DepthStencilViewDesc, &depthStencilConfiguration);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to create depth-stencil view.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}
	// Not needed by default as swapchain is already created and bound to the device.

	deviceContext->OMSetRenderTargets(1, &gameFrame, depthStencilConfiguration); 
	
	return true;
}

void NRenderer::TestDrawSetup()
{
	HRESULT hr;

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	std::fstream  shaderBin;
	shaderBin.open("BasicVertex.cso", std::ios::in | std::ios::binary);

	int vsSize = 0;
	int psSize = 0;

	char* vsData = nullptr;
	char* psData = nullptr;

	if (!shaderBin.fail()) 
	{
		// MEGA TODO - Create file reader classes to handle this functionality. 
		shaderBin.seekg(0, shaderBin.end);
		vsSize = shaderBin.tellg();
		shaderBin.seekg(0, shaderBin.beg);
		vsData = new char[vsSize];
		shaderBin.read(vsData, vsSize);


		hr = renderDevice->CreateVertexShader(vsData, vsSize, nullptr, &vertexShader);
	}

	shaderBin.close();

	shaderBin.open("BasicPixel.cso", std::ios::in | std::ios::binary);
	if (!shaderBin.fail())
	{
		// MEGA TODO - Create file reader classes to handle this functionality. 
		shaderBin.seekg(0, shaderBin.end);
		psSize = shaderBin.tellg();
		shaderBin.seekg(0, shaderBin.beg);
		psData = new char[psSize];
		shaderBin.read(psData, psSize);


		hr = renderDevice->CreatePixelShader(psData, psSize, nullptr, &pixelShader);
	}

	deviceContext->VSSetShader(vertexShader, nullptr, 0);
	deviceContext->PSSetShader(pixelShader, nullptr, 0);

	// Create the Vertex Buffer.
	D3D11_BUFFER_DESC  bufferDiscriptor; // The Buffer info
	bufferDiscriptor.Usage = D3D11_USAGE_DEFAULT;
	bufferDiscriptor.ByteWidth = sizeof(VertexInput) * ARRAYSIZE(verticies);
	bufferDiscriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDiscriptor.CPUAccessFlags = 0;
	bufferDiscriptor.MiscFlags = 0;
	bufferDiscriptor.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA  initData; // The buffer data.
	initData.pSysMem = verticies;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	hr = renderDevice->CreateBuffer(&bufferDiscriptor, &initData, &vertexBuffer);

	// Create the Index Buffer.
	D3D11_BUFFER_DESC  bufferDiscriptor2; // The Buffer info
	bufferDiscriptor2.Usage = D3D11_USAGE_DEFAULT;
	bufferDiscriptor2.ByteWidth = sizeof(unsigned int) * ARRAYSIZE(indicies);
	bufferDiscriptor2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDiscriptor2.CPUAccessFlags = 0;
	bufferDiscriptor2.MiscFlags = 0;
	bufferDiscriptor2.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA  initData2; // The buffer data.
	initData2.pSysMem = indicies;
	initData2.SysMemPitch = 0;
	initData2.SysMemSlicePitch = 0;

	hr = renderDevice->CreateBuffer(&bufferDiscriptor2, &initData2, &indexBuffer);

	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	UINT stride = sizeof(VertexInput);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	hr = renderDevice->CreateInputLayout(layout, 2, vsData, vsSize, &inputLayout);
	deviceContext->IASetInputLayout(inputLayout);

	// Setup view and projection matracies.
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(10.0f, 0.0f, 0.0f, 1.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90.0f), 1280 / 720, 0.1f, 101.0f);
	
	world = DirectX::XMMatrixTranspose(world);
	view = DirectX::XMMatrixTranspose(view);
	proj = DirectX::XMMatrixTranspose(proj);

	DirectX::XMStoreFloat4x4(&worldInput.world, world);
	DirectX::XMStoreFloat4x4(&worldInput.view, view);
	DirectX::XMStoreFloat4x4(&worldInput.proj, proj);

	D3D11_BUFFER_DESC constBufferDesc;
	constBufferDesc.ByteWidth = sizeof(worldInput);
	constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constBufferDesc.MiscFlags = 0;
	constBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA constData;
	constData.pSysMem = &worldInput;
	constData.SysMemPitch = 0;
	constData.SysMemSlicePitch = 0;

	hr = renderDevice->CreateBuffer(&constBufferDesc, &constData, &constBuffer);
	deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);
}

void NRenderer::TestDraw()
{

}
