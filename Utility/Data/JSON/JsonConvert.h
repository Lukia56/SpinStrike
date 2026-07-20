#pragma once

#include "../Data.h"
#include "Utility/Vector.h"

inline void from_json(const Data::Json::JsonObject& j, Vector2& val)
{
	if (!j.contains("x")
	|| !j.contains("y"))
	{
		assert(false && "from_json() // ¬•ª‚ª‘«‚è‚È‚¢‚½‚ßVector2‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½");
		val = Vector2::Zero;
		return;
	}

	val.x = j.at("x").get<float>();
	val.y = j.at("y").get<float>();
}

inline void from_json(const Data::Json::JsonObject& j, Vector3& val)
{
	if (!j.contains("x")
	|| !j.contains("y")
	|| !j.contains("z"))
	{
		assert(false && "from_json() // ¬•ª‚ª‘«‚è‚È‚¢‚½‚ßVector3‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½");
		val = Vector3::Zero;
		return;
	}

	val.x = j.at("x").get<float>();
	val.y = j.at("y").get<float>();
	val.z = j.at("z").get<float>();
}
