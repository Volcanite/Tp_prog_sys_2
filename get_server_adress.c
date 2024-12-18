//
// Created by matis on 18/12/24.
//

#include "get_server_adress.h"

/**
 * Résout l'adresse d'un serveur à partir de son nom d'hôte et du port.
 *
 * @param host      Nom d'hôte ou adresse IP du serveur.
 * @param port      Numéro de port du serveur.
 * @param addr      Pointeur vers une structure sockaddr_in à remplir.
 * @return          0 en cas de succès, -1 en cas d'échec.
 */


int get_server_address(const char *host, int port, struct sockaddr_in *addr) {
    struct addrinfo hints, *res;
    char port_str[taille_port]; // Pour convertir le port en chaîne (max 5 chiffres + '\0')

    // Initialisation de la structure hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // Utilisation de IPv4
    hints.ai_socktype = SOCK_DGRAM; // Protocole UDP

    // Conversion du port en chaîne
    snprintf(port_str, sizeof(port_str), "%d", port);

    // Résolution de l'adresse
    int status = getaddrinfo(host, port_str, &hints, &res);
    if (status != Status_error) {
        fprintf(stderr, "Erreur dans getaddrinfo: %s\n", gai_strerror(status));
        return error;
    }

    // Copie de l'adresse dans sockaddr_in
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    memcpy(addr, ipv4, sizeof(struct sockaddr_in));

    freeaddrinfo(res); // Libération de la mémoire allouée par getaddrinfo
    return good;
}
