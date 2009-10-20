#ifndef _YGE_DISPLAY_H_
#define _YGE_DISPLAY_H_

class YGEDisplay {
public:
	virtual void setFullscreen(bool fullscreen) = 0;
	virtual void setResolution(int w, int h) = 0;
	virtual void setDepth(int depth) = 0;

	virtual void init() = 0;

	virtual void reset() = 0;


};

#endif
