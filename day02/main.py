# day02.py

def parse(input_text):
    linhas = input_text.strip().split(",")
    return [linha.split("-") for linha in linhas]


def part01(conteudo):
    intervalos = parse(conteudo)
    soma = 0

    for inicio, fim in intervalos:
        ini = int(inicio)
        fm = int(fim)

        for i in range(ini, fm + 1):
            valor = str(i)
            
            if len(valor) % 2 != 0:
                continue

            metade = len(valor) // 2

            if valor[:metade] == valor[metade:]:
                soma += i

    return soma


def part02(conteudo):
    intervalos = parse(conteudo)
    soma = 0

    for inicio, fim in intervalos:
        ini = int(inicio)
        fm = int(fim)

        for i in range(ini, fm + 1):
            valor = str(i)
            n = len(valor)

            for size in range(1, n // 2 + 1):
                if n % size != 0:
                    continue

                bloco = valor[:size]
                repeticoes = n // size

                if bloco * repeticoes == valor:
                    soma += i
                    break

    return soma


if __name__ == "__main__":
    with open("input.txt", "r", encoding="utf-8") as f:
        conteudo = f.read()

    print("P1:", part01(conteudo))
    print("P2:", part02(conteudo))
