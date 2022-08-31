#include "Ui.h"
#include "Tests.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

UI::UI(Service& srv, Validator valid) : service{ srv }, validator{ valid } {}

std::string UI::readUserCommand()
{
    std::string input;
    bool finishReading = false;
    while (!finishReading)
    {
        std::cout << "  Please select an option from the menu > ";
        getline(cin, input, '\n');
        try
        {
            this->validator.validateUserCommand(input);
            finishReading = true;
            return input;
        }
        catch (ValidatorException& err)
        {
            std::cout << err.what() << std::endl;
        }
    }
}

void UI::addEventAdminUI()
{
    std::string title, description, date, time, link, numberOfPeople;
    std::string day, month, year;
    std::string hour, minutes;
    std::cout << " > Input the title of the event: ";
    getline(cin, title, '\n');
    trimWhiteSpaces(title);
    transform(title.begin(), title.end(), title.begin(), ::tolower);
    std::cout << " > Input the description of the event: ";
    getline(cin, description, '\n');
    trimWhiteSpaces(description);
    transform(description.begin(), description.end(), description.begin(), ::tolower);
    std::cout << " > Input the day of the event: ";
    getline(cin, day, '\n');
    std::cout << " > Input the month of the event: ";
    getline(cin, month, '\n');
    std::cout << " > Input the year of the event: ";
    getline(cin, year, '\n');
    std::cout << " > Input the hour of the event: ";
    getline(cin, hour, '\n');
    std::cout << " > Input the minutes of the event: ";
    getline(cin, minutes, '\n');
    std::cout << " > Input the number of people attending the event: ";
    getline(cin, numberOfPeople, '\n');
    trimWhiteSpaces(numberOfPeople);
    std::cout << " > Input the link of the event: ";
    getline(cin, link, '\n');
    trimWhiteSpaces(link);
    transform(link.begin(), link.end(), link.begin(), ::tolower);
    try
    {
        this->validator.validateAll(title, description, day, month, year, hour, minutes, numberOfPeople, link);
        if (stoi(day) < 10)
            day = "0" + day;
        if (stoi(month) < 10)
            month = "0" + month;
        date = day + "/" + month + "/" + year;
        if (stoi(hour) < 10)
            hour = "0" + hour;
        if (stoi(minutes) < 10)
            minutes = "0" + minutes;
        time = hour + ":" + minutes;
        int people;
        people = stoi(numberOfPeople);

        this->service.addEventService(title, description, date, time, people, link);
        std::cout << "  Event added successfully!" << std::endl;
    }
    catch (RepositoryException& rerr)
    {
        std::cout << rerr.what() << std::endl;
    }
    catch (ValidatorException& verr)
    {
        std::cout << verr.what() << std::endl;
    }
    catch (FileException& ferr)
    {
        std::cout << ferr.what() << std::endl;
    }
}

void UI::deleteEventAdminUI()
{
    std::string title, date, day, month, year;
    std::cout << " > Input the title of the event: ";
    getline(cin, title, '\n');
    trimWhiteSpaces(title);
    transform(title.begin(), title.end(), title.begin(), ::tolower);
    std::cout << " > Input the day of the event: ";
    getline(cin, day, '\n');
    std::cout << " > Input the month of the event: ";
    getline(cin, month, '\n');
    std::cout << " > Input the year of the event: ";
    getline(cin, year, '\n');

    try
    {
        this->validator.validateTitleDate(title, day, month, year);
        if (stoi(day) < 10)
            day = "0" + day;
        if (stoi(month) < 10)
            month = "0" + month;
        date = day + "/" + month + "/" + year;
        this->service.deleteEventService(title, date);
        std::cout << "  Event deleted successfully!" << std::endl;
    }
    catch (RepositoryException& rerr)
    {
        std::cout << rerr.what() << std::endl;
    }
    catch (ValidatorException& verr)
    {
        std::cout << verr.what() << std::endl;
    }
    catch (FileException& ferr)
    {
        std::cout << ferr.what() << std::endl;
    }
}

