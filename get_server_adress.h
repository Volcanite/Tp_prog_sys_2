//
// Created by matis on 18/12/24.
//

#ifndef GET_SERVER_ADRESS_H
#define GET_SERVER_ADRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define taille_port 6
#define Status_error 0
#define error (-1)
#define good 0

int get_server_address(const char *host, int port, struct sockaddr_in *addr);

#endif //GET_SERVER_ADRESS_H
