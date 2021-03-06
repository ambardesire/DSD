#include <stdio.h>
#include <stdlib.h>         // atoi
using namespace std;

#include "Solicitud.h"
#include "SocketMulticast.h"
#include <time.h>           // time
#include <string.h>         // bzero

int main(int argc, char *argv[]) {
    Solicitud sol = Solicitud();
    srand(time(NULL));
    char* argumentos = new char[4000];

    char *ip = argv[1];
    int puerto = atoi(argv[2]);
    bzero(argumentos, 4000);
    memcpy(argumentos, argv[3], sizeof(argv[3]));

    sol.doOperation(ip, puerto, 0, 1, argumentos);

    return 0;
}