#ifndef MET_II_DERIVATIVE_HPP_
#define MET_II_DERIVATIVE_HPP_

#include <functional>
#include <limits>

namespace metII {

    class Derivative {

        private:

            std::function<double(double)> f;
            std::size_t derivative_order, error_order;
            double epsilon, h_divider, initial_h;
            bool check_for_invalid_iterations;

            virtual double first_derivative (const double x, const double h) const = 0;
            virtual double second_derivative (const double x, const double h) const = 0;
            virtual double third_derivative (const double x, const double h) const = 0;
            virtual double fourth_derivative (const double x, const double h) const = 0;

        public:

            Derivative (std::function<double(double)> _f, std::size_t _derivative_order = 1, std::size_t _error_order = 1, double _epsilon = 1.0e-6, double _h_divider = 2.0, double _initial_h = 0.1, bool _check_for_invalid_iterations = false);

            std::function<double(double)> get_f () const;
            void set_f (std::function<double(double)> _f);

            std::size_t get_derivative_order () const;
            void set_derivative_order (std::size_t _derivative_order);

            std::size_t get_error_order () const;
            void set_error_order (std::size_t _error_order);

            double get_epsilon () const;
            void set_epsilon (double _epsilon);

            double get_h_divider () const;
            void set_h_divider (double _h_divider);

            double get_initial_h () const;
            void set_initial_h (double _initial_h);

            bool get_check_for_invalid_iterations () const;
            void set_check_for_invalid_iterations (bool _check_for_invalid_iterations);

            virtual double derive (const double x, const double h) const final;
            virtual double iterate (const double x, const std::size_t max_of_invalid_iterations = 100) const final;

    };

}

#endif