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
  
## Como rodar o projeto
Instale o CMake: Certifique-se de que o CMake está instalado no computador de destino.

Clone ou copie o projeto: Transfira os arquivos do projeto, incluindo o CMakeLists.txt, para o computador de destino.

Crie um diretório de build: No diretório do projeto, crie um diretório separado para os arquivos de compilação (por exemplo, build).

``mkdir build
cd build`

Configure o projeto com CMake: No diretório de build, execute o comando CMake para configurar o projeto. Isso gerará os arquivos de projeto ou makefiles necessários.

bash

cmake ..

(Use cmake -G <generator> para especificar um gerador específico, como Ninja ou Unix Makefiles, se necessário.)

Compile o projeto: Após a configuração, compile o projeto usando o make ou o gerador especificado.

bash

make

(Ou outro comando dependendo do gerador escolhido, como ninja.)

Execute o projeto: Depois de compilado, você pode executar os binários gerados conforme necessário.
