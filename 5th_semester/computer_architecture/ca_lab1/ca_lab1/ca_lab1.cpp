#define _CRT_SECURE_NO_WARNINGS

#include "mpi.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int num_processes; 
int my_rank;
const int ROOT = 0;
const std::string PATH = "C:/Users/ksesha/source/repos/ca_lab1/Debug/input.txt";


void IterJacoby(double* procRows, double* b, double* X_old, double* X_new, int n, int start, int RowNum) {
	for (int i = start; i < RowNum + start; ++i) X_new[i] = b[i];
	for (int row = 0; row < RowNum; ++row) {
		for (int col = 0; col < n; ++col) {
			if ((row + start) != col) X_new[row + start] += procRows[row * n + col] * X_old[col];
		}
	}
}

double difference(double* X_old, double* X_new, int matrix_size) {
	double result = 0;
	for (int i = 0; i < matrix_size; ++i) result += abs(X_new[i] - X_old[i]);
	return result;
}

double* SolveSLAE(double* procRows, double* b, int* arrNum, int* arrInd, int matrix_size, double epsilon, int& iter_count) {
	double* X_all_old = new double[matrix_size];
	double* X_all_new = new double[matrix_size];
	int start = arrInd[my_rank];

	for (int i = 0; i < matrix_size; ++i) X_all_old[i] = b[i];

	double diff = 1.;
	int iters = 0;
	do {
		IterJacoby(procRows, b, X_all_old, X_all_new, matrix_size, arrInd[my_rank], arrNum[my_rank]);
		iters++;

		MPI_Allgatherv(X_all_new + arrInd[my_rank], arrNum[my_rank], MPI_DOUBLE, X_all_new, arrNum, arrInd, MPI_DOUBLE, MPI_COMM_WORLD);

		if (my_rank == ROOT) diff = difference(X_all_old, X_all_new, matrix_size);
		if (diff > epsilon) for (int i = 0; i < matrix_size; ++i) X_all_old[i] = X_all_new[i];
		MPI_Bcast(&diff, 1, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
	} while (diff > epsilon);

	delete[] X_all_old;
	iter_count = iters;
	return X_all_new;
}

int main(int argc, char* argv[]) {
	double epsilon = 0.000001; 
	double* A;
	double* b;
	size_t matrix_size = 0; 
	double* procRows;
	int iter_count;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	int* arrNum;
	int* arrInd;
	std::ifstream fin;
	fin.open(PATH);
	if (my_rank == ROOT) fin >> matrix_size;

	MPI_Bcast(&matrix_size, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

	int rows_left = matrix_size;

	arrNum = new int[num_processes];
	arrInd = new int[num_processes];

	int row_number = (matrix_size / num_processes);
	arrNum[0] = row_number;
	arrInd[0] = 0;

	for (int i = 1; i < num_processes; i++) {
		rows_left -= row_number;
		row_number = rows_left / (num_processes - i);
		arrNum[i] = row_number;
		arrInd[i] = arrInd[i - 1] + arrNum[i - 1];
	}

	b = new double[matrix_size];
	int size = arrNum[my_rank] * matrix_size;
	procRows = new double[size];
	size = matrix_size * matrix_size;
	A = new double[size];

	if (my_rank == ROOT) {
		for (int row = 0; row < matrix_size; row++) {
			for (int column = 0; column < matrix_size; column++) {
				fin >> A[row * matrix_size + column];
			}
			fin >> b[row];
		}
	}
	fin.close();

	if (my_rank == ROOT) {
		for (int row = 0; row < matrix_size; ++row) {
			double diag_elem = A[row * matrix_size + row];
			for (int column = 0; column < matrix_size; ++column) {
				A[row * matrix_size + column] /= diag_elem;
				A[row * matrix_size + column] = -A[row * matrix_size + column];
			}
			b[row] /= diag_elem;
		}
	}

	int* amount_sent; // the number of elements sent to the process
	int* first_sent; // the index of the first data element sent to the process

	MPI_Bcast(b, matrix_size, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
	MPI_Bcast(A, matrix_size * matrix_size, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

	first_sent = new int[num_processes];
	amount_sent = new int[num_processes];


	for (int i = 0; i < num_processes; i++) {
		amount_sent[i] = arrNum[i] * matrix_size;
		if (i > 0) first_sent[i] = first_sent[i - 1] + amount_sent[i - 1];
		else first_sent[i] = 0;
	}

	MPI_Scatterv(A, amount_sent, first_sent, MPI_DOUBLE, procRows, amount_sent[my_rank], MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

	delete[] amount_sent;
	delete[] first_sent;

	double startTime = MPI_Wtime();
	double* X = SolveSLAE(procRows, b, arrNum, arrInd, matrix_size, epsilon, iter_count);
	double finishTime = MPI_Wtime();

	if (my_rank == 0) {
		std::cout << "\nalgorithm took " << finishTime - startTime << " seconds with eps = " << epsilon << " on " << num_processes << " processes\n";
		std::ofstream fout("output.txt");
		fout << std::fixed << std::setprecision(10);
		for (size_t i = 0; i < matrix_size; i++) {
			fout << X[i] << "\n";
		}
	}
	MPI_Finalize();
	delete[] X;
	delete[] A;
	delete[] b;
	return 0;
}


//Results
//
//algorithm took 0.738572 seconds with eps = 1e-06 on 1 processes
//
//algorithm took 0.477039 seconds with eps = 1e-06 on 2 processes
//
//algorithm took 0.383698 seconds with eps = 1e-06 on 4 processes
//
//algorithm took 0.365017 seconds with eps = 1e-06 on 8 processes