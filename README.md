# Understanding State Machine Design Pattern

## Introduction
A state machine design pattern is a behavioral design pattern in which the <code><b>state</b></code> of an object 
changes based on <code><b>events</b></code> triggered by internal processes.<br>
The code has the following key components:
1. An object referred to as a <code><b>machine</b></code> with different stages in its execution.
2. The <code><b>states</b></code> which the machine attains during its execution.
3. The <code><b>events</b></code> which trigger the state transitions.

## The Problem Statement - Example
Our aim is to implement a feature that maintains the exam record of a particular course of a university student. Here 
is a description of the process for the student for a single course.

### States
- There are three stages of writing an exam, namely:
    - <code><b>Unregistered</b></code>: This is initial state when a student is unregistered for a module.
    - <code><b>Registered</b></code>: Registration for a course before beginning to participate in the lectures is 
    mandatory. This is the state that is attained once the student is registered for a module. This is followed by the
    preparation for the module. 
    - <code><b>Preparation</b></code>: Participating in the lecture is treated as the preparatory phase for the 
    students attends the lectures. There are `MAX_LECTURES` number of lectures for each course, say 10 in our case.
    - <code><b>Examination</b></code>: There are `NUM_EXAM_QUESTIONS` number of question in the exam. Say, this number 
    is 7. The students must score 50% in the exams to pass it. Otherwise, the student retakes the exam, provided the
    maximum registration has not been exceeded.
    - <code><b>ModuleCompleted</b></code>: This is the final phase of the course module once it is successfully
    completed. No state transition is possible from this phase to the other states.<br>
- There are some additional rules to follow:
    - All modules that are registered must be passed. A student is automatically re-registered upon failing the 
    examination.
    - A maximum of `MAX_REGISTRATIONS` is allowed per module. No further re-registrations are allowed. For example, if 
    this number is 3, it implies 1 registration plus 2 re-registrations.

### Events
- There are five different events that trigger transition from one state to the other. These are: <br>
    - <code><b>Register</b></code>: This trigger the registration process for a module causing the `Unregistered` state 
    to transition to `Registered` state. 
    - <code><b>Prepare</b></code>: A student must begin the preparation once registered. This event triggers the state 
    transition from `Registered` to `Preparation`. Preparation is necessary to appear for the exam. The student should 
    have completed 80% of the `MAX_LECTURES` to appear for the examination.
    - <code><b>WriteExam</b></code>: Once the student is done with attending the lectures, the student is ready to take 
    the examination. This event triggers transition from `Preparation` to `Examination`.
    - <code><b>ResultPass</b></code>: If the examination leads to a success, then this event triggers the transition
    from `Examination` to `ModuleCompleted`. To succeed in an examination, a minimum of 50% must be secured. For
    example, in an examination with (`NUM_EXAM_QUESTIONS = `) 7 questions, at least 4 must be correct. 
    - <code><b>ResultFail</b></code>: In case the student fails the examination, this event transitions the student to 
    either `Registered` state if re-registration is still possible (based on `MAX_REGISTRATIONS`) and the process 
    repeats, or to `ModuleFailed` if no more re-registrations are allowed.

