#include "LaplaceFilter.hpp"

metII::LaplaceFilter::LaplaceFilter () : metII::Filter(kernel3{{{0.0, 1.0, 0.0}, {1.0, -4.0, 1.0}, {0.0, 1.0, 0.0}}}) {}