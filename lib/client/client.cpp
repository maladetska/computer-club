#include "client.hpp"

namespace computer_club {
    Client::Client(const std::string& name) : name_(name) {}

    std::string Client::GetName() const {
        return name_;
    }

    bool Client::GetQueueStatus() const {
        return is_in_queue_;
    }

    void Client::SetStatusInQueue() {
        is_in_queue_ = true;
    }

    void Client::SetStatusNotInQueue() {
        is_in_queue_ = false;
    }

    TableNumber Client::GetPlace() const {
        return place_in_club_;
    }

    void Client::SetPlace(TableNumber table_num) {
        place_in_club_ = table_num;
    }

    bool Client::operator==(const Client& other) const {
        return name_ == other.name_;
    }
} // namespace computer_club
