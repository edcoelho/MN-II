#include "integration/GaussIntegral.hpp"

metII::GaussIntegral::GaussIntegral (double _lower_limit, double _upper_limit, bool _use_partitions, double _epsilon) : metII::Integral(_lower_limit, _upper_limit, _use_partitions, _epsilon) {}