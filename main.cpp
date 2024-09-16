#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // for formatting

struct MemoryBlock {
    unsigned int base;  // Base register
    unsigned int limit; // Limit register
};

void readMemorySlots(const std::string& filename, std::vector<MemoryBlock>& memoryBlocks) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        exit(1);
    }

    unsigned int base, limit;
    // Read values until the end of the file
    while (infile >> std::hex >> base >> limit) {
        // Validate base and limit range
        if (base > 0xFFFF || base + limit > 0xFFFF) {
            std::cerr << "Error: Invalid base or limit value." << std::endl;
            exit(1);
        }
        memoryBlocks.push_back({base, limit});
    }

    infile.close();
}


void displayMemorySlots(const std::vector<MemoryBlock>& memoryBlocks) {
    std::cout << "Base Register  Limit Register" << std::endl;
    for (const auto& block : memoryBlocks) {
        std::cout << "0x" << std::setw(4) << std::setfill('0') << std::hex << block.base << "        "
                  << "0x" << std::setw(4) << std::setfill('0') << std::hex << block.limit << std::endl;
    }
}

void generateMemoryMap(const std::vector<MemoryBlock>& memoryBlocks) {
    unsigned int totalMemory = 0xFFFF;
    unsigned int currentAddress = 0x0000;

    std::cout << "\nMemory Map:\n";
    for (const auto& block : memoryBlocks) {
        // Unused memory
        if (currentAddress < block.base) {
            std::cout << "Free: 0x" << std::setw(4) << std::setfill('0') << std::hex << currentAddress << " to 0x"
                      << std::setw(4) << std::setfill('0') << std::hex << (block.base - 1) << std::endl;
        }

        // Used memory
        std::cout << "Used: 0x" << std::setw(4) << std::setfill('0') << std::hex << block.base << " to 0x"
                  << std::setw(4) << std::setfill('0') << std::hex << (block.base + block.limit - 1) << std::endl;

        currentAddress = block.base + block.limit;
    }

    // Check for memory after the last block
    if (currentAddress < totalMemory) {
        std::cout << "Free: 0x" << std::setw(4) << std::setfill('0') << std::hex << currentAddress << " to 0xFFFF"
                  << std::endl;
    }
}

int main() {
    std::cout << "This program creates the memory map table in regards to used and unused areas in the system memory after receiving the base and limit register contents." << std::endl;
    std::cout << std::endl;
    std::cout << "These base and limit values are being read from the file containing user input." << std::endl;
    std::cout << std::endl;
    std::string filename = "24F_COP4610_Project1_InputFile.txt";
    std::vector<MemoryBlock> memoryBlocks;

    // Read and display the memory slots
    std::cout << "The table of unused memory area\n" << "-------------------------------\n";
    readMemorySlots(filename, memoryBlocks);
    displayMemorySlots(memoryBlocks);

    // Generate and display the memory map
    generateMemoryMap(memoryBlocks);

    return 0;
}
