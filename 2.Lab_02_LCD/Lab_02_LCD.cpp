#include "mbed.h"
#include "mbed_wait_api.h"
#include <cstdint>
// #include <cstdint>

// Blinking rate in milliseconds
// Blinking rate in milliseconds
#define BLINKING_RATE 500 // Define el tiempo en milisegundos
BusOut LEDS(PB_12, PB_13, PB_14, PB_15, PA_8, PA_9, PA_10, PA_11, PA_12, PA_15,
            PB_3, PB_4, PB_5, PB_6, PB_7, PB_8); // Secuencia 0 para probar

BusOut LEDS_1(PA_15, PA_10, PB_13, PB_12, PA_11, PA_12, PB_5, PB_6, PB_7, PB_8,
              PB_4, PA_8, PB_15, PB_14, PA_9, PB_3); // Secuencia 1

BusOut LEDS_2A(PB_6, PA_15, PA_12, PA_11, PB_12, PA_10); // Secuencia 2A
BusOut LEDS_2B(PB_14, PA_9, PA_8, PB_4, PB_8, PB_3);     // Secuencia 2B

BusOut LEDS_3A(PB_12, PB_13, PB_14, PB_15); // Secuencia 2B
BusOut LEDS_3B(PA_11, PA_10, PA_9, PA_8);   // Secuencia 2B
BusOut LEDS_3C(PA_12, PA_15, PB_3, PB_4);   // Secuencia 2B
BusOut LEDS_3D(PB_5, PB_6, PB_7, PB_8);     // Secuencia 2B

BusOut LEDS_4(PB_4, PB_7, PB_6, PA_12, PA_11, PB_13, PB_14, PA_8, PB_3, PA_15,
              PA_10, PA_9);

BusOut LEDS_5A(PA_11, PB_6, PB_3, PB_8, PB_4, PB_7, PA_15,
               PB_5); // Secuencia 5A
BusOut LEDS_5B(PA_12, PB_13, PA_9, PB_15, PA_8, PB_14, PA_10,
               PB_12); // Secuencia 5B

/*************************************** LCD
 * ******************************************************************/

BusOut D0_A_D7(PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PB_0); // Secuencia 2A
DigitalOut EN(PA_0);
DigitalOut RS(PC_15);
// 123456789
char CADENA[50] = {"HOLA MUNDO"};

uint8_t CADENA2[50] = {
    "KEVIN VIVAS     "}; // No es recomendable para utilizar letras
uint8_t CADENA3[50] = {"JESUS ZULUAGA   "};

void R_I(uint8_t COMANDO);
void R_D(uint8_t CARACTER);
void MENSAJE(void); // Mensaje de la primera secuencia
void MENSAJE2(void);
void MENSAJE3(void); // Mensaje de la segunda secuencia
void MENSAJE4(void); // Mensaje de la tercera secuencia
void MENSAJE5(void); // Mensaje de la cuarta secuencia
void MENSAJE6(void); // Mensaje de la quinta secuencia
void INICIALIZAR(void);
//

BusIn INTERRUPTOR(PB_11, PB_10,
                  PB_1); // Bus del Interreptor para elegir las secuencias

void F0(void); // Funcion para la secuencia de prueba
void F1(void); // Funcion para la Primera secuencia
void F2(void); // Funcion para la segunda secuencia
void F3(void); // Funcion para la tercera secucncia
void F4(void); // Funcion para la cuarta secuencia
void F5(void); // Funcion para la quinta secuencia

uint8_t bandera = 255;

int main(void) {

  /* MENSAJE2();*/
  R_I(1); // Rutina instruccion, borra la pantalla y ubica el cursor en el home
          // Es decir en el primer renglon primer caracter

  INICIALIZAR();
  MENSAJE2();
  ThisThread::sleep_for(5000ms); // Muestra el mensaje anterior durante la
                                 // cantidad de segundos indicada
  R_I(1);

  while (1) {

    switch (INTERRUPTOR)
    // implica leer  puerto de la selecion (dip swich)
    //  determinar la secuencia que debe realizar
    {
    case 0:
      F0();
      break;
    case 1:
      F1();
      break;
    case 2:
      F2();
      break;
    case 3:
      F3();
      break;
    case 4:
      F4();
      break;
    case 5:
      F5();
      break;
    default:
      LEDS = 0;
      break;
    }
  }
}

