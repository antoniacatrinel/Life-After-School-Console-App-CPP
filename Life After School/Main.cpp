#include "Ui.h"
#include "Service.h"
#include "InmemoryRepository.h"
#include "FileRepository.h"
#include "CSVEventsList.h"
#include "HTMLEventsList.h"
#include "Tests.h"
#include <string>
#include <iostream>
#include <crtdbg.h>

int main()
{
    Tests::test_genericSort();
    Tests::run_all_tests();

    std::string filename, filenameUserEvents, fileOption;

    std::cout << "Please input name of file from which you wish to load and save the entities: ";
    getline(std::cin, filename, '\n');

    std::cout << "Do you wish to save your event list in a csv or html file? ";
    getline(std::cin, fileOption, '\n');

    if (fileOption == "csv" || fileOption == "html")
    {
        try
        {
            FileRepository fileRepo{ filename };
            RepositoryUser* eventsList;

            if (fileOption == "csv")
                eventsList = new CSVEventsList();
            else
                eventsList = new HTMLEventsList();

            Service srv{ fileRepo, eventsList };
            Validator valid{};
            UI ui{ srv, valid };
            ui.startUI();
            delete eventsList;
        }
        catch (FileException& ferr)
        {
            std::cout << ferr.what();
        }
    }
    else
        std::cout << "Invalid file type! It can only be csv or html!" << std::endl;
  
    _CrtDumpMemoryLeaks();
    return 0;
}
