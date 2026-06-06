/*
 * player.cpp
 *
 *  Created on: Jun 1, 2026
 *      Author: lrose
 */

#include "main.h"
#include "buttonState.hpp"
#include "player.hpp"
#include <stack>
#include <optional>

uint32_t button_push_detected_time = 0;
uint32_t last_trigger_time = 0;
int j = 0;
buttonState cur_button_state;
std::stack<buttonState> button_st;

enum note note_arr[] = {C, A, F, C, D, E, F, D, F, C};
int32_t time_arr[] = {1000, 1000, 1000, 1000, 500, 500, 500, 1000, 500, 1500};//{NOTE_E, NOTE_C, NOTE_A, NOTE_F, NOTE_G, NOTE_A, NOTE_B, NOTE_G, NOTE_B, NOTE_F};
int length = sizeof(note_arr) / sizeof(note_arr[0]);

int  handle_button_trigger() {
//	stack<buttonState> button_st;
	if (button_st.empty()) {
		return 0;
	}

	buttonState top_button_state = button_st.top();

	uint32_t current_time = HAL_GetTick();

	if (cur_button_state.note != top_button_state.note) { // first push detected
		button_push_detected_time = current_time;
		cur_button_state = top_button_state;
		return 0;
	}

	if (cur_button_state.debounced) {
		if (HAL_GPIO_ReadPin(top_button_state.port, top_button_state.pin)) {
			button_st.pop(); // remove the element after it's no longer pushed
			return 0;
		}
	}

	// if the button is still pushed after 10 ticks, button is stable
	uint32_t time_diff = current_time - button_push_detected_time;
	if (!(time_diff > 10)) {
		return 0;
	}
	if (HAL_GPIO_ReadPin(top_button_state.port, top_button_state.pin)) {
		button_st.pop(); // remove the element after it's no longer pushed
		return 0;
	}
	cur_button_state.debounced = true;
	return 1;
}


// note -> arr
int32_t get_arr(enum note note) {
	 switch (note) {
	 case C: return 17200;
	 case D: return 15323.6;
	 case E: return 13652;
	 case F: return 12886;
	 case G: return 11479.7;
	 case A: return 10228;
	 case B: return 9111.5;
	 case NONE: return 0;
	 }
}

void play_tune() {

	  int32_t CH1_DC = get_arr(note_arr[j]);
	  TIM2->ARR = CH1_DC;
	  TIM2->CCR1 = CH1_DC*.5;
	  HAL_Delay(time_arr[j]);

	  j = j+1;
	  if (j >= length) {
		  j = 0;
		  TIM2->CCR1 = 0;
		  HAL_Delay(500);
	  }

}

void loop() {


//	  HAL_GPIO_WritePin(GPIOA, 5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, 5, GPIO_PIN_SET);

	 if(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
		 play_tune();
		 return;
	 }


	  int button_down = handle_button_trigger();
	  if (!button_down) {

		  TIM2->CCR1 = 0;
		  return;
	  }
	  if (cur_button_state.note == NONE) {
		  TIM2->CCR1 = 0;
		  return;
	  }

	  int32_t CH1_DC = get_arr(cur_button_state.note);
	  TIM2->ARR = CH1_DC;
	  TIM2->CCR1 = CH1_DC*.5;

}

void setup() {

}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//  static uint32_t last_trigger_time = 0;
  if(GPIO_Pin == GPIO_PIN_1) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = C;
	  button_st.push(curr_button_state);
  }
  if(GPIO_Pin == GPIO_PIN_4) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = D;
	  button_st.push(curr_button_state);
  }
  if(GPIO_Pin == GPIO_PIN_5) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = E;
	  button_st.push(curr_button_state);
  }

  // f g a b
  if(GPIO_Pin == GPIO_PIN_6) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = F;
	  button_st.push(curr_button_state);
  }

  if(GPIO_Pin == GPIO_PIN_7) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = G;
	  button_st.push(curr_button_state);
  }

  if(GPIO_Pin == GPIO_PIN_8) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = A;
	  button_st.push(curr_button_state);
  }

  if(GPIO_Pin == GPIO_PIN_9) {

	  buttonState curr_button_state;
	  curr_button_state.pin = GPIO_Pin;
	  curr_button_state.port = GPIOA;
	  curr_button_state.note = B;
	  button_st.push(curr_button_state);
  }
}



