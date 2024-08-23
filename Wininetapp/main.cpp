#include <iostream>
#include <windows.h>
#include <wininet.h>

int main() {
    DWORD dwFlags;
    while (true) {
        bool isConnected = InternetGetConnectedState(&dwFlags, 0);
        if (isConnected) {

            std::cout << "Hay internet" << std::endl;
        }
        else {
            std::cout << "No hay internet"<<std::endl;
        }
        Sleep(1000);
    }
    return 0;
}