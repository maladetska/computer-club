#include "computer_club.hpp"

namespace computer_club {
    ComputerClub::ComputerClub(std::filesystem::path& path) : input_path_(path) {
        stream_from_.open(input_path_);

        stream_from_ >> table_number_;

        stream_from_ >> opening_time_;
        stream_from_ >> closing_time_;

        CostSize cost_per_hour;
        stream_from_ >> cost_per_hour;

        for (TableNumber i = 0; i < table_number_; ++i) {
            tables_[i] = Place(i, cost_per_hour);
        }
    }

    void ComputerClub::LaunchApp() {
        std::cout << opening_time_ << std::endl;

        ReadEvents();
        stream_from_.close();

        ClubClosing();
        std::cout << closing_time_ << std::endl;
        PrintPlacesResult();
    }

    void ComputerClub::ReadEvents() {
        while (stream_from_) {
            Event event;
            stream_from_ >> event;
            if (!event.body_.empty()) {
                std::cout << event << std::endl;
                EventHandler(event);
            }
        }
    }

    void ComputerClub::EventHandler(Event& event) {
        std::string client_name = event.body_[0];

        try {
            switch (event.id_) {
                case Event::StatusId::kClientHasCome:
                    ClientHasCome(event.time_, client_name);
                    break;
                case Event::StatusId::kClientHasSatDownAtTable:
                    ClientHasSatDownAtTable(event.time_,
                                            client_name, std::stoi(event.body_[1]) - 1);
                    break;
                case Event::StatusId::kClientIsWaiting:
                    ClientIsWaiting(event.time_, client_name);
                    break;
                case Event::StatusId::kClientHasLeftBeforeClosingTime:
                    ClientHasLeftBeforeClosingTime(event.time_, client_name);
                    break;
                default:
                    throw WrongEventIdException();
                    break;
            }
        } catch (const std::exception& e) {
            Event error_event = Event(event.time_, Event::StatusId::kError, {e.what()});
            std::cout << error_event << std::endl;
        }
    }

    void ComputerClub::ClubClosing() {
        std::map<std::string, Client> remaining_clients;
        for (auto [name, client]: clients_) {
            remaining_clients.insert({name, client});
        }
        clients_.clear();
        for (auto& [name, client]: remaining_clients) {
            ClientHasLeftAfterClosingTime(closing_time_, client);
        }
    }

    void ComputerClub::PrintPlacesResult() {
        for (TableNumber i = 0; i < table_number_; ++i) {
            std::cout << tables_[i] << std::endl;
        }
    }

    bool ComputerClub::IsClientInClubByName(const std::string& client_name) {
        return clients_.contains(client_name);
    }

    void ComputerClub::ClientHasCome(const TimeFormat&  event_time,
                                     const std::string& client_name) {
        if (event_time < opening_time_) {
            throw NotOpenYetException();
        }
        if (IsClientInClubByName(client_name)) {
            throw YouShallNotPassException();
        }
        clients_.insert({client_name, Client(client_name)});
    }

    void ComputerClub::ClientHasSatDownAtTable(const TimeFormat&  event_time,
                                               const std::string& client_name,
                                               TableNumber        curr_table_number) {
        if (!IsClientInClubByName(client_name)) {
            throw ClientUnknownException();
        }

        if (tables_[curr_table_number].IsPlaceOccupied()) {
            throw PlaceIsBusyException();
        }
        tables_[curr_table_number].MakePlaceOccupiedAt(event_time);
        clients_[client_name].SetPlace(curr_table_number);
        ++occupied_tables_number_;
    }

    void ComputerClub::ClientIsWaiting(const TimeFormat&  event_time,
                                       const std::string& client_name) {
        if (occupied_tables_number_ < table_number_) {
            throw ICanWaitNoLongerException();
        }
        if (clients_queue_.size() > table_number_) {
            Event new_event = Event(
                    event_time,
                    Event::StatusId::kClientHasLeftAfterClosingTime,
                    {client_name});
            std::cout << new_event << std::endl;
            clients_.erase(client_name);

            return;
        }
        clients_queue_.emplace_back(client_name);
        clients_[client_name].SetStatusInQueue();
    }

    void ComputerClub::ClientHasLeftBeforeClosingTime(const TimeFormat&  event_time,
                                                      const std::string& client_name) {
        if (!IsClientInClubByName(client_name)) {
            throw ClientUnknownException();
        }
        --occupied_tables_number_;
        auto client_place = clients_[client_name].GetPlace();
        tables_[client_place].UpdateHoldingTime(event_time);
        clients_.erase(client_name);
        if (!clients_queue_.empty()) {
            ++occupied_tables_number_;
            std::string new_client_name = clients_queue_.front().GetName();
            clients_queue_.pop_front();
            clients_[new_client_name].SetPlace(client_place);
            clients_[new_client_name].SetStatusNotInQueue();
            Event new_event = Event(
                    event_time,
                    Event::StatusId::kClientFromQueueHasSatDownAtTable,
                    {new_client_name, std::to_string(client_place + 1)});
            std::cout << new_event << std::endl;
        }
    }

    void ComputerClub::ClientHasLeftAfterClosingTime(const TimeFormat& event_time,
                                                     Client&           client) {
        --occupied_tables_number_;
        if (!client.GetQueueStatus()) {
            tables_[client.GetPlace()].UpdateHoldingTime(event_time);
        }
        Event new_event = Event(
                event_time,
                Event::StatusId::kClientHasLeftAfterClosingTime,
                {client.GetName()});
        std::cout << new_event << std::endl;
    }

    ComputerClub::Event::Event(const TimeFormat&               time,
                               StatusId                        id,
                               const std::vector<std::string>& body) : time_(time),
                                                                       id_(id),
                                                                       body_(body) {}

    std::fstream& operator>>(std::fstream& fs, ComputerClub::Event& event) {
        std::string line;
        std::getline(fs, line);
        std::istringstream fss(line);

        short event_id;
        fss >> event.time_ >> event_id;
        event.id_ = ComputerClub::Event::StatusId(event_id);

        std::string body_part;
        while (fss >> body_part) {
            event.body_.push_back(body_part);
        }

        return fs;
    }

    std::ostream& operator<<(std::ostream& os, const ComputerClub::Event& event) {
        os << event.time_ << ' ' << ComputerClub::Event::StatusIdToInt(event.id_) << ' ';
        for (auto& body_part: event.body_) {
            os << body_part << ' ';
        }

        return os;
    }

    auto ComputerClub::Event::StatusIdToInt(StatusId value)
            -> typename std::underlying_type<StatusId>::type {
        return static_cast<typename std::underlying_type<StatusId>::type>(value);
    }
} // namespace computer_club
