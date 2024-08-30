#ifndef METII_FINITE_DIFFERENCE_PLUS_HPP
#define METII_FINITE_DIFFERENCE_PLUS_HPP

#include "eigen/Matrix.hpp"
#include "eigen/Vector.hpp"
#include "utils.hpp"
#include <vector>

namespace metII {

    class FiniteDifferencePlus {

        private:

            std::vector<metII::boundary> boundaries;
            std::size_t n;
            double f_value;

            metII::Vector solve_system_of_equations (metII::Matrix A, metII::Vector b) const;

        public:

            FiniteDifferencePlus (std::size_t _n, std::vector<metII::boundary> _boundaries, double _f_value = 0.0);

            std::size_t get_n () const;
            void set_n (std::size_t _n);

            std::vector<metII::boundary> get_boundaries () const;
            void set_boundaries (std::vector<metII::boundary> _boundaries);

            double get_f_value () const;
            void set_f_value (double _f_value);

            metII::Vector compute_nodes (BVP_kernel_plus kernel) const;

    };

}

#endif