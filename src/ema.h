#pragma once

class EMA {
    public:
        EMA(float a): alpha(a) {}
        float add(float v) {
            value = alpha * v + (1.f - alpha) * value;
            return value;
        }
        float get() { return value; }
    private:
        float alpha = 0.f;
        float value = 0.f;
};
