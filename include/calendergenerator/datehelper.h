#pragma once

#include <unordered_map>
#include <string>

#include "types.h"

namespace calendergenerator::datehelper {

    /**
     * \brief For a date get the number of days in the month.
     * \param date
     * \return number of days
     */
    int get_days_in_month(Date date);

    /**
     * \brief For a year check if it is a leap year or not.
     * \see https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
     * \param year
     * \return is leap year or not
     */
    bool is_leap_year(int year);

    /**
     * \brief For a date get the day of the week it is on.
     * \see https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/
     * \param date
     * \return day of the week
     */
    DayOfWeek get_day_of_week(Date date);
}
