# BitDogLab Raspberry Pi Pico W Project
# Vídeo do projeto https://youtu.be/MSnW2AVbOuY

### Autor: Davi Bezerra Cavalcanti

Este projeto foi desenvolvido para a placa **BitDogLab**, utilizando a **Raspberry Pi Pico W**. O objetivo é controlar um display OLED com um quadrado em movimento, controlado por um joystick e com LEDs representando a intensidade do movimento. O projeto inclui a interação com botões para controlar o estado do LED verde e realizar o bootsel da placa.

## Estrutura do Repositório

O repositório está organizado da seguinte forma:

- **src/**: Contém o código principal do projeto.
- **include/**: Contém as bibliotecas criadas especificamente para o projeto.

## Pré-requisitos

Para compilar e executar este projeto, é necessário configurar corretamente o ambiente de desenvolvimento com as seguintes extensões:

- **CMakeLists**: Para gerenciar a construção do projeto.
- **Raspberry Pi Pico**: Extensão necessária para importar e compilar o código para a Raspberry Pi Pico W.

## Como Compilar e Executar

1. **Instalar as dependências**:
   - Certifique-se de que você tem o **CMake** e a **extensão Raspberry Pi Pico** configurados corretamente no seu ambiente de desenvolvimento.

2. **Configurar o ambiente**:
   - Abra o projeto no **Visual Studio Code**

3. **Compilação**:
   - Utilize a extensão da Raspberry importar o projeto, em seguida, compile o código.

4. **Execução**:
   - Após compilar o código, envie-o para sua placa **Raspberry Pi Pico W** em modo bootsel utilizando a ferramenta apropriada para o upload do código ou movendo o arquivo uf2 para a sua placa

## Funcionalidades

- **Controle do Cubo**: O cubo no display OLED é controlado pelo movimento do joystick.
- **LEDs**: Os LEDs da placa indicam a intensidade do movimento do joystick.
- **Botões**: Existem três botões configurados:
  - **Botão A**: Altera o estado dos LEDs.
  - **Botão B**: Desliga o display e coloca a Raspberry Pi Pico W em bootsel.
  - **Botão do Joystick**: Alterna o estado do LED verde.

## Código Principal

O código realiza a leitura do joystick, atualiza a posição do cubo no display e ajusta os LEDs conforme os valores do joystick. Ele também responde aos botões para realizar algumas ações, como alterar o estado dos LEDs ou reiniciar o sistema.

## Observações

- Este projeto foi desenvolvido especificamente para a **Raspberry Pi Pico W** utilizando a **BitDogLab**.

## Contribuições

Contribuições são bem-vindas! Caso queira colaborar, sinta-se à vontade para abrir um *pull request* ou relatar problemas.
