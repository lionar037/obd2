///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                          main.cpp
//
///////////////////////////////////////////////////////////////////////////////////////////////////


//#include <bluetooth_connection.hpp>
#include <elm327.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <sys/socket.h>

#define OBD2_MAC "00:1D:A5:07:23:6E"

int main() {
    try {
        // Dirección MAC del ELM327
        std::string elm327Address = OBD2_MAC ;  // Reemplaza con la MAC de tu dispositivo

        // Instancia del ELM327
        ELM327_BLUETOOTH::ELM327 elm327(elm327Address);

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
