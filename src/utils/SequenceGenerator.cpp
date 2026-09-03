#include "SequenceGenerator.h"

#include <Arduino.h>

void SequenceGenerator::generate(
    int sequence[],
    int length,
    int maxValue
) {
    for (int i = 0; i < length; ++i) {
        sequence[i] = random(0, maxValue);
    }
}