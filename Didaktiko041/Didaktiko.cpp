#include "Didaktiko.h"
#include <Servo.h>


// =====================================
// LED RGB
// =====================================

// Estos tres deben ser PWM
const byte LED_R = 3;
const byte LED_G = 5;
const byte LED_B = 6;

// Seleccion individual de las 4 tiras
const byte LED1_PIN = A0;
const byte LED2_PIN = A1;
const byte LED3_PIN = A2;
const byte LED4_PIN = A3;

// =====================================
// PINES DEL DRIVER DE MOTORES ,  pwm 3, 5, 6, 9, 10 y 11., normales:2,4,7,8,9,12,13
// =====================================

const byte IN1 = 2; //ok
const byte IN2 = 4;
const byte IN3 = 7;
const byte IN4 = 8;


// =====================================
// SERVOMOTORES
// =====================================

const byte SERVO1_PIN = 9;
const byte SERVO2_PIN = 10;
const byte SERVO3_PIN = 11;
const byte SERVO4_PIN = 12;

// =====================================
// BUZZER
// =====================================

const byte BUZZER = 13; //ok

// Colores guardados para cada tira

byte ledRojo[4] = {
  0, 0, 0, 0
};

byte ledVerde[4] = {0, 0, 0, 0};

byte ledAzul[4] = {0, 0, 0, 0};


// Tira que se esta mostrando actualmente

byte ledActual = 0;

// Control del multiplexado

unsigned long tiempoLed = 0;

// Si todos estan apagados,
// no hacemos multiplexado

bool ledsActivos = false;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


// =====================================
// MELODIA: STAR WARS
// =====================================

const int notasStarWars[] = {

  SOL4, SOL4, SOL4,

  DO5, SOL5,

  FA5, MI5, RE5,

  DO5, SOL5,

  FA5, MI5, RE5,

  DO5
};

const int tiemposStarWars[] = {

  350, 350, 350,

  500, 500,

  180, 180, 180,

  500, 500,

  180, 180, 180,

  500
};


// =====================================
// MELODIA: MARIO
// =====================================

const int notasMario[] = {

  MI5, MI5, 0,

  MI5, 0,

  DO5, MI5,

  SOL5
};

const int tiemposMario[] = {

  150, 150, 100,

  150, 100,

  150, 150,

  300
};


// =====================================
// MELODIA: TETRIS
// =====================================

const int notasTetris[] = {

  MI5, SI4, DO5, RE5,
  DO5, SI4,

  LA4, LA4, DO5, MI5,
  RE5, DO5,

  SI4, SI4, DO5, RE5,
  MI5,

  DO5, LA4, LA4,

  RE5, FA5, LA5,
  SOL5, FA5,

  MI5, DO5, MI5,
  RE5, DO5,

  SI4, SI4, DO5, RE5,
  MI5,

  DO5, LA4, LA4
};

const int tiemposTetris[] = {

  200, 100, 100, 200,
  100, 100,

  200, 100, 100, 200,
  100, 100,

  200, 100, 100, 200,
  300,

  200, 200, 400,

  200, 100, 200,
  100, 100,

  200, 100, 200,
  100, 100,

  200, 100, 100, 200,
  300,

  200, 200, 400
};


// =====================================
// MELODIA: ODA A LA ALEGRIA
// =====================================

const int notasOda[] = {

  MI4, MI4, FA4, SOL4,

  SOL4, FA4, MI4, RE4,

  DO4, DO4, RE4, MI4
};

const int tiemposOda[] = {

  250, 250, 250, 250,

  250, 250, 250, 250,

  250, 250, 250, 400
};


// =====================================
// MELODIA: CAMPANITA
// =====================================

const int notasCampanita[] = {

  DO4, DO4,

  SOL4, SOL4,

  LA4, LA4,

  SOL4
};

const int tiemposCampanita[] = {

  250, 250,

  250, 250,

  250, 250,

  500
};


// =====================================
// VARIABLES DEL REPRODUCTOR
// =====================================

const int* notasActuales = NULL;
const int* tiemposActuales = NULL;

int cantidadNotas = 0;
int notaActual = 0;

unsigned long tiempoAnteriorMusica = 0;

int duracionNotaActual = 0;

bool musicaActiva = false;


// =====================================
// FUNCION INTERNA
// REPRODUCIR NOTA ACTUAL
// =====================================

void reproducirNotaActual() {

  if (!musicaActiva) {
    return;
  }

  int frecuencia = notasActuales[notaActual];
  duracionNotaActual = tiemposActuales[notaActual];

  // La nota suena el 85% del tiempo.
  // El resto queda como pequena pausa.

  int tiempoSonando = duracionNotaActual * 85 / 100;


  if (frecuencia > 0) {

    tone(BUZZER,frecuencia,tiempoSonando);

  } else {

    noTone(BUZZER);
  }


  tiempoAnteriorMusica = millis();
}


// =====================================
// INICIAR ROBOT
// =====================================

