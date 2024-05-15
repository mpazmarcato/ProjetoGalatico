#include "../include/astronauta.hpp"
#include "../include/flight.hpp"
#include <iostream>
#include <algorithm>

Flight::Flight(std::string codigo) : codigo(codigo), status(PLANNED) {}

std::string Flight::getCodigo() const {
    return codigo;
}

Flight::Status Flight::getStatus() const {
    return status;
}

void Flight::adicionarPassageiro(Astronaut& astronauta) {
    passageiros.push_back(astronauta);
    std::cout << "Astronauta adicionado ao voo com sucesso!" << std::endl;
}

void Flight::removerPassageiro(Astronaut& astronauta) {
    auto it = std::find_if(passageiros.begin(), passageiros.end(), [&](const Astronaut& a) {
        return a.getCPF() == astronauta.getCPF();
    });

    if (it != passageiros.end()) {
        passageiros.erase(it);
        std::cout << "Astronauta removido do voo com sucesso!" << std::endl;
    } 
}

void Flight::launchFlight(std::list<Astronaut>& astronauts) {
    if (status != PLANNED) {
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
        status = IN_PROGRESS;
        std::cout << "Voo lançado com sucesso!" << std::endl;
    } else {
        std::cout << "Voo não pode ser lançado devido a astronautas indisponíveis." << std::endl;
    }
}

void Flight::explode(std::list<Astronaut>& astronauts) {
    if (status == IN_PROGRESS) {
        status = FINISHED_FAILURE;
        std::string codigoVoo = getCodigo();
        for (auto& astronauta : astronauts) {
            astronauta.setVivo(false);
            astronauta.setDisponivel(false);
            astronauta.addVooParticipado(codigoVoo);
            astronautasMortos.push_back(astronauta);
        }
        std::cout << "Voo explodido com sucesso!" << std::endl;
    } else {
        std::cout << "Voo não pode ser explodido. Verifique o status do voo." << std::endl;
    }
}

void Flight::finish(Status finishStatus, std::list<Astronaut>& astronauts) {
    if (status == IN_PROGRESS) {
        status = finishStatus;
        std::string codigoVoo = getCodigo();
        for (auto& astronauta : astronauts) {
            astronauta.setVivo(true);
            astronauta.setDisponivel(true);
            astronauta.addVooParticipado(codigoVoo);
        }
        std::cout << "Voo finalizado com sucesso!" << std::endl;
    } else {
        std::cout << "Voo não pode ser finalizado. Verifique o status do voo." << std::endl;
    }
}

const std::list<Astronaut>& Flight::getPassageiros() const {
    return passageiros;
}

void Flight::listarAstronautasMortos(std::list<Astronaut> astronauts) {
    for(auto& astronauta : astronauts){
        if (astronauta.isDead()){
            std::cout << "CPF: " << astronauta.getCPF() << std::endl;
            std::cout << "Nome: " << astronauta.getNome() << std::endl;
            std::cout << "Voos em que o astronauta participou: \n";
            for (auto& codigo : astronauta.getVoosParticipados()){
                std::cout << "  - Código do voo: " << codigo << std::endl;
            }
        }
    }
}
