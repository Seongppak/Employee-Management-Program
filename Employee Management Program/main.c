/*
각 직원에 대해 사번, 이름 ,전화번호, 생일(년/월/일)을 관리
직원 데이터는 사용자로부터 직접 읽어들인다.
초기화 불가
프로그램 실행시 해당월에 생일인 사람을 출력한다.
 이름과 생일 날자(일)
검색 기능을 제공
 사번으로 검색. 이때 날자 대신 나이를 출력한다.
 최소 10명을 처리하도록 구현
*/

#define N 12
#include <stdio.h>
#include<time.h>


struct member
{
	int number;
	char name[N];
	char phone_number[15];
};
struct date
{
	int year;
	int month;
	int day;
};

void all_member(struct member human[], struct date birthdays[]);
void this_month_birth(struct member human[], struct date birthdays[]);

int main()
{
	
	struct member human[N] = //회사원들 목록
	{
		{1001,"김민수", "010-2345-6781"}, {1002, "이지은","010-3456-7892"},{1003,"박준호","010-4567-8903"}, {1004,"최서연", "010-5678-9014"},
		{1005,"정현우","010-6789-0125"},{1006,"강수빈","010-7890-1236"}, {1007, "조성민", "010-8901-2347"}, {1008, "윤하늘", "010-9012-3458"},
		{1009,"장도윤","010-1234-5679"}, {1010, "임지수", "010-2345-6780"}, {1011, "한유진", "010-3456-7891"}, {1012,"오태양", "010-4567-8902"}
	};

	struct date birthdays[N] = // 회사원들 생일
	{
		{1998, 9 ,3}, {2000,3,15}, {1995, 9,12}, {2002,11,28},{1999,07,21},{2001,9,25},
		{1997,1, 9}, {2003,9,30}, {1996,12,5}, {2000,9,18}, {1994,5,14},{2004,2,29}
	};


	int choice;
	printf("1. 금월 생일자 조회, 2. 나이 검색 3. 전체 사원 출력 0. 종료\n원하는 기능의 번호를 입력하십시오.:");
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
	{
		this_month_birth(human, birthdays);
		break;
	}
	//case 2: // 나이 검색
	case 3: {
		all_member(human, birthdays); // 배열은 기본적으로 주소를 전달하기 때문에 &를 붙이지 않아도 주소 전달이 된다.
		break;
			};
	case 0: {
		printf("프로그램이 종료됩니다.");
			return 0;
			}
	}

	
	return 0;
}


void this_month_birth(struct member human[], struct date birthdays[]) //1. 금월 생일자 조회
{
	time_t now = time(NULL); // 시스템 시간 불러오기
	struct tm* today = localtime(&now); // 구조체의 값을 now의 주소에서 가지고 옴. , localtime()함수가 now 안에 있는 시스템 시간을 현재 시간으로 변환함.

	int month = today->tm_mon + 1; //0부터 시작하기 때문에 +1 해줘야 이번달이 나옴. today->tm_mon = (*today).tm_mon +1
	int found[N]; // 생일자들 저장하는 배열
	int count = 0; // 생일자들 숫자 카운트
	for(int i = 0; i < N; i++)
	{
		if (month == birthdays[i].month)
		{
			found[count] = i;
			count++;
		}
	}
	printf("======================== 금월 생일자들  ========================\n");
	for (int i = 0; i < count; i++)
	{
		int index = found[i];
		printf("사번 = %d, 이름 = %s, 전화번호 = %s\n", human[index].number, human[index].name, human[index].phone_number);
		printf("생년월일: 연도 = %d, 월 = %d, 일 = %d\n\n", birthdays[index].year, birthdays[index].month, birthdays[index].day);
		printf("총원 = %d명\n", count);
	}
	printf("================================================================\n");
}





void all_member(struct member human[], struct date birthdays[]) // 3. 사원 전체 출력 
{
	printf("======================== 현재 사내 사원 ========================\n");
	for (int i = 0; i < N; i++)
	{
		printf("사번 = %d, 이름 = %s, 전화번호 = %s\n", human[i].number, human[i].name, human[i].phone_number);
		printf("년 = %d, 월 = %d, 일 = %d\n\n", birthdays[i].year, birthdays[i].month, birthdays[i].day);
	}
	printf("================================================================\n");
	return 0;
}
//프로그램 실행 시 몇월인지에 따라 그 생일인 사람을 출력한다.
 

// 사번으로 검색하여 이때 나이를 출력한다 --> 현재 프로그램 작동중인 컴퓨터의 연도 정보를 받아와서 현재연도 - 출생연도 하면 될듯