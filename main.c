#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "qrcodegen.h" //Libreria para generacion de codigos QR

// Prototipos de las funciones del programa

void registrarUsuario(char[] /*NOMBRE*/, int /*CEDULA*/);
// ^ Funcion de Ingreso de Datos

void FormatearNombrePIngreso(char[] /*NOMBRE*/);
void QuitarEspacios(char[] /*NOMBRE*/);
void FormatearNombrePUso(char[]/*NOMBRE*/);

void consultarUsuario(int /*CEDULA*/);

// Definicion de estructuras

struct usuario{
  char nombre[35];
  int cedula;
  float saldo;
};

// Fin de definicion de estructuras

// Fin de los prototipos de las funciones del programa

// Prototipos de las funciones para codigos QR

static void genQrCode(const char *text);
static void printQr(const uint8_t qrcode[]);

// Fin de los prototipos de las funciones para codigos QR

int main(void) 
{
  int opcion, cedula;
  char nombre[35] ,mensaje[100];
  do
  {
    printf("===========================\n\tSeleccion de Perfil\n===========================\n\n1)Usuario\n2)Administrador\n3)Pruebas\n4)Salir\n");
    printf("Escoja opcion: ");
    scanf("%d",&opcion);
    switch(opcion)
    {
      case 1:
        system("clear");
        do
        {
          printf("===============\n\tUSUARIO\n===============\n\n1)Consultar Saldo\n2)Depositar Saldo\n3)Adquirir ticket\n4)Salir\nEscoja opcion: ");
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
              printf("\n\033[1;31mOpcion Invalida intente de nuevo.\n\n\033[0m");
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
          printf("=====================\n\tADMINISTRADOR\n=====================\n\n1)Registrar Usuario\n2)Eliminar Usuario\n3)Modificar Usuario\n4)Consultar/Buscar Usuario\n5)Volver\nEscoja opcion: ");
          scanf("%d",&opcion);
          switch(opcion)
          {
            case 1:
              system("clear");
              getchar();
              registrarUsuario(nombre, cedula);
            break;
            case 2:
              
            break;
            case 3:
              
            break;
            case 4:
              system("clear");
              printf("Ingrese la cedula del usuario a consultar: ");
              scanf("%d", &cedula);
              consultarUsuario(cedula);
              cedula = 0;
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
        printf("\033[1;31m _____ ___ _   _ \n|  ___|_ _| \\ | |\n| |_   | ||  \\| |\n|  _|  | || |\\  |\n|_|   |___|_| \\_|\n\nFIN DEL PROGRAMA");
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
  float saldo = 0;
  FILE *puntero;
  printf("===========================\n\tRegistro de Usuario\n===========================\n\n");
  printf("Ingrese el nombre: ");
  fgets(nombre,35,stdin);
  nombre[strcspn(nombre,"\n")] = 0;
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
  printf("===========================\n\tRegistro de Usuario\n===========================\n\n");
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
      FormatearNombrePIngreso(nombre);
      puntero = fopen("datos/usuarios.txt", "a");
      fprintf(puntero,"%d %s %.2f\n", cedula, nombre, saldo);
      fclose(puntero);
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

void FormatearNombrePIngreso(char nombre[])
{
  int i;
  char temp;
  for(i=0;i<strlen(nombre);i++)
  {
    nombre[i] = tolower(nombre[i]);
  }
  nombre[0] = toupper(nombre[0]);
  for(i=0;i<strlen(nombre);i++)
  {
    if(nombre[i]==' ')
    {
      nombre[i+1] = toupper(nombre[i+1]);
    }
  }
  QuitarEspacios(nombre);
}

void QuitarEspacios(char nombre[])
{
  int i,j;
  char temp;
  for(i=0;i<strlen(nombre);i++)
  {
    if(nombre[i] == ' ')
    {
      for(j=i;j<=strlen(nombre);j++)
      {
        temp = nombre[j+1];
        nombre[j] = temp;
      }
    }
  }
}

void consultarUsuario(int cedula)
{
  struct usuario usuario1;
  bool encontrado = false, finArchivo;
  FILE *puntero;
  system("clear");
  puntero = fopen("datos/usuarios.txt", "r");
  do
  {
    finArchivo = feof(puntero);
    memset(usuario1.nombre,0,sizeof usuario1.nombre);
    fscanf(puntero,"%d %s %f", &usuario1.cedula, usuario1.nombre, &usuario1.saldo);
    if(usuario1.cedula == cedula)
    {
      encontrado = true;
      finArchivo = true;
    }
  }while(!finArchivo);
  fclose(puntero);
  
  if(encontrado)
  {
    printf("Usuario Encontrado!");
    FormatearNombrePUso(usuario1.nombre);
    printf("\nNombre: %s\nCedula: %d\nSaldo: %.2f$",usuario1.nombre,cedula, usuario1.saldo);
  }
  else
  {
    printf("Usuario No Encontrado!");
  }
  getchar();
  getchar();
  system("clear");
}

void FormatearNombrePUso(char nombre[])
{
  int h,i,j,k,l,m;
  char temp1[25];
  h = strlen(nombre);
  for(i=1;i<h;i++)
  {
    if(isupper(nombre[i])>0)
    {
      k=0;
      l = strlen(nombre);
      for(j=i;j<=l;j++)
      {
        temp1[k] = nombre[j];
        k++;
      }
      nombre[i] = ' ';
      k = 0;
      m = strlen(nombre)+1;
      for(j=i+1;j<m;j++)
      {
        nombre[j] = temp1[k];
        k++;
      }
      i++;
    }
  }
}

// Fin de Declaracion de funciones del programa

// Funciones de la generacion de codigos QR

static void genQrCode(const char *text)
{
  enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;
  uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
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