#ifndef _YGE_TIMER_H_
#define _YGE_TIMER_H_


class YGETimer {
protected:
public:
	/**
	 * @return time in microseconds since game has started
	 */
	virtual long long getTime() = 0;

	/**
	 * start the timer
	 */
	virtual void startTimer() = 0;

	/**
	 * stop the timer
	 * @return time in microseconds between start and calling of this
	 * function
	 */
	virtual long long stopTimer() = 0;


};

#endif