#pragma once

#include <functional>

/// <summary>
/// ImGui‚ğŠÇ—‚µ‚Ä•`‰æ‚·‚éƒNƒ‰ƒX
/// </summary>
class ImGuiRenderer
{
public:

	ImGuiRenderer() = default;
	~ImGuiRenderer() = default;

	void Initialize() const;

	void Finalize() const;

	/// <summary>
	/// ImGui•`‰æˆ—
	/// </summary>
	/// <param name="func">•`‰æˆ—‚ğs‚¤ŠÖ”</param>
	void Draw(std::function<void(void)> func) const;
};
