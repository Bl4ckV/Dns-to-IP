#include <winsock2.h>   //librería de sockets
#include <ws2tcpip.h>   //necesario para resolver el dns
#include <iostream>
#include <string>
#pragma comment (lib, "Ws2_32.lib")

using namespace std;

int main() {
    string dns;
    cout << "Introduce un dns: ";
    cin >> dns;
    WSADATA wsaData;     //declaramos e inicializamos las estructuras del socket
    DWORD dwRetval;
    struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;
    struct sockaddr_in* sockaddr_ipv4 = { 0 };
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;  //establecemos el tipo de socket
    hints.ai_protocol = IPPROTO_TCP;
    dwRetval = getaddrinfo(dns.c_str(), "0", &hints, &result); //con "getaddrinfo" traducimos un protocolo de nombre de host a una dirección
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
         sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
    }
    freeaddrinfo(result);
    WSACleanup();
    cout << "IP: " << inet_ntoa(sockaddr_ipv4->sin_addr);
    return 0;
}
