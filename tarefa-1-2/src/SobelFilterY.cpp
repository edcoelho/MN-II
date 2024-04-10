#include "SobelFilterY.hpp"

metII::SobelFilterY::SobelFilterY () : metII::Filter(kernel3{{{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}}}) {}