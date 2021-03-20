#include <Move.h>

bool operator==(const Move & lhs, const Move & rhs) {
    bool comp_origin = (lhs.origin == rhs.origin);
    bool comp_dest = (lhs.destination == rhs.destination);
    return (comp_dest && comp_origin);
}