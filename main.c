#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "qrcodegen.h" //Libreria para generacion de codigos QR

#define MAX_USUARIOS 100 //Cantidad Maxima de Usuarios
#define MAX_NOMBRE_LEN 35 //Longitud Maxima de Nombre
// Prototipos de las funciones del programa

//Uso General

//Funcion que formatea el nombre quitando espacios antes de ser guardado en el archivo de texto
void FormatearNombrePIngreso(char[] /*NOMBRE*/);

//Funcion que elimina el formato dado para uso dentro de la aplicacion
void FormatearNombrePUso(char[]/*NOMBRE*/);

//Elimina espacios de los nombres para el ingreso al archivo
void QuitarEspacios(char[] /*NOMBRE*/);

bool consultarUsuario(int /*CEDULA*/,char[] /*NOMBRE*/, float* /*SALDO*/);

//Obtiene los usuarios del archivo "usuarios.txt" y los almacena dentro de los arreglos que se le pasan
int obtenerUsuarios(char[MAX_USUARIOS][MAX_NOMBRE_LEN] /*NOMBRES*/, int[]/*CEDULAS*/, float[]/*SALDOS*/);

//Obtiene el indice de un arreglo indicando donde esta dicho usuario
int obtenerIndice(int /*CEDULA*/);

//Actualiza el archivo "usuarios.txt" con la nueva informacion proporcionada
void actualizarUsuarios(char[MAX_USUARIOS][MAX_NOMBRE_LEN]/*NOMBRES*/,int[]/*CEDULAS*/,float[]/*SALDOS*/);

//Usuario

//Modifica el saldo de el usuario ingresado por el valor ingresado
void DepositarSaldo(int /*CEDULA*/);

//Adquiere un ticket con el saldo del usuario y lo actualiza
void AdquirirTicket(int /*CEDULA*/);

//Admin

//Registra un Usuario con la informacion ortorgada
void registrarUsuario(char[] /*NOMBRE*/, int /*CEDULA*/);
// ^ Funcion de Ingreso de Datos

//Modifica una de las variables(Nombre, Cedula o Saldo) de el usuario ingresado
void modificarUsuario(int /*CEDULA*/);


// Definicion de estructuras

//Estructura de un usuario(Nombre, Cedula, Saldo)
struct usuario{
  char nombre[MAX_NOMBRE_LEN];
  int cedula;
  float saldo;
};

// Fin de definicion de estructuras

// Fin de los prototipos de las funciones del programa

// Prototipos de las funciones para codigos QR

static void genQrCode(const char *text);
static void printQr(const uint8_t qrcode[]);

// Fin de los prototipos de las funciones para codigos QR

//Variables Globales

int cedulas[MAX_USUARIOS];
char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN];
float saldos[MAX_USUARIOS];
int cantUsuarios;
struct usuario usuarioGeneral;

