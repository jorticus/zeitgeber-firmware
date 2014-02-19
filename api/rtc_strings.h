/* 
 * File:   rtc_strings.h
 * Author: Jared
 *
 * Created on 5 July 2013, 3:07 PM
 *
 * Localizable calendar strings.
 * ONLY INCLUDE THIS FILE IN RTC.C!
 */

#ifndef RTC_STRINGS_H
#define	RTC_STRINGS_H

const char* days[7] = {
    "Sunday\0",
    "Monday\0",
    "Tuesday\0",
    "Wednesday\0",
    "Thursday\0",
    "Friday\0",
    "Saturday\0"
};
const char* short_days[7] = {
    "Sun\0",
    "Mon\0",
    "Tue\0",
    "Wed\0",
    "Thu\0",
    "Fri\0",
    "Sat\0"
};

const char* months[12] = {
    "January\0",
    "February\0",
    "March\0",
    "April\0",
    "May\0",
    "June\0",
    "July\0",
    "August\0",
    "September\0",
    "October\0",
    "November\0",
    "December\0"
};
const char* short_months[12] = {
    "Jan\0",
    "Feb\0",
    "Mar\0",
    "Apr\0",
    "May\0",
    "Jun\0",
    "Jul\0",
    "Aug\0",
    "Sep\0",
    "Oct\0",
    "Nov\0",
    "Dec\0"
};

const char* day_suffix[] = {
    "th",
    "st",
    "nd",
    "rd",
    "th"
};

const char* ampm[] = {"am\0", "pm\0"};

#endif	/* RTC_STRINGS_H */

