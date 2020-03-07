//
// Created by Jesus on 13/06/2019.
//

#ifndef PRENIGMA_ENIG_H
#define PRENIGMA_ENIG_H


struct Rotor{
    int entrada[26];
    int salida[26];
};

typedef struct Rotor Rotor;


struct Maquina_Enigma{

    struct Rotor rotores [4]; //los 3 rotores y el reflector, que funciona igual que un rotor
    int posicionesinic[3];
};

typedef struct Maquina_Enigma ME;

void muestra_rotor(Rotor rot);


void creaRotor(Rotor *rot, int entrada[26], int salida[26]); //crea un rotor con las entradass y las salidas

void ConfigurarEnigma(ME *maquina);

void giraRotor(Rotor* rot, int inic);

void muestramakina(ME mak);

void procesarcadena(char* mensaje, ME* maquina);

char procesaChar(ME *me, char c); //método que dada una máquina enigma y un caracter, la pasa a traves de la maquina

void muestramenu();

void reseteaRotores(ME *enijma);

#endif //PRENIGMA_ENIG_H
