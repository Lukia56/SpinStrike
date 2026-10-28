#include "PlayerDataManager.h"
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kParamPath = "Resources\\MasterData\\Player\\PlayerParam.csv";
	const char* const kAABBParamPath = "Resources\\MasterData\\Player\\PlayerAABBColliderParam.csv";
	const char* const kAnimationParamPath = "Resources\\MasterData\\Player\\PlayerAnimationParam.csv";
}

void PlayerDataManager::Initialize()
{
	mPlayerParam = Data::Csv::LoadCsvAs<PlayerParam>(kParamPath)[0];

	mAABBParams = Data::Csv::LoadCsvAs<AABBColliderParam>(kAABBParamPath);

	mAnimationParams = Data::Csv::LoadCsvAs<AnimationParam>(kAnimationParamPath);
}

PlayerDataManager& PlayerDataManager::GetInstance()
{
	static PlayerDataManager instance;

	return instance;
}

const AnimationParam& PlayerDataManager::GetAnimationParam(PlayerAnimation animID) const
{
	size_t index = static_cast<size_t>(animID);

	assert(index < mAnimationParams.size() && "Player // 存在しないアニメーションデータにアクセスしました");

	return mAnimationParams[index];
}
