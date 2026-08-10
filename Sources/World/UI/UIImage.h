#pragma once

#include "../GameObject.h"
#include <string>

class SpriteRenderer;

class UIImage : public GameObject
{
public:

	UIImage(const std::string& spritePath);
	~UIImage() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	std::unique_ptr<SpriteRenderer> mRenderer;
};
