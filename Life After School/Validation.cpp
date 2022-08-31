#include "Validation.h"
#include <algorithm>
#include <string>

void Validator::validateUserCommand(std::string& input)
{
    if (input.length() == 0)
        throw ValidatorException("  Input error: command cannot be empty!");
    else
    {
        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        transform(input.begin(), input.end(), input.begin(), ::tolower);
    }
}

void Validator::validateEventTitle(const std::string& title)
{
    if (title.length() == 0)
        throw ValidatorException("  Input error: title of event cannot be empty!");
}

void Validator::validateEventDescription(const std::string& description)
{
    if (description.length() == 0)
        throw ValidatorException("  Input error: description of event cannot be empty!");
}

void Validator::validateEventDay(const std::string& day)
{
    if (day.length() == 0)
        throw ValidatorException("  Input error: day of event cannot be empty!");

    int isint = Validator::isInteger(day);
    if (isint == -1)
        throw ValidatorException("  Input error: day of event must be an integer between 1 and 30!");

    int dayy = stoi(day);
    if (dayy < 1 || dayy > 30)
        throw ValidatorException("  Input error: day of event must be an integer between 1 and 30!");
}

void Validator::validateEventMonth(const std::string& month)
{
    if (month.length() == 0)
        throw ValidatorException("  Input error: month of event cannot be empty!");

    int isint = Validator::isInteger(month);
    if (isint == -1)
        throw ValidatorException("  Input error: month of event must be an integer between 1 and 12!");

    int monthh = stoi(month);
    if (monthh < 0 || monthh > 12)
        throw ValidatorException("  Input error: month of event must be an integer between 1 and 12!");
}

void Validator::validateEventYear(const std::string& year)
{
    if (year.length() == 0)
        throw ValidatorException("  Input error: year of event cannot be empty!");

    int isint = Validator::isInteger(year);
    if (isint == -1)
        throw ValidatorException("  Input error: year of event must be an integer between 2000 and 2100!");

    int yearr = stoi(year);
    if (yearr < 2000 || yearr > 2100)
        throw ValidatorException("  Input error: year of event must be an integer between 2000 and 2100!");
}

void Validator::validateEventHour(const std::string& hour)
{
    if (hour.length() == 0)
        throw ValidatorException("  Input error: hour of event cannot be empty!");

    int isint = Validator::isInteger(hour);
    if (isint == -1)
        throw ValidatorException("  Input error: hour of event must be an integer between 0 and 23!");

    int hourr = stoi(hour);
    if (hourr < 0 || hourr > 23)
        throw ValidatorException("  Input error: hour of event must be an integer between 0 and 23!");
}

void Validator::validateEventMinutes(const std::string& minutes)
{
    if (minutes.length() == 0)
        throw ValidatorException("  Input error: minutes of event cannot be empty!");

    int isint = Validator::isInteger(minutes);
    if (isint == -1)
        throw ValidatorException("  Input error: minutes of event must be an integer between 0 and 59!");

    int minutess = stoi(minutes);
    if (minutess < 0 || minutess > 59)
        throw ValidatorException("  Input error: minutes of event must be an integer between 0 and 59!");
}

void Validator::validateEventLink(const std::string& link)
{
    if (link.length() == 0)
        throw ValidatorException("  Input error: title of event cannot be empty!");
}

void Validator::validateEventNrOfPeople(const std::string& numberOfPeople)
{
    if (numberOfPeople.length() == 0)
        throw ValidatorException("  Input error: number of people attending the event cannot be empty!");

    int isint = Validator::isInteger(numberOfPeople);
    if (isint == -1)
        throw ValidatorException("  Input error: number of people attending the event must be a positive integer!");

    int number = stoi(numberOfPeople);
    if (number < 0)
        throw ValidatorException("  Input error: number of people attending the event must be a positive integer!");
}

int Validator::isInteger(const std::string& s)
{
    int i;
    for (i = 0; i < s.length(); i++)
    {
        if (i == 0 && isdigit(s[i]) == false && s[i] == '-')
            continue;
        if (isdigit(s[i]) == false)
            return -1;
    }

    return stoi(s);
}

void Validator::validateAll(std::string& title, std::string& description, std::string& day, std::string& month, std::string& year, std::string& hour, std::string& minutes, std::string& numberOfPeople, std::string& link)
{
    std::string exception = "";
    try {
        validateEventTitle(title);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventDescription(description);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventDay(day);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMonth(month);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventYear(year);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventHour(hour);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMinutes(minutes);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventNrOfPeople(numberOfPeople);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventLink(link);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateTitleDate(std::string& title, std::string& day, std::string& month, std::string& year)
{
    std::string exception = "";
    try {
        validateEventTitle(title);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventDay(day);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMonth(month);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventYear(year);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateDate(std::string& day, std::string& month, std::string& year)
{
    std::string exception = "";
    try {
        validateEventDay(day);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMonth(month);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventYear(year);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
    }
    if (exception != "")
        throw ValidatorException(exception);
}

void Validator::validateTime(std::string& hour, std::string& minutes)
{
    std::string exception = "";
    try {
        validateEventHour(hour);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }
    try {
        validateEventMinutes(minutes);
    }
    catch (ValidatorException& ve) {
        exception += ve.what();
        exception += "\n";
    }

    if (exception != "")
        throw ValidatorException(exception);
}