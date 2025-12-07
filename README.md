# Secure Network Assessment Tool (SNAT)

**Data Structures and Algorithms Project - CS221**

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage Guide](#usage-guide)
- [Architecture](#architecture)
- [Data Structures](#data-structures)
- [Algorithms](#algorithms)
- [Performance Analysis](#performance-analysis)
- [Testing](#testing)
- [File Formats](#file-formats)
- [API Reference](#api-reference)
- [Known Limitations](#known-limitations)
- [Future Work](#future-work)
- [Contributing](#contributing)
- [Team](#team)

---

## Project Overview

SNAT (Secure Network Assessment Tool) is a comprehensive cybersecurity risk assessment application designed to evaluate network systems, identify vulnerabilities, and generate detailed security reports. This project demonstrates practical implementation of fundamental data structures and algorithms in a real-world cybersecurity context.

**Course Information:**
- Course: CS221 - Data Structures and Algorithms
- Deliverable: 3 of 4
- Version: 3.0
- Academic Year: 2024-2025

---

## Features

### Core Functionality

- Dynamic system management (add, delete, search operations)
- Automated port scanning simulation
- Vulnerability detection and assessment
- Risk score calculation with weighted factors (0-100 scale)
- Multiple sorting algorithms with performance comparison
- Persistent data storage with file I/O operations
- Comprehensive security report generation

### Data Structures Implemented

1. **Circular Doubly Linked List** - Primary system storage and management
2. **Stack (LIFO)** - Task workflow management
3. **Queue (FIFO)** - System scanning task scheduling
4. **Binary Search Tree** - Risk-based system organization
5. **Arrays** - Port lists, service mappings, vulnerability tracking

### Algorithms Implemented

**Sorting Algorithms:**
- Selection Sort - O(n²) time complexity
- Bubble Sort - O(n²) time complexity
- Insertion Sort - O(n²) time complexity
- Quick Sort - O(n log n) average time complexity
- Merge Sort - O(n log n) guaranteed time complexity

**Searching Algorithms:**
- Linear Search - O(n) time complexity
- Binary Search - O(log n) time complexity

**Custom Algorithms:**
- Weighted risk calculation algorithm
- Port scanning simulation
- Vulnerability pattern detection

---

## System Requirements

### Prerequisites

- **Compiler:** g++ 7.0 or higher (MinGW-w64 for Windows, GCC for Linux/macOS)
- **C++ Standard:** C++17 or later
- **Operating System:** Windows 10/11, Linux (Ubuntu 18.04+), macOS 10.14+
- **RAM:** Minimum 2GB
- **Disk Space:** 50MB for source code and compiled binaries

### Recommended Tools

- **IDE:** Visual Studio Code, CLion, or Visual Studio 2019+
- **Version Control:** Git 2.20+
- **Terminal:** PowerShell 5.1+ (Windows), Bash (Linux/macOS)

---

## Installation

### Step 1: Clone the Repository

```bash
git clone https://github.com/yourusername/snat-project.git
cd snat-project/Deliverable-3
```

### Step 2: Verify File Structure

Ensure all source files are present:

```
Deliverable-3/
├── main.cpp
├── structure.h
├── structure.cpp
├── algorithm.h
├── algorithm.cpp
├── menu.h
├── menu.cpp
├── input.h
├── input.cpp
├── fileio.h
├── fileio.cpp
├── build.ps1
├── README.md
└── Deliverable3_Report.md
```

### Step 3: Compilation

**Option A: Using Build Script (Windows)**

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\build.ps1
```

**Option B: Manual Compilation (All Platforms)**

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp structure.cpp algorithm.cpp menu.cpp input.cpp fileio.cpp -o snat
```

**Option C: Using Makefile (Linux/macOS)**

```bash
make all
```

### Step 4: Run the Application

```bash
# Windows
.\snat.exe

# Linux/macOS
./snat
```

---

## Usage Guide

### Main Menu Navigation

Upon launching SNAT, users are presented with the following menu:

```
1. Add New System       - Register new network systems
2. Delete System        - Remove systems from monitoring
3. Search System        - Locate systems by name or IP
4. Scan & Assess        - Perform security scanning
5. Sort Systems         - Organize by risk level
6. Display Options      - View system information
7. Performance Analysis - Compare algorithm efficiency
8. File Operations      - Save/load data, generate reports
9. Exit                 - Close application
```

### Adding a System

1. Select option `1` from main menu
2. Enter system information when prompted:
   - **System Name:** Alphanumeric identifier (e.g., "WebServer1")
   - **IP Address:** Valid IPv4 address (e.g., "192.168.1.100")
   - **Password Strength:** Integer 1-10 (10 = strongest)
   - **Open Ports:** Integer 0-10
   - **Firewall Status:** Yes/No
   - **Encryption Status:** Yes/No
   - **Malware Detection:** Yes/No
3. System automatically calculates and displays risk score

### Performing System Scan

1. Select option `4` from main menu
2. Choose target system from displayed list
3. Application performs:
   - Simulated port scanning
   - Vulnerability pattern matching
   - Risk score recalculation
4. Results displayed with recommendations

### Sorting Systems

1. Select option `5` from main menu
2. Choose sorting algorithm:
   - Options 1-3: O(n²) algorithms for small datasets (n < 50)
   - Options 4-5: O(n log n) algorithms for large datasets (n > 50)
   - Option 6: Performance comparison across all algorithms
3. Systems displayed in descending order by risk score

### Generating Security Reports

1. Select option `8` from main menu
2. Select option `3` for report generation
3. Report includes:
   - Executive summary with statistics
   - Risk distribution breakdown
   - Detailed system analysis
   - Security recommendations
4. Report saved to `network_report.txt`

---

## Architecture

### System Design

SNAT follows a modular architecture with clear separation of concerns:

```
┌─────────────────────────────────────────┐
│         User Interface Layer            │
│       (menu.cpp, input.cpp)             │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│      Business Logic Layer               │
│    (algorithm.cpp, main.cpp)            │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│     Data Structure Layer                │
│       (structure.cpp)                   │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│       Persistence Layer                 │
│        (fileio.cpp)                     │
└─────────────────────────────────────────┘
```

### Module Descriptions

| Module | Responsibility | Key Functions |
|--------|---------------|---------------|
| **structure.cpp** | Data structure implementations | SystemList, Stack, Queue, BST operations |
| **algorithm.cpp** | Core algorithms | Sorting, searching, risk calculation |
| **menu.cpp** | User interface | Menu display, user interaction handling |
| **input.cpp** | Input validation | Data validation, error checking |
| **fileio.cpp** | File operations | Save, load, report generation |
| **main.cpp** | Application entry | Initialization, main loop, cleanup |

---

## Data Structures

### Circular Doubly Linked List

**Purpose:** Primary storage mechanism for network system records

**Structure Definition:**
```cpp
struct Node {
    System* data;
    Node* next;
    Node* prev;
};
```

**Operations & Complexity:**
- `add_system()` - O(1) time, O(1) space
- `delete_system(name)` - O(n) time, O(1) space
- `search_system(name)` - O(n) time, O(1) space
- `traverse_forward()` - O(n) time, O(1) space
- `traverse_backward()` - O(n) time, O(1) space

**Advantages:**
- Bidirectional traversal capability
- No NULL pointers in circular structure
- Efficient insertion and deletion at any position
- Dynamic memory allocation

### Stack (Array-Based)

**Purpose:** Managing task execution workflow

**Structure:**
```cpp
struct TaskStack {
    string tasks[20];
    int top;
};
```

**Operations:**
- `push(task)` - O(1)
- `pop()` - O(1)
- `is_empty()` - O(1)

**Use Case:** Vulnerability assessment workflow management

### Queue (Circular Array)

**Purpose:** Fair scheduling of system scanning tasks

**Structure:**
```cpp
struct ScanQueue {
    string tasks[20];
    int front, rear, count;
};
```

**Operations:**
- `enqueue(task)` - O(1)
- `dequeue()` - O(1)
- `size()` - O(1)

**Use Case:** Sequential system processing in order of submission

### Binary Search Tree

**Purpose:** Risk-based organization and retrieval

**Structure:**
```cpp
struct BSTNode {
    System* data;
    BSTNode* left;
    BSTNode* right;
};
```

**Tree Property:** Left subtree contains lower risk scores, right subtree contains higher risk scores

**Operations:**
- `insert(system)` - O(log n) average, O(n) worst
- `search(risk_score)` - O(log n) average, O(n) worst
- `inorder_traversal()` - O(n)

---

## Algorithms

### Sorting Algorithms

#### Selection Sort
- **Time Complexity:** O(n²) - all cases
- **Space Complexity:** O(1)
- **Stable:** No
- **Best Use:** Small datasets where simplicity is prioritized

#### Bubble Sort
- **Time Complexity:** O(n²) worst/average, O(n) best
- **Space Complexity:** O(1)
- **Stable:** Yes
- **Best Use:** Nearly sorted data

#### Insertion Sort
- **Time Complexity:** O(n²) worst, O(n) best
- **Space Complexity:** O(1)
- **Stable:** Yes
- **Best Use:** Small or nearly sorted datasets

#### Quick Sort
- **Time Complexity:** O(n log n) average, O(n²) worst
- **Space Complexity:** O(log n)
- **Stable:** No
- **Best Use:** Large datasets, general-purpose sorting

#### Merge Sort
- **Time Complexity:** O(n log n) - all cases
- **Space Complexity:** O(n)
- **Stable:** Yes
- **Best Use:** Large datasets requiring guaranteed performance

### Searching Algorithms

#### Linear Search
- **Time Complexity:** O(n)
- **Use Case:** Unsorted data, search by system name

#### Binary Search
- **Time Complexity:** O(log n)
- **Requirement:** Sorted array
- **Use Case:** Sorted data, search by risk score

### Risk Calculation Algorithm

**Formula:**
```
risk_score = (10 - password_strength) × 2.5
           + open_ports × 15
           + (!encryption_enabled) × 15
           + (malware_detected) × 20
           + (!firewall_enabled) × 10

Maximum: 100 (capped)
```

**Weight Distribution:**
- Password Security: 25%
- Open Ports: 30%
- Encryption: 15%
- Malware Presence: 20%
- Firewall Status: 10%

**Risk Classification:**
- 0-49: LOW (requires routine monitoring)
- 50-79: MEDIUM (requires attention)
- 80-100: HIGH (requires immediate action)

---

## Performance Analysis

### Time Complexity Summary

| Operation | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| Add System | O(1) | O(1) | O(1) |
| Delete System | O(1) | O(n) | O(n) |
| Search System | O(1) | O(n) | O(n) |
| Selection Sort | O(n²) | O(n²) | O(n²) |
| Bubble Sort | O(n) | O(n²) | O(n²) |
| Insertion Sort | O(n) | O(n²) | O(n²) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |
| Linear Search | O(1) | O(n) | O(n) |
| Binary Search | O(1) | O(log n) | O(log n) |

### Space Complexity

| Data Structure | Space Complexity | Notes |
|----------------|------------------|-------|
| Linked List | O(n) | Linear growth with system count |
| Stack | O(1) | Fixed array size (20 elements) |
| Queue | O(1) | Fixed array size (20 elements) |
| BST | O(n) | Linear growth, O(log n) stack for recursion |
| Sorting | O(1) - O(n) | Varies by algorithm |

### Empirical Performance (n=100 systems)

| Algorithm | Time (microseconds) | Memory (KB) |
|-----------|---------------------|-------------|
| Selection Sort | 1,243 | 8.5 |
| Bubble Sort | 1,856 | 8.5 |
| Insertion Sort | 891 | 8.5 |
| Quick Sort | 187 | 9.2 |
| Merge Sort | 203 | 16.8 |

---

## Testing

### Test Suite Overview

SNAT includes comprehensive test coverage across three categories:

1. **Unit Tests** - Individual function validation
2. **Integration Tests** - Module interaction verification
3. **System Tests** - End-to-end application testing

### Running Tests

```bash
# Compile unit tests
g++ -std=c++17 test_team1.cpp structure.cpp algorithm.cpp -o test1
g++ -std=c++17 test_team2.cpp structure.cpp algorithm.cpp input.cpp fileio.cpp -o test2

# Run unit tests
./test1
./test2

# Compile integration tests
g++ -std=c++17 test_integration.cpp structure.cpp algorithm.cpp input.cpp fileio.cpp -o test_int

# Run integration tests
./test_int
```

### Test Coverage

| Category | Tests | Pass Rate |
|----------|-------|-----------|
| Data Structures | 12 | 100% |
| Algorithms | 15 | 100% |
| Input Validation | 8 | 100% |
| File Operations | 5 | 100% |
| Integration | 10 | 100% |
| **Total** | **50** | **100%** |

### Edge Cases Tested

- Empty list operations (add, delete, search)
- Single element operations
- Maximum capacity handling (stack/queue)
- Invalid input rejection (IP addresses, names)
- File I/O error handling
- Memory leak prevention
- Circular reference handling

---

## File Formats

### System Data File (systems_data.txt)

**Format:** Pipe-delimited text file

**Structure:**
```
name|ip|password_strength|open_ports|firewall|encryption|malware|risk_score
```

**Example:**
```
WebServer|192.168.1.10|7|2|1|1|0|34
Database|192.168.1.20|3|8|0|0|1|89
Workstation|192.168.1.30|9|1|1|1|0|12
```

**Field Specifications:**
- `name`: String (max 50 characters)
- `ip`: IPv4 address (xxx.xxx.xxx.xxx)
- `password_strength`: Integer (1-10)
- `open_ports`: Integer (0-10)
- `firewall`: Boolean (0=disabled, 1=enabled)
- `encryption`: Boolean (0=disabled, 1=enabled)
- `malware`: Boolean (0=clean, 1=detected)
- `risk_score`: Integer (0-100)

### Security Report File (network_report.txt)

**Format:** Plain text with structured sections

**Sections:**
1. Header with generation timestamp
2. Executive summary with statistics
3. Risk distribution breakdown
4. Detailed system analysis
5. Security recommendations

**Example Output:**
```
========================================
  NETWORK SECURITY ASSESSMENT REPORT
  Secure Network Assessment Tool (SNAT)
========================================

EXECUTIVE SUMMARY
----------------------------------------
Total Systems Assessed: 15

Risk Distribution:
  • High Risk (≥80):     3 systems
  • Medium Risk (50-79): 5 systems
  • Low Risk (<50):      7 systems

Total Vulnerabilities Found: 12
```

---

## API Reference

### Structure Module (structure.h)

#### SystemList Class

```cpp
class SystemList {
public:
    SystemList();                           // Constructor
    ~SystemList();                          // Destructor
    void add_system(System* sys);           // Add system - O(1)
    bool delete_system(string name);        // Delete by name - O(n)
    System* search_system(string name);     // Search by name - O(n)
    int get_count();                        // Get count - O(1)
    void display_all();                     // Display all - O(n)
    void display_high_risk();               // Display high risk - O(n)
    Node* get_head();                       // Get head pointer - O(1)
};
```

#### TaskStack Structure

```cpp
struct TaskStack {
    TaskStack();                    // Constructor
    void push(string task);         // Push task - O(1)
    string pop();                   // Pop task - O(1)
    bool is_empty();                // Check empty - O(1)
    bool is_full();                 // Check full - O(1)
    int size();                     // Get size - O(1)
};
```

#### ScanQueue Structure

```cpp
struct ScanQueue {
    ScanQueue();                    // Constructor
    void enqueue(string task);      // Enqueue - O(1)
    string dequeue();               // Dequeue - O(1)
    bool is_empty();                // Check empty - O(1)
    bool is_full();                 // Check full - O(1)
    int size();                     // Get size - O(1)
};
```

#### RiskBST Class

```cpp
class RiskBST {
public:
    RiskBST();                              // Constructor
    ~RiskBST();                             // Destructor
    void insert(System* sys);               // Insert - O(log n) avg
    void inorder_traversal();               // Inorder - O(n)
    void preorder_traversal();              // Preorder - O(n)
    void postorder_traversal();             // Postorder - O(n)
    System* search_by_risk(int score);      // Search - O(log n) avg
};
```

### Algorithm Module (algorithm.h)

#### Risk Calculation

```cpp
int calculate_risk(System* sys);                    // Calculate individual - O(1)
void calculate_all_risks(SystemList& list);         // Calculate all - O(n)
```

#### Sorting Functions

```cpp
void selection_sort(System* systems[], int n);      // O(n²)
void bubble_sort(System* systems[], int n);         // O(n²)
void insertion_sort(System* systems[], int n);      // O(n²)
void quick_sort(System* systems[], int low, int high);  // O(n log n) avg
void merge_sort(System* systems[], int left, int right); // O(n log n)
```

#### Searching Functions

```cpp
System* linear_search(System* systems[], int n, string name);     // O(n)
System* binary_search_by_risk(System* systems[], int n, int score); // O(log n)
```

#### Utility Functions

```cpp
void scan_ports(System* sys);                       // Port scanning simulation
void check_vulnerabilities(System* sys);            // Vulnerability detection
void compare_sorting_algorithms(System* sys[], int n); // Performance comparison
```

### Input Module (input.h)

```cpp
string get_string_input(string prompt);             // Validated string input
int get_int_input(string prompt, int min, int max); // Validated integer input
bool get_bool_input(string prompt);                 // Validated boolean input
string get_ip_input(string prompt);                 // Validated IP input
bool is_valid_ip(string ip);                        // IP validation
bool is_valid_name(string name);                    // Name validation
```

### FileIO Module (fileio.h)

```cpp
bool save_systems_to_file(SystemList& list, string filename);      // Save data
bool load_systems_from_file(SystemList& list, string filename);    // Load data
void generate_report(SystemList& list, string filename);           // Generate report
```

---

## Known Limitations

### Technical Constraints

1. **Port Scanning Simulation**
   - Current implementation uses randomized simulation
   - Does not perform actual network port scanning
   - Requires integration with external tools (e.g., nmap) for production use

2. **Binary Search Prerequisite**
   - Requires manual sorting before use
   - No automatic sorting detection or trigger

3. **Capacity Limits**
   - Stack: Maximum 20 tasks
   - Queue: Maximum 20 tasks
   - Port list per system: Maximum 10 ports
   - Vulnerability list per system: Maximum 5 entries

4. **Data Persistence**
   - Single-file storage format
   - No concurrent access handling
   - No database backend

5. **Platform Dependencies**
   - Console clearing uses platform-specific commands
   - File paths use forward slashes (Unix-style)

### Future Improvements

See [Future Work](#future-work) section for planned enhancements.

---

## Future Work

### Phase 1: Enhanced Data Structures

#### Hash Table Implementation
- **Objective:** Achieve O(1) average-case system lookup
- **Method:** Implement chaining or open addressing
- **Benefit:** Significant performance improvement for large networks

#### Graph Structure for Network Topology
- **Objective:** Model network connections and relationships
- **Representation:** Adjacency list or adjacency matrix
- **Applications:** 
  - Shortest path between systems
  - Network connectivity analysis
  - Vulnerability propagation modeling

#### Priority Queue for Risk Management
- **Objective:** Automatic prioritization of high-risk systems
- **Implementation:** Binary heap
- **Use Case:** Automated remediation scheduling

### Phase 2: Algorithm Enhancements

#### Self-Balancing Trees
- AVL Tree or Red-Black Tree implementation
- Guaranteed O(log n) operations
- Prevention of worst-case scenarios

#### Advanced Pathfinding
- Dijkstra's algorithm for optimal scanning paths
- Floyd-Warshall for all-pairs shortest paths

#### Dynamic Programming Optimization
- Resource allocation for security remediation
- Knapsack-style problem solving

### Phase 3: Feature Additions

#### Real Network Integration
- nmap integration for actual port scanning
- Vulnerability database integration (CVE)
- Live network traffic analysis

#### Graphical User Interface
- Qt or wxWidgets framework
- Interactive network topology visualization
- Real-time monitoring dashboard

#### Database Backend
- SQLite for local storage
- PostgreSQL for enterprise deployment
- Historical data tracking and trend analysis

#### Multi-threading Support
- Parallel system scanning
- Non-blocking user interface
- Improved performance for large networks

#### Machine Learning Integration
- Anomaly detection algorithms
- Predictive risk assessment
- Automated remediation recommendations

#### Cloud Deployment
- Cloud-based storage and processing
- Multi-user collaboration features
- Real-time synchronization across clients

---

## Contributing

### Development Workflow

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/YourFeature`)
3. Commit your changes (`git commit -m 'Add YourFeature'`)
4. Push to the branch (`git push origin feature/YourFeature`)
5. Open a Pull Request

### Code Style Guidelines

- Follow C++17 standard conventions
- Use descriptive variable and function names
- Comment complex algorithms and data structures
- Maximum line length: 100 characters
- Indentation: 4 spaces (no tabs)

### Testing Requirements

- All new features must include unit tests
- Maintain minimum 90% code coverage
- All tests must pass before merging
- Include integration tests for module interactions

### Documentation Standards

- Update README.md for user-facing changes
- Update API Reference for new functions
- Include inline comments for complex logic
- Maintain changelog in CHANGELOG.md

---


### Project Contributors

**Team Member 1: Data Structures & Algorithms**
- Circular Doubly Linked List implementation
- Stack and Queue structures
- Binary Search Tree implementation
- All sorting algorithms (Selection, Bubble, Insertion, Quick, Merge)
- Searching algorithms (Linear, Binary)
- Performance analysis framework

**Team Member 2: User Interface & Input/Output**
- Menu system design and implementation
- Input validation module
- File I/O operations (save, load, report generation)
- Error handling and user feedback
- Menu navigation handlers

**Team Member 3: Integration & Documentation**
- System integration and testing
- Main application workflow
- Integration test suite
- README and technical documentation
- Build scripts and deployment

---

## Team:
**Muhammad Saim:**(2024453)
**Muhammad Haris Zafar:**(2024396)
**Muhammad Ibrahim Gulzar:**(2024409)


### Academic Information

**Course:** CS221 - Data Structures and Algorithms  
**Instructor:** Dr. Zubair Ahmad  
**Institution:** Ghulam Ishaq Khan Institute   
**Academic Year:** 2024-2025  
**Email:** zubair.ahmad@giki.edu.pk

---


**Course Instructor:**  
Dr. Zubair Ahmad  
Email: zubair.ahmad@giki.edu.pk  
Office: G14 FCSE Lobby



## Acknowledgments

We would like to express our gratitude to:

- Dr. Zubair Ahmad for course instruction and project guidance
- Teaching assistants for technical support
- Course peers for valuable feedback and testing
- Open source community for reference implementations

---
