#include "GaussianFilter.hpp"

metII::GaussianFilter::GaussianFilter (metII::image image) : metII::Filter(image, kernel3{{{0.4, 0.6, 0.4}, {0.6, 1.0, 0.6}, {0.4, 0.6, 0.4}}}) {}