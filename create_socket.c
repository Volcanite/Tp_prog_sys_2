//
// Created by matis on 18/12/24.
//

#include "create_socket.h"
/**
 * Fonction pour réserver une socket UDP.
 *
 * @return  Le descripteur de fichier de la socket, ou -1 en cas d'erreur.
 */
int create_udp_socket() {
    int sockfd;

    // Création de la socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création de la socket UDP");
        return -1;
    }

    printf("Socket UDP créée avec succès. Descripteur : %d\n", sockfd);
    return sockfd;
}
