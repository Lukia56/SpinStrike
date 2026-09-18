#include "Renderer.h"
#include "System/Resource/ResourceBase.h"

Renderer::Renderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource) :
	mResource(nullptr),
	mOwner(owner)
{
}
