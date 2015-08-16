#include "CommunicationProtocol.h"

rt_err_t getProtocalData(CommunicationProtocol *cp ,rt_uint8_t * data)
{
	cp = (CommunicationProtocol *)data;
	return RT_EOK;
}

