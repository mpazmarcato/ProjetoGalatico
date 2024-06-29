#include <iostream>
#include <list>
#include <limits>
#include "astronauta.hpp"
#include "flight.hpp"
#include "controller.hpp"
#include "interface.hpp"

using namespace std;

int main() {
    list<Astronaut> astronauts;
    list<Flight> flights;
    int option;
    
    do {
        //clearScreen();
        interface();
        cout << "Escolha uma opção: ";
        cin >> option;

        switch (option) {
            case 1:
                cadastrarAstronauta(astronauts);
                break;
            case 2:
                cadastrarVoo(flights);
                break;
            case 3:
                adicionarAstronautaEmVoo(astronauts, flights);
                break;
            case 4:
                removerAstronautaDeVoo(astronauts, flights);
                break;
            case 5:
                lancarVoo(astronauts, flights);
                break;
            case 6:
                explodirVoo(astronauts, flights);
                break;
            case 7:
                finalizarVoo(astronauts, flights);
                break;
            case 8:
                listarVoos(flights);
                break;
            case 9:
                listarAstronautasMortos(astronauts);
                break;
            case 0:
                cout << "Saindo do sistema." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }

        if (option != 0) {
            cout << "Pressione Enter para continuar...";
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (option != 0);

    return 0;
}
