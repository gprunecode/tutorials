# -*- coding: utf-8 -*-

def palindrome(word):
    reversed_word = word[::-1]

    if word == reversed_word:
        return True

    return False


if __name__ == '__main__':
    word = str(raw_input('Escribe una palabra: '))

    result = palindrome(word)

    if result is True:
        print('{} sí es un palíndromo.'.format(word))
    else:
        print('{} no es un palíndromo.'.format(word))