void iniciarRobot() {

  // Motores

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // =====================================
  // INICIALIZAR LED RGB
  // =====================================

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);

  apagarLeds();

  // Buzzer

  pinMode(BUZZER, OUTPUT);


  // Servomotores

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);


  // Estado inicial

  stopM();
  silencio();


  // Posicion inicial de servos

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}


// =====================================
// AVANZAR
// =====================================

void avanzar() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// =====================================
// RETROCEDER
// =====================================

void retroceder() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// =====================================
// IZQUIERDA
// =====================================

void izquierda() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// =====================================
// DERECHA
// =====================================

void derecha() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// =====================================
// DETENER MOTORES
// =====================================

void stopM() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// =====================================
// NOTA INDIVIDUAL / MINI PIANO
// =====================================

void nota(int frecuencia, int duracion) {

  // Si habia una melodia larga,
  // la detenemos.

  detenerMusica();

  tone(
    BUZZER,
    frecuencia,
    duracion
  );
}


// =====================================
// SONIDO LIBRE
// =====================================

void sonido(int frecuencia, int duracion) {

  detenerMusica();

  tone(
    BUZZER,
    frecuencia,
    duracion
  );
}


// =====================================
// SILENCIO
// =====================================

void silencio() {

  noTone(BUZZER);
}


// =====================================
// INICIAR MUSICA
// =====================================

void iniciarMusica(byte cancion) {

  // Detener cualquier sonido anterior

  noTone(BUZZER);

  notaActual = 0;
  cantidadNotas = 0;


  // ---------------------------------
  // STAR WARS
  // ---------------------------------

  if (cancion == STARWARS) {

    notasActuales =
      notasStarWars;

    tiemposActuales =
      tiemposStarWars;

    cantidadNotas =
      sizeof(notasStarWars) /
      sizeof(notasStarWars[0]);
  }


  // ---------------------------------
  // MARIO
  // ---------------------------------

  else if (cancion == MARIO) {

    notasActuales =
      notasMario;

    tiemposActuales =
      tiemposMario;

    cantidadNotas =
      sizeof(notasMario) /
      sizeof(notasMario[0]);
  }


  // ---------------------------------
  // TETRIS
  // ---------------------------------

  else if (cancion == TETRIS) {

    notasActuales =
      notasTetris;

    tiemposActuales =
      tiemposTetris;

    cantidadNotas =
      sizeof(notasTetris) /
      sizeof(notasTetris[0]);
  }


  // ---------------------------------
  // ODA A LA ALEGRIA
  // ---------------------------------

  else if (cancion == ODA_ALEGRIA) {

    notasActuales =
      notasOda;

    tiemposActuales =
      tiemposOda;

    cantidadNotas =
      sizeof(notasOda) /
      sizeof(notasOda[0]);
  }


  // ---------------------------------
  // CAMPANITA
  // ---------------------------------

  else if (cancion == CAMPANITA) {

    notasActuales =
      notasCampanita;

    tiemposActuales =
      tiemposCampanita;

    cantidadNotas =
      sizeof(notasCampanita) /
      sizeof(notasCampanita[0]);
  }


  // ---------------------------------
  // CANCION NO VALIDA
  // ---------------------------------

  else {

    musicaActiva = false;

    return;
  }


  musicaActiva = true;

  reproducirNotaActual();
}


// =====================================
// ACTUALIZAR MUSICA
// ESTA FUNCION DEBE ESTAR EN loop()
// =====================================

void musicaLoop() {

  if (!musicaActiva) {
    return;
  }


  unsigned long ahora = millis();


  if (ahora - tiempoAnteriorMusica >= (unsigned long)duracionNotaActual) 
{

    notaActual++;


    // ---------------------------------
    // TERMINO LA CANCION
    // ---------------------------------

    if (notaActual >= cantidadNotas) {

      detenerMusica();

      return;
    }


    // ---------------------------------
    // SIGUIENTE NOTA
    // ---------------------------------

    reproducirNotaActual();
  }
}


// =====================================
// DETENER MUSICA
// =====================================

void detenerMusica() {

  musicaActiva = false;

  noTone(BUZZER);

  notaActual = 0;
  cantidadNotas = 0;
}


// =====================================
// EFECTOS CORTOS
// =====================================

