<?php
/**
 * @Author: minshengwu
 * @Date: 2019-10-19
 */

class PersonRemote{
    private $consumer;
    function __construct()
    {
        $this->consumer=new RPCConsumer("127.0.0.1",9501);

    }
   function test($args){
       return $this->consumer->run("Person","test",$args);
   }
}

$person = new PersonRemote();
var_dump($person->test("1111"));

