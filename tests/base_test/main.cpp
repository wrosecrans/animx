#include "animx.h"

#include <vector>
#include <iostream>

using adsk::Keyframe;
using adsk::InfinityType;

class Curve : public adsk::ICurve {
public:
    Curve(std::vector<Keyframe> source) {
        if (source.size() < 2) {
            throw std::logic_error("This class either needs more keyframes, or better edge case handling.");
        }
        keyframes = source;
    }

    virtual bool keyframeAtIndex(int index, Keyframe &key) const override {
        if(index < 0 || index >= keyframes.size()) {
            return false;
        }
        key = keyframes[index];
        return true;
    }

    /*!
        Returns closest key at or after the specified time, or the last key if time is
        beyond the end of the curve.
    */

    virtual bool keyframe(double time, Keyframe &key) const override {
        key = keyframes[0];
        for (auto &candidate : keyframes) {
            if(candidate.time >= time) {
                key = candidate;
                return true;
            }
            key = candidate;
        }
        return false;
    }
    virtual bool first(Keyframe &key) const override {
        key = keyframes[0];
        return true;
    }
    virtual bool last(Keyframe &key) const override {
        key = keyframes.back();
        return true;
    }
    virtual InfinityType preInfinityType() const override {
        return InfinityType::Constant;
    }
    virtual InfinityType postInfinityType() const override {
        return InfinityType::Constant;
    }
    virtual bool isWeighted() const override {
        return false;
    }
    virtual unsigned int keyframeCount() const override {
        return keyframes.size();
    }
    virtual bool isStatic() const override {
        return false;
    }

    std::vector<Keyframe> keyframes;
};


Keyframe make_keyframe(double time=0, double value=0, int idx = 0) {
    Keyframe k;
    k.time = time;
    k.value = value;
    k.index = idx;
    k.linearInterpolation = true;
    k.quaternionW = 0;
    adsk::Tangent In;
    In.type = adsk::TangentType::Auto;
    In.x = -1;  In.y = 0;
    k.tanIn = In;
    In.x = -1;  In.y = 0;
    k.tanOut = In;

    return k;
}

int main() {
    std::vector<Keyframe> keyframes;
    keyframes.push_back(make_keyframe(0,0,0));
    keyframes.push_back(make_keyframe(50,-10,1));
    keyframes.push_back(make_keyframe(100,100,2));


    Curve c(keyframes);
    for (int i = -10; i < 120; i+= 5) {
        auto result = adsk::evaluateCurve(i, c);
        std::cout << i << " : " << result << std::endl;
    }
    // std::cout << "Half way between 0 and 100 is about " << halfway << std::endl;

    return 0;
}
