#include "ProyectoLib.h"

// Variables Globales

extern int cedulas[MAX_USUARIOS];
extern char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN];
extern float saldos[MAX_USUARIOS];
extern int cantUsuarios;
extern struct usuario usuarioGeneral;

void ConsultarSaldo()
{
    int indice;
    system("clear");
    do
    {
        printf("Ingrese el numero de cedula a consultar: ");
        scanf("%d", &usuarioGeneral.cedula);
        if (!(usuarioGeneral.cedula > 0))
        {
            system("clear");
            CedulaInvalidaM();
            getchar();
            getchar();
            system("clear");
        }
    } while (!(usuarioGeneral.cedula > 0));
    if (consultarUsuario(usuarioGeneral.cedula))
    {
        system("clear");
        UsuarioEncontradoM();
        indice = obtenerIndice(usuarioGeneral.cedula);
        printf("%s con cedula %d su saldo es: %.2f$", nombres[indice], cedulas[indice], saldos[indice]);
    }
    else
    {
        system("clear");
        UsuarioNoEncontradoM();
    }
    getchar();
    getchar();
    system("clear");
}

void DepositarSaldo()
{
    int indice, opcion;
    float deposito;
    system("clear");
    do
    {
        printf("Ingrese su numero de cedula: ");
        scanf("%d", &usuarioGeneral.cedula);
        if (!(usuarioGeneral.cedula > 0))
        {
            system("clear");
            CedulaInvalidaM();
        }
    } while (!(usuarioGeneral.cedula > 0));
    if (consultarUsuario(usuarioGeneral.cedula))
    {
        indice = obtenerIndice(usuarioGeneral.cedula);
        UsuarioEncontradoM();
        printf("\nNombre: %s\nCedula: %d\nSaldo: %.2f$\nDesea continuar?\n1)Si\t2)No", nombres[indice], cedulas[indice], saldos[indice]);
        do
        {
            printf("\nElija una opcion: ");
            scanf("%d", &opcion);
            if (!(opcion > 0 && opcion < 3))
            {
                OpcionInvalidaM();
            }
        } while (!(opcion > 0 && opcion < 3));
        system("clear");
        switch (opcion)
        {
        case 1:
            do
            {
                printf("Ingrese cuanto saldo desea depositar: ");
                scanf("%f", &deposito);
                if (!(deposito > 0))
                {
                    printf("\n\033[1;31mCantidad Invalida!\033[0m\n");
                }
            } while (!(deposito > 0));
            system("clear");
            printf("Gracias por su deposito\n\nNombre: %s\nCedula: %d\nSaldo anterior: %.2f$\nNuevo Saldo: %.2f$ ", nombres[indice], cedulas[indice], saldos[indice], saldos[indice] + deposito);
            saldos[indice] += deposito;
            actualizarUsuarios(nombres, cedulas, saldos);
            break;
        case 2:
            printf("\n\033[1;31mAccion cancelada por el Usuario!\033[0m\n");
            break;
        default:
            OpcionInvalidaM();
            break;
        }
    }
    else
    {
        UsuarioNoEncontradoM();
    }
    fflush(stdout);
    getchar();
    getchar();
    system("clear");
}

void AdquirirTicket()
{
    int indiceUsuario, opcion, transac;
    char objQR[100] = "{cedula: ", temp[MAX_NOMBRE_LEN];
    srand((unsigned)15124);

    system("clear");
    do
    {
        printf("Ingrese el numero de cedula: ");
        scanf("%d", &usuarioGeneral.cedula);
        if (!(usuarioGeneral.cedula > 0))
        {
            system("clear");
            CedulaInvalidaM();
            getchar();
            getchar();
            system("clear");
        }
    } while (!(usuarioGeneral.cedula > 0));
    if (consultarUsuario(usuarioGeneral.cedula))
    {
        system("clear");
        obtenerUsuarios();
        indiceUsuario = obtenerIndice(usuarioGeneral.cedula);
        UsuarioEncontradoM();
        printf("El precio del ticket es de 0.35$ desea continuar?\n1)Si\t2)No");
        do
        {
            printf("\nElija opcion: ");
            scanf("%d", &opcion);
            if (!(opcion > 0 && opcion < 3))
            {
                system("clear");
                OpcionInvalidaM();
                getchar();
                getchar();
                system("clear");
            }
        } while (!(opcion > 0 && opcion < 3));
        system("clear");
        switch (opcion)
        {
        case 1:
            if (saldos[indiceUsuario] >= 0.35)
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
            }
            else
            {
                printf("\033[1;31mSaldo Insuficiente!\033[0m\nSu saldo es de %.2f$", saldos[indiceUsuario]);
                getchar();
                getchar();
                system("clear");
            }
            break;
        case 2:
            printf("\n\033[1;31mAccion cancelada por el Usuario!\033[0m\n");
            getchar();
            getchar();
            system("clear");
            break;
        }
    }
    else
    {
        system("clear");
        UsuarioNoEncontradoM();
        getchar();
        getchar();
        system("clear");
    }
}