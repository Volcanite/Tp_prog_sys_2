//
// Created by matis on 18/12/24.
//

#include "gettftp.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s host file\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *host = argv[1];
    const char *file = argv[2];
    struct sockaddr_in server_addr;

    printf("Résolution de l'adresse pour l'hôte : %s, fichier : %s\n", host, file);

    // Appel à get_server_address pour remplir la structure server_addr
    if (get_server_address(host, 1069, &server_addr) < 0) {
        fprintf(stderr, "Impossible de résoudre l'adresse du serveur.\n");
        return EXIT_FAILURE;
    }

    // Affichage de l'adresse IP résolue
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(server_addr.sin_addr), ip_str, INET_ADDRSTRLEN);
    printf("Adresse résolue : %s:%d\n", ip_str, ntohs(server_addr.sin_port));

    int sockfd = create_udp_socket();
    if (sockfd < 0) {
        return EXIT_FAILURE; // Erreur lors de la création de la socket
    }

    printf("Socket UDP prête pour communiquer avec le serveur.\n");

    char request[256];
    snprintf(request, sizeof(request), "GET %s\n", file);

    // Envoi de la requête au serveur
    if (sendto(sockfd, request, strlen(request), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur lors de l'envoi de la requête");
        close(sockfd);
        return EXIT_FAILURE;
    }
    printf("Requête envoyée au serveur : %s\n", request);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier local");
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("Réception des données...\n");
    while ((bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL)) > 0) {
        fwrite(buffer, 1, bytes_received, fp);
        // Arrêt si le serveur envoie moins que BUFFER_SIZE, ce qui peut indiquer la fin
        if (bytes_received < BUFFER_SIZE) {
            break;
        }
    }

    if (bytes_received < 0) {
        perror("Erreur lors de la réception des données");
    } else {
        printf("Fichier '%s' téléchargé avec succès.\n", file);
    }


    close(sockfd);
    return EXIT_SUCCESS;
}
