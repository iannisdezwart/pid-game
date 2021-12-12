#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <bits/stdc++.h>

namespace interconnect::model
{

struct component_t
{

};

struct component_transform_t : public component_t
{
	float position_x;
	float position_y;
	float orientation;
};

}

#endif //COMPONENT_HPP
