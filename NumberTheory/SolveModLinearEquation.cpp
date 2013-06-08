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
