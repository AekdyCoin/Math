
  template<class T> inline bool IsPrime(T n)
	{
		if(n<2)return false;
		if(n==2)return true;
		if(!(n&0x1))return false;
		if(n==3||n==5||n==7||n==11||n==13||n==17||n==19||n==23)return true;
		if(n%3==0||n%5==0||n%7==0||n%11==0||n%13==0||n%17==0||n%19==0||n%23==0)return false;
		if(n<Plimit)
		{
			if(!IsPlistCreated)CreatPlist(Plimit);
			return !IsP[(n-1)>>1];
		}
		LL x,m;
		int k,i,t=2;
		while(t--)
		{
			k=0;
			for(m=n-1;!(m&0x1);m>>=1,++k);
			x=HPowMod((T)lrand()%(n-2)+2,(T)m,(T)n);
			if(x!=1)
			{
				for(i=0;i<k&&x!=n-1;++i)x=MulMod((T)x,(T)x,(T)n);
				if(i==k)return false;
			}
		}
		return true;
	}
