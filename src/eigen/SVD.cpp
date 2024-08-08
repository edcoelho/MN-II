#include "SVD.hpp" 
#include "QR.hpp"
#include <cmath>
#include <iostream> 

std::tuple<metII::Matrix, metII::Matrix, metII::Matrix> metII::SVD::decompose (metII::Matrix matrix) const {
    metII::Matrix matrix_cpy (matrix); 
    size_t m = matrix.m_size(), n = matrix.n_size(); 
    bool lines_larger_then_columns = (m >= n); 
    // Se as linhas são maiores ou iguais que as colunas, recebe A^t * A. Se as linhas são menores que as colunas, recebe A * A^t 
    metII::Matrix matrix_transposed = matrix.transpose(); 
    metII::Matrix symetric_A_bar = lines_larger_then_columns? (matrix_transposed * matrix) : (matrix * matrix_transposed);  
    int symetric_A_bar_size = symetric_A_bar.m_size(); 

    // 4) Achar os autovalores e autovetores de A_bar
    metII::QR qr_method;
    std::pair<metII::Matrix, metII::Vector> eigenvectors_eigenvalues = qr_method.compute(symetric_A_bar); 
    metII::Matrix qr_matrix = eigenvectors_eigenvalues.first; 
    metII::Vector eigenvalues = eigenvectors_eigenvalues.second; 

    // 5) Calcular os valores singulares sigma_i = sqrt(lambda_i) na matriz sigma
    size_t min_dimension = std::min(m, n); 
    metII::Matrix sigma_matrix (min_dimension, min_dimension); 
    for (size_t i = 0; i < eigenvalues.size(); i ++) {
        sigma_matrix(i,i) = std::sqrt(eigenvalues[i]); 
    }

    // 7) Montar as matrizes U e V
    size_t r  = symetric_A_bar_size; 
    metII::Matrix U (m,r); 
    metII::Matrix V (n,r);
    // 

    metII::Matrix *mat_aux = lines_larger_then_columns? &V: &U; 

    int qr_matrix_size = std::min(m, n); 
    for (int j = 0; j < qr_matrix_size; j++){ 
        double norm = 0; 
        for (int i = 0 ; i < qr_matrix_size; i++) {
            norm += qr_matrix(i,j) * qr_matrix(i,j);
        }
        //normalize
        for (int i = 0; i < qr_matrix_size; i++) {
            qr_matrix(i,j) = qr_matrix(i,j)/norm; 
            // caso m < n => U recebe esses valores 
            // caso m >= n => V recebe esses valores
            (*mat_aux)(i,j) = qr_matrix(i,j); 
        }
    }

    if (lines_larger_then_columns) { // caso m >= n faremos u_i = (1/sigma_i) * A * v_i
        // mat_aux is equivalent to V. 
        for (int j = 0; j <  qr_matrix_size; j++) {
            metII::Vector v_j (qr_matrix_size); 
            for (int i = 0; i < qr_matrix_size; i++) {
                v_j[i] = (*mat_aux)(i,j); 
            }
            metII::Vector A_times_vj = matrix * v_j; 

            double sigma;
            for (size_t i = 0; i < m; i++) {
                sigma = sigma_matrix(j,j);
                if (sigma == 0) {
                    sigma = 1; 
                }
                U(i,j) = (1/sigma)*A_times_vj[i]; 
            }
        }
    }
    else { // caso n>m faremos v_j = (1/sigma_j) * A^t * u_j
        // mat_aux is equivalent to U.
        for (int j = 0; j < qr_matrix_size; j++) {
            metII::Vector u_j (qr_matrix_size); 
            for (int i = 0; i < qr_matrix_size; i++) {
                u_j[i] = (*mat_aux) (i,j);
            }
            metII::Vector A_transpose_times_u_j = matrix_transposed * u_j; 

            double sigma; 
            for (size_t i = 0; i < n; i++) {
                sigma = sigma_matrix(j,j);
                if (sigma == 0) {
                    sigma = 1; 
                }
                V(i,j) = (1/sigma) * A_transpose_times_u_j[i];
            }
        }
    }  

    return std::tuple<metII::Matrix, metII::Matrix, metII::Matrix> (U, sigma_matrix, V); 
}