#include <phpx.h>
#include <iostream>
#include "RPCServer.h"
#include "RPCClient.h"

using namespace php;
using namespace std;

PHPX_METHOD(RPCProvider, __construct) {
    auto rpcServer = new RPCServer(args[0].toCString(), args[1].toInt(), args[2].toInt());
    _this.oSet("rpcServer", "RPCServer", rpcServer);
}

PHPX_METHOD(RPCProvider, run) {
    auto rpcServer = _this.oGet<RPCServer>("rpcServer", "RPCServer");
    rpcServer->start();
}

PHPX_METHOD(RPCConsumer, __construct) {
    auto rpcClient = new RPCClient(args[0].toCString(), args[1].toInt());
    _this.oSet("rpcClient", "RPCClient", rpcClient);
}

PHPX_METHOD(RPCConsumer, run) {
    auto rpcClient = _this.oGet<RPCClient>("rpcClient", "RPCClient");
    string ret = rpcClient->start(args[0].toString(), args[1].toString(), args[2].toString());
    retval=ret;
}

void rpc_server_dtor(zend_resource *res) {
    auto server = static_cast<RPCServer *>(res->ptr);
    delete server;
}

void rpc_client_dtor(zend_resource *res) {
    auto client = static_cast<RPCClient *>(res->ptr);
    delete client;
}

PHPX_EXTENSION() {
    auto *extension = new Extension("php-rpc", "0.0.4");
    extension->require("json");
    extension->onStart = [extension]() noexcept {
        auto rpcProvider = new Class("RPCProvider");
        rpcProvider->addProperty("rpcServer", nullptr);
        rpcProvider->addMethod(PHPX_ME(RPCProvider, __construct), CONSTRUCT);
        rpcProvider->addMethod(PHPX_ME(RPCProvider, run));
        extension->registerClass(rpcProvider);

        auto rpcConsumer = new Class("RPCConsumer");
        rpcProvider->addProperty("rpcClient", nullptr);
        rpcConsumer->addMethod(PHPX_ME(RPCConsumer, __construct), CONSTRUCT);
        rpcConsumer->addMethod(PHPX_ME(RPCConsumer, run));
        extension->registerClass(rpcConsumer);

        extension->registerResource("RPCServer", rpc_server_dtor);
        extension->registerResource("RPCClient", rpc_client_dtor);

        extension->info({"demo support", "enabled"},
                        {
                                {"version", extension->version},
                                {"date",    "2019-10-19"},
                        });
    };

    return extension;
}