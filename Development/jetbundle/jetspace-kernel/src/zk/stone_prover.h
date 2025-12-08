#pragma once

#include <vector>
#include <string>

struct ProverConfig {
    std::vector<int> fri_step_list = {4, 4, 2};
};

std::vector<uint8_t> prove_block(
    const std::string& program_json,
    const std::string& public_inputs_json,
    const std::string& private_inputs_json,
    const ProverConfig& config = ProverConfig{}
);
