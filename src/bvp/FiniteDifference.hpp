#ifndef METII_FINITE_DIFFERENCE_HPP
#define METII_FINITE_DIFFERENCE_HPP

#include "eigen/Matrix.hpp"
#include "eigen/Vector.hpp"
#include <vector>

namespace metII {

    class FiniteDifference {

        private:

            metII::Matrix kernel;
            std::vector<double> boundaries;
            std::size_t n;

            metII::Vector solve_system_of_equations (metII::Matrix A, metII::Vector b);

        public:

            FiniteDifference (metII::Matrix _kernel, std::vector<double> _boundaries, std::size_t _n);

            metII::Matrix get_kernel () const;
            void set_kernel (metII::Matrix _kernel);

            std::vector<double> get_boundaries () const;
            void set_boundaries (std::vector<double> _boundaries);

            std::size_t get_n () const;
            void set_n (std::size_t _n);

            std::vector<double> compute_nodes () const;

    };

}

#endif