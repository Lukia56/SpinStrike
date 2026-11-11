#pragma once

#include "../GameObject.h"

struct EnemyInitData;
struct WaypointGroup;

/// <summary>
/// “G‚Ìƒf[ƒ^‚©‚ç“G‚ğ¶¬‚µ‚ÄŠÇ—
/// </summary>
class EnemyManager : public GameObject
{
public:

	EnemyManager(const std::vector<EnemyInitData>& enemyInitData, const std::vector<WaypointGroup>& waypointGroups, Transform* playerTransform);
	~EnemyManager() = default;

	void Init() override;
	void Update() override;
};
