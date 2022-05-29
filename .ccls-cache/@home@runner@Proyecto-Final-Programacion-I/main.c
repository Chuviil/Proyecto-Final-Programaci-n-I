#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "qrcodegen.h" //Libreria para generacion de codigos QR

// Prototipos de las funciones del programa

void registrarUsuario(char[] /*NOMBRE*/, int /*CEDULA*/);

// Fin de los prototipos de las funciones del programa

// Prototipos de las funciones para codigos QR

static void genQrCode(const char *text);
static void printQr(const uint8_t qrcode[]);

// Fin de los prototipos de las funciones para codigos QR

int main(void) 
{
  int opcion, cedula;
  char nombre[20] ,mensaje[10];
  do
  {
    printf("\t\tSeleccion de Perfil\n1)Usuario\n2)Administrador\n3)Pruebas\n4)Salir\n");
    printf("Escoja opcion: ");
    scanf("%d",&opcion);
    switch(opcion)
    {
      case 1:
        system("clear");
        do
        {
          printf("\t\tUSUARIO\n1)Consultar Saldo\n2)Depositar Saldo\n3)Adquirir ticket\n4)Salir\nEscoja opcion: ");
          scanf("%d",&opcion);
          switch(opcion)
          {
            case 1:
              
            break;
            case 2:
              
            break;
            case 3:
              
            break;
            case 4:
              
            break;
            default:
              system("clear");
              printf("\033[1;31m");
              printf("\nOpcion Invalida intente de nuevo.\n\n");
              printf("\033[0m");
              sleep(1);
              system("clear");
            break;
          }
        }while(opcion!=4);
        opcion = 0;
        sleep(1);
        system("clear");
      break;
      case 2:
        system("clear");
        do
        {
          printf("\t\tADMINISTRADOR\n1)Registrar Usuario\n2)Eliminar Usuario\n3)Modificar Usuario\n4)Consultar/Buscar Usuario\n5)Volver\nEscoja opcion: ");
          scanf("%d",&opcion);
          switch(opcion)
          {
            case 1:
              system("clear");
              registrarUsuario(nombre, cedula);
            break;
            case 2:
              
            break;
            case 3:
              
            break;
            case 4:
              
            break;
            case 5:
              
            break;
            default:
              system("clear");
              printf("\033[1;31m");
              printf("\nOpcion Invalida intente de nuevo.\n\n");
              printf("\033[0m");
              sleep(1);
              system("clear");
            break;
          }
        }while(opcion!=5);
        sleep(1);
        system("clear");
      break;
      case 3:
        system("clear");
        printf("Ingrese el mensaje a convertir en QR: ");
        getchar();
        fgets(mensaje, sizeof mensaje, stdin);
        strtok(mensaje, "\n");
        genQrCode(mensaje);
      break;
      case 4:
        system("clear");
        printf("\033[1;31m88888888888 88 888b      88  \n88          88 8888b     88  \n88          88 88 `8b    88  \n88aaaaa     88 88  `8b   88  \n88\"\"\"\"\"     88 88   `8b  88  \n88          88 88    `8b 88  \n88          88 88     `8888  \n88          88 88      `888\n\nFIN DEL PROGRAMA");
      break;
      default:
        system("clear");
        printf("\033[1;31m");
        printf("\nOpcion Invalida intente de nuevo.\n\n");
        printf("\033[0m");
        sleep(1);
        system("clear");
      break;
    }
  }while(opcion != 4);
}

// Declaracion de funciones del programa

void registrarUsuario(char nombre[], int cedula)
{
  int opcion;
  printf("==========================\n\tRegistro de Usuario\n==========================\n\n");
  printf("Ingrese el nombre: ");
  getchar();
  fgets(nombre,20,stdin);
  nombre[strcspn("nombre","\n")] = 0;
  do
  {
    printf("Ingrese la cedula: ");
    scanf("%d", &cedula);
    if(cedula<=0)
    {
      printf("\n\033[1;31mCedula invalida!\033[0m\n\n");
    }
  }while(!(cedula>0));
  system("clear");
  printf("==========================\n\tRegistro de Usuario\n==========================\n\n");
  printf("Nombre: %s\nCedula: %d\n", nombre, cedula);
  do
  {
    printf("Desea registrar este usuario?\n1)Si\t2)No\nEliga una opcion: ");
    scanf("%d", &opcion);
    if(!(opcion>0&&opcion<3))
    {
      printf("\n\033[1;31mOpción invalida!\033[0m\n\n");
    }
  }while(!(opcion>0&&opcion<3));
  switch(opcion)
  {
    case 1:
      system("clear");
      printf("\033[0;32mUsuario Registrado!\033[0m");
      fflush(stdout);
      sleep(1);
    break;
    case 2:
      system("clear");
      printf("\033[1;31mRegresando...\033[0m");
      fflush(stdout);
      sleep(1);
    break;
  }
  system("clear");
}

// Fin de Declaracion de funciones del programa

// Funciones de la generacion de codigos QR

static void genQrCode(const char *text)
{
  enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;
  uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
}

static void printQr(const uint8_t qrcode[])
{
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}

// Fin de las funciones de generacion de codigos QR