#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void) {
	int reg[10] = { 0, };
	char buff[100];
	char* opcode[8] = {"addi","min","move","mul","div","add", "Jump","branch"};
	char instructions[100][100];
	int opcode_type = 0;
	char* ptr;
	int flag=0;
	char* opcode_i;
	char* operand_1;
	char* operand_2;
	int num_1=0;
	int num_2=0;
	int reg_1=0;
	int reg_2=0;
	int a = 0;

	FILE* fp = fopen("instructions.txt", "r");
	if (fp == NULL)
	{
		printf("file is not open");
	}
	else {
		while (!feof(fp)) {
			fgets(instructions[a], 100, fp);
			a++;
		}
		
		for (int i = 0; i < a; i++) {
			fgets(instructions[i], 100, fp); // read file
			ptr = strtok(instructions[i], " ");
			opcode_i = ptr;  // opcode


			// opcode check
			for (int i = 0; i < 8; i++) {

				if (strcmp(opcode[i], opcode_i) == 0)
				{
					flag = 1;
					opcode_type = i;
					break;
				}
				else
					flag = 0;
			}
			if (flag == 0) {
				printf("opcode error");
				break;

			}

			

			if (opcode_type != 6) {
				ptr = strtok(NULL, " ");
				operand_1 = ptr;  // operand1
				ptr = strtok(NULL, " ");
				operand_2 = ptr;  // operand2

				// operand1 check
				if (isdigit(operand_1[0]) != 0)
				{
					flag = 1;
					num_1 = strtol(operand_1, NULL, 16); //16 진수 변환 함수
				}
				else {
					if (operand_1[0] == 'R')      // char 비교할 때 대소비교를 사용 strcmp는 char*를 사용한다.
					{
						flag = 1;
						reg_1 = operand_1[1] - '0';
					}
					else
						flag = 0;
				}
				if (flag == 0) {
					printf("operand1 error");
					break;
				}

				// operand2 check
				if (isdigit(operand_2[0]) != 0)
				{
					flag = 1;
					num_2 = strtol(operand_2, NULL, 16);
				}
				else {
					if (operand_2[0] == 'R')
					{
						flag = 1;
						reg_2 = operand_2[1] - '0';
					}
					else
						flag = 0;
				}
				if (flag == 0) {
					printf("operand2 error");
					break;
				}
			}
			// execution
			switch (opcode_type)
			{
			case(0):
				reg[0] = num_1 + num_2;
				printf("%d: reg[0]:%d\n",i, reg[0]);
				break;
			case(1):
				reg[0] = num_1 - num_2;
				printf("%d: reg[0]:%d\n",i, reg[0]);
				break;
			case(2):
				reg[reg_1] = num_2;
				printf("%d: reg[%d]:%d\n", i,reg_1, reg[reg_1]);
				break;
			case(3):
				reg[0] = num_1 * num_2;
				printf("%d: reg[0]:%d\n", i,reg[0]);
				break;
			case(4):
				reg[0] = num_1 / num_2;
				printf("%d: reg[0]:%d\n", i,reg[0]);
			case(5):
				reg[0] = reg[reg_1] + reg[reg_2];
				printf("%d: reg[0]:%d\n", i,reg[0]);
				break;
			case(6):
				ptr = strtok(NULL, " ");
				operand_1 = ptr;  // operand1
				num_1 = strtol(operand_1, NULL, 16);
				printf("%d: jump", i);
				i = (num_1 - 1);
				printf(" %d\n", i+1);
				break;
			default:
				if (reg[reg_1] == reg[reg_2]) {
					i = i + 1;
				}
				printf("%d: branch\n", i);
				break;
			}
		}
	return 0;
}