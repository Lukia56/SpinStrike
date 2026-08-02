#pragma once

#include "Creator.h"
#include "Param/Param.h"

class GameObject;
namespace Stage
{
	class StageModelDataBase;
}

class StageObjectCreator : Creator<GameObject>
{
public:

	StageObjectCreator(Stage::StageModelDataBase* modelDataBase);
	virtual ~StageObjectCreator() = default;

	std::unique_ptr<GameObject> CreateInstance() override;

public:

	void SetParam(const StageObjectParam& param) { mParam = param; }

private:

	Stage::StageModelDataBase* mModelDataBase;

	StageObjectParam mParam;
};
