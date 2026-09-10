#pragma once

#include <memory>
#include "../Data.h"
#include "Param/TempParam.h"
#include "Utility/Vector.h"
#include "State/Enemy/Action/EnemyActionTest.h"

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

		/// <summary>
		/// 安全な値の取得処理
		/// </summary>
		template <typename T>
		T Get(const JsonObject& json, const std::string& key)
		{
			try
			{
				T value = Convert<T>(json.at(key));

				return value;
			}
			catch (JsonObject::out_of_range)
			{
				assert(false && "Data::Json::Get // 存在しないパラメータ名のため値の取得に失敗しました");

				return T{};
			}
		}
		/// <summary>
		/// 匿名型用の安全な値の取得処理
		/// </summary>
		template <typename T>
		T Get(const JsonObject& json)
		{
			try
			{
				T value = json.get<T>();

				return value;
			}
			catch (JsonObject::out_of_range)
			{
				assert(false && "Data::Json::Get // 存在しないパラメータ名のため値の取得に失敗しました");

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
	val.x = Data::Json::Get<float>(j, "x");
	val.y = Data::Json::Get<float>(j, "y");
}

inline void from_json(const Data::Json::JsonObject& j, Vector3& val)
{
	val.x = Data::Json::Get<float>(j, "x");
	val.y = Data::Json::Get<float>(j, "y");
	val.z = Data::Json::Get<float>(j, "z");
}

inline void from_json(const Data::Json::JsonObject& j, TempTransform& val)
{
	val.position = Data::Json::Get<Vector3>(j, "position");
	val.rotation = Data::Json::Get<Vector3>(j, "rotation");
	val.scale = Data::Json::Get<Vector3>(j, "scale");
}

inline void from_json(const Data::Json::JsonObject& j, TempBounds& val)
{
	val.size = Data::Json::Get<Vector3>(j, "size");
	val.offsetPos = Data::Json::Get<Vector3>(j, "offsetPos");
}

inline void from_json(const Data::Json::JsonObject& j, std::unique_ptr<EnemyActionBase>& action)
{
	std::string actionType = Data::Json::Get<std::string>(j, "actionType");

	// アクションタイプに応じたアクションを生成
	action = std::make_unique<EnemyActionTest>();
}

inline void from_json(const Data::Json::JsonObject& j, WaypointActionData& waypointAction)
{
	waypointAction.waypointID = Data::Json::Get<int>(j, "waypointID");

	waypointAction.actions = Data::Json::Get<std::vector<std::unique_ptr<EnemyActionBase>>>(j, "actions");
}

inline void from_json(const Data::Json::JsonObject& j, Waypoint& waypoint)
{
	waypoint.position = Data::Json::Get<Vector3>(j, "position");
}
