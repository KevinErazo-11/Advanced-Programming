/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

 #include <fstream>
 #include <iostream>
 #include <queue>
 #include <set>
 #include <string>
 #include <unordered_set>
 
 std::string kYourName = "Kevin Erazo"; // Don't forget to change this!
 
 /**
  * Takes in a file name and returns a set containing all of the applicant names as a set.
  *
  * @param filename  The name of the file to read.
  *                  Each line of the file will be a single applicant's name.
  * @returns         A set of all applicant names read from the file.
  *
  * @remark Feel free to change the return type of this function (and the function
  * below it) to use a `std::unordered_set` instead. If you do so, make sure
  * to also change the corresponding functions in `utils.h`.
  */

std::set<std::string> get_applicants(std::string filename) {
    std::set<std::string> applicants;
    std::ifstream file(filename);
    std::string name;
    
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return applicants;
    }

    while (std::getline(file, name)) {
        applicants.insert(name);
    }

    return applicants;
}

 /**
  * Takes in a set of student names by reference and returns a queue of names
  * that match the given student name.
  *
  * @param name      The returned queue of names should have the same initials as this name.
  * @param students  The set of student names.
  * @return          A queue containing pointers to each matching name.
  */
 
 std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  
  if (name.size() < 2) return matches; 
  
  char first_initial = name[0];
  char last_initial = name[name.find(' ') + 1];

  for (const std::string& student : students) {
      if (student.size() < 2) continue; 
      char student_first_initial = student[0];
      char student_last_initial = student[student.find(' ') + 1];

      if (student_first_initial == first_initial && student_last_initial == last_initial) {
          matches.push(&student);
      }
  }

  return matches;
}
 
 /**
  * Takes in a queue of pointers to possible matches and determines the one true match!
  *
  * You can implement this function however you'd like, but try to do something a bit
  * more complicated than a simple `pop()`.
  *
  * @param matches The queue of possible matches.
  * @return        Your magical one true love.
  *                Will return "NO MATCHES FOUND." if `matches` is empty.
  */

 std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
      return "NO MATCHES FOUND.";
  }
  
  if (matches.size() == 1) {
      return *matches.front();
  }
  
  matches.pop(); // Descarta el primero (para hacerlo más interesante)
  
  return *matches.front(); 
}
 
 /* #### Please don't remove this line! #### */
 #include "autograder/utils.hpp"