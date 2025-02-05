#include <iostream>
#include <vector>
#include <Eigen/Dense>
 

class Matrix {
private:
    int rows, cols;
    Eigen::MatrixXd data; // Changed to Eigen matrix    std::vector<std::vector<double>> data;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {}

    double& operator()(int row, int col) {
        return data(row,col);
    }

    // Helper function to find eigenvalues
    Eigen::VectorXd eigenvalues() const {
        Eigen::MatrixXd eigenMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                eigenMatrix(i, j) = data(i, j);
            }
        }
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
        return solver.eigenvalues();
    }

    std::pair<Matrix, Matrix> eigenvectors() const {
        Eigen::MatrixXd eigenMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                eigenMatrix(i, j) = data(i, j);
            }
        }
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
        return std::make_pair(solver.eigenvectors(), solver.eigenvectors().transpose().inverse());
    }


    // Function to create a matrix Delta with eigenvalues on the diagonal
    Matrix delta() const {
        Matrix deltaMatrix(rows, cols);
        Eigen::VectorXd eigenvals = eigenvalues();
        deltaMatrix.data = eigenvals.asDiagonal();
        return deltaMatrix;
    }

    // Function to create matrices T^-1 and T with left and right eigenvectors
    std::pair<Matrix, Matrix> eigenvectors() const {
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(data);
        Matrix invT(rows, cols);
        Matrix T(rows, cols);

        invT.data = solver.eigenvectors().inverse();
        T.data = solver.eigenvectors();

        return std::make_pair(invT, T);
    }



std::pair<Matrix, Matrix> eigenvectors() const {
        Eigen::MatrixXd eigenMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                eigenMatrix(i, j) = data[i][j];
            }
        }
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
        Eigen::MatrixXd leftEigenvectors = solver.eigenvectors().leftCols(rows);
        Eigen::MatrixXd rightEigenvectors = solver.eigenvectors().rightCols(rows);

        Matrix left(rows, rows);
        Matrix right(rows, rows);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < rows; ++j) {
                left(i, j) = leftEigenvectors(i, j);
                right(i, j) = rightEigenvectors(i, j);
            }
        }

        return {left, right};
    }

    Matrix delta() const {
        Eigen::VectorXd eigenvals = eigenvalues();
        Matrix deltaMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == j) {
                    deltaMatrix(i, j) = eigenvals(i);
                } else {
                    deltaMatrix(i, j) = 0.0;
                }
            }
        }
        return deltaMatrix;
    }
};

int 
main ()
{
Matrix A(3,3);
A(0,0) = 1; 
A(0,1) = 2; 
A(0,2) = 3; 
A(1,0) = 4; 
A(1,1) = 5; 
A(1,2) = 6; 
A(2,0) = 7; 
A(2,1) = 8; 
A(2,2) = 9; 


Eigen::VectorXd eigenvals = m.eigenvalues();
    Matrix deltaMatrix = m.delta();
    auto eigenvectorMatrices = m.eigenvectors();
    Matrix invT = eigenvectorMatrices.first;
    Matrix T = eigenvectorMatrices.second;

    std::cout << "Eigenvalues of the matrix m:\n" << eigenvals << std::endl;
    std::cout << "Delta matrix:\n" << deltaMatrix.data << std::endl;
    std::cout << "Inverse of T matrix:\n" << invT.data << std::endl;
    std::cout << "T matrix:\n" << T.data << std::endl;

    return 0;
}


//to find eigen values of mat m: 
   //Eigen::VectorXd eigenvals = m.eigenvalues();
    //std::cout << "Eigenvalues of the matrix m:\n" << eigenvals << std::endl;
// Example usage of eigenvalues()
    Eigen::VectorXd eigenvals = m.eigenvalues();
    std::cout << "Eigenvalues:\n" << eigenvals << std::endl;

    // Example usage of eigenvectors()
    auto eigvecs = m.eigenvectors();
    std::cout << "Left eigenvectors:\n" << eigvecs.first << std::endl;
    std::cout << "Right eigenvectors:\n" << eigvecs.second << std::endl;

    // Example usage of delta()
    Matrix deltaMatrix = m.delta();
    std::cout << "Delta matrix:\n" << deltaMatrix << std::endl;

    return 0;
}
