/*!*************************************************************************
****
\file OnChargeAttack_1.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	1st Charge attacking state for player

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "OnChargeAttack_1.h"
#include "OnIdle.h"
#include "OnBlock.h"
#include "OnDamaged.h"
#include "OnAttack_1.h"
#include "ExoEngine/Timer/Time.h"

namespace EM
{
	OnChargeAttack_1::OnChargeAttack_1(StateMachine* stateMachine) : mTimer{ 0.0f }, mDuration{ 1.0f }, mChargeIndex{ 0 } { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* OnChargeAttack_1::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine);
		UNREFERENCED_PARAMETER(key);
		return nullptr;
	}
	/*!*************************************************************************
		Enter state for Player Attack 1
	****************************************************************************/
	void OnChargeAttack_1::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mChargeTimer = 0.6f;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer = 0.3f;
		}
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[0].should_play = true;
		}
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		mTimer = 0.1f;
	}

	/*!*************************************************************************
		Update state for Player Attack 1
	****************************************************************************/
	void OnChargeAttack_1::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown -= Frametime;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown -= Frametime;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown -= Frametime;
		}
		if (p_Input->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && !p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsChargeAttack)
		{
			mTimer <= 0.0f ? 0.0f : mTimer -= Frametime;
			if (mTimer <= 0.0f)
			{
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("CA1");
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mChargeTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mChargeTimer -= Frametime;
				if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mChargeTimer <= 0.0f)
				{
					p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;
				}
			}
			
		}
		else if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mChargeTimer <= 0.0f)
		{
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHitStopTimer <= 0.0f)
			{
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsChargeAttack = true;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer -= Frametime;
				auto& transform = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
				auto& rigidbody = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
				vec2D dir = rigidbody.GetDir();
				dir = dir * 20.0f;
				rigidbody.SetVel(p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mPhys.accelent(rigidbody.GetVel(), dir, Frametime));
				vec2D nextPos = (transform.GetPos() + rigidbody.GetVel());
				rigidbody.SetNextPos(nextPos);
				if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.15f)
				{
					p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
				}
				if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
					if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged)
					{
						stateMachine->ChangeState(new OnDamaged(stateMachine));
					}
					if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.0f)
					{
						p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
						stateMachine->ChangeState(new OnIdle(stateMachine));
					}
				}
			}
			else
			{
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHitStopTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHitStopTimer -= Frametime;
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;
			}
		}
		else if (p_Input->MouseIsReleased(GLFW_MOUSE_BUTTON_LEFT) && !p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsChargeAttack)
		{
			stateMachine->ChangeState(new OnAttack_1(stateMachine));
		}

		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new OnDamaged(stateMachine));
		}
	}
	/*!*************************************************************************
		Exit state for Player Attack 1
	****************************************************************************/
	void OnChargeAttack_1::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsChargeAttack = false;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHitStopTimer = 0.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}