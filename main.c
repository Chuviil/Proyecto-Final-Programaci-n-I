#include <stdio.h>
#include <stdlib.h>
#include "qrcodegen.h" //Libreria para generacion de codigos QR


// Prototipos de las funciones para codigos QR

static void genQrCode(const char *text);
static void printQr(const uint8_t qrcode[]);

// Fin de los prototipos de las funciones para codigos QR

int main(void) {
  int opcion;
  char mensaje[10];
  while(opcion != 2){
    printf("\t\tMenu Principal\n1)Generar Codigo QR\n2)Salir\n");
    printf("Escoja opcion: ");
    scanf("%d",&opcion);
    switch(opcion){
      case 1:
        system("clear");
        printf("Ingrese el mensaje a convertir en QR: ");
        getchar();
        fgets(mensaje, sizeof mensaje, stdin);
        strtok(mensaje, "\n");
        genQrCode(mensaje);
      break;
      case 2:
        system("clear");
        printf("\033[1;31m88888888888 88 888b      88  \n88          88 8888b     88  \n88          88 88 `8b    88  \n88aaaaa     88 88  `8b   88  \n88\"\"\"\"\"     88 88   `8b  88  \n88          88 88    `8b 88  \n88          88 88     `8888  \n88          88 88      `888\n\nFIN DEL PROGRAMA");
      break;
      default:
        printf("\033[1;31m");
        printf("\nOpcion Invalida intente de nuevo.\n\n");
        printf("\033[0m");
      break;
    }
  }
}

// Funciones de la generacion de codigos QR

static void genQrCode(const char *text){
  enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;
  uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
}

static void printQr(const uint8_t qrcode[]) {
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