#include "place.hpp"

namespace computer_club {
    Place::Place(TableNumber place_number,
                 CostSize    cost_per_hour) : number_(place_number),
                                           cost_per_hour_(cost_per_hour) {}

    void Place::MakePlaceOccupiedAt(const TimeFormat& new_time) {
        is_occupied_ = true;
        UpdateHoldingTime(new_time);
    }

    bool Place::IsPlaceOccupied() const {
        return is_occupied_;
    }

    void Place::UpdateHoldingTime(const TimeFormat& new_time) {
        if (session_start_time_ == TimeFormat{}) {
            session_start_time_ = new_time;
            return;
        }
        auto diff_time = new_time - session_start_time_;
        revenue_ += diff_time.GetMinutesNumber() > 0
                            ? cost_per_hour_ * (diff_time.GetHoursNumber() + 1)
                            : cost_per_hour_ * diff_time.GetHoursNumber();
        holding_time_ += diff_time;
        session_start_time_ = new_time;
    }

    std::ostream& operator<<(std::ostream& os, const Place& p) {
        os << p.number_ + 1 << ' '
           << p.revenue_ << ' '
           << p.holding_time_;

        return os;
    }
} // namespace computer_club
