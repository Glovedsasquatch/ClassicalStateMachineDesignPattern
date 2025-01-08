// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.

#ifndef STATES_H
#define STATES_H

#include <memory>
#include <random>
#include "Events.h"
#include "Config.h"

struct State {
  bool is_module_complete;
  std::uint32_t m_num_lectures_attended;
  static std::uint32_t num_registrations;
  std::unique_ptr<State> m_next_state;

  const ModuleParameters& m_module_params;
  const StudentPerformanceStats& m_stud_perf_stats;

  explicit State( const ModuleParameters& module_parameters,
                  const StudentPerformanceStats& stud_perf_stats,
                  const bool flag = false)
    : is_module_complete(flag)
    , m_num_lectures_attended(0)
    , m_next_state(nullptr)
    , m_module_params(module_parameters)
    , m_stud_perf_stats(stud_perf_stats) {}

  virtual void process_event(Events event,
                             const ModuleParameters &module_params,
                             const StudentPerformanceStats &stud_perf_stats) = 0;
  virtual std::unique_ptr<State> perform_state_activity() = 0;

  virtual ~State() = default;
};


struct Unregistered final : State {
  explicit Unregistered(const ModuleParameters& module_parameters, const StudentPerformanceStats& stud_perf_stats)
    : State(module_parameters, stud_perf_stats) {
    std::cout << "\t Creating Unregistered" << std::endl;
  }

  void process_event(
    Events event, const ModuleParameters &module_params, const StudentPerformanceStats &stud_perf_stats) override;

  std::unique_ptr<State> perform_state_activity() override {
    if (State::num_registrations <= m_module_params.max_module_registrations.value()) {
      std::cout << "Proceeding to registration work ..." << std::endl;
      process_event(Register, m_module_params, m_stud_perf_stats);
      return std::move(m_next_state);
    }

    std::cout << "No further re-registrations allowed!" << std::endl;
    return std::move(m_next_state);
  }
};


struct Registered final : State {
  explicit Registered(
    const ModuleParameters& module_parameters, const StudentPerformanceStats& stud_perf_stats)
    : State(module_parameters, stud_perf_stats) {
    num_registrations++;
    std::cout << "\t Creating Registered" << std::endl;
  }

  void process_event(
    Events event, const ModuleParameters &module_params, const StudentPerformanceStats &stud_perf_stats) override ;

  std::unique_ptr<State> perform_state_activity() override {
    /*std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>    distr(0, 10);
    while (distr(generator) >= 2) {
      std::cout << "\tAwaiting to proceed to preparatory phase!" << std::endl;
    }*/

    process_event(Prepare, m_module_params, m_stud_perf_stats);
    return std::move(m_next_state);
  }
};

struct Preparation final : State {
  explicit Preparation(const ModuleParameters& module_parameters, const StudentPerformanceStats& stud_perf_stats)
    : State(module_parameters, stud_perf_stats) {
    std::cout << "\t Creating Preparation" << std::endl;
  }

  void process_event(
    Events event, const ModuleParameters &module_params, const StudentPerformanceStats &stud_perf_stats) override;

  std::unique_ptr<State> perform_state_activity() override {
    while (++m_num_lectures_attended <= m_module_params.max_module_num_lectures.value()) {
      std::cout << "\t Attending lecture " << m_num_lectures_attended
                << "/" << m_module_params.max_module_num_lectures.value() << std::endl;
    }

    process_event(WriteExam, m_module_params, m_stud_perf_stats);
    return std::move(m_next_state);
  }
};

struct Examination final : State {
  explicit Examination(const ModuleParameters& module_parameters, const StudentPerformanceStats& stud_perf_stats)
    : State(module_parameters, stud_perf_stats) {
    std::cout << "\t Creating Examination" << std::endl;
  }

  void process_event(
    Events event, const ModuleParameters &module_params, const StudentPerformanceStats &stud_perf_stats) override;

  std::unique_ptr<State> perform_state_activity() override {
    int counter = 0;
    int correct_response = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>    distr(0, 10);
    while (++counter <= m_module_params.max_questions_per_exam.value()) {
      std::cout << "\tResponse to question " << counter << "/" << m_module_params.max_questions_per_exam.value();
      if (distr(generator) > static_cast<int>((1.0 - m_stud_perf_stats.probability_of_correct_response.value()) * 10)) {
        correct_response++;
        std::cout << " is correct!" << std::endl;
      }
      else {
        std::cout << " is not correct!" << std::endl;
      }
    }
    if ((correct_response*100 / m_module_params.max_questions_per_exam.value())
          >= m_module_params.min_pass_percentage.value()) {
      process_event(ResultPass, m_module_params, m_stud_perf_stats);
    }
    else {
      process_event(ResultFail, m_module_params, m_stud_perf_stats);
    }

    return std::move(m_next_state);
  }
};

struct ModuleCompleted final : State {
  explicit ModuleCompleted(const ModuleParameters& module_parameters, const StudentPerformanceStats& stud_perf_stats)
    : State(module_parameters, stud_perf_stats, true) {
    std::cout << "Creating ModuleCompleted!" << std::endl;
  }

  void process_event(Events event, const ModuleParameters &module_params, const StudentPerformanceStats &stud_perf_stats) override;

  std::unique_ptr<State> perform_state_activity() override {
    process_event(ResultPass, m_module_params, m_stud_perf_stats);
    return std::move(m_next_state);
  }
};

#endif //STATES_H
