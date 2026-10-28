#include "PlayerModelAnimator.h"
#include "Rendering/ModelRenderer.h"
#include "System/InputManager.h"
#include "System/PlayerDataManager.h"
#include "World/Character/Player.h"

namespace
{
	constexpr Vector3 kSpinRotate{ 0.0f, Math::ToRadian(20.0f), 0.0f };

	constexpr float kStickWallAnimTime = 20.0f;
}

PlayerModelAnimator::PlayerModelAnimator(Player* player, ModelRenderer* renderer, float fps) :
	ModelAnimator(renderer, fps),
	mPlayer(player),
	mCurrentAnimation(PlayerAnimation::Idle)
{
}

void PlayerModelAnimator::Update()
{
	PlayerAnimation nextAnim = PlayerAnimation::Idle;

	if (mPlayer->IsSpinning())
	{
		nextAnim = PlayerAnimation::Spin;
		GetModelRenderer()->Rotate(kSpinRotate);
	}
	else
	{
		GetModelRenderer()->SetRotation(Vector3::Zero);

		if (mPlayer->OnGround())
		{
			if (InputManager::GetInstance().IsPressed(Input::Action::Jump))
			{
				nextAnim = PlayerAnimation::JumpIn;
			}
			else
			if (InputManager::GetInstance().GetAsVector3(Input::Action::Move) != Vector3::Zero)
			{
				if (InputManager::GetInstance().IsDown(Input::Action::Dash))
				{
					nextAnim = PlayerAnimation::Run;
				}
				else
				{
					nextAnim = PlayerAnimation::Walk;
				}
			}
			else
			if (mCurrentAnimation == PlayerAnimation::JumpLoop
			|| (mCurrentAnimation == PlayerAnimation::Land && IsPlaying()))	// 強制再生だとRunやJumpInが再生できなくなるため別途分岐
			{
				nextAnim = PlayerAnimation::Land;
			}
		}
		else
		{
			if (mPlayer->OnWall())
			{
				nextAnim = PlayerAnimation::StickWall;

				SetTime(kStickWallAnimTime);

				// 壁を向かせる
				Vector3 worldRot = mPlayer->GetTransform()->CalculateWorldRotation();
				Vector3 wallNormalRot = Vector3(0.0f, std::atan2(mPlayer->GetLastCollideNormal().x, mPlayer->GetLastCollideNormal().z), 0.0f);
				GetModelRenderer()->SetRotation(wallNormalRot - worldRot);
			}
			else
			{
				nextAnim = PlayerAnimation::JumpLoop;
			}
		}
	}

	// アニメーション切り替え
	if (mCurrentAnimation != nextAnim)
	{
		if (Play(PlayerDataManager::GetInstance().GetAnimationParam(nextAnim)))
		{
			mCurrentAnimation = nextAnim;
		}
	}

	ModelAnimator::Update();
}
