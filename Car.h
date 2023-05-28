#pragma once
#include "Vehicle.h"
#include <windows.h> 


class car : public vehicle {

private:

    std::string body;

    std::vector<std::string> electro_systems;

public:

    car(std::string name, std::map<short, short> engine, std::string color, short wheels, float battery, short mass, short breaks, short max_speed, std::string body, std::vector<std::string> electro_systems)
        : vehicle(name, engine, color, wheels, battery, mass, breaks, max_speed)
    {
        this->body = body; this->electro_systems = electro_systems;
    }

    car(std::string name, std::map<short, short> engine, std::string color, short wheels, float battery, short mass, short breaks, short max_speed)
        : vehicle(name, engine, color, wheels, battery, mass, breaks, max_speed) {}

    car() { body = "NaN"; }



    void CheckElectroSystems() {
        for (std::string& val : electro_systems) {
            std::cout << "Checking vehicle " << name << " " << val << "..." << std::endl;
            Sleep(500);
        }
        std::cout << "Car " << name << " all systems allright" << std::endl;
    }

    void registrateVehicle() {
        std::cout << "Car " << name << " was registred as Car type" << std::endl;
    }

    void setElectoSystem(std::vector<std::string> ThisVector) {
        this->electro_systems = ThisVector;
    }

    std::vector<std::string> getElectroSystem() {
        return electro_systems;
    }

    void setBody(std::string ThisString) {
        if (ThisString != "sedan" && ThisString != "cuv") {
            std::cout << "incorect input";
            return;
        }
        else {
            this->body = ThisString;
        }
    }

    std::string getBody() {
        return body;
    }

};