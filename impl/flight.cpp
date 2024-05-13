#include "../include/flight.hpp"
#include "../include/astronauta.hpp"
#include "../include/enum/flightStateEnum.hpp"

Flight::Flight(){};

Flight::Flight(std::string codigo, FlightStatus flightStatus, std::list<std::string> passageiros){
  this->codigo = codigo;
  this->flightStatus = flightStatus;
  this->passageiros = passageiros;
}

std::string Flight::getCodigo() { return this->codigo; }
FlightStatus Flight::getFlightStatus() { return this->flightStatus; } 
std::list<std::string>& Flight::getPassageiros() { return this->passageiros; }

void Flight::setCodigo(std::string codigo) { this->codigo = codigo; }
void Flight::setFlightStatus(FlightStatus flightStatus) {this->flightStatus = flightStatus;}