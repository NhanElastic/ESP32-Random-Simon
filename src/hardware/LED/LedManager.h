#pragma once

class LedManager {
    public:
        void begin();

        void turnOn(int index);
        void turnOff(int index);
        void turnOffAll();
};