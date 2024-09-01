#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define wall_len 100
#define ball_home_len 50


void game_Clear(void)
{
	system("cls");
}
/*콘솔 창 비우는 함수*/


void game_GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/*커서 좌표 이동 함수*/


void game_SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
	if (_BgColor > 15 || _TextColor > 15) return;

	unsigned short ColorNum = (_BgColor << 4) | _TextColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}
/*글자, 배경생 변경 함수*/


void game_SetCursor(BOOL _bShow)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = _bShow;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
/*커서 숨기는 함수*/


void keyMove(char enter_key, int* x, int* y)// 매개변수 x,y값을 바꾸기 위해 포인터로
{
	if (enter_key == 'w'|| enter_key == 'W') {
		(*y)--;
	}
	if (enter_key == 's'|| enter_key == 'S') {
		(*y)++;
	}
	if (enter_key == 'a'|| enter_key == 'A') {
		(*x)--; 
	}
	if (enter_key == 'd'|| enter_key == 'D') {
		(*x)++; 
	}
}
/*방향 이동 함수*/


struct StageData
{
	int x;
	int y;

	int wall_x[wall_len]; // 100개
	int wall_y[wall_len];

	int ball_x[ball_home_len]; // 50개
	int ball_y[ball_home_len];

	int home_x[ball_home_len];
	int home_y[ball_home_len];
};
/*스테이지 데이터 구조체*/


