#include "StageObjectCreator.h"
#include <memory>
#include "Param/Param.h"
#include "Stage/StageModelDataBase.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "World/Object/InhalableStageObject.h"
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

    std::unique_ptr<StageObject> instance;
    if (mParam.canInhale)
    {
        instance = std::make_unique<InhalableStageObject>(mParam, model);
    }
    else
    {
        instance = std::make_unique<StageObject>(mParam, model);
    }

    return std::move(instance);
}
