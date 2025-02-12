<div align="center">
    <img src="https://moodle.embarcatech.cepedi.org.br/pluginfile.php/1/theme_moove/logo/1733422525/Group%20658.png" alt="Logo Embarcatech" height="100">
</div>

<br>

# Controle de servomotor por PWM

## Sumário

- [Descrição](#descrição)
- [Funcionalidades Implementadas](#funcionalidades-implementadas)
- [Ferramentas utilizadas](#ferramentas-utilizadas)
- [Objetivos](#objetivos)
- [Instruções de uso](#instruções-de-uso)
- [Vídeo de apresentação](#vídeo-de-apresentação)
- [Aluno e desenvolvedor do projeto](#aluno-e-desenvolvedor-do-projeto)
- [Licensa](#licença)

## Descrição

Este projeto implementa o controle de um servomotor utilizando modulação por largura de pulso (PWM) utilizando o microcontrolador Raspberry Pi Pico W. O projeto consiste em fazer uma configuração específica do PWM para que a sua frequência seja de 50Hz, e a partir disso fazer ajustes no seu ciclo de trabalho para movimentar o servomotor entre os ângulos de 0°, 90° e 180°. Além disso, implementar uma rotina para movimentação suave entre 0° e 180°. Por fim, foi realizada uma experiência prática com a placa BitDogLab utilizando o LED RGB azul para observar o comportamento do mesmo com as rotinas PWM implementadas.

## Funcionalidades Implementadas

1. Configuração do PWM na GPIO 22:

   - Configurei o *Wrap* = 20000 (us) e defini o valor do *di* a partir da fórmula:\
$Fpwm = \frac{Fclock}{(di + \frac{df}{16}) \cdot Wrap}$ \
$50Hz = \frac{125 \cdot 10^6 Hz}{(di + \frac{0}{16}) \cdot 20000}$ \
$di = 125$ 
   - Dessa forma, encontrei o conjunto de valores de *Wrap* e *di* que define a frequência do PWM para 50Hz.

2. Posicionamento inicial do Servomotor:

   - 180°: Ciclo ativo de 2.400µs (~12%) e espera de 5 segundos.
   - 90°: Ciclo ativo de 1.470µs (~7,35%) e espera de 5 segundos.
   - 0°: Ciclo ativo de 500µs (~2,5%) e espera de 5 segundos.
  
3. Rotina de movimentação Contínua e Suave do Servomotor:

   - O servomotor oscila entre 0° e 180° de forma gradual.
   - O ciclo ativo é ajustado em incrementos de ±5µs a cada 10 ms, garantindo um movimento suave.
    
4. Experimento com LED RGB (GPIO 12) na BitDogLab:

   - Observação do impacto do PWM no comportamento da iluminação do LED.

## Ferramentas utilizadas

- **Simulador de eletrônica wokwi**: Ambiente utilizado para simular o hardware e validar o funcionamento do sistema.
- **Ferramenta educacional BitDogLab (versão 6.3)**: Placa de desenvolvimento utilizada para programar o microcontrolador.
- **Microcontrolador Raspberry Pi Pico W**: Responsável pelo controle do servomotor e da implementação do PWM.
- **Servomotor (motor micro servo padrão)**: Movimenta-se de acordo com o que foi programado.
- **LED RGB**: Permite a experimentação do PWM no Hardware.
- **Visual Studio Code (VS Code)**: IDE utilizada para o desenvolvimento do código com integração ao Pico SDK.
- **Pico SDK**: Kit de desenvolvimento de software utilizado para programar o Raspberry Pi Pico W em linguagem C.
- **Monitor serial do VS Code**: Ferramenta utilizada para monitorar o valor do ciclo de trabalho (*Duty Cycle*).

## Objetivos

1. Compreender o funcionamento e a aplicação do módulo PWM.
2. Experimentar na prática o uso do PWM no Hardware.
3. Desenvolver um projeto funcional que combine hardware e software.

## Instruções de uso

1. **Clonar o Repositório**:

```bash
git clone https://github.com/bigodinhojf/embarcatech_tarefa_06_02.git
```

2. **Compilar e Carregar o Código**:
   No VS Code, configure o ambiente e compile o projeto com os comandos:

```bash	
cmake -G Ninja ..
ninja
```

3. **Interação com o Sistema**:
   - Conecte a placa ao computador.
   - Clique em run usando a extensão do raspberry pi pico.
   - Clique no arquivo *diagram.json* para abrir a simulação no Wokwi e clique em iniciar.
   - Observer a movimentação do servomotor no ciclo inicial e na rotina de movimentação suave.

## Vídeo de apresentação

O vídeo apresentando o projeto pode ser assistido [clicando aqui](https://youtu.be/mVY0w1Lo0Og).

## Aluno e desenvolvedor do projeto

<a href="https://github.com/bigodinhojf">
        <img src="https://github.com/bigodinhojf.png" width="150px;" alt="João Felipe"/><br>
        <sub>
          <b>João Felipe</b>
        </sub>
</a>

## Licença

Este projeto está licenciado sob a licença MIT.
