def cholesky_factorization(A, n):
    L = [[0 for x in range(n)] for y in range(n)]
    
    for i in range(n):
        for j in range(i+1):
            sum1 = 0  
            if i == j:
                for k in range(j):
                    sum1 += L[i][k] ** 2
                L[i][j] = (A[i][i] - sum1) ** 0.5
            else:
                for k in range(j):
                    sum1 += L[i][k] * L[j][k]
                L[i][j] = (A[i][j] - sum1) / L[j][j]
    
    return L

A = [[16, 4, 8],
     [4, 10, 10],
     [8, 10, 26]]
n = len(A)

L = cholesky_factorization(A, n)

print("L =", end = '')
for i in range(n):
    for j in range(n):
        print("{:.4f}".format(L[i][j]), end="\t")
    print(" ")


print("L(transpose) =", end = '')
for i in range(n):
    for j in range(n):
        print("{:.4f}".format(L[j][i]), end="\t")
    print(" ")


