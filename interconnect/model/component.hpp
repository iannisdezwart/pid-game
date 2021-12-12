#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace interconnect::model
{

struct component_transform_t
{
	float position_x;
	float position_y;
	float orientation;
};

enum component_type_t
{
	transform
};

struct component_t
{
	component_type_t type;
	void *data;
};

}

#endif //COMPONENT_HPP
