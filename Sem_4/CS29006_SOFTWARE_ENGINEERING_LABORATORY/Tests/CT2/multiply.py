def multiply(*inputs):
    ans = 1
    for num in inputs:
        ans *= num
    print(ans)


if __name__ == '__main__':
    multiply(3, 4)
    multiply(3, 4, 5)
    multiply(3, 4, 5, 6)
