#include "Adder_16Bits.h"

#include <ap_int.h>
#include <utility>


/**
 * @brief Perform a 4-bit carry look-ahead addition.
 * Sum of two 4-bit numbers using carry look-ahead logic, which is a fast addition method that reduces
 * the propagation delay by calculating the carry signals in advance,
 * based on the generate (g) and propagate (p) signals of the addends.
 *
 * @param a First 4-bit operand.
 * @param b Second 4-bit operand.
 * @param cin Input carry (carry-in).
 * @return A pair where the first element is the 4-bit sum and the second is the carry out (bool).
 */
std::pair<ap_uint<4>, bool> CLA4(ap_uint<4> a, ap_uint<4> b, bool cin)
{
    // Propagate (p) and generate (g) for the 4 bits
    ap_uint<4> p = a ^ b;
    ap_uint<4> g = a & b;

    // Intermediate carry for each bit
    ap_uint<4> c;
    c[0] = cin;
    c[1] = g[0] | (p[0] & cin);
    c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & cin);
    c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);

    ap_uint<4> sum = p ^ c;

    bool cout = g[3] |
    		   (p[3] & g[2]) |
			   (p[3] & p[2] & g[1]) |
			   (p[3] & p[2] & p[1] & g[0]) |
			   (p[3] & p[2] & p[1] & p[0] & cin);

    return std::make_pair(sum, cout);
}


/**
 * @brief Perform a 16-bit carry look-ahead addition.
 * Takes two 16-bit numbers and an input carry, and computes their sum using the carry look-ahead.
 * It divides the operation into four 4-bit CLA operations and propagates the carry
 * from each block to the next to obtain the final result.
 *
 * @param a First 16-bit operand.
 * @param b Second 16-bit operand.
 * @param cin Input carry (carry-in).
 * @param sum A 16-bit unsigned int where the sum will be stored.
 * @param cout A boolean where the carry out will be stored.
 */
void CLA16(ap_uint<16> a, ap_uint<16> b, bool cin, ap_uint<16>& sum, bool& cout)
{
	#pragma HLS INTERFACE ap_none port=a
	#pragma HLS INTERFACE ap_none port=b
	#pragma HLS INTERFACE ap_none port=cin
	#pragma HLS INTERFACE ap_none port=sum
	#pragma HLS INTERFACE ap_none port=cout
	#pragma HLS INTERFACE ap_none port=return

	std::pair<ap_uint<4>, bool> result;

    // Process the first 4-bit block
    result = CLA4(a.range(3, 0), b.range(3, 0), cin);
    sum.range(3, 0) = result.first;
    bool c_out0 = result.second;

    // Process the second 4-bit block
    result = CLA4(a.range(7, 4), b.range(7, 4), c_out0);
    sum.range(7, 4) = result.first;
    bool c_out1 = result.second;

    // Process the third 4-bit block
    result = CLA4(a.range(11, 8), b.range(11, 8), c_out1);
    sum.range(11, 8) = result.first;
    bool c_out2 = result.second;

    // Process the fourth 4-bit block
    result = CLA4(a.range(15, 12), b.range(15, 12), c_out2);
    sum.range(15, 12) = result.first;
    cout = result.second;
}
