/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include "class.h"
#include <iostream>
void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  
  Car myCar(60, 50.0f);
  std::cout << "Initial speed: " << myCar.getSpeed() << " km/h" << std::endl;
  myCar.drive();
  myCar.setSpeed(80);
  myCar.drive();
  myCar.refuel(30.0f);
  std::cout << "Refueled and ready to go!" << std::endl;
  myCar.drive();

}

