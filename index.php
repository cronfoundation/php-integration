<?php

/*
 * CRON FOUNDATION <http://cronfoundation.org> 
 * CRON Library Example
 */

// URL of CRON RPC NODE:
// https://github.com/cronfoundation/cron-node
// You need also to install our custom edition of RpcSystemAssetTracker plugin:
// https://github.com/cronfoundation/neo-plugins/tree/master/RpcSystemAssetTracker
// It's better to use it wrapped in HTTPS prootocol
define('URL_CRON_RPC_NODE', 'http(s)://<YOUR_CRON_NODE_HOST>:<RPC_PORT_OF_NODE>');

set_time_limit(60);

include 'cron.inc';

$a1 = "<address01>"; // i.e AP9uMNczdkCwJ7JkiDR842qM5pgV2doiTi
$a2 = "<Address02>"; // i.e AP9uMNczdkCwJ7JkiDR842qM5pgV2doiTi
$a3 = "<Address02>"; // i.e AP9uMNczdkCwJ7JkiDR842qM5pgV2doiTi

$pkSpend1 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
$aiSpend1 = CRON_addressFromKey($pkSpend1);

$pkSpend2 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
$aiSpend2 = CRON_addressFromKey($pkSpend2);

$pkSpend3 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
$aiSpend3 = CRON_addressFromKey($pkSpend3);

echo "<html><body><pre>"; 
echo "Block Count: " . json_encode( CronAsk("getblockcount") ). PHP_EOL; 

echo PHP_EOL.PHP_EOL."TEST BALANCES".PHP_EOL.PHP_EOL;
echo "$a1: ". CRON_getBalance($a1) .PHP_EOL;
echo "$a2: ". CRON_getBalance($a2) .PHP_EOL;
echo "$a3: ". CRON_getBalance($a3) .PHP_EOL;

echo "Address to spend from: $aiSpend1->address: ". CRON_getBalance($aiSpend1->address) .PHP_EOL;
echo "Address to spend from: $aiSpend2->address: ". CRON_getBalance($aiSpend2->address) .PHP_EOL;
echo "Address to spend from: $aiSpend3->address: ". CRON_getBalance($aiSpend3->address) .PHP_EOL;

echo PHP_EOL.PHP_EOL."TEST Transfers".PHP_EOL.PHP_EOL;

$txn1 = CRON_transfer($pkSpend1, $a1, 0.0001); sleep(5);
$txn2 = CRON_transfer($pkSpend2, $a2, 0.0001); sleep(3);
$txn3 = CRON_transfer($pkSpend3, $a3, 0.0001);

echo "$a1: ". $txn1 .PHP_EOL;  
echo "$a2: ". $txn2 .PHP_EOL;  
echo "$a3: ". $txn3 .PHP_EOL;  
sleep (16); 

echo PHP_EOL.PHP_EOL."TEST Txn blocks".PHP_EOL.PHP_EOL;
echo "Block for $a1 $txn1: ". CRON_getTxnBlock($txn1).PHP_EOL;
echo "Block for $a2 $txn2: ". CRON_getTxnBlock($txn2).PHP_EOL;
echo "Block for $a3 $txn3: ". CRON_getTxnBlock($txn3).PHP_EOL;


?>

