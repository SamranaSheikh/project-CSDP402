//Samrana Sheikh
//Simple Messaging System Submission
//The project is a simple client-server messaging system where the client sends a message to the server, 
// and the server echoes the message back to the client, demonstrating basic TCP socket communication.
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib") // Link Winsock library

using namespace std;

#define PORT 9999 // Port for the server to listen on

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Set up the server address
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on any network interface
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for a connection
    listen(serverSocket, 1);
    cout << "Server is running on port " << PORT << "...\n";

    // Accept a connection from a client
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    cout << "Client connected.\n";

    // Receive a message
    char buffer[1024] = {};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Received message: " << buffer << endl;

    // Echo the message back to the client
    send(clientSocket, buffer, sizeof(buffer), 0);

    // Clean up
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
