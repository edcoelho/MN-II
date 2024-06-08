#ifndef MET_II_SPECIAL_GAUSS_INTEGRAL_HPP_
#define MET_II_SPECIAL_GAUSS_INTEGRAL_HPP_

#include "integration/GaussIntegral.hpp"

namespace metII {

    class SpecialGaussIntegral : public GaussIntegral {

        protected:

            double integrate_interval (std::function<double(double)> func, double a, double b) override;

        public:

            SpecialGaussIntegral ();

            virtual ~SpecialGaussIntegral () = 0;

            // Since this is one of Gauss' special quadratures, this method does nothing, because special quadratures cannot use partitioning.
            void set_use_partitions(bool _use_partitions) override;

            // Since this is one of Gauss' special quadratures, this method integrate using no partitions.
            double integrate_partitions(std::function<double(double)> func, std::size_t num_of_partitions = 1) override;


    };

}

#endif