#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "Service.h"

Service::Service(FileRepository& r, RepositoryUser* ur) : repo{ r }, repoUser{ ur } {}

Event Service::findByTitleDate(const std::string& title, const std::string& date)
{
    int position = this->repo.searchByTitleDate(title, date);
    if (position == -1)
        throw RepositoryException("Repository error: nonexistent event!");
    return this->repo.getEvents()[position];
}

void Service::addEventService(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link)
{
    Event e{ title, description, date, time, numberOfPeople, link };
    this->repo.addEvent(e);
}

void Service::deleteEventService(const std::string& title, const std::string& date)
{
    this->repo.deleteEvent(title, date);
    if (this->repoUser->searchByTitleDate(title, date) != -1)
        this->repoUser->deleteUserEvent(title, date);
}

void Service::updateEventService(const Event& oldElem, const Event& newElem)
{
    this->repo.updateEvent(oldElem, newElem);
    if (this->repoUser->searchByTitleDate(oldElem.getTitle(), oldElem.getDate()) != -1)
        this->repoUser->updateUserEvent(oldElem, newElem);
}

void Service::addEventToUserList(const Event& e)
{
    this->repoUser->addUserEvent(e);
    int pos = this->repo.searchByTitleDate(e.getTitle(), e.getDate());
    int nr = this->repo.getEvents()[pos].getNumberOfPeople();
    this->repo.getEvents()[pos].setNumberOfPeople(nr + 1);
    int pos1 = this->repoUser->searchByTitleDate(e.getTitle(), e.getDate());
    int nr1 = this->repoUser->getUserEvents()[pos1].getNumberOfPeople();
    this->repoUser->getUserEvents()[pos1].setNumberOfPeople(nr1 + 1);
    this->repo.writeToFile();
}

void Service::deleteEventUserService(const std::string& title, const std::string& date)
{
    this->repoUser->deleteUserEvent(title, date);
    int pos = this->repo.searchByTitleDate(title, date);
    int nr = this->repo.getEvents()[pos].getNumberOfPeople();
    this->repo.getEvents()[pos].setNumberOfPeople(nr - 1);
    this->repo.writeToFile();
}

int Service::getMonth(const std::string& date)
{
    char* p;
    char str[11] = "";
    strcpy(str, date.c_str());
    p = strtok(str, "/");
    int counter = 0, val = 0;
    while (p)
    {
        counter++;
        if (counter == 2)
        {
            if (p[0] == '0')
                val = p[1] - '0';
            else
                val = atoi(p);
        }
        p = strtok(nullptr, "/");
    }
    return val;
}

std::vector<Event> Service::filterRepoByMonth(int month)
{
    std::vector<Event> repository = this->repo.getEvents();
    std::vector<Event> filtered;

    auto lambdaFunction = std::copy_if(repository.begin(), repository.end(), std::back_inserter(filtered), [month](Event event)
        { return (getMonth(event.getDate()) == month); });

    return filtered;
}

struct dates
{
    int day;
    int month;
    int year;
};

bool Service::compareDates(const Event& event1, const Event& event2)
{
    std::string date1 = event1.getDate();
    std::string date2 = event2.getDate();
    char* p;
    struct dates d1 = { 0 }, d2 = { 0 };
    char str1[11] = "", str2[11] = "";
    strcpy(str1, date1.c_str());
    strcpy(str2, date2.c_str());
    p = strtok(str1, "/");
    int val, counter = 0;
    while (p)
    {
        counter++;
        val = atoi(p);
        if (counter == 1)
            d1.day = val;
        else
            if (counter == 2)
                d1.month = val;
            else
                d1.year = val;
        p = strtok(nullptr, "/");
    }
    p = strtok(str2, "/");
    counter = 0;
    while (p)
    {
        counter++;
        val = atoi(p);
        if (counter == 1)
            d2.day = val;
        else
            if (counter == 2)
                d2.month = val;
            else
                d2.year = val;
        p = strtok(nullptr, "/");
    }
    if (d1.year < d2.year)
        return true;
    else
        if (d1.year > d2.year)
            return false;
        else // d1.year == d2.year
            if (d1.month < d2.month)
                return true;
            else
                if (d1.month > d2.month)
                    return false;
                else // d1.month == d2.month
                    if (d1.day <= d2.day)
                        return true;
                    else
                        return false;
}

void Service::sortRepoByDate(std::vector<Event>& r)
{
    std::sort(r.begin(), r.end(), compareDates);
}
