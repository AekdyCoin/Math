/*
 * $t is the # of tests (2~3 maybe good!)
 */

template<class T> inline bool FastPrimeDet(T n, int t = 2){
	if(n<2)return false;
	if(n==2)return true;
	if(!(n&0x1))return false;
	
	LL x,m;
	int k,i;
	while(t--){
		k=0;
		for(m=n-1;!(m&0x1);m>>=1,++k);
		x=PowMod((T)lrand()%(n-2)+2,(T)m,(T)n);
		if(x!=1){
			for(i=0;i<k&&x!=n-1;++i)x=MulMod((T)x,(T)x,(T)n);
			if(i==k)return false;
		}
	}
	return true;
}
