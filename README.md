# Hello world, a basic RMR send/receiver

This repository contains a basic messaging example using RIC Messaging Router (RMR).

## Dependencies
1. Install the packages
   ~~~
   apt-get install -y build-essential
   wget -nv --content-disposition https://packagecloud.io/o-ran-sc/release/packages/debian/stretch/mdclog_0.0.4-1_amd64.deb/download.deb
   wget -nv --content-disposition https://packagecloud.io/o-ran-sc/release/packages/debian/stretch/mdclog-dev_0.0.4-1_amd64.deb/download.deb
   wget -nv --content-disposition https://packagecloud.io/o-ran-sc/release/packages/debian/stretch/rmr_4.4.6_amd64.deb/download.deb
   wget -nv --content-disposition https://packagecloud.io/o-ran-sc/release/packages/debian/stretch/rmr-dev_4.4.6_amd64.deb/download.deb
   wget --content-disposition https://packagecloud.io/o-ran-sc/staging/packages/debian/stretch/riclibe2ap_0.1.0_amd64.deb/download.deb
   wget --content-disposition https://packagecloud.io/o-ran-sc/staging/packages/debian/stretch/riclibe2ap-dev_0.1.0_amd64.deb/download.deb
   wget -nv --content-disposition https://packagecloud.io/o-ran-sc/release/packages/debian/stretch/rnib_1.0.0_all.deb/download.deb
   dpkg -i mdclog_0.0.4-1_amd64.deb mdclog-dev_0.0.4-1_amd64.deb rmr_4.4.6_amd64.deb rmr-dev_4.4.6_amd64.deb \
           riclibe2ap_0.1.0_amd64.deb riclibe2ap-dev_0.1.0_amd64.deb rnib_1.0.0_all.deb
   ~~~

2. Compile the programs
   ~~~
   make
   ~~~

## Usage
1. Start the receiver
   ~~~
   ./run-receiver
   ~~~
   
2. Run the sender
   ~~~
   ./run-sender "Hello World"
   ~~~
   
### Example receiver output
~~~
# ./run-receiver.sh 
starting up
1644501574 10414/RMR [INFO] ric message routing library on SI95/g mv=3 flg=00 (84423e6 4.4.6 built: Dec  4 2020)
waiting for rmr connection . connected
1644501575 10414/RMR [INFO] sends: ts=1644501575 src=ric:4562 target=127.0.0.1:4562 open=0 succ=0 fail=0 (hard=0 soft=0)
rcv state RMR_OK (state is good) payload Hello World
~~~
