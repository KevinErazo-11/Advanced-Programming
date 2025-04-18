#include <iostream>
#include <vector>

/*
Move Semantics
Overview
In modern C++, move semantics is a powerful feature that allows efficient resource transfer between objects. It is especially useful when dealing with 
objects that manage dynamic memory or other heavy resources. In this lab, students will explore how move semantics work, understand the difference 
between copy and move operations, and implement move constructors and move assignment operators in their own classes.
By the end of the lab, students will have a concrete understanding of when and why move semantics matter, and how to apply them to write more efficient
and modern C++ code.

Part 1: Introduction to Copy vs. Move
✅ Task 1.1 Reading and Discussion
Read the following code snippet:
*/

/*
int main() {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = v1;        // Copy
    std::vector<int> v3 = std::move(v1); // Move

    std::cout << "v1 size: " << v1.size() << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;
    std::cout << "v3 size: " << v3.size() << std::endl;

    return 0;
} */

/*
Questions:

• What is the output of this program?
    v1 size: 0
    v2 size: 4
    v3 size: 4

• Why does v1.size() return 0 after the move?
    Because std::move(v1) transfers internal resources (memory) from v1 to v3. After the move, v1 remains in a valid but undefined state. 
    In the case of std::vector, this usually means that its size becomes 0.

• What does std::move do?
    std::move does not itself move. It only converts an object to an rvalue (of type “temporary”), which allows the move constructor or the
    move assignment operator to be invoked if available.

• Why is v1 still in a valid but unspecified state?
    Because the rules of the C++ standard say that after moving an object, it must be in a valid state to be destroyed, but its contents are 
    not guaranteed (for example, it may be empty or have null values).
*/


/*
Part 2: Implementing Move Semantics
✅ Task 2.1 Define a Simple Resource-Managing Class
Implement a class Buffer that manages a dynamically allocated array of integers.
*/
class Buffer {
    private:
        int* data;
        size_t size;
    
    public:
        Buffer(size_t s) : size(s), data(new int[s]) {
            std::cout << "Constructor called\n";
        }
    
        ~Buffer() {
            delete[] data;
            std::cout << "Destructor called\n";
        }
/*
✅ Task 2.2 Add Copy Constructor and Assignment
Implement the copy constructor and copy assignment operator
*/
        Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
            std::copy(other.data, other.data + other.size, data);
            std::cout << "Copy constructor called\n";
        }
        
        Buffer& operator=(const Buffer& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                data = new int[size];
                std::copy(other.data, other.data + size, data);
                std::cout << "Copy assignment called\n";
            }
            return *this;
        }

/*
✅ Task 2.3 Add Move Constructor and Assignment
Implement the move constructor and move assignment operator.
*/
        Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
            std::cout << "Move constructor called\n";
        }
        
        Buffer& operator=(Buffer&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
        
                other.data = nullptr;
                other.size = 0;
                std::cout << "Move assignment called\n";
            }
            return *this;
        }

    };


/*
Part 3: Using Your Class
✅ Task 3.1 Create Instances and Observe Behavior
Write a main function that uses the Buffer class:
*/

void performance_test();
    int main() {
        Buffer b1(100);
        Buffer b2 = b1;           // Should call copy constructor
        Buffer b3 = std::move(b1); // Should call move constructor
    
        Buffer b4(50);
        b4 = b2;                  // Should call copy assignment
        b4 = std::move(b2);       // Should call move assignment
        performance_test();
    }
/*
Questions: 
• What constructors and assignments are called and when? 
    During program execution, the constructor is called when b1 and b4 are created with a specific size. Then, the copy constructor
    is called when making Buffer b2 = b1, since a new object is being created by copying an existing one. When doing 
    Buffer b3 = std::move(b1), the move constructor is invoked, since b1 becomes an rvalue. Subsequently, when doing b4 = b2, the 
    copy assignment operator is called, and when doing b4 = std::move(b2), the move assignment operator is invoked. Each specific call
    allows us to observe how the different methods behave according to the type of operation being performed (copy or move).
• What happens to the source object after a move? 
    After performing a move operation, the source object remains in a valid but undefined state. This means that its resources 
    (e.g. dynamic memory in this case) have been transferred to the new object, and the source object no longer possesses them. 
    In practice, this means that the source object's pointers point to nullptr and its size is zero. Although it is still a valid 
    object (it can be destroyed without error), its contents are no longer useful, so it should not be actively used after the 
    std::move.
• What would happen if you didn’t define the move constructor/assignment?
    If neither the move constructor nor the move assignment operator were defined, the compiler would use the copy constructors as an 
    alternative even when using std::move. This would imply that instead of transferring resources, they would be copied, which is less 
    efficient, especially with large objects or objects that handle expensive resources. Also, in some cases where the resource type 
    cannot be safely copied (such as single pointers), the absence of move functions could cause compilation errors or undesired 
    behavior.

Part 4: Performance Comparison
✅ Task 3.1 Measure Performance
Wrap a loop around operations with large buffers (e.g., size 10,000,000) and measure time taken when copying vs. moving. Write down your findings.
Use for timing.
*/

#include <chrono>

void performance_test() {
    using namespace std::chrono;

    std::cout << "\n[Copy Test]\n";
    auto start_copy = high_resolution_clock::now();
    Buffer big1(10000000);
    Buffer big2 = big1;  // Copy
    auto end_copy = high_resolution_clock::now();
    std::cout << "Copy duration: " << duration_cast<milliseconds>(end_copy - start_copy).count() << " ms\n";

    std::cout << "\n[Move Test]\n";
    auto start_move = high_resolution_clock::now();
    Buffer big3 = std::move(big1); // Move
    auto end_move = high_resolution_clock::now();
    std::cout << "Move duration: " << duration_cast<milliseconds>(end_move - start_move).count() << " ms\n";
}



/*
Part 5: Summary
Questions
• What did you learn about move semantics?
    Move semantics allow transferring ownership of resources instead of duplicating them. This leads to more efficient memory usage and faster 
    operations, especially for objects that handle large or complex resources like dynamic memory.

• In what kinds of projects do you think this would matter?
    Move semantics are particularly important in:
    - Performance-critical applications (e.g., games, real-time systems).
    - Systems with large data handling (e.g., scientific simulations, media processing).
    - Resource-constrained environments (e.g., mobile or embedded systems).
    - Libraries and APIs that work with generic or dynamic content (like containers or smart pointers).

• What are some risks of using std::move incorrectly?
    - Accidentally moving from an object that you still plan to use, which can result in undefined behavior or logic bugs.
    - Forgetting to reset or handle the moved-from object, leading to issues like double deletion.
    - Not implementing move constructors/operators properly, which can lead to shallow copies, memory leaks, or crashes.
*/



