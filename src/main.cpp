#include <iostream>
#include <sstream>
#include <string>

#include "../include/memory.h"
#include "../include/allocator.h"
#include "../include/cache.h"

int main() {
    Memory mem;
    Allocator alloc;
    MultiLevelCache cache;   // CACHE OBJECT

    std::string line;

    std::cout << "Memory Management Simulator\n";

    while (true) {
        std::cout << "> ";
        getline(std::cin, line);

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "init") {
            std::string word;
            int size;
            ss >> word >> size;   // init memory 1024
            mem.init(size);

        } else if (command == "malloc") {
            int size;
            ss >> size;
            alloc.mallocMemory(mem, size);

        } else if (command == "free") {
            int id;
            ss >> id;
            alloc.freeBlock(mem, id);

        } else if (command == "dump") {
            mem.dump();

        } else if (command == "stats") {
            mem.printStats();

        } else if (command == "set") {
            std::string word, type;
            ss >> word >> type;

            if (type == "first_fit")
                alloc.setAllocator(FIRST_FIT);
            else if (type == "best_fit")
                alloc.setAllocator(BEST_FIT);
            else if (type == "worst_fit")
                alloc.setAllocator(WORST_FIT);

            std::cout << "Allocator changed\n";
        } else if (command == "cache") {
            std::string subcmd;
            ss >> subcmd;

            if (subcmd == "access") {
                int address;
                ss >> address;
                cache.access(address);
                std::cout << "Cache access for address " << address << "\n";

            } else if (subcmd == "stats") {
                cache.stats();

            } else {
                std::cout << "Unknown cache command\n";
            }
        } else if (command == "exit") {
            std::cout << "Exiting simulator...\n";
            break;

        } else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
