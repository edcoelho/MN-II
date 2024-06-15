#ifndef MET_II_INTEGRAL_HPP_
#define MET_II_INTEGRAL_HPP_

#include <functional>

namespace metII {

    class Integral {

        private:
        
            double lower_limit, upper_limit;
            std::function<double(double)> func;
            bool use_partitions;
            double epsilon;

        protected:

            virtual double integrate_interval (double a, double b) = 0;

        public:

            Integral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, bool _use_partitions, double _epsilon = 1e-6);

            double get_lower_limit () const;
            void set_lower_limit (double _lower_limit);

            double get_upper_limit () const;
            void set_upper_limit (double _upper_limit);

            std::function<double(double)> get_func () const;
            void set_func (std::function<double(double)> _func);

            double get_epsilon () const;
            void set_epsilon (double _epsilon);

            bool get_use_partitions () const;
            virtual void set_use_partitions (bool _use_partitions);

            virtual double integrate_partitions(std::size_t num_of_partitions = 1);
            virtual double integrate ();

    };

}

#endif