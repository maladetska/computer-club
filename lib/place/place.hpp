#pragma once

#include "../time_format/time_format.hpp"

namespace computer_club {
    using CostSize = uint64_t;
    using TableNumber = uint64_t;

    struct Place {
    public:
        Place() = default;
        explicit Place(TableNumber place_number, CostSize cost_per_hour);

        [[nodiscard]] bool IsPlaceOccupied() const;

        void MakePlaceOccupiedAt(const TimeFormat&);
        void UpdateHoldingTime(const TimeFormat&);

        friend std::ostream& operator<<(std::ostream& os, const Place& p);

    private:
        TableNumber number_{};

        bool is_occupied_ = false;

        CostSize cost_per_hour_{};
        CostSize revenue_ = 0;

        TimeFormat holding_time_{};
        TimeFormat session_start_time_{};
    };
} // namespace computer_club
