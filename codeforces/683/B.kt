import java.util.*

fun main(args: Array<String>) {
    var a = ArrayList<Pair<Int, String>> ();
    val (n) = readLine()!!.split(' ').map(String::toInt)

    for (i in 0..n - 1) {
        val (name, t) = readLine()!!.split(' ')
        val x = t.toInt()
        a.add(Pair(x, name))
    }
    a.sortBy { it: Pair<Int, String> -> it.first }

    for (x in a)
        println(x.second)
}