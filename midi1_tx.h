#ifndef MIDI1_TX_H
#define MIDI1_TX_H

#include <stddef.h>

#include "midi1.h"

typedef uint8_t err_t;

#define MIDI_H2B(h, l) (h<<4|l)

#define MIDI_MSG_DEF_2B(name, s, da, db) \
inline err_t Midi##name(struct MidiTransmitterState *state, uint8_t ch, uint8_t da, uint8_t db) { \
  state->status = MIDI_H2B(s, ch); \
  uint8_t seq[] = {state->status, da, db}; \
  return state->t->Transmit(state->t, seq, sizeof seq); \
}
#define MIDI_MSG_DEF_1B(name, s, da) \
inline err_t Midi##name(struct MidiTransmitterState *state, uint8_t ch, uint8_t da) { \
  state->status = MIDI_H2B(s, ch); \
  uint8_t seq[] = {state->status, da}; \
  return state->t->Transmit(state->t, seq, sizeof seq); \
}


#define MIDI_SYS_MSG_DEF_2B(name, s, da, db) \
inline err_t Midi##name(struct MidiTransmitterState *state, uint8_t da, uint8_t db) { \
  state->status = s; \
  uint8_t seq[] = {s, da, db}; \
  return state->t->Transmit(state->t, seq, sizeof seq); \
}
#define MIDI_SYS_MSG_DEF_1B(name, s, da) \
inline err_t Midi##name(struct MidiTransmitterState *state, uint8_t da) { \
  state->status = s; \
  uint8_t seq[] = {s, da}; \
  return state->t->Transmit(state->t, seq, sizeof seq); \
}
#define MIDI_SYS_MSG_DEF(name, s) \
inline err_t Midi##name(struct MidiTransmitterState *state) { \
  state->status = s; \
  return state->t->Transmit(state->t, &state->status, 1); \
}


#define MIDI_SYS_RT_DEF(name, s) \
inline err_t Midi##name(const struct MidiTransmitter *t) { \
  uint8_t message = s; \
  return t->Transmit(t, &message, 1); \
}


struct MidiTransmitter {
  err_t (*Transmit)(const struct MidiTransmitter *handle, const uint8_t *buf, size_t size);
  void *handle;
};

struct MidiTransmitterState {
  uint8_t status; // running state
  struct MidiTransmitter *t;
};

MIDI_MSG_DEF_2B(SetNoteOn, MIDI_STATUS_NOTE_ON, note, velocity)
MIDI_MSG_DEF_2B(SetNoteOff, MIDI_STATUS_NOTE_OFF, note, velocity)
MIDI_MSG_DEF_2B(SetPolyphonicKeyPressure, MIDI_STATUS_POLYPHONIC_KEY_PRESSURE, note, pressure)
MIDI_MSG_DEF_2B(ChangeControl, MIDI_STATUS_CONTROL_CHANGE, num, val)
MIDI_MSG_DEF_1B(ChangeProgram, MIDI_STATUS_PROGRAM_CHANGE, num)
MIDI_MSG_DEF_1B(SetChannelPressure, MIDI_STATUS_CHANNEL_PRESSURE, pressure)
MIDI_MSG_DEF_2B(SetPitchBend, MIDI_STATUS_PITCH_BEND_CHANGE, bend_ls_byte, bend_ms_byte)

MIDI_SYS_MSG_DEF_2B(SetSongPosition, MIDI_STATUS_SYS_COMMON_SONG_POSITION_POINTER, num_ms_byte, num_ls_byte)
MIDI_SYS_MSG_DEF_1B(SelectSong, MIDI_STATUS_SYS_COMMON_SONG_SELECT, num)
MIDI_SYS_MSG_DEF(RequestTune, MIDI_STATUS_SYS_COMMON_TUNE_REQUEST)

MIDI_SYS_MSG_DEF(ExclusiveBegin, MIDI_STATUS_SYS_EX_START)
MIDI_SYS_MSG_DEF(ExclusiveEnd, MIDI_STATUS_SYS_EX_END)

MIDI_SYS_RT_DEF(Start, MIDI_STATUS_SYS_RT_START)
MIDI_SYS_RT_DEF(Continue, MIDI_STATUS_SYS_RT_CONTINUE)
MIDI_SYS_RT_DEF(Stop, MIDI_STATUS_SYS_RT_STOP)
MIDI_SYS_RT_DEF(KeepAlive, MIDI_STATUS_SYS_RT_ACTIVE_SENSING)
MIDI_SYS_RT_DEF(SystemReset, MIDI_STATUS_SYS_RT_SYSTEM_RESET)

err_t MidiSetNoteOnWithState(struct MidiTransmitterState *state, uint8_t ch, uint8_t note, uint8_t velocity);

inline err_t MidiSetNoteOffWithState(struct MidiTransmitterState *state, uint8_t ch, uint8_t note) {
  return MidiSetNoteOnWithState(state, ch, note, 0);
}

inline err_t MidiSyncTimeCode(const struct MidiTransmitter *t, uint8_t h, uint8_t m, uint8_t s, uint8_t frame) {
  uint8_t seq[] = {MIDI_STATUS_SYS_RT_TIMING_CLOCK, h,
                   MIDI_STATUS_SYS_RT_TIMING_CLOCK, m,
                   MIDI_STATUS_SYS_RT_TIMING_CLOCK, s,
                   MIDI_STATUS_SYS_RT_TIMING_CLOCK, frame};
  return t->Transmit(t, seq, sizeof seq);
}

#endif //MIDI1_TX_H
