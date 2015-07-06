#include<stdio.h>

typedef unsigned char uchar;

/***************初始化128bit，全部置0*****************/
void init128(uchar a[128])
{
	int i=0;
	for(i=0;i<128;i++)
	{
		a[i]=0;
	}
}

/**************128bit自增***************************/
void addz(uchar a[128])
{
	int i=0;
	uchar c=1;

	while(c==1&&i<128)
	{
	if(a[i]==0)
	      {a[i]=1;c=0;}
	else
		  {a[i]=0;c=1;}
	i++;
	}
}

/**************格式化输出128bit**********************/
void shuchu(uchar a[128])
{
	int i;
	for(i=127;i>=0;i--)
	{
		printf("%d",a[i]);
		if(i%4==0) printf(",");
		
	}
	printf("\n");
}

/**************128bit循环左移 **********************/
void shiftL(uchar a[],uchar aa[],int bi[],int L)
{
	int n;
	for(n=0;n<L;n++)
	{
		aa[n]=a[128-L+n];
		bi[n]=128-L+n;
	}
	for(n=L;n<128;n++)
	{
		aa[n]=a[n-L];
		bi[n]=n-L;
	}
}

/*求解循环左移方程*/
void QJ(uchar a1[],uchar a2[],int bi[],uchar c[])
{
	int i,n;
	a1[0]=0;
	a2[0]=1;

	n=0;
	for(i=0;i<128;i++)
	{
		if(c[n]==0)
			a1[bi[n]]=a1[n];
		else
			if(a1[n]==0)
				a1[bi[n]]=1;
			else
				a1[bi[n]]=0;
		
		n=bi[n];

	}
	
	n=0;
	for(i=0;i<128;i++)
	{
		if(c[n]==0)
			a2[bi[n]]=a2[n];
		else
			if(a2[n]==0)
				a2[bi[n]]=1;
			else
				a2[bi[n]]=0;
		
		n=bi[n];
	}
}
/*判断两个128bit是否相等*/
int yanzheng(uchar k[],uchar a[])
{
	int n;
	for(n=0;n<128;n++)
	{
		if(k[n]!=a[n])
			{
		     printf("不相等");
		     return 0;
		    }
	}
	printf("相等");
	return 1;
}

/*两个128bit异或运算*/
void xor128(uchar a[],uchar b[],uchar c[])
{
	int i;
	for(i=0;i<128;i++)
		c[i]=a[i]^b[i];
}

/*16字节转化为128bit*/
void char16char128(uchar a16[],uchar a128[])
{
	int i,j,n=0;
	
	for(i=15;i>=0;i--)
	{
		for(j=0;j<8;j++)
		{
			a128[n]=(a16[i]>>j)&0x01;
			n++;
		}
	}


}

/*128bit转化16字节*/
void char128char16(uchar a128[],uchar a16[])
{
	int i,j,n=127;
	uchar t;	
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			a16[i]=(a16[i]<<1)+a128[n];
			n--;
		}
	}
	/*for(i=0;i<16;i++)
	{
		t=a16[i]&0x0f;
		a16[i]=a16[i]>>4;
		a16[i]=a16[i]+ (t<<4);
	}*/
}

/*密钥*/
uchar K[  ] ={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10};
//uchar K[16]={0x11,0x23,0x45,0x67,0xa9,0xAD,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x37,0x17};
uchar coo[] ={0xa3,0x90,0x81,0xb2,0x6f,0x5c,0x32,0x81,0xa3,0x90,0x81,0xb2,0x6f,0x5c,0x32,0x81};


/*驱动函数，验证该算法正确与否*/
void main()
{
	uchar k[128],kl[128],y[128],b[128],a1[128],a2[128],c[128],K1[16],K2[16],co[128];
	int bi[128];
	int i=127,j,z=1;
	int x=1,aaa=0,bbb=0;
	
	init128(k);
	init128(y);
	init128(c);
	init128(a1);
	init128(a2);
	//init128(kl);
	/*while(z)
	{
		addz(k);
		if(k[16]==1) z=0;*/
    
	/***********************16字节转化为128bit*********************/
	char16char128(K,k);
	//char128char16(k,K1);

	/*for(j=0;j<16;++j)
	{
		printf("%X,",K1[j]);
	}
	printf("\n");
	for(j=0;j<16;++j)
	{
		printf("%X,",K[j]);
	}
	printf("\n");*/
	/***********************128bit循环左移15bit*********************/
	shiftL(k,y,bi,15);
	
	/***********************k异或y，结果在c里 *********************/
	xor128(k,y,c);

	//char128char16(c,K2);
	/*for(j=0;j<16;++j)
	{
		printf("%x,",K2[j]);
	}
	/printf("\n");*/

	//char16char128(coo,co);
	
	/***********************求解循环异或方程 *********************/
	QJ(a1,a2,bi,c);
	
	/***********************输出计算结果     *********************/
	/*yanzheng(k,a1);
	yanzheng(k,a2);*/
	printf("原始密钥：\n");
	shuchu(k);
	printf("左移密钥：\n");
	shuchu(y);
	printf("异或值：\n");
	shuchu(c);
	printf("猜测密钥1：\n");
	shuchu(a1);
	printf("猜测密钥2：\n");
	shuchu(a2);
	
	printf("猜测密钥1是否和原始密钥相等：");
	aaa = aaa+ yanzheng(k,a1);
	printf("\n");
	
	printf("猜测密钥2是否和原始密钥相等：");
	bbb = bbb + yanzheng(k,a2);
	printf("\n");
	
	//printf("%d %d\n",aaa,bbb);
	//printf("%d %d",aaa,bbb);

	/*while(i>=0)
	{
		printf("%d ",bi[i]);
		i--;
	}*/
	//printf("%d",sizeof(unsigned long long));

	getchar();
}
