#include "../include/astronauta.hpp"
#include "../include/enum/astronautStateEnum.hpp"

Astronaut::Astronaut() {}

Astronaut::Astronaut(std::string cpf, std::string nome, int idade, bool disponivel, AstronautStatus astronautStatus, std::list<std::string> voosParticipados) {
    this->cpf = cpf;
    this->nome = nome;
    this->idade = idade;
    this->disponivel = disponivel;
    this->astronautStatus = astronautStatus;
    this->voosParticipados = voosParticipados;
}

std::string Astronaut::getNome() { return this->nome; }
std::string Astronaut::getCPF() { return this->cpf; }
int Astronaut::getIdade() { return this->idade; }
bool Astronaut::isDisponivel() { return this->disponivel; }
AstronautStatus Astronaut::getAstronautStatus() { return this->astronautStatus; }
std::list<std::string>& Astronaut::getVoosParticipados() { return this->voosParticipados; }

void Astronaut::setNome(std::string nome) { this->nome = nome; }
void Astronaut::setCPF(std::string cpf) { this->cpf = cpf; }
void Astronaut::setIdade(int idade) { this->idade = idade; }
void Astronaut::setDisponivel(bool disponivel) { this->disponivel = disponivel; }
void Astronaut::setAstronautStatus(AstronautStatus AstronautStatus) { this->astronautStatus = astronautStatus; }