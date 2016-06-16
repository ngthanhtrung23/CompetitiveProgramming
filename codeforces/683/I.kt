import java.util.*

fun di(dir: Int): Int {
    when (dir) {
        0 -> return -1
        1 -> return 1
        2 -> return 0
        3 -> return 0
    }
    return 0
}
fun dj(dir: Int): Int {
    when (dir) {
        0 -> return 0
        1 -> return 0
        2 -> return -1
        3 -> return 1
    }
    return 0
}

fun dc(dir: Int): Char {
    when (dir) {
        0 -> return 'n'
        1 -> return 's'
        2 -> return 'w'
        3 -> return 'e'
    }
    return ' '
}

class State(var x: Int, var y: Int, var u: Int, var v: Int, var f: Int, var tr: Char): Comparable<State> {
    override fun compareTo(other: State) = when {
        f < other.f -> -1
        f > other.f -> 1
        else -> 0
    }
}

var a = Array(44, { i: Int -> ""})
var M = 0
var N = 0
var mark = Array(44, { Array(44, { Array(44, { IntArray(44) } )}) })

var tx = Array(44, { Array(44, { Array(44, { IntArray(44) } )}) })
var ty = Array(44, { Array(44, { Array(44, { IntArray(44) } )}) })
var tu = Array(44, { Array(44, { Array(44, { IntArray(44) } )}) })
var tv = Array(44, { Array(44, { Array(44, { IntArray(44) } )}) })
var td = Array(44, { Array(44, { Array(44, { CharArray(44) } )}) })

fun outside(u: Int, v: Int): Boolean {
    return u < 0 || v < 0 || u >= M || v >= N
}

fun go(cur: State, dir: Int): State {
    val next = State(cur.x + di(dir), cur.y + dj(dir), cur.u, cur.v, cur.f + 1, dc(dir))
    if (outside(next.x, next.y) || a[next.x][next.y] == 'X') {
        next.f = -1
        return next
    }

    if (next.u == next.x && next.v == next.y) {
        next.tr = next.tr.toUpperCase()
        next.u += di(dir)
        next.v += dj(dir)

        if (outside(next.u, next.v) || a[next.u][next.v] == 'X') next.f = -1
        else next.f += 9999
    }
    return next
}

fun trace(cur: State) {
    if (td[cur.x][cur.y][cur.u][cur.v] == ' ') {
        return
    }
    var next = State(
            tx[cur.x][cur.y][cur.u][cur.v],
            ty[cur.x][cur.y][cur.u][cur.v],
            tu[cur.x][cur.y][cur.u][cur.v],
            tv[cur.x][cur.y][cur.u][cur.v],
            0, ' ')
    trace(next)
    print(td[cur.x][cur.y][cur.u][cur.v])
}

fun main(args: Array<String>) {
    val (m, n) = readLine()!!.split(' ').map(String::toInt)
    M = m
    N = n
    for (i in 0..m-1) {
        a[i] = readLine()!!
    }

    var yi = -1
    var yj = -1
    var bi = -1
    var bj = -1
    var targeti = -1
    var targetj = -1

    for (i in 0..m-1)
        for (j in 0..n-1)
            if (a[i][j] == 'Y') {
                yi = i
                yj = j
            } else if (a[i][j] == 'B') {
                bi = i
                bj = j
            } else if (a[i][j] == 'T') {
                targeti = i
                targetj = j
            }

    val start = State(yi, yj, bi, bj, 0, ' ')
    var q = PriorityQueue<State>()
    q.add(start)

    for (x in 0..43)
        for (y in 0..43)
            for (i in 0..43)
                for (j in 0..43) {
                    mark[x][y][i][j] = 1000111000
                    td[x][y][i][j] = ' '
                }

    mark[yi][yj][bi][bj] = 0

    while (!q.isEmpty()) {
        val cur = q.remove()
        if (cur.u == targeti && cur.v == targetj) {
            println("YES")
            trace(cur)
            return
        }
        for (dir in 0..3) {
            val next = go(cur, dir)
            if (next.f >= 0 && next.f < mark[next.x][next.y][next.u][next.v]) {
                mark[next.x][next.y][next.u][next.v] = next.f
                tx[next.x][next.y][next.u][next.v] = cur.x
                ty[next.x][next.y][next.u][next.v] = cur.y
                tu[next.x][next.y][next.u][next.v] = cur.u
                tv[next.x][next.y][next.u][next.v] = cur.v
                td[next.x][next.y][next.u][next.v] = next.tr
                q.add(next)
            }
        }
    }
    println("NO")
}