int main(void) 
{
  int opcion;
  char mensaje[100];
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
              do
              {
                system("clear");
                printf("Ingrese su numero de cedula: ");
                scanf("%d", &usuarioGeneral.cedula);
                if(!(usuarioGeneral.cedula>0))
                {
                  system("clear");
                  printf("\033[1;31mCedula Invalida!\033[0m");
                  fflush(stdout);
                  sleep(1);
                }
              }while(!(usuarioGeneral.cedula>0));
              if(consultarUsuario(usuarioGeneral.cedula,usuarioGeneral.nombre,&usuarioGeneral.saldo))
              {
                printf("Usuario Encontrado!\n");
                FormatearNombrePUso(usuarioGeneral.nombre);
                printf("%s con cedula %d su saldo es: %.2f$",usuarioGeneral.nombre,usuarioGeneral.cedula, usuarioGeneral.saldo); 
              }
              else
              {
                printf("\033[1;31mUsuario No Encontrado!\033[0m");
              }
              getchar();
              getchar();
              system("clear");
            break;
            case 2:
              do
              {
                system("clear");
                printf("Ingrese su numero de cedula: ");
                scanf("%d", &usuarioGeneral.cedula);
                if(!(usuarioGeneral.cedula>0))
                {
                  system("clear");
                  printf("\033[1;31mCedula Invalida!\033[0m");
                  fflush(stdout);
                  sleep(1);
                }
              }while(!(usuarioGeneral.cedula>0));
              DepositarSaldo(usuarioGeneral.cedula);
            break;
            case 3:
              system("clear");
              printf("Ingrese su cedula: ");
              scanf("%d", &usuarioGeneral.cedula);
              if(consultarUsuario(usuarioGeneral.cedula,usuarioGeneral.nombre,&usuarioGeneral.saldo))
              {
                AdquirirTicket(usuarioGeneral.cedula);
              }
              else
              {
                printf("Usuario No Encontrado!");
              }
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
              registrarUsuario(usuarioGeneral.nombre, usuarioGeneral.cedula);
            break;
            case 2:
              
            break;
            case 3:
              do
              {
                system("clear");
                printf("Ingrese el numero de cedula del usuario a modificar: ");
                scanf("%d", &usuarioGeneral.cedula);
                if(!(usuarioGeneral.cedula>0))
                {
                  system("clear");
                  printf("\033[1;31mCedula Invalida!\033[0m");
                  fflush(stdout);
                  sleep(1);
                }
              }while(!(usuarioGeneral.cedula>0));
              modificarUsuario(usuarioGeneral.cedula);
            break;
            case 4:
              system("clear");
              printf("Ingrese la cedula del usuario a consultar: ");
              scanf("%d", &usuarioGeneral.cedula);
              if(consultarUsuario(usuarioGeneral.cedula,usuarioGeneral.nombre,&usuarioGeneral.saldo))
              {
               printf("Usuario Encontrado!");
               FormatearNombrePUso(usuarioGeneral.nombre);
               printf("\nNombre: %s\nCedula: %d\nSaldo: %.2f$",usuarioGeneral.nombre,usuarioGeneral.cedula, usuarioGeneral.saldo); 
              }
              else
              {
                printf("Usuario No Encontrado!");
              }
              getchar();
              getchar();
              system("clear");
              usuarioGeneral.cedula = 0;
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

void DepositarSaldo(int cedula)
{
  int indice, opcion;
  float deposito;
  if(consultarUsuario(cedula, usuarioGeneral.nombre, &usuarioGeneral.saldo))
  {
    obtenerUsuarios(nombres, cedulas, saldos);
    indice = obtenerIndice(cedula);
    printf("Usuario Encontrado\n\nNombre: %s\nCedula: %d\nSaldo: %.2f$\nDesea continuar?\n1)Si\t2)No\nElija una opcion: ",nombres[indice],cedulas[indice],saldos[indice]);
    scanf("%d",&opcion);
    system("clear");
    switch(opcion)
    {
      case 1:
        printf("Ingrese cuanto saldo desea depositar: ");
        scanf("%f",&deposito);
        system("clear");
        printf("Gracias por su deposito\n\nNombre: %s\nCedula: %d\nSaldo anterior: %.2f$\nNuevo Saldo: %.2f$ ",nombres[indice],cedulas[indice],saldos[indice],saldos[indice]+deposito);
        saldos[indice] += deposito;
        actualizarUsuarios(nombres,cedulas,saldos);
      break;
      case 2:
        printf("Regresando...");
      break;
      default:
        printf("Opcion Invalida");
      break;
    }
  }
  else
  {
    printf("Usuario No Encontrado!");
  }
  fflush(stdout);
  getchar();
  getchar();
  system("clear");
}

void AdquirirTicket(int cedula)
{
  int indiceUsuario, opcion, transac;
  char objQR[100] = "{cedula: ", temp[MAX_NOMBRE_LEN];
  srand((unsigned) 15124);

  system("clear");
  obtenerUsuarios(nombres, cedulas, saldos);
  indiceUsuario = obtenerIndice(cedula);
  printf("El precio del ticket es de 0.35$ desea continuar?\n1)Si\t2)No\nElija opcion: ");
  scanf("%d", &opcion);
  system("clear");
  switch(opcion)
  {
    case 1:
      if(saldos[indiceUsuario]>=0.35)
      {
        saldos[indiceUsuario] -= 0.35;
        printf("Ticket Adquirido\nSu nuevo saldo es %.2f$\nPresione Enter para imprimir su ticket", saldos[indiceUsuario]);
        getchar();
        getchar();
        system("clear");
        transac = rand();
        sprintf(temp, "%d", usuarioGeneral.cedula);
        strcat(objQR, temp);
        strcat(objQR, ",transaccion: ");
        sprintf(temp, "%d", transac);
        strcat(objQR, temp);
        strcat(objQR, "}");
        genQrCode(objQR);
        actualizarUsuarios(nombres, cedulas, saldos);
        printf("Numero de Transaccion: %d\n", transac);
        printf("Tambien puede usar su numero de transaccion como ticket");
        getchar();
        system("clear");
      } else 
      {
        printf("Saldo Insuficiente!\nSu saldo es de %.2f$",saldos[indiceUsuario]);
      }
    break;
    case 2:
      printf("Accion cancelada por el usuario");
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
}

void registrarUsuario(char nombre[], int cedula)
{
  int opcion;
  float saldo = 0;
  FILE *puntero;
  printf("===========================\n\tRegistro de Usuario\n===========================\n\n");
  printf("Ingrese el nombre: ");
  fgets(nombre,MAX_NOMBRE_LEN,stdin);
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

bool consultarUsuario(int cedula, char nombre[], float *saldo)
{
  bool encontrado = false, finArchivo;
  int cedulatemp;
  FILE *puntero;
  system("clear");
  puntero = fopen("datos/usuarios.txt", "r");
  do
  {
    finArchivo = feof(puntero);
    memset(nombre,0,MAX_NOMBRE_LEN);
    fscanf(puntero,"%d %s %f", &cedulatemp, nombre, saldo);
    if(cedulatemp == cedula)
    {
      encontrado = true;
      finArchivo = true;
    }
  }while(!finArchivo);
  fclose(puntero);
  
  return encontrado;
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

int obtenerUsuarios(char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN], int cedulas[], float saldos[])
{
  memset(nombres,0,MAX_USUARIOS);
  memset(cedulas,0,MAX_USUARIOS);
  memset(saldos,0,MAX_USUARIOS);
  FILE *puntero;
  int index = 0; 
  cantUsuarios = 0;
  puntero = fopen("datos/usuarios.txt", "r");
  while(!feof(puntero))
  {
    fscanf(puntero, "%d %s %f", &cedulas[index], nombres[index], &saldos[index]);
    FormatearNombrePUso(nombres[index]);
    index++;
    cantUsuarios++;
  }
  fclose(puntero);
  cantUsuarios--;
  return cantUsuarios;
}

int obtenerIndice(int cedula)
{
  int indice;
  for(int i = 0;i < sizeof(cedulas);i++)
  {
    if(cedulas[i]==cedula)
    {
      indice = i;
      break;
    }
  }
  return indice;
}

void actualizarUsuarios(char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN], int cedulas[], float saldos[])
{
  FILE *puntero;
  puntero = fopen("datos/usuarios.txt","w");
  for(int i = 0;i < cantUsuarios; i++)
  {
    FormatearNombrePIngreso(nombres[i]);
    fprintf(puntero,"%d %s %.2f\n", cedulas[i], nombres[i], saldos[i]);
  }
  fclose(puntero);
}

void modificarUsuario(int cedula)
{
  struct usuario UsuarioTemp;
  int indice,opcion,modOpcion;
  system("clear");
  if(consultarUsuario(cedula, usuarioGeneral.nombre, &usuarioGeneral.saldo))
  {
    obtenerUsuarios(nombres, cedulas, saldos);
    indice = obtenerIndice(cedula);
    do
    {
      system("clear");
      printf("============================\n\tMODIFICACION USUARIO\n============================\n\nNombre: %s\nCedula: %d\nSaldo: %.2f$\n\nQue desea modificar?\n1)Nombre\n2)Cedula\n3)Saldo\n4)Salir\nElija una opcion: ",nombres[indice],cedulas[indice],saldos[indice]);
      scanf("%d",&opcion);
      switch(opcion)
      {
        case 1:
          system("clear");
          printf("==========================\n\tModificando Nombre\n==========================\n\nIngrese el nuevo nombre: ");
          getchar();
          fgets(UsuarioTemp.nombre,MAX_NOMBRE_LEN,stdin);
          UsuarioTemp.nombre[strcspn(UsuarioTemp.nombre,"\n")] = 0;
          system("clear");
          do
          {
            printf("==========================\n\tModificando Nombre\n==========================\n\nAnterior Nombre: %s\nNuevo Nombre: %s\n\nDesea realizar el cambio?\n1)Si\t2)No\nElija una opcion: ",nombres[indice],UsuarioTemp.nombre);
            scanf("%d",&modOpcion);
            switch(modOpcion)
            {
              case 1:
                FormatearNombrePIngreso(UsuarioTemp.nombre);
                FormatearNombrePUso(UsuarioTemp.nombre);
                strcpy(nombres[indice],UsuarioTemp.nombre);
                actualizarUsuarios(nombres,cedulas,saldos);
                FormatearNombrePUso(nombres[indice]);
              break;
              case 2:
              break;
              default:
                system("clear");
                printf("\n\033[1;31mOpcion Invalida intente de nuevo.\n\n\033[0m");
              break;
            }
          }while(!(modOpcion>0&&modOpcion<3));
        break;
        case 2:
          system("clear");
          printf("==========================\n\tModificando Cedula\n==========================\n\nIngrese la nueva cedula: ");
          scanf("%d", &UsuarioTemp.cedula);
          system("clear");
          do
          {
            printf("==========================\n\tModificando Cedula\n==========================\n\nAnterior Cedula: %d\nNueva Cedula: %d\n\nDesea realizar el cambio?\n1)Si\t2)No\nElija una opcion: ",cedulas[indice], UsuarioTemp.cedula);
            scanf("%d",&modOpcion);
            switch(modOpcion)
            {
              case 1:
                cedulas[indice] = UsuarioTemp.cedula;
                actualizarUsuarios(nombres,cedulas,saldos);
              break;
              case 2:
              break;
              default:
                system("clear");
                printf("\n\033[1;31mOpcion Invalida intente de nuevo.\n\n\033[0m");
              break;
            }
          }while(!(modOpcion>0&&modOpcion<3));
        break;
        case 3:
          system("clear");
          printf("==========================\n\tModificando Saldo\n==========================\n\nIngrese el nuevo saldo: ");
          scanf("%f", &UsuarioTemp.saldo);
          system("clear");
          do
          {
            printf("==========================\n\tModificando Saldo\n==========================\n\nAnterior Saldo: %.2f$\nNuevo Saldo: %.2f$\n\nDesea realizar el cambio?\n1)Si\t2)No\nElija una opcion: ",saldos[indice], UsuarioTemp.saldo);
            scanf("%d",&modOpcion);
            switch(modOpcion)
            {
              case 1:
                saldos[indice] = UsuarioTemp.saldo;
                actualizarUsuarios(nombres,cedulas,saldos);
              break;
              case 2:
              break;
              default:
                system("clear");
                printf("\n\033[1;31mOpcion Invalida intente de nuevo.\n\n\033[0m");
              break;
            }
          }while(!(modOpcion>0&&modOpcion<3));
        break;
        case 4:
          sleep(1);
          system("clear");
        break;
        default:
          printf("\n\033[1;31mOpcion Invalida intente de nuevo.\n\n\033[0m");
        break;
      }
    }while(opcion!=4);
  }
  else
  {
    printf("\n\033[1;31mUsuario No Encontrado!\033[0m");
    fflush(stdout);
    sleep(1);
    system("clear");
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