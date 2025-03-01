/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

 #include <algorithm>
 #include <fstream>
 #include <iostream>
 #include <sstream>
 #include <string>
 #include <vector>
 
 const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
 const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";
 
 /**
  * Represents a course a student can take in ExploreCourses.
  * Definimos los campos: title, number_of_units y quarter, todos de tipo std::string.
  */
 struct Course {
   std::string title;
   std::string number_of_units;
   std::string quarter;
 };
 
 /**
  * Actualizamos las firmas de las funciones para pasar el vector por referencia.
  *
  * parse_csv: se encarga de llenar el vector de cursos (por ello se pasa por referencia).
  * write_courses_offered: escribe y elimina de 'courses' los cursos que están ofrecidos.
  * write_courses_not_offered: escribe los cursos no ofrecidos (se pasa como const referencia ya que solo se lee).
  */
 void parse_csv(const std::string &filename, std::vector<Course>& courses);
 void write_courses_offered(std::vector<Course>& courses);
 void write_courses_not_offered(const std::vector<Course>& courses);
 
 /**
  * Note:
  * We need to #include utils.cpp _after_ we declare the Course struct above
  * so that the code inside utils.cpp knows what a Course is.
  * Recall that #include literally copies and pastes file contents.
  */
 #include "utils.cpp"
 
 /**
  * This function should populate the `courses` vector with structs of type
  * `Course`. We want to create these structs with the records in the courses.csv
  * file, where each line is a record!
  *
  * Hints:
  * 1) Take a look at the split function we provide in utils.cpp
  * 2) Each LINE is a record! *this is important, so we're saying it again :>)*  
  * 3) The first line in the CSV defines the column names, so you can ignore it!
  *
  * @param filename The name of the file to parse.
  * @param courses  A vector of courses to populate.
  */
 void parse_csv(const std::string &filename, std::vector<Course>& courses) {
     std::ifstream file(filename);
     std::string line;
 
     // Salta la primera línea (encabezado)
     std::getline(file, line);
 
     while (std::getline(file, line)) {
         // Dividimos la línea en tres partes: título, número de unidades y trimestre
         std::vector<std::string> tokens = split(line, ','); // Utilizamos la función split para separar la línea
 
         if (tokens.size() == 3) { // Asegurarse de que hay tres elementos
             Course c;
             c.title = tokens[0];
             c.number_of_units = tokens[1];
             c.quarter = tokens[2];
 
             // Añadir el curso al vector
             courses.push_back(c);
         }
     }
 }
 
 /**
  * This function has TWO requirements.
  *
  * 1) Write the courses that are offered to the file
  * "student_output/courses_offered.csv"
  *
  * 2) Delete the courses that are offered from the `all_courses` vector.
  * IMPORTANT: do this after you write out to the file!
  *
  * HINTS:
  * 1) Keep track of the classes that you need to delete!
  * 2) Use the delete_elem_from_vector function we give you!
  * 3) Remember to write the CSV column headers at the beginning of the output!
  *    See courses.csv for reference.
  *
  * @param all_courses A vector of all courses gotten by calling `parse_csv`.
  *                    This vector will be modified by removing all offered courses.
  */
 void write_courses_offered(std::vector<Course>& courses) {
     std::ofstream file(COURSES_OFFERED_PATH);
     
     // Escribimos el encabezado
     file << "Title,Number of Units,Quarter" << std::endl;
 
     // Usamos un vector auxiliar para almacenar cursos a eliminar
     std::vector<Course> offered_courses;
 
     // Iteramos sobre los cursos y seleccionamos los ofrecidos
     for (auto it = courses.begin(); it != courses.end(); ) {
         if (it->quarter != "null") { // Si el curso está ofrecido
             file << it->title << "," << it->number_of_units << "," << it->quarter << std::endl;
             offered_courses.push_back(*it);
             it = courses.erase(it); // Eliminar curso de courses
         } else {
             ++it; // Continuar al siguiente curso
         }
     }
 }
 
 /**
  * This function writes the courses NOT offered to the file
  * "student_output/courses_not_offered.csv".
  *
  * This function is ALWAYS called after the `write_courses_offered` function.
  * `unlisted_courses` will trivially contain classes that are not offered
  * since you delete offered classes from `all_courses` in the
  * `write_courses_offered` function.
  *
  * HINT: This should be VERY similar to `write_courses_offered`
  *
  * @param unlisted_courses A vector of courses that are not offered.
  */
 void write_courses_not_offered(const std::vector<Course>& courses) {
     std::ofstream file(COURSES_NOT_OFFERED_PATH);
     
     // Escribimos el encabezado
     file << "Title,Number of Units,Quarter" << std::endl;
 
     // Iteramos sobre los cursos no ofrecidos
     for (const auto& c : courses) {
         file << c.title << "," << c.number_of_units << "," << c.quarter << std::endl;
     }
 }
 

 int main() {
  // Verificación sencilla de la estructura
  if (std::string().empty() || std::string().empty() || std::string().empty()) {
    std::cerr << "Course struct is not correctly defined!" << std::endl;
    return 1;  // Terminar si la estructura no está bien definida
  }

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  // Uncomment for debugging...
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}

 