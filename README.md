# piezo_player_9000
Piezo piano using a passive piezoelectric buzzer and tactile buttons on a Nucleo STM F103RB board.

## Implementation
### Requirements
The piano needs to be able to play the most recently pressed note, even if other keys are pressed. When the user releases a key, the next note played should be next key in reverse chronological order. i.e.:
* User holds down A,G, and E (in that order)
* The note played is E
* User releases G and E
* The note played is A

### Solution
The piano is implemented using a stack to track pressed keys. This allows the piano to always play the most recently pressed key while maintaining the order of previously pressed keys. Button presses trigger hardware interrupts which update the stack.

## Future Work
### Chords
A limitation of the current implementation is that it can only sound a single note at a time. i.e. it cannot play musical chords.

A piezo buzzer is an amplifier for electric signals, in this case a PWM signal produced by the MCU. The MCU produces musical notes by generating a PWM signal of the correct frequency. In a normal piano, playing multiple notes simultaneously causes constructive and destructive interence in the waveforms. This produces a complex and (critically) non-uniform waveform which corresponds to a chord. 

<img width="455" height="326" alt="chord_waveforms" src="https://github.com/user-attachments/assets/49036311-f0e9-4da3-8ca0-5391bdb803a8" />

A single piezo buzzer will amplify any signal it receives, so chords would be possible if the MCU could produce an accurate chord waveform. The challenge would be to determine the appropriate waveform and manipulate the clock in order to produce the signal. Another approach is to add multiple piezo buzzers to the player. The player could read keys off the stack up to the number of buzzers. With this approach the work of producing the chord waveform is offloaded onto physics. 

## Learnings
PWM signals, interrupts, button debouncing, PU and PD resistors, piezoelectric materials

## Demo 
[![Watch the video](https://img.youtube.com/vi/_WzDCoJYSG8/0.jpg)](https://youtu.be/_WzDCoJYSG8)

