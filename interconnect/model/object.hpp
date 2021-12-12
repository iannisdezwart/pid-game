#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <bits/stdc++.h>
#include <model/component.hpp>

namespace interconnect::model
{

struct object_t
{
	uint64_t uuid;
	std::vector<component_t> components;
};

}

#endif //OBJECT_HPP
