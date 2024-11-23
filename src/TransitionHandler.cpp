// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.
//

# include <iostream>
# include "States/States.h"
# include "Events/Events.h"

std::unique_ptr<State> Unregistered::process_event(const Events event) {
    if (event == Register) {
        std::cout << "Want to register? -> " << event << std::endl;
        return std::make_unique<Registered>();
    }
    else if (event == WriteExam) {
        std::cout << "You are still unregistered! Sorry, you cannot take the exam!" << std::endl;
        return nullptr;
    }

    std::cout << "You are still unregistered! " << std::endl;
    return nullptr;
}

std::unique_ptr<State> Registered::process_event(const Events event) {
    if (event == Prepare) {
        std::cout << "Ready to take up lectures? -> " << event << std::endl;
        return std::make_unique<Preparation>();
    }
    if (event == WriteExam) {
        std::cout << "You are registered but not prepared. Sorry, you cannot take the exam!" << std::endl;
        return nullptr;
    }

    std::cout << "You are registered but not preparing! Everything okay?" << std::endl;
    return nullptr;
}

std::unique_ptr<State> Preparation::process_event(const Events event) {
    if (event == WriteExam) {
        std::cout << "Done with preparations! -> " << event << std::endl;
        return std::make_unique<Examination>();
    }

    std::cout << "Still preparing? -> " << event << std::endl;
    return nullptr;
}

std::unique_ptr<State> Examination::process_event(const Events event) {
    if (event == ResultFail) {
        std::cout << "Awaiting results? Final results out -> " << event << std::endl;
        return std::make_unique<Registered>();
    }
    else if (event == ResultPass) {
        std::cout << "Awaiting results? Final results out -> " << event << std::endl;
        return std::make_unique<ModuleCompleted>();
    }

    std::cout << "Examinations still under progress! " << std::endl;
    return nullptr;
}

std::unique_ptr<State> ModuleCompleted::process_event(const Events event) {
    return std::make_unique<ModuleCompleted>();
}
