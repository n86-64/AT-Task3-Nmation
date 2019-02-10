#include <algorithm>
#include <queue>

#include "NRenderer.h"

#include "Helpers/NMath_Colour.h"
#include "Renderer/NMaterial.h"
#include "Core/Camera.h"
#include "Core/Triangle.h"

#include "Core/N3DComponent.h"
#include "Core/NSkeletalMeshComponent.h"

constexpr unsigned int SWAP_CHAIN_BACK_BUFFER = 0;

NRenderer::~NRenderer()
{
	constBuffer->Release();

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

	if (result) 
	{
		result = setupRenderingPipelineRasterizer(parameters);
		result = setupRenderingPipelineOutputMerger(parameters);
		result = setupRenderingPipelineDepthStencil(parameters);
		result = setupRenderingMatrix();
	}

	assetBuffer.setRenderDevice(renderDevice);
	assetBuffer.loadAssets("meshes/cube.obj");
	assetBuffer.loadAssets("meshes/Cycles.blend");
	assetBuffer.loadAssets("meshes/Tux4.blend");
	assetBuffer.loadAssets("meshes/forest-monster-final.blend");
	assetBuffer.loadAssets("meshes/fgc_skeleton.blend");
	assetBuffer.loadAssets("meshes/Taunt.fbx");

	return result;
}

