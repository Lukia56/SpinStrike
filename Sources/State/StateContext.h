#pragma once

#include <cassert>
#include <concepts>
#include <memory>
#include <stack>
#include <typeindex>
#include <unordered_map>
#include "IState.h"

/// <summary>
/// 状態を管理し、状態切り替えを行う
/// </summary>
template <class Owner>
class StateContext
{
public:

	using StateInst = std::unique_ptr<IState<Owner>>;

	StateContext(Owner* owner);
	~StateContext() = default;

	void Update();

	template <class State>
	requires std::derived_from<State, IState<Owner>>
	void ChangeState();

	template <class State>
	requires std::derived_from<State, IState<Owner>>
	void PushState(bool isCallExit = true);

	void PopState(bool isCallEnter = true);

	void AddStateToPool(StateInst state);

private:

	std::stack<StateInst> mActiveStates;

	std::unordered_map<std::type_index, StateInst> mPoolStates;

	Owner* mOwner;
};

template<class Owner>
inline StateContext<Owner>::StateContext(Owner* owner) :
	mOwner(owner)
{
	assert(mOwner && "StateContext // 所有者がnullptrです");
}

template<class Owner>
inline void StateContext<Owner>::Update()
{
	if (mActiveStates.empty()) return;

	mActiveStates.top()->Update(*mOwner, *this);
}

template<class Owner>
template<class State>
requires std::derived_from<State, IState<Owner>>
inline void StateContext<Owner>::ChangeState()
{
	PopState(false);
	PushState<State>(false);
}

template<class Owner>
template<class State>
requires std::derived_from<State, IState<Owner>>
inline void StateContext<Owner>::PushState(bool isCallExit)
{
	std::type_index type = typeid(State);

	if (!mPoolStates.contains(type))
	{
		assert(false && "StateContext // プールに存在しない状態をプッシュできませんでした");
		return;
	}

	// 現在の状態を出る
	if (isCallExit && !mActiveStates.empty())
	{
		mActiveStates.top()->Exit(*mOwner);
	}

	// 状態をプールから取り出しアクティブにする
	StateInst state = std::move(mPoolStates.at(type));
	mPoolStates.erase(type);
	
	state->Enter(*mOwner);
	mActiveStates.emplace(std::move(state));
}

template<class Owner>
inline void StateContext<Owner>::PopState(bool isCallEnter)
{
	if (mActiveStates.empty()) return;

	StateInst state = std::move(mActiveStates.top());
	mActiveStates.pop();

	// ポップする状態を出て、次の状態に入る
	state->Exit(*mOwner);
	if (isCallEnter && !mActiveStates.empty())
	{
		mActiveStates.top()->Enter(*mOwner);
	}

	// プールに移動
	mPoolStates.insert_or_assign(typeid(*state.get()), std::move(state));
}

template<class Owner>
inline void StateContext<Owner>::AddStateToPool(StateInst state)
{
	if (!state) return;

	// 状態の型をキーにインスタンスを追加する
	mPoolStates.try_emplace(typeid(*state.get()), std::move(state));
}
