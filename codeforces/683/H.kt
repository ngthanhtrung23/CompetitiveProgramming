import java.util.*

fun mul(a: IntArray, b: IntArray, n: Int): IntArray {
    var res = IntArray(n, {i: Int -> 0})

    for (i in 0..n-1) {
        res[i] = a[b[i]]
    }
    return res
}

fun inv(a: IntArray, n: Int): IntArray {
    var res = IntArray(n, {i: Int -> 0})
    for (i in 0..n-1) {
        res[a[i] - 1] = i
    }
    return res
}

fun main(args: Array<String>) {
    val (sn, sk) = readLine()!!.split(' ')
    val n = sn.toInt()
    var k = sk.toLong()
    var a = readLine()!!.split(' ').map(String::toInt).toIntArray()
    a = inv(a, n)

    var res = IntArray(n, { i: Int -> i+1})
    while (k > 0) {
        if (k % 2 == 1L) {
            res = mul(res, a, n)
        }
        k /= 2
        a = mul(a, a, n)
    }

    for (x in res) {
        print("$x ")
    }
    println("")
}
