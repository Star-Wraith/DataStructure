#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int rec_count = 0; //재귀적 함수 호출 횟수를 저장하기 위한 함수


#define PROB 5 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
/* Compute power(x, n) for int x, n */
// 1번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현
#define X_NUM 2
#define N_NUM 5
double power(double x, int n)
{
	++rec_count;
	if (n == 0) return 1;
	else if ((n % 2) == 0)
		return power(x * x, n / 2);
	else return x * power(x * x, (n - 1) / 2);
}
double slow_power(double x, int n)
{
	int i;
	double result = 1.0;
	for (i = 0; i < n; i++)
		result = result * x;
	return(result);
}

int main()
{
	double x = X_NUM;
	int	n = N_NUM;
	
	clock_t start_repet, end_repet; // 반복적
	clock_t start_recur, end_recur; // 재귀적



	start_repet = clock();
	double repetitive = slow_power(x, n);
	end_repet = clock();
	
	start_recur = clock();
	double recursive = power(x, n);
	end_recur = clock();

	printf("문제1\n");
	printf("x, n 입력<x^n> : %d %d\n", X_NUM, N_NUM);
	printf("ITR: %d^%d = %f, 수행시간 :%f\n", X_NUM, N_NUM, repetitive, (double)(end_repet - start_repet));
	printf("REC: %d^%d = %f, 수행시간 :%f, 함수호출횟수 : %d\n", X_NUM, N_NUM, recursive, (double)(end_recur - start_recur), rec_count);

	
	
}

#elif PROB == 2
/* Binomial Coef */
// 2번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현


#define N_NUM 10
#define K_NUM 5

double binomial_recur(int n, int k)
{
	++rec_count;
	if (k == 0 || k == n) {
		return 1;
	}
	else if (0 < k && k < n) {
		return (binomial_recur(n - 1, k - 1) + binomial_recur(n - 1, k));
	}

	return 0;
}
int factorial(int n) {
	int i, result = 1;

	for (i = n; n > 0; n--) {
		result *= n;
	}
		
	return result;
}
double binomial_repet(int n, int k)
{
	if (k == 0 || k == n) return 1;
	else if ((0 < k) && (k < n)) {
		int i, num = 1;
		if (k > n / 2) {
			k = n - k;
		}
			
		for (i = 1; i <= k; i++, n--) {

			num *= n;
		}
		return num /factorial(k) ;
	}
	else return 0;
}
int main()
{
	int n = N_NUM;
	int	k = K_NUM;

	clock_t start_repet, end_repet; // 반복적
	clock_t start_recur, end_recur; // 재귀적



	start_repet = clock();
	double repetitive = binomial_repet(n,k);
	end_repet = clock();

	start_recur = clock();
	double recursive = binomial_recur(n, k);
	end_recur = clock();

	printf("문제2\n");
	printf("n, k 입력<n >= k> : %d %d\n", N_NUM, K_NUM);
	printf("ITR: %dC%d = %f, 수행시간 :%f\n", N_NUM, K_NUM, repetitive, (double)(end_repet - start_repet));
	printf("REC: %dC%d = %f, 수행시간 :%f, 함수호출횟수 : %d\n", N_NUM, K_NUM, recursive, (double)(end_recur - start_recur), rec_count);



}
#elif PROB == 3
/* Ackerman function */

#define M_NUM 3
#define N_NUM 7


double Ackerma_rep(int m, int n) //여기서부터 하면 될듯
{
	int list[100000];
	int esp = 0;

	list[esp++] = m;
	list[esp] = n;

	while (1) {
		if (esp == 0) {
			return list[esp];
		}
		else if (list[esp - 1] == 0) {
			list[esp - 1] = list[esp] + 1;

			esp = esp - 1;
		}
		else if (list[esp] == 0) {
			list[esp - 1] = list[esp - 1] - 1;
			list[esp] = 1;
		}
		else {
			list[esp + 1] = list[esp] - 1;
			list[esp] = list[esp - 1];
			list[esp - 1] = list[esp - 1] - 1;

			esp = esp + 1;
		}
	}
}

