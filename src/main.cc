#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>

#define OBD2 "00:1D:A5:07:23:6E"


int main() {
    struct sockaddr_rc addr = { 0 };
    int sock, status;
    char dest[18] = OBD2 ;  // MAC del ELM327

    // Crear socket RFCOMM
    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Configurar la dirección
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(dest, &addr.rc_bdaddr);

    // Conectar al dispositivo
    status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    if (status == 0) {
        std::cout << "Conexión exitosa con ELM327." << std::endl;
        // Aquí puedes enviar comandos AT o interactuar con el ELM327
        char command[] = "ATZ\r";  // Comando para reiniciar el ELM327
        write(sock, command, sizeof(command));
    } else {
        std::cerr << "Error de conexión." << std::endl;
    }

    close(sock);
    return 0;
}

