#include "FiniteDifference.hpp"

metII::Vector metII::FiniteDifference::solve_system_of_equations (metII::Matrix A, metII::Vector b) {
    metII::Vector permutation_vector(std::pair<int, int>(0, A.m_size() - 1)); 
    std::pair<metII::Matrix, metII::Matrix> LU_pair = A.get_LU_pair(permutation_vector);  
    metII::Matrix L = LU_pair.first; 
    metII::Matrix U = LU_pair.second; 
    metII::Vector x = metII::LU_solver(L, U, permutation_vector, b); 
    return x; 
}