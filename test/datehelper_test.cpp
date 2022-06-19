#include <gtest/gtest.h>
#include <tuple>

#include <calendergenerator/datehelper.h>

class LeapYearParameterizedTest : public ::testing::TestWithParam<std::tuple<int, bool>> {
};

TEST_P(LeapYearParameterizedTest, CheckIsLeapYear) {
    auto const year = std::get<0>(GetParam());
    auto const expected = std::get<1>(GetParam());
    ASSERT_EQ(expected, calendergenerator::datehelper::is_leap_year(year));
}

INSTANTIATE_TEST_CASE_P(
        LeapYearTests,
        LeapYearParameterizedTest,
        ::testing::Values(
                std::make_tuple(7, false),
                std::make_tuple(2001, false),
                std::make_tuple(1996, true),
                std::make_tuple(1700, false),
                std::make_tuple(1600, true),
                std::make_tuple(2024, true)
                )
);

class DayOfWeekTest : public ::testing::TestWithParam<std::tuple<
        calendergenerator::Date, calendergenerator::DayOfWeek>> {
};

TEST_P(DayOfWeekTest, CheckDayOfWeek) {
    auto const date = std::get<0>(GetParam());
    auto const expected = std::get<1>(GetParam());
    ASSERT_EQ(expected, calendergenerator::datehelper::get_day_of_week(date))
      << date.day << "/" << static_cast<int>(date.month) + 1 << "/" << date.year;
}

INSTANTIATE_TEST_CASE_P(
        DayOfWeekTests,
        DayOfWeekTest,
        ::testing::Values(
          std::make_tuple(calendergenerator::Date{.day=30, .month=calendergenerator::Month::June, .year=2021}, calendergenerator::DayOfWeek::Wednesday),
          std::make_tuple(calendergenerator::Date{.day=29, .month=calendergenerator::Month::February, .year=2024}, calendergenerator::DayOfWeek::Thursday),
          std::make_tuple(calendergenerator::Date{.day=13, .month=calendergenerator::Month::April, .year=1998}, calendergenerator::DayOfWeek::Monday),
          std::make_tuple(calendergenerator::Date{.day=27, .month=calendergenerator::Month::April, .year=1800}, calendergenerator::DayOfWeek::Sunday),
          std::make_tuple(calendergenerator::Date{.day=14, .month=calendergenerator::Month::December, .year=1900}, calendergenerator::DayOfWeek::Friday),
          std::make_tuple(calendergenerator::Date{.day=16, .month=calendergenerator::Month::October, .year=2000}, calendergenerator::DayOfWeek::Monday),
          std::make_tuple(calendergenerator::Date{.day=28, .month=calendergenerator::Month::February, .year=2017}, calendergenerator::DayOfWeek::Tuesday),
          std::make_tuple(calendergenerator::Date{.day=1, .month=calendergenerator::Month::April, .year=2000}, calendergenerator::DayOfWeek::Saturday)
        )
);

class DaysInMonthTest : public ::testing::TestWithParam<std::tuple<
        calendergenerator::Date, int>> {
};

TEST_P(DaysInMonthTest, CheckDaysInMonth) {
    auto const date = std::get<0>(GetParam());
    auto const expected = std::get<1>(GetParam());
    ASSERT_EQ(expected, calendergenerator::datehelper::get_days_in_month(date))
                                << date.day << "/" << static_cast<int>(date.month) << "/" << date.year;
}

INSTANTIATE_TEST_CASE_P(
        DaysInMonthTests,
        DaysInMonthTest,
        ::testing::Values(
                std::make_tuple(calendergenerator::Date{.day=30, .month=calendergenerator::Month::January, .year=2021}, 31),
                std::make_tuple(calendergenerator::Date{.day=30, .month=calendergenerator::Month::June, .year=2024}, 30),
                std::make_tuple(calendergenerator::Date{.day=29, .month=calendergenerator::Month::February, .year=2001}, 28),
                std::make_tuple(calendergenerator::Date{.day=13, .month=calendergenerator::Month::February, .year=1996}, 29)
        )
);



