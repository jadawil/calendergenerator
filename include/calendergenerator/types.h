#pragma once

#include <map>

namespace calendergenerator {

    enum Month {
        January,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    static std::map<Month, std::string> const MONTH_WITH_NAME = {
            {January, "January"}, {February, "February"}, {March, "March"}, {April, "April"},
            {May, "May"}, {June, "June"}, {July, "July"}, {August, "August"},
            {September, "September"}, {October, "October"}, {November, "November"}, {December, "December"}
    };

    struct Date {
        int day;
        Month month;
        int year;
    };

    enum class DayOfWeek {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday,
    };
}
