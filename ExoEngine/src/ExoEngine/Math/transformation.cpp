#include "Transformation.h"

namespace EM
{
	Transform2::Transform2()
	{

	}

	Transform2::Transform2(vec2D Pos, vec2D Scale, float Rotation)
	{
		pos = Pos;
		scale = Scale;
		rotation = Rotation;
	}

	void Transform2::set_pos(vec2D Pos)
	{
		pos = Pos;
	}

	void Transform2::set_scale(vec2D Scale)
	{
		scale = Scale;
	}

	void Transform2::set_rotation(float Rotation)
	{
		rotation = Rotation;
	}

	void Transform2::set_collision_flag(bool flag)
	{
		collision_flag = flag;
	}

	vec2D Transform2::get_pos()
	{
		return pos;
	}

	float Transform2::get_rotation()
	{
		return rotation;
	}

	bool Transform2::get_collision()
	{
		return colision_flag;
	}

	void Transform2::add_pos(vec2D Pos)
	{
		pos.x += Pos.x;
		pos.y += Pos.y;
	}

	void Transform2::subtract_pos(vec2D Pos)
	{
		pos.x -= Pos.x;
		pos.y -= Pos.y;
	}

	void Transform2::multiply_scale(vec2D Scale)
	{
		scale.x += Scale.x;
		scale.y += Scale .y;
	}

}