void F0(void) {

  LEDS = 0;
  if (bandera != 0) {
    bandera = 0;
    R_I(1);
  } else {
  }
  uint16_t AA = 0;
  uint8_t i = 0;

  ThisThread::sleep_for(400ms); // Usa esta función para esperar
  LEDS = 1;
  ThisThread::sleep_for(400ms); // Usa esta función para esperar
}

void F1(void) {

  LEDS = 0;

  if (bandera == 0) {
    MENSAJE();
    bandera = 1;
    ThisThread::sleep_for(3000ms);
    R_I(1);
  } else {
  }

  uint16_t AA = 0;
  uint8_t i = 0;

  ThisThread::sleep_for(400ms); // Usa esta función para esperar

  AA = 1;

  for (i = 0; i < 16; i++) {
    LEDS_1 = AA;
    ThisThread::sleep_for(400ms); // Usa esta función para esperar
    AA = (AA << 1) | 1;
  }

  AA = 65534;

  for (i = 0; i < 15; i++) {
    LEDS_1 = AA;
    ThisThread::sleep_for(400ms);
    AA = AA << 1;
  }
}

void F2(void) {

  LEDS = 0;

  if (bandera != 0) {
    MENSAJE3();
    bandera = 0;
    ThisThread::sleep_for(3000ms);
    R_I(1);
  } else {
  }

  uint8_t AA, BB, i;
  AA = BB = i = 0;

  ThisThread::sleep_for(400ms); // Usa esta función para esperar

  AA = 1;
  BB = 1;

  for (i = 0; i < 8; i++) {
    LEDS_2A = AA;
    LEDS_2B = BB;
    ThisThread::sleep_for(400ms);
    AA = (AA << 1) | 1;
    BB = (BB << 1) | 1;
  }

  AA = 31;
  BB = 31;

  for (i = 0; i < 7; i++) {
    LEDS_2A = AA;
    LEDS_2B = BB;
    ThisThread::sleep_for(400ms);
    AA = AA >> 1;
    BB = BB >> 1;
  }
}

void F3(void) {

  LEDS = 0;
  if (bandera == 0) {
    MENSAJE4();
    bandera = 1;
    ThisThread::sleep_for(3000ms);
    R_I(1);
  } else {
  }

  uint8_t AA, BB, i;
  AA = BB = i = 0;

  ThisThread::sleep_for(400ms); // Usa esta función para esperar

  AA = 1;

  for (i = 0; i < 7; i++) {

    LEDS_3D = LEDS_3C;
    LEDS_3C = LEDS_3B;
    LEDS_3B = LEDS_3A;
    LEDS_3A = AA;
    ThisThread::sleep_for(400ms);
    AA = (AA << 1) | 1;
  }

  BB = 7;

  for (i = 0; i < 6; i++) {

    LEDS_3A = LEDS_3B;
    LEDS_3B = LEDS_3C;
    LEDS_3C = LEDS_3D;

    LEDS_3D = BB;

    ThisThread::sleep_for(400ms);

    BB = BB >> 1;
  }
}

void F4(void) {

  LEDS = 0;

  if (bandera != 0) {
    MENSAJE5();
    bandera = 0;
    ThisThread::sleep_for(3000ms);
    R_I(1);
  } else {
  }

  uint16_t AA = 0;
  uint8_t i = 0;

  ThisThread::sleep_for(400ms); // Usa esta función para esperar

  AA = 1;

  for (i = 0; i < 12; i++) {
    LEDS_4 = AA;
    ThisThread::sleep_for(400ms); // Usa esta función para esperar
    AA = (AA << 1) | 1;
  }

  AA = 2047;

  for (i = 0; i < 11; i++) {
    LEDS_4 = AA;
    ThisThread::sleep_for(400ms);
    AA = AA >> 1;
  }
}

