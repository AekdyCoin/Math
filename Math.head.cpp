

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

