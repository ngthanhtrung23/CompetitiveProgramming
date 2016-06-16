import java.util.*

fun main(args: Array<String>) {
    var (n) = readLine()!!.split(' ').map(String::toInt)
    var a = readLine()!!.split(' ').map(String::toInt)
    var b = Array<Int>(n, {i: Int -> a[i]})

    for(turn in 1..n) {
        var x = 0
        for (i in 0..n-1)
            if (b[i] == 0) {
                b[i] = -1
                x = i
                break
            }
        print("${x+1} ")

        for (i in 0..x-1) {
            b[i] = b[i] - 1
        }
    }
}