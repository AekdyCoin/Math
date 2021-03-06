typedef long long LL ;

/* a Mod b
 * $a could be negative, $b have to be positive integer
 */
 
template<class T> T Mod( T a, T b) {
  	a%=b;
	return a<0?a+b:a;
}

/* a*b Mod c
 * $a,$b could be negative, $c have to be positive integer
 */
 
template<class T> T MulMod( T a, T b, T c) {
	T r=0;
	a=Mod(a,c);
	b=Mod(b,c);
	while(b != 0) {
		if(b & 1) if((r += a) >= c) r-= c;
		if( (a<<=1) >= c) a-= c;
		b>>=1;
	}
	return r;
}

template <class T>inline T GCD(T A,T B){T C;while(B!=0)C=B,B=A%B,A=C;return A;}

template <class T>T EXT_GCD(T a,T b,T& x,T& y)	{
	T t,ret;
	if (!b){
		x=1,y=0;
		return a;
	}
	ret=EXT_GCD(b,a%b,x,y);
	t=x,x=y,y=t-a/b*y;
	return ret;
}

LL lrand() {return (LL)rand() * rand() ; }

/*
 * Must guarantee c+c DO NOT OVERFLOW!!!(both a, b, c are INTEGERS)
 * $a or $b may be negative, however $c must be positive
 */
template<class T> T PowMod( T a, T b, T c) {
   	T r=Mod((T)1,c);
   	a=Mod(a,c);
	while(b != 0) {
		if(b & 1) r=MulMod(r, a, c);
		a = MulMod( a, a, c);
		b >>= 1;
	}
	return r;
}

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

template<class T>inline T Pollard_rho(T c, T num){
	int i(1), k(2);
	T x = lrand() % num;
	T y = x, comDiv;
	do{
		++i;
		x=MulMod(x,x,num) + c;
		if(x >= num) x-=num;
		if (x==y)break;
		comDiv=GCD((y-x+num)%num,num);
		if (comDiv>1&&comDiv<num )return comDiv;
		if(i==k){
			y=x;
			k*=2;
		}
	}while(1);
	return num;
}

/*
 * Algorithm Time Complexity( Exception) O(n^0.25) 
 */
 
template<class T> void FastFactorization(T num){
	if (FastPrimeDet(num)){
		// num is one prime factor
		// do sth here
		return;
	}
	T factor;
	do{
		factor=Pollard_rho(lrand()%(num-1) + 1, num);
	}while (factor>=num);
	FastFactorization(factor);
	FastFactorization(num/factor);
}

/*
 * solve ax=b(mod n)
 * $x is the smallest solution.
 * function return pair< # of solution, x >
 * */

template<class T>
pair< T, T > SolveModLinearEquation( T a, T b, T n) {
	T g,x,y,e,i,gap;
	g=EXT_GCD(a,n,x,y);
	if(b%g)return make_pair( 0, 0) ;
	e=(x*(b/g)%n+n)%n; gap=n/g;
	return make_pair(g, e-(e/gap)*gap);
}

/*
 * x = c1 ( mod b1)
 * x = c2 ( mod b2)
 * Merge to: x = c(mod b) (if could not merge, just return false, otherwise return true )
 */

template<class T>
bool MergeModLinearEquationS(T c1,T b1,T c2,T b2,T &c,T &b){
  	T tb1=b1,tb2=b2;
	c=Mod(c2-c1,b2);
	T G=GCD(b1,b2);
	if(c%G)return false;
	c/=G;b1/=G;b2/=G;
	c=MulMod(c,SolveModLinearEquation(b1,(T)1, b2).second,b2);
	b=tb1*(tb2/G);
	c=MulMod(c,tb1,b);
	c=Mod(c+c1,b);
	return true;
}

