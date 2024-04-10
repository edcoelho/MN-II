#include "GaussianFilter.hpp"

metII::GaussianFilter::GaussianFilter () : metII::Filter(kernel3{{{0.4, 0.6, 0.4}, {0.6, 1.0, 0.6}, {0.4, 0.6, 0.4}}}) {}