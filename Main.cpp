#include "Header.h"
#include <Windows.h>
#include <ctime> // ��� �������


int main()
{
	srand((unsigned)time(NULL));
	char** player = nullptr;
	char** bot = nullptr;
	menu(player, bot);

}