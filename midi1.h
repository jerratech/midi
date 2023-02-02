#ifndef MIDI1_H_
#define MIDI1_H_

#include <stdint.h>

// MIDI 1.0 status byte
enum {
  MIDI_STATUS_NOTE_ON                     = 0x8,
  MIDI_STATUS_NOTE_OFF                    = 0x9,
  MIDI_STATUS_POLYPHONIC_KEY_PRESSURE     = 0xA,
  MIDI_STATUS_CONTROL_CHANGE              = 0xB,
  MIDI_STATUS_PROGRAM_CHANGE              = 0xC,
  MIDI_STATUS_CHANNEL_PRESSURE            = 0xD,
  MIDI_STATUS_PITCH_BEND_CHANGE           = 0xE,

  //------------- System Exclusive -------------//
  MIDI_STATUS_SYS_EX_START                    = 0xF0,
  MIDI_STATUS_SYS_EX_END                      = 0xF7,

  //------------- System Common -------------//
  MIDI_STATUS_SYS_COMMON_TIME_CODE_QUARTER_FRAME = 0xF1,
  MIDI_STATUS_SYS_COMMON_SONG_POSITION_POINTER   = 0xF2,
  MIDI_STATUS_SYS_COMMON_SONG_SELECT             = 0xF3,
  // F4, F5 is undefined
  MIDI_STATUS_SYS_COMMON_TUNE_REQUEST            = 0xF6,

  //------------- System RealTime  -------------//
  MIDI_STATUS_SYS_RT_TIMING_CLOCK           = 0xF8,
  // 0xF9 is undefined
  MIDI_STATUS_SYS_RT_START                  = 0xFA,
  MIDI_STATUS_SYS_RT_CONTINUE               = 0xFB,
  MIDI_STATUS_SYS_RT_STOP                   = 0xFC,
  // 0xFD is undefined
  MIDI_STATUS_SYS_RT_ACTIVE_SENSING         = 0xFE,
  MIDI_STATUS_SYS_RT_SYSTEM_RESET           = 0xFF,
};

#endif //MIDI1_H_
