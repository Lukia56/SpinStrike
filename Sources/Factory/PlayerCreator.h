#pragma once

#include "Creator.h"
#include <string>

class Player;
class PlayerTornado;

class PlayerCreator : public Creator<Player>
{
public:

	PlayerCreator(const std::string& initData, std::unique_ptr<PlayerTornado> tornado);
	virtual ~PlayerCreator() = default;

	std::unique_ptr<Player> CreateInstance() override;

private:

	std::string mInitDataPath;

	std::unique_ptr<PlayerTornado> mTornado;
};
