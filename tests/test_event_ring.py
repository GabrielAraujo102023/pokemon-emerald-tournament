"""Ring arithmetic regression tests; not substitutes for real ARM overflow evidence."""
import pytest
from emerald_tournament.emu_protocol import ring_spans


def test_physical_spans_cross_capacity():
    assert ring_spans(126,132,128)==[(126,2),(0,4)]
    assert ring_spans(128,256,128)==[(0,128)]
    assert ring_spans(132,132,128)==[]


@pytest.mark.parametrize('consumed,produced,capacity',[(0,129,128),(3,2,128),(0,0,0),(-1,0,128),(0,0,9000)])
def test_reject_lost_or_invalid_cursors(consumed,produced,capacity):
    with pytest.raises(ValueError):ring_spans(consumed,produced,capacity)