void UI::updateEventAdminUI()
{
    std::cout << "  Which event do you want to update?" << std::endl;
    std::string title, date, day, month, year;
    std::cout << " > Input the title of the event: ";
    getline(cin, title, '\n');
    trimWhiteSpaces(title);
    transform(title.begin(), title.end(), title.begin(), ::tolower);
    std::cout << " > Input the day of the event: ";
    getline(cin, day, '\n');
    std::cout << " > Input the month of the event: ";
    getline(cin, month, '\n');
    std::cout << " > Input the year of the event: ";
    getline(cin, year, '\n');

    try
    {
        this->validator.validateTitleDate(title, day, month, year);
        if (stoi(day) < 10)
            day = "0" + day;
        if (stoi(month) < 10)
            month = "0" + month;
        date = day + "/" + month + "/" + year;

        Event oldElem = this->service.findByTitleDate(title, date);
        std::string option;
        std::cout << "  What do you want to update? (title, description, date, time, people or link)> ";
        getline(cin, option, '\n');
        option.erase(remove(option.begin(), option.end(), ' '), option.end());
        transform(option.begin(), option.end(), option.begin(), ::tolower);

        if (option == "title")
        {
            try
            {
                std::string newtitle;
                std::cout << " > Input the title of the event: ";
                getline(cin, newtitle, '\n');
                trimWhiteSpaces(newtitle);
                transform(newtitle.begin(), newtitle.end(), newtitle.begin(), ::tolower);
                this->validator.validateEventTitle(newtitle);
                Event newElem{ newtitle, oldElem.getDescription(), oldElem.getDate(), oldElem.getTime(), oldElem.getNumberOfPeople(), oldElem.getLink() };
                this->service.updateEventService(oldElem, newElem);
                std::cout << "  Event updated successfully!" << std::endl;
            }
            catch (RepositoryException& rerr)
            {
                std::cout << rerr.what() << std::endl;
            }
            catch (ValidatorException& verr)
            {
                std::cout << verr.what() << std::endl;
            }
        }
        else
            if (option == "description")
            {
                try
                {
                    std::string newdesc;
                    std::cout << " > Input the description of the event: ";
                    getline(cin, newdesc, '\n');
                    trimWhiteSpaces(newdesc);
                    transform(newdesc.begin(), newdesc.end(), newdesc.begin(), ::tolower);
                    this->validator.validateEventDescription(newdesc);
                    Event newElem{ oldElem.getTitle(), newdesc, oldElem.getDate(), oldElem.getTime(), oldElem.getNumberOfPeople(), oldElem.getLink() };
                    this->service.updateEventService(oldElem, newElem);
                    std::cout << "  Event updated successfully!" << std::endl;
                }
                catch (RepositoryException& rerr)
                {
                    std::cout << rerr.what() << std::endl;
                }
                catch (ValidatorException& verr)
                {
                    std::cout << verr.what() << std::endl;
                }
            }
            else
                if (option == "date")
                {
                    try
                    {
                        std::string newdate, newday, newyear, newmonth;
                        std::cout << " > Input the day of the event: ";
                        getline(cin, newday, '\n');
                        std::cout << " > Input the month of the event: ";
                        getline(cin, newmonth, '\n');
                        std::cout << " > Input the year of the event: ";
                        getline(cin, newyear, '\n');
                        this->validator.validateDate(newday, newmonth, newyear);
                        if (stoi(day) < 10)
                            day = "0" + day;
                        if (stoi(month) < 10)
                            month = "0" + month;
                        date = day + "/" + month + "/" + year;
                        Event newElem{ oldElem.getTitle(), oldElem.getDescription(), newdate, oldElem.getTime(), oldElem.getNumberOfPeople(), oldElem.getLink() };
                        this->service.updateEventService(oldElem, newElem);
                        std::cout << "  Event updated successfully!" << std::endl;
                    }
                    catch (RepositoryException& rerr)
                    {
                        std::cout << rerr.what() << std::endl;
                    }
                    catch (ValidatorException& verr)
                    {
                        std::cout << verr.what() << std::endl;
                    }
                    catch (FileException& ferr)
                    {
                        std::cout << ferr.what() << std::endl;
                    }
                }
                else
                    if (option == "time")
                    {
                        try
                        {
                            std::string newtime, newhour, newminutes;
                            std::cout << " > Input the hour of the event: ";
                            getline(cin, newhour, '\n');
                            std::cout << " > Input the minutes of the event: ";
                            getline(cin, newminutes, '\n');
                            this->validator.validateTime(newhour, newminutes);
                            if (stoi(newhour) < 10)
                                newhour = "0" + newhour;
                            if (stoi(newminutes) < 10)
                                newminutes = "0" + newminutes;
                            newtime = newhour + ":" + newminutes;
                            Event newElem{ oldElem.getTitle(), oldElem.getDescription(), oldElem.getDate(), newtime, oldElem.getNumberOfPeople(), oldElem.getLink() };
                            this->service.updateEventService(oldElem, newElem);
                            std::cout << "  Event updated successfully!" << std::endl;
                        }
                        catch (RepositoryException& rerr)
                        {
                            std::cout << rerr.what() << std::endl;
                        }
                        catch (ValidatorException& verr)
                        {
                            std::cout << verr.what() << std::endl;
                        }
                        catch (FileException& ferr)
                        {
                            std::cout << ferr.what() << std::endl;
                        }
                    }
                    else
                        if (option == "people")
                        {
                            try
                            {
                                std::string people;
                                int newpeople;
                                std::cout << " > Input the number of people attending the event: ";
                                getline(cin, people, '\n');
                                trimWhiteSpaces(people);
                                this->validator.validateEventNrOfPeople(people);
                                newpeople = stoi(people);
                                Event newElem{ oldElem.getTitle(), oldElem.getDescription(), oldElem.getDate(), oldElem.getTime(), newpeople, oldElem.getLink() };
                                this->service.updateEventService(oldElem, newElem);
                                std::cout << "  Event updated successfully!" << std::endl;
                            }
                            catch (RepositoryException& rerr)
                            {
                                std::cout << rerr.what() << std::endl;
                            }
                            catch (ValidatorException& verr)
                            {
                                std::cout << verr.what() << std::endl;
                            }
                            catch (FileException& ferr)
                            {
                                std::cout << ferr.what() << std::endl;
                            }
                        }
                        else
                            if (option == "link")
                            {
                                try
                                {
                                    std::string newlink;
                                    std::cout << " > Input the link of the event: ";
                                    getline(cin, newlink, '\n');
                                    trimWhiteSpaces(newlink);
                                    transform(newlink.begin(), newlink.end(), newlink.begin(), ::tolower);
                                    this->validator.validateEventLink(newlink);
                                    Event newElem{ oldElem.getTitle(), oldElem.getDescription(), oldElem.getDate(), oldElem.getTime(), oldElem.getNumberOfPeople(), newlink };
                                    this->service.updateEventService(oldElem, newElem);
                                    std::cout << "  Event updated successfully!" << std::endl;
                                }
                                catch (RepositoryException& rerr)
                                {
                                    std::cout << rerr.what() << std::endl;
                                }
                                catch (ValidatorException& verr)
                                {
                                    std::cout << verr.what() << std::endl;
                                }
                                catch (FileException& ferr)
                                {
                                    std::cout << ferr.what() << std::endl;
                                }
                            }
                            else
                                throw UserInputException("  Input error: you can only update the title, description, date, time, people or link!");


    }
    catch (RepositoryException& rerr)
    {
        std::cout << rerr.what() << std::endl;
    }
    catch (ValidatorException& verr)
    {
        std::cout << verr.what() << std::endl;
    }
    catch (FileException& ferr)
    {
        std::cout << ferr.what() << std::endl;
    }
}

