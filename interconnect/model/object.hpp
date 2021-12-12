#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <bits/stdc++.h>

namespace interconnect::model
{

struct object_t
{
	uint64_t uuid;
	uint16_t components_size;
	void *components;
};

}

#endif //OBJECT_HPP