double Ackerman(int m, int n)
{
	++rec_count;
	if (m == 0) {
		return n + 1;
	}
	else if (m != 0 && n == 0) {
		return Ackerman(m - 1, 1);
	}
	else {
		return Ackerman(m - 1, Ackerman(m, n - 1));
	}
}

int main() 
{
	int m = M_NUM;
	int	n = N_NUM;

	clock_t start_repet, end_repet; // 반복적
	clock_t start_recur, end_recur; // 재귀적


	

	start_repet = clock();
	double repetitive = Ackerma_rep(m,n);
	end_repet = clock();

	start_recur = clock();
	double recursive = Ackerman(m, n);
	end_recur = clock();

	printf("문제3\n");
	printf("n, n 입력<n , n> : %d %d\n", M_NUM, N_NUM);
	printf("ITR: A<%d,%d> = %f, 수행시간 :%f\n", M_NUM, N_NUM, repetitive, (double)(end_repet - start_repet));
	printf("REC: A<%d,%d> = %f, 수행시간 :%f, 함수호출횟수 : %d\n", M_NUM, N_NUM, recursive, (double)(end_recur - start_recur), rec_count);


}
#elif PROB == 4
/* 문제 3) 피보나치 수열 */
#define N_NUM 4


int fib_rep(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	int pp = 0;
	int p = 1;
	int result = 0;

	for (int i = 2; i <= n; i++) {
		result = p + pp;
		pp = p;
		p = result;
	}
	return result;
}


int fib(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return (fib(n - 1) + fib(n - 2));
}

int main()
{
	int	n = N_NUM;

	clock_t start_repet, end_repet; // 반복적
	clock_t start_recur, end_recur; // 재귀적




	start_repet = clock();
	double repetitive = fib_rep(n);
	end_repet = clock();

	start_recur = clock();
	double recursive = fib(n);
	end_recur = clock();

	printf("문제4\n");
	printf("Input 피보나치 항 : %d\n", N_NUM);
	printf("ITR: %d 번째 항의 값 : %f, 수행시간 :%f\n", N_NUM, repetitive, (double)(end_repet - start_repet));
	printf("REC: %d 번째 항의 값 : %f, 수행시간 :%f, 함수호출횟수 : %d\n", N_NUM, recursive, (double)(end_recur - start_recur), rec_count);


}
#elif PROB == 5
/* 문제 4) Binary Search */

int binarySearchRep(int nums[], int n, int target)
{

	int low = 0, high = n - 1;

	while (low <= high)
	{


		int mid = (low + high) / 2;  

		if (target == nums[mid]) {
			return mid;
		}
		else if (target < nums[mid]) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return -1;
}


int binarySearchRec(int nums[], int low, int high, int target)
{
	++rec_count;
	if (low > high) {
		return -1;
	}

	int mid = (low + high) / 2;   

	if (target == nums[mid]) {
		return mid;
	}
	else if (target < nums[mid]) {
		return binarySearchRec(nums, low, mid - 1, target);
	}
	else {
		return binarySearchRec(nums, mid + 1, high, target);
	}
}

#define NUM 50000
int main()
{
	int nums[NUM] = { 0};
	int target = 0;

	for (int i = 0; i < NUM; ++i) {
		nums[i] = i;
	}

	printf("\n찾을 수를 입력하시오: ");
	scanf_s("%d", &target);
	putchar('\n');

	int n = sizeof(nums) / sizeof(nums[0]);
	

	clock_t start_repet, end_repet; // 반복적
	clock_t start_recur, end_recur; // 재귀적
	int low = 0, high = n - 1;



	start_repet = clock();
	int repetitive = binarySearchRep(nums, n, target);
	end_repet = clock();

	start_recur = clock();
	int recursive = binarySearchRec(nums, low, high, target);
	end_recur = clock();

	printf("문제5\n");

	printf("ITR: %d 값의 index : %d, 수행시간 :%f\n", target ,repetitive, (double)(end_repet - start_repet));
	printf("REC: %d 값의 index : %d, 수행시간 :%f\n, 함수호출횟수 : %d\n", target, recursive, (double)(end_recur - start_recur), rec_count);

}
#endif
