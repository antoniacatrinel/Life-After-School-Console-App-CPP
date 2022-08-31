#include <algorithm>
#include "InmemoryRepository.h"

int Repository::searchByTitleDate(const std::string& title, const std::string& date)
{
    std::vector<Event>::iterator it;
    it = std::find_if(this->events.begin(), this->events.end(), [&](const Event& x) { return x.getTitle() == title && x.getDate() == date; });

    if (it != this->events.end())
        return (int)(it - this->events.begin());  

    return -1;
}

void Repository::addEvent(const Event& elem)
{
    if (searchByTitleDate(elem.getTitle(), elem.getDate()) != -1) 
        throw RepositoryException("Repository error: this event already exists!");

    this->events.push_back(elem);

    /* Same as
    this->events = this->events + elem;
    this->events = elem + this->events;*/
}

void Repository::deleteEvent(const std::string& title, const std::string& date)
{
    int position = searchByTitleDate(title, date);
    if (position == -1)  
        throw RepositoryException("Repository error: nonexistent event!");

    if (position == 0)
        this->events.pop_back();
    else
    {
        std::vector<Event>::iterator it = this->events.begin() + position;
        this->events.erase(it);
    }

    /* Same as
    Event e = this->events[position];
    this->events = this->events - e;*/
}

void Repository::updateEvent(const Event& oldElem, const Event& newElem)
{
    int position = searchByTitleDate(oldElem.getTitle(), oldElem.getDate());
    if (position == -1) 
        throw RepositoryException("Repository error: nonexistent event!");

    this->events[position].setTitle(newElem.getTitle());
    this->events[position].setDescription(newElem.getDescription());
    this->events[position].setDate(newElem.getDate());
    this->events[position].setTime(newElem.getTime());
    this->events[position].setNumberOfPeople(newElem.getNumberOfPeople());
    this->events[position].setLink(newElem.getLink());
}