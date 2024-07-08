// sistema.cpp
#include <iostream>
#include <list>
#include <algorithm>
#include <limits>
#include "astronauta.hpp"
#include "flight.hpp"

using namespace std;

void cadastrarAstronauta(list<Astronaut>& astronauts) {
    string cpf, nome;
    int idade;
    bool cpfRepetido;

    do {
        cout << "CPF do astronauta (11 digitos numericos): ";
        cin >> cpf;
        if (cpf.length() != 11 || !all_of(cpf.begin(), cpf.end(), ::isdigit)) {
            cout << "CPF inválido. Por favor, insira um CPF com 11 dígitos numéricos.\n";
            continue;
        }
        cpfRepetido = false;
        for (const auto& astronauta : astronauts) {
            if (astronauta.getCPF() == cpf) {
                cout << "CPF já cadastrado. Por favor, insira um CPF diferente.\n";
                cpfRepetido = true;
                break; 
            }
        }
    } while (cpf.length() != 11 || !all_of(cpf.begin(), cpf.end(), ::isdigit) || cpfRepetido);

    do {
        cout << "Nome do astronauta: ";
        cin.ignore();
        getline(cin, nome);
        if (nome.empty()) {
            cout << "O nome não pode ser vazio. Por favor, insira um nome válido.\n";
            continue;
        }
        if (all_of(nome.begin(), nome.end(), ::isdigit)) {
            cout << "O nome não pode conter números. Por favor, insira um nome válido.\n";
            continue;
        }
    } while (nome.empty() || all_of(nome.begin(), nome.end(), ::isdigit));
    
    do { 
        cout << "Idade do astronauta: ";
        cin >> idade;
        if (cin.fail() || idade < 23 || idade > 90) {
            cout << "Idade inválida. Por favor, insira uma idade entre 23 e 90 anos.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (idade < 23 || idade > 90);

    Astronaut novoAstronauta(cpf, nome, idade);
    astronauts.push_back(novoAstronauta);
    
    cout << "Astronauta cadastrado com sucesso!" << endl;
}

void cadastrarVoo(list<Flight>& flights) {
    string codigo;
    do {
        cout << "Codigo do voo (1 letra maiúscula seguida de 3 dígitos, por exemplo, V001): ";
        cin >> codigo;

        auto it = find_if(flights.begin(), flights.end(), [&codigo](const Flight& voo) {
            return voo.getCodigo() == codigo;
        });

        if (codigo.length() != 4 || !isupper(codigo[0]) || !isdigit(codigo[1]) || !isdigit(codigo[2]) || !isdigit(codigo[3]) || it != flights.end()) {
            cout << "Código do voo inválido ou já existente. Deve conter exatamente 1 letra maiúscula seguida de 3 dígitos e ser único." << endl;
            continue; 
        }


        Flight novoVoo(codigo);
        flights.push_back(novoVoo);
        
        cout << "Voo cadastrado com sucesso!" << endl;
        break; 
    } while (true);
}

void adicionarAstronautaEmVoo(list<Astronaut>& astronauts, list<Flight>& flights) {
    if (flights.empty()) {
        cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
        return;
    }

    string cpf, codigoVoo;
    cout << "CPF do astronauta: ";
    cin >> cpf;

    auto astronauta = find_if(astronauts.begin(), astronauts.end(), [cpf](const Astronaut& a) {
        return a.getCPF() == cpf;
    });

    if (astronauta == astronauts.end()) {
        cout << "Astronauta não encontrado." << endl;
        return;
    }

    if (!astronauta->isVivo()) {
        cout << "Astronauta não disponível para ser adicionado como passageiro." << endl;
        return;
    }

    cout << "Código do voo: ";
    cin >> codigoVoo;

    auto voo = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& v) {
        return v.getCodigo() == codigoVoo && v.getStatus() == Flight::PLANNED;
    });

    if (voo == flights.end()) {
        cout << "Voo não encontrado." << endl;
        return;
    } 

    if (voo->getStatus() != Flight::PLANNED) {
        std::cout << "O voo não está planejado para adicionar o astronauta nele." << std::endl;
        return;
    }

    bool astronautaJaCadastrado = any_of(voo->getPassageiros().begin(), voo->getPassageiros().end(),
                                         [cpf](const Astronaut& a) { return a.getCPF() == cpf; });

    if (astronautaJaCadastrado) {
        cout << "CPF já cadastrado nesse voo. Por favor, insira um CPF diferente." << endl;
    } else { 
        voo->addAstronaut(*astronauta);
        cout << "Astronauta adicionado com sucesso!" << endl;
    }
    
}

