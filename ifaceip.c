#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void print_ip(const char *iface) {
    struct ifaddrs *ifaddr, *ifa;
    char ip[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    int found = 0;
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        if ((ifa->ifa_addr->sa_family == AF_INET) && strcmp(ifa->ifa_name, iface) == 0) {
            found = 1;
            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
            printf("%s", ip);
            break;
        }
    }

    freeifaddrs(ifaddr);

    if (!found) {
        fprintf(stderr, "Interface '%s' not found or has no IPv4 address.\n", iface);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <interface_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_ip(argv[1]);

    return EXIT_SUCCESS;
}
