#include "StageObjectCreator.h"
#include <memory>
#include "Param/Param.h"
#include "Stage/StageModelDataBase.h"
#include "World/Object/StageObject.h"

StageObjectCreator::StageObjectCreator(Stage::StageModelDataBase* modelDataBase) :
    mModelDataBase(modelDataBase),
    mParam{}
{
}

std::unique_ptr<GameObject> StageObjectCreator::CreateInstance()
{
    auto instance = std::make_unique<StageObject>(mParam, mModelDataBase->GetFilePath(mParam.name));

    return std::move(instance);
}
