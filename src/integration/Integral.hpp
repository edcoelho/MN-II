#ifndef MET_II_INTEGRAL_HPP_
#define MET_II_INTEGRAL_HPP_

#include <functional>

namespace metII {

    class Integral {

        private:
        
            double lower_limit, upper_limit;

        protected:

            virtual double integrate_interval (std::function<double(double)> func, double a, double b) = 0;

        public:

            Integral (double _lower_limit, double _upper_limit);

            double get_lower_limit () const;
            void set_lower_limit (double ll);

            double get_upper_limit () const;
            void set_upper_limit (double ul);

            virtual double integrate_partitions(std::function<double(double)> func, std::size_t num_of_partitions = 1);
            virtual double integrate (std::function<double(double)> func, double epsilon = 0.000001);

    };

}

#endif