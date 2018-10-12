#include "DonationHandler.h"

void DonationHandler::CheckDonationFile()
{
	//This function checks for the donation file and creates it if it does not exist
	if(!std::fstream(this->donationFilePath))
	{
		std::ofstream file("donations.txt", std::ios::trunc);
		file << 0;
		for(int i=0; i<10; i++)
		{
			file << " ";
		}
	}
}

void DonationHandler::Convert(wchar_t *name, wchar_t *amount)
{
	//Use this function to convert and set the name and amount variables
	std::wstring wsName(name);

	std::string sName(wsName.begin(), wsName.end());
	double dAmount = wcstod(amount, NULL);

	//Passing converted values back to class
	this->name = sName;
	this->amount = dAmount;
}

void DonationHandler::CurrentTotal()
{
	std::string currentTotal{};

	std::fstream file(this->donationFilePath, std::ios::in | std::ios::out);
	file >> currentTotal;
	file.close();

	double tempTotal = std::stod(currentTotal, NULL);
	this->total = tempTotal;
}

void DonationHandler::SetTotalToGuiFormat(HWND hwnd)
{
	CurrentTotal();
	std::stringstream total;
	total << this->total;
	SetWindowText(hwnd, total.str().c_str());
}


DonationHandler::DonationHandler()
{
	CheckDonationFile();
}

DonationHandler::~DonationHandler()
{
}

std::string DonationHandler::CallCurrentName()
{
	return std::string(this->name);
}

double DonationHandler::CallCurrentAmount()
{
	return this->amount;
}

double DonationHandler::CallCurrentTotal()
{
	return this->total;
}

void DonationHandler::SetCurrentName(std::string name)
{
	this->name = name;
}

std::string DonationHandler::GetDonationFilePath()
{
	return this->donationFilePath;
}

char * DonationHandler::GetFilePathChar()
{
	std::string stringPath = this->donationFilePath;
	char *charPath = new char[stringPath.length() + 1];
	strcpy_s(charPath, stringPath.length() + 1, stringPath.c_str());
	return charPath;
}

void DonationHandler::SetDonationFilePath(char path[100])
{
	this->donationFilePath = path;
}

void DonationHandler::AddDonation()
{
	////Run the file check here
	CheckDonationFile();

	//Find current total
	CurrentTotal();

	//Opening file
	std::fstream file(this->donationFilePath, std::ios::in | std::ios::out);

	//Updating total
	this->total += this->amount;
	file << this->total;
	file.close();

	//Adding to file
	file.open(this->donationFilePath, std::ios::in | std::ios::out | std::ios::app);
	file << std::endl << this->name << " $" << this->amount;
	file.close();
}
