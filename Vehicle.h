#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>


class vehicle {

protected:

    std::string name;

    std::map<short, short> engine;

    std::string color;

    short wheels;
    float battery;
    short mass;
    short breaks;

    short max_speed;

public:

    vehicle(std::string name, std::map<short, short> engine, std::string color, short wheels, float battery, short mass, short breaks, short max_speed) {
        this->name = name; this->engine = engine; this->color = color; this->wheels = wheels; this->battery = battery; this->mass = mass; this->breaks = breaks; this->max_speed = max_speed;
    }

    vehicle() { name = "NaN"; color = "NaN"; wheels = 0; battery = 0.0; mass = 0; breaks = 0; max_speed = 0; }



    void accelerate(short NrEngine, int seconds) {
        auto accelerateSpeed = engine.find(NrEngine)->second * seconds;
        if (accelerateSpeed < max_speed) {
            std::cout << "Vehicle " << name << " acceleration of " << std::to_string(seconds) << " seconds ";
            std::cout << "reached speed of " << std::to_string(accelerateSpeed / 10) << "km/h" << std::endl;
        }
        else {
            std::cout << "Vehicle " << name << " acceleration of " << std::to_string(seconds) << " seconds ";
            std::cout << "reached max speed of " << std::to_string(max_speed) << "km/h" << std::endl;
        }
    }

    void registrateVehicle() {
        std::cout << "Vehicle " << name << " was registred as Vehicle type" << std::endl;
    }

    void reachTopSpeed() {
        std::cout << "Vehicle " << name << " reached top speed " << std::to_string(max_speed) << "km/h" << std::endl;
    }

    void useBreaks() {
        std::cout << "vehicle " << name << " use breaks" << std::endl;
    }

    void startEngine() {
        if (engine.empty()) {
            std::cout << "Vehicle " << name << " do not have an engine" << std::endl;
            return;
        }
        std::cout << "Vehicle " << name << " Engine started" << std::endl;
    }

    void stopEngine() {
        if (engine.empty()) {
            std::cout << "Vehicle " << name << " do not have an engine" << std::endl;
            return;
        }
        std::cout << "Vehicle " << name << " engine stopped" << std::endl;
    }



    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    void setEngine(short NrEngine, short power) {
        engine.insert(std::map<short, short>::value_type(NrEngine, power));
    }

    std::map<short, short> getEngine() {
        return engine;
    }

    void setColor(std::string ThisColor) {
        this->color = ThisColor;
    }

    std::string getColor() {
        return color;
    }

    void setWheels(short ThisWheels) {
        this->wheels = ThisWheels;
    }

    short getWheels() {
        return wheels;
    }

    void setBattery(float ThisBattery) {
        this->battery = ThisBattery;
    }

    float getBattery() {
        return battery;
    }

    void setMass(short ThisMass) {
        this->mass = ThisMass;
    }

    short getMass() {
        return mass;
    }

    void setMaxSpeed(short ThisMaxSpeed) {
        this->max_speed = ThisMaxSpeed;
    }

    short getMaxSpeed() {
        return max_speed;
    }

};