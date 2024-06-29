#include "../include/astronauta.hpp"
#include "../include/flight.hpp"
#include <iostream>
#include <algorithm>

Flight::Flight(std::string codigo)
    : codigo(codigo), status(PLANNED) {
    // Constructor initialization
}

std::string Flight::getCodigo() const {
    return codigo;
}

Flight::Status Flight::getStatus() const {
    return status;
}

void Flight::setStatus(Status newStatus) {
    status = newStatus;
}

const std::list<Astronaut>& Flight::getPassageiros() const {
    return passageiros;
}

void Flight::addAstronaut(const Astronaut& astronaut) {
    passageiros.push_back(astronaut);
}

void Flight::removeAstronaut(const std::string& cpf) {
    auto it = std::find_if(passageiros.begin(), passageiros.end(),
                           [&cpf](const Astronaut& astronaut) {
                               return astronaut.getCPF() == cpf;
                           });

    if (it != passageiros.end()) {
        passageiros.erase(it);
    } else {
        std::cout << "Astronauta não encontrado neste voo." << std::endl;
    }
}

void Flight::listPassengers() const {
    std::cout << "Passageiros do voo " << codigo << ":" << std::endl;
    for (const auto& astronaut : passageiros) {
        std::cout << "- " << astronaut.getNome() << std::endl;
    }
}




