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
    std::list<Astronaut> astronautasMortos;

public:
    Flight(std::string codigo);

    std::string getCodigo() const;
    Status getStatus() const;
    void adicionarPassageiro(Astronaut& astronauta);
    void removerPassageiro(Astronaut& astronauta);
    void launchFlight(std::list<Astronaut>& astronauts);
    void explode(std::list<Astronaut>& astronauts);
    void finish(Status finishStatus, std::list<Astronaut>& astronauts);
    const std::list<Astronaut>& getPassageiros() const;
    //void listarAstronautasMortos(std::list<Flight> flights) const;
    void listarAstronautasMortos(const std::list<Astronaut> astronauts);
};

#endif
