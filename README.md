

# cron-php-integration

2020-02-07: New Plugins release: https://github.com/cronfoundation/neo-plugins/releases/tag/v2.9.4.6

#### CRON Integration Note

To quickly integrate CRON as a payment tool, it is proposed to use the plugin for CRONIUM v.2.9.4 RpcSystemAssetTracker
https://github.com/cronfoundation/neo-plugins/tree/master/RpcSystemAssetTracker

Intended use: generate private keys with random numbers and hash, transfer them to cron_get_address and receive addresses. Also, private keys will then be needed for cron_send to transfer funds from these addresses. Private keys should be stored in an encrypted database, and the JSON-RPC call should be internal (on the same machine as the RPC node). 