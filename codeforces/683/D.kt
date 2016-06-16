import java.util.*

fun main(args: Array<String>) {
    var (q) = readLine()!!.split(' ').map(String::toInt)
    for (test in 1..q) {
        val (m, n, x) = readLine()!!.split(' ').map(String::toInt)
        var good = 0

        for (i in 1..m) {
            if (x % i == 0 && x / i <= n) {
                good = 1
                break
            }
        }

        if (good == 0) println("No")
        else println("Yes")
    }
}