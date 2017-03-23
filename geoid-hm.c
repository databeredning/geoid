#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
  double lat;
  double lon;
  double height;
} dem_node;


dem_node dem[801][376]; // 301176 points

void create_dem( char * filename )
{
  FILE *fp;
  double lat, lon, height;
  int row = 801;
  int col = 1;
  int i = 0;

  fp = fopen( filename, "r");

  if(fp == NULL)
    exit(EXIT_FAILURE);

  while( fscanf( fp, "%lf %lf %lf", &lat, &lon, &height ) != -1 )
  {
    i++;
    dem[row - 1][col - 1].lat = lat;
    dem[row - 1][col - 1].lon = lon;
    dem[row - 1][col - 1].height = height;
    col++;
    if( col > 376 )
    {
      col = 1;
      row--;
    }
  }

  fclose( fp );
}

double get_dem( double lat, double lon )
{

/*


  y2  Q12------R2-----------Q22
               |
               |
  y   ---------P------------
               |
               |
               |
               |
  y1  Q11------R1----------Q21
               
      x1       x           x2

  R1 = ((x2 - x)/(x2 - x1))*Q11 + ((x - x1)/(x2 - x1))*Q21
  R2 = ((x2 - x)/(x2 - x1))*Q12 + ((x - x1)/(x2 - x1))*Q22
  P  = ((y2 - y)/(y2 - y1))*R1 + ((y - y1)/(y2 - y1))*R2

*/

  int row;
  int col;
  
  double x,x1,x2,y,y1,y2;
  double q11,q12,q21,q22;
  double r1, r2, p;

  row = (int)((double)((lat - 54)/0.02)); 
  col = (int)((double)((lon - 10)/0.04));

  q12 = dem[row+1][col].height;  
  q22 = dem[row+1][col+1].height;  
  q11 = dem[row][col].height;  
  q21 = dem[row][col+1].height;

   x = lon;
  x1 = dem[row][col].lon;  
  x2 = dem[row][col+1].lon;

   y = lat;
  y1 = dem[row][col].lat;  
  y2 = dem[row+1][col].lat;  
 
  r1 = ((x2-x)/(x2-x1))*q11 + ((x-x1)/(x2-x1))*q21;
  r2 = ((x2-x)/(x2-x1))*q12 + ((x-x1)/(x2-x1))*q22;
   p = ((y2-y)/(y2-y1))*r1 + ((y-y1)/(y2-y1))*r2;
/*
  printf(" dem[%d][%d] = %2.7lf %2.7lf %2.4lf\t", 
           row+1, col, dem[row+1][col].lat, dem[row+1][col].lon, dem[row+1][col].height );

  printf(" dem[%d][%d] = %2.7lf %2.7lf %2.4lf\n", 
           row+1, col+1, dem[row+1][col+1].lat, dem[row+1][col+1].lon, dem[row+1][col+1].height );

  printf("                     %2.7lf %2.7lf %2.4lf\n", lat, lon, p );

  printf(" dem[%d][%d] = %2.7lf %2.7lf %2.4lf\t", 
           row, col, dem[row][col].lat, dem[row][col].lon, dem[row][col].height );

  printf(" dem[%d][%d] = %2.7lf %2.7lf %2.4lf\n", 
           row, col+1, dem[row][col+1].lat, dem[row][col+1].lon, dem[row][col+1].height );
*/

  return p;
}

int main(int argc, char *argv[])
{

  FILE *fp;
  double lat,lon,gh;

  fp = fopen( argv[1], "r");

  if(fp == NULL)
  {
    printf("Could not open %s\n", argv[1] );
    exit(EXIT_FAILURE);
  }

  create_dem( "SWEN08_RH2000.dat" );

  while( fscanf( fp,"%lf %lf", &lat, &lon ) != -1 )
  {
    gh = get_dem( lat, lon );
    printf("%2.7lf,%2.7lf,%2.4lf\n", lat, lon, gh );
  }

/*
  gh = get_dem( 60.6664566666667, 17.1324938888889 ); 
  printf("%2.4lf\n",gh);
*/
  exit(EXIT_SUCCESS);
  
}

