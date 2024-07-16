#ifndef MET_II_SQUARE_MATRIX_HPP_
#define MET_II_SQUARE_MATRIX_HPP_

#include <vector>
#include "eigen/Vector.hpp"

namespace metII {

    class SquareMatrix {

        private:

            std::vector<std::vector<double>> data;

            void swap_lines(int line1, int line2); 

        public:
            
            SquareMatrix (std::size_t size = 3);
            SquareMatrix (std::size_t size, double value, bool diagonal = false);
            SquareMatrix (std::vector<std::vector<double>>); 

            double operator() (std::size_t row, std::size_t column) const;
            double& operator() (std::size_t row, std::size_t column);

            metII::SquareMatrix operator+ (metII::SquareMatrix const& other) const;
            metII::SquareMatrix operator- (metII::SquareMatrix const& other) const;
            metII::SquareMatrix operator* (double const& scalar) const;
            metII::SquareMatrix operator* (metII::SquareMatrix const& other) const;
            metII::Vector operator* (metII::Vector const& vector) const;

            bool operator == (metII::SquareMatrix const& other) const;
            bool operator != (metII::SquareMatrix const& other) const;

            std::pair<metII::SquareMatrix, metII::SquareMatrix> get_LU_pair() const; 

            std::size_t size () const;
        
    };

}

#endif