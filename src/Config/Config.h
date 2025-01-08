// Copyright (c) 2024. Prabha Shankar.
// All rights reserved.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <optional>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

struct ModuleParameters {
    std::optional<std::uint16_t> max_module_registrations;
    std::optional<std::uint16_t> max_module_num_lectures;
    std::optional<std::uint16_t> min_percentage_attendance_criteria;
    std::optional<std::uint16_t> min_questions_per_exam;
    std::optional<std::uint16_t> max_questions_per_exam;
    std::optional<std::uint16_t> min_pass_percentage;
};

struct StudentPerformanceStats {
    std::optional<double> probability_of_attendance;
    std::optional<double> probability_of_correct_response;
};

class Config {
public:
    explicit Config(const std::string& config_file) {
        m_config_path_.assign(config_file);

        if (!std::filesystem::exists(m_config_path_.filename()) ||
                !std::filesystem::is_regular_file(m_config_path_.filename())) {
            throw std::runtime_error("File does not exist or is not a regular file: " + m_config_path_.string());
        }

        if (std::ifstream config_file_stream(m_config_path_.filename()); !config_file_stream.is_open()) {
            throw std::runtime_error("Could not open config file: " + m_config_path_.string());
        }
        else {
            std::cout << "Config file loaded successfully: " << m_config_path_.filename() << std::endl << std::endl;
            config_file_stream.close();
        }

        setParameters();
    }

    [[nodiscard]] ModuleParameters getModuleParameters() const { return m_module_params_; }

    [[nodiscard]] StudentPerformanceStats getStudentPerformanceStats() const { return m_student_performance_stats_; }

    ~Config() = default;

private:
    void setParameters() {
        std::ifstream file(m_config_path_.filename());
        nlohmann::json input_file = nlohmann::json::parse(file);

        if (input_file.contains("ModuleParams")) {
            const auto& module_parameters = input_file["ModuleParameters"];

            if (module_parameters.contains("max_permissible_registration")) {
                m_module_params_.max_module_registrations
                    = module_parameters["max_permissible_registration"].get<std::uint16_t>();
            }
            else m_module_params_.max_module_registrations = 3;

            if (module_parameters.contains("max_module_lecture_per_preparation")) {
                m_module_params_.max_module_num_lectures
                    = module_parameters["max_module_lecture_per_preparation"].get<std::uint16_t>();
            }
            else m_module_params_.max_module_num_lectures = 10;

            if (module_parameters.contains("min_attendance_percentage_to_attend_exam")) {
                m_module_params_.min_percentage_attendance_criteria
                    = module_parameters["min_attendance_percentage_to_attend_exam"].get<std::uint16_t>();
            }
            else m_module_params_.min_percentage_attendance_criteria = 75;

            if (module_parameters.contains("min_examination_questions")) {
                m_module_params_.min_questions_per_exam
                    = module_parameters["min_examination_questions"].get<std::uint16_t>();
            }
            else m_module_params_.min_questions_per_exam = 10;

            if (module_parameters.contains("max_examination_questions")) {
                m_module_params_.max_questions_per_exam
                    = module_parameters["max_examination_questions"].get<std::uint16_t>();
            }
            else m_module_params_.min_questions_per_exam = 15;

            if (module_parameters.contains("max_examination_questions")) {
                m_module_params_.min_pass_percentage
                    = module_parameters["max_examination_questions"].get<std::uint16_t>();
            }
            else m_module_params_.min_pass_percentage = 50;
        }

        if (input_file.contains("StudentPerformanceStats")) {
            const auto& perf_stats_parameters = input_file["StudentPerformanceStats"];

            if (perf_stats_parameters.contains("probability_a_lecture_is_attended")) {
                m_student_performance_stats_.probability_of_attendance
                    = perf_stats_parameters["probability_a_lecture_is_attended"].get<double>();
            }
            else m_student_performance_stats_.probability_of_attendance = 0.8;

            if (perf_stats_parameters.contains("probability_in_favor_of_correct_response")) {
                m_student_performance_stats_.probability_of_correct_response
                    = perf_stats_parameters["probability_in_favor_of_correct_response"].get<double>();
            }
            else m_student_performance_stats_.probability_of_correct_response = 0.6;
        }
    }

    ModuleParameters m_module_params_;
    StudentPerformanceStats m_student_performance_stats_;
    std::filesystem::path m_config_path_;
};

#endif //CONFIG_H