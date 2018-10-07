////Window API practice
#include <Windows.h>
#include "DonationHandler.h"

//Define All Menu Calls Here
#define File_Menu_AddNewDonation 1
#define Help_Menu_ShowDocumentation 3
#define File_Menu_Exit 5
#define Help_SubMenu_HowToUse 4

//Prototyping
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddControls(HWND);

//Global Variables
HMENU hMenu;
HWND hDonorName;
HWND hAmount;
HWND hTotal;
HWND hDonationList;
DonationHandler *DH = new DonationHandler();

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
	switch (msg)
	{
	case WM_COMMAND:
		switch(wparam)
		{
		case NULL:
			break;
		case File_Menu_Exit:
			DestroyWindow(hwnd);
			break;
		case File_Menu_AddNewDonation:
			//Here is where I'll add my code
			wchar_t DonorName[100];
			wchar_t AmountDonated[100];
			GetWindowTextW(hDonorName, DonorName, 100);
			GetWindowTextW(hAmount, AmountDonated, 100);
			DH->Convert(DonorName, AmountDonated);
			DH->AddDonation();
			SetWindowTextW(hDonorName, L"");
			SetWindowTextW(hAmount, L"");
			SetWindowTextW(hTotal, DH->guiTotal); ////Close but not yet working...
			DH->UpdateList();
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
		AddMenus(hwnd);
		AddControls(hwnd);
		break;

	case WM_DESTROY:
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
	CreateWindowW(L"Static", L"Add New Donation:", 
		WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER,
		10, 20, 350, 65,
		hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Name of Donor: ",
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		20, 40, 150, 20,
		hwnd, NULL, NULL, NULL);
	hDonorName = CreateWindowW(L"Edit", L"John Doe",
		WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER,
		140, 40, 200, 15,
		hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Amount Donated: $",
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		20, 60, 150, 20,
		hwnd, NULL, NULL, NULL);
	hAmount = CreateWindowW(L"Edit", L"0.00",
		WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER,
		145, 60, 200, 15,
		hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Donation Total: $", 
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 
		150, 400, 200, 22, hwnd,
		NULL, NULL, NULL);
	hTotal = CreateWindowW(L"Static", L"0.00",
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		265, 402, 50, 18,
		hwnd, NULL, NULL, NULL);
	CreateWindowW(L"button", L"Add new donation",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		120, 90, 120, 30,
		hwnd, (HMENU)File_Menu_AddNewDonation, NULL, NULL);
	hDonationList = CreateWindowW(L"Static", L"Donation List",
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT | WS_VSCROLL,
		10, 125, 350, 250, hwnd,
		NULL, NULL, NULL);
}