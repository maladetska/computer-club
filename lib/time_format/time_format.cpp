#include "time_format.hpp"

namespace computer_club {
    TimeFormat::TimeFormat(const std::optional<std::string>& input_time)
        : time_str_(input_time) {
        if (!input_time.has_value()) {
            ParseTimePoint();
        }
    }

    TimeFormat::TimeFormat(tm* time) {
        hours_ = time->tm_hour;
        minutes_ = time->tm_min;
        time_str_ = TimeToString();
        time_point_ = std::chrono::system_clock::from_time_t(mktime(time));
    }

    unsigned TimeFormat::GetHoursNumber() const {
        return hours_;
    }

    unsigned TimeFormat::GetMinutesNumber() const {
        return minutes_;
    }

    bool TimeFormat::operator<(const TimeFormat& other) const {
        return time_point_ < other.time_point_;
    }

    bool TimeFormat::operator==(const TimeFormat& other) const {
        return time_point_ == other.time_point_;
    }

    TimeFormat TimeFormat::operator-(const TimeFormat& other) const {
        time_t now = time(nullptr);
        tm*    diff_time = localtime(&now);

        diff_time->tm_min = minutes_ < other.minutes_
                                    ? 60 - other.minutes_ + minutes_
                                    : minutes_ - other.minutes_;
        diff_time->tm_hour = hours_ - other.hours_;
        diff_time->tm_hour -= minutes_ < other.minutes_ ? 1 : 0;

        return TimeFormat(diff_time);
    }


    TimeFormat TimeFormat::operator+(const TimeFormat& other) const {
        if (!time_str_.has_value()) {
            return other;
        }

        time_t now = time(nullptr);
        tm*    sum_time = localtime(&now);

        sum_time->tm_min = minutes_ + other.minutes_;
        sum_time->tm_hour = hours_ + other.hours_;
        sum_time->tm_hour += sum_time->tm_min >= 60 ? 1 : 0;
        sum_time->tm_min -= sum_time->tm_min >= 60 ? 60 : 0;

        return TimeFormat(sum_time);
    }

    TimeFormat& TimeFormat::operator+=(const TimeFormat& other) {
        *this = *this + other;
        return *this;
    }

    std::istringstream& operator>>(std::istringstream& is, TimeFormat& t) {
        std::string time_str;
        is >> time_str;
        t.time_str_ = time_str;
        t.ParseTimePoint();

        return is;
    }

    std::fstream& operator>>(std::fstream& fs, TimeFormat& t) {
        std::string time_str;
        fs >> time_str;
        t.time_str_ = time_str;
        t.ParseTimePoint();

        return fs;
    }

    std::ostream& operator<<(std::ostream& os, const TimeFormat& t) {
        if (t.time_str_.has_value()) {
            os << t.time_str_.value();
        } else {
            os << t.TimeToString();
        }

        return os;
    }

    void TimeFormat::ParseTimePoint() {
        time_t now = time(nullptr);
        tm*    time = localtime(&now);
        time->tm_sec = 0;

        std::istringstream ss(time_str_.value());
        ss >> std::get_time(time, kTimeFormat);
        minutes_ = time->tm_min;
        hours_ = time->tm_hour;
        if (!ss.fail() && ss.eof()) {
            time_point_ = std::chrono::system_clock::from_time_t(mktime(time));
        }
    }

    std::string TimeFormat::TimeToString() const {
        return (hours_ > 9 ? std::to_string(hours_) : ("0" + std::to_string(hours_))) + ':' +
               (minutes_ > 9 ? std::to_string(minutes_) : ("0" + std::to_string(minutes_)));
    }
} // namespace computer_club
