#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "flight.hpp"

#include <list>
#include <string>

using namespace std;

void cadastrarAstronauta(list<Astronaut>& astronauts);

void cadastrarVoo(list<Flight>& flights);

void adicionarAstronautaEmVoo(list<Astronaut>& astronauts, list<Flight>& flights);

void removerAstronautaDeVoo(list<Astronaut>& astronauts, list<Flight>& flights);

void lancarVoo(list<Astronaut>& astronauts, list<Flight>& flights);

void explodirVoo(list<Astronaut>& astronauts, list<Flight>& flights);

void finalizarVoo(list<Astronaut>& astronauts, list<Flight>& flights);

void listarVoos(const list<Flight>& flights);

void listarAstronautasMortos(const list<Astronaut>& astronauts);
        
#endif