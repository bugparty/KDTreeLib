# KDTreeLib

## Project Structure Overview

This paragraph outlines the organization of the MyProject codebase. Our structure is designed to help developers and new contributors understand where specific types of files can be found and how the project is organized.

### Directory Layout

- `src/`: Contains the project's C++ source files. This is where the main functionality of the project is implemented.

    - `main.cpp`: The main entry point of the application. It ties together functionalities from other modules.

- `include/`: Holds all the header files. Separating the headers from the source files helps in managing dependencies and increases the clarity of the interface.

    - `kdtree_lib/`: A directory named after the project to prevent name clashes with headers from other projects or libraries.

- `third_party/`: Contains third-party dependencies not managed by a package manager. This ensures that all external dependencies are version-controlled along with the project.

    - `i-octree/`: A directory for the external library `i-octree` that is used in this project.
    - `ikd-Tree/`: A directory for the external library `ikd-Tree` that is used in this project.

- `tests/`: Contains unit tests, potentially leveraging a framework like Google Test. This helps in maintaining the quality and reliability of the codebase.


- `CMakeLists.txt`: For projects using CMake, this is the main CMake configuration file. It defines how the project should be built.

- `README.md`: Provides an introduction or guide to the project. This is the document you're currently reading.

- `.gitignore`: Specifies intentionally untracked files that Git should ignore. This usually includes build output, temporary files, and sensitive information.

### Additional Notes

This structure is a starting point and can be adapted based on the specific needs of the project. For example, projects may also include:

- `docs/`: For project documentation.
- `bin/`: For binary executables.
- `lib/`: For static and dynamic libraries.

### Conclusion

We hope this layout helps you navigate the KDTreeLib codebase. If you have any questions or suggestions for improvement, please feel free to contribute or contact the project maintainers.
## Documentation
documentation is available at [KDTreeLib](https://bugparty.github.io/KDTreeLib/)
You can append the following instructions to your `README.md` file to guide users on how to generate Doxygen documentation:

## Generating Documentation

This project uses Doxygen for documentation. To generate the documentation, follow the steps below:

1. Ensure that Doxygen is installed on your system. If not, you can install it using the package manager for your system. For example, on macOS, you can use Homebrew:

```bash
brew install doxygen
```

2. Navigate to the project directory:

```bash
cd path/to/project
```

3. Run the `gendocs` script:

```bash
./gendocs
```

4. The documentation will be generated and can be found in the `docs/` directory. Open the `index.html` file in a web browser to view the documentation.

Please note that the `gendocs` script should be executable. If it's not, you can make it executable by running:

```bash
chmod +x gendocs
```
