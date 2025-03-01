#include <iostream>
#include <tuple>
#include <string>

//Structured Binding (C++ 17)
std::tuple<std::string, std::string, std::string> getClassInfo(){
    std::string className = "I am " ;
    std::string buildingName = "using " ;
    std::string finish = "Structured Binding (C++ 17).";
    return {className, buildingName, finish};
}


int main(){
    //initial values
    int numOne = 11;
    double numTwo{11.1};
    std::string myString = "This is my string.";
    bool myBool(true);

    printf("--------------------------------------------------------\n");
    printf("Part 1: Variable Initialization:\n");
    std::cout << "An `int` with an initial value is: " << numOne << std::endl;
    std::cout << "A `double` with an initial value is: " << numTwo << std::endl;
    std::cout << "A `std::string` with an initial value: " << myString << std::endl;
    std::cout << "A `bool` with an initial value is: " << myBool << std::endl;

    printf("--------------------------------------------------------\n");

    //Declare a reference to a and use it to modify the value of the previously created variables.
    printf("Part 3: References\n");
    int& ref = numOne;
    ref = 10; // Assigning a new value through the reference
    printf("I assign 10 to ref, we also change the value of numOne (11)\n");
    std::cout << "\tPrint the values again to confirm changes: " << numOne << std::endl;

    double& ref1 = numTwo;
    ref1 = 5.5;
    printf("I assign 5.5 to ref1, we also change the value of numTwo (11.1)\n");
    std::cout << "\tPrint the values again to confirm changes: " << ref1 << std::endl;

    bool& ref2 = myBool;
    ref2 = false;
    printf("I assign false to ref2, we also change the value of myBool (true)\n");
    std::cout << "\tPrint the values again to confirm changes: " << ref2 << std::endl;

    printf("--------------------------------------------------------\n");


    //Part 4: Structured Binding
    auto [className, buildingName, finish] = getClassInfo();
    std::cout << "Print the unpacked values:\n" << className << buildingName << finish << std::endl;
    printf("--------------------------------------------------------\n");

    //Part 5: Identifying l-values and r-values

    a = 42; //l-value
    int x = a + b; // a and b are l-values, (a + b) is an r-value
    &a; // l-value
    std::string s = c + " World"; // c is an l-value, "World" is an r-value, (c + " World") is an r-value
    int& refX = x; // l-value reference
    int&& rref = 100; // r-value reference

    return 0;
}

