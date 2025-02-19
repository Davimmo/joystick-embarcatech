// Bibliotecas padrão do C
#include <stdio.h>
#include <stdlib.h>

// Bibliotecas da Raspberry Pi Pico
#include "pico/stdlib.h"
#include "pico/bootrom.h"

// Bibliotecas específicas do projeto
#include "include/joystick.h"
#include "include/ssd1306.h"
#include "include/leds.h"

// Definição de macros
#define LOG(var) printf("%s: %d\n", #var, var);
#define TEMPO_DEBOUNCE 150
#define BOTAO_A 5
#define BOTAO_B 6

// Protótipos das funções relacionadas aos botões
void botao_callback(uint gpio, uint32_t eventos);
void botao_init(uint8_t pino);

// Variável global para o display
display tela;

// Variáveis para controle de debounce
static volatile uint32_t ultima_interrupcao_a = 0;
static volatile uint32_t ultima_interrupcao_b = 0;
static volatile uint32_t ultima_interrupcao_joystick = 0;
static volatile uint8_t contador_borda = 0;

// Estado do LED e do botão
volatile bool estado_led_verde = 0;
volatile bool estado_botao_a = 0;

int main() {
    stdio_init_all();
    
    // Inicialização dos LEDs
    led_init(LED_RED);
    led_init(LED_GREEN);
    led_init(LED_BLUE);

    // Inicialização do joystick
    joystick_init(JOYSTICK_X_PIN, JOYSTICK_Y_PIN);

    // Inicialização do display
    uint8_t cubo_x = (DISPLAY_WIDTH / 2) - 4;
    uint8_t cubo_y = (DISPLAY_HEIGHT / 2) - 4;
    uint8_t cubo_x_anterior = cubo_x;
    uint8_t cubo_y_anterior = cubo_y;

    // Limpa e inicializa o display
    display_clear(&tela);
    display_init(&tela);
    display_draw_rectangle(0, 0, 127, 63, false, true, &tela);
    display_draw_rectangle(cubo_x, cubo_y, cubo_x + 8, cubo_y + 8, true, true, &tela);
    display_update(&tela);

    // Inicialização dos botões
    botao_init(BOTAO_A);
    botao_init(BOTAO_B);
    botao_init(JOYSTICK_BUTTON);

    while (true) {
        // Leitura do joystick com valores ajustados
        int16_t joystick_x = joystick_read(JOYSTICK_X_PIN, 10, 510);
        int16_t joystick_y = joystick_read(JOYSTICK_Y_PIN, 10, 510);
        
        // Ajusta intensidade dos LEDs
        if (!estado_botao_a) {
            led_intensity(LED_BLUE, abs(joystick_y));
            led_intensity(LED_RED, abs(joystick_x));
            led_intensity(LED_GREEN, estado_led_verde * 255);
        } else {
            led_intensity(LED_BLUE, 0);
            led_intensity(LED_RED, 0);
            led_intensity(LED_GREEN, 0);
        }

        // Normaliza a velocidade do cubo
        joystick_x = ((joystick_x * 10) / 510);
        joystick_y = ((joystick_y * 10) / 510) * (-1);

        // Debug utilizando porta serial
        LOG(joystick_x);
        LOG(joystick_y);
        
        // Atualiza posição do cubo
        cubo_x = (cubo_x + joystick_x + DISPLAY_WIDTH) % DISPLAY_WIDTH;
        cubo_y = (cubo_y + joystick_y + DISPLAY_HEIGHT) % DISPLAY_HEIGHT;

        if (cubo_x_anterior != cubo_x || cubo_y_anterior != cubo_y) {
            display_draw_rectangle(cubo_x_anterior, cubo_y_anterior, cubo_x_anterior + 8, cubo_y_anterior + 8, true, false, &tela);
            display_draw_rectangle(cubo_x, cubo_y, cubo_x + 8, cubo_y + 8, true, true, &tela);
            cubo_x_anterior = cubo_x;
            cubo_y_anterior = cubo_y;
        }

        // Atualiza borda da tela
        if (contador_borda >= 4) {
            for (int i = 1; i <= contador_borda; i++) {
                display_draw_rectangle(i, i, 127 - i, 63 - i, false, false, &tela);
                display_draw_rectangle(i+5, i+5, 127 - i-5, 63 - i-5, false, false, &tela);
            }
            contador_borda = 0;
        }

        for (int i = 1; i <= contador_borda; i++) {
            display_draw_rectangle(i, i, 127 - i, 63 - i, false, true, &tela);
            display_draw_rectangle(i+5, i+5, 127 - i-5, 63 - i-5, false, true, &tela);
        }

        display_draw_rectangle(0, 0, 127, 63, false, true, &tela);
        display_update(&tela);
        sleep_ms(30);
    }
    return 0;
}

void botao_callback(uint gpio, uint32_t eventos) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());
    
    switch (gpio) {
        case BOTAO_A:
            if (tempo_atual - ultima_interrupcao_a > TEMPO_DEBOUNCE) {
                ultima_interrupcao_a = tempo_atual;
                if (eventos & GPIO_IRQ_EDGE_FALL) {
                    estado_botao_a = !estado_botao_a;
                }
            }
            break;
        
        case BOTAO_B:
            if (tempo_atual - ultima_interrupcao_b > TEMPO_DEBOUNCE) {
                ultima_interrupcao_b = tempo_atual;
                if (eventos & GPIO_IRQ_EDGE_FALL) {
                    display_shutdown(&tela);
                    reset_usb_boot(0, 0);
                }
            }
            break;
        
        case JOYSTICK_BUTTON:
            if (tempo_atual - ultima_interrupcao_joystick > TEMPO_DEBOUNCE) {
                ultima_interrupcao_joystick = tempo_atual;
                if (eventos & GPIO_IRQ_EDGE_FALL) {
                    estado_led_verde = !estado_led_verde;
                    contador_borda++;
                }
            }
            break;
    
        default:
            // Caso não seja nenhum dos botões ou joystick
            break;
    }
}

void botao_init(uint8_t pino) {
    gpio_init(pino);
    gpio_set_dir(pino, GPIO_IN);
    gpio_pull_up(pino);
    gpio_set_irq_enabled_with_callback(pino, GPIO_IRQ_EDGE_FALL, true, &botao_callback);
}
