#include <iostream>
#include "eigen/Vector.hpp"
#include "eigen/SquareMatrix.hpp"
#include "eigen/PowerIteration.hpp"
#include "eigen/InversePowerIteration.hpp"
#include "eigen/ShiftedPowerIteration.hpp"

void print_vector (metII::Vector vector) {

    for (std::size_t index = 0; index < vector.size(); index++) {

        std::cout << vector[index] << std::endl;

    }

}

void print_matrix (metII::SquareMatrix matrix) {

    for (std::size_t row = 0; row < matrix.size(); row++) {

        for (std::size_t column = 0; column < matrix.size(); column++) {

            std::cout << matrix(row, column) << " ";

        }

        std::cout << std::endl;

    }

}

void test_vectors () {

    metII::Vector v1(4);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;
    v1[3] = 4.0;

    metII::Vector v2(4);
    v2[0] = 0.5;
    v2[1] = 1.5;
    v2[2] = 2.5;
    v2[3] = 3.5;

    // operators +, -, *
    metII::Vector sum = v1 + v2;
    metII::Vector diff = v1 - v2;
    metII::Vector scalar_mul = v1 * 2.0;

    std::cout << "Vector v1: " << std::endl;
    print_vector(v1);
    std::cout << std::endl;

    std::cout << "Vector v2: " << std::endl;
    print_vector(v2);
    std::cout << std::endl;

    std::cout << "Vector v1 + v2: " << std::endl;
    print_vector(sum);
    std::cout << "(Expected: 1.5 3.5 5.5 7.5)" << std::endl << std::endl;

    std::cout << "Vector v1 - v2: " << std::endl;
    print_vector(diff);
    std::cout << "(Expected: 0.5 0.5 0.5 0.5)" << std::endl << std::endl;

    std::cout << "Vector v1 * 2.0: " << std::endl;
    print_vector(scalar_mul);
    std::cout << "(Expected: 2.0 4.0 6.0 8.0)" << std::endl << std::endl;

    // operators == , !=
    if (v1 == v1)
        std::cout << "Vector v1 is equal to itself." << std::endl << std::endl;
    if (v1 != v2)
        std::cout << "Vector v1 is not equal to v2." << std::endl << std::endl;

    // size
    std::cout << "Size of Vector v1 is " << v1.size() << std::endl << std::endl;
    std::cout << "Size of Vector v2 is " << v2.size() << std::endl << std::endl;

    // dot product
    double dot_product = v1.dot(v2);
    std::cout << "Dot product of v1 and v2: " << dot_product << " (Expected: 25.0)" << std::endl << std::endl;

    // norm
    double vector_norm = v1.norm();
    std::cout << "Norm of v1: " << vector_norm << " (Expected: 5.477)" << std::endl << std::endl;

    // normalize
    v1.normalize();
    vector_norm = v1.norm();
    std::cout << "Norm of normalized v1: " << vector_norm << " (Expected: 1.0)" << std::endl << std::endl;

}

void test_matrices() {
    // Testing constructor and operator ()
    metII::SquareMatrix m1(3);  // 3x3 matrix initialized with zeros (default)
    m1(0, 0) = 1.0;
    m1(1, 1) = 2.0;
    m1(2, 2) = 3.0;

    metII::SquareMatrix m2(3, 1.0, true);  // Diagonal 3x3 matrix with 1.0 on the diagonal

    // Testing operators +, -, *, ==
    metII::SquareMatrix sum = m1 + m2;
    metII::SquareMatrix diff = m1 - m2;
    metII::SquareMatrix scalar_mul = m1 * 2.0;
    metII::SquareMatrix matrix_mul = m1 * m2;

    std::cout << "Matrix m1:" << std::endl;
    print_matrix(m1);
    std::cout << "(Expected: 1.0 0.0 0.0, 0.0 2.0 0.0, 0.0 0.0 3.0)" << std::endl << std::endl;

    std::cout << "Matrix m2:" << std::endl;
    print_matrix(m2);
    std::cout << "(Expected: 1.0 0.0 0.0, 0.0 1.0 0.0, 0.0 0.0 1.0)" << std::endl << std::endl;

    std::cout << "Matrix m1 + m2:" << std::endl;
    print_matrix(sum);
    std::cout << "(Expected: 2.0 0.0 0.0, 0.0 3.0 0.0, 0.0 0.0 4.0)" << std::endl << std::endl;

    std::cout << "Matrix m1 - m2:" << std::endl;
    print_matrix(diff);
    std::cout << "(Expected: 0.0 0.0 0.0, 0.0 1.0 0.0, 0.0 0.0 2.0)" << std::endl << std::endl;

    std::cout << "Matrix m1 * 2.0:" << std::endl;
    print_matrix(scalar_mul);
    std::cout << "(Expected: 2.0 0.0 0.0, 0.0 4.0 0.0, 0.0 0.0 6.0)" << std::endl << std::endl;

    std::cout << "Matrix m1 * m2:" << std::endl;
    print_matrix(matrix_mul);
    std::cout << "(Expected: 1.0 0.0 0.0, 0.0 2.0 0.0, 0.0 0.0 3.0)" << std::endl << std::endl;

    // Testing comparison operators
    if (m1 == m1)
        std::cout << "Matrix m1 is equal to itself." << std::endl << std::endl;
    if (m1 != m2)
        std::cout << "Matrix m1 is not equal to m2." << std::endl << std::endl;

    // Testing matrix-vector multiplication
    metII::Vector v(3);
    v[0] = 9.2;
    v[1] = 13.25;
    v[2] = 7.98;
    metII::Vector matrix_vector_mul = m1 * v;

    std::cout << "Vector v: " << std::endl;
    print_vector(v);
    std::cout << std::endl;

    std::cout << "Matrix-vector multiplication m1 * v:" << std::endl;
    print_vector(matrix_vector_mul);
    std::cout << "(Expected: 9.2 26.5 23.94)" << std::endl << std::endl;
}

