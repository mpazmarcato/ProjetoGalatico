#include <iostream>
#include "../include/sistema.hpp"
#include "../include/enum/flightStateEnum.hpp"
#include "../include/astronauta.hpp"
#include "../include/flight.hpp"

Astronaut* findAstronautByCPF(std::string cpf, std::list<Astronaut> astronauts) {
    for (auto& astronaut : astronauts) {
      if (astronaut.getCPF() == cpf) {
        return &astronaut;
      }
    }
    return nullptr;
}


void adicionarPassageiro(std::string cpf, Flight &flight) {
    if (flight.getFlightStatus() == PLANNED) {  
        flight.getPassageiros().push_back(cpf);
        std::cout << "Astronauta adicionado ao voo com sucesso!" << std::endl;
    }
}

void removerPassageiro(std::string cpf, Flight &flight) {
    if (flight.getFlightStatus() == PLANNED) {  
        flight.getPassageiros().remove(cpf);
        std::cout << "Astronauta removido do voo com sucesso!" << std::endl;
    }
}

void launch(Flight &flight, std::list<Astronaut> &astronauts) {
    if (flight.getFlightStatus() != PLANNED) {
        std::cout << "Voo não pode ser lançado. Verifique se o voo está planejado." << std::endl;
        return;
    }

    if (astronauts.empty()) {
        std::cout << "Voo não pode ser lançado. Verifique se há astronautas." << std::endl;
        return;
    }

    bool allAstronautsAvailable = true;

    for (auto& astronaut : astronauts) {
        if (!astronaut.isDisponivel()) {
            std::cout << "Astronauta " << astronaut.getNome() << " não está disponível para a missão." << std::endl;
            allAstronautsAvailable = false;
            break;
        }
    }

    if (allAstronautsAvailable) {
        for (auto& astronaut : astronauts) {
            astronaut.setDisponivel(false);
        }
        flight.setFlightStatus(IN_PROGRESS); 
        std::cout << "Voo lançado com sucesso!" << std::endl;
    } else {
        std::cout << "Voo não pode ser lançado." << std::endl;
    }
}

void explode(Flight &flight, std::list<Astronaut> &astronauts) {
    if (flight.getFlightStatus() == IN_PROGRESS) {
        for (auto& astronauta : astronauts) {            
            astronauta.setDisponivel(false);
            astronauta.setAstronautStatus(DEAD);
        }
        flight.setFlightStatus(FINISHED_FAILURE);
        std::cout << "Voo explodido com sucesso!" << std::endl;
    } else {
        std::cout << "Voo não pode ser explodido. Verifique o status do voo." << std::endl;
    }
}


void finish(Flight &flight, std::list<Astronaut> &astronauts) {
    if (flight.getFlightStatus() == IN_PROGRESS) {
        for (auto& astronauta : astronauts) {            
            astronauta.setDisponivel(true);
        }
        flight.setFlightStatus(FINISHED_SUCCESS);
        std::cout << "Voo finalizado com sucesso!" << std::endl;
    } else {
        std::cout << "Voo não pode ser finalizado. Verifique o status do voo." << std::endl;
    }
}


void listFlights(std::list<Flight> flights, std::list<Astronaut> astronauts) {
    std::cout << "Voos Planejados:" << std::endl;
    bool hasPlannedFlights = false;
    for (auto& flight : flights) {
        if (flight.getFlightStatus() == FlightStatus::PLANNED) {
            std::cout << "  Código: " << flight.getCodigo() << std::endl;
            std::cout << "  Passageiros: ";
            if (flight.getPassageiros().empty()) {
                std::cout << "Nenhum passageiro registrado." << std::endl;
            } else {
                for (auto& cpf : flight.getPassageiros()) {
                    Astronaut* astronauta = findAstronautByCPF(cpf, astronauts);
                    std::cout << astronauta->getNome() << " (CPF: " << astronauta->getCPF() << "), ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            hasPlannedFlights = true;
        }
    }
    if (!hasPlannedFlights) {
        std::cout << "Nenhum voo planejado." << std::endl;
    }

    std::cout << "Voos em Progresso:" << std::endl;
    bool hasInProgressFlights = false;
    for (auto& flight : flights) {
        if (flight.getFlightStatus() == FlightStatus::IN_PROGRESS) {
            std::cout << "  Código: " << flight.getCodigo() << std::endl;
            std::cout << "  Passageiros: ";
            if (flight.getPassageiros().empty()) {
                std::cout << "Nenhum passageiro registrado." << std::endl;
            } else {
                for (auto& cpf : flight.getPassageiros()) {
                    Astronaut* astronauta = findAstronautByCPF(cpf, astronauts);
                    std::cout << astronauta->getNome() << " (CPF: " << astronauta->getCPF() << "), ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            hasInProgressFlights = true;
        }
    }
    if (!hasInProgressFlights) {
        std::cout << "Nenhum voo em progresso." << std::endl;
    }

    std::cout << "Voos Finalizados:" << std::endl;
    bool hasFinishedFlights = false;
    for (auto& flight : flights) {
        if (flight.getFlightStatus() == FlightStatus::FINISHED_SUCCESS || flight.getFlightStatus() == FlightStatus::FINISHED_FAILURE) {
            std::cout << "  Código: " << flight.getCodigo() << std::endl;
            std::cout << "  Status: " << (flight.getFlightStatus() == FlightStatus::FINISHED_SUCCESS ? "Finalizado com sucesso" : "Finalizado com falha") << std::endl;
            std::cout << "  Passageiros: ";
            if (flight.getPassageiros().empty()) {
                std::cout << "Nenhum passageiro registrado." << std::endl;
            } else {
                for (auto& cpf : flight.getPassageiros()) {
                    Astronaut* astronauta = findAstronautByCPF(cpf, astronauts);
                    std::cout << astronauta->getNome() << " (CPF: " << astronauta->getCPF() << "), ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            hasFinishedFlights = true;
        }
    }
    if (!hasFinishedFlights) {
        std::cout << "Nenhum voo finalizado." << std::endl;
    }
}

// void listarAstronautasMortos(std::list<Astronaut> astronauts){
//     for(auto& astronauta : astronauts){
//         if (astronauta.getAstronautStatus() == DEAD){
//             std::cout << "CPF: " << astronauta.getCPF() << std::endl;
//             std::cout << "Nome: " << astronauta.getNome() << std::endl;
//             std::cout << "Voos em que o astronauta participou: \n";
//             for (auto& codigo : astronauta.getVoosParticipados()){
//                 std::cout << "  - Código do voo: " << codigo << std::endl;
//             }
//         }
//     }
// }

void listarAstronautasMortos(std::list<Flight> flights, std::list<Astronaut> astronauts) {
    for(auto& astronauta : astronauts) {
        if (astronauta.getAstronautStatus() == AstronautStatus::DEAD){
            std::cout << "CPF: " << astronauta.getCPF() << std::endl;
            std::cout << "Nome: " << astronauta.getNome() << std::endl;
            std::cout << "Voos em que o astronauta participou: \n";
              
            for (auto& flight : flights) {
                if (flight.getFlightStatus() == FlightStatus::FINISHED_FAILURE) {
                    for (auto& passenger : flight.getPassageiros()) {
                        if (passenger == astronauta.getCPF()) {
                            std::cout << "  - Código do voo: " << flight.getCodigo() << std::endl;
                            break;
                        }
                    }
                }
            }
        }
    }
}