void F5(void) {

  LEDS = 0;

  if (bandera == 0) {
    MENSAJE6();
    bandera = 1;
    ThisThread::sleep_for(3000ms);
    R_I(1);
  } else {
  }

  uint8_t AA, BB, i;
  AA = BB = i = 0;

  ThisThread::sleep_for(400ms); // Usa esta función para esperar

  AA = 1;
  BB = 1;

  for (i = 0; i < 4; i++) {
    LEDS_5A = AA;
    LEDS_5B = BB;
    ThisThread::sleep_for(400ms);
    AA = (AA << 1) | 1;
    BB = (BB << 1) | 1;
    ThisThread::sleep_for(400ms);
  }

  LEDS = 0;
  ThisThread::sleep_for(400ms);

  AA = 16;
  BB = 16;

  for (i = 0; i < 4; i++) {
    LEDS_5A = AA;
    LEDS_5B = BB;
    ThisThread::sleep_for(400ms);
    AA = (AA << 1) | AA;
    BB = (BB << 1) | BB;
  }
}

void R_I(uint8_t COMANDO) {
  RS = 0;
  // RW =0;
  EN = 0;
  D0_A_D7 = COMANDO;

  EN = 1;
  ThisThread::sleep_for(1ms);
  EN = 0;

  ThisThread::sleep_for(2ms);
}

void R_D(uint8_t CARACTER) {
  RS = 1;
  // RW =0;
  EN = 0;
  D0_A_D7 = CARACTER;

  EN = 1;
  ThisThread::sleep_for(1ms);
  EN = 0;

  ThisThread::sleep_for(2ms);
}

void MENSAJE(void) { // Mensaje para la primera secuencia

  R_I(201);
  R_D('M');
  ThisThread::sleep_for(800ms);
  R_I(133);
  R_D('M');
  ThisThread::sleep_for(800ms);
  R_I(131);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(202);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(130);
  R_D('W');
  ThisThread::sleep_for(800ms);
  R_I(199);
  R_D('G');
  ThisThread::sleep_for(800ms);
  R_I(200);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(132);
  R_D('R');
  ThisThread::sleep_for(800ms);

}

void MENSAJE3(void) { // Mensaje para la segunda secuencia

  R_I(198);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(134);
  R_D('J');
  ThisThread::sleep_for(800ms);
  R_I(130);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(138);
  R_D('L');
  ThisThread::sleep_for(800ms);
  R_I(137);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(201);
  R_D('S');
  ThisThread::sleep_for(800ms);
  R_I(132);
  R_D('P');
  ThisThread::sleep_for(800ms);
  R_I(200);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(197);
  R_D('R');
  ThisThread::sleep_for(800ms);
  R_I(135);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(133);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(199);
  R_D('V');
  ThisThread::sleep_for(800ms);
  R_I(131);
  R_D('S');
  ThisThread::sleep_for(800ms);
}

