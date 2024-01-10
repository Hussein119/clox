# Clox - Crafting Interpreters

This repository contains the Clox codebase developed as part of the "Crafting Interpreters" book by Bob Nystrom. The code in this repository corresponds to the implementation discussed in Chapters 14 and 15 of the book.

## Getting Started

To run and experiment with Clox, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/Hussein119/clox.git
   cd craftinginterpreters
   ```

2. Navigate to the `clox` directory:

   ```bash
   cd clox
   ```

3. Build the Clox interpreter:

   ```bash
   gcc main.c memory.c chunk.c debug.c value.c vm.c -o main
   ```

4. Run the Clox interpreter with a script:

   ```bash
   ./main
   ```

## Additional Resources

- [Crafting Interpreters Book](https://craftinginterpreters.com/): The official website for the book with free online access.

- [Clox Repository](https://github.com/munificent/craftinginterpreters): The original repository for the Clox code.

## Acknowledgments

- Bob Nystrom: Author of "Crafting Interpreters" and creator of the Clox interpreter.
- The Crafting Interpreters community: For their contributions and discussions.

Happy coding!