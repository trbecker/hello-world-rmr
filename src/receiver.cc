#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>

#include <rmr/rmr.h>
#include "aux.h"

/* The port at which we listen to */
#define PORT "4562"

/* The payload of the message */
#define MESSAGE "Message Payload"

using namespace std;

int main(int argc, char **argv) {
	void *rmr_ctx;
	rmr_mbuf_t *msg = NULL;

	std::cout << "starting up" << std::endl;

	/*
	 * This will start the communication thread...
	 */
	rmr_ctx = rmr_init(PORT, RMR_MAX_RCV_BYTES, RMRFL_NONE);

	std::cout << "waiting for rmr connection ";

	/*
	 * Wait until rmr communication thread is ready
	 */
	while(!rmr_ready(rmr_ctx)) {
		std::cout << "." << std::flush;
		std::this_thread::sleep_for(1000ms);
	}
	std::cout << " connected" << std::endl;
	/* RMR is ready */

	while (true) {
		msg = rmr_rcv_msg(rmr_ctx, msg);
		if (!msg) {
			std::cout << "received NULL" << std::endl;
			continue;
		}

		std::cout << "rcv state" << rmr_error(msg->state) << std::endl;
	}

	return 0;
}
