#include"empch.h"
#include"BossAttack.h"
#include"BossIdle.h"
#include"BossChasing.h"

namespace EM
{
	BossAttack::BossAttack(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EYEBOSS_Attack");
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer = 2.f;
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[0].should_play = true;
		}
	}

	/*!*************************************************************************
	Update state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer -= Frametime;

		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Boss Laser")
			{

				p_ecs.GetComponent<Transform>(i).SetPos(p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().x - 0.64f,
					p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().y - 0.106f);
				p_ecs.GetComponent<Sprite>(i).SetLayerOrder(5);


				if (p_ecs.GetComponent<Sprite>(i).GetTexture() == "Boss_Laser_1" && p_ecs.GetComponent<Sprite>(i).GetIndex().x == p_ecs.GetComponent<Sprite>(i).GetMaxIndex()-1)
				{
					p_ecs.GetComponent<Sprite>(i).GetIndex().x = 0;
					p_ecs.GetComponent<Sprite>(i).SetTexture("Boss_Laser_2");

				}
				else if(p_ecs.GetComponent<Sprite>(i).GetTexture() == "Boss_Laser_2" && p_ecs.GetComponent<Sprite>(i).GetIndex().x == p_ecs.GetComponent<Sprite>(i).GetMaxIndex()-1)
				{
					p_ecs.GetComponent<Sprite>(i).GetIndex().x = 0;
					p_ecs.GetComponent<Sprite>(i).SetTexture("Boss_Laser_3");
				}

			}
		}

		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 1.f)
		{
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		}
		if(p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f)
		{
			stateMachine->ChangeState(new BossIdle(stateMachine));
		}

	}

	/*!*************************************************************************
	Exit state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnExit(StateMachine* stateMachine)
	{
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Boss Laser")
			{
				p_ecs.GetComponent<Sprite>(i).GetIndex().x = 0;
				p_ecs.GetComponent<Sprite>(i).SetLayerOrder(8);
				p_ecs.GetComponent<Sprite>(i).SetTexture("Boss_Laser_1");
			}
		}
		
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID())[1].is_Alive = false;
		delete this;
	}
}