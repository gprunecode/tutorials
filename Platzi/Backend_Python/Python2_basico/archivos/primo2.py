# -*- coding: utf-8 -*-


def is_prime(number):
    if number < 2:
        return False
    for x in range(2, number):
        if number % x == 0:
            return False
    else:
        return True


def run():

    number = int(raw_input('Ingresa un número: '))

    result = is_prime(number)
    if result is True:
        print('{} es primo.'.format(number))
    else:
        print('{} no es primo.'.format(number))


if __name__ == '__main__':
    run()
