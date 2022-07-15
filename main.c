#include <stdio.h>
#include "ProyectoLib.h"

int main(void)
{
  int opcion;
  char mensaje[100];
  do
  {
    printf("===========================\n\tSeleccion de Perfil\n===========================\n\n1)Usuario\n2)Administrador\n3)Pruebas\n4)Salir\n");
    printf("Escoja opcion: ");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
      system("clear");
      do
      {
        printf("===============\n\tUSUARIO\n===============\n\n1)Consultar Saldo\n2)Depositar Saldo\n3)Adquirir ticket\n4)Salir\nEscoja opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
          ConsultarSaldo();
          break;
        case 2:
          DepositarSaldo();
          break;
        case 3:
          AdquirirTicket();
          break;
        case 4:

          break;
        default:
          system("clear");
          OpcionInvalidaM();
          getchar();
          getchar();
          break;
        }
      } while (opcion != 4);
      opcion = 0;
      system("clear");
      break;
    case 2:
      system("clear");
      do
      {
        printf("=====================\n\tADMINISTRADOR\n=====================\n\n1)Registrar Usuario\n2)Eliminar Usuario\n3)Modificar Usuario\n4)Consultar/Buscar Usuario\n5)Volver\nEscoja opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
          registrarUsuario();
          break;
        case 2:
          system("clear");
          EliminarUsuario();
          break;
        case 3:
          modificarUsuario();
          break;
        case 4:
          system("clear");
          printf("Ingrese la cedula del usuario a consultar: ");
          scanf("%d", &usuarioGeneral.cedula);
          if (consultarUsuario(usuarioGeneral.cedula, usuarioGeneral.nombre, &usuarioGeneral.saldo))
          {
            printf("Usuario Encontrado!");
            FormatearNombrePUso(usuarioGeneral.nombre);
            printf("\nNombre: %s\nCedula: %d\nSaldo: %.2f$", usuarioGeneral.nombre, usuarioGeneral.cedula, usuarioGeneral.saldo);
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
          OpcionInvalidaM();
          break;
        }
      } while (opcion != 5);
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
  } while (opcion != 4);
}