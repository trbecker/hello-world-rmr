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
