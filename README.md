# 🌲 Set — Custom STL-Compatible Associative Container in C++

![C++20](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![Type](https://img.shields.io/badge/Type-Balanced%20BST%20%7C%20AVL%20Tree-green.svg)
![Complexity](https://img.shields.io/badge/Complexity-O(log%20N)-brightgreen.svg)
![Coursework](https://img.shields.io/badge/University-Data%20Structures%20Course-orange.svg)
![Tests](https://img.shields.io/badge/Tests-TDD%20(12%20Suites)-brightgreen.svg)

A university coursework project for the **Data Structures and Algorithms** course. This repository provides an object-oriented implementation of an associative set of unique sorted integers (`Set`), built on top of a **self-balancing Binary Search Tree (AVL Tree / Balanced BST)** and adhering to the semantics of `std::set` from the C++ Standard Template Library.

---

## 📌 Architectural Highlights

### 1. Balanced Tree Data Structure
Each element is stored in a tree node tracking left/right children, a parent pointer, and subtree height:
```cpp
struct Node {
    int _val;
    int _height;
    Node* _left;
    Node* _right;
    Node* _parent;
};
```
Because each node stores its `_parent` pointer, in-order traversal and iterator steps require **no auxiliary stack or dynamic heap allocations**.

### 2. Guaranteed O(log N) Logarithmic Bounds
- Insertion (`insert`), membership testing (`contains`, `find`), deletion (`erase`), and range searches (`lower_bound`, `upper_bound`) strictly maintain **O(log N)** time complexity.
- A dedicated benchmark test **`TimeLimitTest`** asserts that logarithmic tree depth is sustained under heavy insertion and deletion workloads.

### 3. Bidirectional In-Order Iterators
The container iterator traverses keys in strict ascending numerical order:
- **`++it` (Successor)**: Computes the next key via `inorder_next`:
  - If a right child exists, navigates to the leftmost descendant of that right subtree.
  - Otherwise, ascends parent links until arriving at an ancestor whose left child was the traversed path.
- **`--it` (Predecessor)**: Symmetric predecessor navigation via `inorder_prev`.
- Satisfies the `std::bidirectional_iterator` requirements.

### 4. Boundary Range Searches (lower_bound & upper_bound)
Implements standard STL boundary queries:
- `lower_bound(val)`: Returns an iterator pointing to the first element that is **not less than** `val` (i.e. `>= val`).
- `upper_bound(val)`: Returns an iterator pointing to the first element that is **strictly greater than** `val` (i.e. `> val`).

---

## 📁 Repository Structure

```text
Set/
├── Set.sln                          # Visual Studio 2022 Solution
├── .gitignore                       # Git ignores for build artifacts
│
└── Set/
    ├── Set.h                        # Interface header: Set and internal Node
    ├── Set.cpp                      # Tree balancing, rotations, and algorithm logic
    ├── main.cpp                     # Test execution entry point
    ├── Set.vcxproj                  # MSVC Project file
    │
    └── Tests/                       # 12 Modular TDD Test Suites
        ├── 1BasicConstructorsTest.h
        ├── 2InsertContainsTest.h
        ├── 3EraseValueTest.h
        ├── 4InitializerListTest.h
        ├── 5CopyConstructorTest.h
        ├── 6AssignmentOperatorTest.h
        ├── 7IteratorTest.h
        ├── 8IteratorStlCompatibilityTest.h
        ├── 9FindTest.h
        ├── 10UpperAndLowerBoundsTest.h
        ├── 11EraseIteratorTest.h
        ├── 12TimeLimitTest.h
        └── Fixtures/                # CustomAsserts test helpers
```

---

## 📋 Method Reference & Complexity

| Method | Signature | Time Complexity | Description |
| :--- | :--- | :--- | :--- |
| `insert` | `void insert(int val)` | `O(log N)` | Inserts unique value into the balanced tree |
| `contains` | `bool contains(int val)` | `O(log N)` | Checks whether value exists in the set |
| `find` | `iterator find(int val)` | `O(log N)` | Finds element; returns `end()` if absent |
| `erase(val)` | `void erase(int val)` | `O(log N)` | Removes element by value |
| `erase(it)` | `void erase(iterator it)` | `O(log N)` / `O(1)` amort. | Removes node by iterator position |
| `lower_bound` | `iterator lower_bound(int val)` | `O(log N)` | Iterator to first element `>= val` |
| `upper_bound` | `iterator upper_bound(int val)` | `O(log N)` | Iterator to first element `> val` |
| `size` | `size_t size()` | `O(1)` | Number of elements in the set |
| `empty` | `bool empty()` | `O(1)` | Returns true if set contains no elements |
| `begin` | `iterator begin()` | `O(log N)` | Iterator to minimum key in the tree |
| `end` | `iterator end()` | `O(1)` | Sentinel end iterator (`nullptr`) |
| `operator=` | `Set& operator=(const Set&)` | `O(N)` | Deep tree copy assignment |
| `operator==` | `bool operator==(const Set&, ...)` | `O(N)` | Element-by-element equality check |

---

## 🧪 Unit Testing (TDD)

The set passes **12 unit test suites**:
1. Default construction and empty state verification.
2. Value insertion (`insert`) and membership lookup (`contains`).
3. Deletion (`erase(val)`) across leaf nodes, nodes with 1 child, and nodes with 2 children.
4. Construction via `std::initializer_list<int>`.
5. Deep copy construction via BFS queue traversal.
6. Copy assignment operator with self-assignment guard.
7. Bidirectional iterator traversal: `++`, `--`, dereferencing.
8. **Standard algorithm interoperability** (`std::find`, `std::count`, `std::distance`).
9. `find()` behavior and `end()` returns for absent elements.
10. `lower_bound()` and `upper_bound()` boundary accuracy.
11. Iterator-based erasure `erase(iterator)`.
12. **`TimeLimitTest`**: high-throughput stress test confirming strict logarithmic `O(log N)` scaling.

---

## ⚙️ Build and Execution

1. Open `Set.sln` in **Visual Studio 2022**.
2. Select configuration **Debug / x64** or **Release / x64**.
3. Compile (`Ctrl + Shift + B`) and run tests (`Ctrl + F5`).
4. Output when all suites pass:
   ```text
   All tests passed!
   ```

---

## 👨‍💻 Author

- **Davit Bakhshyan ([DavitBakh](https://github.com/DavitBakh))**
