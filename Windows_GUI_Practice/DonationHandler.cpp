#include "DonationHandler.h"

void DonationHandler::CheckDonationFile()
{
	//This function checks for the donation file and creates it if it does not exist
	if(!std::fstream("donations.txt"))
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

	std::fstream file("donations.txt", std::ios::in | std::ios::out);
	file >> currentTotal;
	file.close();

	double tempTotal = std::stod(currentTotal, NULL);
	this->total = tempTotal;
}

void DonationHandler::SetTotalToGuiFormat()
{
	double tempDTotal = this->total;
	wchar_t tempCTotal = (wchar_t)tempDTotal;
	this->guiTotal = (LPCWSTR)tempCTotal;
}

void DonationHandler::UpdateList()
{
	//Copy contents of file to LPCWSTR format and send to the window.
}


DonationHandler::DonationHandler()
{
	CheckDonationFile();
}

DonationHandler::~DonationHandler()
{
}

void DonationHandler::AddDonation()
{
	////Run the file check here
	CheckDonationFile();

	//Find current total
	CurrentTotal();

	//Opening file
	std::fstream file("donations.txt", std::ios::in | std::ios::out);

	//Updating total
	this->total += this->amount;
	file << this->total;
	file.close();

	//Adding to file
	file.open("donations.txt", std::ios::in | std::ios::out | std::ios::app);
	file << std::endl << this->name << " $" << this->amount;
	file.close();
}

void DonationHandler::ShowDonationList()
{
}
