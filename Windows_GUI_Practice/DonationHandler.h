#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>

class DonationHandler
{
private:
	std::string name{};
	double amount{};
	double total{};
	std::string donationFilePath = "donations.txt";

	void CheckDonationFile();
	

protected:

public:

	//Constructors & Destructor
	DonationHandler();
	virtual ~DonationHandler();

	//Getters and setters
	std::string CallCurrentName();
	double CallCurrentAmount();
	double CallCurrentTotal();
	void SetCurrentName(std::string);
	std::string GetDonationFilePath();
	char* GetFilePathChar();
	void SetDonationFilePath(char path[100]);

	//Public Functions
	void AddDonation();
	void Convert(wchar_t*, wchar_t*);
	void CurrentTotal();
	LPCWSTR SetTotalToGuiFormat();
};