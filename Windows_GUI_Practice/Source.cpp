////Window API practice
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "DonationHandler.h"

//Define All Menu Calls Here
#define File_Menu_AddNewDonation 1
#define Help_Menu_ShowDocumentation 3
#define File_Menu_Exit 5
#define Help_SubMenu_HowToUse 4
#define OPEN_FILE_BUTTON 2
#define SHOW_DONATIONS 6

//Prototyping
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddControls(HWND);
void LoadImages();
void AddDonation();
void DisplayDonations(char*);
void OpenFile(HWND);

//Global Variables & Handlers
HMENU hMenu;
HWND hDonorName;
HWND hAmount;
HWND hTotal;
HWND hDonationList;
HWND hLogo;
DonationHandler *DH = new DonationHandler();
HBITMAP logo;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Creating a windows class
	WNDCLASSW wc = { 0 };
	//Defining the class variables
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WndProc; //Defined in a seperate function

	//Registering the window class so that it can be used to make windows
	if(!RegisterClassW(&wc))
	{
		MessageBox(NULL, "Unable to register window class!", "Registration Error", MB_OK);
		return -1;
	}

	//Creating the window!!!!!!
	CreateWindowW(L"myWindowClass", L"Donation Keeper", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL,
		NULL, NULL, NULL);

	//Define message structure
	MSG msg = { 0 };

	//Creating the window loop
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//Variable
	int mb{};

	//Switch crap
	switch (msg)
	{
	case WM_COMMAND:
		switch(wparam)
		{
		case NULL:
			break;
		case File_Menu_Exit:
			mb = MessageBoxW(hwnd, L"Are you sure you want to quit?", L"Conformation", MB_YESNO | MB_ICONQUESTION);
			if(mb == IDYES)
			{
				DestroyWindow(hwnd);
			}
			break;
		case File_Menu_AddNewDonation:
			//Donation setup
			wchar_t DonorName[100];
			wchar_t AmountDonated[100];
			GetWindowTextW(hDonorName, DonorName, 100);
			GetWindowTextW(hAmount, AmountDonated, 100);
			DH->Convert(DonorName, AmountDonated);
			//Check for blank input then add donation
			if(DH->CallCurrentAmount() == 0)
			{
				mb = MessageBoxW(hwnd, L"The amount donated is $0, are you sure you wish to add this?",
					L"Add $0 donation?", MB_YESNO | MB_ICONQUESTION);
				if(mb == IDYES)
				{
					AddDonation();
				} else {
					MessageBoxW(hwnd, L"The donation was not added.", L"Information", MB_OK | MB_ICONINFORMATION);
				}
			} else {
				AddDonation();
			}
			break;
		case OPEN_FILE_BUTTON:
			//Opening donation file code goes here
			OpenFile(hwnd);
			break;
		case SHOW_DONATIONS:
			DisplayDonations(DH->GetFilePathChar());
			break;
		case Help_Menu_ShowDocumentation:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case Help_SubMenu_HowToUse:
			MessageBeep(MB_OK);
			break;
		}
		break;

	case WM_CREATE:
		LoadImages();
		AddMenus(hwnd);
		AddControls(hwnd);
		break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hwnd, msg, wparam, lparam);

	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();
	HMENU helpSubMenu = CreateMenu();

	//hFileMenu
	AppendMenu(hFileMenu, MF_POPUP, OPEN_FILE_BUTTON, "Open donation file");
	AppendMenu(hFileMenu, MF_STRING, File_Menu_Exit, "Exit Program");

	//HelpSubMenus
	AppendMenu(helpSubMenu, MF_STRING, Help_SubMenu_HowToUse, "How To use");
	//hHelpMenu
	AppendMenu(hHelpMenu, MF_POPUP, (UINT_PTR)helpSubMenu, "Show Documentation");

	//hMenu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

	SetMenu(hWnd, hMenu);
}


void AddControls(HWND hwnd) 
{
	//Add new donation lable
	CreateWindowW(L"Static", L"Add New Donation:", 
		WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER,
		10, 20, 350, 65,
		hwnd, NULL, NULL, NULL);
	//Name of doner prefix
	CreateWindowW(L"Static", L"Name of Donor: ",
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		20, 40, 150, 20,
		hwnd, NULL, NULL, NULL);
	//Name of doner
	hDonorName = CreateWindowW(L"Edit", L"Unknown",
		WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER,
		140, 40, 200, 15,
		hwnd, NULL, NULL, NULL);
	//Amount to donate prefix
	CreateWindowW(L"Static", L"Amount Donated: $",
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		20, 60, 150, 20,
		hwnd, NULL, NULL, NULL);
	//Amount to donate
	hAmount = CreateWindowW(L"Edit", L"0.00",
		WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER,
		145, 60, 200, 15,
		hwnd, NULL, NULL, NULL);
	//Donation Total prefix
	CreateWindowW(L"Static", L"Donation Total: $", 
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 
		160, 400, 200, 22, hwnd,
		NULL, NULL, NULL);
	//Donation Total
	hTotal = CreateWindowW(L"Static", L"0.00",
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		275, 402, 50, 18,
		hwnd, NULL, NULL, NULL);
	//Add new donation Button
	CreateWindowW(L"button", L"Add new donation",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		120, 90, 120, 30,
		hwnd, (HMENU)File_Menu_AddNewDonation, NULL, NULL);
	//Donation List Window
	hDonationList = CreateWindowW(L"Static", L"Donation List",
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT | WS_VSCROLL,
		10, 125, 350, 250, hwnd,
		NULL, NULL, NULL);
	//Logo
	hLogo = CreateWindowW(L"Static", NULL, 
		WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_BORDER,
		450, 10, 20, 20, hwnd,
		NULL, NULL, NULL);
	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
	//Show Donation List
	CreateWindowW(L"button", L"Show donation list", 
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 390, 137, 32, hwnd,
		(HMENU)SHOW_DONATIONS, NULL, NULL);
}

void LoadImages() 
{
	logo = (HBITMAP)LoadImageW(NULL, L"logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}


void AddDonation() 
{
	if (DH->CallCurrentName() == "")
	{
		DH->SetCurrentName("Unknown");
	}
	DH->AddDonation();
	SetWindowTextW(hDonorName, L"Unknown");
	SetWindowTextW(hAmount, L"0.00");
	SetWindowTextW(hTotal, DH->SetTotalToGuiFormat()); ////Close but not yet working... AND I DON'T KNOW WHY!!!!!!
}


void OpenFile(HWND hwnd) 
{
	char fileName[100];

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME)); //Sets all ofn elements to 0

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "Text Files\0*.txt\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;

	GetOpenFileName(&ofn);
	DH->SetDonationFilePath(ofn.lpstrFile); //Sends the file path to my Donation Handler class
	DisplayDonations(ofn.lpstrFile);
}


void DisplayDonations(char* path) 
{
	std::ifstream file(path, std::ios::binary | std::ios::beg);
	char *contents = new char[sizeof(file)];
	
	file.ignore(SIZE_MAX, '\n'); //Ignores the first line of text, aka; the total.
	while (!file.eof()) 
	{
		file.getline(contents, 50); //Avarage length of line is 14, 50 is more than safe to use
	}
	file.close();

	SetWindowText(hDonationList, contents);
}