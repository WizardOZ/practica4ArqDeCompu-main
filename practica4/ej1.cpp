#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size, numero;
    int buffer[size]; // Se define el buffer donde almacenamos los números de los procesos

    MPI_Init(&argc, &argv); // Iniciar
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rango de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total de procesos


    numero = rank + 1; // Asignamos a cada proceso un rango

    // MPI_Allgather para recolectar los números en todos los procesos
    MPI_Allgather(&numero, 1, MPI_INT, buffer, 1, MPI_INT, MPI_COMM_WORLD);

    printf("El proceso %d recibió los números: ", rank);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
