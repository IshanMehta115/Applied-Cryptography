# TRIAD-AE Cipher Encryption and Decryption

## Overview

The TRIAD-AE cipher is one of the Round 1 candidates of the Lightweight Cryptography Project by NIST. You can find the specifications of the cipher [here](https://csrc.nist.gov/CSRC/media/Projects/Lightweight-Cryptography/documents/round-1/spec-doc/TRIAD-spec.pdf) (PDF file also available in the repository).

## Project Objective

The main objective of this project is to construct a function that implements the encryption and decryption algorithms of the TRIAD-AE cipher.

### Encryption

The encryption function should take the following inputs:
- A key `K`.
- A nonce `N`.
- A message `M`.

The output of the encryption function is a ciphertext `C`.

### Decryption

The decryption function should take the following inputs:
- A key `K`.
- A nonce `N`.
- The ciphertext `C`.

The output of the decryption function is the original message.

## Implementation Details

- The project is implemented in C++.
- The encryption algorithm of TRIAD-AE should be implemented following the specifications provided by NIST.
- The decryption algorithm is the reverse process, following the decryption specifications.

## Usage

- Clone this repository.
- Compile and run the code.
- Provide the key `K`, nonce `N`, and message `M` (for encryption), or key `K`, nonce `N`, and ciphertext `C` (for decryption).
- Retrieve the ciphertext (encryption) or the original message (decryption) as output.

## Security Note

Encryption is a crucial security measure, and the TRIAD-AE cipher is a candidate under consideration by NIST. Always ensure that you follow best practices for secure key management and use encryption responsibly.<br>
**Although the algorithm is correct. It is advised to not use it in real-life.**
