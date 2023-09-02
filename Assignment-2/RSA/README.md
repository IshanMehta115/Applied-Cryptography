# RSA Algorithm Implementation

## Overview

This project involves the implementation of the RSA (Rivest–Shamir–Adleman) algorithm, one of the most widely used public-key encryption methods. The objective is to create three functions: `Keys`, `Enc`, and `Dec`.

## Project Objective

### `Keys` Function

- Upon calling the `Keys` function, it generates both the public and private keys.
- The generated keys are fundamental for encryption and decryption processes.

### `Enc` Function

- The `Enc` function takes as input a message `m`, represented as a bit string of size 32 bits.
- Using the public key obtained from the `Keys` function, it encrypts the message `m`.
- The output is the ciphertext `c`.

### `Dec` Function

- The `Dec` function is designed for decryption.
- It takes the ciphertext `c` as input and, using the private key obtained from the `Keys` function, decrypts it.
- The output of this function is the original message `m`.

## Implementation Details

- The project is implemented in Python.
- The RSA algorithm involves complex mathematical operations, including modular arithmetic and prime number generation.
- Ensure that the keys generated are kept secure, especially the private key, as it's used for decryption.

## Usage

- Clone this repository.
- Compile and run the code.
- Utilize the `Keys` function to generate keys.
- Use the `Enc` function to encrypt a message.
- Employ the `Dec` function to decrypt the ciphertext.

## Security Note

RSA is a widely used encryption method. Always ensure that you follow best practices for secure key management and use encryption responsibly.
