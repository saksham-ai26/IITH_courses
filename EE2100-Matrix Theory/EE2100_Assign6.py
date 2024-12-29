def gaussian_elimination(A, b):
    n = len(A)
    
    # Augment the matrix A with the vector b
    augmented_matrix = [A[i] + [b[i]] for i in range(n)]
    
    for i in range(n):
        # Partial pivoting: Find the row with the largest absolute value in the current column
        max_row = i
        for j in range(i + 1, n):
            if abs(augmented_matrix[j][i]) > abs(augmented_matrix[max_row][i]):
                max_row = j
        
        # Swap the current row with the row with the largest absolute value
        augmented_matrix[i], augmented_matrix[max_row] = augmented_matrix[max_row], augmented_matrix[i]
        
        # Check if the pivot element is zero (no unique solution)
        if augmented_matrix[i][i] == 0:
            return None  # No unique solution
        
        # Scale the current row so that the pivot element becomes 1
        pivot = augmented_matrix[i][i]
        for j in range(i, n + 1):
            augmented_matrix[i][j] /= pivot
        
        # Eliminate other rows
        for j in range(n):
            if j != i:
                factor = augmented_matrix[j][i]
                for k in range(i, n + 1):
                    augmented_matrix[j][k] -= factor * augmented_matrix[i][k]
    
    # Back-substitution to find the solution
    solution = [augmented_matrix[i][-1] for i in range(n)]
    return solution

# Example usage:
import random

# Create a random matrix A and vector b
n = 3  # Adjust the size of the matrix as needed
A = [[random.randint(1, 10) for _ in range(n)] for _ in range(n)]
b = [random.randint(1, 10) for _ in range(n)]

print("Matrix A:")
for row in A:
    print(row)
print("Vector b:", b)

# Solve the system of equations
solution = gaussian_elimination(A, b)

if solution is None:
    print("No unique solution exists.")
else:
    print("Solution:", solution)
