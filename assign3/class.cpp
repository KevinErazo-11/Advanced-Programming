#include "class.h"
#include <iostream>

Car::Car() : speed(0), fuelLevel(100.0f) {}

Car::Car(int startSpeed, float startFuel) : speed(startSpeed), fuelLevel(startFuel) {}

int Car::getSpeed() const {
    return speed;
}

void Car::setSpeed(int newSpeed) {
    if (newSpeed >= 0) {
        speed = newSpeed;
    }
}

void Car::refuel(float amount) {
    fuelLevel += amount;
    if (fuelLevel > 100.0f) {
        fuelLevel = 100.0f;
    }
}

void Car::drive() {
    if (fuelLevel > 0) {
        std::cout << "Driving at " << speed << " km/h" << std::endl;
        consumeFuel();
    } else {
        std::cout << "Out of fuel!" << std::endl;
    }
}

void Car::consumeFuel() {
    fuelLevel -= speed * 0.05f;
    if (fuelLevel < 0) {
        fuelLevel = 0;
    }
}
