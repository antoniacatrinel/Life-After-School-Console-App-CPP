#pragma once
#include "Service.h"
#include "Validation.h"

class UI {

private:
    Service& service;
    Validator validator;

public:
    /// <summary>
    /// Constructor for the UI class
    /// </summary>
    /// <param name="srv">the service</param>
    /// <param name="valid">he validator</param>
    explicit UI(Service& srv, Validator valid);

    /// <summary>
    /// Displays the admin menu to the console
    /// </summary>
    static void adminMenu();

    /// <summary>
    /// Displays the user menu to the console
    /// </summary>
    static void userMenu();

    /// <summary>
    /// Displays the parsing user menu to the console
    /// </summary>
    static void parseMenu();

    /// <summary>
    /// Menu option for adding an event
    /// </summary>
    void addEventAdminUI();

    /// <summary>
    /// Menu option for deleting an event
    /// </summary>
    void deleteEventAdminUI();

    /// <summary>
    /// Menu option for updating an event
    /// </summary>
    void updateEventAdminUI();

    /// <summary>
    /// Menu option for displaying the list of events
    /// </summary>
    void listEventsAdminUI();

    /// <summary>
    /// Filters the events by month
    /// </summary>
    std::vector<Event> filterRepoUI(std::string& month);

    /// <summary>
    /// Menu option for parsing user's list of events
    /// </summary>
    void parseAndAddUserUI();

    /// <summary>
    /// Menu option for adding an event to the user list
    /// </summary>
    void addUserUI(const Event& e);

    /// <summary>
    /// Menu option for deleting an event from the user list
    /// </summary>
    void deleteUserUI();

    /// <summary>
    /// Menu option for displaying the user's list of events
    /// </summary>
    void listEventsUserUI();

    /// <summary>
    /// Menu option for opening the user's list of events in an app
    /// </summary>
    void openAppEventsList();

    /// <summary>
    /// Menu option for saving the user's list of events
    /// </summary>
    void saveEventsList();

    /// <summary>
    /// Loop for admin mode
    /// </summary>
    void runAdmin();

    /// <summary>
    /// Loop for user mode
    /// </summary>
    void runUser();

    /// <summary>
    /// Main loop of the app
    /// </summary>
    void startUI();

private:
    /// <summary>
    /// Populates the inmemory repository
    /// </summary>
    void populate();

    /// <summary>
    /// Reads a command from the user
    /// </summary>
    std::string readUserCommand();

    /// <summary>
    /// Trims user command
    /// </summary>
    void trimWhiteSpaces(std::string& s);
};
