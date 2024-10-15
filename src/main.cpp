#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <sys/socket.h>

#define PAIR "00:1D:A5:07:23:6E"

class BluetoothConnection {
private:
    int sock;
    struct sockaddr_rc addr;

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

class ELM327 {
private:
    BluetoothConnection btConnection;

public:
    ELM327(const std::string& btAddress) : btConnection(btAddress) {
        btConnection.connectToDevice();
    }

    std::string sendATCommand(const std::string& command) {
        btConnection.sendCommand(command);
        std::string response = btConnection.receiveResponse();
        return response;
    }

    void executeCommands(const std::vector<std::string>& commands) {
        for (const auto& cmd : commands) {
            try {
                std::string response = sendATCommand(cmd);
                std::cout << "Respuesta para comando [" << cmd << "]: " << response << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "Error al ejecutar el comando [" << cmd << "]: " << e.what() << std::endl;
            }
        }
    }
};

int main() {
    try {
        // Dirección MAC del ELM327
        std::string elm327Address = PAIR ;  // Reemplaza con la MAC de tu dispositivo

        // Instancia del ELM327
        ELM327 elm327(elm327Address);

        // Lista de comandos AT a enviar
        std::vector<std::string> commands = {
            "ATZ",      // Reiniciar el ELM327
            "ATL1",     // Activar líneas largas
            "ATE0",     // Desactivar eco
            "ATSP0",    // Protocolo automático
            "0100"      // Consultar PIDs soportados
        };

        // Ejecutar los comandos
        elm327.executeCommands(commands);

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
