
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

int all_member(struct member human[], struct date birthdays[]); //전체 호출
void this_month_birth(struct member human[], struct date birthdays[]); // 생일자 조회
void search_how_old(struct member human[], struct date birthdays[]); // 나이 검색 

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

	this_month_birth(human, birthdays);

	while (1) {
		int choice;
		printf("===== 기능 목록 =====\n");
		printf("1. 금월 생일자 조회\n2. 나이 검색\n3. 전체 사원 출력\n0. 종료\n원하는 기능의 번호를 입력하십시오.:");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			this_month_birth(human, birthdays);
			break;
		}
		case 2: // 나이 검색
		{
			search_how_old(human, birthdays);
			break;
		}
		case 3: {
			all_member(human, birthdays); // 배열은 기본적으로 주소를 전달하기 때문에 &를 붙이지 않아도 주소 전달이 된다.
			break;
		};
		case 0: {
			printf("================================================================\n");
			printf("프로그램이 종료됩니다.\n");
			printf("================================================================\n");
			return 0;
		}
		default:
			{
			printf("================================================================\n");
			printf("잘못된 값을 입력했습니다.\n");
			printf("================================================================\n");
			}
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
			found[count] = i; // 배열에 i 즉, 구조체의 위치? 를 집어넣어서 출력할 수 있도록 만듦
			count++;
		}
	}
	printf("======================== %d월 생일자들  ========================\n",today->tm_mon + 1);
	for (int i = 0; i < count; i++)
	{
		int index = found[i]; // 위에서 저장된 위치 출력
		printf("================================================================\n");
		printf("사번 = %d\n이름 = %s\n전화번호 = %s\n", human[index].number, human[index].name, human[index].phone_number);
		printf("생년월일:\n연도 = %d\n월 = %d\n일 = %d\n\n", birthdays[index].year, birthdays[index].month, birthdays[index].day);
		printf("================================================================\n");
	}
	printf("총원 = %d\n", count);
	printf("================================================================\n");
}


void search_how_old(struct member human[], struct date birthdays[]) // 2. 나이 검색  , 나이 = 현재 년도 -  출생 년도 + 1
{
	int num;
	printf("검색할 인원의 사번을 입력하십시오:");
	scanf_s("%d", &num);
	time_t now = time(NULL);
	struct tm* today = localtime(&now);
	int found = 0;
	for (int i = 0; i < N; i++)
	{
		if (num == human[i].number)
		{
			int year = (*today).tm_year + 1900;
			int birth_year = birthdays[i].year;
			int old = year - birth_year + 1;
			printf("================================================================\n");
			printf("%s님의 나이는 %d세 입니다.(%d년 기준)\n", human[i].name, old,today->tm_year + 1900);
			printf("================================================================\n");
			found = 1;
			break;
		}
		
	}
	if (found == 0)
		printf("사원이 검색되지 않습니다.");
}


int all_member(struct member human[], struct date birthdays[]) // 3. 사원 전체 출력 
{
	printf("========================== 전체 사원 ===========================\n");
	int count = 0;
	for (int i = 0; i < N; i++)
	{	
		printf("================================================================\n");
		printf("사번 = %d\n이름 = %s\n전화번호 = %s\n", human[i].number, human[i].name, human[i].phone_number);
		printf("생년월일:\n연도 = %d\n월 = %d\n일 = %d\n\n", birthdays[i].year, birthdays[i].month, birthdays[i].day);
		printf("================================================================\n");
		count++;
	}
	printf("총원 = %d\n", count);
	printf("================================================================\n");
	
	return 0;
}
 