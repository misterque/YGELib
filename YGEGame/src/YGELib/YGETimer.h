#ifndef _YGE_TIMER_H_
#define _YGE_TIMER_H_

#include "YGETimer.h"

namespace YGECore {


	class YGETimer {
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

		YGETimer();

		/**
		* @return time in microseconds since game has started
		*/
		virtual long long getTime();


		/**
		* start the timer
		*/
		virtual void startTimer();

		/**
		* stop the timer
		* @return time in microseconds between start and calling of this
		* function
		*/
		virtual long long stopTimer();

	};

}

#endif