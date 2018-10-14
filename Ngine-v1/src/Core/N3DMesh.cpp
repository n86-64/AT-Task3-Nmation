#include "N3DMesh.h"

N3DMesh::N3DMesh(std::string name, ID3D11Device* device)
	:meshName(name)
{
	// Load the mesh and then render. 

}

std::string N3DMesh::getName() const
{
	return meshName;
}

ID3D11Buffer* N3DMesh::getVertexBuffer()
{
	return vBuffer;
}

ID3D11Buffer * N3DMesh::getIndexBuffer()
{
	return iBuffer;
}

void N3DMesh::loadMesh(std::string name)
{
	// Here we load the mesh
}

void N3DMesh::setupMesh(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	// here we setup the mesh.
	D3D11_BUFFER_DESC   vBufDesc = {};
	vBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufDesc.ByteWidth = sizeof(VertexInput) * verticies.size();
	vBufDesc.StructureByteStride = 0;
	vBufDesc.CPUAccessFlags = 0;
	vBufDesc.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA   vdata;
	vdata.pSysMem = verticies.data();
	vdata.SysMemPitch = 0;
	vdata.SysMemSlicePitch = 0;

	// here we setup the mesh.
	D3D11_BUFFER_DESC   iBufDesc = {};
	iBufDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufDesc.ByteWidth = sizeof(unsigned int) * indicies.size();
	iBufDesc.StructureByteStride = 0;
	iBufDesc.CPUAccessFlags = 0;
	iBufDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA   idata;
	idata.pSysMem = indicies.data();
	idata.SysMemPitch = 0;
	idata.SysMemSlicePitch = 0;


	hr = device->CreateBuffer(&vBufDesc, &vdata, &vBuffer);
	hr = device->CreateBuffer(&iBufDesc, &idata, &iBuffer);
}
