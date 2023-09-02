# TRIAD-HASH Implementation

## Overview

This project focuses on the implementation of the TRIAD-HASH function, a cryptographic hash function based on the TRIAD cipher. The objective is to create a function that computes a 32-byte hash value corresponding to a given message `M`.

## Project Objective

### TRIAD-HASH Function

- The `TRIAD-HASH` function is designed to take as input a message `M` of arbitrary length.
- It computes a 32-byte hash value that corresponds uniquely to the provided message `M`.
- The generated hash value can be used for data integrity verification, password hashing, or other cryptographic purposes.

## Implementation Details

- The project can be implemented in C++.
- The specifications for TRIAD-HASH can be found [here](https://csrc.nist.gov/CSRC/media/Projects/Lightweight-Cryptography/documents/round-1/spec-doc/TRIAD-spec.pdf).
- Understanding the principles of the TRIAD cipher is essential for correctly implementing the `TRIAD-HASH` function.

## Usage

- Clone this repository.
- Compile and run the code.
- Utilize the `TRIAD-HASH` function to compute hash values for messages.
- The generated hash values can be used for cryptographic applications.

## Contributing

Contributions and improvements to this project are welcome! Feel free to open issues or pull requests.

## Security Note

The TRIAD cipher is designed to be lightweight, and its use in cryptographic hashing should follow best practices to ensure security.<br>
**Although the algorithm is correct. It is advised to not use it in real-life.**
