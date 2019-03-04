#include <algorithm>
#include <climits>

#include <Assimp/mesh.h>
#include <Assimp/scene.h>

#include "Renderer/NMaterialProperites.h"

#include "Helpers/OBJ_Loader.h"
#include "N3DMesh.h"
#include "Renderer/NMaterial.h"


N3DMesh::N3DMesh(std::string name, ID3D11Device* device)
	:meshName(name)
{
	// Load the mesh and then render. 
	loadMesh(name);
	setupMesh(device);
}

N3DMesh::N3DMesh(ID3D11Device* device, aiMesh* meshObject)
{
	VertexInput newInput;
	verticies.reserve(meshObject->mNumVertices);

	meshName = std::string(meshObject->mName.C_Str());
	aiVector3D vec;

	for (int i = 0; i < meshObject->mNumVertices; i++) 
	{
		vec = meshObject->mVertices[i];
		newInput.pos = DirectX::XMFLOAT4(vec.x, vec.y, vec.z, 1.0f);

		if (meshObject->mColors[0])
		{
			newInput.col = DirectX::XMFLOAT4((float)meshObject->mColors[0][i].r, (float)meshObject->mColors[0][i].g, (float)meshObject->mColors[0][i].b, (float)meshObject->mColors[0][i].a);
		}

		if (meshObject->mTextureCoords[0])
		{
			newInput.uv = DirectX::XMFLOAT2((float)meshObject->mTextureCoords[0][i].x, (float)meshObject->mTextureCoords[0][i].y);
		}

		if (meshObject->mColors[0]) 
		{
			newInput.col = DirectX::XMFLOAT4((float)meshObject->mColors[0][i].r, (float)meshObject->mColors[0][i].g, (float)meshObject->mColors[0][i].b, (float)meshObject->mColors[0][i].a);
		}
		else 
		{
			newInput.col = DirectX::XMFLOAT4(meshObject->mNormals[i].x, meshObject->mNormals[i].y, meshObject->mNormals[i].z, 1.0f);
		}

		verticies.emplace_back(newInput);
	}

	for (int j = 0; j < meshObject->mNumFaces; j++) 
	{
		for (int k = 0; k < meshObject->mFaces[j].mNumIndices; k++) 
		{
			indicies.emplace_back(meshObject->mFaces[j].mIndices[k]);
		}
	}


	//setupMesh(device);
}

N3DMesh::~N3DMesh()
{
	NMATERIAL_RELEASE(vBuffer);
	NMATERIAL_RELEASE(iBuffer);
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

int N3DMesh::getIndexCount() const
{
	return indicies.size();
}

DirectX::XMMATRIX N3DMesh::setModelMatrix(aiNode* node)
{
	modelMatrix = convertToMatrix(&node->mTransformation);
	return modelMatrix;
}

void N3DMesh::addBoneValues(int vertexID, int boneId, float weight)
{
	DirectX::XMVECTOR indexVec = DirectX::XMVectorSetInt(verticies[vertexID].bIndex.x, verticies[vertexID].bIndex.y, verticies[vertexID].bIndex.z, verticies[vertexID].bIndex.w);
	DirectX::XMVECTOR weightVec = DirectX::XMLoadFloat4(&verticies[vertexID].bWeight);
	
	int boneSlot = -1;
	for (int i = 0; i < 4; i++) 
	{
		if (DirectX::XMVectorGetIntByIndex(indexVec, i) == UINT_MAX) 
		{
			boneSlot = i;
			break;
		}
	}

	if (boneSlot == -1) { return; }

	indexVec = DirectX::XMVectorSetIntByIndex(indexVec, boneId, boneSlot);
	weightVec = DirectX::XMVectorSetByIndex(weightVec, weight, boneSlot);

	// Set the bone values manualy.
	verticies[vertexID].bIndex.x = DirectX::XMVectorGetIntByIndex(indexVec, 0);
	verticies[vertexID].bIndex.y = DirectX::XMVectorGetIntByIndex(indexVec, 1);
	verticies[vertexID].bIndex.z = DirectX::XMVectorGetIntByIndex(indexVec, 2);
	verticies[vertexID].bIndex.w = DirectX::XMVectorGetIntByIndex(indexVec, 3);


//	DirectX::XMStoreUInt4A(&verticies[vertexID].bIndex, indexVec);
	DirectX::XMStoreFloat4(&verticies[vertexID].bWeight, weightVec);
}

void N3DMesh::loadMesh(std::string name)
{
	// Here we load the mesh (Currently only supports OBJ but can be expanded later.)
	objl::Loader  object;

	DirectX::XMFLOAT4  pos;
	DirectX::XMFLOAT4  col;
	DirectX::XMFLOAT2  uv;

	if (object.LoadFile("resources/meshes/" + name + ".obj")) 
	{
		// Load the mesh into memory.
		verticies.resize(object.LoadedMeshes[0].Vertices.size());
		int i = 0;
		for (objl::Vertex v : object.LoadedMeshes[0].Vertices) 
		{
			pos = DirectX::XMFLOAT4(v.Position.X, v.Position.Y, v.Position.Z, 1.0f);
			col = DirectX::XMFLOAT4(clamp(v.Position.X, 0.0f, 0.2f), clamp(v.Position.Y, 0.2f, 0.5f), clamp(v.Position.Z, 0.f, 1.0f), 1.0f);
			uv = DirectX::XMFLOAT2(v.TextureCoordinate.X, v.TextureCoordinate.Y);

			verticies[i] = VertexInput{ pos, col, uv };
			++i;
		}

		indicies = object.LoadedIndices;
	}
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
