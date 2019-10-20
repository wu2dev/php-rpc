/**
* @Author: minshengwu
* @Date: 2019-10-19
*/

#include "RPCClient.h"

RPCClient::RPCClient(const char *address, uint16_t port) {
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);
    bzero(&(server_addr.sin_zero), 8);
    if (connect(this->server_fd, (sockaddr *) &server_addr, sizeof(sockaddr)) == -1) {
        perror("Connect Server Failed...\n");
        exit(EXIT_FAILURE);
    }
    printf("Connected Server.... \n");
}

string RPCClient::start(const string &className, const string &methodName, const string &args) {
    char buf[1024];
    StreamWriterBuilder builder;
    Value root, data;

    builder["commentStyle"] = "None";
    builder["indentation"] = "";
    root["className"] = className.c_str();
    root["methodName"] = methodName.c_str();
    root["args"] = args.c_str();
    const string msg = writeString(builder, root);
    if (send(this->server_fd, msg.c_str(), msg.length(), 0) == -1) {
        perror("Sent Message Failed...\n");
        exit(EXIT_FAILURE);
    }
    memset(buf, 0, sizeof(buf) / sizeof(char));
    if (recv(this->server_fd, buf, sizeof(buf), 0) == -1) {
        perror("Recv Message Failed...\n");
        exit(EXIT_FAILURE);
    }
    return buf;
}

RPCClient::~RPCClient() {
    close(this->server_fd);
    printf("DisConnect Server.... \n");
}