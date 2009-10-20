#ifndef _YGE_CORE_H_
#define _YGE_CORE_H_

#define USE_SDL

#include "YGESDLDisplay.h"


class YGECore {

	//@todo just use YGEDisplay... make it nicer... more PFI
	YGESDLDisplay* display;

public:
	void run();
	void init();
};


#endif