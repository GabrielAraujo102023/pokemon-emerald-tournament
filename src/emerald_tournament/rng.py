"""Emerald Random(), accepting an explicit full 32-bit internal state.

SeedRng in the game takes u16. This constructor deliberately sets gRngValue
instead, allowing replay from arbitrary saved states. No frame calls are added.
"""
from dataclasses import dataclass


@dataclass
class EmeraldRng:
    state: int
    calls: int = 0

    def __post_init__(self) -> None:
        if not 0 <= self.state <= 0xFFFFFFFF:
            raise ValueError("RNG state must be an unsigned 32-bit integer")

    def random16(self) -> int:
        self.state = (1103515245 * self.state + 24691) & 0xFFFFFFFF
        self.calls += 1
        return self.state >> 16
