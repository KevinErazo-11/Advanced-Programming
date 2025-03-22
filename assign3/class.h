#ifndef CAR_H
#define CAR_H

class Car {
private:
    int speed;
    float fuelLevel;
    void consumeFuel();

public:
    Car(); 
    Car(int startSpeed, float startFuel);

    int getSpeed() const; 
    void setSpeed(int newSpeed); 
    void refuel(float amount); 
    void drive(); 
};

#endif