#include <iostream>
#include "include/astronauta.hpp"
#include "include/flight.hpp"
#include "include/interface.hpp"
#include "include/sistema.hpp"
#include "include/enum/astronautStateEnum.hpp"
#include <list>
#include <cstdlib>
#include <algorithm>
#include <limits>

int main() {
    std::list<Flight> databaseFlight;
    std::list<Astronaut> databaseAstronaut;
    
    int option;
    char confirm;

    do {
        confirm = 'n';
        std::system("clear");
        interface();

        std::cout << "Digite a opção: ";
        std::cin >> option;
        getchar();

        switch (option) {
            case 1: {
                Astronaut astronaut;
                std::string nome;
                std::string cpf;
                int idade;
                std::list<std::string> voosParticipados;

                bool cpfRepetido;
                do {
                    std::cout << "CPF do astronauta (11 digitos numericos): ";
                    std::cin >> cpf;
                    if (cpf.length() != 11 || !all_of(cpf.begin(), cpf.end(), ::isdigit)) {
                        std::cout << "CPF inválido. Por favor, insira um CPF com 11 dígitos numéricos.\n";
                        continue;
                    }
                    cpfRepetido = false;
                    for (auto& astronauta : databaseAstronaut) {
                        if (astronauta.getCPF() == cpf) {
                            std::cout << "CPF já cadastrado. Por favor, insira um CPF diferente.\n";
                            cpfRepetido = true;
                            break; 
                        }
                    }
                } while (cpf.length() != 11 || !all_of(cpf.begin(), cpf.end(), ::isdigit) || cpfRepetido);

                do {
                    std::cout << "Nome do astronauta: ";
                    std::cin.ignore();
                    getline(std::cin, nome);
                    if (nome.empty()) {
                        std::cout << "O nome não pode ser vazio. Por favor, insira um nome válido.\n";
                        continue;
                    }
                    if (all_of(nome.begin(), nome.end(), ::isdigit)) {
                        std::cout << "O nome não pode conter números. Por favor, insira um nome válido.\n";
                        continue;
                    }
                } while (nome.empty() || all_of(nome.begin(), nome.end(), ::isdigit));
                
                do { 
                    std::cout << "Idade do astronauta: ";
                    std::cin >> idade;
                    if (std::cin.fail() || idade < 23 || idade > 90) {
                        std::cout << "Idade inválida. Por favor, insira uma idade entre 23 e 90 anos.\n";
                        std::cin.clear(); 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                        continue;
                    }
                } while (idade < 23 || idade > 90);

                astronaut = Astronaut(cpf, nome, idade, true, ALIVE, voosParticipados);
                databaseAstronaut.push_back(astronaut);
                
                std::cout << "Astronauta cadastrado com sucesso!" << std::endl;
                break;
            } case 2: {
                Flight flight;
                std::string codigo;
                std::list<std::string> passageiros;
                do {
                    std::cout << "Codigo do voo (4 digitos seguidos): ";
                    std::cin >> codigo;

                    auto it = find_if(databaseFlight.begin(), databaseFlight.end(), [&codigo](Flight& voo) {
                        return voo.getCodigo() == codigo;
                    });

                    if (codigo.length() != 4 || it != databaseFlight.end()) {
                        std::cout << "Código do voo inválido ou já existente. Deve conter exatamente 4 dígitos e ser único." << std::endl;
                        continue; 
                    }

                    if (codigo.find('e') != std::string::npos) {
                        std::cout << "Código do voo inválido. Não pode conter o número 'e'." << std::endl;
                        continue;
                    }
                    flight = Flight(codigo, PLANNED, passageiros);
                    databaseFlight.push_back(flight);
                    std::cout << "Voo cadastrado com sucesso!" << std::endl;
                    break; 
                } while (true);
                break;
            } case 3: { // Adicionar Astronauta em Voo
                if (databaseFlight.empty()) {
                    std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
                    break;
                }

                std::string cpf;
                std::string codigoVoo;
                std::cout << "CPF do astronauta: ";
                std::cin >> cpf;
                std::cout << "Código do voo: ";
                std::cin >> codigoVoo;

                auto astronauta = find_if(databaseAstronaut.begin(), databaseAstronaut.end(), [cpf](Astronaut& a) {
                    return a.getCPF() == cpf && a.isDisponivel();
                });

                auto voo = find_if(databaseFlight.begin(), databaseFlight.end(), [codigoVoo](Flight& v) {
                    return v.getCodigo() == codigoVoo && v.getFlightStatus() == PLANNED;
                });

                if (voo == databaseFlight.end()) {
                    std::cout << "Voo não encontrado ou não está planejado." << std::endl;
                    break;
                }

                if (astronauta == databaseAstronaut.end()) {
                    std::cout << "Astronauta não encontrado." << std::endl;
                    break;
                }

                if (!astronauta->isDisponivel() || astronauta->getAstronautStatus() == DEAD) {
                    std::cout << "Astronauta não está disponível para ser adicionado como passageiro." << std::endl;
                    break;
                }

                if (voo->getFlightStatus() != FlightStatus::PLANNED) {
                    std::cout << "Não é possível adicionar astronautas a um voo em andamento." << std::endl;
                    break;
                }

                bool astronautaJaCadastrado = false;
                for (const auto& passageiro : voo->getPassageiros()) {
                    if (passageiro == cpf) {
                        astronautaJaCadastrado = true;
                        break;
                    }
                }

                if (astronautaJaCadastrado) {
                    std::cout << "CPF já cadastrado nesse voo. Por favor, insira um CPF diferente." << std::endl;
                } else {
                    adicionarPassageiro(cpf, *voo);
                }
                break;
            } case 4: { // Remover Astronauta de um Voo
                if (databaseFlight.empty()) {
                    std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
                    break;
                }

                std::string cpf;
                std::string codigoVoo;
                std::cout << "CPF do astronauta: ";
                std::cin >> cpf;
                std::cout << "Código do voo: ";
                std::cin >> codigoVoo;

                auto astronauta = find_if(databaseAstronaut.begin(), databaseAstronaut.end(), [cpf](Astronaut& a) {
                    return a.getCPF() == cpf && a.isDisponivel();
                });

                auto voo = find_if(databaseFlight.begin(), databaseFlight.end(), [codigoVoo](Flight& v) {
                    return v.getCodigo() == codigoVoo && v.getFlightStatus() == PLANNED;
                });

                if (voo == databaseFlight.end()) {
                    std::cout << "Voo não encontrado ou não está planejado." << std::endl;
                    break;
                }

                if (astronauta == databaseAstronaut.end()) {
                    std::cout << "Astronauta não encontrado." << std::endl;
                    break;
                }

                if (voo->getFlightStatus() != FlightStatus::PLANNED) {
                    std::cout << "Não é possível remover astronautas a um voo em andamento." << std::endl;
                } else {
                    removerPassageiro(cpf, *voo);
                }
                break;
            } case 5: { // Lançar um Voo
                if (databaseFlight.empty()) {
                    std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
                    break;
                }

                std::string codigoVoo;
                std::cout << "Código do voo a ser lançado: ";
                std::cin >> codigoVoo;

                auto voo = find_if(databaseFlight.begin(), databaseFlight.end(), [codigoVoo](Flight& voo) { 
                    return voo.getCodigo() == codigoVoo; 
                });

                if (voo != databaseFlight.end()) {
                    if (voo->getPassageiros().empty()) {
                        std::cout << "Não é possível lançar o voo sem passageiros." << std::endl;
                    } else {
                        launch(*voo, databaseAstronaut);}
                } else {
                    std::cout << "Voo não encontrado." << std::endl;
                }
                
                break;
            } case 6: { // Explodir Voo
                if (databaseFlight.empty()) {
                    std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
                    break;
                }

                std::string codigoVoo;
                std::cout << "Código do voo a ser explodido: ";
                std::cin >> codigoVoo;

                auto voo = find_if(databaseFlight.begin(), databaseFlight.end(), [codigoVoo](Flight& voo) { 
                    return voo.getCodigo() == codigoVoo; 
                });
                
                if (voo != databaseFlight.end()) {
                    explode(*voo, databaseAstronaut);
                } else {
                    std::cout << "Voo não encontrado." << std::endl;
                }
                break;
            } case 7:{
                if (databaseFlight.empty()) {
                    std::cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << std::endl;
                    break;
                }

                std::string codigoVoo;
                std::cout << "Código do voo a ser finalizado: ";
                std::cin >> codigoVoo;

                auto voo = find_if(databaseFlight.begin(), databaseFlight.end(), [codigoVoo](Flight& voo) { 
                    return voo.getCodigo() == codigoVoo; 
                });
                
                if (voo != databaseFlight.end()) {
                    finish(*voo, databaseAstronaut);
                } else {
                    std::cout << "Voo não encontrado." << std::endl;
                }
                break;
            } case 8: {
                if (databaseFlight.empty()) {
                    std::cout << "Nenhum voo cadastrado." << std::endl;
                    break;
                }

                std::cout << "============================================" << std::endl;
                std::cout << "            Lista de Voos" << std::endl;
                std::cout << "============================================" << std::endl;

                listFlights(databaseFlight, databaseAstronaut);
                
                break;
            } case 9 : {
                if (databaseAstronaut.empty()) {
                    std::cout << "Nenhum astronauta cadastrado." << std::endl;
                    break;
                }

                std::cout << "============================================" << std::endl;
                std::cout << "          Lista de Astronautas" << std::endl;
                std:: cout << "============================================" << std::endl;

                if (!databaseFlight.empty()) {
                    listarAstronautasMortos(databaseFlight, databaseAstronaut);
                }
                
                break;
            } case 0: {
                std::cout << "Saindo do sistema..." << std::endl;
                confirm = 's'; 
                break;
            } default: {
                std::cout << "Escolha inválida. Por favor, tente novamente." << std::endl;
                break;
            }
        }
        if (confirm != 's') {
            std::cout << "Pressione Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    } while (option != 0);

    return 0;
}