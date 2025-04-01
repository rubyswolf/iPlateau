/**
 * @file InterpDelay2.hpp
 * @author Dale Johnson, Valley Audio Soft
 * @brief A more optimised version of the linear interpolating delay.
 */

#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include "Utilities.hpp"

template<typename T = float>
class InterpDelay {
public:
    //Initialize input and output sample values to 0
    T input = T(0);
    T output = T(0);

    //Define the interpolating delay
    InterpDelay(uint64_t maxLength = 512, uint64_t initDelayTime = 0) {
        assert(maxLength != 0); //Buffer cannot have 0 length
        bufferLength = maxLength; //buffer length int
        buffer = std::vector<T>(bufferLength, T(0)); //Create a delay buffer of length l
        setDelayTime(initDelayTime); //Initalize delay time
    }

    void process() {
        //Make sure you don't right out of bounds
        assert(bufferWritePosition >= 0);
        assert(bufferWritePosition < bufferLength);

        //write the current sample to the buffer
        buffer[bufferWritePosition] = input;

        //Set the read head position to before the write position based on the delay
        int64_t bufferReadPosition = bufferWritePosition - currentDelay;
        
        //Wrap read head around buffer
        if (bufferReadPosition < 0) {
            bufferReadPosition += bufferLength;
        }

        //Increment write head position
        ++bufferWritePosition;

        //Wrap write head around buffer
        if (bufferWritePosition == bufferLength) {
            bufferWritePosition = 0;
        }

        //The other value to interpolate with if error occurs
        int64_t upperR = bufferReadPosition - 1;

        //Wrap it around the buffer
        if (upperR < 0) {
            upperR += bufferLength;
        }

        //Validate that the read positions are inside the buffer
        assert(bufferReadPosition >= 0);
        assert(bufferReadPosition < bufferLength);
        assert(upperR >= 0);
        assert(upperR < bufferLength);

        //Output sample is calculated by interpolating between the two relevant samples
        output = linterp(buffer[bufferReadPosition], buffer[upperR], castError);
    }

    T tap(int64_t i) const {

        //i is an index within the buffer
        assert(i < bufferLength);
        assert(i >= 0);

        //j is the sample i steps from the write head
        int64_t j = bufferWritePosition - i;

        //wrap j around the buffer
        if (j < 0) {
            j += buffer.size();
        }

        //Return the sample i samples before the write head
        return buffer[j];
    }

    void setDelayTime(T newDelayTime) {

        //Validate new time
        //if (newDelayTime >= bufferLength) { //The delay time may not exceed the maximum buffer length
        //    newDelayTime = bufferLength - 1; //If it does then just max out the delay
        //}
        //if (newDelayTime < 0) { //Make sure delay time is greater than 0
        //    newDelayTime = 0;
        //}

		assert(newDelayTime >= 0);
		assert(newDelayTime < bufferLength);

        //Update delay time
        currentDelay = static_cast<int64_t>(newDelayTime);

        //Calculate the error caused by casting to discrete samples
        castError = newDelayTime - static_cast<T>(currentDelay);
    }

    void clear() {
        //Clear buffer
        std::fill(buffer.begin(), buffer.end(), T(0));

        //Reset in and out samples
        input = T(0);
        output = T(0);
    }

private:
    //Initalize private properties
    std::vector<T> buffer;
    int64_t bufferWritePosition = 0;
    int64_t currentDelay = 0;
    T castError = T(0);
    int64_t bufferLength = 512;
};

