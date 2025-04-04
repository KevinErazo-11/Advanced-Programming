/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

 #include <iostream>
 #include <string>
 
 class User
 {
 public:
   User(const std::string& name);
   void add_friend(const std::string& name);
   std::string get_name() const;
   size_t size() const;
   void set_friend(size_t index, const std::string& name);
 
   /** 
    * STUDENT TODO:
    * Your custom operators and special member functions will go here!
    */
   
   // Destructor
   ~User();
 
   // Copy constructor
   User(const User& other);
 
   // Copy assignment operator
   User& operator=(const User& other);
 
   // Deleted move constructor and move assignment operator
   User(User&&) = delete;
   User& operator=(User&&) = delete;
 
   // Operator << for printing
   friend std::ostream& operator<<(std::ostream& os, const User& user);
 
   // Operator += for mutual friendship
   User& operator+=(User& rhs);
 
   // Operator < for ordering (by name)
   bool operator<(const User& rhs) const;
 
 private:
   std::string _name;
   std::string* _friends;
   size_t _size;
   size_t _capacity;
 };
 