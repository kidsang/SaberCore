#include "scMovable.h"
#include "scSceneManager.h"


scMovable::scMovable(scSceneManager* sceneManager, const std::string& name)
	: mSceneManager(sceneManager), mName(name), mVisible(true)
{
}

scMovable::~scMovable( void )
{

}

