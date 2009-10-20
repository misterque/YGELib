#ifndef _YGE_TIMER_H_
#define _YGE_TIMER_H_


class YGETimer {

public:
	static void fetchBasetime();

	long long getTime();

	void startTimer();
	long long stopTimer();


};
