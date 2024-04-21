#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#define LEN sizeof(struct addritem)																		// 定义结构体的长度
#define FORMAT "%-10s%-10s%-15s%-25s%-30s%\n"															// 这个宏规定了输出的格式
#define DATA addrinfo[i].name, addrinfo[i].sex, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address // 代表结构体数组元素中的各个成员
// 定义结构体成员
struct addritem
{
	char name[10];
	char sex[10];
	char tel[15];
	char email[25];
	char address[30];
};
struct addritem addrinfo[100]; // 定义结构体数组
// 声明函数
void input();
void search();
void update();
void del();
void display();
void sort();
void menu();
void menu() // 主菜单函数
{
	system("cls"); // 调用cls函数清空界面
	printf("\n\n\n\n\n");
	printf("\t\t|----------------------------------CONTACT----------------------------------------------------|\n");
	printf("\t\t|0. 退出                                                                                      |\n");
	printf("\t\t|1. 添加联系人                                                                                |\n");
	printf("\t\t|2. 查找联系人                                                                                |\n");
	printf("\t\t|3. 更新联系人                                                                                |\n");
	printf("\t\t|4. 删除联系人                                                                                |\n");
	printf("\t\t|5. 排序联系人                                                                                |\n");
	printf("\t\t|6. 联系人列表                                                                                |\n");
	printf("\t\t|---------------------------------------------------------------------------------------------|\n");
	printf("\t\t\t选择(0-6):");
}
void main()
{
	int n;
	menu();			 // 调用列表界面
	scanf("%d", &n); // 获取用户的选择
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
		menu(); // 选择完成后任意键返回菜单
		scanf("%d", &n);
	}
}
// 添加联系人
void input()
{
	int i, count = 0;							// i做循环变量，count储存联系人下标
	char ch[2];									// ch记录用户输入
	FILE *fp;									// 指向所保存数据文件的指针
	if ((fp = fopen("data.txt", "a+")) == NULL) // 创建文本保存联系人信息
	{
		printf("无法打开!\n");
		return;
	}
	while (!feof(fp)) // 判断文件是否结束
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1) // 用于从文件中读取数据。它的作用是从指定的文件中读取数据块，并将数据存储到指定的内存位置中
			count++;
	}
	fclose(fp);		// 关闭文件函数
	if (count == 0) // 联系人数目为0
		printf("无记录\n");
	else
	{
		system("cls"); // 清空列表
		display();	   // 展示界面
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		printf("无法打开联系人列表!\n");
		return;
	}
	// 将文件重新写入磁盘
	for (i = 0; i < count; i++)
		fwrite(&addrinfo[i], LEN, 1, fp);
	printf("请输入(y/n)");
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		printf("姓名:");
		scanf("%s", &addrinfo[count].name);
		// 判断用户姓名是否存在
		for (i = 0; i < count; i++)
			if (strcmp(addrinfo[i].name, addrinfo[count].name) == 0)
			{
				printf("该姓名已经存在，请输入任意键返回菜单");
				getch();
				fclose(fp);
				return;
			}
		printf("性别:");
		scanf("%s", &addrinfo[count].sex);
		printf("电话:");
		scanf("%s", &addrinfo[count].tel);
		printf("邮箱:");
		scanf("%s", &addrinfo[count].email);
		printf("地址:");
		scanf("%s", &addrinfo[count].address);
		// 将addrinfo数组中第count个元素作为一个数据块，
		// 每个数据块的大小为LEN，写入到文件指针fp所指向的文件中。
		// 这行代码还会检查写入操作是否成功，如果不成功，则返回值不等于1。
		if (fwrite(&addrinfo[count], LEN, 1, fp) != 1)
		{
			printf("无法保存!");
			getch();
		}
		else
		{
			printf("%s 保存成功!\n", addrinfo[count].name);
			count++;
		}
		printf("是否继续存入联系人(y/n):");
		scanf("%s", ch);
	}
	fclose(fp);
	printf("OK!\n");
}
// 以姓名或地址进行搜索
void search()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], name[15], address[15];
	// 以只读方式打开名为 "data.txt" 的文件，并将文件指针赋值给变量
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("无法打开\n");
		return;
	}
	while (!feof(fp)) // 遍历完成
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("无该联系人!\n");
		return;
	}
	int n;
	printf("请输入查找方式 1姓名 2地址");
	scanf("%d", &n);
	if (n == 1)
	{
		printf("请输入姓名:");
		scanf("%s", name);
		// 比较两个字符串是否相等
		for (i = 0; i < count; i++)
			if (strcmp(name, addrinfo[i].name) == 0)
			{
				printf("找到该联系人是否输出(y/n):");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					printf("姓名     性别        电话           邮箱                    地址\t\n ");
					printf(FORMAT, DATA);
				}
				break;
			}
		// 不存在重名情况
		if (i == count)
			printf("无该联系人!\n");
	}
	else
	{
		printf("请输入地址:");
		scanf("%s", address);
		for (i = 0; i < count; i++)
			if (strcmp(address, addrinfo[i].address) == 0)
			{
				printf("已找到该联系人是否输出(y/n):");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					printf("姓名     性别        电话           邮箱                    地址\t\n ");
					printf(FORMAT, DATA);
				}
			}
		// 不break 有相同地址
		if (i == count)
			printf("已无该地址联系人!\n");
	}
}
// 更新联系人信息
void update()
{
	FILE *fp;
	int i, j, count = 0;
	char name[15];
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("无法打开!\n");
		return;
	}
	// 文件流fp还未到达文件末尾，可以继续进行文件读取操作。
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	if (count == 0)
	{
		printf("无该联系人!\n");
		fclose(fp);
		return;
	}
	display();
	// 修改联系人信息
	printf("请输入你要修改的联系人姓名!\n");
	printf("姓名:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("找到该联系人可以修改!\n");
			printf("姓名:");
			scanf("%s", &addrinfo[i].name);
			printf("性别:");
			scanf("%s", &addrinfo[i].sex);
			printf("电话:");
			scanf("%s", &addrinfo[i].tel);
			printf("邮箱:");
			scanf("%s", &addrinfo[i].email);
			printf("地址:");
			scanf("%s", &addrinfo[i].address);
			printf("修改成功!");
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("无法打开!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("无法保存!");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("未找到该联系人!\n");
}
// 删除联系人
void del()
{
	FILE *fp;
	int i, j, count = 0;
	char ch[2];
	char name[15];
	//"r+"标识表示以读写方式打开文件，如果文件不存在则会创建文件。
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("无法打开!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("无该联系人!\n");
		return;
	}
	display();
	// 删除模块
	printf("请输入想要删除的联系人姓名:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("找到该联系人是否删除(y/n)");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				for (j = i; j < count; j++)
					addrinfo[j] = addrinfo[j + 1];
			count--;
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("无法打开!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("无法保存!\n");
					getch();
				}
			fclose(fp); // 关闭文件释放内存
			printf("删除成功!\n");
			return;
		}
	}
	printf("未找到该联系人!\n");
}
// 按姓名排序
void sort()
{
	FILE *fp;
	struct addritem t;
	int i = 0, j = 0, count = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("无法打开!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("无数据文件!\n");
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
		printf("无法打开!\n");
		return;
	}
	for (i = 0; i < count; i++)
		if (fwrite(&addrinfo[i], LEN, 1, fp) != 1)
		{
			printf("无法保存!\n");
			getch();
		}
	fclose(fp);
	printf("排序成功!\n");
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
	printf("姓名     性别        电话           邮箱                    地址\t\n");
	for (i = 0; i < count; i++)
		printf(FORMAT, DATA);
}
