// File - N3DMesh.h
// Description - Describes 3D mewsh data for loading and instanciating.

#pragma once

#include <vector>
#include <string>
#include "Helpers/NMaths.h"

class N3DMesh 
{
public:
	N3DMesh(std::string name); 

	// TODO - Add code to retreive model, vertex, uv data etc.
	void loadMesh();

	std::string getName() const;

	DirectX::XMFLOAT4   getPositionVertex(int index);
	DirectX::XMFLOAT4   getColourVertex(int index);
	DirectX::XMFLOAT2   getTextureUVVertex(int index);

private:
	std::string meshName = "Null mesh";

	int arrayCount = 0;
	std::vector<DirectX::XMFLOAT2>    uv;
	std::vector<DirectX::XMFLOAT4>   pos;
	std::vector<DirectX::XMFLOAT4>   col;
	std::vector<unsigned int>		 indicies;
};