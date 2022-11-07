/*!*************************************************************************
****
\file Transform.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Transform component used to set the pos, scale and rot of the
entity and used for various systems such as graphics to render images

****************************************************************************
***/

#pragma once
#include "ExoEngine/Math/Vmath.h"
#include "IComponent.h"

namespace EM
{
	class Transform : public IComponent
	{
	public:
		Transform();
		~Transform() = default;
		virtual bool Deserialize(const rapidjson::Value & obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>*writer) const;

		vec2D& GetPos() { return mPosition; }
		//const vec2D& GetPos() { return mPosition; } const
		vec2D& GetScale() { return mScale; }
		//const vec2D& GetScale() { return mScale; } const
		float& GetRot() { return mRot; }
		//const float& GetRotConst() { return mRot; } const

		void SetPos(vec2D Pos) { mPosition = Pos; }
		void SetPos(float posX, float posY) { mPosition = vec2D(posX, posY); }
		void SetScale(vec2D Scale) { mScale = Scale; }
		void SetScale(float X, float Y) { mScale = vec2D(X, Y); }
		void SetRot(float value) { mRot = value; }


	private:
		vec2D mPosition;
		vec2D mScale;
		float mRot;
	};
}