void UI::listEventsAdminUI()
{
    int repolength = this->service.getRepo().getRepoSize();
    if (repolength == 0)
    {
        std::cout << "  There are no events in the database!" << std::endl;
        return;
    }

    std::cout << "   > Events list:" << std::endl;
    for (auto& event : this->service.getRepo().getEvents())
        std::cout << std::endl << event.toString();
}

void UI::addUserUI(const Event& e)
{
    try
    {
        this->service.addEventToUserList(e);
        std::cout << "  Event added successfully!" << std::endl;
    }
    catch (RepositoryException& rerr)
    {
        std::cout << rerr.what() << std::endl;
    }
    catch (ValidatorException& verr)
    {
        std::cout << verr.what() << std::endl;
    }
    catch (FileException& ferr)
    {
        std::cout << ferr.what() << std::endl;
    }
}

std::vector<Event> UI::filterRepoUI(std::string& month)
{
    Repository currentRepo = this->service.getRepo();
    std::vector<Event> filteredRepo = this->service.getRepo().getEvents();
    if (stoi(month) == 0)
    {
        Service::sortRepoByDate(filteredRepo);
    }
    else
    {
        filteredRepo = this->service.filterRepoByMonth(stoi(month));
        if (filteredRepo.size() > 0)
            Service::sortRepoByDate(filteredRepo);
    }
    return filteredRepo;
}

