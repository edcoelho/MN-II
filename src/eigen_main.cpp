#include <iostream>
#include "eigen/Vector.hpp"
#include "eigen/Matrix.hpp"
#include "eigen/PowerIteration.hpp"
#include "eigen/InversePowerIteration.hpp"
#include "eigen/ShiftedPowerIteration.hpp"
#include "eigen/Householder.hpp"
#include "eigen/QR.hpp"
#include "eigen/SVD.hpp"
#include <cmath>

void print_vector (metII::Vector vector) {

    for (std::size_t index = 0; index < vector.size(); index++) {

        std::cout << vector[index] << std::endl;

    }

}

void print_matrix (metII::Matrix matrix) {

    for (std::size_t row = 0; row < matrix.m_size(); row++) {

        for (std::size_t column = 0; column < matrix.n_size(); column++) {

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
    metII::Matrix m1(3, 3);  // 3x3 matrix initialized with zeros (default)
    m1(0, 0) = 1.0;
    m1(1, 1) = 2.0;
    m1(2, 2) = 3.0;

    metII::Matrix m2(3, 3, 1.0, true);  // Diagonal 3x3 matrix with 1.0 on the diagonal

    // Testing operators +, -, *, ==
    metII::Matrix sum = m1 + m2;
    metII::Matrix diff = m1 - m2;
    metII::Matrix scalar_mul = m1 * 2.0;
    metII::Matrix matrix_mul = m1 * m2;

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
    metII::Matrix A(3, 3);

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

void test_LU() {
    metII::Matrix mat(std::vector<std::vector<double>>({{1,-1,1,2},{-2,1,1,1},{2,-1,2,3},{-4,1,0,2}})); 
    metII::Vector permutation_vector(std::pair<int, int>(0,mat.m_size() - 1));
    std::pair<metII::Matrix,metII::Matrix> LU_pair = mat.get_LU_pair(permutation_vector); 
    metII::Matrix L =  LU_pair.first; 
    metII::Matrix U = LU_pair.second; 
    std::cout << "L matrix\n"; 
    print_matrix(L); 
    std::cout << "\nU matrix\n"; 
    print_matrix(U) ;
    std::cout << "\npermutation vector\n"; 
    print_vector(permutation_vector);

    // Create permutation matrix P
    size_t n = mat.m_size(); 
    metII::Matrix P(n, n);
    for (size_t i = 0; i < n; i++) {
        P(i, permutation_vector[i]) = 1.0;
    }

    // Resulting matrix PA
    metII::Matrix PA = P * mat;
    std::cout << "Resulting matrix PA:\n"; 
    print_matrix(PA);

    // Reconstructed matrix from L and U
    metII::Matrix A_reconstructed = L * U;
    std::cout << "Reconstructed matrix L * U:\n"; 
    print_matrix(A_reconstructed);
}

void test_InversePower() {
    metII::Matrix A(std::vector<std::vector<double>>({{5,2,1},{2,3,1},{1,1,2}})); 
    metII::InversePowerIteration inverse_power_iteration;

    std::cout << "MatrixA\n"; print_matrix(A); std::cout << "\n";
    metII::Vector previous_eigenvector(A.m_size()); 
    for (int i = 1; i <= 25; i++) {
        double epsilon = pow(10, -i); 
        std::cout << "error = " << epsilon << "\n"; 
        std::pair<double, metII::Vector> eigen_pair = inverse_power_iteration.compute(A, epsilon);
        std::cout << "Eigenvalue of matrix A using inverse power iteraction: " << eigen_pair.first << "\n\n" ;
        // std::cout << "Eigenvector of matrix A using inverse power iteraction: " << std::endl;
        // print_vector(eigen_pair.second);
        if (i > 1) {
            std::cout << "\ndifference between 2 last eigenvectors\n"; 
            print_vector(eigen_pair.second - previous_eigenvector); //observe o erro antes da estabilizacao. 
        }
        previous_eigenvector = eigen_pair.second; 
        std::cout << std::endl;
    } 
    /*Observe que o numero de iterações está se estabilizando em 54*/ 
    return; 

    // metII::InversePowerIteration inverse_power_iteration; 
    double epsilon = 0.00000000001; 
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

void test_householder () {

    metII::Matrix matrix({

        {40.0, 8.0, 4.0, 2.0, 1.0},
        {8.0, 30.0, 12.0, 6.0, 2.0},
        {4.0, 12.0, 20.0, 1.0, 2.0},
        {2.0, 6.0, 1.0, 25.0, 4.0},
        {1.0, 2.0, 2.0, 4.0, 5.0}

    });

    std::pair<metII::Matrix, metII::Matrix> householder_pair = metII::Householder().compute(matrix);

    std::cout << "Matrix: " << std::endl;
    print_matrix(matrix);
    std::cout << std::endl;

    std::cout << "Householder matrix: " << std::endl;
    print_matrix(householder_pair.first);
    std::cout << std::endl;

    std::cout << "Tridiagonal matrix: " << std::endl;
    print_matrix(householder_pair.second);
    std::cout << std::endl;

}

void test_qr () {

    metII::Matrix matrix({

        {40.0, 8.0, 4.0, 2.0, 1.0},
        {8.0, 30.0, 12.0, 6.0, 2.0},
        {4.0, 12.0, 20.0, 1.0, 2.0},
        {2.0, 6.0, 1.0, 25.0, 4.0},
        {1.0, 2.0, 2.0, 4.0, 5.0}

    });

    std::pair<metII::Matrix, metII::Vector> qr_pair = metII::QR(1.0e-10).compute(matrix);

    std::cout << "Matrix: " << std::endl;
    print_matrix(matrix);
    std::cout << std::endl;

    std::cout << "Eigenvectors (Q) matrix: " << std::endl;
    print_matrix(qr_pair.first);
    std::cout << std::endl;

    std::cout << "Eigenvalues matrix: " << std::endl;
    print_vector(qr_pair.second);
    std::cout << std::endl;

}

void test_svd() {
    metII::Matrix matriz_4x5 ({
        {1, 0, 0, 0, 2},
        {0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0},
    }); //passou

    metII::Matrix matriz_4x2 ({
        {-2,1},
        {-1,0}, 
        {0,0},
        {1,2}
    });

    metII::Matrix matriz_3x2 ({
        {1,2}, 
        {1,1}, 
        {1,-1}
    }); //passou

    metII::Matrix matriz_2x3 ( {
        {0,1,3}, 
        {1,0,2}
    }); // passou, mas onde seria 0, retornou valores muito proximos de 0 

    metII::Matrix matriz_2x2 ({
        {2,1},
        {-1,2}
    });  //passou



    metII::SVD svd_method; 
    std::tuple <metII::Matrix, metII::Matrix, metII::Matrix> svd_decomposition = svd_method.decompose(matriz_4x2);  
    metII::Matrix U = std::get<0>(svd_decomposition); 
    metII::Matrix sigma = std::get<1>(svd_decomposition); 
    metII::Matrix V = std::get<2>(svd_decomposition); 

    print_matrix(U);std::cout << "\n"; 
    print_matrix(sigma);std::cout << "\n";
    print_matrix(V);std::cout << "\n";

    std::cout << "multiplicadas\n"; 
    print_matrix(U*sigma*V.transpose()); 
}

int main() {

    // test_vectors();

    // test_matrices();

    // test_matrices();

    // test_power_iterations();

    // test_LU(); 
    //test_InversePower(); 

    //test_householder();

    // test_qr();

    test_svd(); 

    return EXIT_SUCCESS;
}