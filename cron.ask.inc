<?php
/*
 * CRON FOUNDATION <http://cronfoundation.org> 
 * CRON JSON-RPC low level interface
 */
 

/**
 * @description Make JSON-RPC call to URL_CRON_RPC_NODE
 * @param type $method JSON-RPC method name
 * @param type $params optional array of parameters
 * @param type $rpcId optional JSON-RPC query id for tracking answers
 * @return result or error sub-objects
 */
function CronAsk( $method, $params = array(), $rpcId = 0 )
{    
 $arr = array(
     "jsonrpc" => "2.0",
     "id"      => $rpcId,
     "method"  => $method,
     "params"  => $params );
 $res = HTTPPost(URL_CRON_RPC_NODE, $arr);
 $obj = json_decode($res);
 if(!isset($obj))
   { return NULL; }
 if(isset($obj->error))
   { return $obj->error; }
 return $obj->result;
}

/**
     * @description Make HTTP-POST call
     * @param       $url
     * @param       array $params
     * @return      HTTP-Response body or an empty string if the request fails
     *              or is empty
*/
function HTTPPost($url, array $params)
{
    $query = json_encode($params, JSON_PRESERVE_ZERO_FRACTION);
     echo $query.PHP_EOL; 
    $ch    = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HEADER, false);
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $query);
    $response = curl_exec($ch);
    curl_close($ch);
    return $response;
}    