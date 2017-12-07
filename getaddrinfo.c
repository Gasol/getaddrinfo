#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define HOST_SIZE 255

int main(int argc, char** argv)
{
    char ipstr[HOST_SIZE];
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int ret = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *domain_name = argv[1];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    ret = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *) rp->ai_addr;
        void *addr = &(ipv4->sin_addr);
        inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr);
        printf("%s\n", ipstr);
    }
    freeaddrinfo(result);

    return EXIT_SUCCESS;
}
