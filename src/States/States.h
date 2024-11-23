// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.

#ifndef STATES_H
#define STATES_H

#include <memory>
#include "Events.h"


struct State {
  bool is_module_complete;

  explicit State(const bool flag = false) : is_module_complete(flag) {}
  virtual std::unique_ptr<State> process_event(Events event) = 0;

  virtual ~State() = default;
};

struct Unregistered final : State {
  std::unique_ptr<State> process_event(Events event) override;
};

struct Registered final : State {
  std::unique_ptr<State> process_event(Events event) override ;
};

struct Preparation final : State {
  std::unique_ptr<State> process_event(Events event) override;
};

struct Examination final : State {
  std::unique_ptr<State> process_event(Events event) override;
};

struct ModuleCompleted final : State {
  ModuleCompleted() : State(true) {}
  std::unique_ptr<State> process_event(Events event) override;
};

#endif //STATES_H
