import numpy as np

def fft(x):
    N = len(x)
    if N <= 1:
        return x

    even = fft(x[0::2])
    odd = fft(x[1::2])

    T = [np.exp(-2j * np.pi * k / N) * odd[k] for k in range(N // 2)]

    return [even[k] + T[k] for k in range(N // 2)] + [even[k] - T[k] for k in range(N // 2)]


#signal = np.array([1, 2, 3, 4], dtype=complex)  #Sample signal

signal = np.array([])
a=int(input("Size of array:"))
for i in range(a):
    x=complex(input("Element:"))
    signal = np.append(signal,x)

result = fft(signal)
index = int(input("Enter the index of the DFT coefficient to compute: "))
print("DFT coefficients:", result[index])
