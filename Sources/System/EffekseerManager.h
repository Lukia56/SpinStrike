#pragma once

/// <summary>
/// Effekseerの設定処理を管理する
/// </summary>
class EffekseerManager
{
public:

	EffekseerManager() = delete;

	static bool Initialize();

	/// <summary>
	/// Effkseer_End関数のラッパー
	/// </summary>
	static void Finalize();

	/// <summary>
	/// UpdateEffekseer3D関数のラッパー
	/// </summary>
	static void Update();

	/// <summary>
	/// DrawEffekseer3D関数のラッパー
	/// </summary>
	static void Draw();

	/// <summary>
	/// Effekseer_Sync3DSetting関数のラッパー
	/// </summary>
	static void Sync3DSettings();
};
