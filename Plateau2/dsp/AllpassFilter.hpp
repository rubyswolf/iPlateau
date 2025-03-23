/**
 * @file AllpassFilter.hpp
 * @author Dale Johnson
 * @date ...uhhh
 */

#pragma once
#include "InterpDelay.hpp"
#include <cassert>

template<class T>
class AllpassFilter {
public:
    AllpassFilter() {
        gain1 = 0;
        gain2 = 0;
        decay1 = 0;
        decay2 = 0;
        clear();
    }

    AllpassFilter(long maxDelay, long initDelay1 = 0, T initGain1 = 0, long initDelay2 = 0, T initGain2 = 0) {
        delay1 = InterpDelay<T>(maxDelay, initDelay1);
        delay2 = InterpDelay<T>(maxDelay, initDelay2);
        gain1 = initGain1;
        gain2 = initGain2;
        decay1 = 0.8;
        decay2 = 0.8;
        clear();
    }

    T inline process() {
        if (nested) {
            _inSum1 = input + delay1.output * gain1;
            _inSum2 = _inSum1 + delay2.output * gain2;
            delay2.input = _inSum2;
            delay1.input = delay2.output * decay2 - _inSum2 * gain2;
            output = delay1.output * decay1 - _inSum1 * gain1;
            delay1.process();
            delay2.process();
            return output;
        }
        else {
            //Note that negative gain does something

            //Feedback into delay buffer based on gain
            _inSum1 = input + delay1.output * gain1;

            //output is the delay output subtract the feedback input
            output = delay1.output - _inSum1 * gain1;

            //feed the next sample into the delay
            delay1.input = _inSum1;

            //proccess the delay sample
            delay1.process();

            return output;
        }
    }

    void setGain(const T newGain1, const T newGain2) {
        assert(newGain1 >= -1.0);
        assert(newGain1 <= 1.0);
        assert(newGain2 >= -1.0);
        assert(newGain2 <= 1.0);

        gain1 = newGain1;
        gain2 = newGain1;
    }

	void setDecay(const T newDecay1, const T newDecay2) {
		assert(newDecay1 >= 0.0);
		//assert(newDecay1 <= 1.0);
		assert(newDecay2 >= 0.0);
		//assert(newDecay2 <= 1.0);
		decay1 = newDecay1;
		decay2 = newDecay2;
	}

    void clear() {
        input = 0;
        output = 0;

        _inSum1 = 0;
        _inSum2 = 0;

        delay1.clear();
        delay2.clear();
    }

    //IO
    T input;
    T output;

    //2 gains
    T gain1, gain2;

    //2 decays
    T decay1, decay2;

    //2 delays
    InterpDelay<T> delay1, delay2;

    bool nested = false;
private:
    T _inSum1, _inSum2;
};
