// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.
//

#ifndef EVENTS_H
#define EVENTS_H

#include <ostream>

enum Events { Register, Prepare, WriteExam, ResultPass, ResultFail };

inline std::ostream &operator<<(std::ostream& os, Events event) {
    switch (event) {
        case Register: os << "Registered for the module "; break;
        case Prepare: os << "Preparation under process "; break;
        case WriteExam: os << "Examination under process " ; break;
        case ResultPass: os << "Congratulations! You passed the module. "; break;
        case ResultFail: os << "Sorry! You need to retake the module."; break;
    }
    return os;
}

#endif //EVENTS_H
