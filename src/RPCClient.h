/**
* @Author: minshengwu
* @Date: 2019-10-19
*/

#ifndef PHP_RPC_RPCCLIENT_H
#define PHP_RPC_RPCCLIENT_H

#include <arpa/inet.h>
#include <unistd.h>
#include <json/json.h>
#include <string>


using namespace Json;
using namespace std;

class RPCClient {
private:
    int server_fd;

public:
    RPCClient(const char *address, uint16_t port);

    string start(const string &className, const string &methodName, const string &args);

    virtual ~RPCClient();
};


#endif //PHP_RPC_RPCCLIENT_H
