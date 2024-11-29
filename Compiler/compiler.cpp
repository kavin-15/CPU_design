#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*
 Instruction format notes
 R-type:
     instruction rd rs
        ex: add 2 3
            this instruction adds registers 2 and 3 together and saves the
            value in register 2.
    Special case: sll and srl
        ex: sll 2 6
            This instruction shifts the contents of register 2 by 6 bits. The
            shift ammount is saved in the rs operand slot
 I-Type:
    instruction rd imm
        ex: addi 2 23
            This instruction adds 23 to the value in register 2
    Special Case: sw, lw.
        ex: sw 2 3 8
            This instruction saves the content in register 2 to the memory
            address saved in register 3 plus the offset which is 8. This offset
            is saved in the last four bits of the instruction.
 j-type:
    instruction addr
        ex: j 3004
        addr can be up to 12 bits long
 */

unordered_map<string, string> op_code_mapping = {
    {"add", "0000"},
    {"sub", "0000"},
    {"or", "0000"},
    {"and", "0000"},
    {"not", "0000"},
    {"xor", "0000"},
    {"mult", "0000"},
    {"div", "0000"},
    {"slt", "0000"},
    {"sgt", "0000"},
    {"sll", "0000"},
    {"srl", "0000"},
    {"sw", "0001"},
    {"lw", "0010"},
    {"j", "0011"},
    {"jr", "0100"},
    {"jal", "0101"},
    {"lui", "0110"},
    {"addi", "0111"},
    {"bis", "1000"},
    {"bns", "1001"},
    {"lui", "1010"},
    {"li", "1011"}
};

unordered_map<string, string> func_code_mapping = {
        {"add", "0000"},
        {"sub", "0001"},
        {"or", "0010"},
        {"and", "0011"},
        {"not", "0100"},
        {"xor", "0101"},
        {"mult", "0110"},
        {"div", "0111"},
        {"slt", "1000"},
        {"sgt", "1001"},
        {"sll", "1010"},
        {"srl", "1011"}
    };

int main() {
    // Input file name
    std::string filename;
    std::cout << "Enter the name of the text file: ";
    std::cin >> filename;

    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }
    // 2D array to store words
    std::vector<std::vector<std::string>> instructions;
    std::vector<std::string> binary;


    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::vector<std::string> words;
        std::stringstream ss(line);
        std::string word;

        // Split the line into words
        while (ss >> word) {
            words.push_back(word);
        }

        // Add the words of this line to the 2D array
        instructions.push_back(words);
    }

    file.close();

    // Display the content of the 2D array
    std::cout << "\nBinary Representation:\n";
    for (const auto& row : instructions) {
        int iteration = 0;
        string instr = "0000000000000000";
        for (const auto& word : row) {
            if (iteration == 0) { // instruction name = op code
                string opcode = op_code_mapping[word];
                instr.replace(0, 4, opcode);
                if (opcode == "0000") {
                    instr.replace(12, 4, func_code_mapping[word]);
                }
            }
            else {
                int number = stoi(word);
                if (number < 0 || number > 15) {
                    throw std::out_of_range("Number must be between 0 and 15 for a 4-bit representation.");
                }

                std::bitset<4> b(number); // Convert to 4-bit binary
                instr.replace(iteration*4, 4, b.to_string());
            }
            //std::cout << word << " ";
            iteration++;
        }
        
        std::cout << instr << std::endl;
        binary.push_back(instr);
    }

    return 0;
}
