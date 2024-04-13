#include "GaussianFilter.hpp"

metII::GaussianFilter::GaussianFilter () : metII::Filter(metII::kernel3{{{1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}, {2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f}, {1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}}}) {}