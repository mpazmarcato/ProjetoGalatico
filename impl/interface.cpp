#include <iostream>
#include "../include/interface.hpp"

void interface() {
    std::cout << "============================================" << std::endl;
    std::cout << "     Sistema de Gerenciamento Espacial" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "1. Cadastrar Astronauta" << std::endl;
    std::cout << "2. Cadastrar Voo" << std::endl;
    std::cout << "3. Adicionar Astronauta em Voo (por CPF)" << std::endl;
    std::cout << "4. Remover Astronauta de um Voo (por CPF)" << std::endl;
    std::cout << "5. Lançar um Voo" << std::endl;
    std::cout << "6. Explodir Voo" << std::endl;
    std::cout << "7. Finalizar um Voo (com sucesso)" << std::endl;
    std::cout << "8. Listar todos os voos" << std::endl;
    std::cout << "9. Listar todos os astronautas mortos" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "============================================" << std::endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}