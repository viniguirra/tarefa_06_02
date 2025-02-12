// Inclusão de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Declaração de constantes
#define PWM_SERVO 22 // Define o pino PWM do Servo na GPIO 22
#define TIME_PAUSE 5000 // Define o tempo de pausa entre as posições iniciais do servo (5000ms)
#define SERVO_STEP 5 // Passo do incremento/decremento do ciclo ativo (5us)
#define TIME_CICLE 10 // Define o tempo de atraso de ajuste do incremento di ciclo ativo (10ms)

#define ANGULO_180 2400 // Ciclo ativo de 2400us = Duty cycle de 12% (180°)
#define ANGULO_90 1470 // Ciclo ativo de 1470us = Duty cycle de 7,35% (90°)
#define ANGULO_0 500 // Ciclo ativo de 500us = Duty cycle de 2,5% (0°)

// Declaração de variáveis globais
volatile uint up_down = 1; // Variável que controla se o ângulo do servo aumenta ou diminui
volatile uint servo_level = 500; // Valor inicial do ciclo ativo do PWM (500us = DC 12%)

// Função principal
int main()
{
    // Inicializações
    stdio_init_all(); // Inicializa o monitor serial

    // Configuração do PWM
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM); // Define a função da porta GPIO 22 do servo como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO); // Guarda o canal do PWM
    pwm_set_clkdiv(slice, 125.0); // Define o divisor de clock do PWM (di = 125 para que Fpwm = 50Hz)
    pwm_set_wrap(slice, 20000); // Define o valor do wrap (20ms = 20.000us)
    pwm_set_enabled(slice, true); // Habilita o PWM no slice

    // Ciclo inicial = 180° - 5s - 90° - 5s - 0° - 5s
    pwm_set_gpio_level(PWM_SERVO, ANGULO_180); // Define o ciclo de trabalho de 12% = 180 graus

    sleep_ms(TIME_PAUSE);

    pwm_set_gpio_level(PWM_SERVO, ANGULO_90); // Define o ciclo de trabalho de 7,35% = 90 graus

    sleep_ms(TIME_PAUSE);

    pwm_set_gpio_level(PWM_SERVO, ANGULO_0); // Define o ciclo de trabalho de 2,5% = 0 grau

    sleep_ms(TIME_PAUSE);

    while (true) {

        // Rotina para movimentação periódica do servomotor entre 0° e 180°
        printf("Ciclo ativo:%d\n", servo_level); // Imprime o  ciclo ativo do PWM (500 - 2400)
        pwm_set_gpio_level(PWM_SERVO, servo_level); // Define o nível atual do ciclo de trabalho do PWM

        if(up_down){ // Se up_down = 1, incrementa
          servo_level += SERVO_STEP; // Incrementa o valor do DC
          if(servo_level >= ANGULO_180){ 
            // Se o valor do ciclo de trabalho alcançou o máximo (180°), muda up_down para decrementar
            up_down = 0;
          }
        } else{ // Se up_down = 0, decrementa
            servo_level -= SERVO_STEP; // Decrementa o valor de DC
            if(servo_level<= ANGULO_0){
                // Se o valor do ciclo de trabalho alcançou o mínimo (0°), muda up_down para incrementar
                up_down = 1;
            }
        }
        sleep_ms(TIME_CICLE);
    }
}
