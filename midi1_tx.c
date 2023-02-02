#include "midi1_tx.h"

err_t MidiSetNoteOnWithState(struct MidiTransmitterState *state, uint8_t ch, uint8_t note, uint8_t velocity) {
  if (state->status == MIDI_H2B(MIDI_STATUS_NOTE_ON, ch)) {
    uint8_t seq[] = {note, velocity};
    return state->t->Transmit(state->t, seq, sizeof seq);
  }
  return MidiSetNoteOn(state, ch, note, velocity);
}