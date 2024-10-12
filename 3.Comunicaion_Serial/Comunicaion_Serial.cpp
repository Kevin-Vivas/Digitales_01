#include "mbed.h"

UnbufferedSerial PUERTO_PC(PA_9, PA_10, 9600); // (TX, RX)
UnbufferedSerial PUERTO_CEL(PB_10, PB_11, 9600); // (TX, RX)

// Buffers para almacenar la entrada del usuario
char RX_PC[50], RX_CEL[50];
int index_PC = 0, index_CEL = 0;

// Almacenar las contraseñas de las habitaciones
char contrasena_habitacion[100][5] = {""};

// Variables para el proceso del cliente
int habitacion_cliente = -1;
int etapa_cliente = 0;  // Variable para seguir el flujo del cliente

// Prototipos de funciones
void limpiarBuffer(char* buffer, int& index);
void procesarComandoPC();
void procesarComandoCel();
void leerContrasena(int habitacion);
void validarContrasenaCliente(int habitacion, const char* contrasena_cliente);
void manejarPuertoPC();
void manejarPuertoCel();
void iniciarNuevoProceso(); // Nueva función para reiniciar el flujo

int main() {
    while (1) {
        iniciarNuevoProceso(); // Inicia todo el proceso de nuevo
    }
}

// Nueva función para reiniciar todo el proceso
void iniciarNuevoProceso() {
    PUERTO_PC.write("\n\r\t\tBIENVENIDO AL HOTEL MAS CHIMBA!\n\r", 41);
    PUERTO_PC.write("\n\rSeleccione numero de la habitacion (3 caracteres):\n\r", 51);

    // Bucle principal
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
    habitacion_cliente = atoi(RX_PC);
    char CADENA[100];

    sprintf(CADENA, "\n\rAsigne la contrasena para habitacion %d (4 caracteres):\n\r", habitacion_cliente);
    PUERTO_PC.write(CADENA, strlen(CADENA));

    leerContrasena(habitacion_cliente);
    limpiarBuffer(RX_PC, index_PC);
}

// Función para procesar los comandos recibidos por el celular (Cliente)
void procesarComandoCel() {
    RX_CEL[index_CEL] = '\n'; // Asegura que el buffer sea un string
    char CADENA[100];

    if (etapa_cliente == 1) {  // El cliente ingresa la habitacion
        habitacion_cliente = atoi(RX_CEL);
        sprintf(CADENA, "\n\rHas ingresado a la habitacion %d.\n\r", habitacion_cliente);
        PUERTO_CEL.write(CADENA, strlen(CADENA));

        sprintf(CADENA, "\n\rIngrese la contraseña para la habitacion %d:\n\r", habitacion_cliente);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        etapa_cliente = 2;  // Cambia a la etapa de ingresar la contraseña
    } else if (etapa_cliente == 2) {  // El cliente ingresa la contraseña
        validarContrasenaCliente(habitacion_cliente, RX_CEL);
        // No reinicia el flujo aquí para volver a pedir contraseña si es incorrecta
    }

    limpiarBuffer(RX_CEL, index_CEL);
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
    sprintf(CADENA, "\n\rContrasena asignada con exito!\n\r");
    PUERTO_PC.write(CADENA, strlen(CADENA));

    // Enviar mensaje al cliente pidiéndole ingresar la habitación
    sprintf(CADENA, "\n\rBienvenido! Por favor, ingrese el numero de la habitacion asignada:\n\r");
    PUERTO_CEL.write(CADENA, strlen(CADENA));
    etapa_cliente = 1;  // Cambia la etapa del cliente para que ingrese la habitación
}

// Función para validar la contraseña del cliente
void validarContrasenaCliente(int habitacion, const char* contrasena_cliente) {
   // Comprobar si la longitud de la contraseña ingresada es 4
    if (strlen(contrasena_cliente) != 4) {
        char CADENA[100];
        sprintf(CADENA, "\n\rLa contraseña debe tener 4 caracteres. Intente nuevamente:\n\r");
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        return; // Salir de la función sin reiniciar el flujo
    }

    // Validar la contraseña
    if (strcmp(contrasena_habitacion[habitacion], contrasena_cliente) == 0) {
        char CADENA[100];
        sprintf(CADENA, "Acceso a habitacion %d autorizado.", habitacion);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        sprintf(CADENA, "\n\rEl usuario ingreso de forma correcta a la habitacion %d.\n\r", habitacion);
        PUERTO_PC.write(CADENA, strlen(CADENA));
    } else {
        char CADENA[100];
        sprintf(CADENA, "\n\rAcceso a habitacion %d denegado. Contrasena incorrecta.\n\r", habitacion);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
        sprintf(CADENA, "\n\rIntento de ingreso a la habitacion %d sin contraseña correcta.\n\r", habitacion);
        PUERTO_PC.write(CADENA, strlen(CADENA));

        // Volver a pedir la contraseña al cliente
        sprintf(CADENA, "\n\rIngrese nuevamente la contraseña para la habitacion %d:\n\r", habitacion);
        PUERTO_CEL.write(CADENA, strlen(CADENA));
    }
}