void MENSAJE4(void) { // Mensaje para la tercera secuencia

  R_I(198);
  R_D('R');
  ThisThread::sleep_for(800ms);
  R_I(204);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(129);
  R_D('D');
  ThisThread::sleep_for(800ms);
  R_I(136);
  R_D('L');
  ThisThread::sleep_for(800ms);
  R_I(194);
  R_D('C');
  ThisThread::sleep_for(800ms);
  R_I(133);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(201);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(203);
  R_D('N');
  ThisThread::sleep_for(800ms);
  R_I(131);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(196);
  R_D('N');
  ThisThread::sleep_for(800ms);
  R_I(195);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(199);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(130);
  R_D('I');
  ThisThread::sleep_for(800ms);
  R_I(200);
  R_D('T');
  ThisThread::sleep_for(800ms);
  R_I(202);
  R_D('R');
  ThisThread::sleep_for(800ms);
  R_I(132);
  R_D('G');
  ThisThread::sleep_for(800ms);
  R_I(135);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(134);
  R_D('N');
  ThisThread::sleep_for(800ms);
}
void MENSAJE5(void) { // Mensaje para la cuarta secuencia

  R_I(133);
  R_D('I');
  ThisThread::sleep_for(800ms);
  R_I(200);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(203);
  R_D('I');
  ThisThread::sleep_for(800ms);
  R_I(195);
  R_D('F');
  ThisThread::sleep_for(800ms);
  R_I(130);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(138);
  R_D('D');
  ThisThread::sleep_for(800ms);
  R_I(198);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(135);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(132);
  R_D('P');
  ThisThread::sleep_for(800ms);
  R_I(201);
  R_D('C');
  ThisThread::sleep_for(800ms);
  R_I(202);
  R_D('C');
  ThisThread::sleep_for(800ms);
  R_I(136);
  R_D('L');
  ThisThread::sleep_for(800ms);
  R_I(197);
  R_D('B');
  ThisThread::sleep_for(800ms);
  R_I(134);
  R_D('R');
  ThisThread::sleep_for(800ms);
  R_I(199);
  R_D('N');
  ThisThread::sleep_for(800ms);
  R_I(131);
  R_D('S');
  ThisThread::sleep_for(800ms);
  R_I(139);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(196);
  R_D('I');
  ThisThread::sleep_for(800ms);
}
void MENSAJE6(void) { // Mensaje para la Quinta secuencia

  R_I(195);
  R_D('D');
  ThisThread::sleep_for(800ms);
  R_I(139);
  R_D('N');
  ThisThread::sleep_for(800ms);
  R_I(131);
  R_D('S');
  ThisThread::sleep_for(800ms);
  R_I(199);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(136);
  R_D('S');
  ThisThread::sleep_for(800ms);
  R_I(201);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(134);
  R_D('T');
  ThisThread::sleep_for(800ms);
  R_I(202);
  R_D('L');
  ThisThread::sleep_for(800ms);
  R_I(197);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(132);
  R_D('A');
  ThisThread::sleep_for(800ms);
  R_I(138);
  R_D('E');
  ThisThread::sleep_for(800ms);
  R_I(196);
  R_D('I');
  ThisThread::sleep_for(800ms);
  R_I(135);
  R_D('O');
  ThisThread::sleep_for(800ms);
  R_I(133);
  R_D('L');
  ThisThread::sleep_for(800ms);
  R_I(198);
  R_D('G');
  ThisThread::sleep_for(800ms);
  R_I(200);
  R_D('N');
  ThisThread::sleep_for(800ms);
}

void MENSAJE2(void) {
  uint8_t INDICE;
  uint8_t LONGUITUD = 0;

  R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer
            // caracter)

  LONGUITUD = sprintf(CADENA, "JESUS ZULUAGA");

  for (INDICE = 0; INDICE < LONGUITUD; INDICE++) {
    R_D(CADENA[INDICE]);
    ThisThread::sleep_for(50ms);
  }

  R_I(192); // Rurina instruccion (Es la posicion del segundo renglon primer
            // caracter)

  for (INDICE = 0; INDICE <= 16; INDICE++) {
    R_D(CADENA2[INDICE]);
    ThisThread::sleep_for(50ms);
  }
}

void INICIALIZAR(void) {
  ThisThread::sleep_for(50ms);
  R_I(0b00110000);

  ThisThread::sleep_for(25ms);
  R_I(0b00110000);

  ThisThread::sleep_for(1ms);
  R_I(0b00110000);

  R_I(0b00111000); // Activa la segunda linea y estable ce la interfaz en 8 bits
  R_I(0b00001100); // R_I(0b00001100) Sin cursor y sin parpadeo
  R_I(0b00000001);
       //
}