void UI::parseAndAddUserUI()
{
    std::string month;
    std::cout << " > Input the month of the event, 0 for no month: ";
    getline(cin, month, '\n');
    try
    {
        this->validator.validateEventMonth(month);
    }
    catch (ValidatorException& verr)
    {
        std::cout << verr.what() << std::endl;
    }

    std::vector<Event> filteredRepo = UI::filterRepoUI(month);
    std::string userCommand;
    int repolength = filteredRepo.size();
    if (repolength == 0)
    {
        std::cout << "  There are no events in given month in the database!" << std::endl;
        return;
    }
    int counter = 0;
    int index = 0;
    int running = 1;
    while (running)
    {
        counter++;
        Event e = filteredRepo[index];
        std::cout << std::endl << "Current event: " << std::endl;
        std::cout << e.toString() << std::endl;

        system(std::string("start " + e.getLink()).c_str());
        ///system(std::string("xdg-open " + e.getLink()).c_str());

        UI::parseMenu();
        std::string command;

        command = UI::readUserCommand();
        if (command == "exit")
        {
            running = 0;
        }
        else
            if (command == "add")
            {
                UI::addUserUI(e);
                filteredRepo = UI::filterRepoUI(month);  
                index += 1; 
                if (index == repolength)
                    index = 0;   
            }
            else
                if (command == "next")
                {
                    index += 1;
                    if (index == repolength)
                        index = 0;   
                }
                else
                {
                    std::cout << "  Invalid command! It can only be add, next or exit!" << std::endl;
                }
    }
}

void UI::deleteUserUI()
{
    std::string title, date, day, month, year;
    std::cout << " > Input the title of the event: ";
    getline(cin, title, '\n');
    trimWhiteSpaces(title);
    transform(title.begin(), title.end(), title.begin(), ::tolower);
    std::cout << " > Input the day of the event: ";
    getline(cin, day, '\n');
    std::cout << " > Input the month of the event: ";
    getline(cin, month, '\n');
    std::cout << " > Input the year of the event: ";
    getline(cin, year, '\n');

    try
    {
        this->validator.validateTitleDate(title, day, month, year);
        if (stoi(day) < 10)
            day = "0" + day;
        if (stoi(month) < 10)
            month = "0" + month;
        date = day + "/" + month + "/" + year;
        this->service.deleteEventUserService(title, date);
        std::cout << "  Event deleted successfully!" << std::endl;
    }
    catch (RepositoryException& rerr)
    {
        std::cout << rerr.what() << std::endl;
    }
    catch (ValidatorException& verr)
    {
        std::cout << verr.what() << std::endl;
    }
    catch (FileException& ferr)
    {
        std::cout << ferr.what() << std::endl;
    }
}

void UI::listEventsUserUI()
{
    int repolength = this->service.getUserRepo()->getRepoSize();
    if (repolength == 0)
    {
        std::cout << "  There are no events in your list!" << std::endl;
        return;
    }
    std::cout << "   > List of events you want to attend:" << std::endl;
    for (auto& event : this->service.getUserRepo()->getUserEvents())
        std::cout << std::endl << event.toString();
}

void UI::openAppEventsList()
{
    this->service.getUserRepo()->openInApp();
}

void UI::saveEventsList()
{
    this->service.getUserRepo()->writeToFile();
}

