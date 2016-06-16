import java.util.*

fun main(args: Array<String>) {
    var a1 = readLine()!!.split(' ').map(String::toInt)
    var a2 = readLine()!!.split(' ').map(String::toInt)

    val n1 = a1.size
    val n2 = a2.size

    a1 = a1.subList(1, n1)
    a2 = a2.subList(1, n2)

    var s1 = a1.toSet()
    var s2 = a2.toSet()

    var res = s1.minus(s2).plus(s2.minus(s1))
    print(res.size)
    for (x in res)
        print(" $x")
}