//Samrana Sheikh
//Simple Messaging System Submission
//The project is a simple client-server messaging system where the client sends a message to the server, 
// and the server echoes the message back to the client, demonstrating basic TCP socket communication.
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // Required for inet_pton
#include <string>     // Required for std::getline

#pragma comment(lib, "Ws2_32.lib") // Link Winsock library

using namespace std;

#define PORT 9999 // Port to connect to
#define SERVER_IP "127.0.0.1" // Localhost (server running on the same machine)

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed.\n";
        return 1;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Error creating socket.\n";
        WSACleanup();
        return 1;
    }

    // Set up the server address
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Error connecting to server.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to the server.\n";

    // Send a message to the server
    string message;
    cout << "Enter a message: ";
    std::getline(cin, message);
    send(clientSocket, message.c_str(), static_cast<int>(message.size()), 0);

    // Receive a response
    char buffer[1024] = {};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Null-terminate the string
        cout << "Server echoed: " << buffer << endl;
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
