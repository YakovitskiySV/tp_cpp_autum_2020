#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdint.h>

void generate_file(std::ostream& file, int size) {
    file << size << std::endl;
    int64_t min_number = -2147483648;
    int64_t max_number = 2147483647;
    for (size_t i = 0; i < size; ++i) {
            file <<
            rand()
            % max_number + min_number << ' ';
    }
}

int main(int argc, char **argv) {
    std::ofstream file(argv[1]);
    int size = 0;
    std::stringstream(argv[2]) >> size;
    if (size < 1) {
        std::cerr << "wrong size parameter" << std::endl;
        return 1;
    }
    generate_file(file, size);
    return 0;
}
