#pragma once

#include "../place/place.hpp"

namespace computer_club {
    class Client {
    public:
        Client() = default;
        explicit Client(const std::string& name);

        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] TableNumber GetPlace() const;
        [[nodiscard]] bool        GetQueueStatus() const;

        void SetStatusInQueue();
        void SetStatusNotInQueue();

        void SetPlace(TableNumber);

        bool operator==(const Client& other) const;

    private:
        std::string name_;
        TableNumber place_in_club_{};
        bool        is_in_queue_ = false;
    };
} // namespace computer_club
