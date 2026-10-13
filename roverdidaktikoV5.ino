/*
comandos
F B L R S  → Movimiento

1 2 3 4 5 6 7 8 → Piano

a → Star Wars
b → Mario
c → Tetris
d → Oda a la Alegría
e → Campanita

q → Detener música

v → Victoria
x → Error
z → Alarma
n → Encendido
m → Robot

V0...V180 → Servo 1

*/

#include <Didaktiko.h>

char incomingByte;


void setup() {

  iniciarRobot();

  Serial.begin(9600);
  led(1, ROSA);

}


void loop() {

  // =====================================
  // ACTUALIZAR MUSICA
  // =====================================
  // Esta linea permite que la musica siga
  // sonando sin detener el resto del robot.

  musicaLoop();
  ledLoop();

  // =====================================
  // RECIBIR BLUETOOTH
  // =====================================

  if (Serial.available() > 0) {

    incomingByte = Serial.read();


    // =====================================
    // MOVIMIENTO
    // =====================================

    if (incomingByte == 'F') {
      avanzar();
    }

    if (incomingByte == 'B') {
      retroceder();
    }

    if (incomingByte == 'L') {
      izquierda();
    }

    if (incomingByte == 'R') {
      derecha();
    }

    if (incomingByte == 'S') {
      stopM();
    }


    // =====================================
    // MINI PIANO
    // =====================================

    if (incomingByte == '1') {
      nota(DO4, 250);
    }

    if (incomingByte == '2') {
      nota(RE4, 250);
    }

    if (incomingByte == '3') {
      nota(MI4, 250);
    }

    if (incomingByte == '4') {
      nota(FA4, 250);
    }

    if (incomingByte == '5') {
      nota(SOL4, 250);
    }

    if (incomingByte == '6') {
      nota(LA4, 250);
    }

    if (incomingByte == '7') {
      nota(SI4, 250);
    }

    if (incomingByte == '8') {
      nota(DO5, 250);
    }


    // =====================================
    // MELODIAS
    // =====================================

    if (incomingByte == 'a') {
      iniciarMusica(STARWARS);
    }

    if (incomingByte == 'b') {
      iniciarMusica(MARIO);
    }

    if (incomingByte == 'c') {
      iniciarMusica(TETRIS);
    }

    if (incomingByte == 'd') {
      iniciarMusica(ODA_ALEGRIA);
    }

    if (incomingByte == 'e') {
      iniciarMusica(CAMPANITA);
    }


    // =====================================
    // DETENER MUSICA
    // =====================================

    if (incomingByte == 'q') {
      detenerMusica();
    }


    // =====================================
    // EFECTOS CORTOS
    // =====================================

    if (incomingByte == 'v') {
      efecto(VICTORIA);
    }

    if (incomingByte == 'x') {
      efecto(ERROR);
    }

    if (incomingByte == 'z') {
      efecto(ALARMA);
    }

    if (incomingByte == 'n') {
      efecto(ENCENDIDO);
    }

    if (incomingByte == 'm') {
      efecto(ROBOT);
    }


    // =====================================
    // SERVOMOTOR 1
    // =====================================
    //
    // Slider Bluetooth Electronics:
    //
    // Minimo:       0
    // Maximo:       180
    // Start String: V
    //
    // Ejemplo:
    // V90
    //
    // =====================================

    if (incomingByte == 'V') {

      int angulo = Serial.parseInt();

      servo(1, angulo);

    }

  }

}