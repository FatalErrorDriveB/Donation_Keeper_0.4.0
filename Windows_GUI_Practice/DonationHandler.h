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

	//Public Functions
	void AddDonation();
	void ShowDonationList();
	void Convert(wchar_t*, wchar_t*);
	void CurrentTotal();
	void SetTotalToGuiFormat();
	void UpdateList();
};