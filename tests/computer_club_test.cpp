#include "lib/computer_club.hpp"

#include <gtest/gtest.h>

TEST(ComputerClub, DefaultTest) {
    std::filesystem::path path_in = "./resources/input0.txt";
    const char           *path_out = "./resources/ouput0.txt";

    computer_club::ComputerClub club(path_in);

    FILE *out_file = freopen(path_out, "w", stdout);
    club.LaunchApp();

    // fclose(out_file);

    std::ifstream fin(path_out);
    std::string   result((std::istreambuf_iterator<char>(fin)),
                         std::istreambuf_iterator<char>());

    const std::string kExpected =
            "09:00\n"
            "08:48 1 client1 \n"
            "08:48 13 NotOpenYet \n"
            "09:41 1 client1 \n"
            "09:48 1 client2 \n"
            "09:52 3 client1 \n"
            "09:52 13 ICanWaitNoLonger! \n"
            "09:54 2 client1 1 \n"
            "10:25 2 client2 2 \n"
            "10:58 1 client3 \n"
            "10:59 2 client3 3 \n"
            "11:30 1 client4 \n"
            "11:35 2 client4 2 \n"
            "11:35 13 PlaceIsBusy \n"
            "11:45 3 client4 \n"
            "12:33 4 client1 \n"
            "12:33 12 client4 1 \n"
            "12:43 4 client2 \n"
            "15:52 4 client4 \n"
            "19:00 11 client3 \n"
            "19:00\n"
            "1 70 05:58\n"
            "2 30 02:18\n"
            "3 90 08:01\n";

    EXPECT_EQ(result, kExpected);
}

TEST(ComputerClub, BigTest) {
    std::filesystem::path path_in = "./resources/input1.txt";
    const char           *path_out = "./resources/ouput1.txt";

    computer_club::ComputerClub club(path_in);

    FILE *out_file = freopen(path_out, "w", stdout);
    club.LaunchApp();

    // fclose(out_file);

    std::ifstream fin(path_out);
    std::string   result((std::istreambuf_iterator<char>(fin)),
                         std::istreambuf_iterator<char>());

    const std::string kExpected =
            "09:00\n"
            "08:48 1 client1 \n"
            "08:48 13 NotOpenYet \n"
            "09:41 1 client1 \n"
            "09:42 1 client1 \n"
            "09:42 13 YouShallNotPass \n"
            "09:48 1 client2 \n"
            "09:48 5 client2 \n"
            "09:48 13 WrongEventId \n"
            "09:52 3 client1 \n"
            "09:52 13 ICanWaitNoLonger! \n"
            "09:54 2 client1 1 \n"
            "10:25 2 client2 2 \n"
            "10:58 1 client3 \n"
            "10:59 2 client3 1 \n"
            "10:59 13 PlaceIsBusy \n"
            "11:00 3 client3 \n"
            "11:20 1 client4 \n"
            "11:30 2 client7 1 \n"
            "11:30 13 ClientUnknown \n"
            "11:35 2 client4 1 \n"
            "11:35 13 PlaceIsBusy \n"
            "11:45 3 client4 \n"
            "12:00 1 client5 \n"
            "12:05 4 client7 \n"
            "12:05 13 ClientUnknown \n"
            "12:15 3 client5 \n"
            "12:20 1 client6 \n"
            "12:21 3 client6 \n"
            "12:21 11 client6 \n"
            "12:33 4 client1 \n"
            "12:33 12 client3 1 \n"
            "19:00 11 client2 \n"
            "19:00 11 client3 \n"
            "19:00 11 client4 \n"
            "19:00 11 client5 \n"
            "19:00\n"
            "1 250 09:06\n"
            "2 225 08:35\n";

    EXPECT_EQ(result, kExpected);
}
