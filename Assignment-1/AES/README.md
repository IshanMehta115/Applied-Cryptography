# Advanced Encryption Scheme (AES) Implementation

## Overview

This project implements the Advanced Encryption Scheme (AES), which is one of the two National Institute of Standards and Technology (NIST) approved block cipher schemes. Depending on the length of the key used, there are three variants of AES — AES-128, AES-196, and AES-256.

## Project Objective

The main objective of this project is to implement the AES encryption and decryption scheme. The encryption algorithm takes the following inputs:

- A bit string message of size 128 bits.
- A security parameter `l` ∈ {128, 196, 256}.
- A key of length `l`.

The encryption algorithm outputs the ciphertext.

Similarly, the decryption algorithm takes the following inputs:

- A ciphertext of size 128 bits.
- A security parameter `l` ∈ {128, 196, 256}.
- A key of length `l`.

The decryption algorithm outputs the plaintext.

## Implementation Details

- The code is implemented in C++.
- The encryption and decryption algorithms adhere to the AES standards for the selected key length (128, 196, or 256 bits).

## Usage

- Clone this repository.
- Compile and run the code.
- Provide the required inputs: message, key, and security parameter.
- Retrieve the ciphertext (encryption) or plaintext (decryption) as output.

## Security Note

Please exercise caution when working with encryption algorithms. Ensure that you follow best practices for secure key management and use encryption responsibly.

