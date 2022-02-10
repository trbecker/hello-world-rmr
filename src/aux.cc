/*
 * Don't look under the hood...
 * Really, there's nothing here but some auxiliary functions to make the execution more understandable.
 */
#include <rmr/rmr.h>

struct {
	int rmr_err;
	const char *rmr_msg;
} rmr_errors[] = {
	{ RMR_OK, "RMR_OK (state is good)" },
	{ RMR_ERR_BADARG, "RMR_ERR_BADARG (argument passd to function was unusable)" },
	{ RMR_ERR_NOENDPT, "RMR_ERR_NOENDPT (send/call could not find an endpoint based on msg type)" },
	{ RMR_ERR_EMPTY, "RMR_ERR_EMPTY (msg received had no payload; attempt to send an empty message)" },
	{ RMR_ERR_NOHDR, "RMR_ERR_NOHDR (message didn't contain a valid header)" },
	{ RMR_ERR_SENDFAILED, "RMR_ERR_SENDFAILED (send failed; errno has nano reason)" },
	{ RMR_ERR_CALLFAILED, "RMR_ERR_CALLFAILED (unable to send call() message)" },
	{ RMR_ERR_NOWHOPEN, "RMR_ERR_NOWHOPEN (no wormholes are open)" },
	{ RMR_ERR_WHID, "RMR_ERR_WHID (wormhole id was invalid)" },
	{ RMR_ERR_OVERFLOW, "RMR_ERR_OVERFLOW (operation would have busted through a buffer/field size)" },
	{ RMR_ERR_RETRY, "RMR_ERR_RETRY (request (send/call/rts) failed, but caller should retry (EAGAIN for wrappers))" },
	{ RMR_ERR_RCVFAILED, "RMR_ERR_RCVFAILED (receive failed (hard error))" },
	{ RMR_ERR_TIMEOUT, "RMR_ERR_TIMEOUT (message processing call timed out)" },
	{ RMR_ERR_UNSET, "RMR_ERR_UNSET (the message hasn't been populated with a transport buffer)" },
	{ RMR_ERR_TRUNC, "RMR_ERR_TRUNC (received message likely truncated)" },
	{ RMR_ERR_INITFAILED, "RMR_ERR_INITFAILED (initialisation of something (probably message) failed)" },
	{ RMR_ERR_NOTSUPP, "RMR_ERR_NOTSUPP (the request is not supported, or RMr was not initialised for the request)" }
};

const char *rmr_error(int error)
{
	return rmr_errors[error].rmr_msg;
}
