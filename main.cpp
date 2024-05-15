#include <iostream>
#include <list>
#include <sstream>
#include <algorithm>
#include <limits>
#include "astronauta.hpp"
#include "flight.hpp"
#include "interface.hpp"

using namespace std;

int main() {
    list<Astronaut> astronauts;
    list<Flight> flights;

    string input;
    char confirm;

    do {
        confirm = 'n';
        clearScreen();
        interface();

        cout << "Escolha sua opcao: ";
        getline(cin, input); // Read entire line of input

        stringstream ss(input);
        int choice;

        if (!(ss >> choice) || ss.rdbuf()->in_avail() != 0) { // Check for conversion failure or leftover characters
            cout << "Opção inválida. Por favor, escolha uma opção válida." << endl;
            continue;
        }

        switch (choice) {
            case 1: { // Cadastrar Astronauta
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
                        cin.clear(); // Limpa o estado de erro de cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix: Include template argument and delimiter
                        continue;
                    }
                } while (idade < 23 || idade > 90);

                Astronaut novoAstronauta(cpf, nome, idade);
                astronauts.push_back(novoAstronauta);
                
                cout << "Astronauta cadastrado com sucesso!" << endl;
                break;
            } case 2: { // Cadastrar Voo
                string codigo;
                do {
                    cout << "Codigo do voo (4 digitos seguidos): ";
                    cin >> codigo;

                    auto it = find_if(flights.begin(), flights.end(), [&codigo](const Flight& voo) {
                        return voo.getCodigo() == codigo;
                    });

                    if (codigo.length() != 4 || it != flights.end()) {
                        cout << "Código do voo inválido ou já existente. Deve conter exatamente 4 dígitos e ser único." << endl;
                        continue; 
                    }

                    if (codigo.find('e') != string::npos) {
                        cout << "Código do voo inválido. Não pode conter o número 'e'." << endl;
                        continue;
                    }

                    Flight novoVoo(codigo);
                    flights.push_back(novoVoo);
                    
                    cout << "Voo cadastrado com sucesso!" << endl;
                    break; 
                } while (true);
                break;
            } case 3: { // Adicionar Astronauta em Voo
                if (flights.empty()) {
                    cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
                    break;
                }

                string cpf;
                string codigoVoo;
                cout << "CPF do astronauta: ";
                cin >> cpf;
                cout << "Código do voo: ";
                cin >> codigoVoo;

                auto astronauta = find_if(astronauts.begin(), astronauts.end(), [cpf](const Astronaut& a) {
                    return a.getCPF() == cpf && a.isVivo() && a.isDisponivel();
                });

                auto voo = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& v) {
                    return v.getCodigo() == codigoVoo && v.getStatus() == Flight::PLANNED;
                });

                if (voo == flights.end()) {
                    cout << "Voo não encontrado ou não está planejado." << endl;
                    break;
                }

                if (astronauta == astronauts.end()) {
                    cout << "Astronauta não encontrado." << endl;
                    break;
                }

                if (!astronauta->isDisponivel() ) {
                    cout << "Astronauta morto ou não disponível para ser adicionado como passageiro." << endl;
                    break;
                }

                if (voo->getStatus() != Flight::PLANNED) {
                    cout << "Não é possível adicionar astronautas a um voo em andamento." << endl;
                    break;
                }


                // Verificar se o astronauta já está cadastrado nesse voo
                bool astronautaJaCadastrado = false;
                for (const auto& passageiro : voo->getPassageiros()) {
                    if (passageiro.getCPF() == cpf) {
                        astronautaJaCadastrado = true;
                        break;
                    }
                }

                if (astronautaJaCadastrado) {
                    cout << "CPF já cadastrado nesse voo. Por favor, insira um CPF diferente." << endl;
                } else {
                    voo->adicionarPassageiro(*astronauta);
                }
                
                break;
            } case 4: { // Remover Astronauta de um Voo
                if (flights.empty()) {
                    cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
                    break;
                }

                string cpf;
                string codigoVoo;
                cout << "CPF do astronauta: ";
                cin >> cpf;
                cout << "Codigo do voo: ";
                cin >> codigoVoo;

                auto astronauta = find_if(astronauts.begin(), astronauts.end(), [cpf](const Astronaut& astronauta) {
                    return astronauta.getCPF() == cpf;
                });

                auto voo = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& voo) {
                    return voo.getCodigo() == codigoVoo && voo.getStatus() == Flight::PLANNED;
                });

                if (voo == flights.end()) {
                    cout << "Voo não encontrado ou não está planejado." << endl;
                    break;
                } 

                if (astronauta == astronauts.end()) {
                    cout << "Astronauta não encontrado." << endl;
                    break;
                } 

                if (voo->getStatus() != Flight::PLANNED) {
                    cout << "Não é possível remover astronautas a um voo em andamento." << endl;
                } else {
                    voo->removerPassageiro(*astronauta);
                }
                break;
            } case 5: { // Lançar um Voo
                if (flights.empty()) {
                    cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
                    break;
                }

                string codigoVoo;
                cout << "Código do voo a ser lançado: ";
                cin >> codigoVoo;

                auto it = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& voo) { return voo.getCodigo() == codigoVoo; });
                if (it != flights.end()) {
                    if (it->getPassageiros().empty()) {
                        cout << "Não é possível lançar o voo sem passageiros." << endl;
                    } else {
                        it->launchFlight(astronauts);
                    }
                } else {
                    cout << "Voo não encontrado." << endl;
                }
                break;
            } case 6: { // Explodir Voo
                if (flights.empty()) {
                    cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
                    break;
                }

                string codigoVoo;
                cout << "Código do voo a ser explodido: ";
                cin >> codigoVoo;

                auto it = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& voo) { return voo.getCodigo() == codigoVoo; });
                if (it != flights.end()) {
                    it->explode(astronauts);
                } else {
                    cout << "Voo não encontrado." << endl;
                }
                break;
            } case 7: { // Finalizar um Voo (com sucesso)
                if (flights.empty()) {
                    cout << "Nenhum voo cadastrado. Por favor, cadastre um voo primeiro." << endl;
                    break;
                }

                string codigoVoo;
                cout << "Código do voo a ser finalizado: ";
                cin >> codigoVoo;

                auto it = find_if(flights.begin(), flights.end(), [codigoVoo](const Flight& voo) { return voo.getCodigo() == codigoVoo; });
                if (it != flights.end()) {
                        it->finish(Flight::FINISHED_SUCCESS, astronauts);
                } else {
                    cout << "Voo não encontrado." << endl;
                }
                break;
            } case 8: { // Listar todos os voos organizados por status
                if (flights.empty()) {
                    cout << "Nenhum voo cadastrado." << endl;
                    break;
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
                        cout << endl;
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
                        cout << endl;
                        hasInProgressFlights = true;
                    }
                }
                if (!hasInProgressFlights) {
                    cout << "Nenhum voo em progresso." << endl;
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
                            cout << "Nenhum passageiro registrado." << endl;
                        } else {
                            for (const auto& astronauta : passageiros) {
                                cout << astronauta.getNome() << " (CPF: " << astronauta.getCPF() << "), ";
                            }
                            cout << endl;
                        }
                        cout << endl;
                        hasFinishedFlights = true;
                    }
                }
                if (!hasFinishedFlights) {
                    cout << "Nenhum voo finalizado." << endl;
                }

                break;
            } case 9: { // Listar astronautas mortos
                if (astronauts.empty()) {
                    cout << "Nenhum astronauta cadastrado." << endl;
                    break;
                }

                cout << "============================================" << endl;
                cout << "          Lista de Astronautas" << endl;
                cout << "============================================" << endl;

                //listarAstronautasMortos(astronauts);
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
                break;
            } case 0: {
                cout << "Saindo do sistema..." << endl;
                confirm = 's'; 
                break;
            } //default: {
            //     cout << "Opção inválida. Por favor, escolha uma opção válida." << endl;
            //     break;
            // }
        }

        if (confirm != 's') {
            cout << "Pressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        
    } while (confirm != 's');

    return 0;
}