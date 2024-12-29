import numpy as np

def gram_schmidt(A):
    """
    Ths function computes an orthogonal basis for the subspace spanned by the vectors in matrix A.
    Also detects linearly dependent vectors.

    Args:
    A: A numpy array where each column represents a vector.

    Returns:
    Q: Orthogonal basis for the subspace spanned by A.
    R: Upper triangular matrix representing the decomposition of A.
    dependent_vectors: List of indices of linearly dependent vectors in A.
    """
    A = A.astype(np.float64)  # Ensure all elements are of float64 type
    m, n = A.shape
    Q = np.zeros((m, n))
    R = np.zeros((n, n))
    dependent_vectors = []

    for j in range(n):
        v = A[:, j]  #Extracting jth column of matrix A
        for i in range(j):
            R[i, j] = np.dot(Q[:, i], A[:, j])
            v -= R[i, j] * Q[:, i]
        R[j, j] = np.linalg.norm(v)
        
        if np.isclose(R[j, j], 0.0):
            dependent_vectors.append(j)
        else:
            Q[:, j] = v / R[j, j]

    return Q, R, dependent_vectors

# Example usage:
# Define the vectors as columns of a matrix
vectors = np.array([[1, 2, 3],
                    [2, 3, 4],
                    [3, 4, 5]], dtype=np.float64)  # Specifying dtype as float64

# Calling the Gram-Schmidt function
Q, R, dependent_vectors = gram_schmidt(vectors)

print("Orthogonal Basis Q:")
print(Q)
print("\nUpper Triangular Matrix R:")
print(R)
if dependent_vectors:
    print("\nLinearly Dependent Vectors (indices):", dependent_vectors)
else:
    print("\nNo linearly dependent vectors found.")
