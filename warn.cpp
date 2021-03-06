/**
 * Generated by:         ecc v0.2beta
 * Generation timestamp: Wed Feb 26 07:00:33 2014
 */
#include <string>
#include <sstream>
using namespace std;

#include "warn.h"

namespace {
    static const string notfound="";
    static const string warningcode_NoWarning = "NoWarning";
    static const string warningcode_DuplicateValue = "DuplicateValue";
    static const string warningcode_l_DuplicateValue = "Duplicate member value on #enum at line #line";
}

namespace ecc {

    const string& getstr_warningcode(warningcode v, bool longStr)
    {
        switch (v) {
            case NoWarning:
                return warningcode_NoWarning;
            case DuplicateValue:
                return (longStr)?warningcode_l_DuplicateValue:warningcode_DuplicateValue;
            default: 
                return notfound;
        }
    }
}
