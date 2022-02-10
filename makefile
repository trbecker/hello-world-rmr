all: sender receiver

sender: src/sender.cc src/aux.cc src/aux.h
	g++ -g -o sender src/sender.cc src/aux.cc -I /usr/local/include -L/usr/local/lib -lrmr_si -pthread
	
receiver: src/receiver.cc src/aux.cc src/aux.h
	g++ -g -o receiver src/receiver.cc src/aux.cc -I /usr/local/include -L/usr/local/lib -lrmr_si -pthread
