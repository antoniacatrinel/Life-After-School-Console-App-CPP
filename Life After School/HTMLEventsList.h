#pragma once
#include <string>
#include <vector>
#include "RepositoryUser.h"

class HTMLEventsList : public RepositoryUser {

public:
	/// <summary>
	/// Constructor for HTMLEventsList class
	/// </summary>
	HTMLEventsList();

	/// <summary>
	/// Destructor for CSVEventsList class
	/// </summary>
	~HTMLEventsList();

	/// <summary>
	/// Overrides the write to file function from the repository
	/// </summary>
	void writeToFile() override;

	/// <summary>
	/// Overrides the open in app function
	/// </summary>
	void openInApp() override;
};
