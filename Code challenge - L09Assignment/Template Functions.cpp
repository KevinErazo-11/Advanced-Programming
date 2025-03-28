#include <iostream>
#include <concepts>

/*
Part 1: Basic Template Functions
    Create a template function called maxValue that takes two arguments of the same type and returns the maximum value.
    Test the function with different types, including int, double, and std::string.
*/
using namespace std;


template <typename T>
T maxValue1(T a, T b) {
    return (a > b) ? a : b;
}

/*
int main() {
    cout << maxValue(5, 10) << endl;          // Should print 10
    cout << maxValue(3.5, 2.1) << endl;       // Should print 3.5
    cout << maxValue(string("apple"), string("orange")) << endl; // Should print "orange"
}
*/



/*
Task 1.2: Overload a Template Function
    1: Create an overloaded version of the maxValue template that takes three parameters.
    2: Test the function with integers and floating-point numbers.
*/

template <typename T>
T maxValue2(const T& a, const T&b) { 
    return (a>b) ? a : b;
}

template <typename T>
T maxValue2(const T& a, const T&b, const T& c) {
    auto m = max(b,c);
    return (a>m) ? a : m;
}

/*
int main() {
    cout << maxValue(2, 6, 4) << endl;          // Should print 6
    cout << maxValue(2.5, 5.3, 1.2) << endl;    // Should print 5.3
}
*/


/* Part 2: Concepts
✅ Task 2.1: Create a Template with a Concept  
    1. Create a concept called Numeric that allows only integral or floating-point types. 
    2. Write a template function add that accepts two parameters constrained by the Numeric concept.
*/

#include <type_traits>
using namespace std;

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
T add(T a, T b) {
    return a + b;
}

/*
int main() {
    cout << add(3, 4) << endl;       // Imprime 7
    cout << add(2.5, 3.1) << endl;  // Imprime 5.6
    // cout << add("a", "b");       // Error de compilación
    return 0;
}
*/


// Part 3: Variadic Templates
// ✅ Task 3.1: Write a Variadic Template Function
// 1.	Write a variadic template function called printAll that accepts any number of parameters and prints them separated by spaces.
// 2.	Test it with different types of arguments.

template <typename T>
void printAll(T t) {
    std::cout << t << std::endl;
}

template <typename T, typename... Args>
void printAll(T t, Args... args) {
    std::cout << t << " ";
    printAll(args...);
}

/*
int main() {
    printAll(1, 2.5, "Hello", 'c'); // Should print: 1 2.5 Hello c
}
*/


/*
✅ Task 3.2: Variadic Template for Summation
    1.	Write a variadic template function called sum that returns the sum of all arguments.
    2.	Test it with integers and floating-point values.
*/

template <typename T>
T sum(T t) {
    return t;
}

template <typename T, typename... Args>
T sum(T t, Args... args) {
    return t + sum(args...);
}

/*
int main() {
    cout << sum(1, 2, 3, 4, 5) << endl;             // Should print 15
    cout << sum(1.1, 2.2, 3.3) << endl;             // Should print 6.6
}
*/


/*
Part 4: Template Metaprogramming
✅ Task 4.1: Compile-Time Factorial Using Templates
    1.	Write a recursive template that calculates the factorial of a number at compile time using template metaprogramming.
    2.	Test it with a constexpr value.
*/

#include <iostream>

template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr int value = 1;
};



/*
int main() {
    constexpr int result = Factorial<5>::value;
    std::cout << result << std::endl;  // Should print 120
}
*/


/*
✅ Task 4.2: Fibonacci Series Using Template Metaprogramming
    1.	Write a recursive template that calculates the nth Fibonacci number at compile time.
    2.	Test it with constexpr values.
*/

template <int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template <>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

/*
int main() {
    constexpr int result = Fibonacci<10>::value;
    std::cout << result << std::endl; // Should print 55
}
*/


int main() {
    std::cout << "------------------------" << std::endl;
    std::cout << "         PART 1         " << std::endl;
    std::cout << "------------------------" << std::endl;
    cout << maxValue1(5, 10) << endl;          // Should print 10
    cout << maxValue1(3.5, 2.1) << endl;       // Should print 3.5
    cout << maxValue1(string("apple"), string("orange")) << endl; // Should print "orange"

    std::cout << "Task 1.2:" << std::endl;
    cout << maxValue2(2, 6, 4) << endl;          // Should print 6
    cout << maxValue2(2.5, 5.3, 1.2) << endl;    // Should print 5.3
    std::cout << "\n" << std::endl;
    
    
    std::cout << "------------------------" << std::endl;
    std::cout << "         PART 2"          << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Task 2.1:" << std::endl;
    cout << add(3, 4) << endl;       // Imprime 7
    cout << add(2.5, 3.1) << endl;  // Imprime 5.6
    // cout << add("a", "b");       // Error de compilación
    std::cout << "\n" << std::endl;


    std::cout << "------------------------" << std::endl;
    std::cout << "         PART 3"          << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Task 3.1:" << std::endl;
    printAll(1, 2.5, "Hello", 'c'); // Should print: 1 2.5 Hello c

    std::cout << "Task 3.2:" << std::endl;
    cout << sum(1, 2, 3, 4, 5) << endl;             // Should print 15
    cout << sum(1.1, 2.2, 3.3) << endl;             // Should print 6.6
    std::cout << "\n" << std::endl;

    std::cout << "------------------------" << std::endl;
    std::cout << "         PART 4"          << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Task 4.1:" << std::endl;
    constexpr int result1 = Factorial<5>::value;
    std::cout << result1 << std::endl;  // Should print 120
        
    std::cout << "Task 4.2:" << std::endl;
    constexpr int result2 = Fibonacci<10>::value;
    std::cout << result2 << std::endl; // Should print 55

}