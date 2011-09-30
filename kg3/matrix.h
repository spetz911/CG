#ifndef MATRIX_H
#define MATRIX_H
#include <math.h>




typedef float Matrix[4][4];

typedef float Point[4];


typedef struct Vector {
            float x;
            float y;
            float z;
            Vector(){};
            Vector (float a, float b, float c)
            {
                x = a;
                y = b;
                z = c;
            }
            Vector(Point p1, Point p2)
            {
                x = p2[0] - p1[0];
                y = p2[1] - p1[1];
                z = p2[2] - p1[2];
            }
        } Vector;

void Point_copy(float dst[4], const float src[4])
{
    int i;
    for(i=0;i<4;i++)
    {
        dst[i] = src[i];
    }
}

void Point_mul(Point res,const Matrix M, const Point src){
    int i,j;

  //  M[0][0] = 1;
  //  M[1][1] = 1;
  //  M[2][2] = 1;
  //  M[3][3] = 1;

    for(i=0;i<4;i++)
        {
            res[i] = 0;
            for (j=0;j<4;j++){
                res[i]+= M[j][i]*src[j];
            }
    //        res[i] = src[i];
        }
}

float Point_scalar(Point p1, Point p2){
int i;
float z = 0;

    for (i=0;i<4;i++)
        z+= p1[i]*p2[i];
return z;
}


void Point_minus(Point res, Point p1, Point p2){
int j;
    for (j=0;j<4;j++)
        res[j] = p1[j] - p2[j];
}

void Matrix4f_set_E(float M[4][4]){
int i,j;
    for (i=0;i<4;i++)
        for (j=0;j<4;j++)
        {
            if (i==j)
            {M[i][j] = 1;}
            else
            {M[i][j] = 0;}

        }
}


void Matrix4f_set_scale(Matrix M, float scale)
{
    M[0][0] = scale;
    M[1][1] = scale;
    M[2][2] = scale;
    M[3][3] = 1;
}

void Matrix4f_set_rotX(Matrix M, float rotX){

    M[1][1] = cos(rotX*(3.145/180));
    M[1][2] =-sin(rotX*(3.145/180));
    M[2][1] = sin(rotX*(3.145/180));
    M[2][2] = cos(rotX*(3.145/180));
    M[0][0] = 1;
    M[3][3] = 1;
}

void Matrix4f_set_rotY(Matrix M, float rotateY){

    M[0][0] = cos(rotateY*(3.145/180));
    M[0][2] =-sin(rotateY*(3.145/180));
    M[2][0] = sin(rotateY*(3.145/180));
    M[2][2] = cos(rotateY*(3.145/180));
    M[1][1] = 1;
    M[3][3] = 1;
}
/*
void Matrix4f_Frustum(Matrix M, float l, float r, float b, float t, float n, float f)
{

    M[0][0] = cos(rotateY*(3.145/180));
    M[0][2] =-sin(rotateY*(3.145/180));
    M[2][0] = sin(rotateY*(3.145/180));
    M[2][2] = cos(rotateY*(3.145/180));
    M[1][1] = 1;
    M[3][3] = 1;
}
*/
void Matrix4f_set_rotZ(Matrix M, float rotZ){

    M[0][0] = cos(rotZ*(3.145/180));
    M[0][1] = sin(rotZ*(3.145/180));
    M[1][0] =-sin(rotZ*(3.145/180));
    M[1][1] = cos(rotZ*(3.145/180));
    M[2][2] = 1;
    M[3][3] = 1;
}

void Matrix4f_new(float M[4][4]){
//int i;
    if (!M)
    {
//    M = (float**)malloc(4*sizeof(float*));
//    for (i=0;i<4;i++)
  //      M[i] = (float*)malloc(4*sizeof(float));
    }
    Matrix4f_set_E(M);

}


void Matrix4f_mult(Matrix M1, Matrix M2)
{
float Z[4][4];
int i,j,k;
          for (i=0;i<4;i++)
              for (j=0;j<4;j++)
              {
                    Z[i][j] = 0;
                    for (k=0;k<4;k++)
                    {
                       Z[i][j]+= M1[i][k]*M2[k][j];
                    }
               }
           for (i=0;i<4;i++)
               for (j=0;j<4;j++)
                 M1[i][j] = Z[i][j];

}

Vector Normalize(Point p1, Point p2, Point p3)
{
  Vector n;
  double x1,y1,z1,x2,y2,z2,m;
  x1 = p1[0]-p2[0];
  y1 = p1[1]-p2[1];
  z1 = p1[2]-p2[2];
  x2 = p1[0]-p3[0];
  y2 = p1[1]-p3[1];
  z2 = p1[2]-p3[2];
 n.x = (y1*z2-y2*z1);
 n.y = -(x1*z2-z1*x2);
 n.z = x1*y2-y1*x2;
 m = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
 n.x /= -m;
 n.y /= -m;
 n.z /= -m;
 return n;
}





#endif // MATRIX_H
