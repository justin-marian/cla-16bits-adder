# [Carry-Lookahead Adder](./CLA16.pdf)

The **Carry-Lookahead Adder (CLA) 16-bits Adder** is a type of digital circuit that improves upon the performance of a standard ripple-carry adder by reducing the propagation delay caused by carry bits.

## [Full Adder](https://en.wikipedia.org/wiki/Adder_(electronics)#Full_adder)

A full adder is the building block of a CLA, which performs the addition of three bits: two significant bits and one carry-in bit (`Cin`). It produces a sum bit and a carry-out bit (`Cout`), where:

- **\(Sum \)** $=$ \( A \oplus B \oplus \text{Cin} \)
- **\(Cout\)** $=$ \( (A \land B) \lor (B \land \text{Cin}) \lor (A \land \text{Cin}) \)

### [CLA4](https://en.wikipedia.org/wiki/Lookahead_carry_unit)

A 4-bit CLA uses full adders by generating and propagating carry bits without waiting for carry-out from the previous stage. This is achieved by introducing two signals for each bit position:

- **G (Generate)**: Indicates if a carry bit will be generated.
- **P (Propagate)**: Indicates if a carry bit will be propagated.

The carry bits are calculated using these signals, which allows the CLA to determine carry bits in parallel.

### [CLA16](https://en.wikipedia.org/wiki/Lookahead_carry_unit)

For the **16-bit CLA**, **four 4-bit CLA blocks** are interconnected, each block responsible for a group of 4 bits. The CLA16 extends the concept of carry generation and propagation across 16 bits, making it suitable for larger binary numbers.

### Signals for 16-bit CLA

The key signals `Gi` and `Pi` are used for the ith group of bits, where:

- **Gi**: True if the ith group generates a carry.
- **Pi**: True if the ith group can propagate a carry.

These signals allow the calculation of the carry bits (`Ci+1`) for each group using logical equations.

## Advantages of CLA

- **Quick Carry Calculation**: Carry bits are determined without sequential dependency.
- **Latency Reduction**: Parallel calculation of carry bits reduces overall latency.
- **Scalability**: CLA scales efficiently for larger binary numbers.

## Testing and Validation

The CLA circuit is tested using various input cases to ensure its correct operation under different conditions such as random values, boundary conditions, and specific binary patterns.

**Implementation Details:**

- **Product Family**: Target FPGA device family, e.g., "artix7".
- **Target Device**: Specific FPGA model used for synthesis.
- **Timing**: Design constraints for clock frequency and propagation delay.

**Ports and Interface:**

- **a and b**: Operand inputs for the addition operation.
- **cin**: Input carry bit (carry-in).
- **sum**: Output port for the result of addition.
- **cout**: Output carry bit (carry-out).
