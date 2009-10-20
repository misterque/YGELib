#ifndef _YGE_CORE_H_
#define _YGE_CORE_H_

#define USE_SDL

#include "YGESDLDisplay.h"
#include "YGESDLInputManager.h"
#include "YGESDLTimer.h"

#include "YGELogger.h"


class YGECore {

	//@todo just use YGEDisplay... make it nicer... more PFI
	// true object orientation
	YGESDLDisplay* display;
	YGESDLInputManager* input;

	YGELogger* logger;

	YGESDLTimer* timer;

public:
	void run();
	void init();
	void update();
	
};


#endif