// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.
//

# include <iostream>
# include "States/States.h"
# include "Events/Events.h"

std::uint32_t State::num_registrations = 0;

void Unregistered::process_event(const Events event) {
    if (event == Register) {
        std::cout << "\tRegistration under process -> " << event << std::endl;
        m_next_state = std::make_unique<Registered>();
        return;
    }

    std::cout << "\tModule still unregistered!" << std::endl;
    m_next_state = std::make_unique<Unregistered>();
}

void Registered::process_event(const Events event) {
    if (event == Prepare) {
        std::cout << "Ready to take up lectures? -> " << event << std::endl;
        m_next_state = std::make_unique<Preparation>();
        return;
    }

    std::cout << "Registered but not preparing! " << std::endl;
    m_next_state = std::make_unique<Registered>();
}

void Preparation::process_event(const Events event) {
    if (event == WriteExam) {
        std::cout << "Done with preparations! -> " << event << std::endl;
        m_next_state = std::make_unique<Examination>();
        return;
    }

    std::cout << "Need more preparation ... Not writing exams! " << std::endl;
    m_next_state = std::make_unique<Preparation>();
}

void Examination::process_event(const Events event) {
    if (event == ResultFail) {
        std::cout << "Awaiting results? Final results out -> " << event << std::endl;
        m_next_state = std::make_unique<Registered>();
        return;
    }
    else if (event == ResultPass) {
        std::cout << "Awaiting results? Final results out -> " << event << std::endl;
        m_next_state = std::make_unique<ModuleCompleted>();
    }
}

void ModuleCompleted::process_event(const Events event) {
    m_next_state = std::make_unique<ModuleCompleted>();
}
