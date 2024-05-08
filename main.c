#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "conn.h"

int permanent[10] = { 0 };
int prev_node[10] = { -1 };
int distance[10][10] = { -1 };

void set_first_line( )
{
    permanent[0] = 1;

    prev_node[0] = 0;

    distance[0][0] = 0;
    for( int i=1; i<10; i++ )
        distance[0][i] = -1;
}

void confirm_line( int row )
{
    printf("==== Line %d ====\n", row );

    printf("Permanent: ");
    for( int i=0; i<10; i++ )
        if( permanent[i] ) printf("%c ", 'A'+i );
    printf("\n");

    printf("Previous: ");
    for( int i=0; i<10; i++ )
        if( prev_node[i]>0 ) printf("%c->%c ", 'A'+i, 'A'+prev_node[i] );
    printf("\n");

    printf("Distances from A: ");
    for( int i=0; i<10; i++ )
    {
        printf( "%c->A:%d ", 'A'+i, distance[row][i] );
    }
    printf("\n");
}

void update_dist( int row, int node )
{
    if( permanent[node] == 0 )
    {
        printf("Trying to update distance from a node that is not permanent yet. ERROR!\n" );
        exit( -1 );
    }

    for( int i=0; i<10; i++ )
    {
        if( connections[node][i] == -1 ) continue;

        int dist = distance[row][node] + connections[node][i];

        if( distance[row][i] < 0 )
        {
            distance[row][i] = dist;
            prev_node[i] = node;
        }
        else if( distance[row][i] > dist )
        {
            distance[row][i] = dist;
            prev_node[i] = node;
        }
    }
}

int find_min( int row )
{
    int val = INT_MAX;
    int ret = -1;
    for( int i=0; i<10; i++ )
    {
        if( permanent[i] ) continue;
        if( distance[row][i] < 0 ) continue;
        if( distance[row][i] < val )
        {
            val = distance[row][i];
            ret = i;
        }
    }
    if( ret < 0 )
    {
        printf("Couldn't find a new minimum in row %d. ERROR!\n", row);
        exit(-1);
    }
    return ret;
}

void set_permanent( int node )
{
    permanent[node] = 1;
}

void copy_line( int row )
{
    for( int i=0; i<10; i++ )
        distance[row][i] = distance[row-1][i];
}

void compute_neighbours( int row, int conn )
{
    for( int i=0; i<10; i++ )
    {
        distance[row][i] = distance[row-1][i];
    }
    for( int i=0; i<10; i++ )
    {
        if( permanent[i] ) continue;
        if( connections[conn][i] < 0 ) continue;

        distance[row][i] = distance[row][conn] + connections[conn][i];
    }
}

void print_final_table( )
{
    printf("==============================\n");
    for( int i=0; i<10; i++ ) printf(" %c ", 'A'+i);
    printf("\n");

    for( int row=0; row<10; row++ )
    {
        for( int i=0; i<10; i++ )
        {
            if( distance[row][i] < 0 )
                printf( ".. ");
            else
                printf("%2d ", distance[row][i] );
        }
        printf("\n");
    }
    printf("==============================\n");
    for( int i=0; i<10; i++ ) printf(" %c ", 'A'+i);
    printf("\n");
    printf("via\n");
    for( int i=0; i<10; i++ ) printf(" %c ", 'A'+prev_node[i]);
    printf("\n");
    printf("==============================\n");
}

int main( int argc, char* argv[] )
{
    print_horiz(); // print_vert();

    set_first_line( );
    update_dist(0,0);
    confirm_line(0);

    int nextnode;

    for( int row=1; row<10; row++ )
    {
        nextnode = find_min(row-1);
        set_permanent( nextnode );
        printf("New minimum is %c\n", 'A'+nextnode);
        copy_line(row);
        update_dist(row,nextnode);
        confirm_line(row);
    }

    print_final_table();
    return 0;
}

