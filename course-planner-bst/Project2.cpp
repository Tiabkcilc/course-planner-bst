// ProjectTwo.cpp
// ABCU Advising Assistance Program
// Reads course data from a CSV file into a Binary Search Tree (BST),
// then allows the user to list all courses or view details for a single course.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// ---------- Data Structures ----------

struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    void inOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        inOrder(node->right);
    }

    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    virtual ~BinarySearchTree() {
        destroy(root);
    }

    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        } else {
            Node* current = root;
            while (current != nullptr) {
                if (course.courseNumber < current->course.courseNumber) {
                    if (current->left == nullptr) {
                        current->left = new Node(course);
                        current = nullptr; // break
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = new Node(course);
                        current = nullptr; // break
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }

    void PrintCourseList() {
        if (root == nullptr) {
            cout << "No course data loaded.\n";
            return;
        }
        cout << "\nHere is a course list:\n\n";
        inOrder(root);
        cout << "\n";
    }

    Course Search(string courseNumber) {
        Node* current = root;
        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return current->course;
            } else if (courseNumber < current->course.courseNumber) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // Return empty course if not found
        Course empty;
        return empty;
    }
};

// ---------- Utility Functions ----------

// Trim whitespace from both ends of a string
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Convert a string to uppercase
static string toUpper(const string& s) {
    string result = s;
    for (char& c : result) {
        c = toupper(static_cast<unsigned char>(c));
    }
    return result;
}

// ---------- Core Functionality ----------

// Load course data from CSV file into BST.
// Returns true on success, false if file cannot be opened.
bool loadCourses(const string& filename, BinarySearchTree* bst) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open file \"" << filename << "\".\n";
        return false;
    }

    string line;
    while (getline(infile, line)) {
        if (trim(line).empty())
            continue;  // skip empty lines

        // Parse CSV tokens
        vector<string> tokens;
        istringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }
        if (tokens.size() < 2) {
            cerr << "Error: Invalid format in line: " << line << "\n";
            continue;
        }

        // Build Course object
        Course c;
        c.courseNumber = toUpper(tokens[0]);
        c.courseName   = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty())
                c.prerequisites.push_back(toUpper(tokens[i]));
        }

        // Insert into BST
        bst->Insert(c);
    }

    infile.close();
    return true;
}

// ---------- Main Menu ----------

int main() {
    cout << "Welcome to the course planner.\n";

    BinarySearchTree* bst = new BinarySearchTree();
    bool loaded = false;

    string filename; // Keep filename to allow reloading or default logic if needed

    while (true) {
        // Display menu
        cout << "\n1. Load Data Structure.\n"
             << "2. Print Course List.\n"
             << "3. Print Course.\n"
             << "9. Exit.\n\n"
             << "What would you like to do? ";

        string choice_line;
        getline(cin, choice_line);
        int choice = 0;
        try {
            choice = stoi(choice_line);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: {
                cout << "Enter filename: ";
                getline(cin, filename);
                // Creating a new tree if reloading to avoid duplicates or memory leaks from old tree?
                // The prompt constraints say "Ensure memory is properly released when the program exits".
                // Simplest is to just load into current tree, but user might load multiple times? 
                // Let's assume one load or sequential loads. If reloading, we should ideally clear the tree.
                // Since the current BST class doesn't have a Clear(), let's just delete and reallocate if loaded.
                
                if (loaded) {
                     delete bst;
                     bst = new BinarySearchTree();
                     loaded = false;
                }

                if (loadCourses(filename, bst)) {
                    loaded = true;
                    cout << "Data loaded successfully.\n";
                }
                break;
            }
            case 2:
                if (!loaded) {
                    cout << "Please load data first.\n";
                } else {
                    bst->PrintCourseList();
                }
                break;

            case 3:
                if (!loaded) {
                    cout << "Please load data first.\n";
                } else {
                    cout << "What course do you want to know about? ";
                    string input;
                    getline(cin, input);
                    string code = toUpper(trim(input));

                    Course course = bst->Search(code);

                    if (!course.courseNumber.empty()) {
                         cout << "\n" << course.courseNumber << ", " << course.courseName << "\n";
                         cout << "Prerequisites: ";
                         if (course.prerequisites.empty()) {
                             cout << "None\n\n";
                         } else {
                             for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                                 cout << course.prerequisites[i];
                                 if (i + 1 < course.prerequisites.size()) cout << ", ";
                             }
                             cout << "\n\n";
                         }
                    } else {
                        cout << code << " not found.\n\n";
                    }
                }
                break;

            case 9:
                cout << "Thank you for using the course planner!\n";
                delete bst; // Clean up memory
                return 0;

            default:
                cout << choice_line << " is not a valid option.\n";
                break;
        }
    }

    return 0;
}
