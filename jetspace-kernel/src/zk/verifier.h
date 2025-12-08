#pragma once

#include <vector>
#include <string>

bool verify_stark(
    const std::vector<uint8_t>& proof,
    const std::string& public_inputs_json
);

