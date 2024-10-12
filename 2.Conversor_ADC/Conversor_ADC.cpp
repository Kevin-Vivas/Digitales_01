#include "mbed.h"
                           
UnbufferedSerial SERIAL_CEL(PA_9, PA_10); // TX - RX 
AnalogIn ANALOG(PA_4); // Entrada análoga

// Rutinas
void VOLTAJE(void);

// Variables
float VOL; // Variable auxiliar
int ENTERO = 0, DECIMAL = 0; // Mediciones

int main(void) 
{
    while (1) 
    {
        VOLTAJE();
    }
}

void VOLTAJE(void) 
{
    float FUENTE; // Medición "real"
    uint8_t INDICE;
    int LONGITUD = 0;
    int a = 0;

    FUENTE = ANALOG.read(); // Lee puerto análogo
    FUENTE =  ((FUENTE * 1.020) * 3)* 3.20; // Medición "real" * Voltaje en divisor * # resistencias
    VOL = FUENTE * 100; // "Conversión" a decimal
    ENTERO = (int)VOL / 100; // Parte entera
    DECIMAL = (int)VOL % 100; // Parte decimal

    // Enviar datos por el puerto serie principal
    char CADENA[100];
    LONGITUD = sprintf(CADENA, "\n\r El Voltaje es:  %i . %.2i", ENTERO,DECIMAL);
    a = 0;

    do
    {
        if (SERIAL_CEL.writeable())
        {
            SERIAL_CEL.write(&CADENA[a], 1);
            a++;
        }       

    } while (a < LONGITUD);
    
    ThisThread::sleep_for(1s);
}