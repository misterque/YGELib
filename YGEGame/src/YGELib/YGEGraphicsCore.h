#ifndef _YGE_DISPLAY_H_
#define _YGE_DISPLAY_H_

#include "YGEGraphicsContext.h"

namespace YGETimeSpace {
	class YGESpace;
	class YGEEntity;
	class YGEObserver;
}

namespace YGECore {

class YGEGraphicsCore {
private:
	YGEGraphicsContext context;
	void renderEntity(YGETimeSpace::YGEEntity* entity);

public:
	int windowClosed;

	virtual void setFullscreen(bool fullscreen) = 0;
	virtual void setResolution(int w, int h) = 0;
	virtual void setDepth(int depth) = 0;

	virtual void init() = 0;

	virtual void reset() = 0;

	virtual void update() = 0;

	virtual void setTitle(const char* title) = 0;


	void renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer);


};

}

#endif
