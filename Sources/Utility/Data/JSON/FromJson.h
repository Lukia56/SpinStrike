#pragma once

#include "../Data.h"
#include "JsonConvert.h"
#include "Param/Param.h"

namespace Data
{
	namespace Json
	{
		template <typename T>
		struct FromJson
		{
			static T Binding(const JsonObject& json)
			{
				static_assert(sizeof(T) == 0, "Data::Json::FromJson // Cannot binding an undefined type");

				return T{};
			}
		};

		template <>
		struct FromJson<StageObjectParam>
		{
			static StageObjectParam Binding(const JsonObject& json)
			{
				StageObjectParam param;

				param.name = Get<std::string>(json, "name");
				param.transform = Get<TempTransform>(json, "transform");
				param.bounds = Get<TempBounds>(json, "bounds");

				return param;
			}
		};

		template <>
		struct FromJson<EnemyPatrollingData>
		{
			static EnemyPatrollingData Binding(const JsonObject& json)
			{
				EnemyPatrollingData data;

				data.waypointGroupID = Get<int>(json, "waypointGroupID");
				data.isLoop = Get<bool>(json, "isLoop");
				data.waypointActions = Get<std::vector<WaypointActionData>>(json, "waypointActions");

				return data;
			}
		};

		template <>
		struct FromJson<WaypointGroup>
		{
			static WaypointGroup Binding(const JsonObject& json)
			{
				WaypointGroup data;

				data.waypoints = Get<std::vector<Waypoint>>(json);

				return data;
			}
		};
	}
}
