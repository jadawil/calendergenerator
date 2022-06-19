#include <vector>

#include "calendergenerator/datehelper.h"

namespace calendergenerator::datehelper {

    int get_days_in_month(Date date) {
        static std::vector<int> const MONTH_TO_DAYS = {
                31,28,31,30,31,30,31,31,30,31,30,31,
        };

        if(date.month == February && is_leap_year(date.year)) return 29;

        return MONTH_TO_DAYS[date.month];
    }

    bool is_leap_year(int year) {
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }

    DayOfWeek get_day_of_week(Date date) {

        static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        auto const adjusted_month = date.month + 1;
        auto const adjusted_year = date.month < 3 ? date.year - 1 : date.year;
        auto const day_of_week = ( adjusted_year + adjusted_year / 4 - adjusted_year / 100 +
                adjusted_year / 400 + t[adjusted_month - 1] + date.day) % 7;

        //This outputs day_of_week with 0 as Sunday so we adjust here to match the enum order.
        if(day_of_week == 0) return DayOfWeek::Sunday;

        return static_cast<DayOfWeek>(day_of_week - 1);
    }
}