void UI::populate()
{
    this->service.addEventService("carrer fest", "career event in cluj-napoca", "29/10/2022", "10:30", 5000, "https://www.targuldecariere.ro/cluj-global");
    this->service.addEventService("transylvania international film festival", "film festival in cluj-Napoca", "17/06/2022", "17:00", 3000, "https://tiff.ro/en");
    this->service.addEventService("color run", "marathon in cluj-Napoca", "07/05/2022", "10:00", 2000, "https://www.thecolorrun.ro/evenimente/cluj-napoca/");
    this->service.addEventService("sports festival", "festival in cluj-napoca", "09/06/2022", "09:00", 10000, "https://www.sportsfestival.com/");
    this->service.addEventService("untold", "music festival in cluj-napoca", "04/08/2022", "16:00", 650000, "https://untold.com");
    this->service.addEventService("festival de cannes", "film festival in france", "17/05/2022", "20:00", 35000, "https://www.festival-cannes.com/en");
    this->service.addEventService("european games", "sports competition in poland", "21/06/2023", "14:00", 250000, "https://www.european-games.org/european-games-2023/");
    this->service.addEventService("electric castle", "music festival in cluj-napoca", "13/07/2022", "18:00", 45000, "https://electriccastle.ro/");
    this->service.addEventService("st. patrick's day", "parade in ny", "17/03/2022", "8:00", 350000, "https://www.nycstpatricksparade.org/");
    this->service.addEventService("venice international film festival", "film festival in italy", "31/08/2022", "19:45", 4000, "https://www.labiennale.org/en/cinema/2022");
    this->service.addEventService("transylvania open", "tennis tournament in cluj-napoca", "23/10/2022", "14:30", 15000, "https://transylvaniaopen.ro/ro/");
    this->service.addEventService("special olympics world games", "sports competition in berlin", "17/07/2024", "13:30", 80000, "https://www.specialolympics.org");
    this->service.addEventService("indagra food", "cooking festival in bucharest", "26/10/2022", "12:00", 10000, "https://www.indagra-food.ro/ro/");
    this->service.addEventService("oktoberfest", "german festival in munich", "25/09/2022", "11:00", 125000, "https://www.oktoberfest.de/en");
    this->service.addEventService("coachella", "music festival in california", "15/04/2022", "15:50", 500000, "https://www.coachella.com/");
}

void UI::adminMenu()
{
    std::cout << std::endl;
    std::cout << " >  Welcome to administrator mode!" << std::endl;
    std::cout << " >  You may choose to:" << std::endl;
    std::cout << " >      (add) Add a new event" << std::endl;
    std::cout << " >      (delete) Delete an event" << std::endl;
    std::cout << " >      (update) Update an event" << std::endl;
    std::cout << " >      (list) Display all events" << std::endl;
    std::cout << " >      (mode) Switch to user mode" << std::endl;
    std::cout << " >      (exit) Exit the application" << std::endl;
}

void UI::userMenu()
{
    std::cout << std::endl;
    std::cout << " >  Welcome to user mode!" << std::endl;
    std::cout << " >  You may choose to:" << std::endl;
    std::cout << " >      (parse) See the events in the database for a given month, one by one and choose to add events to your list" << std::endl;
    std::cout << " >      (delete) Delete an event from your list" << std::endl;
    std::cout << " >      (list) Display all events from your list" << std::endl;
    std::cout << " >      (save) Save all events from your list to given file" << std::endl;
    std::cout << " >      (display) Open csv/html events list in app" << std::endl;
    std::cout << " >      (mode) Switch to admin mode" << std::endl;
    std::cout << " >      (exit) Exit the application" << std::endl;
}

void UI::parseMenu()
{
    std::cout << std::endl;
    std::cout << " >  You may choose to:" << std::endl;
    std::cout << " >      (add) Add current event to your list" << std::endl;
    std::cout << " >      (next) Move on to the next event in the database" << std::endl;
    std::cout << " >      (exit) Exit parse mode and return to user mode" << std::endl;
}

void UI::startUI()
{
    std::cout << "\n Welcome to Life After School!" << std::endl;
    std::cout << " In order to update the database or see all the events, you must be in administrator mode!" << std::endl;
    std::cout << " In order to create a list with the events that you are interested in, you must be in user mode!" << std::endl;
    std::cout << " Type 'admin' for admin mode, 'user' for user mode!" << std::endl;

    //UI::populate();
    int running = 1;
    while (running)
    {
        std::string option;
        std::cout << " > Run as (admin/user): ";
        std::getline(std::cin, option, '\n');
        option.erase(remove(option.begin(), option.end(), ' '), option.end());
        transform(option.begin(), option.end(), option.begin(), ::tolower);
        if (option == "admin")
        {
            runAdmin();
            running = 0;
        }
        else
            if (option == "user")
            {
                runUser();
                running = 0;
            }
            else
                std::cout << " Invalid mode! It can only be admin or user!" << std::endl;
    }
}

