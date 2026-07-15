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
				static_assert(sizeof(T) == 0, "Data::Csv::FromCsv // ’è‹`‚³‚ê‚Ä‚¢‚È‚¢Œ^‚ÉŠ„‚è“–‚Ä‚Å‚«‚Ü‚¹‚ñ");

				return T{};
			}
		};

		template <>
		struct FromCsv<PlayerParam>
		{
			static PlayerParam Binding(const Row& row)
			{
				PlayerParam param;
				param.walkSpeed = Convert<float>(row.at("walkSpeed"));
				param.walkAccel = Convert<float>(row.at("walkAccel"));
				param.dashCoef = Convert<float>(row.at("dashCoef"));
				param.jumpForce = Convert<float>(row.at("jumpForce"));
				param.jumpCancelThreshold = Convert<float>(row.at("jumpCancelThreshold"));
				param.jumpBufferTime = Convert<float>(row.at("jumpBufferTime"));
				param.wallJumpVerticalForce = Convert<float>(row.at("wallJumpVerticalForce"));
				param.wallJumpHorizontalForce = Convert<float>(row.at("wallJumpHorizontalForce"));
				param.wallJumpIgnoreMoveInputTime = Convert<float>(row.at("wallJumpIgnoreMoveInputTime"));
				param.stickWallFallSpeed = Convert<float>(row.at("stickWallFallSpeed"));
				param.stickWallCancelTimeThreshold = Convert<float>(row.at("stickWallCancelTimeThreshold"));
				param.stickWallCancelMoveVectorThreshold = Convert<float>(row.at("stickWallCancelMoveVectorThreshold"));
				param.airResistanceCoef = Convert<float>(row.at("airResistanceCoef"));
				param.gravity = Convert<float>(row.at("gravity"));
				return param;
			}
		};
	}
}
