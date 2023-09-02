# TRIAD-MAC Implementation

## Overview

This project focuses on the implementation of the TRIAD-MAC function, a component of the lightweight cipher TRIAD. The objective is to create a function that generates a tag `T` corresponding to a given message `M`.

## Project Objective

### TRIAD-MAC Function

- The `TRIAD-MAC` function is designed to take as input a message `M` of arbitrary length.
- It computes a tag `T` that corresponds to the provided message `M`.
- The generated tag `T` serves as a verification code or authentication code for the given message `M`.

## Implementation Details

- The project can be implemented in C++.
- The specifications for TRIAD-MAC can be found [here](https://csrc.nist.gov/CSRC/media/Projects/Lightweight-Cryptography/documents/round-1/spec-doc/TRIAD-spec.pdf).
- Understanding the TRIAD cipher's principles is essential for correctly implementing the `TRIAD-MAC` function.

## Usage

- Clone this repository.
- Compile and run the code.
- Utilize the `TRIAD-MAC` function to generate tags for messages.
- The generated tags can be used for message verification or authentication.

## Contributing

Contributions and improvements to this project are welcome! Feel free to open issues or pull requests.

## Security Note

The TRIAD cipher is designed to be lightweight, but proper implementation and use are crucial for security. Ensure that you follow best practices for secure messaging.<br>
**Although the algorithm is correct. It is advised to not use it in real-life.**
