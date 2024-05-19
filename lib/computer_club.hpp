#pragma once

#include "client/client.hpp"
#include "exceptions.hpp"
#include "place/place.hpp"
#include "time_format/time_format.hpp"

#include <deque>
#include <filesystem>
#include <map>
#include <unordered_map>

namespace computer_club {
    class ComputerClub {
    public:
        explicit ComputerClub(std::filesystem::path& path);

        void LaunchApp();

        struct Event {
            enum class StatusId {
                kClientHasCome = 1,
                kClientHasSatDownAtTable = 2,
                kClientIsWaiting = 3,
                kClientHasLeftBeforeClosingTime = 4,
                kClientHasLeftAfterClosingTime = 11,
                kClientFromQueueHasSatDownAtTable = 12,
                kError = 13,
            };

            Event() = default;
            explicit Event(const TimeFormat&,
                           StatusId,
                           const std::vector<std::string>&);

            friend std::fstream& operator>>(std::fstream& fs, Event&);
            friend std::ostream& operator<<(std::ostream& os, const Event&);

            static auto StatusIdToInt(StatusId value)
                    -> typename std::underlying_type<StatusId>::type;

            TimeFormat               time_{};
            StatusId                 id_{};
            std::vector<std::string> body_{};
        };

    private:
        void ReadEvents();
        void EventHandler(Event&);
        void ClubClosing();
        void PrintPlacesResult();

        bool IsClientInClubByName(const std::string&);

        void ClientHasCome(const TimeFormat&, const std::string&);
        void ClientHasSatDownAtTable(const TimeFormat&, const std::string&, TableNumber);
        void ClientIsWaiting(const TimeFormat&, const std::string&);
        void ClientHasLeftBeforeClosingTime(const TimeFormat&, const std::string&);
        void ClientHasLeftAfterClosingTime(const TimeFormat&, Client&);

        std::filesystem::path input_path_;
        std::fstream          stream_from_;

        TimeFormat opening_time_;
        TimeFormat closing_time_;

        TableNumber table_number_ = 0;
        TableNumber occupied_tables_number_ = 0;

        std::unordered_map<TableNumber, Place>  tables_;
        std::unordered_map<std::string, Client> clients_;
        std::deque<Client>                      clients_queue_;
    };
} // namespace computer_club
