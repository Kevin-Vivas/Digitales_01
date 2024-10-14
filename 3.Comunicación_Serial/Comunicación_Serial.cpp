#include "mbed.h"

UnbufferedSerial PUERTO_PC(PA_9, PA_10); // (TX, RX)
UnbufferedSerial PUERTO_CEL(PB_10, PB_11); // (TX, RX)

char RX_PC[50], RX_CEL[50];
int index_PC = 0, index_CEL = 0;

// Almacenar las contraseñas de las habitaciones
char contrasena_habitacion[100][5] = {""};

int habitacion_cliente = -1; // Variables para el proceso del cliente
int etapa_cliente = 0;  // Variable para seguir el flujo del cliente

// Funciones
void limpiarBuffer(char* buffer, int& index);
void procesarComandoPC();
void procesarComandoCel();
void leerContrasena(int habitacion);
void validarContrasenaCliente(int habitacion, const char* contrasena_cliente);
void manejarPuertoPC();
void manejarPuertoCel();
void limpiarEntrada(char* entrada, int longitud); // Función para limpiar la entrada

int main() {
    PUERTO_PC.write("\n\r\t\tBIENVENIDO AL HOTEL MAS CHIMBA!\n\r", 43);  
    PUERTO_PC.write("\n\rSeleccione numero de la habitacion (3 caracteres):\n\r", 55);  

    while (1) {
        manejarPuertoPC();
        manejarPuertoCel();
        ThisThread::sleep_for(50ms);
    }
}

// Función para manejar la lectura desde PUERTO_PC
void manejarPuertoPC() {
    if (PUERTO_PC.readable()) {
        PUERTO_PC.read(&RX_PC[index_PC], 1);
        if (RX_PC[index_PC] == '\r') {
            procesarComandoPC();
        } else {
            index_PC++;
            if (index_PC >= 50) limpiarBuffer(RX_PC, index_PC);
        }
    }
}

// Función para manejar la lectura desde PUERTO_CEL
void manejarPuertoCel() {
    if (PUERTO_CEL.readable()) {
        PUERTO_CEL.read(&RX_CEL[index_CEL], 1);
        if (RX_CEL[index_CEL] == '\r') {
            procesarComandoCel();
        } else {
            index_CEL++;
            if (index_CEL >= 50) limpiarBuffer(RX_CEL, index_CEL);
        }
    }
}

// Función para limpiar el buffer y resetear el índice
void limpiarBuffer(char* buffer, int& index) {
    memset(buffer, 0, 50);
    index = 0;
}

// Función para procesar los comandos recibidos por PC (Administrador)
void procesarComandoPC() {
    RX_PC[index_PC] = '\0';    
    char habitacion[4]; 
    strncpy(habitacion, RX_PC, 3);
    habitacion[3] = '\0'; 
    
    habitacion_cliente = atoi(habitacion);
    
    char CADENA[100];
    sprintf(CADENA, "\n\rAsigne la contrasena para habitacion %s (4 caracteres):\n\r", habitacion);
    PUERTO_PC.write(CADENA, strlen(CADENA));

    leerContrasena(habitacion_cliente);
    limpiarBuffer(RX_PC, index_PC);
}

// Función para procesar los comandos recibidos por el celular (Cliente)
void procesarComandoCel() {
    RX_CEL[index_CEL] = '\0';
    char CADENA[100];

    if (etapa_cliente == 1) {  
        sprintf(CADENA, "\n\rIngrese la contraseña para la habitacion %d (4 caracteres):\n\r", habitacion_cliente);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        etapa_cliente = 2;  
        limpiarBuffer(RX_CEL, index_CEL);
    } else if (etapa_cliente == 2) {  
        char contrasena_cliente[50]; 
        strncpy(contrasena_cliente, RX_CEL, 50);
        limpiarEntrada(contrasena_cliente, 50);
        validarContrasenaCliente(habitacion_cliente, contrasena_cliente);
        limpiarBuffer(RX_CEL, index_CEL);
    }
}

// Función para limpiar caracteres no deseados de la entrada
void limpiarEntrada(char* entrada, int longitud) {
    char temp[50] = {0}; 
    int j = 0;

    for (int i = 0; i < longitud; i++) {
        if (entrada[i] != '\n' && entrada[i] != '\r' && entrada[i] != ' ') {
            temp[j++] = entrada[i];
        }
    }
    strncpy(entrada, temp, longitud);
}

// Función para leer y asignar la contraseña (Administrador)
void leerContrasena(int habitacion) {
    char temp[5] = "";
    int index_temp = 0;

    while (index_temp < 4) {
        if (PUERTO_PC.readable()) {
            PUERTO_PC.read(&temp[index_temp], 1);
            index_temp++;
        }
    }
    
    temp[4] = '\0';
    strcpy(contrasena_habitacion[habitacion], temp);

    char CADENA[100];
    sprintf(CADENA, "\n\rLa contraseña es %s\n\r", temp);
    PUERTO_PC.write(CADENA, strlen(CADENA));
    PUERTO_PC.write("\n\rContrasena asignada con exito!\n\r", 34);  

    sprintf(CADENA, "\n\rBienvenido! Por favor, ingrese el numero de la habitacion asignada:\n\r");
    PUERTO_CEL.write(CADENA, strlen(CADENA));
    etapa_cliente = 1;  
}

// Función para validar la contraseña del cliente
void validarContrasenaCliente(int habitacion, const char* contrasena_cliente) {
    char CADENA[100];
    if (strcmp(contrasena_habitacion[habitacion], contrasena_cliente) == 0) {
        sprintf(CADENA, "\n\rAcceso a habitacion %d autorizado.\n\r", habitacion);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        sprintf(CADENA, "\n\rEl usuario ingreso de forma correcta a la habitacion %d.\n\r", habitacion);
        PUERTO_PC.write(CADENA, strlen(CADENA));
        
        // Reiniciar flujo
        habitacion_cliente = -1;
        etapa_cliente = 0;
        index_PC = 0;
        index_CEL = 0;
        memset(RX_PC, 0, sizeof(RX_PC));
        memset(RX_CEL, 0, sizeof(RX_CEL));
        PUERTO_PC.write("\n\rSeleccione numero de la habitacion (3 caracteres):\n\r", 55);
    } else {
        sprintf(CADENA, "\n\rAcceso a habitacion %d denegado. Contrasena incorrecta.\n\r", habitacion);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        sprintf(CADENA, "\n\rIntento de ingreso a la habitacion %d con contraseña incorrecta.\n\r", habitacion);
        PUERTO_PC.write(CADENA, strlen(CADENA));

        sprintf(CADENA, "\n\rPor favor, intente ingresar la contraseña nuevamente:\n\r");
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        etapa_cliente = 2;
    }
}