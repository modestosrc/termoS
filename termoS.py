#!/usr/bin/env python

import os


def main():
    termos = []
    with open('Lista.txt', 'r') as arquivo1:
        for linha in arquivo1:
            if len(linha) == 6:
                termos.append(linha)
    os.remove('termoS.txt')
    with open('termoS.txt', 'w') as arquivo2:
        for palavra in termos:
            arquivo2.write(palavra)
    return 0


if __name__ == '__main__':
    main()
