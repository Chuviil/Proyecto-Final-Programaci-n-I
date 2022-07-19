#MAKEFILE DEL PROYECTO

CC = clang
CFLAGS = -Wall
OBJ = proyectoC

all:
	$(CC) $(CFLAGS) main.c AdministradorFunciones.c generalFunciones.c Mensajes.c qrcodegen.c UsuarioFunciones.c -o $(OBJ)
exec:
	clear
	mkdir -p datos
	touch ./datos/usuarios.txt
	./proyectoC
clean:
	rm -rf *.o