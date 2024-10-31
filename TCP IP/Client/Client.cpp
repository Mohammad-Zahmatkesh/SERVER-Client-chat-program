using namespace std;
#include <iostream>
#include <string> 
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main()
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };

    // راه‌اندازی Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup failed" << endl;
        return -1;
    }

    // ایجاد سوکت
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
    {
        cout << "Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // تبدیل آدرس IPv4 و IPv6 از متن به باینری
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        cout << "Invalid address / Address not supported" << endl;
        return -1;
    }

    // اتصال به سرور
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
    {
        cout << "Connection failed" << endl;
        return -1;
    }

    while (true)
    {
        cout << "You: ";
        string message;
        getline(cin, message);
        send(sock, message.c_str(), message.size(), 0);
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        cout << "Server: " << buffer << endl;
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}
