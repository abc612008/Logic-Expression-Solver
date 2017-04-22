#pragma once
#include <ostream>

enum class Logic
{
    Unknown, True, False
};

inline Logic operator && (Logic lhs, Logic rhs)
{
    if (lhs == Logic::True && rhs == Logic::True) return Logic::True;
    if (lhs == Logic::False || rhs == Logic::False)return Logic::False;
    return Logic::Unknown;
}

inline Logic operator || (Logic lhs, Logic rhs)
{
    if (lhs == Logic::True || rhs == Logic::True) return Logic::True;
    if (lhs == Logic::False && rhs == Logic::False) return Logic::False;
    return Logic::Unknown;
}

inline Logic operator ! (Logic logic)
{
    if (logic == Logic::True) return Logic::False;
    if (logic == Logic::False) return Logic::True;
    return Logic::Unknown;
}