void efecto(byte tipo) {

  // Si habia musica larga,
  // primero la detenemos.

  detenerMusica();


  // ---------------------------------
  // VICTORIA
  // ---------------------------------

  if (tipo == VICTORIA) {

    tone(BUZZER, DO5, 120);
    delay(140);

    tone(BUZZER, MI5, 120);
    delay(140);

    tone(BUZZER, SOL5, 120);
    delay(140);

    tone(BUZZER, DO5, 300);
    delay(320);

    noTone(BUZZER);
  }


  // ---------------------------------
  // ERROR
  // ---------------------------------

  else if (tipo == ERROR) {

    tone(BUZZER, RE4, 180);
    delay(200);

    tone(BUZZER, DO4, 350);
    delay(370);

    noTone(BUZZER);
  }


  // ---------------------------------
  // ALARMA
  // ---------------------------------

  else if (tipo == ALARMA) {

    for (byte i = 0; i < 3; i++) {

      tone(BUZZER, LA5, 120);
      delay(140);

      tone(BUZZER, LA4, 120);
      delay(140);
    }

    noTone(BUZZER);
  }


  // ---------------------------------
  // ENCENDIDO
  // ---------------------------------

  else if (tipo == ENCENDIDO) {

    tone(BUZZER, DO4, 70);
    delay(90);

    tone(BUZZER, MI4, 70);
    delay(90);

    tone(BUZZER, SOL4, 70);
    delay(90);

    tone(BUZZER, DO5, 160);
    delay(180);

    noTone(BUZZER);
  }


  // ---------------------------------
  // ROBOT
  // ---------------------------------

  else if (tipo == ROBOT) {

    tone(BUZZER, 300, 70);
    delay(90);

    tone(BUZZER, 500, 70);
    delay(90);

    tone(BUZZER, 700, 70);
    delay(90);

    tone(BUZZER, 400, 150);
    delay(170);

    noTone(BUZZER);
  }
}


// =====================================
// SERVOMOTORES
// =====================================

void servo(byte numero, int angulo) {

  angulo =
    constrain(angulo,0,180);


  if (numero == 1) {

    servo1.write(angulo);
  }


  if (numero == 2) {

    servo2.write(angulo);
  }


  if (numero == 3) {

    servo3.write(angulo);
  }


  if (numero == 4) {

    servo4.write(angulo);
  }
}

// =====================================
// CONFIGURAR UNA TIRA
// =====================================

void led(
  byte numero,
  byte rojo,
  byte verde,
  byte azul
) {

  if (numero < 1 || numero > 4) {
    return;
  }

  byte posicion = numero - 1;

  ledRojo[posicion] = rojo;
  ledVerde[posicion] = verde;
  ledAzul[posicion] = azul;

  // Si tiene algun color,
  // activamos el multiplexado

  if (
    rojo > 0 ||
    verde > 0 ||
    azul > 0
  ) {

    ledsActivos = true;
  }
}


// =====================================
// TODAS DEL MISMO COLOR
// =====================================

void todosLed(
  byte rojo,
  byte verde,
  byte azul
) {

  for (byte i = 0; i < 4; i++) {

    ledRojo[i] = rojo;
    ledVerde[i] = verde;
    ledAzul[i] = azul;
  }

  if (
    rojo > 0 ||
    verde > 0 ||
    azul > 0
  ) {

    ledsActivos = true;

  } else {

    apagarLeds();
  }
}


// =====================================
// APAGAR UNA TIRA
// =====================================

void apagarLed(byte numero) {

  if (numero < 1 || numero > 4) {
    return;
  }

  byte posicion = numero - 1;

  ledRojo[posicion] = 0;
  ledVerde[posicion] = 0;
  ledAzul[posicion] = 0;


  // Revisar si todavia queda
  // algun LED encendido

  ledsActivos = false;

  for (byte i = 0; i < 4; i++) {

    if (
      ledRojo[i] > 0 ||
      ledVerde[i] > 0 ||
      ledAzul[i] > 0
    ) {

      ledsActivos = true;
      break;
    }
  }
}


// =====================================
// APAGAR TODAS
// =====================================

void apagarLeds() {

  for (byte i = 0; i < 4; i++) {

    ledRojo[i] = 0;
    ledVerde[i] = 0;
    ledAzul[i] = 0;
  }

  ledsActivos = false;


  // Apagar seleccion de tiras

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);


  // Apagar RGB

  analogWrite(LED_R, 0);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 0);
}


// =====================================
// MULTIPLEXADO DE LEDS
// =====================================

void ledLoop() {

  // Si no hay LEDs activos,
  // salir inmediatamente

  if (!ledsActivos) {
    return;
  }


  // Cambiar de tira cada 1 ms

  unsigned long ahora = micros();

  if (ahora - tiempoLed < 1000) {
    return;
  }

  tiempoLed = ahora;


  // =====================================
  // APAGAR TODAS ANTES DE CAMBIAR
  // =====================================

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);


  // =====================================
  // COLOCAR COLOR
  // =====================================

  analogWrite(
    LED_R,
    ledRojo[ledActual]
  );

  analogWrite(
    LED_G,
    ledVerde[ledActual]
  );

  analogWrite(
    LED_B,
    ledAzul[ledActual]
  );


  // =====================================
  // ACTIVAR TIRA
  // =====================================

  if (ledActual == 0) {
    digitalWrite(LED1_PIN, HIGH);
  }

  if (ledActual == 1) {
    digitalWrite(LED2_PIN, HIGH);
  }

  if (ledActual == 2) {
    digitalWrite(LED3_PIN, HIGH);
  }

  if (ledActual == 3) {
    digitalWrite(LED4_PIN, HIGH);
  }


  // =====================================
  // SIGUIENTE TIRA
  // =====================================

  ledActual++;

  if (ledActual >= 4) {
    ledActual = 0;
  }
}