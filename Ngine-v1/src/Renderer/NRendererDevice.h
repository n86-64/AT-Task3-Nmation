#pragma once

// File - NRenderDevice.h
// Discription - Abstraction for setting up render devices in D3D11 and Vulkan.

#include <memory>
#include <dxgi.h>

// TODO - Do we need error codes for debugging purposes.
// TODO - Finish implimentation of this to allow for more dynamic system.
//  (If I have Time.)

// Abstraction for retrieving a compatable rendering device for use in initialising Direct3D


//class NRenderDevice 
//{
//public:
//	NRenderDevice() {};
//
//	bool fetchGraphicsAdapter();
//
//private:
//	std::unique_ptr<IDXGIAdapter>    device = nullptr;
//	std::unique_ptr<IDXGIFactory1>    deviceDatabase = nullptr;
//
//	DXGI_ADAPTER_DESC				 deviceInformation;
//};