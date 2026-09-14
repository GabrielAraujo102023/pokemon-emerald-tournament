# Future native backend

Do not implement a native simulator or relocation backend before the emulated reference battle passes. A future optimization may preserve four-byte script fields and use typed virtual addresses resolved through checked script, constant-data and writable-memory regions. Numeric immediates remain numeric. C callback pointers require a distinct representation.

Generate relocation metadata from reviewed operand semantics and linked symbols. Cover explicit READ_32 casts, C-to-script references, saved cursors/return addresses and non-script data references. Never globally widen .4byte or u32. Validate bounds, nulls and region permissions; use the emulated engine's decoded states, actions, RNG and terminal traces as the differential oracle. Throughput is unmeasured and does not justify a fidelity compromise.
