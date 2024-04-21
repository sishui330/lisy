#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#define LEN sizeof(struct addritem)																		// ����ṹ��ĳ���
#define FORMAT "%-10s%-10s%-15s%-25s%-30s%\n"															// �����涨������ĸ�ʽ
#define DATA addrinfo[i].name, addrinfo[i].sex, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address // ����ṹ������Ԫ���еĸ�����Ա
// ����ṹ���Ա
struct addritem
{
	char name[10];
	char sex[10];
	char tel[15];
	char email[25];
	char address[30];
};
struct addritem addrinfo[100]; // ����ṹ������
// ��������
void input();
void search();
void update();
void del();
void display();
void sort();
void menu();
void menu() // ���˵�����
{
	system("cls"); // ����cls������ս���
	printf("\n\n\n\n\n");
	printf("\t\t|----------------------------------CONTACT----------------------------------------------------|\n");
	printf("\t\t|0. �˳�                                                                                      |\n");
	printf("\t\t|1. �����ϵ��                                                                                |\n");
	printf("\t\t|2. ������ϵ��                                                                                |\n");
	printf("\t\t|3. ������ϵ��                                                                                |\n");
	printf("\t\t|4. ɾ����ϵ��                                                                                |\n");
	printf("\t\t|5. ������ϵ��                                                                                |\n");
	printf("\t\t|6. ��ϵ���б�                                                                                |\n");
	printf("\t\t|---------------------------------------------------------------------------------------------|\n");
	printf("\t\t\tѡ��(0-6):");
}
void main()
{
	int n;
	menu();			 // �����б����
	scanf("%d", &n); // ��ȡ�û���ѡ��
	while (n)
	{
		switch (n)
		{
		case 1:
			input();
			break;
		case 2:
			search();
			break;
		case 3:
			update();
			break;
		case 4:
			del();
			break;
		case 5:
			sort();
			break;
		case 6:
			display();
			break;
		default:
			break;
		}
		getch();
		menu(); // ѡ����ɺ���������ز˵�
		scanf("%d", &n);
	}
}
// �����ϵ��
void input()
{
	int i, count = 0;							// i��ѭ��������count������ϵ���±�
	char ch[2];									// ch��¼�û�����
	FILE *fp;									// ָ�������������ļ���ָ��
	if ((fp = fopen("data.txt", "a+")) == NULL) // �����ı�������ϵ����Ϣ
	{
		printf("�޷���!\n");
		return;
	}
	while (!feof(fp)) // �ж��ļ��Ƿ����
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1) // ���ڴ��ļ��ж�ȡ���ݡ����������Ǵ�ָ�����ļ��ж�ȡ���ݿ飬�������ݴ洢��ָ�����ڴ�λ����
			count++;
	}
	fclose(fp);		// �ر��ļ�����
	if (count == 0) // ��ϵ����ĿΪ0
		printf("�޼�¼\n");
	else
	{
		system("cls"); // ����б�
		display();	   // չʾ����
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		printf("�޷�����ϵ���б�!\n");
		return;
	}
	// ���ļ�����д�����
	for (i = 0; i < count; i++)
		fwrite(&addrinfo[i], LEN, 1, fp);
	printf("������(y/n)");
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		printf("����:");
		scanf("%s", &addrinfo[count].name);
		// �ж��û������Ƿ����
		for (i = 0; i < count; i++)
			if (strcmp(addrinfo[i].name, addrinfo[count].name) == 0)
			{
				printf("�������Ѿ����ڣ���������������ز˵�");
				getch();
				fclose(fp);
				return;
			}
		printf("�Ա�:");
		scanf("%s", &addrinfo[count].sex);
		printf("�绰:");
		scanf("%s", &addrinfo[count].tel);
		printf("����:");
		scanf("%s", &addrinfo[count].email);
		printf("��ַ:");
		scanf("%s", &addrinfo[count].address);
		// ��addrinfo�����е�count��Ԫ����Ϊһ�����ݿ飬
		// ÿ�����ݿ�Ĵ�СΪLEN��д�뵽�ļ�ָ��fp��ָ����ļ��С�
		// ���д��뻹����д������Ƿ�ɹ���������ɹ����򷵻�ֵ������1��
		if (fwrite(&addrinfo[count], LEN, 1, fp) != 1)
		{
			printf("�޷�����!");
			getch();
		}
		else
		{
			printf("%s ����ɹ�!\n", addrinfo[count].name);
			count++;
		}
		printf("�Ƿ����������ϵ��(y/n):");
		scanf("%s", ch);
	}
	fclose(fp);
	printf("OK!\n");
}
// ���������ַ��������
void search()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], name[15], address[15];
	// ��ֻ����ʽ����Ϊ "data.txt" ���ļ��������ļ�ָ�븳ֵ������
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("�޷���\n");
		return;
	}
	while (!feof(fp)) // �������
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("�޸���ϵ��!\n");
		return;
	}
	int n;
	printf("��������ҷ�ʽ 1���� 2��ַ");
	scanf("%d", &n);
	if (n == 1)
	{
		printf("����������:");
		scanf("%s", name);
		// �Ƚ������ַ����Ƿ����
		for (i = 0; i < count; i++)
			if (strcmp(name, addrinfo[i].name) == 0)
			{
				printf("�ҵ�����ϵ���Ƿ����(y/n):");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					printf("����     �Ա�        �绰           ����                    ��ַ\t\n ");
					printf(FORMAT, DATA);
				}
				break;
			}
		// �������������
		if (i == count)
			printf("�޸���ϵ��!\n");
	}
	else
	{
		printf("�������ַ:");
		scanf("%s", address);
		for (i = 0; i < count; i++)
			if (strcmp(address, addrinfo[i].address) == 0)
			{
				printf("���ҵ�����ϵ���Ƿ����(y/n):");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					printf("����     �Ա�        �绰           ����                    ��ַ\t\n ");
					printf(FORMAT, DATA);
				}
			}
		// ��break ����ͬ��ַ
		if (i == count)
			printf("���޸õ�ַ��ϵ��!\n");
	}
}
// ������ϵ����Ϣ
void update()
{
	FILE *fp;
	int i, j, count = 0;
	char name[15];
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("�޷���!\n");
		return;
	}
	// �ļ���fp��δ�����ļ�ĩβ�����Լ��������ļ���ȡ������
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	if (count == 0)
	{
		printf("�޸���ϵ��!\n");
		fclose(fp);
		return;
	}
	display();
	// �޸���ϵ����Ϣ
	printf("��������Ҫ�޸ĵ���ϵ������!\n");
	printf("����:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("�ҵ�����ϵ�˿����޸�!\n");
			printf("����:");
			scanf("%s", &addrinfo[i].name);
			printf("�Ա�:");
			scanf("%s", &addrinfo[i].sex);
			printf("�绰:");
			scanf("%s", &addrinfo[i].tel);
			printf("����:");
			scanf("%s", &addrinfo[i].email);
			printf("��ַ:");
			scanf("%s", &addrinfo[i].address);
			printf("�޸ĳɹ�!");
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("�޷���!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("�޷�����!");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("δ�ҵ�����ϵ��!\n");
}
// ɾ����ϵ��
void del()
{
	FILE *fp;
	int i, j, count = 0;
	char ch[2];
	char name[15];
	//"r+"��ʶ��ʾ�Զ�д��ʽ���ļ�������ļ���������ᴴ���ļ���
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("�޷���!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("�޸���ϵ��!\n");
		return;
	}
	display();
	// ɾ��ģ��
	printf("��������Ҫɾ������ϵ������:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("�ҵ�����ϵ���Ƿ�ɾ��(y/n)");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				for (j = i; j < count; j++)
					addrinfo[j] = addrinfo[j + 1];
			count--;
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("�޷���!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("�޷�����!\n");
					getch();
				}
			fclose(fp); // �ر��ļ��ͷ��ڴ�
			printf("ɾ���ɹ�!\n");
			return;
		}
	}
	printf("δ�ҵ�����ϵ��!\n");
}
// ����������
void sort()
{
	FILE *fp;
	struct addritem t;
	int i = 0, j = 0, count = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("�޷���!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("�������ļ�!\n");
		return;
	}
	for (i = 0; i < count - 1; i++)
		for (j = i + 1; j < count; j++)
			if (strcmp(addrinfo[i].name, addrinfo[j].name) > 0)
			{
				t = addrinfo[i];
				addrinfo[i] = addrinfo[j];
				addrinfo[j] = t;
			}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		printf("�޷���!\n");
		return;
	}
	for (i = 0; i < count; i++)
		if (fwrite(&addrinfo[i], LEN, 1, fp) != 1)
		{
			printf("�޷�����!\n");
			getch();
		}
	fclose(fp);
	printf("����ɹ�!\n");
}
void display()
{
	FILE *fp;
	int i, count = 0;
	fp = fopen("data.txt", "rb");
	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);
	printf("����     �Ա�        �绰           ����                    ��ַ\t\n");
	for (i = 0; i < count; i++)
		printf(FORMAT, DATA);
}
