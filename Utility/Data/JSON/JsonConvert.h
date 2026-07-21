#pragma once

#include "../Data.h"
#include "Utility/Vector.h"

inline void from_json(const Data::Json::JsonObject& j, Vector2& val)
{
	try
	{
		val.x = j.at("x").get<float>();
		val.y = j.at("y").get<float>();
	}
	catch (Data::Json::JsonObject::out_of_range e)
	{
		assert(false && "from_json() // —v‘f‚ª•s‘«‚µ‚Ä‚¢‚é‚½‚ßVector2‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½");
		val = Vector2::Zero;
	}
}

inline void from_json(const Data::Json::JsonObject& j, Vector3& val)
{
	try
	{
		val.x = j.at("x").get<float>();
		val.y = j.at("y").get<float>();
		val.z = j.at("z").get<float>();
	}
	catch (Data::Json::JsonObject::out_of_range e)
	{
		assert(false && "from_json() // —v‘f‚ª•s‘«‚µ‚Ä‚¢‚é‚½‚ßVector3‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½");
		val = Vector3::Zero;
	}
}
