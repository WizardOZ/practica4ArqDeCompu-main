#include <iostream>
#include <mpi.h>
#include <iostream>

#define N 4 // Dimensión de la matriz NxN

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv); // Iniciar

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rango de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total de procesos

    if (size != N)
    {
        if (rank == 0)
        {
            cerr << "Este programa requiere exactamente " << N << " procesos." << endl;
        }
        MPI_Finalize();
        return 1;
    }

    int matrix[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    int send_data[N]; 
    int recv_data[N]; // En cada proceso se almacena una columna transpuesta

    // Distribuir las filas entre los procesos
    MPI_Alltoall(matrix, N, MPI_INT, send_data, N, MPI_INT, MPI_COMM_WORLD);

    // Transponemos los numeros
    for (int i = 0; i < N; i++)
    {
        recv_data[i] = send_data[i];
    }

    // Guardamos las columnas transpuestas
    int result[N][N];
    MPI_Allgather(recv_data, N, MPI_INT, result, N, MPI_INT, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "Matriz transpuesta:" << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << result[j][i] << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize(); //Cerrar
    return 0;
}
