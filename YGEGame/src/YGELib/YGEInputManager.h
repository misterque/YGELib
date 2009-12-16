#ifndef _YGE_INPUT_MANAGER_
#define _YGE_INPUT_MANAGER_

#include "YGEKeyDownListener.h"
#include "YGEKeyUpListener.h"
#include "YGEMouseMoveListener.h"

#include <list>

namespace YGEInput {


	/**
	* @brief observer style input distributer
	*/
	class YGEInputManager {
	protected:
		std::list<YGEKeyDownListener*> keydownlisteners;
		std::list<YGEKeyUpListener*> keyuplisteners;
		std::list<YGEMouseMoveListener*> mousemovelisteners;

		std::list<YGEKeyDownListener*> copyKeydownlisteners;
		std::list<YGEKeyUpListener*> copyKeyuplisteners;
		std::list<YGEMouseMoveListener*> copyMousemovelisteners;

	public:

		/**
		* @brief initialize this subsystem
		*/
		virtual void init();

		/**
		* @brief notifies all registered listeners about the event
		*/
		void notifyEvent(SDL_Event *event);

		void addKeyDownListener(YGEKeyDownListener* listener);

		void addKeyUpListener(YGEKeyUpListener* listener);

		void addMouseMoveListener(YGEMouseMoveListener* listener);

		void removeKeyDownListener(YGEKeyDownListener* listener);

		void removeKeyUpListener(YGEKeyUpListener* listener);

		void removeMouseMoveListener(YGEMouseMoveListener* listener);

	};

}
#endif