int main() {

	game_SetCursor(FALSE);
	int stage_level = 0;

	while (1){ /* 게임 시작 루프 */

		game_Clear();
		game_GotoXY(8, 3);
		printf("stage %d", stage_level + 1);
		Sleep(1000);
		game_Clear();
		/*스테이지 레벨 표시*/

		game_GotoXY(30, 1);
		printf("w : ↑");
		game_GotoXY(30, 2);
		printf("s : ↓");
		game_GotoXY(30, 3);
		printf("a : ←");
		game_GotoXY(30, 4);
		printf("d : →");
		game_GotoXY(30, 5);
		printf("r : 리셋");
		/*조작법 설명 표시*/

		struct StageData stage[] =
		{
			{4, 4,
			{2,3,4,2,4,2,4,5,6,7,0,1,2,7,0,5,6,7,0,1,2,3,5,3,5,3,4,5},
			{0,0,0,1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,5,6,6,7,7,7},
			{3,5,3,4}, {3,3,4,5},
			{3,6,1,4}, {1,3,4,6}},

			{2, 3,
			{1,2,3,4,5,6,7,1,7,8,9,0,1,3,4,5,9,0,9,0,4,8,9,0,1,4,8,1,2,3,4,5,6,7,8},
			{0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,3,3,4,4,4,4,5,5,5,5,6,6,6,6,6,6,6,6},
			{2,4,7,6}, {2,3,3,4},
			{2,3,2,3}, {4,4,5,5}},
			
			{1, 1,
			{0,1,2,3,4,0,4,0,4,6,7,8,0,4,6,8,0,1,2,4,5,6,8,1,2,8,1,5,8,1,5,6,7,8,1,2,3,4,5},
			{0,0,0,0,0,1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,4,4,4,5,5,5,6,6,6,7,7,7,7,7,8,8,8,8,8},
			{2,3,2}, {2,2,3},
			{7,7,7}, {3,4,5}},

			{1, 2, 
			{ 1,2,3,4,0,1,4,0,4,0,1,4,5,0,1,5,0,5,0,5,0,1,2,3,4,5 },
			{ 0,0,0,0,1,1,1,2,2,3,3,3,3,4,4,4,5,5,6,6,7,7,7,7,7,7},
			{2,2,3,2,3}, {2,3,4,5,6},
			{1,1,2,3,4}, {5,6,6,6,6}},

			{2, 1,
			{1,2,3,4,1,4,5,6,1,6,0,1,2,4,6,7,0,2,4,7,0,5,7,0,7,0,1,2,3,4,5,6,7},
			{0,0,0,0,1,1,1,1,2,2,3,3,3,3,3,3,4,4,4,4,5,5,5,6,6,7,7,7,7,7,7,7,7},
			{3,2,5}, {2,5,6},
			{1,1,1}, {4,5,6}}
		};
		/* 구조체 배열 */

		int x = stage[stage_level].x;
		int y = stage[stage_level].y;

		int* wall_x = stage[stage_level].wall_x;
		int* wall_y = stage[stage_level].wall_y;

		int* ball_x = stage[stage_level].ball_x;
		int* ball_y = stage[stage_level].ball_y;
		
		int* home_x = stage[stage_level].home_x;
		int* home_y = stage[stage_level].home_y; // 배열 변수는 첫번째 요소의 주소값을 갖기 때문에 포인터로 변수 할당
		/* 스테이지 레벨에 맞는 데이터 */
		
		int real_wall_len = 0;
		for (int i = 0; i < wall_len; i++) {
			real_wall_len++;
			if (stage[stage_level].wall_y[i]> stage[stage_level].wall_y[i+1]) {
				break;
			}
		}
		/* 실제 벽 개수 */

		int real_ball_home_len = 0;
		for (int i = 0; i < ball_home_len; i++) {
			if (stage[stage_level].home_y[i] == 0) {
				break;
			}
			real_ball_home_len++;
		}
		/* 실제 공, 집 개수, 스테이지 완료에 필요 */

		for (int i = 0; i < real_wall_len; i++) {
			game_GotoXY(wall_x[i]*2, wall_y[i]);
			game_SetColor(0, 10);
			printf("▩");
			game_SetColor(0, 15);
		}
		/*벽 생성*/

		for (int i = 0; i < real_ball_home_len; i++) {
			game_GotoXY(ball_x[i] * 2, ball_y[i]);
			printf("●");
		}
		/* 공 생성 */

		for (int i = 0; i < real_ball_home_len; i++) {
			game_GotoXY(home_x[i] * 2, home_y[i]);
			printf("□");
		}
		/* 집 생성 */

		game_GotoXY(x * 2, y);
		game_SetColor(0, 12);
		printf("◆");
		game_SetColor(0, 15);
		/* 캐릭터 생성 */


		while (1){ /* 스테이지 진행 루프 */
		
			if (_kbhit()) { // 키보드 입력이 있으면 true 반환
				char enter_key = _getch(); // 입력 값 저장

				if (enter_key == 'r'|| enter_key == 'R') {
					Sleep(100);
					break;
				}
				/* 리셋 */

				/*///////////////////////////////////

				        1. 이동 전 좌표 저장 

				///////////////////////////////////*/
				int ex_x = x, ex_y = y;


				/*///////////////////////////////////

					  2. 이동 전 좌표 글자 삭제

				///////////////////////////////////*/
				game_GotoXY(x * 2, y);
				printf("  ");


				/*///////////////////////////////////

	      				3. keyMove로 좌표 이동

				///////////////////////////////////*/
				keyMove(enter_key, &x, &y);


				/*////////////////////////////////////////////

				  4. 겹치는 요소있는지 확인 후 로직대로 처리

				////////////////////////////////////////////*/

				/* 4-2) 캐릭터가 벽과 만남 */
				for (int i = 0; i < real_wall_len; i++) {
					if (x == wall_x[i] && y == wall_y[i]) {
						x = ex_x;
						y = ex_y;
					}
				}

				/* 4-3) 캐릭터가 공1과 만남 */
				for (int i = 0; i < real_ball_home_len; i++) {
					if (x == ball_x[i] && y == ball_y[i]) {
						
						/**************  공  ****************

            					1. 이동 전 좌표 저장

						************************************/
						int ex_ball_x = ball_x[i], ex_ball_y = ball_y[i]; // 공 이동 전 좌표 저장


						/**************  공  ****************

						      2. 이동 전 좌표 글자 삭제

						************************************/
						game_GotoXY(ball_x[i] * 2, ball_y[i]);
						printf("  ");


						/**************  공  ****************

						       3. keyMove로 좌표 이동

						************************************/
						keyMove(enter_key, &ball_x[i], &ball_y[i]);


						/******************  공  *********************

					      4. 겹치는 요소있는지 확인 후 로직대로 처리

						*********************************************/

						/* 4-3-1) 공1이 벽과 만남 */
						for (int j = 0; j < real_wall_len; j++) {
							if ((ball_x[i] == wall_x[j] && ball_y[i] == wall_y[j])) {
								ball_x[i] = ex_ball_x;
								ball_y[i] = ex_ball_y;
								x = ex_x;
								y = ex_y;
							}
						}

						/* 4-3-2) 공1이 공2와 만남 */
						for (int j = 0; j < real_ball_home_len; j++) {
							if ((i != j && ball_x[i] == ball_x[j] && ball_y[i] == ball_y[j])) {
								ball_x[i] = ex_ball_x;
								ball_y[i] = ex_ball_y;
								x = ex_x;
								y = ex_y;
							}
						}

						/**************  공  ****************

   							        5. 글자 생성

						************************************/
						game_GotoXY(ball_x[i]*2 , ball_y[i]);
						printf("●");
					}
				}
				
			}
			
			int ball_in_home_len = 0; // 들어간 공의 수 / 스테이지 끝낼 때 사용

			for (int i = 0; i < real_ball_home_len; i++) {

				int ball_in_home = 0; // 현재 집에 공이 들어갔는지 참/거짓 / 집 그릴 때 사용

				for (int j = 0; j < real_ball_home_len; j++) {
					if (ball_x[j] == home_x[i] && ball_y[j] == home_y[i]) {
						ball_in_home_len++;
						ball_in_home = 1;
						break;
					}
				}
				if (ball_in_home == 0) {
					game_GotoXY(home_x[i] * 2, home_y[i]);
					printf("□");
				}
				else {
					game_GotoXY(home_x[i] * 2, home_y[i]);
					printf("■");
				}
			}
			/* 집 그리기, 공이 들어간 집 그리기 */

			
			/*///////////////////////////////////

				       5. 글자 생성

			///////////////////////////////////*/
			game_GotoXY(x * 2, y);
			game_SetColor(0, 12);
			printf("◆");
			game_SetColor(0, 15);


			if (ball_in_home_len == real_ball_home_len) {
				stage_level++;
				break;
			}
			/* 완료 시 스테이지 레벨 증가*/

			Sleep(50);
		}

		if (stage_level > sizeof(stage) / sizeof(stage[0]) - 1)
		{
			break;
		}
		/* 구조체 배열의 길이와 스테이지 레벨 비교로 게임 끝냄 */
	}

	game_Clear();

	game_GotoXY(8, 3);
	printf("game end\n\n\n");

	Sleep(3000);

	return 0;
}