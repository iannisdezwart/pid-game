#ifndef COMPONENT_HPP
#define COMPONENT_HPP

using

namespace interconnect::raw_model
{

struct component_transform_header_t
{
	float position_x;
	float position_y;
	float orientation;
};

enum component_type_t
{
	transform
};

struct component_header_t
{
	component_type_t type;
};

}

#endif //COMPONENT_HPP
