# Simple C Lexical Analyzer

A simple, educational C program that tokenizes a given C source code file. This project demonstrates the core principles of lexical analysis, including identifying keywords, identifiers, operators, delimiters, and numerical literals.

## Repository Structure

The project is organized in a clear hierarchy to facilitate understanding and use:
* `/compiler_design`
    * `lexical.c`        # The main source file containing all function implementations
    * `lexical.h`        # The header file with all function prototypes
    * `test_code1.c`     # An example C code file for testing
    * `test_code2.c`     # Another example C code file for testing

* `lexical.exe` is the compiled executable file. It will be generated after building the project.

## Features

-   **Keyword Recognition:** Identifies all 32 standard C keywords.
-   **Identifier Validation:** Correctly validates identifiers based on C syntax rules (starts with a letter/underscore, followed by letters/digits/underscores).
-   **Tokenization:** Splits an input C file into a stream of tokens, including numbers and operators.
-   **File I/O:** Reads C code from a source file and processes it.

## How to Build and Run

1.  **Clone the Repository:**

2.  **Compile the Code:**
    Use `gcc` to compile the main source file and link the header file.
    ```bash
    gcc lexical.c -o lexical.exe
    ```

3.  **Run with Test Cases:**
    The project includes two test files. To run the analyzer on `test_code1.c` and `test_code2.c`, you will need to ensure those files exist in the same directory as the executable.

    Execute the compiled program:
    ```bash
    ./lexical.exe
    ```

## Example Output

For a test file with `int a = 5;`, the output will be similar to:

- Keyword: int
- Identifier: a
- Operator: =
- Integer: 5
- Delimiter: ;


## Acknowledgements

This project was inspired by and implemented with guidance from a fantastic YouTube playlist on GCC Toolchain. A special thank you to the creator for providing a clear, step-by-step approach to building a lexical analyzer from scratch.

* **Compiler Design Playlist:** [https://youtube.com/playlist?list=PLwHa6WZP7iSIz4vFoNVv5q-5qMM1DUGZ1](https://youtube.com/playlist?list=PLwHa6WZP7iSIz4vFoNVv5q-5qMM1DUGZ1)

