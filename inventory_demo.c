#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void update_image(char* data, int size_of_data, int width, const int selectedIndex, const int index_to_swap) 
{
	system("cls");

	printf("--------------INVENTORY DEMO--------------\n");
	//print data
	for (int i = 0; i < size_of_data; i++) {
		//highlight for selected item
		if (i == selectedIndex)
			printf("\033[3;47;35m|%c|\033[0m", data[i]);
		else 
			//highlight for item for swap
			if(i == index_to_swap)
				printf("\033[3;100;30m|%c|\033[0m", data[i]);
			//regular item
			else
				printf("|%c|", data[i]);
		//break of line when reaching max amount of items in the row
		if (i != 0 && (i + 1) % width == 0) printf("\n");
	}

	//helper
	if (index_to_swap != -1)
		printf("\n\nTo exit swap mode press <Enter> to confirm swap or <Esc> to cancel\n");
	else
		printf("\n\nTo enter swap mode press <Enter>\n");	
}

void read_arrow_keys(int* selectedIndex, int size, int width)
{
	int key_code = _getch();
	switch (key_code) {
		case 75:
			//left
			if (*selectedIndex - 1 < 0)
				*selectedIndex = size - 1;
			else (* selectedIndex)--;
			break;
		case 72:
			//up
			if (*selectedIndex >= width)
				*selectedIndex -= width;
			else
				while (*selectedIndex + width < size)
					*selectedIndex += width;
			break;
		case 77:
			//right
			if (*selectedIndex + 1 >= size)
				*selectedIndex = 0;
			else (*selectedIndex)++;
			break;
		case 80:
			//down
			if (*selectedIndex + width < size)
				*selectedIndex += width;
			else
				while (*selectedIndex - width >= 0)
					(*selectedIndex) -= width;
			break;
	}
}

void swap_items(char* data, int selectedIndex, int index_to_swap)
{
	char temp = data[selectedIndex];
	data[selectedIndex] = data[index_to_swap];
	data[index_to_swap] = temp;
}

char* gen_inventory(int size)
{
	char* data = (char*)malloc(sizeof(char) * size);
	if (data == NULL) 
		return NULL;

	for (int i = 0; i < size; i++) {
		data[i] = i + 97;
	}
	return data;
}

int main()
{
	//predetermined data
	int width = 4;
	int size = 34;
	int selectedIndex = 0;
	int index_to_swap = -1;

	char* data = gen_inventory(size);

	//display inventory
	update_image(data, size, width, selectedIndex, index_to_swap);

	//continiously check for user input
	while (1)
	{
		if (_kbhit()) {
			int ch = getch();
			switch (ch) {
				//arrow keys input starts with a character with code 224, 
				//after that there is the keycode for the arrow key, 
				//thats why there's two _getch(), one here and one in read_arrow_keys
				case 224:
					read_arrow_keys(&selectedIndex, size, width);
					update_image(data, size, width, selectedIndex, index_to_swap);
					break;
				//enter
				case 13:
					if (index_to_swap != -1)
					{
						swap_items(data, selectedIndex, index_to_swap);
						index_to_swap = -1;
					}
					else index_to_swap = selectedIndex;
					update_image(data, size, width, selectedIndex, index_to_swap);
					break;
				//esc
				case 27:
					index_to_swap = -1;
					if(index_to_swap >= 0)
						update_image(data, size, width, selectedIndex, index_to_swap);
					break;
				}
		}
		else continue;
	}
	return 0;
}