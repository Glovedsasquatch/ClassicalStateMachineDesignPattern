// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.

#ifndef STATES_H
#define STATES_H

#include <memory>
#include <random>
#include "Events.h"


struct State {
  bool is_module_complete;
  std::uint32_t m_num_lectures_attended;
  static std::uint32_t num_registrations;
  std::unique_ptr<State> m_next_state;

  const std::uint32_t m_MAX_REGISTRATIONS = 3;
  const uint32_t m_MAX_LECTURES = 10;
  const uint32_t m_MAX_EXAMINATION_QUESTIONS = 15;
  const std::uint32_t m_MIN_PERCENT_FOR_PASS = 50;

  explicit State(const bool flag = false)
    : is_module_complete(flag)
    , m_num_lectures_attended(0)
    , m_next_state(nullptr)
  {}
  virtual void process_event(Events event) = 0;
  virtual std::unique_ptr<State> perform_state_activity() = 0;

  virtual ~State() = default;
};


struct Unregistered final : State {
  explicit Unregistered() {
    std::cout << "\t Creating Unregistered" << std::endl;
  }

  void process_event(Events event) override;

  std::unique_ptr<State> perform_state_activity() override {
    if (State::num_registrations <= m_MAX_REGISTRATIONS) {
      std::cout << "Proceeding to registration work ..." << std::endl;
      process_event(Register);
      return std::move(m_next_state);
    }

    std::cout << "No further re-registrations allowed!" << std::endl;
    return std::move(m_next_state);
  }
};


struct Registered final : State {
  explicit Registered() {
    num_registrations++;
    std::cout << "\t Creating Registered" << std::endl;
  }

  void process_event(Events event) override ;

  std::unique_ptr<State> perform_state_activity() override {
    /*std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>    distr(0, 10);
    while (distr(generator) >= 2) {
      std::cout << "\tAwaiting to proceed to preparatory phase!" << std::endl;
    }*/

    process_event(Prepare);
    return std::move(m_next_state);
  }
};

struct Preparation final : State {
  explicit Preparation() {
    std::cout << "\t Creating Preparation" << std::endl;
  }

  void process_event(Events event) override;

  std::unique_ptr<State> perform_state_activity() override {
    while (++m_num_lectures_attended <= m_MAX_LECTURES) {
      std::cout << "\t Attending lecture " << m_num_lectures_attended << "/" << m_MAX_LECTURES << std::endl;
    }

    process_event(WriteExam);
    return std::move(m_next_state);
  }
};

struct Examination final : State {
  explicit Examination() {
    std::cout << "\t Creating Examination" << std::endl;
  }

  void process_event(Events event) override;

  std::unique_ptr<State> perform_state_activity() override {
    int counter = 0;
    int correct_response = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>    distr(0, 10);
    while (++counter <= m_MAX_EXAMINATION_QUESTIONS) {
      std::cout << "\tResponse to question " << counter << "/" << m_MAX_EXAMINATION_QUESTIONS;
      if (distr(generator) > 6) {
        correct_response++;
        std::cout << " is correct!" << std::endl;
      }
      else {
        std::cout << " is not correct!" << std::endl;
      }
    }
    if ((correct_response*100 / m_MAX_EXAMINATION_QUESTIONS) >= m_MIN_PERCENT_FOR_PASS) {
      process_event(ResultPass);
    }
    else {
      process_event(ResultFail);
    }

    return std::move(m_next_state);
  }
};

struct ModuleCompleted final : State {
  ModuleCompleted() : State(true) {
    std::cout << "Creating ModuleCompleted!" << std::endl;
  }

  void process_event(Events event) override;

  std::unique_ptr<State> perform_state_activity() override {
    process_event(ResultPass);
    return std::move(m_next_state);
  }
};

#endif //STATES_H
