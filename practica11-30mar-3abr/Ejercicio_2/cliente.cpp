#include <stdio.h>
#include <stdlib.h>         // atoi
using namespace std;

#include "Solicitud.h"
#include "SocketDatagrama.h"
#include <time.h>           // time
#include <string.h>         // bzero

int main(int argc, char *argv[]) {
    Solicitud sol = Solicitud();
    srand(time(NULL));

    char *ip = argv[1];
    int puerto = atoi(argv[2]);
    int n = atoi(argv[3]);
    char *pesos = new char[1];
    int ndb = 0;

    char argumentos[4000];

    for (int i=0 ; i<n ; i++) {
        bzero(argumentos, 4000);
        pesos[0] = (char)(rand()%9 + 49);
        strcat(argumentos, pesos);
        printf("%s\n", argumentos);
        sol.doOperation(ip, puerto, 1, argumentos);
    }

    return 0;
}