void UI::runAdmin()
{
    int running = 1;
    while (running)
    {
        UI::adminMenu();
        std::string command;
        command = UI::readUserCommand();
        if (command == "exit")
        {
            running = 0;
        }
        else
            if (command == "add")
            {
                try
                {
                    UI::addEventAdminUI();
                }
                catch (RepositoryException& rerr)
                {
                    std::cout << rerr.what() << std::endl;
                }
                catch (ValidatorException& verr)
                {
                    std::cout << verr.what() << std::endl;
                }
                catch (FileException& ferr)
                {
                    std::cout << ferr.what() << std::endl;
                }
                catch (UserInputException& uierr)
                {
                    std::cout << uierr.what() << std::endl;
                }
            }
            else
                if (command == "delete")
                {
                    try
                    {
                        UI::deleteEventAdminUI();
                    }
                    catch (RepositoryException& rerr)
                    {
                        std::cout << rerr.what() << std::endl;
                    }
                    catch (ValidatorException& verr)
                    {
                        std::cout << verr.what() << std::endl;
                    }
                    catch (FileException& ferr)
                    {
                        std::cout << ferr.what() << std::endl;
                    }
                    catch (UserInputException& uierr)
                    {
                        std::cout << uierr.what() << std::endl;
                    }
                }
                else
                    if (command == "update")
                    {
                        try
                        {
                            UI::updateEventAdminUI();
                        }
                        catch (RepositoryException& rerr)
                        {
                            std::cout << rerr.what() << std::endl;
                        }
                        catch (ValidatorException& verr)
                        {
                            std::cout << verr.what() << std::endl;
                        }
                        catch (FileException& ferr)
                        {
                            std::cout << ferr.what() << std::endl;
                        }
                        catch (UserInputException& uierr)
                        {
                            std::cout << uierr.what() << std::endl;
                        }
                    }
                    else
                        if (command == "list")
                        {
                            UI::listEventsAdminUI();
                        }
                        else
                            if (command == "mode")
                            {
                                running = 0;
                                runUser();
                            }
                            else
                            {
                                std::cout << "  Invalid command! It can only be add, delete, update, list, mode or exit!" << std::endl;

                            }
    }
}

void UI::runUser()
{
    int running = 1;
    while (running)
    {
        UI::userMenu();
        std::string command;
        command = UI::readUserCommand();
        if (command == "exit")
        {
            running = 0;
        }
        else
            if (command == "parse")
            {
                try
                {
                    UI::parseAndAddUserUI();
                }
                catch (RepositoryException& rerr)
                {
                    std::cout << rerr.what() << std::endl;
                }
                catch (ValidatorException& verr)
                {
                    std::cout << verr.what() << std::endl;
                }
                catch (FileException& ferr)
                {
                    std::cout << ferr.what() << std::endl;
                }
                catch (UserInputException& uierr)
                {
                    std::cout << uierr.what() << std::endl;
                }
            }
            else
                if (command == "delete")
                {
                    try
                    {
                        UI::deleteUserUI();
                    }
                    catch (RepositoryException& rerr)
                    {
                        std::cout << rerr.what() << std::endl;
                    }
                    catch (ValidatorException& verr)
                    {
                        std::cout << verr.what() << std::endl;
                    }
                    catch (FileException& ferr)
                    {
                        std::cout << ferr.what() << std::endl;
                    }
                    catch (UserInputException& uierr)
                    {
                        std::cout << uierr.what() << std::endl;
                    }
                }
                else
                    if (command == "list")
                    {
                        UI::listEventsUserUI();
                    }
                    else
                        if (command == "save")
                        {
                            UI::saveEventsList();
                        }
                        else
                            if (command == "display")
                            {
                                UI::openAppEventsList();
                            }
                            else
                                if (command == "mode")
                                {
                                    running = 0;
                                    runAdmin();
                                }
                                else
                                {
                                    std::cout << "  Invalid command! It can only be parse, delete, list, display, save, mode or exit!" << std::endl;
                                }
        this->service.getUserRepo()->writeToFile();
    }

}

void UI::trimWhiteSpaces(std::string& s)
{
    char str[101] = "";
    strcpy(str, s.c_str());
    int i = 0;
    while (i < strlen(str))
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else
            break;
    }

    i = (int)strlen(str) - 1;
    while (i > 0)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        else
            break;
    }
    str[i + 1] = '\n';
    s.copy(str, strlen(str), 0);
}
