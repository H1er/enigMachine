#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Enig.h"


int main(void)
{
	ME enijma;
	int logout = 0;
	int configurada = 0;
	int opcion=-1;
	char *cadena = malloc(sizeof(char)*100);

	while(!logout)
	{
		muestramenu();

		printf("\nIntroduzca la opcion que desee realizar: ");
		fflush(stdout);
		scanf("%d", &opcion);
		fflush(stdin);


		switch(opcion)
		{
			case 1:
			{
				ConfigurarEnigma(&enijma);
				printf("\nConfiguracion guardada\n\n\n");
				configurada=1;
				break;
			};

			case 2:
			{
				int ok = 1;
				int cont=0;

				if (configurada) //solo se puede cifrar cuando haya una maquina previamente configurada
				{
					while(ok==1)
					{
						fflush(stdout);
						printf("Introduzca la cadena a cifrar(introduzca solo letras en mayusculas): ");
						scanf("%s",cadena);

						while(cadena[cont] != '\0' && ok !=0)
						{

							if('A'<= cadena[cont] && cadena[cont] <= 'Z')
							{
								ok=0;
							}
							cont++;
						}

						cont=0;
					}

					procesarcadena(cadena, &enijma);
					printf("\nCadena cifrada: %s\n\n\n", cadena);
				}
				else
				{
					printf("\nConfigure primero una maquina enigma antes de cifrar un mensaje...\n\n\n");
				}
				break;
			};

			case 3:
			{
				int ok = 1;
				int cont =0;

				if (configurada) //solo se puede descifrar cuando haya una maquina previamente configurada
				{
					while(ok==1)
					{
						printf("Introduzca la cadena a descifrar (introduzca solo letras en mayusculas): ");
						scanf("%s",cadena);

						while(cadena[cont] != '\0' && ok !=0)
						{

							if('A'<= cadena[cont] && cadena[cont] <= 'Z')
							{
								ok=0;
							}
							cont++;
						}

						cont=0;
					}

					procesarcadena(cadena, &enijma);
					printf("\nCadena descifrada: %s\n\n\n", cadena);
				}
				else
				{
					printf("\nConfigure primero una maquina enigma antes de descifrar un mensaje...\n\n\n");
				}
				break;
			};

			case 4:
			{
				int ok = 1;
				int cont=0;

				if (configurada) //solo se puede cifrar cuando haya una maquina previamente configurada
				{
					reseteaRotores(&enijma);
					printf("\nRotores reseteados! \n\n\n");
				}
				else
				{
					printf("\nConfigure primero una maquina enigma antes de resetear los rotores...\n\n\n");
				}
				break;
			};

			case 5:
			{
				printf("\nHasta luego!\n");
				logout=1;
				break;
			};

			default:
			{
				printf("\nIntroduzca una opcion valida...\n\n\n");
				break;
			};
		}
	}

    return 0;
}
