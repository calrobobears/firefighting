#define typeR JOIN(type, R)
#define typeC JOIN(type, C)

#ifndef typeRxC
#define typeRxC JOIN(JOIN(type, R), JOIN(x, C))
#endif
#ifndef typeCxR
#define typeCxR JOIN(JOIN(type, C), JOIN(x, R))
#endif

typeRxC operator*(type c, typeRxC A)
{
    typeRxC cA;
    for(int i = 0; i < R*C; i++) cA.data[i] = c*A.data[i];
    return cA;
}

typeRxC operator*(typeRxC A, type c)
{
    return c*A;
}

typeRxC operator/(typeRxC A, type c)
{
    return (1.0/c)*A;
}

typeRxC operator+(typeRxC A, typeRxC B)
{
    typeRxC sum;
    for(int i = 0; i < R; i++) sum[i] = A[i]+B[i];
    return sum;
}

typeRxC operator-(typeRxC A, typeRxC B)
{
    typeRxC sum;
    for(int i = 0; i < R; i++) sum[i] = A[i]-B[i];
    return sum;
}

eq_op(+, typeRxC, typeRxC, typeRxC);
eq_op(-, typeRxC, typeRxC, typeRxC);
eq_op(*, typeRxC, typeRxC, type);
eq_op(/, typeRxC, typeRxC, type);

typeCxR transpose(typeRxC A)
{
    typeCxR At;
    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            At[j][i] = A[i][j];
    return At;
}

typeR operator*(typeRxC A, typeC x)
{
    typeR result = {};
    for(int i = 0; i < R; i++) result += A[i]*x[i];
    return result;
}

#undef typeR
#undef typeC
#undef typeRxC
#undef typeCxR
#undef R
#undef C
