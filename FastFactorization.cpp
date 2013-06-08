
template<class T>inline T Pollard_rho(T c, T num){
	int i(1), k(2);
	T x = rand() % num;
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
	if (IsPrime(num)){
		// num is one prime factor
		// do sth here
		return;
	}
	T factor;
	do{
		factor=Pollard_rho(rand()%(num-1) + 1, num);
	}while (factor>=num);
	FastFactorization(factor);
	FastFactorization(num/factor);
}

