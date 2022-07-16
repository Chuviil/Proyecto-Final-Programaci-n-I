#include "ProyectoLib.h"

//Variables Globales

extern int cedulas[MAX_USUARIOS];
extern char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN];
extern float saldos[MAX_USUARIOS];
extern int cantUsuarios;
extern struct usuario usuarioGeneral;

bool consultarUsuario(int cedula)
{
    bool encontrado = false;
    obtenerUsuarios();
    for(int i = 0; i < cantUsuarios; i++)
    {
        if(cedula == cedulas[i]) encontrado = true;
    }
    return encontrado;
}

void FormatearNombrePUso(char nombre[])
{
  char temp1[MAX_NOMBRE_LEN];
  int h = strlen(nombre);
  for(int i=1;i<h;i++)
  {
    if(isupper(nombre[i])>0)
    {
      int k=0;
      int l = strlen(nombre);
      for(int j=i;j<=l;j++)
      {
        temp1[k] = nombre[j];
        k++;
      }
      nombre[i] = ' ';
      k = 0;
      int m = strlen(nombre)+1;
      for(int j=i+1;j<m;j++)
      {
        nombre[j] = temp1[k];
        k++;
      }
      i++;
    }
  }
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

void obtenerUsuarios()
{
  memset(nombres,0,MAX_USUARIOS);
  memset(cedulas,0,MAX_USUARIOS);
  memset(saldos,0,MAX_USUARIOS);
  FILE *puntero;
  int index = 0; 
  puntero = fopen("datos/usuarios.txt", "r");
  while(!feof(puntero))
  {
    fscanf(puntero, "%d %s %f", &cedulas[index], nombres[index], &saldos[index]);
    FormatearNombrePUso(nombres[index]);
    index++;
  }
  fclose(puntero);
  cantUsuarios = index - 1;
}

void FormatearNombrePIngreso(char nombre[])
{
  int i;
  char temp;
  for (i = 0; i < strlen(nombre); i++)
  {
    nombre[i] = tolower(nombre[i]);
  }
  nombre[0] = toupper(nombre[0]);
  for (i = 0; i < strlen(nombre); i++)
  {
    if (nombre[i] == ' ')
    {
      nombre[i + 1] = toupper(nombre[i + 1]);
    }
  }
  QuitarEspacios(nombre);
}

void QuitarEspacios(char nombre[])
{
  int i, j;
  char temp;
  for (i = 0; i < strlen(nombre); i++)
  {
    if (nombre[i] == ' ')
    {
      for (j = i; j <= strlen(nombre); j++)
      {
        temp = nombre[j + 1];
        nombre[j] = temp;
      }
    }
  }
}

void actualizarUsuarios(char nombres[MAX_USUARIOS][MAX_NOMBRE_LEN], int cedulas[], float saldos[])
{
  FILE *puntero;
  puntero = fopen("datos/usuarios.txt", "w");
  for (int i = 0; i < cantUsuarios; i++)
  {
    FormatearNombrePIngreso(nombres[i]);
    fprintf(puntero, "%d %s %.2f\n", cedulas[i], nombres[i], saldos[i]);
  }
  fclose(puntero);
}
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