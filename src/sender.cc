#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>

#include <rmr/rmr.h>
#include "aux.h"

/* The port at which we listen to */
#define PORT "4561"

/* The payload of the message */
#define MESSAGE "Message Payload"

using namespace std;

int main(int argc, char **argv) {
	void *rmr_ctx;
	rmr_mbuf_t *msg = NULL, *reply;

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



	/* Send the message. If RMR tells us to retry, then retry sending the message. */
	do {
		/* Free the previous message */
		if (msg)
			rmr_free_msg(msg);

		/* Allocate a new message */
		msg = rmr_alloc_msg(rmr_ctx, RMR_DEF_SIZE);

		/* Copy the message payload */
		memcpy(msg->payload, MESSAGE, std::strlen(MESSAGE));
		/* Need to define an endpoint */

		msg->mtype = 0;
		msg->len = std::strlen(MESSAGE);
		msg->state = RMR_OK;

		/* Send the message */
		reply = rmr_send_msg(rmr_ctx, msg);
	} while(reply->state == RMR_ERR_RETRY);
	/* RANT: rmr returns the same struct  that is passed into it, which is a bad design.
	 * It's unclear if it will consume the message and free it.
	 * In this form, it just overcomplicates the memory management from the application perspective.
	 * It should instead create a new message, transfer it to the callee to manage.
	 * The test below shows if the message and reply are the same.
	 */

	if (msg == reply) 
		std::cerr << "msg and reply are the same" << std::endl;
	else
		std::cerr << "msg and reply are different" << std::endl;

	if (!reply)
		std::cout << "Error in sending message" << std::endl;
	else if (reply->state != RMR_OK)
		std::cout << "rmr message got error " << rmr_error(reply->state) << std::endl;

	std::cout << "message sent, mtype=" << reply->mtype << ", state=" << reply->state << std::endl;

	return 0;
}
