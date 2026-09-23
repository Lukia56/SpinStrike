#pragma once

#include "Creator.h"
#include <string>

class Player;
class PlayerTornado;

class PlayerCreator : public Creator<Player>
{
public:

	PlayerCreator(const std::string& modelPath, const std::string& playerParamPath, const std::string& aabbParamPath, const std::string& initData, PlayerTornado* tornado);
	virtual ~PlayerCreator() = default;

	std::unique_ptr<Player> CreateInstance() override;

private:

	std::string mModelPath;
	std::string mPlayerParamPath;
	std::string mAABBParamPath;
	std::string mInitDataPath;

	PlayerTornado* mTornado;
};
