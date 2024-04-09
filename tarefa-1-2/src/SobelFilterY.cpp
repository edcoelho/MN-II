#include "SobelFilterY.hpp"

metII::SobelFilterY::SobelFilterY (metII::image image) : metII::Filter(image, kernel3{{{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}}}) {}