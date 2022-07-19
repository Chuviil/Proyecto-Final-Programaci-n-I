#include "ProyectoLib.h"

// Variables Globales

extern int cedulas[MAX_USUARIOS];
extern char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN];
extern float saldos[MAX_USUARIOS];
extern int cantUsuarios;
extern struct usuario usuarioGeneral;

void registrarUsuario()
{
    int opcion, cedula;
    char nombre[MAX_NOMBRE_LEN];
    float saldo = 0;
    FILE *puntero;
    system("clear");
    getchar();
    printf("===========================\n\tRegistro de Usuario\n===========================\n\n");
    do
    {
        printf("Ingrese el nombre: ");
        fgets(nombre, MAX_NOMBRE_LEN, stdin);
        if (!(strlen(nombre) > 1))
        {
            NombreInvalidoM();
        }
    } while (!(strlen(nombre) > 1));
    nombre[strcspn(nombre, "\n")] = 0;
    do
    {
        printf("Ingrese la cedula: ");
        scanf("%d", &cedula);
        if (cedula <= 0)
        {
            CedulaInvalidaM();
        }
    } while (!(cedula > 0));
    system("clear");
    printf("===========================\n\tRegistro de Usuario\n===========================\n\n");
    printf("Nombre: %s\nCedula: %d\n", nombre, cedula);
    do
    {
        printf("Desea registrar este usuario?\n1)Si\t2)No\nEliga una opcion: ");
        scanf("%d", &opcion);
        if (!(opcion > 0 && opcion < 3))
        {
            OpcionInvalidaM();
        }
    } while (!(opcion > 0 && opcion < 3));
    switch (opcion)
    {
    case 1:
        system("clear");
        FormatearNombrePIngreso(nombre);
        puntero = fopen("datos/usuarios.txt", "a");
        fprintf(puntero, "%d %s %.2f\n", cedula, nombre, saldo);
        fclose(puntero);
        printf("\033[0;32mUsuario Registrado!\033[0m");
        fflush(stdout);
        getchar();
        getchar();
        break;
    case 2:
        system("clear");
        printf("\033[1;31mCancelado por el Usuario\033[0m");
        fflush(stdout);
        getchar();
        getchar();
        break;
    }
    system("clear");
}

void EliminarUsuario()
{
    char nuevosNombres[MAX_USUARIOS][MAX_NOMBRE_LEN];
    int indice, opcion, nuevasCedulas[MAX_USUARIOS];
    float nuevosSaldos[MAX_USUARIOS];

    system("clear");
    do
    {
        printf("Ingrese el numero de cedula del usuario a eliminar: ");
        scanf("%d", &usuarioGeneral.cedula);
        if (!(usuarioGeneral.cedula > 0))
        {
            CedulaInvalidaM();
        }
    } while (!(usuarioGeneral.cedula > 0));

    if (consultarUsuario(usuarioGeneral.cedula))
    {
        obtenerUsuarios();
        indice = obtenerIndice(usuarioGeneral.cedula);
        system("clear");
        printf("Se va a eliminar al usuario: \nNombre: %s\nCedula: %d\n Saldo: %.2f$\nDesea continuar?\n1)Si\t2)No", nombres[indice], cedulas[indice], saldos[indice]);
        do
        {
            printf("\nElija opcion: ");
            scanf("%d", &opcion);
            if (!(opcion > 0 && opcion < 3))
            {
                OpcionInvalidaM();
            }
        } while (!(opcion > 0 && opcion < 3));
        switch (opcion)
        {
        case 1:
            for (int i = 0; i < indice; i++)
            {
                strcpy(nuevosNombres[i], nombres[i]);
                nuevasCedulas[i] = cedulas[i];
                nuevosSaldos[i] = saldos[i];
            }
            for (int j = indice + 1; j < cantUsuarios; j++)
            {
                strcpy(nuevosNombres[j - 1], nombres[j]);
                nuevasCedulas[j - 1] = cedulas[j];
                nuevosSaldos[j - 1] = saldos[j];
            }
            /*for(int k = 0;k < cantUsuarios-1; k++)
            {
              printf("Nombre #%d: %s\nCedula: %d\nSaldo: %.2f\n\n",k, nuevosNombres[k],nuevasCedulas[k],nuevosSaldos[k]);
            }*/
            cantUsuarios--;
            actualizarUsuarios(nuevosNombres, nuevasCedulas, nuevosSaldos);
            system("clear");
            printf("\n\033[1;32mUsuario Eliminado!\033[0m\n");
            break;
        case 2:
            system("clear");
            printf("\033[1;31mCancelado por el Usuario\033[0m");
            fflush(stdout);
            getchar();
            getchar();
            system("clear");
            break;
            break;
        default:
            break;
        }
    }
    else
    {
        UsuarioNoEncontradoM();
        getchar();
        getchar();
    }
}

