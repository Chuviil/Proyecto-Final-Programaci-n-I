#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
//#include "qrcodegen.h"

#define MAX_USUARIOS 100 //Cantidad Maxima de Usuarios
#define MAX_NOMBRE_LEN 35 //Longitud Maxima de Nombre

// Prototipos de las funciones del programa

//Uso General

//Funcion que formatea el nombre quitando espacios antes de ser guardado en el archivo de texto
void FormatearNombrePIngreso(char[] /*NOMBRE*/);

//Funcion que elimina el formato dado para uso dentro de la aplicacion
void FormatearNombrePUso(char[]/*NOMBRE*/);

//Funcion que se le pasa como argumento una cedula y regresa True en caso de encontrarlo y False en caso de no encontrarlo
bool consultarUsuario(int /*CEDULA*/);

//Elimina espacios de los nombres para el ingreso al archivo
void QuitarEspacios(char[] /*NOMBRE*/);

//Obtiene los usuarios del archivo "usuarios.txt" y los almacena dentro de los arreglos que se le pasan
void obtenerUsuarios();

//Obtiene el indice de un arreglo indicando donde esta dicho usuario
int obtenerIndice(int /*CEDULA*/);

//Actualiza el archivo "usuarios.txt" con la nueva informacion proporcionada
void actualizarUsuarios(char[MAX_USUARIOS][MAX_NOMBRE_LEN]/*NOMBRES*/,int[]/*CEDULAS*/,float[]/*SALDOS*/);

//Usuario

//Consulta el saldo de un usario determinado
void ConsultarSaldo();

//Modifica el saldo de el usuario ingresado por el valor ingresado
void DepositarSaldo();

//Adquiere un ticket con el saldo del usuario y lo actualiza
void AdquirirTicket();

//Admin

//Registra un Usuario con la informacion ortorgada
void registrarUsuario();
// ^ Funcion de Ingreso de Datos

//Modifica una de las variables(Nombre, Cedula o Saldo) de el usuario ingresado
void modificarUsuario();

//Elimina el usuario ingresado(CEDULA)
void EliminarUsuario();

// Fin de los prototipos de las funciones del programa

// Prototipos de las funciones de mensajes

//Imprime Opcion Invalida! en color rojo
void OpcionInvalidaM();

//Imprime Cedula Invalida! en color rojo
void CedulaInvalidaM();

//Imprime Usuario Encontrado! en color verde
void UsuarioEncontradoM();

//Imprime Usuario No Encontrado! en color rojo
void UsuarioNoEncontradoM();

//Imprime Nombre No Valido! en color rojo
void NombreInvalidoM();

// Fin de los prototipos de las funciones de mensajes

// Definicion de estructuras

//Estructura de un usuario(Nombre, Cedula, Saldo)
struct usuario{
  char nombre[MAX_NOMBRE_LEN];
  int cedula;
  float saldo;
};

// Fin de definicion de estructuras


// Prototipos de las funciones para codigos QR

// static void genQrCode(const char *text);
// static void printQr(const uint8_t qrcode[]);

// Fin de los prototipos de las funciones para codigos QR