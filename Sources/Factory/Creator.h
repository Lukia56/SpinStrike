#pragma once

#include <memory>

/// <summary>
/// ファクトリーの基底
/// </summary>
template <class T>
class Creator
{
public:

	Creator() = default;
	virtual ~Creator() = default;

	virtual std::unique_ptr<T> CreateInstance() = 0;
};
