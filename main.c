#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct customer
{
	int c_custkey;//顾客编号 
	char c_ment[10];//市场部门 
}cus;

typedef struct lineitme
{
	int l_orderkey;//订单号 
	float l_price;//价格 
	char sdate[10];//发货时间 
}line;

typedef struct orders
{
	int o_orderkey;//订单号 
	long int o_custkey;//顾客编号 
	char odate[10];//下单时间 
}order;

typedef struct result
{
	int l_orderkey;//订单号 
	char o_orderdate[10];//下单时间 
	double l_extendedprice;//销售额 
}select_result;

int main(int argc,char **argv)
{
    int q,p;
    p=atoi(argv[4]);
    printf("%d",p);
    for(q=0;q<p;q++)
    {
    	int k,j,l = 0,m = 0,i = 0;
	char order_date[] = " ";
	char ship_date[] = " ";
	strcpy(order_date,argv[6+q*4]);
	strcpy(ship_date,argv[7+q*4]);
	cus customer[1000];
	line lineitme[3000];
	order orders[10000];
	
	FILE* fp;
	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Can not1\n");
		exit(1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%d|%s", &customer[i].c_custkey, &customer[i].c_ment);
		i++;
	}
	/*
	j= i;
	for(i=0;i<j;i++)
		printf("%d%s\n",customer[i].c_custkey,customer[i].c_ment);
	*/
	fclose(fp);


	if ((fp = fopen(argv[3], "r")) == NULL)
	{
		printf("Can not2\n");
		exit(1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%d|%f|%s", &lineitme[i].l_orderkey, &lineitme[i].l_price, &lineitme[i].sdate);
		i++;
	}
	/*
	j = i;
	for(i=0;i<j;i++)
		printf("%d %f %d-%d-%d\n",lineitme[i].l_orderkey,lineitme[i].l_price,lineitme[i].sdate.year,lineitme[i].sdate.mouth,lineitme[i].sdate.day);
	*/
	fclose(fp);


	if ((fp = fopen(argv[2], "r")) == NULL)
	{
		printf("Can not3\n");
		exit(1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%d|%ld|%s", &orders[i].o_orderkey, &orders[i].o_custkey, &orders[i].odate);
		i++;
	}
	/*
	j = i;
	for(i=0;i<j;i++)
		printf("%d %ld %d-%d-%d\n",orders[i].o_orderkey,orders[i].o_custkey,orders[i].odate.year,orders[i].odate.mouth,orders[i].odate.day);
	*/
	fclose(fp);

	
	select_result result1[2000];
	select_result result2[2000];

//	for (i = 0; i < 100; i++)//customer i 
//	{
		for (j = 0; j < 5000; j++)//orders j
		{
			for (k = 0; k < 1000; k++)//lineitme k
				if (customer[i].c_custkey == (orders[j].o_custkey%100) && orders[j].o_orderkey == lineitme[k].l_orderkey && (strcmp(orders[j].odate, order_date) < 0) && (strcmp(lineitme[k].sdate, ship_date) > 0))
				{
					result1[l].l_orderkey = lineitme[k].l_orderkey;
					strcpy(result1[l].o_orderdate, orders[j].odate);
					result1[l].l_extendedprice = lineitme[k].l_price;
					l++;
					
				}
		}
	
//	}

	for (i = 0; i < l; i++)
	{
	
		if (i == 0)
		{
			result2[m].l_orderkey = result1[i].l_orderkey;
			strcpy(result2[m].o_orderdate, result1[i].o_orderdate);
			result2[m].l_extendedprice = result1[i].l_extendedprice;
			continue;
		}
		if (result1[i].l_orderkey == result1[i - 1].l_orderkey)
		{
			result2[m].l_extendedprice = result2[m].l_extendedprice + result1[i].l_extendedprice;

		}
		else
		{

			m++;
			result2[m].l_orderkey = result1[i].l_orderkey;
			strcpy(result2[m].o_orderdate, result1[i].o_orderdate);
			result2[m].l_extendedprice = result1[i].l_extendedprice;

		}
	
	}
	//printf("%s",order_date);
	//printf("%-10d|%-11s|%-20.2lf\n",result2[0].l_orderkey,result2[0].o_orderdate,result2[0].l_extendedprice);
	printf("l_orderkey|o_orderdate|revenue\n");
	//q=0;
	//printf("%d\n",q);
	//printf("%d",atoi(argv[8+4*q]));
	for(i=0;i<atoi(argv[8+4*q]);i++)
		{
			
			if(result2[i].l_orderkey == 0)
			{
				continue; 
			} 
			else
			{
				printf("%-10d|%-11s|%-20.2lf\n",result2[i].l_orderkey,result2[i].o_orderdate,result2[i].l_extendedprice);
			}
			
		}
	}
    return 0;
}


