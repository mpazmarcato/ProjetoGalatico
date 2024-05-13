#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "astronauta.hpp"
#include "flight.hpp"
#include <list>
#include <string>

Astronaut* findAstronautByCPF(std::string cpf, std::list<Astronaut> astronauts);

void adicionarPassageiro(std::string cpf, Flight &flight);

void removerPassageiro(std::string cpf, Flight &flight);

void launch(Flight &flights, std::list<Astronaut> &astronauts); 

void explode(Flight &flights, std::list<Astronaut> &astronauts); 

void finish(Flight &flights, std::list<Astronaut> &astronauts);

void listFlights(std::list<Flight> flights, std::list<Astronaut> astronauts);

void listarAstronautasMortos(std::list<Flight> flights, std::list<Astronaut> astronauts);

#endif