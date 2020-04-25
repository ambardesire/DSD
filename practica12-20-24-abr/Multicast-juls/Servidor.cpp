#include <iostream>
#include <cstring>
#include "SocketMulticast.hpp"
#include "mensaje.h"

using namespace std;

static const char * group = "224.0.0.2";

static int nbd = 0;

int main() {
    SocketMulticast multicast(7272); // Puerto multicast a la escucha en 7272

    multicast.unirseGrupo(group);

    while (true) {
        auto vec = multicast.recibe();
        auto &paquete = vec[0];

        int *arr = (int *)paquete.obtieneDatos();

        //cout << arr[0] << ", " << arr[1] << endl;

        int suma = arr[0] + arr[1];

        PaqueteDatagrama resp(&suma, sizeof(suma), paquete.obtieneDireccion(), paquete.puerto);

        multicast.envia(resp, 0);

        std::cout << "respondido a " << paquete.obtieneDireccion() << ":" << paquete.puerto << std::endl;
    }
}