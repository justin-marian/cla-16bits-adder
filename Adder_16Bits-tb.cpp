#include "Adder_16Bits-tb.h"

#include <iostream>
#include <cstdlib>

void run_test(const ap_uint<16>& a, const ap_uint<16>& b, bool cin)
{
    ap_uint<16> sum = 0;
    bool cout = 0;
    bool expected_cout;
    ap_uint<17> expected_sum;

    CLA16(a, b, cin, sum, cout);

    expected_sum = a.to_uint() + b.to_uint() + cin;
    expected_cout = expected_sum[16];

    if (sum != expected_sum.range(15, 0) || cout != expected_cout) {
        std::cout << "Test failed for:\n";
        std::cout << "\ta: " << a.to_string() << "\n";
        std::cout << "\tb: " << b.to_string() << "\n";
        std::cout << "\tcin: " << cin << "\n";
        std::cout << "Expected:\n";

        std::cout << "\tSum: " << expected_sum.range(15, 0).to_string() << "\n";
        std::cout << "\tCout: " << expected_cout << "\n";
        std::cout << "Actual:\n";
        std::cout << "\tSum: " << sum.to_string() << "\n";
    } else {
        std::cout << "Test passed for:\n";
        std::cout << "\ta: " << a.to_string() << "\n";
        std::cout << "\tb: " << b.to_string() << "\n";
        std::cout << "\tcin: " << cin << "\n";
        std::cout << "\tcout: " << expected_cout << "\n";
        std::cout << "\tSum: " << expected_sum.range(15, 0).to_string() << "\n";
    }
}


int main()
{
    // Random test cases
    run_test(0x14DC, 0xA628, 0); 		// 0xBB04
    run_test(0xBFD3, 0xC9B9, 0);		// 0x898C
    run_test(0xF186, 0x5BE3, 1);		// 0x4D6A

    // Boundary Conditions Test
    run_test(0x0000, 0x0000, 0);		// Both inputs as zero, no carry-in
    run_test(0xFFFF, 0xFFFF, 0);		// Both inputs at maximum value, no carry-in
    run_test(0x0000, 0xFFFF, 1);		// One input zero, the other at maximum, and carry-in
    run_test(0xFFFF, 0x0000, 1);		// One input at maximum, the other zero, and carry-in
    run_test(0x0001, 0x0001, 0);		// Small numbers
    run_test(0xFFFE, 0x0001, 1);		// Overflow edge case
    run_test(0x8000, 0x8000, 0);		// Mid-range overflow
    run_test(0x7FFF, 0x7FFF, 1);		// Just below mid-range with carry-in

    // Pattern Test
    run_test(0xAAAA, 0x5555, 0);		// Alternating bit pattern (1010...1010 and 0101...0101), no carry-in
    run_test(0x5555, 0xAAAA, 1);		// Alternating bit pattern (0101...0101 and 1010...1010), with carry-in
    run_test(0xF0F0, 0x0F0F, 0);		// Alternate nibble patterns
    run_test(0x3333, 0xCCCC, 1);		// Complementary bit patterns
    run_test(0x1234, 0xEDCB, 0);		// Sequential increasing vs decreasing
    run_test(0xAAAA, 0x0001, 1);		// Pattern with minimal increment

    return 0;
}
