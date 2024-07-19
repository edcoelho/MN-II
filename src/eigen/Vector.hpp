#ifndef MET_II_VECTOR_HPP_
#define MET_II_VECTOR_HPP_

#include <vector>

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

            bool operator== (metII::Vector const& other) const;
            bool operator!= (metII::Vector const& other) const;

            std::size_t size () const;
            double dot (metII::Vector const& other) const;
            double norm () const;
            void normalize ();

            void swap_elements(int pos1, int pos2); 
        
    };

}

#endif