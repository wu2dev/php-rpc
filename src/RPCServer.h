/**
* @Author: minshengwu
* @Date: 2019-10-19
*/

#ifndef PHP_RPC_RPCSERVER_H
#define PHP_RPC_RPCSERVER_H

#include <arpa/inet.h>
#include <json/json.h>
#include <string>
#include <phpx.h>


using namespace std;
using namespace Json;
using namespace php;

class RPCServer {
private:
    int server_fd, count;

public:
    RPCServer(const char *address, uint16_t port, int count = 10);

    void start();

    static string resolve(const string &className, const string &methodName, const string &args);

    virtual ~RPCServer();
};


#endif //PHP_RPC_RPCSERVER_H
