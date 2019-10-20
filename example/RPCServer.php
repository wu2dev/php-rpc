<?php
/**
 * @Author: minshengwu
 * @Date: 2019-10-19
 */

class Person{
    function test($args){
        return "Hi ".$args;
   }
}


$provider = new RPCProvider("127.0.0.1",9501,2);
$provider->run();