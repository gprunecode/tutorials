from primo2 import is_prime


def main():
    n = int(input('Ingrese el numero de primos que desea: '))

    cont = 0
    number = 2
    while cont < n:
        if is_prime(number):
            print(number, end=' ')
            cont += 1
        number += 1


if __name__ == '__main__':
    main()
