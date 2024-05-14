#include "astronauta.hpp"
#include "flight.hpp"
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
    if (!astronauta.isDisponivel()) {
        std::cout << "Astronauta não está disponível para ser adicionado como passageiro." << std::endl;
        return;
    }

    if (astronauta.isDead()) {
        std::cout << "Astronauta está marcado como morto e não pode ser adicionado como passageiro." << std::endl;
        return;
    }

    passageiros.push_back(astronauta);
    std::cout << "Astronauta adicionado ao voo com sucesso!" << std::endl;
}

void Flight::removerPassageiro(const Astronaut& astronauta) {
    auto it = std::find_if(passageiros.begin(), passageiros.end(), [&](const Astronaut& a) {
        return a.getCPF() == astronauta.getCPF();
    });

    if (it != passageiros.end()) {
        it->setDisponivel(true);
        passageiros.erase(it);
        std::cout << "Astronauta removido do voo com sucesso!" << std::endl;
    } else {
        std::cout << "Astronauta não encontrado neste voo." << std::endl;
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
        for (auto& astronauta : astronauts) {
            astronauta.setVivo(false);
            astronauta.setDisponivel(false);
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

void Flight::listarAstronautasMortos(std::list<Flight> flights) const {
  if (!astronautasMortos.empty()) {
    for (auto& astronaut : astronautasMortos) {
      std::cout << "CPF: " << astronaut.getCPF() << std::endl;
      std::string cpf = astronaut.getCPF();
      std::cout << "Nome: " << astronaut.getNome() << std::endl;
      std::cout << "Voos em que o astronauta participou:\n";
      for (const auto& flight : flights) {
        if (flight.getStatus() == Flight::FINISHED_FAILURE) {
          for (auto& passenger : flight.getPassageiros()) {
            if (passenger.getCPF() == cpf) {
                std::cout << "  - Código do voo: " << flight.getCodigo() << std::endl;
                break;
            }
          }
        }
      }
    }
  }
} 
