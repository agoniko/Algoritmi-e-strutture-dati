#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *createJumps( int, int );


int main() {
	int r, c; 
	scanf( "%d%d", &r, &c);
	
	int *jump = createJumps( r, c );

	int n = r*c ;
	printf( "%d\n", n );
	for ( int i = 1; i <= n; i++ )	
		printf( "%d ", jump[i] );
	printf( "\n" );
	
	return 0;
}

int *createJumps( int r, int c ){
	int n = r * c;
	int *jump = malloc( (n +1) * sizeof(int) ); // aggiungo n+1 e tolto * a int
	
	int s, m, t;
	scanf( "%d", &s );
	while ( s > 0) {	
		scanf( "%d%d", &m, &t );
		jump[m] = t; //scambiato m con t 
        s--; //decremento il contatore altrimenti
        // ricadiamo in un ciclo infinito
	}

	
   // c * caselle coperte + start % c - 1;

	int l, start, len;
	scanf( "%d", &l );
	for (int i = 0; i < l; i++ ) {	
		scanf( "%d%d", &start, &len );
		int row, col, end;
		row = r -1 - (start - 1)/c; 
		col = (start-1) % c;
		if ( ( row + r ) % 2 == 0 ) 
			col = c - col;

		row = row - len + 1;
		end = c * ( r - row );
		if ( ( row + r ) % 2 == 0  )
			end -= col;
		else 
			end += col - c; // tolto +1
		
		jump[start] = end;
	}

	return jump;
}








