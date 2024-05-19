#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

namespace computer_club {
    class TimeFormat {
    public:
        TimeFormat() = default;
        explicit TimeFormat(const std::optional<std::string>& input_time);
        explicit TimeFormat(tm* time);

        [[nodiscard]] unsigned GetHoursNumber() const;
        [[nodiscard]] unsigned GetMinutesNumber() const;

        bool operator<(const TimeFormat& other) const;
        bool operator==(const TimeFormat& other) const;

        TimeFormat  operator-(const TimeFormat& other) const;
        TimeFormat  operator+(const TimeFormat& other) const;
        TimeFormat& operator+=(const TimeFormat& other);

        friend std::istringstream& operator>>(std::istringstream& is, TimeFormat&);
        friend std::fstream&       operator>>(std::fstream& fs, TimeFormat&);
        friend std::ostream&       operator<<(std::ostream& os, const TimeFormat&);

    private:
        void ParseTimePoint();

        [[nodiscard]] std::string TimeToString() const;

        std::optional<std::string>                         time_str_ = std::nullopt;
        std::chrono::time_point<std::chrono::system_clock> time_point_{};

        unsigned hours_ = 0;
        unsigned minutes_ = 0;

        const char* kTimeFormat = "%H:%M";
    };
} // namespace computer_club
