# course-planner-bst
### Algorithms and Data Structures Narrative

**Artifact Description**
The artifact selected for the Algorithms and Data Structures category is the "ABCU Advising Assistance Program," a console-based application originally developed in CS 260: Data Structures and Algorithms. Written in C++, the program is designed to load university course data from a CSV file and allow users to either print a sorted alphanumeric list of courses or search for specific course details and prerequisites.

**Justification for Inclusion**
I selected this artifact because it demonstrates the critical difference between using a library and understanding the underlying logic of data organization. In the original iteration, the application relied heavily on standard libraries (`std::vector` and `std::sort`) to organize data. While functional, this approach masked the computational cost of sorting.
* **Skills Showcased:** By refactoring this artifact, I demonstrated the ability to implement complex data structures manually. Specifically, I replaced the linear containers with a custom Binary Search Tree (BST). This required advanced C++ skills, including direct memory management, pointer manipulation, and recursive algorithm design.
* **Improvements:** The transition to a BST significantly improved the theoretical efficiency of the application. The original program required an $O(N \log N)$ sorting operation every time the user requested a course list. The enhanced BST version sorts data naturally upon insertion; this means the data is always sorted, allowing the "Print List" feature to run in linear $O(N)$ time via an in-order traversal.



**Course Outcomes Analysis**
With this enhancement, I have fully met the course outcome to design and evaluate computing solutions that solve a given problem using algorithmic principles and computer science practices and standards appropriate to its solution, while managing the trade-offs involved in design choices.
* **Evaluation:** I successfully evaluated the trade-off between implementation time and runtime efficiency. While the `std::sort` method was faster to write, the BST implementation is more efficient for large datasets where the list is accessed frequently.
* **Outcome Updates:** My plan for this outcome remained consistent throughout the development process. The successful implementation of the BST confirms that I can apply algorithmic principles to optimize software performance, fulfilling the core requirements of this module.

**Reflection on the Process**
Enhancing this artifact highlighted the precision required when working with memory-managed languages like C++.
* **Challenges:** The primary challenge I faced was managing the pointers within the `Node` structure. Unlike the standard vector which handles memory automatically, building a BST required me to manually allocate and link nodes. Debugging the recursive logic for the `Insert` and `InOrderTraversal` functions was difficult; specifically, ensuring that the base cases were correct to prevent infinite recursion or null pointer exceptions.
* **Learning:** This process reinforced my understanding of "Big O" notation in a practical setting. Seeing the list print instantly without a sort function call validated the theoretical efficiency of the tree structure. It also emphasized the importance of encapsulation, by hiding the complex tree logic behind a clean public API (`tree->Insert()`), I kept the `main()` function clean and readable, adhering to good software engineering practices.
