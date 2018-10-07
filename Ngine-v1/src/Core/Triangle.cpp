#include "Triangle.h"

Triangle::Triangle(NMaterial * material)
	:mat(material)
{
	createObjectDiscriptors();
}

Triangle::~Triangle()
{
	if (mat) { delete mat; mat = nullptr; }
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }
}

void Triangle::Update()
{
	return;
}

void Triangle::Render(NRenderer* renderer)
{
	// Here we draw the triangle. 

}

void Triangle::createObjectDiscriptors()
{
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(VertexInput) * ARRAYSIZE(verticies);
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.CPUAccessFlags = 0;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(unsigned short) * ARRAYSIZE(indicies);
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.CPUAccessFlags = 0;

	vdata.pSysMem = &verticies;
	vdata.SysMemPitch = 0;
	vdata.SysMemSlicePitch = 0;

	idata.pSysMem = &indicies;
	idata.SysMemPitch = 0;
	idata.SysMemSlicePitch = 0;

}
