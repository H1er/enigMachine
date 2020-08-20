//
// Created by Jesus on 13/06/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Enig.h"

int inp[26]  =   {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
int otpA[26] =   {5,11,13,6,12,7,4,17,22,26,14,20,15,23,25,8,24,21,19,16,1,9,2,18,3,10};
int otpB[26] =   {1,10,4,11,19,9,18,21,24,2,12,8,23,20,13,3,17,7,26,14,16,25,6,22,15,5};
int otpC[26] =   {2,4,6,8,10,12,3,16,18,20,24,22,26,14,25,5,9,23,7,1,11,13,21,19,17,15};
int otpD[26] =   {5,19,15,22,16,26,10,1,25,17,21,9,18,8,24,12,14,6,20,7,11,4,3,13,23,2};
int otpE[26] =   {22,26,2,18,7,9,20,25,21,16,19,4,14,8,12,24,1,23,13,10,17,15,6,5,3,11};
int otpRef[26] = {6,22,16,10,9,1,15,25,5,4,18,26,24,23,7,3,20,11,21,17,19,2,14,13,8,12};

Rotor rotA;
Rotor rotB;
Rotor rotC;
Rotor rotD;
Rotor rotE;
Rotor reflector;


void creaRotor(Rotor *rot, int entrada[26], int salida[26])
{
    for (int i=0;i<26;++i)
    {
        rot->salida[i] = salida[i];
        rot->entrada[i] = entrada[i];
    }
}

void muestra_rotor(Rotor rot)
{
    printf("Entrada: ");
    for(int i=0;i<26;i++)
    {
        printf("%c, ", rot.entrada[i]+'A'-1);
    }
    printf("\n");

    printf("Rels:    ");
    for(int i=0;i<26;i++)
    {
        printf("%c, ", rot.salida[i]+'A'-1);
    }

    printf("\n");

    printf("Salidas: ");
    for(int i=0;i<26;i++)
    {
        printf("%c, ", rot.entrada[i]+'A'-1);
    }
    printf("\n\n\n");
}

void ConfigurarEnigma(ME *maquina)
{
    //INTRODUCIR ROTORES
    char *rotores = malloc(sizeof(char)*4);
    int pinicial[3];
    int verdad=0;
    int n=0;
    //rotores[3]='\0';


    while (verdad == 0) //Mientras no se introduzca una entrada valida
    {
        printf("Introduce tres rotores validos(A,B,C,D,E) en forma de cadena (por ejemplo EDC)\n");
        fflush(stdout);

        
        scanf("%s", rotores);
        fflush(stdin);

        if (rotores[0] != rotores[1] && rotores[1] != rotores[2] && rotores[0] != rotores[2] && rotores[3] == '\0') //No se puede seleccionar el mismo rotor
        {
            int cont = 0;

            for (int i = 0; i < 3; i++)
            {
                if (rotores[i] >= 'A' && rotores[i] <= 'E')
                {
                    cont++;

                    if (cont == 3)
                        verdad = 1;
                }
            }
        }

        
    }


    for (int j = 0; j < 3; j++)
    {
        if (rotores[j]=='A')
        {
            creaRotor(&rotA, inp, otpA);
            maquina->rotores[j] = rotA;
        }
        else  if (rotores[j]=='B')
        {
            creaRotor(&rotB, inp, otpB);
            maquina->rotores[j] = rotB;
        }
        else  if (rotores[j]=='C')
        {
            creaRotor(&rotC, inp, otpC);
            maquina->rotores[j] = rotC;
        }
        else  if (rotores[j]=='D')
        {
            creaRotor(&rotD, inp, otpD);
            maquina->rotores[j] = rotD;
        }
        else
        {
            creaRotor(&rotE, inp, otpE);
            maquina->rotores[j] = rotE;
        }
    }

    creaRotor(&reflector, inp,otpRef);
    maquina->rotores[3] = reflector;//-----------------------------maquina con todos los rotores puestos

    //POSICION INICIAL DE LOS ROTORES
    int c = 0;
    verdad = 0;

    while (verdad == 0)
    {
        fflush(stdin);
        printf("Introduce la posicion inicial del rotor %c \n", rotores[c]);
        fflush(stdout);

        scanf("%d", &pinicial[c]);


        if (pinicial[c] >= 1 && pinicial[c] <= 26)
        {
            c++;
            if (c == 3)
                verdad = 1;
        }
    }

    for (int k = 0; k < 3; k++)
    {
        maquina->posicionesinic[k] = pinicial[k];
        giraRotor(&maquina->rotores[k], pinicial[k]);
    }
}

void giraRotor(Rotor* rot, int inic) //desplaza a la izquierda 'inic' veces los arrays del rotor
{
   // muestra_rotor(*rot);
    for (int i = 0; i < inic-1; i++)//---Se hace inic veces desplazamiento a la izquierda
    {
        int entinic=rot->entrada[0];
        int salinic=rot->salida[0];

        for (int j = 0; j < 26; j++)
        {
            if (j==25)
            {
                rot->entrada[j]=entinic;
                rot->salida[j]=salinic;
            }
            else
            {
                rot->entrada[j]=rot->entrada[j+1];
                rot->salida[j]=rot->salida[j+1];
            }
        }
    }
}

void muestramakina(ME mak)
{
    printf("-----Maquina Enigma-----");
    printf("\n\n\t-----Rotores-----\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Rotor %d: \n",i+1);
        muestra_rotor(mak.rotores[i]);
    }
    printf("\n\n\t-----Reflector-----\n");
    muestra_rotor(mak.rotores[3]);


}

