# Projeto Galáctico
O Projeto Galáctico é um sistema de gestão de astronautas e voos espaciais em C++ que permite a exploração do cosmos e a realização de viagens intergalácticas na disciplina de LP1

## Descrição

O Projeto Galáctico visa criar uma plataforma abrangente para o gerenciamento de missões espaciais, permitindo o cadastro de astronautas, a criação e administração de voos espaciais, e o acompanhamento do status das missões.
## Funcionalidades Principais
- **Cadastro de Astronauta**
- **Cadastro de Voo**
- **Adicionar Astronauta em Voo**
- **Remover Astronauta de um Voo**
- **Lançar um Voo**
- **Explodir Voo**
- **Finalizar um Voo (com sucesso)**
- **Listar todos os voos**
- **Listar todos os astronautas mortos**
  
## Como rodar o projeto (Linux)
Para executar o Projeto Galáctico, é necessário clonar o projeto com o comando abaixo:
```
git clone https://github.com/mpazmarcato/ProjetoGalatico.git
```

Na pasta principal do projeto utilize o comando:
```
cmake -S . -B build
cmake --build build
```
Obs: Será criado um diretório chamado `build`.
Logo, digite
```
./build/ProjetoGalatico
```
e programa será executado.
