- IoT Measurement Analyzer - Submission 2
https://github.com/SomaDilshad/Inlamningsuppgift-2-cpp.git

- Overview
This is an enhanced version of the IoT measurement analysis system from Submission 1. The program has been restructured using object-oriented principles with classes and structs, and new file handling capabilities have been added.

- Key Improvements from Submission 1

 1. Class and Struct Implementation
- Measurement struct: Simple data container for individual measurements with value and timestamp
- DataManager class: Comprehensive class handling all data operations and analysis

 2. File Handling (New Feature)
- Save measurements to CSV files
- Load measurements from CSV files
- Automatic saving on exit
- Support for loading previous sessions

 3. Code Structure
- Separated into multiple files for better organization
- Clear separation of interface and implementation
- Improved modularity and maintainability

 Compilation and Usage

- Compilation
```bash
# Using makefile
make

# Or compile manually
g++ -std=c++11 -I. main.cpp measurement.cpp data_manager.cpp -o iot_analyzer
```

- Running the Program
```bash
./iot_analyzer
```

- File Structure
```
├── main.cpp              - Main program with menu interface
├── measurement.h         - Measurement struct definition
├── measurement.cpp       - Measurement struct implementation
├── data_manager.h       - DataManager class definition
├── data_manager.cpp     - DataManager class implementation
├── makefile            - Build automation
├── README.md           - Documentation
└── measurements.csv    - Example data file
```

- Technical Design Decisions

- Why Use Struct for Measurement?
I chose a struct for the Measurement type because it's primarily a data container without complex behavior. The struct is simple, efficient, and appropriate for representing individual data points.

- Why Use Class for DataManager?
The DataManager class encapsulates complex operations like statistical calculations, file I/O, and data manipulation. Using a class allows for:
- Information hiding (private helper methods)
- Organized method grouping
- Better code reusability and maintainability

- File Format Choice
I chose CSV format because:
- It's human-readable
- Compatible with spreadsheet software
- Easy to parse and generate
- Widely used in data analysis

- Features Carried Over from Submission 1
- Manual data input with validation
- Sensor data simulation
- Statistical analysis (mean, variance, standard deviation)
- Search functionality
- Sorting capabilities
- Threshold analysis
- Moving average calculation
- ASCII histogram visualization

- New Features in Submission 2
- File save/load functionality
- Improved code structure with multiple files
- Better error handling for file operations
- Timestamp preservation in saved files

- Sample Usage
```
=== IoT DATA ANALYZER ===
1. Add manual measurements
2. Simulate sensor data
3. Show statistics
4. Search for value
5. Sort measurements
6. Threshold analysis
7. Moving average
8. Display histogram
9. Show all measurements
10. Clear all measurements
11. Save to file
12. Load from file
0. Exit program
Choice: 12
```

- Error Handling
- File I/O errors are caught and reported
- Invalid user input is handled gracefully
- Empty data sets are handled appropriately
- Memory management is automatic via RAII

- Extensibility
The modular design makes it easy to add new features:
1. Add new analysis methods to DataManager class
2. Extend Measurement struct with additional fields
3. Add new file formats by extending file handling methods
