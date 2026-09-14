/* Proposed ABI v1; contract only. This header does not implement a battle adapter.
 * Use upstream u32 after global.h in the ARM build. No native pointer fields.
 */
#ifndef TOURNAMENT_PROTOCOL_H
#define TOURNAMENT_PROTOCOL_H
#define TOURNAMENT_MAGIC 0x45544F55u
#define TOURNAMENT_ABI 1u
/* All words are little endian. Pointers are real ARM addresses from the ELF. */
enum TournamentPhase {
    TOURNAMENT_IDLE, TOURNAMENT_REQUEST_LOADED, TOURNAMENT_CHECKPOINT_READY,
    TOURNAMENT_RNG_SEEDED, TOURNAMENT_PARTIES_CONSTRUCTED,
    TOURNAMENT_RUNNING, TOURNAMENT_COMPLETE, TOURNAMENT_RESULT_READY,
    TOURNAMENT_ERROR
};
struct TournamentControl {
    u32 magic, abi, phase;
    u32 trainer_a, trainer_b, seed, rules_version;
    u32 outcome, turns, rng_start, rng_after_party_init, rng_final;
    u32 event_count, event_overflow, event_address, event_capacity;
    u32 initial_party_address, initial_party_size;
    u32 final_party_address, final_party_size;
    u32 decoded_address, decoded_count;
    u32 error_code;
};
/* outcome: 0 unset, 1 A wins, 2 B wins, 3 engine draw, 4 timeout, 5 error.
 * Event append-only buffer must fail closed on overflow. No silent wrapping.
 */
struct TournamentEvent {
    u32 sequence, turn, kind, battler, value0, value1, rng, phase;
};
/* GetMonData-derived initial snapshot. One record per nonempty party slot. */
struct TournamentMonSnapshot {
    u32 side, slot, species, level, personality, ot_id, nature, ability, gender;
    u32 hp, max_hp, attack, defense, speed, sp_attack, sp_defense, status, held_item;
    u32 move0, move1, move2, move3, pp0, pp1, pp2, pp3, friendship, experience;
};
extern volatile struct TournamentControl gTournamentControl;
#endif
