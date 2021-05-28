#include <stdio.h>
#include <stdlib.h>

int *createJumps( int r, int c ){
	int n = r * c;
	int *jump = malloc( n * sizeof(int) ); //tolto int *
	
	int s, m, t;
	scanf( "%d", &s );
	while ( s > 0) {	
		scanf( "%d%d", &m, &t );
		jump[m-1] = t; //scambiati m e t (da mouth vado a t) e aggiunto -1 perchè indici partono da 0 e non 1
        s--; //aggiunto decremento altrimenti era un ciclo infinito
	}

	
	int l, start, len;
	scanf( "%d", &l );
	for (int i = 0; i < l; i++ ) {	
		scanf( "%d%d", &start, &len );
		int row, col, end;
		row = r - 1 - (start-1)/c;
		col = (start-1) % c;
		if ( ( row + r ) % 2 == 0 ) 
			col = c - col;

		row = row - len + 1;
		end = c * ( r - row );
		if ( ( row + r ) % 2 == 0  )
			end -= col;
		else 
			end += col - c ;//tolto il +1
		
		jump[start-1] = end; // aggiunto -1 perchè indici partono da 0 e non 1
	}

	return jump;
}

int main(){
    int r = 5;
    int c = 6;

    int *j = createJumps(r,c);

    for (int i = 0; i< r*c; i++){
        printf("%d ",j[i]);
    }
    printf("\n");

}