# Life After School Console Application

Lectures, seminars and labs ... school in general must be taken seriously; BUT so must be your social life and leisure time. To manage the latter and be always informed about the interesting events happening in your city you will implement a software application. The application can be used in two modes: administrator and user. When the application is started, it will offer the option to choose the mode.

**Administrator mode:** The application will have a database which holds all the interesting events in your area. You must be able to update the database, meaning: add a new event, delete an event and update the information of an event. Each **Event** has a `title`, a `description`, a `date and time`, a `number of people` who are going and a `link` towards the online resource containing the event. The administrators will also have the option to see all the events in the database.\
**User mode:** A user can create a list with the events that he/she is interested in. The application will allow the user to:
- See the events in the database for a given month (if there is no month given, see all the events, ordered chronologically), one by one. When the user chooses this option, the data of the first event (title, description, date and time, number of people who are going) is displayed, and the event is opened in the browser (e.g. Facebook event).
- If the user wants to participate in the event he/she can choose to add it to his/her events list. When this happens, the number of people who are going to the event increases (for the event in the repository).
- If the event seems uninteresting, the user can choose not to add it to the list and continue to the next. In this case, the information corresponding to the next event is shown, and the user is again offered the possibility to add it to his/her list. This can continue as long as the user wants, as when arriving to the end of the list of events for the given month, if the user chooses next, the application will again show the first event.
- Delete an event from the list. When the user deletes an event from his/her list, the number of people who are going to the event decreases.
- See the list of events the user wants to attend.

***Requirements:***
- Write tests for every non-UI function
- Use STL algorithms wherever possible in your application (e.g. in your filter function you could use copy_if, count_if). Replace all your for loops either with STL algorithms, or with C++11's ranged-based for loop.
- Store data in a text file. When the program starts, entities are read from the file. Modifications made during program execution are stored in the file. Implement this using the iostream library. Create insertion and extraction operators for your entities and use these when reading/writing to files or the console.
- Use exceptions to signal errors:
    - from the repository
    - validation errors – validate your entities using Validator classes
    - create your own exception classes
    - validate program input
- Store your events list in a file. When the application starts, the user should choose the type of file between CSV or HTML. Depending on the type, the application will save the list in the correct format. The CSV file will contain each entity on one line and the attributes will be separated by comma. The HTML file will contain a table, in which each row holds the data of one entity. The columns of the table will contain the names of the data attributes. CSV and HTML files are used to save and display data to the user; they act as program outputs, so data should not be read from them!
- Add a new command, allowing the user to see the list of events.
- Displaying the list means opening the saved file (CSV or HTML) with the correct application (CSV files using Notepad, Notepad++, Microsoft Excel etc. and HTML files using a browser)
- Implement a class template Comparator, which has a pure virtual function, compare, that receives two generic elements; the function return type is bool. Two concrete classes which inherit from Comparator and implement the compare function, in different ways (e.g. ComparatorAscendingByTitle, ComparatorDescendingByAge, etc…)
- Implement a generic sort function, which receives an STL vector and a Comparator (pointer or reference, for polymorphism) and sorts the elements in the vector, according to the compare function in the Comparator.
