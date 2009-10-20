#include "YGETimer.h"

class YGESDLTimer : protected YGETimer {
	/** 
	 * time at init of the timer
	 */
	long long basetime;

	/**
	 * time in milliseconds measured with this timer
	 * between call of startTimer() and stopTimer()
	 */
	long long stoppedTime;


public:

	YGESDLTimer();

	virtual long long getTime();

	virtual void startTimer();

	virtual long long stopTimer();

};