void NRenderer::Clear()
{
	deviceContext->OMSetRenderTargets(1, &gameFrame, depthStencilConfiguration);
	deviceContext->ClearRenderTargetView(gameFrame, clearColour.getColourArray());
	deviceContext->ClearDepthStencilView(depthStencilConfiguration, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	UpdateRenderState();
}

void NRenderer::Present()
{
	swapChain->Present(0, 0); // Draw The Screen.
}

// TODO - Define a version of this which takes a file and uses that to create a material. 
// Then Setup the shader.
NMaterial* NRenderer::createMaterial(std::string name) 
{
	NMaterial*  newMat = nullptr;
	newMat = searchMaterials(name);

	if (!newMat) 
	{
		newMat = new NMaterial(name, renderDevice);
		// Setup the Materials (TODO - Add the ability to set shaders.)

		if (!newMat->materialLoaded())
		{
			delete newMat;
			newMat = nullptr;
		}
		else 
		{
			materialBuffer.push_back(std::unique_ptr<NMaterial>(newMat));
		}
	}

	return newMat;
}

N3DMesh* NRenderer::createMesh(std::string name)
{
	// TODO - Add checks and buffering to prevent exessive reads and writes. 
	N3DMesh* mesh = nullptr;
	mesh = searchMesh(name);

	if (!mesh)
	{
		mesh = new N3DMesh(name, renderDevice);
		// Setup the Materials (TODO - Add the ability to set shaders.)
		meshBuffer.push_back(std::unique_ptr<N3DMesh>(mesh));
	}

	return mesh;
}

N3DMesh* NRenderer::aquireMeshAsset(std::string name)
{
	return assetBuffer.aquireMesh(name);
}

void NRenderer::setMainCamera(NCamera* camera)
{
	mainCamera = camera;
}

bool NRenderer::setupTriangle(Triangle* resource)
{
	return resource->SetupBuffers(renderDevice);
}

void NRenderer::DrawObject(N3DComponent* component) 
{
	NGameObject*    componentObject = component->getGameObject(); 
	
	mvpMatracies.mvMatrix = DirectX::XMMatrixMultiply(componentObject->getModelMatrix(), view);
	mvpMatracies.mvMatrix = DirectX::XMMatrixTranspose(mvpMatracies.mvMatrix);

	deviceContext->UpdateSubresource(constBuffer, 0, nullptr, &mvpMatracies, 0, 0);

	deviceContext->IASetInputLayout(component->getMaterial()->getInputLayout());

	ID3D11Buffer* vBuffer = component->getMesh()->getVertexBuffer(); // Allows an array of elements to be passed in.

	// Set buffers
	UINT stride = sizeof(VertexInput);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(component->getMesh()->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	deviceContext->VSSetShader(component->getMaterial()->getVertexShader(), nullptr, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);

	deviceContext->PSSetShader(component->getMaterial()->getFragmentShader(), nullptr, 0);

	// DRAW! DRAW! DRAW!
	deviceContext->DrawIndexed(component->getMesh()->getIndexCount(), 0, 0);
}

void NRenderer::DrawObject(NSkeletalMeshComponent* component)
{
	NGameObject*     componentObject = component->getGameObject();
	NSkeletalNode*   node = nullptr;
	NSkeletalMesh*   mesh = component->getMesh();
	N3DMesh*		 meshComponent = nullptr;

	std::queue<int> nodeToRender;
	nodeToRender.emplace(0);
	
	while (!nodeToRender.empty()) 
	{
		node = mesh->retrieveNode(nodeToRender.front());
		
		// Render each mesh.
		for (int mIndex : node->getModelIndicies()) 
		{
			meshComponent = mesh->getMesh(mIndex);

			mvpMatracies.mvMatrix = DirectX::XMMatrixMultiply(componentObject->getModelMatrix() * node->getModelMatrix(), view);
			mvpMatracies.mvMatrix = DirectX::XMMatrixTranspose(mvpMatracies.mvMatrix);

			deviceContext->UpdateSubresource(constBuffer, 0, nullptr, &mvpMatracies, 0, 0);

			deviceContext->IASetInputLayout(component->getMaterial()->getInputLayout());

			ID3D11Buffer* vBuffer = meshComponent->getVertexBuffer(); // Allows an array of elements to be passed in.

			// Set buffers
			UINT stride = sizeof(VertexInput);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
			deviceContext->IASetIndexBuffer(meshComponent->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			deviceContext->VSSetShader(component->getMaterial()->getVertexShader(), nullptr, 0);
			deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);

			deviceContext->PSSetShader(component->getMaterial()->getFragmentShader(), nullptr, 0);

			// DRAW! DRAW! DRAW!
			deviceContext->DrawIndexed(meshComponent->getIndexCount(), 0, 0);
		}

		for (int nodesToAdd : node->getChildren()) 
		{
			nodeToRender.emplace(nodesToAdd);
		}

		nodeToRender.pop();
		mvpMatracies.mvMatrix = DirectX::XMMatrixIdentity();
	}

}

NSkeletalMesh* NRenderer::aquireSkeletalMesh(std::string meshName)
{
	return assetBuffer.aquireSkeletalMesh(meshName);
}

void NRenderer::setMaterial()
{

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
	swapchainDiscription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // TODO - Consider changing to a double buffer model with flipping.
	swapchainDiscription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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
		MessageBox(windowHadle, "Failed to create the device and swapchain." , "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}

bool NRenderer::setupRenderingPipelineRasterizer(NRendererConfig& params)
{
	HRESULT hr;

	// Set the renderer viewport and scisor rectangle.
	D3D11_VIEWPORT         viewport;
	viewport.Width = (float)params.width;
	viewport.Height = (float)params.height;
	viewport.MinDepth = D3D11_MIN_DEPTH;
	viewport.MaxDepth = D3D11_MAX_DEPTH;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
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
	// TODO - Consider removing this.
	D3D11_DEPTH_STENCIL_DESC  dsDescription = {};
	
	// Depth Test Settings.
	dsDescription.DepthEnable = true;
	dsDescription.DepthFunc = D3D11_COMPARISON_LESS;
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
	dsDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	renderDevice->CreateDepthStencilState(&dsDescription, &depthStencilState);
	deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC  DepthStencilViewDesc = {};
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDesc.Format = dsTexDescription.Format;
	DepthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = renderDevice->CreateDepthStencilView(depthStencilTextureBuffer, &DepthStencilViewDesc, &depthStencilConfiguration);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to create depth-stencil view.", "NGine Direct3D Error", MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}

bool NRenderer::setupRenderingMatrix()
{
	HRESULT  hr = S_OK;

	D3D11_BUFFER_DESC   constBufferDesc = {0};
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constBufferDesc.ByteWidth = sizeof(cBufferMatrix);
	constBufferDesc.CPUAccessFlags = 0;
	constBufferDesc.StructureByteStride = 0;
	constBufferDesc.MiscFlags = 0;

	hr = renderDevice->CreateBuffer(&constBufferDesc, nullptr, &constBuffer);

	return SUCCEEDED(hr);
}

void NRenderer::UpdateRenderState()
{
	// Updates constant buffers before allowing objects to draw and then present. 
	// Base update on the assigned rendering camera.

	// Setup Main camera and construct matrix.

	view = DirectX::XMMatrixLookAtLH(
		mainCamera->getPosition().getRawVector(),
		mainCamera->getCameraLookAt().getRawVector(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
	);

	mvpMatracies.projMatrix = DirectX::XMMatrixTranspose
	(
		DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(mainCamera->getCameraFov()), 1280 / 720, mainCamera->getCameraNearZ(), mainCamera->getCameraFarZ())
	);
}

NMaterial* NRenderer::searchMaterials(std::string name)
{
	for (int i = 0; i < materialBuffer.size(); i++) 
	{
		if (materialBuffer[i]->getShaderName() == name) 
		{
			return materialBuffer[i].get();
		}
	}

	return nullptr;
}

N3DMesh* NRenderer::searchMesh(std::string name)
{
	for (int i = 0; i < meshBuffer.size(); i++)
	{
		if (meshBuffer[i]->getName() == name)
		{
			return meshBuffer[i].get();
		}
	}

	return nullptr;
}
