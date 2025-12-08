#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <cstddef>

using DilithiumPk = std::array<uint8_t, 1952>;
using DilithiumSk = std::array<uint8_t, 4032>;
using DilithiumSig = std::vector<uint8_t>;

std::pair<DilithiumPk, DilithiumSk> dilithium_keygen();

DilithiumSig dilithium_sign(const DilithiumSk& sk, const std::array<uint8_t, 32>& msg);

bool dilithium_verify(const std::array<uint8_t, 32>& msg, const DilithiumSig& sig, const DilithiumPk& pk);

std::vector<DilithiumSig> aggregate_sigs(const std::vector<DilithiumSig>& sigs, uint8_t threshold_bitmap);

