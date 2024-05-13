#ifndef ASTRONAUTA_HPP
#define ASTRONAUTA_HPP

#include <string>
#include <list>
#include "enum/astronautStateEnum.hpp"

class Astronaut {
private:
        std::string cpf;
        std:: string nome;
        int idade;
        bool disponivel;
        AstronautStatus astronautStatus;
        std::list<std::string> voosParticipados;

    public:
        Astronaut();
        Astronaut(std::string cpf, std::string nome, int idade, bool disponivel, AstronautStatus astronautStatus, std::list<std::string> voosParticipados);

        //Getters
        std::string getNome();
        std::string getCPF();
        int getIdade(); 
        bool isDisponivel();
        AstronautStatus getAstronautStatus();
        std::list<std::string>& getVoosParticipados();

        //Setters
        void setNome(std::string nome);
        void setCPF(std::string cpf);
        void setIdade(int idade);
        void setAstronautStatus(AstronautStatus astronautStatus);
        void setDisponivel(bool disponivel);
};

#endif