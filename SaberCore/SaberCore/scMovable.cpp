#include "scMovable.h"


scMovable::scMovable(scSceneManager* sceneManager, const std::string& name)
	: mSceneManager(sceneManager), mName(name)
{
}

scMovable::~scMovable( void )
{

}

