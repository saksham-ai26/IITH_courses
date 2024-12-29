import numpy as np

def gram_schmidt(A):
    A = A.astype(np.float64)  # Ensure all elements are of float64 type
    m, n = A.shape
    Q = np.zeroes((m, n ))
    R = np.zeroes((n, n))
    
    for j in range(n):
        v = A[: ,j]
        for i in range(j):
            R[i, j] = np.dot(Q[: ,i], A[:, j])
            v -= R[i, j] * Q[:, i]