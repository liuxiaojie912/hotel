#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//定义全局变量
typedef struct  {
	int ID;
	char name[16];
	int num;
	int room;
}client;
client customer[100];   //使用数组,将newuser的信息存储到customer数组里去
int client_count=0;     //用户人数,从0开始,将用户信息存储到数组去

//前置页面
void prelanding()      
{
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t***************************\n");
	printf("\t\t\t\t\t\t*                         *\n");
	printf("\t\t\t\t\t\t*      酒店管理系统       *\n");
	printf("\t\t\t\t\t\t*                         *\n");
	printf("\t\t\t\t\t\t*    welcome   hotel      *\n");
	printf("\t\t\t\t\t\t*                         *\n");
	printf("\t\t\t\t\t\t***************************\n");
	getchar();

	system("clear");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t<press the ENTER key to proceed to the main menu >");
}



//主页面,用户输入1,2,3,4,5
void homepage()       
{
	system("clear");
	printf("\n\n\n\n\n");
	printf(" \t\t\t\t\t\t    >>hotel management<<\n");
	printf(" \t\t\t\t\t\t1.输入用户记录\n");
	printf(" \t\t\t\t\t\t2.浏览全部用户记录\n");
	printf(" \t\t\t\t\t\t3.按照idcard查找用户记录\n");
	printf(" \t\t\t\t\t\t4.按照idcard删除用户记录\n");
	printf(" \t\t\t\t\t\t5.按照idcard修改用户记录\n");
	printf("选择你要进行的操作:\n");
}

//第一部分:输入信息
void input()
{
	client newuser;    //用user定义newuser,使用struct结构体
	char answer;     //获取用户是否继续输入,Y或N


	printf("输入用户信息\n输入7位用户ID:\n");
	scanf("%7d", &newuser.ID);
	getchar();    //读取换行符

	printf("请输入用户姓名:\n");
	scanf("%15s", &newuser.name);


	printf("进店人数:\n");
	scanf("%d", &newuser.num);
	getchar();

	printf("请输入用户的房间号:\n");
	scanf("%d",&newuser.room);
	getchar();

	customer[client_count++] = newuser;

	printf("用户信息输入完成！是否继续输入用户信息 (Y/N):\n ");

	scanf("%c", &answer);
	if (answer == 'Y' || answer == 'y') {
		homepage();
		getchar();
		input();
	}
}


// 第二部分:显示所有用户记录(待优化)
void view_all()
{
	int i;
	if (client_count == 0) {
		printf("暂时没有用户记录\n");
		return;
	}
	printf("ID\t用户名\t房间号\t人数\n");
	for (i = 0; i < client_count; i++) {
		printf("%d\t%s\t%d\t%d\n", customer[i].ID,customer[i].name,customer[i].num,customer[i].room);
	}
}


//查询用户信息
void search()
{
	int j;
	int information_1;
	if (client_count == 0) {
		printf("您还没有输入用户ID\n");
	}

	else {
		printf("请输入您想查询的ID:\n");
		scanf("%d", &information_1);

		for (j = 0; j < client_count; j++) {
			if (customer[j].ID == information_1) {
				printf("ID: %d\n", customer[j].ID);
				printf("姓名: %s\n", customer[j].name);
				printf("进店人数: %d\n", customer[j].num);
				printf("房间号: %d\n", customer[j].room);

				break;
			}
			else  {
				printf("没有此ID,请返回重新输入,谢谢\n");
			}
		}
	}
}

//删除用户记录
void delete()
{
	if (client_count == 0) {
		printf("您还没有输入用户ID\n");
	}

	else {
		int h;
		int k;
		int information_2;
		printf("请输入您想删除的ID:\n");
		scanf("%d", &information_2);
		for (h = 0; h < client_count; h++) {
			if (customer[h].ID == information_2) {
				for (k = h; k < client_count; k++) {
					customer[k] = customer[k + 1];
				}
				client_count--;
				printf("该用户已删除\n");
			}
			else {
				printf("未找到该用户,请查询后再进行删除\n");
			}
			break;
		}
	}
}

//更改用户记录
void chang()
{
	//判断是否输入过用户或全部将用户删除
	//没有的话自动退出,进入while循环
	if (client_count == 0) {

		printf("您还没有输入用户\n");
	}
	//更改主函数
	else {
		int x;
		int information_3;
		printf("请输入您想更改的用户ID\n");
		scanf("%d", &information_3);
		for (x = 0; x < client_count; x++) {
			if (customer[x].ID == information_3) {
				printf("原ID:%d\n", customer[x].ID);
				printf("请输入新的用户ID:\n");
				scanf("%d", &customer[x].ID);       //重新赋值

				printf("原用户姓名:%s\n", &customer[x].name);
				printf("请输入新的用户姓名:\n");
				scanf("%s", &customer[x].name);     //重新赋值

				printf("原进店人数:%d\n", customer[x].num);
				printf("请输入新的进店人数:\n");
				scanf("%d", &customer[x].num);      //重新赋值

				printf("原房间号:%d\n", customer[x].room);
				printf("请输入新的房间号:\n");
				scanf("%d", &customer[x].room);     //重新赋值

				//给出结果
				printf("用户记录已修改");
				break;
			}
			else {
				printf("未找到该用户,请查询后再进行更改\n");
			}
		}
	}
}


//主体部分
int main(void)
{	
	prelanding();	
	getchar();
	while (1) {
		homepage();
		int choice;
		scanf("%d", &choice);
	
		switch (choice) {
		case 1:
			input();
			break;
		case 2:
			view_all();	
			
			break;
		case 3:
			search();
			
			break;
		case 4:
			delete();
			
			break;
		case 5:
			chang();
			break;
		default:
			printf("您输入的有误,请重新输入\n");
		}
		printf("请按回车键继续");
		getchar();
		getchar();
	}	
	return 0;
}
