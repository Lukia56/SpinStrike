#pragma once

#include "Param/Param.h"

class PlayerDataManager
{
private:

	PlayerDataManager() = default;
	PlayerDataManager(const PlayerDataManager&) = delete;
	PlayerDataManager& operator=(const PlayerDataManager&) = delete;
	PlayerDataManager(PlayerDataManager&&) = delete;
	PlayerDataManager& operator=(PlayerDataManager&&) = delete;

public:

	~PlayerDataManager() = default;

	void Initialize();

	static PlayerDataManager& GetInstance();

public:

	const PlayerParam& GetPlayerParam() const { return mPlayerParam; }

	const std::vector<AABBColliderParam>& GetAABBParams() const { return mAABBParams; }

private:

	PlayerParam mPlayerParam;

	std::vector<AABBColliderParam> mAABBParams;
};
