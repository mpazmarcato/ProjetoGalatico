#include "../include/astronauta.hpp"

Astronaut::Astronaut(std::string cpf, std::string nome, int idade)
    : cpf(cpf), nome(nome), idade(idade), disponivel(true), vivo(true) {}

std::string Astronaut::getCPF() const {
    return cpf;
}

std::string Astronaut::getNome() const {
    return nome;
}

int Astronaut::getIdade() const {
    return idade;
}

bool Astronaut::isDisponivel() const {
    return disponivel;
}

bool Astronaut::isVivo() const {
    return vivo;
}

bool Astronaut::isDead() const {
    return !vivo;
}

void Astronaut::setDisponivel(bool disponivel) {
    this->disponivel = disponivel;
}

void Astronaut::setVivo(bool vivo) {
    this->vivo = vivo;
}

void Astronaut::addVooParticipado(const std::string& codigoVoo) {
    voosParticipados.push_back(codigoVoo);
}

const std::list<std::string>& Astronaut::getVoosParticipados() const {
    return voosParticipados;
}