void test_power_iterations () {

    metII::PowerIteration p;
    std::pair<double, metII::Vector> results;
    metII::SquareMatrix A(3);

    A(0, 0) = 5.0;
    A(0, 1) = 2.0;
    A(0, 2) = 1.0;

    A(1, 0) = 2.0;
    A(1, 1) = 3.0;
    A(1, 2) = 1.0;

    A(2, 0) = 1.0;
    A(2, 1) = 1.0;
    A(2, 2) = 2.0;

    results = p.compute(A);

    std::cout << "Matrix A:" << std::endl;
    print_matrix(A);
    std::cout << std::endl << std::endl;
    
    std::cout << "Eigenvalue of matrix A using power iteraction: " << results.first << std::endl << std::endl;
    
    std::cout << "Eigenvector of matrix A using power iteraction: " << std::endl;
    print_vector(results.second);
    std::cout << std::endl;

    std::cout << "Matrix A times Eigenvector: " << std::endl;
    print_vector(A * results.second);
    std::cout << std::endl;

    std::cout << "Eigenvalue times Eigenvector: " << std::endl;
    print_vector(results.second * results.first);
    std::cout << std::endl;

}
//TODO: something wrong with the permutation
void test_LU() {
    metII::SquareMatrix mat(std::vector<std::vector<double>>({{1,-1,1,2},{-2,1,1,1},{2,-1,2,3},{-4,1,0,2}})); 
    metII::Vector permutation_vector(std::pair<int, int>(0,mat.size() - 1));
    std::pair<metII::SquareMatrix,metII::SquareMatrix> LU_pair = mat.get_LU_pair(permutation_vector); 
    metII::SquareMatrix L =  LU_pair.first; 
    metII::SquareMatrix U = LU_pair.second; 
    std::cout << "L matrix\n"; 
    print_matrix(L); 
    std::cout << "\nU matrix\n"; 
    print_matrix(U) ;
    std::cout << "\npermutation vector\n"; 
    print_vector(permutation_vector);

    // Create permutation matrix P
    size_t n = mat.size(); 
    metII::SquareMatrix P(n);
    for (size_t i = 0; i < n; i++) {
        P(i, permutation_vector[i]) = 1.0;
    }

    // Resulting matrix PA
    metII::SquareMatrix PA = P * mat;
    std::cout << "Resulting matrix PA:\n"; 
    print_matrix(PA);

    // Reconstructed matrix from L and U
    metII::SquareMatrix A_reconstructed = L * U;
    std::cout << "Reconstructed matrix L * U:\n"; 
    print_matrix(A_reconstructed);
}

void test_InversePower() {
    metII::SquareMatrix A(std::vector<std::vector<double>>({{5,2,1},{2,3,1},{1,1,2}})); 
    metII::InversePowerIteration inverse_power_iteration; 
    double epsilon = 0.000000000000001; 
    std::pair<double, metII::Vector> results = inverse_power_iteration.compute(A, epsilon); 
    double eigenvalue = results.first; 
    metII::Vector eigenvector = results.second; 

    std::cout << "Matrix A:" << std::endl;
    print_matrix(A);
    std::cout << std::endl << std::endl;
    eigenvector.normalize(); 
    std::cout << "Eigenvalue of matrix A using inverse power iteraction: " << eigenvalue << "\n\n" ;
    
    std::cout << "Eigenvector of matrix A using power iteraction: " << std::endl;
    print_vector(eigenvector);
    std::cout << std::endl;

    std::cout << "Matrix A times Eigenvector: " << std::endl;
    print_vector(A * eigenvector);
    std::cout << std::endl;

    std::cout << "Eigenvalue times Eigenvector: " << std::endl;
    print_vector(eigenvector * results.first);
    std::cout << std::endl;

}

int main() {

    // test_vectors();

    // test_matrices();

    // test_matrices();

    // test_power_iterations();

    // test_LU(); 
    test_InversePower(); 



    return EXIT_SUCCESS;
}