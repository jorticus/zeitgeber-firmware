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
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday",
};
const char* short_days[7] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun",
};

const char* months[13] = {
    "-",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};
const char* short_months[13] = {
    "-",
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
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

