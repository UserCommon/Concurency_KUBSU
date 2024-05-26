#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>
#include <fstream>


// Function which finding max value
auto find_max(const std::string& filename) -> int {
    int max_val = 0;
    std::ifstream file(filename);
    int value;
    while (file >> value) {
        if (file.fail()) {
            std::cerr << "Error reading value from file " << filename << std::endl;
            return -1;
        }
        max_val = std::max(max_val, value);
    }

    return max_val;
}

auto main(int argc, char *argv[]) -> int {
    std::vector<std::string> files = {"f1.txt", "f2.txt", "f3.txt"};
    MPI_Init(&argc, &argv);
    constexpr int elements_per_proc = 1;
    std::vector<int> send_data;
    std::ofstream otp("otp.txt", std::ios::app);
    int world_rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int recv_buff;

    if (world_rank == 0) {
        send_data = {0, 1, 2};
    }

    MPI_Scatter(send_data.data(), elements_per_proc, MPI_INT,
                &recv_buff, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    int max_val = find_max(files[recv_buff]);

    otp << "|Process: "
        << world_rank
        << " |Received: "
        << files[recv_buff]
        << " |Max Value: "
        << max_val
        << "|"
        << std::endl;

    MPI_Finalize();
    return 0;
}
