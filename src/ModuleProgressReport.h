// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.
//

#ifndef MODULEPROGRESSREPORT_H
#define MODULEPROGRESSREPORT_H

#include <iostream>

#include "States.h"

struct ModuleProgressReport {
    std::unique_ptr<State> m_module_state;
    std::uint32_t m_steps_counter;

    explicit ModuleProgressReport()
        : m_module_state(std::make_unique<Unregistered>())
        , m_steps_counter(0) {}

    void begin_module_activity() {
        while (State::num_registrations <= m_module_state->m_MAX_REGISTRATIONS) {
            if (!m_module_state->is_module_complete) {
                if (auto new_module_state = m_module_state->perform_state_activity(); new_module_state)
                    m_module_state = std::move(new_module_state);
            }
            else {
                std::cout << "Module completed. No further action needed!" << std::endl;
                return;
            }
        }

        // This code handles the state where re-registration is not possible and the module is incomplete
        if (!m_module_state->is_module_complete && State::num_registrations > m_module_state->m_MAX_REGISTRATIONS) {
            std::cout   << "You cannot re-register to this module more than "
                        << m_module_state->m_MAX_REGISTRATIONS << " times.\n"
                        << "Sorry, you have failed the module with no possibility for re-registration!" << std::endl;
        }
    }
};

#endif //MODULEPROGRESSREPORT_H
