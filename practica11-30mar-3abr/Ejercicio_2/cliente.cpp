#include <stdio.h>
#include <stdlib.h>         // atoi
using namespace std;

#include "Solicitud.h"
#include "SocketDatagrama.h"

int main(int argc, char *argv[]) {
    Solicitud sol = Solicitud();

    char *ip = argv[1];
    int puerto = atoi(argv[2]);
    int n = atoi(argv[5]);

    char argumentos[4000] = "";
    strcat(argumentos, argv[3]);
    strcat(argumentos, " ");
    strcat(argumentos, argv[4]);

    for (int i=0 ; i<n ; i++) {
        sol.doOperation(ip, puerto, i+1, argumentos);
    }

    return 0;
}