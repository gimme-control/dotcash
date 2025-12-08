#include "verifier.h"
#include <cstdio>
#include <fstream>
#include <sstream>

bool verify_stark(
    const std::vector<uint8_t>& proof,
    const std::string& public_inputs_json) {

    std::string proof_file = "/tmp/proof.bin";
    std::ofstream out(proof_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(proof.data()), proof.size());
    out.close();

    std::string cmd = "cpu_air_verifier --proof_file=" + proof_file +
                      " --public_input_json=" + public_inputs_json;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return false;
    }

    char buffer[128];
    bool success = false;
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::string output(buffer);
        success = output.find("SUCCESS") != std::string::npos;
    }

    pclose(pipe);
    return success;
}
