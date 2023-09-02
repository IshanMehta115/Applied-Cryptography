# Triple DES Encryption and Decryption

## Overview

Triple Data Encryption Standard (Triple DES or 3DES) is an encryption algorithm designed to secure data. It's an enhancement of the original Data Encryption Standard (DES) with improved security through triple encryption. DES is considered insecure due to its short key size of 56 bits, but 3DES is believed to be practically secure.

## Project Objective

The primary objective of this project is to implement the Triple DES encryption and decryption functions. These functions take the following inputs:

- A tuple of three keys, each of length 56 bits.
- The plaintext (for encryption) or ciphertext (for decryption).

The output of the function is a 128-bit ciphertext (for encryption) or plaintext (for decryption).

## Implementation Details

- The project is implemented in C++.
- Triple DES encryption is performed by applying the DES algorithm three times consecutively with three different keys.
- Decryption is the reverse process, where the ciphertext is decrypted three times with the corresponding keys.

## Usage

- Clone this repository.
- Compile and run the code.
- Provide a tuple of three 56-bit keys and the plaintext (for encryption) or ciphertext (for decryption).
- Retrieve the ciphertext (encryption) or plaintext (decryption) as output.

## Security Note

Encryption is a crucial security measure, and Triple DES is considered secure. However, always ensure that you follow best practices for secure key management and use encryption responsibly.<br>
**Although the algorithm is correct. It is advised to not use it in real-life.**
