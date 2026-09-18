#include "StageObjectCreator.h"
#include <memory>
#include "Param/Param.h"
#include "Stage/StageModelDataBase.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "World/Object/StageObject.h"

StageObjectCreator::StageObjectCreator(Stage::StageModelDataBase* modelDataBase) :
    mModelDataBase(modelDataBase),
    mParam{}
{
}

std::unique_ptr<GameObject> StageObjectCreator::CreateInstance()
{
    std::string modelPath = mModelDataBase->GetFilePath(mParam.name);
    std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(modelPath);

    auto instance = std::make_unique<StageObject>(mParam, model);

    return std::move(instance);
}