void modificarUsuario()
{
    struct usuario UsuarioTemp;
    int indice, opcion, modOpcion;

    system("clear");
    do
    {
        printf("Ingrese el numero de cedula del usuario a modificar: ");
        scanf("%d", &usuarioGeneral.cedula);
        if (!(usuarioGeneral.cedula > 0))
        {
            CedulaInvalidaM();
        }
    } while (!(usuarioGeneral.cedula > 0));

    system("clear");
    if (consultarUsuario(usuarioGeneral.cedula))
    {
        obtenerUsuarios();
        indice = obtenerIndice(usuarioGeneral.cedula);
        do
        {
            system("clear");
            printf("============================\n\tMODIFICACION USUARIO\n============================\n\nNombre: %s\nCedula: %d\nSaldo: %.2f$\n\nQue desea modificar?\n1)Nombre\n2)Cedula\n3)Saldo\n4)Salir", nombres[indice], cedulas[indice], saldos[indice]);
            do
            {
                printf("\nElija una opcion: ");
                scanf("%d", &opcion);
                if (!(opcion > 0 && opcion < 5))
                {
                    OpcionInvalidaM();
                }
            } while (!(opcion > 0 && opcion < 5));
            switch (opcion)
            {
            case 1:
                system("clear");
                printf("==========================\n\tModificando Nombre\n==========================\n");
                getchar();
                do
                {
                    printf("\nIngrese el nuevo nombre: ");
                    fgets(UsuarioTemp.nombre, MAX_NOMBRE_LEN, stdin);
                    if (!(strlen(UsuarioTemp.nombre) > 1))
                    {
                        NombreInvalidoM();
                    }
                } while (!(strlen(UsuarioTemp.nombre) > 1));
                UsuarioTemp.nombre[strcspn(UsuarioTemp.nombre, "\n")] = 0;
                system("clear");
                do
                {
                    printf("==========================\n\tModificando Nombre\n==========================\n\nAnterior Nombre: %s\nNuevo Nombre: %s\n\nDesea realizar el cambio?\n1)Si\t2)No", nombres[indice], UsuarioTemp.nombre);
                    do
                    {
                        printf("\nElija una opcion: ");
                        scanf("%d", &modOpcion);
                        if (!(modOpcion > 0 && modOpcion < 3))
                        {
                            OpcionInvalidaM();
                        }
                    } while (!(modOpcion > 0 && modOpcion < 3));
                    switch (modOpcion)
                    {
                    case 1:
                        FormatearNombrePIngreso(UsuarioTemp.nombre);
                        FormatearNombrePUso(UsuarioTemp.nombre);
                        strcpy(nombres[indice], UsuarioTemp.nombre);
                        actualizarUsuarios(nombres, cedulas, saldos);
                        FormatearNombrePUso(nombres[indice]);
                        break;
                    case 2:
                        break;
                    default:
                        system("clear");
                        OpcionInvalidaM();
                        break;
                    }
                } while (!(modOpcion > 0 && modOpcion < 3));
                break;
            case 2:
                system("clear");
                printf("==========================\n\tModificando Cedula\n==========================\n");
                do
                {
                    printf("\nIngrese la nueva cedula: ");
                    scanf("%d", &UsuarioTemp.cedula);
                    if (!(UsuarioTemp.cedula > 0))
                    {
                        CedulaInvalidaM();
                    }

                } while (!(UsuarioTemp.cedula > 0));
                system("clear");
                do
                {
                    printf("==========================\n\tModificando Cedula\n==========================\n\nAnterior Cedula: %d\nNueva Cedula: %d\n\nDesea realizar el cambio?\n1)Si\t2)No", cedulas[indice], UsuarioTemp.cedula);
                    do
                    {
                        printf("\nElija una opcion: ");
                        scanf("%d", &modOpcion);
                        if (!(modOpcion > 0 && modOpcion < 3))
                        {
                            OpcionInvalidaM();
                        }

                    } while (!(modOpcion > 0 && modOpcion < 3));
                    switch (modOpcion)
                    {
                    case 1:
                        cedulas[indice] = UsuarioTemp.cedula;
                        actualizarUsuarios(nombres, cedulas, saldos);
                        break;
                    case 2:
                        break;
                    default:
                        system("clear");
                        OpcionInvalidaM();
                        break;
                    }
                } while (!(modOpcion > 0 && modOpcion < 3));
                break;
            case 3:
                system("clear");
                printf("==========================\n\tModificando Saldo\n==========================\n");
                do
                {
                    printf("\nIngrese el nuevo saldo: ");
                    scanf("%f", &UsuarioTemp.saldo);
                } while (!(UsuarioTemp.saldo > 0));

                system("clear");
                do
                {
                    printf("==========================\n\tModificando Saldo\n==========================\n\nAnterior Saldo: %.2f$\nNuevo Saldo: %.2f$\n\nDesea realizar el cambio?\n1)Si\t2)No", saldos[indice], UsuarioTemp.saldo);
                    do
                    {
                        printf("\nElija una opcion: ");
                        scanf("%d", &modOpcion);
                    } while (!(modOpcion > 0 && modOpcion < 3));
                    switch (modOpcion)
                    {
                    case 1:
                        saldos[indice] = UsuarioTemp.saldo;
                        actualizarUsuarios(nombres, cedulas, saldos);
                        break;
                    case 2:
                        break;
                    default:
                        system("clear");
                        OpcionInvalidaM();
                        break;
                    }
                } while (!(modOpcion > 0 && modOpcion < 3));
                break;
            case 4:
                sleep(1);
                system("clear");
                break;
            default:
                OpcionInvalidaM();
                break;
            }
        } while (opcion != 4);
    }
    else
    {
        UsuarioNoEncontradoM();
        getchar();
        getchar();
        system("clear");
    }
}

void UsuarioConsultar()
{
    int indice;
    system("clear");
    printf("Ingrese la cedula del usuario a consultar: ");
    scanf("%d", &usuarioGeneral.cedula);
    if (consultarUsuario(usuarioGeneral.cedula))
    {
        UsuarioEncontradoM();
        obtenerUsuarios();
        obtenerIndice(usuarioGeneral.cedula);
        printf("\nNombre: %s\nCedula: %d\nSaldo: %.2f$", nombres[indice], cedulas[indice], saldos[indice]);
    }
    else
    {
        UsuarioNoEncontradoM();
    }
    getchar();
    getchar();
    system("clear");
    usuarioGeneral.cedula = 0;
}