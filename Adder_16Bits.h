#pragma once

#ifndef ADDER_16BITS_H
#define ADDER_16BITS_H

#include <ap_int.h>

/**
 * @brief Calculate the 16-bit sum and carry-out.
 * Serves as the top-level function for the HLS synthesis, clean interface for the adder.
 *
 * @param a     First 16-bit operand.
 * @param b     Second 16-bit operand.
 * @param cin   Carry-in value.
 * @param sum   Reference to store the 16-bit sum.
 * @param cout  Reference to store the carry-out flag.
 */
void CLA16(ap_uint<16> a, ap_uint<16> b, bool cin, ap_uint<16>& sum, bool& cout);

#endif // ADDER_16BITS_H
