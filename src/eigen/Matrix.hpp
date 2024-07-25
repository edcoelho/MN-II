#ifndef MET_II_SQUARE_MATRIX_HPP_
#define MET_II_SQUARE_MATRIX_HPP_

#include <vector>
#include "eigen/Vector.hpp"

namespace metII {

    class Vector;

    class Matrix {

        private:

            std::vector<std::vector<double>> data;
            std::size_t m, n;

            void swap_lines(int line1, int line2); 

        public:

            // m x n matrix
            Matrix (std::size_t m = 3, std::size_t n = 3, double value = 0.0, bool diagonal = false);
            Matrix (std::vector<std::vector<double>> matrix);

            double operator() (std::size_t row, std::size_t column) const;
            double& operator() (std::size_t row, std::size_t column);

            metII::Matrix operator+ (metII::Matrix const& other) const;
            metII::Matrix operator- (metII::Matrix const& other) const;
            metII::Matrix operator* (double const& scalar) const;
            metII::Matrix operator* (metII::Matrix const& other) const;
            metII::Vector operator* (metII::Vector const& vector) const;

            bool operator == (metII::Matrix const& other) const;
            bool operator != (metII::Matrix const& other) const;

            std::size_t m_size () const;
            std::size_t n_size () const;
            bool has_same_size (metII::Matrix const& other) const;
            metII::Matrix transpose () const;
            std::pair<metII::Matrix, metII::Matrix> get_LU_pair(metII::Vector &permutation_vector) const; 
        
    };

}

#endif