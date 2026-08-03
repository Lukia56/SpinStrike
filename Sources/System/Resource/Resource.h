#pragma once

#include <string>

class ResourceManager;

/// <summary>
/// リソース系クラスの基底
/// </summary>
class Resource
{
public:

	Resource() : mHandle(-1) {};
	virtual ~Resource() = default;

	virtual int GetHandle() const { return mHandle; }

protected:

	int mHandle;

private:

	friend ResourceManager;
	
	/// <summary>
	/// 読み込み処理がリソースごとに違うため純粋仮想化
	/// </summary>
	/// <returns>読み込みに成功したらtrue</returns>
	virtual bool Load(const std::string& path) = 0;

	/// <summary>
	/// 解放処理がリソースごとに違うため純粋仮想化
	/// </summary>
	virtual void Delete() = 0;
};

/// <summary>
/// テクスチャを管理するクラス
/// </summary>
class Texture : public Resource
{
public:

	Texture() = default;
	~Texture() = default;

private:

	bool Load(const std::string& path) override;

	void Delete() override;
};

/// <summary>
/// モデルを管理するクラス
/// </summary>
class Model : public Resource
{
public:

	Model() = default;
	~Model() = default;

	int GetHandle() const override;

private:

	bool Load(const std::string& path) override;

	void Delete() override;
};

/// <summary>
/// サウンドを管理するクラス
/// </summary>
class Sound : public Resource
{
public:

	Sound() = default;
	~Sound() = default;

private:

	bool Load(const std::string& path) override;

	void Delete() override;
};

/// <summary>
/// サウンドを管理するクラス
/// </summary>
class Font : public Resource
{
public:

	Font() = default;
	~Font() = default;

private:

	bool Load(const std::string& path) override;

	void Delete() override;
};
