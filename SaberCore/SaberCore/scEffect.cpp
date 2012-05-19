#include "scEffect.h"


scEffect::scEffect(std::string name, std::string path, std::string group)
	: scResource(name, path, group)
{
}


scEffect::~scEffect(void)
{
}

bool scEffect::LoadImpl( ID3D11Device* device )
{
	throw std::exception("The method or operation is not implemented.");
}

void scEffect::UnloadImpl()
{
	throw std::exception("The method or operation is not implemented.");
}
