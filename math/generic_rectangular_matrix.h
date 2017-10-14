/* including this file defines matrices of type type and size NxM or MxN,
 */

/*TODO: as needed, diagonalization/jordanlization, exponential, finding eigenvectors, any other operations*/

#define typeN JOIN(type, N)
#define typeM JOIN(type, M)

#ifndef typeNxM
#define typeNxM JOIN(JOIN(type, N), JOIN(x, M))
#endif
#ifndef typeMxN
#define typeMxN JOIN(JOIN(type, M), JOIN(x, N))
#endif
#define typeNxN JOIN(JOIN(type, N), JOIN(x, N))
#define typeMxM JOIN(JOIN(type, M), JOIN(x, M))

struct typeNxM
{
    union
    {
        struct
        {
            typeN columns[M];
        };
        type data[N*M];
    };
    
    typeN& operator[](int i)
    {
        return columns[i];
    }
};

struct typeMxN
{
    union
    {
        struct
        {
            typeM columns[N];
        };
        type data[M*N];
    };
    
    typeM& operator[](int i)
    {
        return columns[i];
    }
};

#define R N
#define C M
#include "generic_rectangular_matrix_helper.h"

#define R M
#define C N
#include "generic_rectangular_matrix_helper.h"

typeM operator*(typeN x, typeNxM A)
{
    typeMxN At = transpose(A);
    return At*x;
}

typeN operator*(typeM x, typeMxN A)
{
    typeNxM At = transpose(A);
    return At*x;
}

typeNxN operator*(typeNxM A, typeMxN B)
{
    typeNxN product;
    for(int i = 0; i < N; i++) product[i] = A*B[i];
    return product;
}

typeMxM operator*(typeMxN A, typeNxM B)
{
    typeMxM product;
    for(int i = 0; i < M; i++) product[i] = A*B[i];
    return product;
}

#undef typeNxM
#undef typeMxN
#undef typeN
#undef type
#undef N
#undef M
