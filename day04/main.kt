import java.io.File

private val adjacentes = listOf(
    Pair(-1, -1), Pair(-1, 0), Pair(-1, 1),
    Pair(0, -1),               Pair(0, 1),
    Pair(1, -1),  Pair(1, 0),  Pair(1, 1)
)

fun parse(conteudo: String): MutableList<MutableList<Char>> {
    return conteudo
        .trim()
        .lines()
        .map { it.toMutableList() }
        .toMutableList()
}

fun part01(conteudo: String): Int {
    val grid = parse(conteudo)
    var acessiveis = 0

    for (l in grid.indices) {
        for (c in grid[l].indices) {
            if (grid[l][c] == '@') {
                val adj = contaArrobasAdjacentes(grid, l, c)
                if (adj < 4) acessiveis++
            }
        }
    }

    return acessiveis
}

fun part02(conteudo: String): Int {
    val grid = parse(conteudo)
    var totalRemovidos = 0

    while (true) {
        val removidos = removerAcessiveis(grid)
        if (removidos == 0) break
        totalRemovidos += removidos
    }

    return totalRemovidos
}

fun removerAcessiveis(grid: MutableList<MutableList<Char>>): Int {
    val paraRemover = mutableListOf<Pair<Int, Int>>()

    for (l in grid.indices) {
        for (c in grid[l].indices) {
            if (grid[l][c] == '@') {
                val adj = contaArrobasAdjacentes(grid, l, c)
                if (adj < 4) {
                    paraRemover.add(Pair(l, c))
                }
            }
        }
    }

    for ((l, c) in paraRemover) {
        grid[l][c] = '.'
    }

    return paraRemover.size
}

fun contaArrobasAdjacentes(
    grid: List<List<Char>>,
    l: Int,
    c: Int
): Int {
    var contador = 0

    for ((dl, dc) in adjacentes) {
        val nl = l + dl
        val nc = c + dc

        if (
            nl in grid.indices &&
            nc in grid[l].indices &&
            grid[nl][nc] == '@'
        ) {
            contador++
        }
    }

    return contador
}

fun main() {
    val conteudo = File("input.txt").readText()

    println(part01(conteudo))
    println(part02(conteudo))
}
