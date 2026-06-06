#ifndef INC_BUTTONSTATE_HPP_
#define INC_BUTTONSTATE_HPP_

#include "main.h"

enum note {
        C,
        D,
        E,
		F,
		G,
		A,
		B,
		NONE
};

class buttonState {
public:
	GPIO_TypeDef* port;
	uint16_t pin;
	bool debounced;
	enum note note;

	buttonState();
};

#endif /* INC_BUTTONSTATE_HPP_ */
