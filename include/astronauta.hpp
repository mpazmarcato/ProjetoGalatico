#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include <string>
#include <list>

class Astronaut {
private:
    std::string cpf;
    std::string nome;
    int idade;
    bool disponivel;
    bool vivo;
    std::list<std::string> voosParticipados;

public:
    Astronaut(std::string cpf, std::string nome, int idade);

    std::string getCPF() const;
    std::string getNome() const;
    int getIdade() const;
    bool isDisponivel() const;
    bool isVivo() const;
    bool isDead() const;
    void setDisponivel(bool disponivel);
    void setVivo(bool vivo);
    void addVooParticipado(const std::string& codigoVoo);
    const std::list<std::string>& getVoosParticipados() const;
};

#endif
