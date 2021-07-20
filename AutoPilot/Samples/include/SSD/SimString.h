#pragma once

#include "ssdexport.h"
#include "SimVector.h"

#define SIMSTRING_SIZE 16

namespace SSD {

    class SSDEXPORT SimString
    {
    public:
        //@brief constructor.
        //@param s is input content value to initialize this string.
        SimString(const char* s = nullptr);

        //@brief destructor.
        ~SimString();

        //@brief copy constructor.
        SimString(const SimString& c);

        //@brief assignment.
        SimString& operator=(const SimString& c);

        //@brief Get const char* value of current string.
        const char* GetString() const;

        //@brief Set content value for current string.
        void SetString(const char* s);

        bool operator== (const SimString & str) const;
        bool operator!= (const SimString & str) const;
        bool operator< (const SimString & str) const;
        bool operator> (const SimString & str) const;
        bool Empty() const;
		sizeT Length() const;

    private:
        char data[SIMSTRING_SIZE];
    };

    template class SSDEXPORT SSD::SimVector<SimString>;
    typedef SSD::SimVector<SimString> SimStringVector;
}

