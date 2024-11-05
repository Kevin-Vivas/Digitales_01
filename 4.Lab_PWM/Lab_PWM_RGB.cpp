#include "mbed.h"

/************************************** ENTRADAS PWM ****************************************************/
PwmOut ROJO(PB_13);
PwmOut VERDE(PB_14);
PwmOut AZUL(PB_15);
DigitalIn Pulsador(PA_8);

/*************************************** LCD ******************************************************************/
BusOut D0_A_D7(PA_1,PA_2,PA_3,PA_4,PA_5,PA_6,PA_7,PB_0); // Pines datos LCD
DigitalOut EN(PA_0); 
DigitalOut RS(PC_15);

char CADENA[50]= {"HOLA MUNDO"};

void R_I(uint8_t COMANDO);
void R_D(uint8_t CARACTER);
void BLANCO_LCD(void);
void AMARILLO_LCD(void);
void ANARANJADO_LCD(void);
void ROJO_ANA_LCD(void);
void ROJO_LCD(void);
void MAGENTA_LCD(void);
//void VIOLETA_LCD(void);
void MORADO_LCD(void);
void AZUL_CLARO_LCD(void);
void AZUL_LCD(void);
void CYAN_LCD(void);
void VERDE_CLARO_LCD(void);
void VERDE_LCD(void);
void APAGADO_LCD(void);
void INICIALIZAR(void);

/*********************************************** FUNCIONES PARA LOS COLORES ******************************/

void BLANCO(void);
void AMARILLO(void);
void ANARANJADO(void);
void ROJO_ANA(void);
void ROJOO(void);
void MAGENTA(void);
void F6(void);
void AZUL_CLARO(void);
void AZULL(void);
void CYAN(void);
void VERDE_CLARO(void);
void VERDEE(void);
void APAGADO(void);

int Color = 0; // Contador inicial

int main() {

    INICIALIZAR();
    ThisThread::sleep_for(1000ms);// Muestra el mensaje anterior durante la cantidad de segundos indicada 

    ROJO.period_ms(1); VERDE.period_ms(1); AZUL.period_ms(1);

    bool ValEst = 1; // Estado anterior del pulsador

    while(1)
    {
       if (Pulsador == 0 && ValEst == 1 )
       {
           Color++;
           if (Color > 13)
           {
               Color = 0;
           }
           ThisThread::sleep_for(500ms);
       }
        ValEst = Pulsador;

        switch (Color)
        {
            case 0: BLANCO();break; // Blanco
            case 1: AMARILLO();break; // Amarillo
            case 2: ANARANJADO();break; // Anaranjado
            case 3: ROJO_ANA();break; // Rojo_ anaranjado
            case 4: ROJOO();break; // Rojo
            case 5: MAGENTA();break; // Magenta
            case 6: F6();break; // Morado
            case 7: AZUL_CLARO();break; // Azul_ Oscuro
            case 8: AZULL();break; // Azul 
            case 9: CYAN();break; // Cyan
            case 10: VERDE_CLARO();break; // Verde oscuro 
            case 11: VERDEE();break; // Verde
            case 12: APAGADO();break; // Apagado
        }   
        ThisThread::sleep_for(500ms);
    }
}

void BLANCO(void){
    ROJO.write(1.0f); VERDE.write(0.2f); AZUL.write(0.1f);
    BLANCO_LCD();
}

void AMARILLO(void){
    ROJO.write(1.0f); VERDE.write(0.2f); AZUL.write(0.0f);
    AMARILLO_LCD();
}

void ANARANJADO(void){
    ROJO.write(0.8f); VERDE.write(0.1f); AZUL.write(0.0f);
    ANARANJADO_LCD();
}

void ROJO_ANA(void){
    ROJO.write(1.0f); VERDE.write(0.09f); AZUL.write(0.0f);
    ROJO_ANA_LCD();
}

