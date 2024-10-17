///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                          main.cpp
//
///////////////////////////////////////////////////////////////////////////////////////////////////


//#include <bluetooth_connection.hpp>
#include <oled.hpp>
#include <elm327.hpp>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <sys/socket.h>

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <unistd.h>

#define OBD2_MAC "00:1D:A5:07:23:6E"

int main() {
    try {
        // Dirección MAC del ELM327
        std::string elm327Address = OBD2_MAC ;  // Reemplaza con la MAC de tu dispositivo




    std::unique_ptr<OLED::Oled_t> oled = std::make_unique<OLED::Oled_t>(128, 32, BCM2835_I2C_CLOCK_DIVIDER_626, 0x3C);

    if (!oled->begin()) {
        return -1;
    }

    oled->clearScreen();
    oled->displayText(OBD2_MAC, 10, 10);
    bcm2835_delay(5000);


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
