#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <list>
#include "astronauta.hpp"
#include "enum/flightStateEnum.hpp"

class Flight {
private:
    std::string codigo;
    FlightStatus flightStatus;
    std::list<std::string> passageiros;

public:
    Flight();
    Flight(std::string codigo, FlightStatus flightStatus, std::list<std::string> passageiros);

    std::string getCodigo();
    FlightStatus getFlightStatus();
    std::list<std::string>& getPassageiros();

    void setCodigo(std::string codigo);
    void setFlightStatus(FlightStatus flightStatus);
};

#endif
  