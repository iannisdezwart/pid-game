#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <bits/stdc++.h>

namespace interconnect::raw_model
{

struct object_header_t
{
	uint64_t uuid;
	uint16_t components_size;
};

}

#endif //OBJECT_HPP
