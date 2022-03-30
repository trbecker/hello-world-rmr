# Building the e2-interface (e2-simulator)
How to build the e2sim.

## Pre-requisites
- Install the needed packages
~~~
  # apt-get update && apt-get install -y build-essential \
        git cmake libsctp-dev autoconf automake libtool \
        bison flex libboost-all-dev
~~~
- Get the repositories
~~~
  # git clone https://gerrit.o-ran-sc.org/r/sim/e2-interface
~~~
- Get the JSON library
~~~
  # mkdir -p /usr/local/include/nlohmann
  # wget https://github.com/nlohmann/json/releases/download/v3.7.3/json.hpp \
      -O /usr/local/include/nlohmann/json.hpp
~~~

## Building the packages
- Build and install the libraries
~~~
  # cd e2-interface/e2sim
  # mkdir -p build
  # cmake ..
  # make package
  # cmake .. -DDEV_PKG=1
  # make package
  # dpkg -i e2sim*.deb
~~~
- Build the `kpm_sim`
~~~
  # cd ../e2sm_examples/kpm_e2sm/
  # mkdir -p build
  # cd build/
  # cmake ..
  # make
  # make install
~~~
- The `kpm_sim` build may fail; in this case, the attached patch may be helpfull to complete the build.
  - The patch adjusts the `cmake` version and add the `RUNTIME DESTINATION bin` directive.

## Running
- Find the ip address and sctp port of the `e2term`:
~~~
# docker ps | grep e2term
528abee4e260   52c4773dbd07           "sh -c ./startup.sh"     25 minutes ago   Up 25 minutes             k8s_container-ricplt-e2term_deployment-ricplt-e2term-alpha-cfb5c4864-2bvxv_ricplt_d486a4b7-b634-4771-bdb3-1b35d426a0da_0

# docker exec 528abee4e260 ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1450
        inet 10.244.0.38  netmask 255.255.255.0  broadcast 0.0.0.0
        ether b2:24:c2:0a:af:e0  txqueuelen 0  (Ethernet)
        RX packets 1574  bytes 201474 (201.4 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 1533  bytes 176745 (176.7 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

# docker exec 528abee4e260 netstat -nlp --sctp
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
sctp                :::36422                                        LISTEN      22/./e2
~~~
- The ip address is `10.244.0.38` and port `36422`. Start the `kpm_sim` with these parameters.
~~~
# cd ..
# ./build/src/kpm/kpm_sim 10.244.0.38 36422
~~~
## Notes
- The last message I recieved now is:
~~~
[E2AP] Received SETUP-RESPONSE-SUCCESS
receive data1
receive data2
~~~
- No messages in `e2term`'s log.
