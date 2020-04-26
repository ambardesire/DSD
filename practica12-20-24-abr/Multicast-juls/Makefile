Servidor: Servidor.o SocketMulticast.o PaqueteDatagrama.o
	g++ Servidor.o SocketMulticast.o PaqueteDatagrama.o -o Servidor
Client: Client.o SocketMulticast.o PaqueteDatagrama.o
	g++ Client.o SocketMulticast.o PaqueteDatagrama.o -o Client
Servidor.o: Servidor.cpp
	g++ Servidor.cpp -c -Wall
Client.o: Client.cpp
	g++ Client.cpp -c -Wall
SocketMulticast.o: SocketMulticast.cpp  SocketMulticast.h mensaje.h
	g++ SocketMulticast.cpp -c -Wall
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h 
	g++ PaqueteDatagrama.cpp -c -Wall
clear:
	rm *.o Servidor Client