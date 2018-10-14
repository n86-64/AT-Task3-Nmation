#include "N3DMesh.h"

N3DMesh::N3DMesh(std::string name)
	:meshName(name)
{
}

std::string N3DMesh::getName() const
{
	return meshName;
}
