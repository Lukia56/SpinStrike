#pragma once

#include <cassert>
#include <memory>
#include "IState.h"

/// <summary>
/// ó‘Ô‚ğ•Û‚µAó‘ÔØ‚è‘Ö‚¦‚ğs‚¤
/// </summary>
template <class OwnerType>
class StateContext
{
public:

	StateContext(OwnerType* owner, std::unique_ptr<IState<OwnerType>> initState);
	~StateContext() = default;

	void Update();

private:

	OwnerType* mOwner;

	std::unique_ptr<IState<OwnerType>> mCurrentState;
};

template<class OwnerType>
inline StateContext<OwnerType>::StateContext(OwnerType* owner, std::unique_ptr<IState<OwnerType>> initState) :
	mOwner(owner),
	mCurrentState(std::move(initState))
{
	if (!mOwner)
	{
		assert(false && "StateContext // Š—LÒ‚ªnullptr‚Å‚·");
		return;
	}
	if (!mCurrentState)
	{
		assert(false && "StateContext // ‰Šúó‘Ô‚ªnullptr‚Å‚·");
		return;
	}
	mCurrentState->Enter(*owner);
}

template<class OwnerType>
inline void StateContext<OwnerType>::Update()
{
	if (!mOwner || !mCurrentState) return;

	auto nextState = mCurrentState->Update(*mOwner);

	if (nextState)
	{
		// ó‘Ô‚ğØ‚è‘Ö‚¦‚é
		mCurrentState->Exit(*mOwner);
		nextState->Enter(*mOwner);

		mCurrentState = std::move(nextState);
	}
}
