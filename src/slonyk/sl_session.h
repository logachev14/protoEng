#pragma once
#include "slonyk_segment.h"

class SlSession
{
public :
	virtual void onSegmentReceived(SlSegment & segment) = 0;
	virtual void sync() = 0;
	virtual ~SlSession(){};
};
