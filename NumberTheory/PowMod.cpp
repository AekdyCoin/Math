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
