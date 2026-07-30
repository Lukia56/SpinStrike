#pragma once

#include "../Data.h"
#include "Param/TempParam.h"
#include "Utility/Vector.h"

namespace Data
{
	namespace Json
	{
		/// <summary>
		/// JSONオブジェクトを任意の型へ変換する
		/// 例外が出たらアサートを表示し、空の値を返す
		/// </summary>
		template <typename T>
		inline T Convert(const JsonObject& json)
		{
			try
			{
				T value = json.get<T>();
				return value;
			}
			catch (JsonObject::type_error)
			{
				assert(false && "Data::Json // 型変換に失敗しました");
				return T{};
			}
		}
	}
}

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

inline void from_json(const Data::Json::JsonObject& j, TempTransform& val)
{
	try
	{
		val.position = j.at("position").get<Vector3>();
		val.rotation = j.at("rotation").get<Vector3>();
		val.scale = j.at("scale").get<Vector3>();
	}
	catch (Data::Json::JsonObject::out_of_range e)
	{
		assert(false && "from_json() // 要素が不足しているためVector3に変換できませんでした");
		val = {};
	}
}

inline void from_json(const Data::Json::JsonObject& j, TempBounds& val)
{
	try
	{
		val.size = j.at("size").get<Vector3>();
		val.offsetPos = j.at("offset").get<Vector3>();
	}
	catch (Data::Json::JsonObject::out_of_range e)
	{
		assert(false && "from_json() // 要素が不足しているためVector3に変換できませんでした");
		val = {};
	}
}
