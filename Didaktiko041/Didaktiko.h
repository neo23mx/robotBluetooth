#ifndef DIDAKTIKO_H
#define DIDAKTIKO_H

#include <Arduino.h>


// =====================================
// NOTAS MUSICALES
// =====================================

// OCTAVA 4
#define DO4    262
#define DOS4   277
#define RE4    294
#define RES4   311
#define MI4    330
#define FA4    349
#define FAS4   370
#define SOL4   392
#define SOLS4  415
#define LA4    440
#define LAS4   466
#define SI4    494

// OCTAVA 5
#define DO5    523
#define DOS5   554
#define RE5    587
#define RES5   622
#define MI5    659
#define FA5    698
#define FAS5   740
#define SOL5   784
#define SOLS5  831
#define LA5    880
#define LAS5   932
#define SI5    988


// =====================================
// MELODIAS LARGAS
// =====================================

#define STARWARS      1
#define MARIO         2
#define TETRIS        3
#define ODA_ALEGRIA   4
#define CAMPANITA     5


// =====================================
// EFECTOS CORTOS
// =====================================

#define VICTORIA      20
#define ERROR         21
#define ALARMA        22
#define ENCENDIDO     23
#define ROBOT         24


// =====================================
// INICIALIZACION
// =====================================

void iniciarRobot();


// =====================================
// MOVIMIENTO
// =====================================

void avanzar();
void retroceder();
void izquierda();
void derecha();
void stopM();


// =====================================
// SONIDO / PIANO
// =====================================

void nota(int frecuencia, int duracion);
void sonido(int frecuencia, int duracion);
void silencio();


// =====================================
// MUSICA NO BLOQUEANTE
// =====================================

void iniciarMusica(byte cancion);
void musicaLoop();
void detenerMusica();


// =====================================
// EFECTOS CORTOS
// =====================================

void efecto(byte tipo);


// =====================================
// SERVOMOTORES
// =====================================

void servo(byte numero, int angulo);

// =====================================
// COLORES RGB
// =====================================

#define ROJO       255, 0, 0
#define VERDE      0, 255, 0
#define AZUL       0, 0, 255
#define BLANCO     255, 255, 255
#define AMARILLO   255, 255, 0
#define CIAN       0, 255, 255
#define MAGENTA    255, 0, 255

#define ROSA       255, 105, 180
#define MENTA      152, 255, 152
#define NARANJA    255, 120, 0
#define MORADO     128, 0, 255
#define TURQUESA   64, 224, 208
#define LIMA       180, 255, 0


// =====================================
// LED RGB
// =====================================

void led(byte numero, byte rojo, byte verde, byte azul);
void todosLed(byte rojo, byte verde, byte azul);

void apagarLed(byte numero);
void apagarLeds();

void ledLoop();

#endif