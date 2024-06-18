#ifndef MET_II_EXPONENTIAL_INTEGRAL_HPP_
#define MET_II_EXPONENTIAL_INTEGRAL_HPP_

#include "integration/Integral.hpp"
#include "custom_types.hpp"

namespace metII {

    class ExponentialIntegral : public Integral {

        private:

            double internal_epsilon;

        protected:

            Integral* internal_quadrature;

            virtual double x (double s) = 0;
            virtual double dx_ds (double s) = 0;
            virtual double integrate_interval (double a, double b) override;

        public:

            ExponentialIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, metII::quadrature_type _internal_quadrature_type, std::size_t _internal_quadrature_num_of_points = 2, bool _use_partitions = true, double _epsilon = 1e-6, double _internal_epsilon = 1e-6);

            ~ExponentialIntegral();

            double get_internal_epsilon () const;
            void set_internal_epsilon (double _internal_epsilon);

            void set_func (std::function<double(double)> _func) override;

            // Since this is one of exponential quadratures, this method works as an alias for metII::ExponentialIntegral::integrate.
            double integrate_partitions(std::size_t num_of_partitions = 1) override;

            virtual double integrate () override;

    };

}

#endif