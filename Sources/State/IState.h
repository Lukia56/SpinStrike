#pragma once

template <class Owner>
class StateContext;

/// <summary>
/// 状態のインターフェース
/// </summary>
template <class Owner>
class IState
{
public:

	virtual ~IState() = default;

	virtual void Enter(Owner& owner) = 0;

	virtual void Update(Owner& owner, StateContext<Owner>& context) = 0;

	virtual void Exit(Owner& owner) = 0;
};
