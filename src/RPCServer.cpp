/**
* @Author: minshengwu
* @Date: 2019-10-19
*/

#include "RPCServer.h"

RPCServer::RPCServer(const char *address, uint16_t port, int count) {
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);
    bzero(&(server_addr.sin_zero), 8);
    int on =1;
    socklen_t size=sizeof(int);
    if(setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &on, size)==-1){
        perror("Server Set Socket Option Failed...\n");
        exit(EXIT_FAILURE);
    }
    if (bind(this->server_fd, (sockaddr *) &server_addr, sizeof(sockaddr)) == -1) {
        perror("Server Bind Failed...\n");
        exit(EXIT_FAILURE);
    }
    if (listen(this->server_fd, 128) == -1) {
        perror("Server Listen Failed...\n");
        exit(EXIT_FAILURE);
    }
    this->count = count;
    printf("Server Start ...\n");
}

void RPCServer::start() {
    char buf[1024];
    sockaddr_in client_addr{};
    unsigned int sin_size = sizeof(sockaddr_in);

    for (int i = 0; i < this->count; i++) {
        memset(buf, 0, sizeof(buf) / sizeof(char));
        int client_fd = accept(this->server_fd, (sockaddr *) &client_addr, &sin_size);
        if (recv(client_fd, &buf, sizeof(buf), 0) == -1) {
            perror("Server Recv Failed...\n");
            exit(EXIT_FAILURE);
        }
        printf("Client: %s\n", buf);
        CharReaderBuilder builder;
        Value root;
        string err;
        const unique_ptr<CharReader> reader(builder.newCharReader());
        if (!reader->parse(buf, buf + sizeof(buf), &root, &err)) {
            printf("Error: %s\n", err.c_str());
            exit(EXIT_FAILURE);
        }
        const string className = root["className"].asString();
        const string methodName = root["methodName"].asString();
        const string args = root["args"].asString();
        const string ret = resolve(className, methodName, args);
        if (send(client_fd, ret.c_str(), 50, 0) == -1) {
            perror("Server Send Message Failed...\n");
            exit(EXIT_FAILURE);
        }
        close(client_fd);
    }
}

string RPCServer::resolve(const string &className, const string &methodName, const string &args) {
    Object person = newObject(className.c_str());
    Variant ret = person.exec(methodName.c_str(), args.c_str());
    return ret.toString();
}

RPCServer::~RPCServer() {
    close(this->server_fd);
    printf("Server stop...\n");
}

