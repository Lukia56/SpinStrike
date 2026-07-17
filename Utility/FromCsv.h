#pragma once

#include "Data.h"
#include "CsvConvert.h"
#include "Param/Param.h"

namespace Data
{
	namespace Csv
	{
		template <typename T>
		struct FromCsv
		{
			static T Binding(const Row& row)
			{
				static_assert(sizeof(T) == 0, "Data::Csv::FromCsv // 定義されていない型に割り当てできません");

				return T{};
			}
		};

		template <typename T>
		T Get(const Row& row, const std::string& key)
		{
			try
			{
				T value = Convert<T>(row.at(key));

				return value;
			}
			catch (std::out_of_range)
			{
				assert(false && "Data::Csv::Get // 存在しないパラメータ名のため値の取得に失敗しました");

				return T{};
			}
		}

		template <>
		struct FromCsv<PlayerParam>
		{
			static PlayerParam Binding(const Row& row)
			{
				PlayerParam param;
				param.walkSpeed = Get<float>(row, "walkSpeed");
				param.walkAccel = Get<float>(row, "walkAccel");
				param.dashCoef = Get<float>(row, "dashCoef");
				param.jumpForce = Get<float>(row, "jumpForce");
				param.jumpCancelThreshold = Get<float>(row, "jumpCancelThreshold");
				param.jumpBufferTime = Get<float>(row, "jumpBufferTime");
				param.wallJumpVerticalForce = Get<float>(row, "wallJumpVerticalForce");
				param.wallJumpHorizontalForce = Get<float>(row, "wallJumpHorizontalForce");
				param.wallJumpIgnoreMoveInputTime = Get<float>(row, "wallJumpIgnoreMoveInputTime");
				param.stickWallFallSpeed = Get<float>(row, "stickWallFallSpeed");
				param.stickWallCancelTimeThreshold = Get<float>(row, "stickWallCancelTimeThreshold");
				param.stickWallCancelMoveVectorThreshold = Get<float>(row, "stickWallCancelMoveVectorThreshold");
				param.airResistanceCoef = Get<float>(row, "airResistanceCoef");
				param.gravity = Get<float>(row, "gravity");
				return param;
			}
		};

		template <>
		struct FromCsv<AABBColliderParam>
		{
			static AABBColliderParam Binding(const Row& row)
			{
				AABBColliderParam param;
				param.size.x = Get<float>(row, "sizeX");
				param.size.y = Get<float>(row, "sizeY");
				param.size.z = Get<float>(row, "sizeZ");
				param.offsetPos.x = Get<float>(row, "offsetX");
				param.offsetPos.y = Get<float>(row, "offsetY");
				param.offsetPos.z = Get<float>(row, "offsetZ");
				param.collisionTag = Get<Collision::Tag>(row, "collisionTag");
				return param;
			}
		};
	}
}
