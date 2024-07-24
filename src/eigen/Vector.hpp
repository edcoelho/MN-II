#ifndef MET_II_VECTOR_HPP_
#define MET_II_VECTOR_HPP_

#include <vector>
#include "eigen/Matrix.hpp"

namespace metII {

    // Column vector
    class Vector {

        private:

            std::vector<double> data;

        public:

            Vector (std::size_t size = 3, double value = 0.0);
            /*Creates a vector in the [range.first, range.second] inclusive integer interval*/
            Vector (std::pair<int, int> range); 

            double operator[] (std::size_t index) const;
            double& operator[] (std::size_t index);

            metII::Vector operator+ (metII::Vector const& other) const;
            metII::Vector operator- (metII::Vector const& other) const;
            metII::Vector operator* (double const& scalar) const;
            metII::Matrix operator* (metII::Matrix const& matrix) const;

            bool operator== (metII::Vector const& other) const;
            bool operator!= (metII::Vector const& other) const;

            std::size_t size () const;
            double dot (metII::Vector const& other) const;
            double norm () const;
            void normalize ();
            metII::Vector normalized () const;
            metII::Matrix transpose () const;

            void swap_elements(std::size_t pos1, std::size_t pos2); 
        
    };

}

#endif