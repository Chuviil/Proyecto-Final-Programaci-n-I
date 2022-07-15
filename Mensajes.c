#include "ProyectoLib.h"

void OpcionInvalidaM()
{
    printf("\n\033[1;31mOpcion Invalida\\n\033[0m");
    fflush(stdout);
}

void CedulaInvalidaM()
{
    printf("\n\033[1;31mCedula Invalida!\033[0m\n");
    fflush(stdout);
}

void UsuarioEncontrado()
{
    printf("\n\033[1;32mUsuario Encontrado!\033[0m\n")
        fflush(stdout);
}

void UsuarioNoEncontradoM()
{
    printf("\n\033[1;31mUsuario No Encontrado!\033[0m\n");
    fflush(stdout);
}

void NombreInvalidoM()
{
    printf("\n\033[1;31mNombre No Valido!\033[0m\n");
    fflush(stdout);
}