char procesaChar(ME *me, char c)
{
    int desp = (c-'A');//Obtener el desplazamiento de la entrada del rotor1
    int valor = 0;
    //printf("%c -> ", c);
    for(int i=0;i<4;i++)    //primera mitad de la traduccion (desde el primer rotor hasta el reflector)
    {
        valor=me->rotores[i].salida[desp];
        desp=0;

        while(valor!=me->rotores[i].entrada[desp])//buscamos la posicion del valor de salida
        {
            desp++;
        }

        //printf("%c ->", (valor+'A'-1));
    }

    for (int j=2;j>=0;j--) //segunda mitad de la traduccion (desde la salida del receptor al inicio)
    {
        valor=me->rotores[j].entrada[desp];
        desp=0;

        while(valor!=me->rotores[j].salida[desp])//buscamos la posicion del valor de salida
        {
            desp++;
        }
        //printf("%c->", (valor+'A'-1));
    }
    c = (char) ('A' + desp);
    //printf("%c\n",c);
    return c;
}





void ObtenerMensaje(char *cifrado)
{
    //MENSAJES: A CIFRAR
    int verdad = 0;
    char* msg = malloc(sizeof(char)*100);
    printf("Introduzca la cadena a cifrar (en mayusculas)\n");
    fflush(stdout);
    scanf("%s", msg);

    int cont = 0;
    while (msg[cont] != '\0')
    {
        cont++;
    }

    char * mensaje = malloc(sizeof(char)*(cont+1));

    for (int i = 0; i <= cont; i++)
    {
        mensaje[i] = msg[i];
    }



    while (verdad == 0)
    {
        int contador = 0;

        for (int i = 0; i < (sizeof(mensaje)); i++)
        {
            if (((mensaje[i] >= 'A' && mensaje[i] <= 'Z') || mensaje[i] == '\0' || mensaje[i]==' '))
            {
                contador++;
                if (contador == sizeof(mensaje))
                {
                    verdad = 1;
                }
            }
        }

        if (verdad == 0)
        {
            printf("Introduce una cadena correcta\n");
            fflush(stdout);
            scanf("%s", mensaje);
        }
    }

    strcpy(cifrado, mensaje);

    free(mensaje);
    free(msg);

}

void reseteaRotores(ME* enijma)
{
    for (int i = 0; i <3 ; i++)     //se recorren los 3 rotores
    {
        while(enijma->rotores[i].entrada[0]!=enijma->posicionesinic[i]) //cada rotor se va desplazando hacia la izquierda hasta que en la primera posicion del rotor esta el valor inicial introducido
        {
            giraRotor(&enijma->rotores[i], 2);
        }
    }
}

void procesarcadena(char* mensaje, ME* maquina)
{
    int contadorgiros = 0; //cuenta las letras
    int contadorrotores = 0; //indica el rotor que se gira

    for (int i=0;mensaje[i]!='\0';i++)
    {
        if (mensaje[i] !=' ') //si es un espacio no se procesa, aunque
        {
            giraRotor(&maquina->rotores[contadorrotores], 2);

            mensaje[i] = procesaChar(maquina, mensaje[i]);

            contadorgiros++;


            if (contadorgiros==26)
            {
                contadorrotores++;
                contadorgiros=0;

                if (contadorrotores==3)
                {
                    contadorrotores = 0;
                }
            }
        }
    }
}

void muestramenu()
{
    printf("\n\t------MENU------\n");
    printf("1- Configurar Maquina Enigma\n");
    printf("2- Cifrar mensaje\n");
    printf("3- Descifrar mensaje\n");
    printf("4- Restablecer posicion inicial\n");
    printf("5- Salir\n\n");
}


