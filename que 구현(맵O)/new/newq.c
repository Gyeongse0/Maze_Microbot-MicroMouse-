#include <stdio.h>
#include <stdlib.h>

#define QUE_SIZE 256

int maze[256] = { 0, };
int maze_reset = 0;
int Que_reset = 0;
int now = 0x78;
int now_search = 0x00;
int maze_num = 4;
int Que[256] = { 0, };
int k = 0;
int y = 0;

unsigned char wall_dir[256] = { 14,  8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  9,
15,  5, 12, 10,  8,  8,  8,  8, 10, 10, 10, 10, 10, 10,  9,  5,
12,  3,  5, 14,  3,  5,  5,  5, 12,  9, 14,  8, 10, 10,  1,  5,
 5, 12,  2, 11, 14,  3,  5,  7,  4,  1, 13,  5, 12, 10,  1,  5,
 5,  5, 14, 10,  8, 10,  3, 14,  2,  3,  5,  5,  6, 10,  1,  5,
 5,  6, 10,  9,  6, 10, 10, 10,  9, 14,  2,  0, 10, 10,  1,  5,
 5, 12,  9,  4,  8,  9, 13, 15,  6,  8,  9,  5, 12,  9,  5,  5,
 5,  5,  7,  5,  5,  5,  4,  8,  9,  5,  5,  5,  5,  6,  1,  5,
 5,  4, 10,  1,  5,  5,  5,  6,  3,  7,  5,  6,  3, 13,  5,  5,
 5,  5, 13,  7,  5,  6,  2,  9, 12,  9,  5, 12,  9,  5,  5,  5,
 5,  4,  2, 10,  3, 13, 12,  3,  5,  5,  5,  4,  1,  6,  1,  5,
 5,  4, 10, 10, 10,  2,  3, 13,  5,  5,  5,  4,  1, 12,  3,  5,
 5,  5, 13, 12, 10,  8, 10,  3,  5,  5,  5,  6,  3,  6,  9,  5,
 5,  5,  5,  5, 14,  2, 10, 10,  1,  6,  2, 10,  9, 12,  3,  5,
 5,  6,  2,  2, 10, 11, 14, 10,  2, 10, 10, 10,  3,  6,  9,  5,
 6, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  2,  3 };


void Push(int nData) {

	int nCount = 0;

	for (int i = 0; i < QUE_SIZE; i++) {

		if (Que[i] == NULL) {		//배열이 안 비었으면 ncount++ , 비었으면 나가기

			break;

		}

		nCount++;

	}

	if (nCount != QUE_SIZE) {		// ncount가 que_size랑 다르면 ==0,1,2,3,4,이면  파라미터를 ncount번째 배열에 넣어줌

		Que[nCount] = nData;

	}

}



int Pop() {
	int nCount = 0;
	int nResult = 0;
	for (int i = 0; i < QUE_SIZE; i++) {		//배열0-4가 null이 아니면 루프 나감, null이면 ncount++

		if (Que[i] != NULL)
		{
			break;
		}
		nCount++;
	}

	if (nCount != QUE_SIZE) {		//ncount가 256가 아니면 ~일때 해당 배열값을 nresult에 넣고 null로 초기화

		nResult = Que[nCount];

		Que[nCount] = NULL;

	}

	for (int i = 0; i < QUE_SIZE; i++) {		//뒤까지 다음 배열값을 앞 배열에 넣음.

		Que[i] = Que[i + 1];

	}

	Que[QUE_SIZE - 1] = NULL;		//null값을 끝 배열에 넣음

	return nResult;		//nresult값을 반환

}


int main(void) {



	for (Que_reset = 0; Que_reset < 256; Que_reset++) {
		Que[Que_reset] = '\0';
	}

	Que[0] = 0x78;
	Que[1] = 0x77;
	Que[2] = 0x87;
	Que[3] = 0x88;		//큐를 nullㅎ=만들고 4개값넣어주기 --> push가 널이어야 해당요소에 들어감

	
	for (maze_reset = 0; maze_reset < 256; maze_reset++) {
		maze[maze_reset] = 255;
	}
	
	maze[0x78] = 0;
	maze[0x77] = 0;
	maze[0x87] = 0;
	maze[0x88] = 0;		//맵무게값을 초기화
	

	while (1) {
		
		if (maze[now - 0x10] == 255 ) {		//8   
			if (wall_dir[now] & 8)
			{
			}
			else {
				Push(now - 0x10);
				maze[now - 0x10] = (maze[now] + 1);
			}
		}

		if (maze[now + 0x01] == 255) {			//1	((maze[now + 0x01] == 255) && (wall_dir[now] & 1) )
			if (wall_dir[now] & 1)
			{
			}
			else {
				Push(now + 0x01);
				maze[now + 0x01] = (maze[now] + 1);
			}
		}

		if (maze[now + 0x10] == 255) {			//2	((maze[now + 0x10] == 255) && (wall_dir[now] & 2) )
			if (wall_dir[now] & 2)
			{
			}
			else {
				Push(now + 0x10);
				maze[now + 0x10] = (maze[now] + 1);
			}
		}

		if (maze[now - 0x01] == 255) {			//4
			if (wall_dir[now] & 4)
			{
			}
			else {
				Push(now - 0x01);
				maze[now - 0x01] = (maze[now] + 1);
			}
		}
		

		now = Pop();

		k++;
		
		if (Que[0] == '\0') //&& (maze[0xf0] != 255) && (maze[0x0f] != 255) && (maze[0xff] != 255)
		{
			break;
		}
		

		/*
		if ((maze[0xf0] != 255) && (maze[0x0f] != 255) && (maze[0xff] != 255) && (maze[0x00] != 255))
		{
			break;
		}
		*/
	}
	
	for (y = 0; y < 256; y++) {
		if ((y % 16) == 0) {
			printf(" \n ", maze[y]);

		}
		printf("%d    ", maze[y]);

	}



	return 0;

}