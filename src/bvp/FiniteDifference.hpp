#ifndef METII_FINITE_DIFFERENCE_HPP
#define METII_FINITE_DIFFERENCE_HPP

#include "eigen/Matrix.hpp"
#include "eigen/Vector.hpp"
#include "custom_types.hpp"
#include <vector>

namespace metII {

    class FiniteDifference {

        private:

            metII::Matrix kernel;
            std::vector<metII::boundary> boundaries;
            std::size_t n;
            double f_value;

            metII::Vector solve_system_of_equations (metII::Matrix A, metII::Vector b) const;

        public:

            FiniteDifference (std::size_t _n, metII::Matrix _kernel, std::vector<metII::boundary> _boundaries, double _f_value = 0.0);

            std::size_t get_n () const;
            void set_n (std::size_t _n);

            metII::Matrix get_kernel () const;
            void set_kernel (metII::Matrix _kernel);

            std::vector<metII::boundary> get_boundaries () const;
            void set_boundaries (std::vector<metII::boundary> _boundaries);

            std::size_t get_f_value () const;
            void set_f_value (std::size_t _f_value);

            metII::Vector compute_nodes () const;

    };

}

#endif