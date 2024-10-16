///////////////////////////////////////////////////////////////////////////////////////////////////
//
//              elm327.hpp
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <bluetooth_connection.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>  // Para std::runtime_error
#include <bluetooth/bluetooth.h>  
#include <cstring>    // Para std::memset
#include <sys/socket.h>  // Para socket(), connect(), etc.
#include <unistd.h>  // Para read(), write(), close()
#include <bluetooth/rfcomm.h>



namespace ELM327_BLUETOOTH{

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

}