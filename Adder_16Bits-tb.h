#pragma once

#ifndef ADDER_16BITS_TB_H
#define ADDER_16BITS_TB_H

#include <ap_int.h>

void CLA16(ap_uint<16> a, ap_uint<16> b, bool cin, ap_uint<16>& sum, bool& cout);
void run_test(const ap_uint<16>& a, const ap_uint<16>& b, bool cin);

#endif // ADDER_16BITS_TB_H
