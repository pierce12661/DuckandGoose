#pragma once
/*!*************************************************************************
****
\file EnemyHealthDrop.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the state when enemy dies.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class EnemyHealthDrop : public IStates
	{
	public:
		EnemyHealthDrop(StateMachine* stateMachine);
		virtual ~EnemyHealthDrop() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		float mPickUpTimer;
		bool mPickUp;
		float mOriginalColMinX;
		float mOriginalColMaxX;
		float mOriginalColMinY;
		float mOriginalColMaxY;
	};
}