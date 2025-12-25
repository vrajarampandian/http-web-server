#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    // printf("Hello world");
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket issue");
        return 1;
    }
    // printf("Socket fd = %d\n", server_fd);
    // close(server_fd);
    int optsize = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, optsize, sizeof(optsize));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4221);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind issue\n");
        return 1;
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("Listen error\n");
        return 1;
    }
    printf("Listening on Port 4221....\n");

    int client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0)
    {
        perror("Accept issue\n");
        return 1;
    }
    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Content-Length: 2\r\n"
                           "\r\n"
                           "OK";
    write(client_fd, response, strlen(response));
    close(client_fd);
    close(server_fd);
    return 0;
}