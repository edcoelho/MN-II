#include "image_processing/LaplaceFilter.hpp"

metII::LaplaceFilter::LaplaceFilter () : metII::Filter(metII::kernel3{{{1.0, 1.0, 1.0}, {1.0, -8.0, 1.0}, {1.0, 1.0, 1.0}}}) {}