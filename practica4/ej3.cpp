#include <iostream>
#include <cmath>
#include <mpi.h>
#include <vector>
#include <iostream>
#include <algorithm> // Para reverse

void bi_to_dec(const string &binary, const string &original_binary)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rango de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total de procesos

    int n = binary.size();
    if (size != n)
    {
        if (rank == 0)
        {
            cerr << "El número de procesos debe ser igual al número de bits del binario (" << n << ")." << endl;
        }
        MPI_Finalize();
        return;
    }

    // Cada proceso obtiene su bit correspondiente
    int bit = binary[rank] - '0'; // Convertir carácter a entero

    // Cada proceso calcula su contribución al valor decimal
    int contribution = bit * pow(2, rank);

    // Recopilar contribuciones de todos los procesos con MPI_Allgather
    vector<int> contributions(size);
    MPI_Allgather(&contribution, 1, MPI_INT, contributions.data(), 1, MPI_INT, MPI_COMM_WORLD);

    
    int total = 0; //Sumador total
    for (int val : contributions)
    {
        total += val;
    }

    // Mostrar el resultado en cada proceso
    cout << "Proceso " << rank << ": El número binario " << original_binary << " es " << total << " en decimal." << endl;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv); // Iniciar

    // Números binarios 
    const string binaries[] = {"1010", "1100", "0001", "1111"};

    for (const auto &binary : binaries)
    {
        // Invertimos la cadena
        string reversed_binary = binary;
        reverse(reversed_binary.begin(), reversed_binary.end());

        bi_to_dec(reversed_binary, binary);

        MPI_Barrier(MPI_COMM_WORLD); // Sincronizamos antes de pasar al siguiente número
    }

    MPI_Finalize(); //Cerrar
    return 0;
}
