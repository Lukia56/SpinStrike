#pragma once

#include <memory>

/// <summary>
/// 状態のインターフェース
/// </summary>
template <class Owner>
class IState
{
public:

	virtual ~IState() = default;

	virtual void Enter(Owner& owner) = 0;

	/// <summary>
	/// 状態の更新処理
	/// </summary>
	/// <returns>次の状態のポインタ。nullptrを返すと遷移しない</returns>
	virtual std::unique_ptr<IState<Owner>> Update(Owner& owner) = 0;

	virtual void Exit(Owner& owner) = 0;
};
