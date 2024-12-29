#Function to compute the mean
def mean(numbers):
    return sum(numbers) / len(numbers)

# Function to compute the covariance
def covariance(x, y):
    x_mean = mean(x)
    y_mean = mean(y)
    covar = 0.0
    for i in range(len(x)):
        covar += (x[i] - x_mean) * (y[i] - y_mean)
    return covar / (len(x) - 1)


def compute_polynomial_coefficients(csv_file, n):
    
    data = []
    with open(csv_file, 'r') as file:
        lines = file.readlines()
        for line in lines[1:]:  # Skipping the first line(as given in example)
            x, y = map(float, line.strip().split(','))
            data.append((x, y))
    

    num_data_points = len(data)
    

    sum_xn = [0] * (2 * n + 1)
    sum_xn_y = [0] * (n + 1)
    
    for i in range(2 * n + 1):
        for j in range(num_data_points):
            x, y = data[j]
            sum_xn[i] += x ** i
            if i <= n:
                sum_xn_y[i] += (x ** i) * y
    
    # Creating the system of linear equations
    coefficients = []
    for i in range(n + 1):
        row = []
        for j in range(i, i + n + 1):
            row.append(sum_xn[j])
        coefficients.append(row)
    
    rhs = sum_xn_y
    
    # Solving the system of linear equations using Gaussian elimination
    for i in range(n + 1):
        max_coeff = abs(coefficients[i][i])
        max_row = i
        for k in range(i + 1, n + 1):
            if abs(coefficients[k][i]) > max_coeff:
                max_coeff = abs(coefficients[k][i])
                max_row = k
        # Swapping the rows
        coefficients[i], coefficients[max_row] = coefficients[max_row], coefficients[i]
        rhs[i], rhs[max_row] = rhs[max_row], rhs[i]

        for k in range(i + 1, n + 1):
            factor = coefficients[k][i] / coefficients[i][i]
            rhs[k] -= factor * rhs[i]
            for j in range(i, n + 1):
                coefficients[k][j] -= factor * coefficients[i][j]

    # Back substitution
    result = [0] * (n + 1)
    for i in range(n, -1, -1):
        result[i] = rhs[i]
        for j in range(i + 1, n + 1):
            result[i] -= coefficients[i][j] * result[j]
        result[i] /= coefficients[i][i]

    return result


if __name__ == "__main__":
    csv_file = "Data.csv"  
    n = 2  
    
    coefficients = compute_polynomial_coefficients(csv_file, n)
    print(f"Coefficients of the polynomial of order {n}: {coefficients}")

