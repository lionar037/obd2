///////////////////////////////////////////////////////////////////////////////////////////////////
//
//              bluetooth_connection.hpp
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <iostream>
#include <stdexcept>  // Para std::runtime_error
#include <cstring>    // Para std::memset
#include <sys/socket.h>  // Para socket(), connect(), etc.
#include <bluetooth/bluetooth.h>  // Para sockaddr_rc y funciones Bluetooth
#include <unistd.h>  // Para read(), write(), close()


#include <vector>
#include <unistd.h>
#include <bluetooth/rfcomm.h>


namespace ELM327_BLUETOOTH {

class BluetoothConnection {
    
private:
    int sock;
    struct sockaddr_rc addr;  // Usamos sockaddr_rc directamente sin prefijo

public:
    BluetoothConnection(const std::string& address) {
        sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        if (sock < 0) {
            throw std::runtime_error("Error al crear socket Bluetooth");
        }

        // Configurar la dirección del dispositivo
        std::memset(&addr, 0, sizeof(addr));
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t) 1;  // Canal RFCOMM para ELM327
        str2ba(address.c_str(), &addr.rc_bdaddr);
    }

    void connectToDevice() {
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            throw std::runtime_error("Error al conectar al dispositivo Bluetooth");
        }
        std::cout << "Conectado al dispositivo ELM327." << std::endl;
    }

    void sendCommand(const std::string& command) {
        std::string fullCommand = command + "\r";  // El ELM327 requiere un \r al final
        ssize_t bytes_sent = write(sock, fullCommand.c_str(), fullCommand.size());
        if (bytes_sent < 0) {
            throw std::runtime_error("Error al enviar comando");
        }
        std::cout << "Comando enviado: " << command << std::endl;
    }

    std::string receiveResponse() {
        char buffer[1024] = {0};
        ssize_t bytes_read = read(sock, buffer, sizeof(buffer));
        if (bytes_read < 0) {
            throw std::runtime_error("Error al recibir respuesta");
        }
        return std::string(buffer, bytes_read);
    }

    ~BluetoothConnection() {
        close(sock);
        std::cout << "Conexión cerrada." << std::endl;
    }
};

}
