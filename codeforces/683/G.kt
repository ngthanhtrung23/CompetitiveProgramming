import java.util.*

fun gcd(_a: Long, _b: Long): Long {
    var a = _a
    var b = _b
    while (a != 0L) {
        var c = a;
        a = b % a;
        b = c;
    }
    return b;
}

class F(_x: Long, _y: Long) {
    val g = gcd(_x, _y)
    val x = _x / g
    val y = _y / g
}

fun add(a: F, b: F): F {
    return F(a.x * b.y + a.y * b.x, a.y * b.y)
}

fun p10(a: Int): Long {
    var res = 1L
    for (i in 1..a) {
        res *= 10L
    }
    return res
}

fun main(args: Array<String>) {
    var s = readLine()!!.split('.')[1]
    s = s.substring(0, s.length - 1)
    val (a, b) = s.split('(')

    if (a.length == 0) {
        val z = F(b.toLong(), p10(b.length) - 1)
        println("${z.x}/${z.y}")
    } else {
        val x = F(a.toLong(), p10(a.length))
        val y = F(b.toLong(), p10(a.length) * (p10(b.length) - 1))

        val z = add(x, y)
        println("${z.x}/${z.y}")
    }
}
