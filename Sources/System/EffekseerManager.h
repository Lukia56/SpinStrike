#pragma once

/// <summary>
/// Effekseer‚Ìİ’èˆ—‚ğŠÇ—‚·‚é
/// </summary>
class EffekseerManager
{
public:

	EffekseerManager() = default;
	~EffekseerManager() = default;

	bool Initialize();

	void Finalize();

	void Update();

	void Draw();
};
