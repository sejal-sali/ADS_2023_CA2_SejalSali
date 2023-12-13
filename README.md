# File Management System Project

This C++ project aims to develop a file management system utilizing a non-linear data structure. The implementation includes the design of a Tree data structure, XML document validation, command-line functionality, and a graphical user interface (GUI) using SFML.

## Objectives

1. **Practice Non-linear Data Structure Implementation:**
   - Design and implement a C++-based non-linear data structure.
   - Gain hands-on experience with advanced C++ concepts such as templates, functors, and predicates.

2. **C++ Unit Testing:**
   - Implement a Test Driven Development (TDD) approach for all functions and classes.
   - Write thorough unit tests for each functionality outlined in the project.

## Core Requirements

### Stage 1: Load XML Document into Tree Data Structure (15 Marks)

- Develop a system to load file system data from a valid XML document into a Tree data structure.
- Implement XML document validation using a stack data structure with the following rules:
  - XML documents must have a root element.
  - XML elements must have a closing tag.
  - XML elements must be properly nested.

### Stage 2: Command-Line Application (60 Marks)

- Implement a command-line application using the Tree data structure created in Stage 1.
  - a. Determine the number of items (Files or folders) within a given folder directory.
  - b. Determine the amount of memory used by a given folder using a breadth-first algorithm.
  - c. Prune the tree to remove empty folders.
  - d. Find a given file/folder with a partial or complete filename (Depth-first Search) and generate the path.
  - e. Display the contents of a given folder, including the size of files (not folders).

### Stage 3: GUI Implementation using SFML (10 Marks)

- Develop a graphical user interface (GUI) using SFML.
- Ensure that all functionalities described in Stage 2 are available in the GUI.
- Note: Complete this stage only after the successful completion of previous stages.

## Unit Testing Requirements (10 Marks)

- Follow a strict Test Driven Development (TDD) approach.
- Write stubs for classes and functions.
- Write comprehensive unit tests for each function outlined in this document.
- Refactor code and re-run tests until success.

## GitHub Usage

- Use GitHub regularly throughout the project for version control.
- Thoroughly unit test all functionalities in Stages 1 and 2.

## How to Contribute

1. Fork the project.
2. Create a new branch (`git checkout -b feature/awesome-feature`).
3. Make changes and commit them (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin feature/awesome-feature`).
5. Create a new Pull Request.

## License

This project is licensed under Sejal - see the [LICENSE.md](LICENSE.md) file for details. (Replace with the appropriate license information.)
