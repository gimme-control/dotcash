#include "stone_prover.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <memory>

std::vector<uint8_t> prove_block(
    const std::string& program_json,
    const std::string& public_inputs_json,
    const std::string& private_inputs_json,
    const ProverConfig& config) {
    
    std::string cmd = "cpu_air_prover --program_json=" + program_json +
                      " --public_input_json=" + public_inputs_json +
                      " --private_input_json=" + private_inputs_json;
    
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return {};
    }
    
    std::vector<uint8_t> proof;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        size_t len = strlen(buffer);
        proof.insert(proof.end(), buffer, buffer + len);
    }
    
    pclose(pipe);
    return proof;
}

