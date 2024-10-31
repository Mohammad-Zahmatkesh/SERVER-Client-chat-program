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
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    // راه‌اندازی Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup failed" << endl;
        return -1;
    }

    // ایجاد سوکت
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Socket creation error" << endl;
        return -1;
    }

    // تنظیم آدرس و پورت
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // بایند کردن سوکت
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
    {
        cout << "Bind failed" << endl;
        return -1;
    }

    // گوش دادن به ورودی‌ها
    if (listen(server_fd, 3) == SOCKET_ERROR)
    {
        cout << "Listen failed" << endl;
        return -1;
    }

    cout << "Waiting for connections..." << endl;

    // قبول اتصال
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) == INVALID_SOCKET)
    {
        cout << "Accept failed" << endl;
        return -1;
    }

    cout << "Connection established!" << endl;

    while (true) 
    {
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, sizeof(buffer), 0);
        cout << "Client: " << buffer << endl;

        cout << "You: ";
        string message;
        getline(cin, message);
        send(new_socket, message.c_str(), message.size(), 0);
    }

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
