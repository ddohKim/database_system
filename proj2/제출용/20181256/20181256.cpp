#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include "mysql.h"
#include <sql.h>
#pragma warning(disable:4996)

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "sgu2646";
const char* db = "project2";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		} //sql workbench 연동하는 코드


		FILE* crud1 = NULL;
		fopen_s(&crud1, "20181256_crud.txt", "r");
		char read_temp[1000];
		int state = 0;
		const char* query;
		while (!feof(crud1))
		{
			query = fgets(read_temp, sizeof(read_temp), crud1);
			state = mysql_query(connection, query);
		}
		fclose(crud1);


		int flag = 1;
		int detail_flag = 1;
		while (flag) {
			int type;
			printf("\n\n\n------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t0. QUIT\n\n\n");
			printf("What Type : ");
			scanf_s("%d", &type);
			switch (type) {
				char query[1000];
				memset(query, 0, sizeof(query));
			case 0:
				printf("\n---- QUIT ----\n\n");
				printf("\n---- Program will be closed ----\n\n");
				flag = 0;
				break;
			case 1:
				detail_flag = 1;
				while (detail_flag)
				{
					printf("\n---- TYPE I ----\n\n");
					printf("**truck X (hint: 1721) is destroyed in a crash at 2022-04-07**\n");
					printf("\n----- Subtypes in TYPE I -----\n\n");
					printf("\t1. TYPE I-1.\n");
					printf("\t2. TYPE I-2.\n");
					printf("\t3. TYPE I-3.\n\n\n");
					printf("We have two truck 1721 and truck 2020\n");
					printf("What Detail Type: ");
					int detail;
					char inputTruck[50];
					scanf_s("%d", &detail);
					memset(query, 0, sizeof(query));
					switch (detail) {
					case 0: detail_flag = 0;  break;
					case 1:
						printf("\nTruck Num (hint: 1721 ): ");
						scanf_s("%s", inputTruck, (int)sizeof(inputTruck));
						printf("\n**Find all customers who had a package on the truck at the time of the crash**\n");
						strcat_s(query, "select * from customers where (customer_id )in (select customer_id from shipments where (shipment_id) in (select shipment_id from tracking where next_place ='truck ");
						strcat_s(query, inputTruck);
						strcat_s(query, "' and  date = '2022-04-07 13:00:00'))");
						state = mysql_query(connection, query);
						if (state == 0)
						{
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("\ncustomer id: %s\tname: %s\taddress: %s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						break;
					case 2:
						printf("\nTruck Num (hint: 1721 ): ");
						scanf_s("%s", inputTruck, (int)sizeof(inputTruck));
						printf("\n**Find all recipients who had a package on the truck at the time of the crash**\n");
						strcat_s(query, "select * from recipient where (recipient_id )in (select recipient_id from shipments where (shipment_id) in (select shipment_id from tracking where next_place ='truck ");
						strcat_s(query, inputTruck);
						strcat_s(query, "' and  date = '2022-04-07 13:00:00'))");
						state = mysql_query(connection, query);
						if (state == 0)
						{
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("\nrecipient id: %s\tname: %s\taddress: %s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						break;
					case 3:
						printf("\nTruck Num (hint: 1721 ): ");
						scanf_s("%s", inputTruck, (int)sizeof(inputTruck));
						printf("\n**Find the last successful delivery by that truck prior to the crash**\n");
						strcat_s(query, "select * from shipments where (shipment_id) in (select max(shipment_id) from tracking where next_place ='truck ");
						strcat_s(query, inputTruck);
						strcat_s(query, "' and status='complete' and date < '2022-04-07 13:00:00' order by date)");
						state = mysql_query(connection, query);
						if (state == 0)
						{
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("\nshipment id: %s\tstarted_date: %s\texpected_date: %s\tended_date: %s\tcustomer_id: %s\trecipient_id: %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
							}
							mysql_free_result(sql_result);
						}
						break;
					default: printf("\nIf you want to go back first then input 0\n"); break;

					}

				}
				break;
			case 2:
				printf("\n---- TYPE II ----\n\n");
				printf("**Find the customer who has shipped the most packages in the past year**\n");
				printf("\nWhich year? ( hint: 2022 ) : ");
				char year[10];
				char year2[10];
				int temp;
				scanf_s("%d", &temp);
				memset(query, 0, sizeof(query));
				sprintf(year, "%d", temp + 1);
				sprintf(year2, "%d", temp);
				strcat_s(query, "select customer_id, count(customer_id) as cnt from bill_pay where date<'");
				strcat_s(query, year);
				strcat_s(query, "-01-01' and date>='");
				strcat_s(query, year2);
				strcat_s(query, "-01-01' group by customer_id order by cnt desc limit 1");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\ncustomer id: %s  shipped count: %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				break;

			case 3:
				printf("\n---- TYPE III ----\n\n");
				printf("**Find the customer who has spent the most money on shipping in the past year**\n");
				printf("\nWhich year? ( hint: 2022 ) : ");
				char year3[10];
				char year4[10];
				int temp2;
				scanf_s("%d", &temp2);
				memset(query, 0, sizeof(query));
				sprintf(year3, "%d", temp2 + 1);
				sprintf(year4, "%d", temp2);
				strcat_s(query, "select customer_id, sum(package_price) as price from shipments where shipment_id in (select bill_id from bill_pay where isrefund=0) and started_date<'");
				strcat_s(query, year3);
				strcat_s(query, "-01-01' and started_date>='");
				strcat_s(query, year4);
				strcat_s(query, "-01-01' group by customer_id order by price desc limit 1");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("\ncustomer id: %s  spent money: %swon\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				break;
			case 4:
				printf("\n---- TYPE IV ----\n\n");
				printf("**Find the packages that were not delivered within the promised time.**\n");
				memset(query, 0, sizeof(query));
				strcat_s(query, "select * from shipments where expected_date!=ended_date or ended_date is null order by expected_date");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						char crashed[30] = "Truck was crashed";
						if (sql_row[3])
						{
							printf("shipment id: %s  expected date: %s ended_date: %s\n", sql_row[0], sql_row[2], sql_row[3]);
						}
						else
						{
							printf("shipment id: %s  expected date: %s ended_date: %s(%s)\n", sql_row[0], sql_row[2], sql_row[3], crashed);
						}
					}
					mysql_free_result(sql_result);
				}
				break;
			case 5:
				printf("\n---- TYPE V ----\n\n");
				printf("**Generate the bill for each customer for the past month.**\n");
				printf("Input Year, Month ( hint: 2022 4  ):");
				char year5[10];
				char year6[10];
				char month1[10];
				char month2[10];
				int temp5; //year1
				int temp6; //month1
				int temp7; //year2
				int temp8; //month2
				scanf_s("%d %d", &temp5, &temp6);
				if (temp6 == 12) {
					temp7 = temp5 + 1;
					temp8 = 1;
				}
				else {
					temp7 = temp5;
					temp8 = temp6 + 1;
				}
				sprintf(year5, "%d-", temp5);
				sprintf(month1, "%d", temp6);
				sprintf(year6, "%d-", temp7);
				sprintf(month2, "%d-01'", temp8);

				printf("\n** Bill List at year: %d month: %d **\n\n", temp5, temp6);
				memset(query, 0, sizeof(query));
				strcat_s(query, "select  c.customer_id, c.name, c.address, s.package_price, pay_date, service_id , b.date from bill_pay as b inner join shipments as s inner join  customers as c  inner join packages as p on p.package_price=s.package_price and c.customer_id=s.customer_id and b.bill_id=s.shipment_id and s.started_date>='");
				strcat_s(query, year5);
				strcat_s(query, month1);
				strcat_s(query, "-01' and s.started_date<'");
				strcat_s(query, year6);
				strcat_s(query, month2);

				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						if (sql_row[4])
							printf("Date: %s Customer id: %s Customer name: %s Customer address: %s \nService_id: %s Each Price: %s won(Paid)\n\n", sql_row[6], sql_row[0], sql_row[1], sql_row[2], sql_row[5], sql_row[3]);
						else
							printf("Date: %s Customer id: %s Customer name: %s Customer address: %s \nService_id: %s Each Price: %s won(You have to pay!)\n\n", sql_row[6], sql_row[0], sql_row[1], sql_row[2], sql_row[5], sql_row[3]);

					}
					mysql_free_result(sql_result);
				}

				break;
			default: printf("\nInput Correct Num!\n");
				break;


			}

		}
	}

	FILE* crud2 = NULL;
	fopen_s(&crud2, "20181256_crud_d.txt", "r");
	char read_temp[1000];
	int state = 0;
	const char* query;
	while (!feof(crud2))
	{
		query = fgets(read_temp, sizeof(read_temp), crud2);
		state = mysql_query(connection, query);
	}
	fclose(crud2);

	mysql_close(connection);

	return 0;
}





/*

	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t6. TYPE 6\n");
	printf("\t7. TYPE 7\n");
	printf("\t0. QUIT\n");
	//printf("----------------------------------\n");
	printf("\n\n");
	printf("---- TYPE 5 ----\n\n");
	printf("** Find the top k brands by unit sales by the year**\n");
	printf(" Which K? : 3\n");

	return 0;

}
*/