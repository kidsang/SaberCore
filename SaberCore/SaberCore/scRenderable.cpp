#include "scRenderable.h"


scRenderable::scRenderable(scMesh* mesh, scVertexShader* vs, scPixelShader* ps)
	: mMesh(mesh), mVertexShader(vs), mPixelShader(ps)
{
}


scRenderable::~scRenderable(void)
{
}
