Introduction
=======================
This guide is for a single masternode, on a Ubuntu 18.04 64bit server (VPS) running headless and will be controlled from the wallet on your local computer (Control wallet). The wallet on the the VPS will be referred to as the Remote wallet.
You will need your server details for progressing through this guide.

First the basic requirements:
------------------------
* 5,000 BULL
* A main computer (Your everyday computer) – This will run the control wallet, hold your collateral 5,000 BULL and can be turned on and off without affecting the masternode.
* Masternode Server (VPS – The computer that will be on 24/7)
* A unique IP address for your VPS / Remote wallet
(For security reasons, you’re are going to need a different IP for each masternode you plan to host)

The basic reasoning for these requirements is that, you get to keep your BULL in your local wallet and host your masternode remotely, securely.

Configuration
------------------------

Note: The auto zBULL minter should be disabled during this setup to prevent autominting of your masternode collateral. BEFORE unlocking your wallet, you can disable autominting in the control wallet option menu.

* 1) Using the control wallet, enter the debug console (Tools > Debug console) and type the following command:
masternode genkey (This will be the masternode’s privkey. We’ll use this later…)

* 2) Using the control wallet still, enter the following command:
getaccountaddress chooseAnyNameForYourMasternode

* 3) Still in the control wallet, send 5,000 BULL to the address you generated in step 2 (Be 100% sure that you entered the address correctly. You can verify this when you paste the address into the “Pay To:” field, the label will autopopulate with the name you chose”, also make sure this is exactly 5,000 BULL; No less, no more.)
– Be absolutely 100% sure that this is copied correctly. And then check it again. We cannot help you, if you send 5,000 BULL to an incorrect address.

* 4) Still in the control wallet, enter the command into the console:
masternode outputs
 (This gets the proof of transaction of sending 5,000)

* 5) Still on the main computer, go into the bulldog data directory, by default in Windows it’ll be
%Appdata%/bulldog
or Linux
~

Find masternode.conf and add the following line to it:
------------------------
```
 <Name of Masternode(Use the name you entered earlier for simplicity)> <Unique IP address>:26740 <The result of Step 1> <Result of Step 4> <The number after the long line in Step 4>

Example: MN1 31.14.135.27:26740 892WPpkqbr7sr6Si4fdsfssjjapuFzAXwETCrpPJubnrmU6aKzh c8f4965ea57a68d0e6dd384324dfd28cfbe0c801015b973e7331db8ce018716999 1

Substitute it with your own values and without the “<>”s
```
VPS Remote wallet install
------------------------
* 7) Install the latest version of the bulldog wallet onto your masternode. The lastest version can be found here: https://github.com/BulldogCrew/bulldog/releases/tag/v2.0.0

* Go to your home directory:
* cd ~
* From your home directory, download the latest version from the bulldog GitHub repository:
wget https://github.com/BulldogCrew/bulldog/releases/download/v2.0.0/ubuntu1804-daemon.zip
* The link above is for Ubuntu (or similar), make sure you choose the correct version of the core wallet if you are not using Ubuntu from: 
https://github.com/BulldogCrew/bulldog/releases/tag/v2.0.0
* Unzip and extract:  
* unzip bulldog-ubuntu18.04.zip
* Go to your bulldog-ubuntu18  directory:
* cd ~/bulldog-ubuntu18
Note: If this is the first time running the wallet in the VPS, you’ll need to attempt to start the wallet 
* ./bulldogd
 this will place the config files in your ~/.bulldog data directory
* press 
CTRL+C
 to exit / stop the wallet then continue to step 8
Configuration Cont.
------------------------
* 8) Now on the masternodes, find the bulldog data directory here.(Linux: ~/.bulldog)
cd ~/.bulldog

* 9) Open the bulldog.conf by typing 
vi bulldog.conf
 then press i to go into insert mode and make the config look like this:
```
 rpcuser=long random username
 rpcpassword=longer random password
 rpcallowip=127.0.0.1
 server=1
 daemon=1
 logtimestamps=1
 maxconnections=256
 masternode=1
 externalip=your unique public ip address
 masternodeprivkey=Result of Step 1
 ```
Make sure to replace rpcuser and rpcpassword with your own.

* 10) to exit the editor press 
esc
 then 
:wq!
 then press enter

Start your masternode
* 11) Now, you need to finally start these things in this order
– Start the daemon client in the VPS. First go back to your installed wallet directory, 
```
cd ~/bulldog-ubuntu18.04/
```
and then start the wallet using 
```
./bulldogd
```
– From the Control wallet debug console
startmasternode alias false <mymnalias>

where <mymnalias> is the name of your masternode alias (without brackets)

The following should appear:
“overall” : “Successfully started 1 masternodes, failed to start 0, total 1”,
“detail” : [
{
“alias” : “<mymnalias>”,
“result” : “successful”,
“error” : “”
}

– Back in the VPS (remote wallet), start the masternode
./bulldog-cli startmasternode local false

– A message “masternode successfully started” should appear

* 12)Use the following command to check status:

./bulldog-cli masternode status

You should see something like:
```
{
“txhash” : “334545645643534534324238908f36ff4456454dfffff51311”,
“outputidx” : 0,
“netaddr” : “175.11.111.111:26740”,
“addr” : “B6fujc45645645445645R7TiCwexx1LA1”,
“status” : 4,
“message” : “Masternode successfully started”
}
```
Congratulations! You have successfully created your masternode!

Now the masternode setup is complete, you are safe to remove “enablezeromint=0” from the bulldog.conf file of the control wallet.`
