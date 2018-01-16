#include <Windows.h>
#include <iostream>
#include "cGame.h"

using namespace std;

#define GAME_ADDR 0x0056BB04 // wrt popcapgame1.exe
int main()
{
	LPVOID lpData = new LPVOID[sizeof(cGame)];
	DWORD dwPID, dwBytesRead, dwBytesWritten;

	cout << "Enter process id: "; cin >> dwPID;
	HANDLE hProcess = OpenProcess(GENERIC_READ | GENERIC_WRITE, FALSE, dwPID);
	
	if (hProcess != NULL)
	{
		while (!GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(GAME_ADDR), lpData, sizeof(cGame), &dwBytesRead))
			{	
				cGame *pGame = static_cast<cGame*>(lpData);
				cout << "Lives: " << pGame->dwLives << endl;

				if (pGame->dwLives == 0)
				{
					pGame->dwLives = 2;
					WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(GAME_ADDR), lpData, sizeof(cGame), &dwBytesWritten);
				}
			}
			Sleep(500);
		}

	}

	if (lpData) delete [] lpData;
	return 0;
}
#pragma once
#include <Windows.h>

class cGame
{
public:
	DWORD dwLives;
	DWORD dwNukes;
	DWORD dwShield;
	DWORD dwSpeedIncreaseUpgrade; 
	DWORD dwGunPowerUpgrade;
	DWORD dwRapidFireUpgrade;
	DWORD dwSpreadShotUpgrade;
	DWORD dwBallShieldUpgrade;
	DWORD dwHomingMissileUpgrade;
	DWORD dwLaserUpgrade;
	DWORD dwMissileUpgrade;
	DWORD dwBurstUpgrade;
	DWORD dwLightningUpgrade;

};
