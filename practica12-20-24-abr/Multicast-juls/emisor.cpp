#include <iostream>
#include "SocketMulticast.h"
#include "mensaje.h"
#include <cstring>

using namespace std;


static const char * GROUP = "127.0.0.1";


int main(int argc, char **argv) {
    SocketMulticast multicast(0); // Puerto para envio multicast

    int arr[2] = {2,7};

    PaqueteDatagrama paquete(arr, sizeof(arr), GROUP, 7272);

    multicast.envia(paquete, 7);
    
    cout << arr[0] << ", " << arr[1] << endl;

    auto vec = multicast.recibe();

    for (auto & p : vec) {
        int suma = *(int *)p.obtieneDatos();

        cout << p.obtieneDireccion() << ", suma : " << suma << endl;
    }

    return 0;
}
