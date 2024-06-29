#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>
#include <list>
#include "astronauta.hpp" 

class Flight {
public:
    enum Status {
        PLANNED,
        IN_PROGRESS,
        FINISHED_SUCCESS,
        FINISHED_FAILURE
    };

private:
    std::string codigo;
    std::list<Astronaut> passageiros;
    Status status;

public:
    Flight(std::string codigo);
    std::string getCodigo() const;
    Status getStatus() const;
    const std::list<Astronaut>& getPassageiros() const;

    void setStatus(Status newStatus);
    void addAstronaut(const Astronaut& astronaut);
    void removeAstronaut(const std::string& astronautName);
    void listPassengers() const;
};

#endif