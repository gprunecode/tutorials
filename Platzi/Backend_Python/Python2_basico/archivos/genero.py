# -*- coding: utf-8 -*-

genero = raw_input("Ingresa tu genero: ")
edad = int(raw_input("Ingresa tu edad: "))

if genero == 'masculino':
    if edad > 18:
        print 'Hola, señor.'
    else:
        print 'Hola niño.'
else:
    if edad > 18:
        print 'Hola, señora.'
    else:
        print 'Hola niña.'
