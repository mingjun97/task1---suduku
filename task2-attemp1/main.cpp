#include <stdio.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
int suku(int arr[9][9],int floors);
int bubble(int *arr);
int sw(int *addr,int no);
void print(int arr[9][9]);
int step = 0;
int main() {
	int starttime, detatime;
	starttime = timeGetTime();
	int arr[9][9];
	//两组测试数据
	int arrtmp[81] = { 6,0,0,1,3,0,0,0,0,8,0,0,0,0,0,0,6,0,0,0,7,0,5,0,3,0,0,3,0,0,0,0,0,0,0,0,5,1,6,0,9,0,2,7,4,0,0,0,0,0,0,0,0,5,0,0,9,0,1,0,8,0,0,0,2,0,0,0,0,0,0,3,0,0,0,0,2,9,0,0,1 };
	/*int arrtmp[81] = {0,7,0,1,0,3,0,6,0	, 0, 5, 0, 0, 0, 0, 0, 7, 0		, 3, 0, 0, 0, 5, 0, 0, 0, 1		, 5, 0, 0, 3, 0, 4, 0, 0, 8		, 4, 0, 7, 0, 0, 0, 1, 0, 2		, 9, 0, 0, 7, 0, 2, 0, 0, 4		, 2, 0, 0, 0, 7, 0, 0, 0, 3		, 0, 3, 0, 0, 0, 0, 0, 4, 0		, 0, 6, 0, 5, 0, 9, 0, 2, 0}*/
	int i, j;
	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8; j++)
			arr[i][j] = arrtmp[i * 9 + j];
	if (suku(arr, 0) == 1) {
		detatime = timeGetTime();
		detatime = detatime - starttime;

		printf("\nsuccess\n调用函数%d次\n用时约%d毫秒\n结果见上方\n", step, detatime);
		getchar();
	}
	else {
		printf("falture");
	}


}
int suku(int arr[9][9], int floors) {
	step++;
	floors++; //递归调用级数
	int i, j,tmpi = 9;
	int tmpj = 9;
	int possible[9] = { 1,2,3,4,5,6,7,8,9 };
	//查找空闲位置 == 0
	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 8;j++)
			if (arr[i][j] == 0) {
				tmpi = i;
				i = 9;
				tmpj = j;
				j = 9;
			}
	i = tmpi;
	j = tmpj;
	//==========================================
	//找不到任何空闲位置，返回为成功
	if (i == 9 && j == 9) {
		//在屏幕上打印目标数组
		print(arr);

		return 1;
	}
	//==========================================
	//获取该空闲位置允许存在的数字
	int foo,bar;
	for (foo = 0; foo <= 8; foo++) if (arr[i][foo] != 0) possible[arr[i][foo] - 1] = 0;
	for (foo = 0; foo <= 8; foo++) if (arr[foo][j] != 0) possible[arr[foo][j] - 1] = 0;
	tmpi = i - i % 3 ;
	tmpj = j - j % 3 ;
	for (foo = 0; foo <= 2; foo++)
		for (bar = 0; bar <= 2; bar++) {
			if (arr[tmpi + foo][tmpj + bar] != 0)
				possible[arr[tmpi + foo][tmpj + bar] - 1] = 0;
		}
				//通过冒泡法重排possible变量,将0放至最后
				bubble(&possible[0]);




	tmpi = 0;



		while (possible[tmpi] != 0) {
			arr[i][j] = possible[tmpi];
			/*
			printf("%d %d %d %d\n", i, j, possible[tmpi], floors);
			printf("-------------\n");
			print(arr);
			printf("=============\n");
			getchar();*/
			if (suku(arr,floors) == 1) return 1;
			tmpi++;
			arr[i][j] = 0;
		}
		return 0;
}


void print(int arr[9][9]) {
	int i, j;
	for (i = 0; i <= 8; i++) {
		for (j = 0; j <= 8; j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
}

int bubble(int *arr) {
	int i, j;
	for (i = 0; i <= 8; i++) {
		for (j = i; j >= 1; j--) {
			if (*(arr + j) >= *(arr + j - 1)) sw(arr, j);
		}

	}
	return 1;

}
int sw(int *addr, int no) {
	int tmp;
	tmp = *(addr + no);
	*(addr + no) = *(addr + no - 1);
	*(addr + no - 1) = tmp;
	return 1;
}