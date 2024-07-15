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
        
    };

}

#endif