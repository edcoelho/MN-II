#include "LaplaceFilter.hpp"

metII::LaplaceFilter::LaplaceFilter (metII::image image) : metII::Filter(image, kernel3{{{0.0, 1.0, 0.0}, {1.0, -4.0, 1.0}, {0.0, 1.0, 0.0}}}) {}