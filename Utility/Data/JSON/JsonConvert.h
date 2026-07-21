#pragma once

#include "../Data.h"
#include "Utility/Vector.h"

// from_jsonのオーバーロードを用意して、ユーザ定義型の変換処理を実装する
// ・注意点
// 　from_json関数は変換したい型と同じ名前空間で定義しなければ、認識されずエラーになる
// ・その他注意点↓
// 　https://github.com/nlohmann/json#basic-usage

inline void from_json(const Data::Json::JsonObject& j, Vector2& val)
{
	try
	{
		val.x = j.at("x").get<float>();
		val.y = j.at("y").get<float>();
	}
	catch (Data::Json::JsonObject::out_of_range e)
	{
		assert(false && "from_json() // 要素が不足しているためVector2に変換できませんでした");
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
		assert(false && "from_json() // 要素が不足しているためVector3に変換できませんでした");
		val = Vector3::Zero;
	}
}
