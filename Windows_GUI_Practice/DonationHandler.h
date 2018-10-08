#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

class DonationHandler
{
private:
	std::string name{};
	double amount{};
	double total{};

	void CheckDonationFile();
	

protected:

public:
	LPCWSTR guiTotal{};

	//Constructors & Destructor
	DonationHandler();
	virtual ~DonationHandler();

	//Getters and setters
	std::string CallCurrentName();
	double CallCurrentAmount();
	double CallCurrentTotal();
	void SetCurrentName(std::string);

	//Public Functions
	void AddDonation();
	void ShowDonationList();
	void Convert(wchar_t*, wchar_t*);
	void CurrentTotal();
	void SetTotalToGuiFormat();
	void UpdateList();
};