void ROJOO(void){
    ROJO.write(1.0f); VERDE.write(0.0f); AZUL.write(0.0f);
    ROJO_LCD();
}

void MAGENTA(void){
    ROJO.write(1.0f); VERDE.write(0.0f); AZUL.write(0.3f);
    MAGENTA_LCD();
}

void F6(void){
    ROJO.write(0.9f); VERDE.write(0.0f); AZUL.write(1.0f);
    MORADO_LCD();
}

void AZUL_CLARO(void){
    ROJO.write(0.2f); VERDE.write(0.1f); AZUL.write(1.0f);
    AZUL_CLARO_LCD();
}

void AZULL(void){
    ROJO.write(0.0f); VERDE.write(0.0f); AZUL.write(1.0f);
    AZUL_LCD();
}

void CYAN(void){
    ROJO.write(0.5f); VERDE.write(0.5f); AZUL.write(0.5f);
    CYAN_LCD();
}

void VERDE_CLARO(void){
    ROJO.write(0.2f); VERDE.write(0.7f); AZUL.write(0.1f);
    VERDE_CLARO_LCD();
}

void VERDEE(void){
    ROJO.write(0.0f); VERDE.write(1.0f); AZUL.write(0.0f);
    VERDE_LCD();
}

void APAGADO(void){
    ROJO.write(0.0f); VERDE.write(0.0f); AZUL.write(0.0f);
    APAGADO_LCD();
}

void R_I(uint8_t COMANDO){
    RS =0;
    // RW =0;
    EN = 0;
    D0_A_D7 = COMANDO;

    EN = 1;
    ThisThread::sleep_for(1ms);
    EN = 0;

    ThisThread::sleep_for(2ms);
}

void R_D(uint8_t CARACTER){
    RS =1;
    // RW =0;
    EN = 0;
    D0_A_D7 = CARACTER;

    EN = 1;
    ThisThread::sleep_for(1ms);
    EN = 0;

    ThisThread::sleep_for(2ms);
}

void BLANCO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R100 G20 B10  ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"    BLANCO      ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void AMARILLO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R100 G20 B0   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }

    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   AMARILLO    ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void ANARANJADO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R80 G10 B0    ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   ANARANJADO   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void ROJO_ANA_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R100 G09 B0   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"    ROJO_ANA    ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void ROJO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   R100 G0 B0   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"     ROJO      ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void MAGENTA_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R100 G0 B30   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"    MAGENTA     ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void MORADO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   R90 G0 B10   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"     MORADO     ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void AZUL_CLARO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R20 G10 B100  ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   AZUL_CLARO   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void AZUL_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   R0 G0 B100   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"     AZUL       ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void CYAN_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R50 G50 B50   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"     CYAN      ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void VERDE_CLARO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  R20 G70 B10   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"  VERDE_CLARO   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}


void VERDE_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   R0 G100 B0   ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"     VERDE      ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}

void APAGADO_LCD(void){
    uint8_t INDICE;
    uint8_t LONGUITUD = 0;

    R_I(128); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"   R0 G0 B0     ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
    R_I(192); // Rutina instruccion (Es la posicion del primer renglon primer caracter)
    LONGUITUD = sprintf(CADENA,"    APAGADO     ");

    for(INDICE=0; INDICE<LONGUITUD; INDICE++)
    {
        R_D(CADENA[INDICE]);
        ThisThread::sleep_for(50ms);
    }
}


void INICIALIZAR(void){
    ThisThread::sleep_for(50ms);
    R_I(0b00110000);

    ThisThread::sleep_for(25ms);
    R_I(0b00110000);

    ThisThread::sleep_for(1ms);
    R_I(0b00110000);

    R_I(0b00111000);    // Activa la segunda linea y estable ce la interfaz en 8 bits
    R_I(0b00001111);    // R_I(0b00001100) Sin cursor y sin parpadeo 
    R_I(0b00000001);    //
}