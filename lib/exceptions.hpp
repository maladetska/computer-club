#include <exception>

namespace computer_club {
    struct YouShallNotPassException : std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "YouShallNotPass";
        }
    };

    struct NotOpenYetException : std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "NotOpenYet";
        }
    };

    struct PlaceIsBusyException : std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "PlaceIsBusy";
        }
    };

    struct ClientUnknownException : std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "ClientUnknown";
        }
    };

    struct ICanWaitNoLongerException : std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "ICanWaitNoLonger!";
        }
    };

    struct WrongEventIdException : std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "WrongEventId";
        }
    };
} // namespace computer_club
