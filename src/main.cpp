#include "phpx.h"
#include <iostream>

using namespace php;
using namespace std;

PHPX_FUNCTION(php-rpc_hello)
{
    echo("argc=%d\n", args.count());
    retval = "hello world\n";
}

PHPX_EXTENSION()
{
    Extension *extension = new Extension("php-rpc", "0.0.1");

    extension->onStart = [extension]() noexcept {
        extension->registerConstant("PHP-RPC_VERSION", 10001);
    };

    //extension->onShutdown = [extension]() noexcept {
    //};

    //extension->onBeforeRequest = [extension]() noexcept {
    //    cout << extension->name << "beforeRequest" << endl;
    //};

    //extension->onAfterRequest = [extension]() noexcept {
    //    cout << extension->name << "afterRequest" << endl;
    //};

    extension->info({"php-rpc support", "enabled"},
                    {
                        {"version", extension->version},
                        {"date", "2019-10-19"},
                    });
    extension->registerFunction(PHPX_FN(php-rpc_hello));

    return extension;
}