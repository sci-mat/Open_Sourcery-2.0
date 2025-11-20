#include<stdio.h>
#include<math.h>
int main()
{
    float a,b,c,d,p,q,r,s,det,adj,x,y;
    printf("Enter a,b,c for first line (ax+by+c=0): ");
    scanf("%f%f%f", &a,&b,&c);
    printf("\nEnter p,q,r for second line (px+qy+r=0): ");
    scanf("%f%f%f", &p,&q,&r);
    det=a*q-b*p;
    x=(b*r-q*c)/det;
    y=(p*c-a*r)/det;
    printf("The intersection of the two lines are (%f,%f)",x,y);
    return 0;
    
}