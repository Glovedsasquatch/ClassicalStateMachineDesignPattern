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

    explicit ModuleProgressReport() : m_module_state(std::make_unique<Unregistered>()) , m_steps_counter(0) {}

    void module_in_progress (const Events event) {
        if (m_module_state->is_module_complete == false) {
            std::cout << "Step #" << ++m_steps_counter << ". ";
            if (auto new_module_state = m_module_state->process_event(event); new_module_state) {
                m_module_state = std::move(new_module_state);
            }
        }
        else {
            std::cout << "Module completed. No further action needed." << std::endl;
        }
    }

    template<typename... Events>
    void progress_module(Events... event) {
        { (module_in_progress(event), ...); }
    }
};

#endif //MODULEPROGRESSREPORT_H
