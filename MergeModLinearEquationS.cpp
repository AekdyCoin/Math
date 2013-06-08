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