void removerAstronautaDeVoo(list<Astronaut>& astronauts, list<Flight>& flights) {
    if (flights.empty()) {
        cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
        return;
    }

    string cpf, codigoVoo;
    cout << "CPF do astronauta: ";
    cin >> cpf;

    auto astronauta = find_if(astronauts.begin(), astronauts.end(), [cpf](const Astronaut& a) {
        return a.getCPF() == cpf;
    });

    if (astronauta == astronauts.end()) {
        cout << "Astronauta não encontrado." << endl;
        return;
    }

    cout << "Codigo do voo: ";
    cin >> codigoVoo;

    auto voo = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& v) {
        return v.getCodigo() == codigoVoo && v.getStatus() == Flight::PLANNED;
    });

    if (voo == flights.end()) {
        cout << "Voo não encontrado." << endl;
        return;
    } else if (voo->getStatus() != Flight::PLANNED) {
        cout << "O voo não está planejado para remover o astronauta dele." << endl;
        return;
    } else {
        voo->removeAstronaut(cpf);
    }
}

void lancarVoo(std::list<Astronaut>& astronauts, std::list<Flight>& flights) {
    if (flights.empty()) {
        std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
        return;
    }

    std::string codigoVoo;
    std::cout << "Código do voo a ser lançado: ";
    std::cin >> codigoVoo;

    auto it = std::find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& voo) {
        return voo.getCodigo() == codigoVoo;
    });

    if (it != flights.end()) {
        if (it->getPassageiros().empty()) {
            std::cout << "Não é possível lançar o voo sem passageiros." << std::endl;
        } else {
            // Check if the flight status is PLANNED before launching
            if (it->getStatus() != Flight::PLANNED) {
                std::cout << "Voo não pode ser lançado. Verifique se o voo está planejado." << std::endl;
                return;
            }

            // Check each astronaut's availability
            bool allAstronautsAvailable = true;
            for (auto& astronaut : it->getPassageiros()) {
                auto astronautIt = std::find_if(astronauts.begin(), astronauts.end(),
                                                [&astronaut](const Astronaut& a) {
                                                    return a.getCPF() == astronaut.getCPF();
                                                });
                if (astronautIt != astronauts.end() && !astronautIt->isDisponivel()) {
                    std::cout << "Astronauta " << astronaut.getNome() << " não está disponível para a missão." << std::endl;
                    allAstronautsAvailable = false;
                    break;
                }
            }

            if (allAstronautsAvailable) {
                // Mark all astronauts in the flight as unavailable for other missions
                for (auto& astronaut : it->getPassageiros()) {
                    auto astronautIt = std::find_if(astronauts.begin(), astronauts.end(),
                                                    [&astronaut](const Astronaut& a) {
                                                        return a.getCPF() == astronaut.getCPF();
                                                    });
                    if (astronautIt != astronauts.end()) {
                        astronautIt->setDisponivel(false);
                    }
                }
                // Set the flight status to IN_PROGRESS
                it->setStatus(Flight::IN_PROGRESS);
                std::cout << "Voo lançado com sucesso!" << std::endl;
            } else {
                std::cout << "Voo não pode ser lançado devido a astronautas indisponíveis." << std::endl;
            }
        }
    } else {
        std::cout << "Voo não encontrado." << std::endl;
    }
}

void explodirVoo(std::list<Astronaut>& astronauts, std::list<Flight>& flights) {
    if (flights.empty()) {
        std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
        return;
    }

    std::string codigoVoo;
    std::cout << "Código do voo a ser explodido: ";
    std::cin >> codigoVoo;

    auto it = std::find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& voo) {
        return voo.getCodigo() == codigoVoo;
    });

    if (it != flights.end()) {
        // Check if the flight is in progress before exploding
        if (it->getStatus() == Flight::IN_PROGRESS) {
            it->setStatus(Flight::FINISHED_FAILURE);
            std::string vooCodigo = it->getCodigo();

            // Process each astronaut in the flight
            for (auto& astronaut : it->getPassageiros()) {
                auto astronautIt = std::find_if(astronauts.begin(), astronauts.end(),
                                                [&astronaut](const Astronaut& a) {
                                                    return a.getCPF() == astronaut.getCPF();
                                                });

                if (astronautIt != astronauts.end()) {
                    astronautIt->setVivo(false);  // Mark astronaut as not alive
                    astronautIt->setDisponivel(false);  // Mark astronaut as unavailable for future missions
                    astronautIt->addVooParticipado(vooCodigo);  // Add this flight to astronaut's participated flights
                }
            }

            std::cout << "Voo explodido com sucesso!" << std::endl;
        } else {
            std::cout << "Voo não pode ser explodido. Verifique o status do voo." << std::endl;
        }
    } else {
        std::cout << "Voo não encontrado." << std::endl;
    }
}

