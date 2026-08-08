#include "ModelInstance.h"
#include <DxLib.h>
#include "System/Resource/ResourceBase.h"

ModelInstance::ModelInstance(std::shared_ptr<Resource::ResourceBase> resource) :
	mDuplicatedHandle(-1)
{
	mDuplicatedHandle = MV1DuplicateModel(resource->GetHandle());
}

ModelInstance::~ModelInstance()
{
	MV1DeleteModel(mDuplicatedHandle);
}
