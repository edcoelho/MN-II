#include "ivp/IVPMethod.hpp"
#include <cmath>

metII::IVPMethod::IVPMethod (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t) {

    this->F = _F;
    this->initial_state = _initial_state;
    this->delta = _delta;
    this->initial_t = _initial_t;

}

std::function<metII::Vector(metII::Vector, double)> metII::IVPMethod::get_F() const {

    return this->F;

}

const std::function<metII::Vector(metII::Vector, double)>& metII::IVPMethod::get_ref_F() const {

    return this->F;

}

void metII::IVPMethod::set_F(std::function<metII::Vector(metII::Vector, double)> _F) {

    this->F = _F;

}

metII::Vector metII::IVPMethod::get_initial_state() const {

    return this->initial_state;

}

void metII::IVPMethod::set_initial_state(metII::Vector _initial_state) {

    this->initial_state = _initial_state;

}

double metII::IVPMethod::get_delta() const {

    return this->delta;

}

void metII::IVPMethod::set_delta(double _delta) {

    this->delta = _delta;

}

double metII::IVPMethod::get_initial_t() const {

    return this->initial_t;

}

void metII::IVPMethod::set_initial_t(double _initial_t) {

    this->initial_t = _initial_t;

}