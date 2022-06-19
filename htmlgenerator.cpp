#include <string>
#include <sstream>

#include <fmt/core.h>

#include "calendergenerator/htmlgenerator.h"
#include "calendergenerator/datehelper.h"

namespace {
    std::string HTML = """<!DOCTYPE html>\n"
                       "<html lang=\"\">\n"
                       "  <head>\n"
                       "    <meta charset=\"utf-8\">\n"
                       "    <title></title>\n"
                       "    <style>\n"
                       "      .column {{\n"
                       "        float: left;\n"
                       "        width: 33.33%;\n"
                       "      }}\n"
                       "      .row:after {{\n"
                       "        content: \"\";\n"
                       "        display: table;\n"
                       "        clear: both;\n"
                       "      }}\n"
                       "    </style>\n"
                       "  </head>\n"
                       "  <body>\n"
                       "    <main>\n"
                       "      <div class=\"row\">\n"
                       "        {}"
                       "      </div>\n"
                       "    </main>\n"
                       "  </body>\n"
                       "</html>""";

    std::string html_calender_for_year(int year) {
        std::stringstream ss;
        int week_num = 0;

        for (auto const& [month, name] : calendergenerator::MONTH_WITH_NAME) {
            auto const date = calendergenerator::Date{.day=1, .month=month, .year=year};
            auto const days = calendergenerator::datehelper::get_days_in_month(date);
            auto const start_day_of_week = calendergenerator::datehelper::get_day_of_week(date);
            ss << "<table border=\"1\">\n"
                  "<tr>\n"
                  "<th colspan=\"8\">" <<
                  name << " "
                  << year << "</th>\n"
                               "<tr>\n"
                                 "<th>Wk</th>\n"
                                 "<th>Mo</th>\n"
                                 "<th>Tu</th>\n"
                                 "<th>We</th>\n"
                                 "<th>Th</th>\n"
                                 "<th>Fr</th>\n"
                                 "<th>Sa</th>\n"
                                 "<th>Su</th>\n"
                               "</tr>";

            week_num++;
            ss << "<tr><td>" << week_num << "</td>";

            int generated_cells = 0;
            //Add in the initial empty cells
            for(int j = 0; j < static_cast<int>(start_day_of_week); j++) {
                ss << "<td></td>";
                generated_cells++;
            }

            for(int j = 1; j <= days; j++) {
                ss << "<td>" << j << "</td>";
                generated_cells++;
                if(generated_cells % 7 == 0) {
                    ss << "</tr><tr>";

                    if(j != days) {
                        week_num++;
                        ss << "<td>" << week_num << "</td>";
                    }
                }
            }

            //Add any remaining empty cells
            while(generated_cells % 7 != 0) {
                ss << "<td></td>";
                generated_cells++;
            }

            ss << "</tr>";
            ss << "</table>";
        }

        return ss.str();
    }
}


namespace calendergenerator::htmlgenerator {
    std::string generate_calender(int year) {
        std::stringstream ss;

        ss << "<div class=\"column\">" << html_calender_for_year(year - 1) << "</div>"
           << "<div class=\"column\">" << html_calender_for_year(year) << "</div>"
           << "<div class=\"column\">" << html_calender_for_year(year + 1) << "</div>";

        return fmt::format(HTML, ss.str());
    }
}