void finalizarVoo(std::list<Astronaut>& astronauts, std::list<Flight>& flights) {
    if (flights.empty()) {
        std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
        return;
    }

    std::string codigoVoo;
    std::cout << "Código do voo a ser finalizado: ";
    std::cin >> codigoVoo;

    auto it = std::find_if(flights.begin(), flights.end(), [codigoVoo](Flight& voo) {
        return voo.getCodigo() == codigoVoo;
    });

    if (it != flights.end()) {
        // Check if the flight is in progress before finishing
        if (it->getStatus() == Flight::IN_PROGRESS) {
            it->setStatus(Flight::FINISHED_SUCCESS);
            std::string vooCodigo = it->getCodigo();

            // Process each astronaut in the flight
            for (auto& astronaut : it->getPassageiros()) {
                auto astronautIt = std::find_if(astronauts.begin(), astronauts.end(),
                                                [&astronaut](const Astronaut& a) {
                                                    return a.getCPF() == astronaut.getCPF();
                                                });

                if (astronautIt != astronauts.end()) {
                    astronautIt->setVivo(true);  // Mark astronaut as alive
                    astronautIt->setDisponivel(true);  // Mark astronaut as available for future missions
                    astronautIt->addVooParticipado(vooCodigo);  // Add this flight to astronaut's participated flights
                }
            }

            std::cout << "Voo finalizado com sucesso!" << std::endl;
        } else {
            std::cout << "Voo não pode ser finalizado. Verifique o status do voo." << std::endl;
        }
    } else {
        std::cout << "Voo não encontrado." << std::endl;
    }
}

void listarVoos(const list<Flight>& flights) {
    if (flights.empty()) {
        cout << "Nenhum voo cadastrado." << endl;
        return;
    }

    cout << "============================================" << endl;
    cout << "            Lista de Voos" << endl;
    cout << "============================================" << endl;

    cout << "Voos Planejados:" << endl;
    bool hasPlannedFlights = false;
    for (const auto& flight : flights) {
        if (flight.getStatus() == Flight::PLANNED) {
            cout << "  Código: " << flight.getCodigo() << endl;
            cout << "  Passageiros: ";
            const auto& passageiros = flight.getPassageiros();
            if (passageiros.empty()) {
                cout << "Nenhum passageiro registrado." << endl;
            } else {
                for (const auto& astronauta : passageiros) {
                    cout << astronauta.getNome() << " (CPF: " << astronauta.getCPF() << "), ";
                }
                cout << endl;
            }
            hasPlannedFlights = true;
        }
    }
    if (!hasPlannedFlights) {
        cout << "Nenhum voo planejado." << endl;
    }

    cout << "Voos em Progresso:" << endl;
    bool hasInProgressFlights = false;
    for (const auto& flight : flights) {
        if (flight.getStatus() == Flight::IN_PROGRESS) {
            cout << "  Código: " << flight.getCodigo() << endl;
            cout << "  Passageiros: ";
            const auto& passageiros = flight.getPassageiros();
            if (passageiros.empty()) {
                cout << "Nenhum passageiro registrado." << endl;
            } else {
                for (const auto& astronauta : passageiros) {
                    cout << astronauta.getNome() << " (CPF: " << astronauta.getCPF() << "), ";
                }
                cout << endl;
            }
            hasInProgressFlights = true;
        }
    }
    if (!hasInProgressFlights) {
        cout << "  Nenhum voo em progresso." << endl;
    }

    cout << "Voos Finalizados:" << endl;
    bool hasFinishedFlights = false;
    for (const auto& flight : flights) {
        if (flight.getStatus() == Flight::FINISHED_SUCCESS || flight.getStatus() == Flight::FINISHED_FAILURE) {
            cout << "  Código: " << flight.getCodigo() << endl;
            cout << "  Status: " << (flight.getStatus() == Flight::FINISHED_SUCCESS ? "Finalizado com sucesso" : "Finalizado com falha") << endl;
            cout << "  Passageiros: ";
            const auto& passageiros = flight.getPassageiros();
            if (passageiros.empty()) {
                cout << "  Nenhum passageiro registrado." << endl;
            } else {
                for (const auto& astronauta : passageiros) {
                    cout << astronauta.getNome() << " (CPF: " << astronauta.getCPF() << "), ";
                }
                cout << endl;
            }
            hasFinishedFlights = true;
        }
    }
    if (!hasFinishedFlights) {
        cout << "  Nenhum voo finalizado." << endl;
    }
}

void listarAstronautasMortos(const list<Astronaut>& astronauts) {
    if (astronauts.empty()) {
        cout << "Nenhum astronauta cadastrado. Por favor, cadastre um astronauta primeiro." << endl;
        return;
    }

    for (Astronaut astronauta : astronauts) {
        if (!astronauta.isVivo()) {
            cout << "CPF: " << astronauta.getCPF() << endl;
            cout << "Nome: " << astronauta.getNome() << endl;
            cout << "Voos em que o astronauta participou: \n";
            for (const auto& codigo : astronauta.getVoosParticipados()) {
                cout << "  - Código do voo: " << codigo << endl;
            }
        }
    }
}

