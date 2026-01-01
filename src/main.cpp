#include <iostream>
#include <sstream>
#include <string>

#include "../include/memory.h"
#include "../include/allocator.h"
#include "../include/cache.h"


int main() {
    Memory mem;
    Allocator alloc;


    TwoLevelCache* cache = nullptr;

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
            ss >> word >> size;  
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

            if (subcmd == "init") {
                int l1Size, l2Size;
                ss >> l1Size >> l2Size;

                if (cache) {
                    delete cache;
                }

                cache = new TwoLevelCache(l1Size, l2Size);
                std::cout << "Cache initialized (L1=" << l1Size
                        << ", L2=" << l2Size << ")\n";

            } else if (subcmd == "access") {
                if (!cache) {
                    std::cout << "Cache not initialized\n";
                    continue;
                }

                int address;
                ss >> address;

                int value = cache->get(address);
                if (value == -1)
                    std::cout << "Cache MISS for address " << address << "\n";
                else
                    std::cout << "Cache HIT, value = " << value << "\n";

            } else if (subcmd == "put") {
                if (!cache) {
                    std::cout << "Cache not initialized\n";
                    continue;
                }

                int address, value;
                ss >> address >> value;

                cache->put(address, value);
                std::cout << "Inserted address " << address
                        << " with value " << value << "\n";

            } else if (subcmd == "display") {
                if (!cache) {
                    std::cout << "Cache not initialized\n";
                    continue;
                }
                cache->display();
            }

            else if (subcmd == "stats") {
                if (!cache) {
                    std::cout << "Cache not initialized\n";
                    continue;
                }
                cache->stats();
            } else {
                std::cout << "Unknown cache command\n";
            }
            
        }else if (command == "exit") {
            std::cout << "Exiting simulator...\n";
            break;

        } else {
            std::cout << "Unknown command\n";
        }
    }
    if(cache){
        delete cache;
    }
    return 0;
}
