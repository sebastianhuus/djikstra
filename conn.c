#include <stdio.h>

#include "conn.h"

/*   A B C D E F G H I J
 * A 0 1 5              
 * B 1 0   1            
 * C 5   0   1 1        
 * D   1   0   1 3   4   
 * E     1   0     1    
 * F     1 1   0 1        
 * G       3   1 0   1      
 * H         1     0 2 1      
 * I       4     1 2 0 4
 * J               1 4 0
 */

int connections[10][10] = {
    {  0,  1,  5, -1, -1, -1, -1, -1, -1, -1 },
    {  1,  0, -1,  1, -1, -1, -1, -1, -1, -1 },
    {  5, -1,  0, -1,  1,  1, -1, -1, -1, -1 },
    { -1,  1, -1,  0, -1,  1,  3, -1,  4, -1 },
    { -1, -1,  1, -1,  0, -1, -1,  1, -1, -1 },
    { -1, -1,  1,  1, -1,  0,  1, -1, -1, -1 },
    { -1, -1, -1,  3, -1,  1,  0, -1,  1, -1 },
    { -1, -1, -1, -1,  1, -1, -1,  0,  2,  1 },
    { -1, -1, -1,  4, -1, -1,  1,  2,  0,  4 },
    { -1, -1, -1, -1, -1, -1, -1,  1,  4,  0 }
};

void print_horiz()
{
    for( int i=0; i<10; i++ )
    {
        for( int j=0; j<10; j++ )
        {
            if( connections[i][j] == -1 )
                printf("  " );
            else
                printf("%d ", connections[i][j] );
        }
        printf("\n");
    }
}

void print_vert( )
{
    for( int i=0; i<10; i++ )
    {
        for( int j=0; j<10; j++ )
        {
            if( connections[i][j] == -1 )
                printf("  " );
            else
                printf("%d ", connections[i][j] );
        }
        printf("\n");
    }
}

