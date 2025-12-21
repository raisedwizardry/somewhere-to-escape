#include "counter.hpp"

int Counter::getIncrementedId() {
    counter++;
    return counter;
}
