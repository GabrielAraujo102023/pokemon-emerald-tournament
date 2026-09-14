#include <iostream>
#include <trainer_parties.h>

int main(int argc, char* argv[]) {
    // argc = argument count
    // argv = argument array
    
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}