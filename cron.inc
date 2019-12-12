<?php

/*
 * CRON FOUNDATION <http://cronfoundation.org> 
 * CRON interface library
 */
ini_set('precision', 8);
ini_set('serialize_precision', 8);

include 'cron.ask.inc';
 
// The CRON asset hash.
// See https://tracker.cron.global/browse/asset/1 for another assets info
// Currently CRON and CRONIUM are implemented in RpcSystemAssetTrackerPlugin for JSON-RPC transfers
// https://github.com/cronfoundation/neo-plugins
// 
define('CRON_ASSET_HASH', '0x602c79718b16e442de58778e148d0b1084e3b2dffd5de6b7b16cee7969282de7') ;

/**
 * @description 
 * WARNING! 
 * The $privateKey parameter must be stored with encryption
 *  and the RPC-call must be executed securely, at the trusted servers
 * @param  $privateKey the private key of address 
 * @return an object with address data: address field is address itself
 */
function CRON_addressFromKey($privateKey)
{  
    $data = CronAsk("cron_get_address", array($privateKey));
    // echo json_encode($data).PHP_EOL; 
    return $data;
}

function CRON_generatePrivKeyExample($salt)
{
  $bytes = random_bytes(128). hex2bin($salt);
  return hash('sha256', hash('sha256', $bytes));  
}
 
/**
 * @description Transfer between single addresses
 * WARNING! 
 * The $privateKey parameter must be stored with encryption
 * and the RPC-call must be executed securely, at the trusted servers
 * @param       $privateKeyFrom the private key of address to fund from
 * @param       $addressTo      address to fund
 * @param       $amount  the amount to transfer
 * @param       $remarks OPTIONAL the remarks txn attribute value. Default is null 
 * @param       $fee     OPTIONAL the transaction fee. Default is zero 
 * @return      Txn hash as hex string on success or error code as negative 
 * integer number
*/
function CRON_transfer($privateKeyFrom, $addressTo, $amount, $remarks = null, $fee = 0.0)
{ 
    if($remarks != null)
    {
       if($fee > 0)
        $a = array($privateKeyFrom, $addressTo, $amount, "CRON", $remarks, $fee);
       else              
        $a = array($privateKeyFrom, $addressTo, $amount, "CRON", $remarks);
    }
    else              
        $a = array($privateKeyFrom, $addressTo, $amount, "CRON");
    $data = CronAsk("cron_send", $a);
    // echo json_encode($data).PHP_EOL; 
    $a = array_values((array)$data);
    return count($a) > 0? $a[0] : null;
}


/**
 * @description Transfer between single addresses
 * WARNING! 
 * The $privateKey parameter must be stored with encryption
 * and the RPC-call must be executed securely, at the trusted servers
 * @param       $privateKeyFrom the private key of address to fund from
 * @param       $targets = array((object)array("address" => "Axxxx...", "amount" => 123.45 ),
 *                               (object)array("address" => "Ayyyy...", "amount" => 678.99 ), ... );
 *              addresses and corresponding amounts to fund 
 * @param       $remarks OPTIONAL the remarks txn attribute value. Default is null 
 * @param       $fee     OPTIONAL the transaction fee. Default is zero 
 * @return      Txn hash as hex string on success or error code as negative 
 * integer number
*/
function CRON_transfer_1xN($privateKeyFrom, $targets, $remarks = null, $fee = 0)
{     
    if($remarks != null)
    {
       if($fee > 0)
        $a = array($privateKeyFrom, $targets, "CRON", $remarks, $fee);
       else              
        $a = array($privateKeyFrom, $targets, "CRON", $remarks);
    }
    else              
        $a = array($privateKeyFrom, $targets,"CRON");
    $data = CronAsk("cron_send_1xN", $a);
    // echo json_encode($data).PHP_EOL; 
    $a = array_values((array)$data);
    return count($a) > 0? $a[0] : null;
}

/**
 * @description Gets address current balance
 * @param  $address 
 * @return current balance of given address
 */
function CRON_getBalance($address)
{
    $data = CronAsk("getaccountstate", array($address));
    $sum = 0;
    
    // echo json_encode($data->balances).PHP_EOL; 
    
    foreach ($data->balances as $val)
    {
        if($val->asset == CRON_ASSET_HASH)
        {
            $sum += $val->value;
        }           
    }    
   
 return $sum;
}

/**
 * @description Gets the block number for existing Txn broadcasted over the CRON blockchain
 * @param type $txnHash transaction hash hex bytes string whose block number
 * should be returned
 * @return block number for the given Txn Hash or null if txn does
 * not exist in the CRON blockchain
 */
function CRON_getTxnBlock($txnHash)
{ 
    if($txnHash == null)
        return null;
    $a = CronAsk("cron_tx_block", array($txnHash));
    //  echo json_encode($data).PHP_EOL;
    if(is_array($a))
    return count($a) > 0? $a[0] : null;    
    else return null;
}


