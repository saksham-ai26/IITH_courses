# Function to convert a matrix to CSR format
def convert_to_csr(matrix):    
    values = []       # List to store non-zero values of the matrix
    col_ind = []      # List to store column indices of non-zero values
    row_ind = []      # List to store row indices to locate the start of each row in values
    count = 0         # Counter for non-zero elements in the matrix

    for i in range(len(matrix)):
        row_ind.append(count)  # Record the start index for the current row
        for j in range(len(matrix[i])):
            if matrix[i][j] != 0:
                values.append(matrix[i][j])  
                col_ind.append(j)            
                count += 1

    row_ind.append(count)  
    return values, col_ind, row_ind

# Function to compute the matrix-vector product using CSR format
def matrix_vector_product(csr_matrix, vector):
    values, col_ind, row_ind = csr_matrix
    result = []  # List to store the result of the matrix-vector product
    
    # Iterate over rows of the matrix
    for k in range(len(row_ind) - 1):
        start = row_ind[k]  
        end = row_ind[k + 1]  
        value = 0  
        
        # Iterate over elements in the current row
        for l in range(start, end):
            if l < len(col_ind) and col_ind[l] < len(vector):
                # Compute the dot product of the row and the vector
                value += values[l] * vector[col_ind[l]]
            else:
                break
        
        result.append(value)  # Store the result for the current row in the result vector

    return result

# Example usage:
sparse_matrix = [
    [1, 0, 2, 0],
    [0, 2, 3, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]
]
vector = [1, 2, 3, 4]

# Convert the sparse matrix to CSR format
csr_format_matrix = convert_to_csr(sparse_matrix)

# Compute the matrix-vector product
result_vector = matrix_vector_product(csr_format_matrix, vector)

print(result_vector)
