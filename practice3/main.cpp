#include <iostream>
#include <mpi.h>

auto main(int argc, char *argv[]) -> int {
    std::cout << argv[1] << std::endl;
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "SIZE: "
              << size
              << " "
              << "Rank = "
              << rank
              << std::endl;
    MPI_Finalize();

    return 0;
}
