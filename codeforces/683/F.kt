import java.util.*

fun main(args: Array<String>) {
    var s = readLine()!!
    // not start & end with spaces
    s = s.replace(Regex("^ +"), "")
    s = s.replace(Regex(" +$"), "")

    // no 2 consecutive spaces
    s = s.replace(Regex(" +"), " ")

    s = s.toLowerCase()

    // comma
    s = s.replace(Regex(" *, *"), ", ")
    // dot
    s = s.replace(Regex(" *\\. *"), ". ")

    s = s.replace(Regex("^ +"), "")
    s = s.replace(Regex(" +$"), "")

    val n = s.length
    var dot = false
    for (i in 0..n-1) {
        val c = s[i]

        if (c != ' ' && c != '.' && c != ',') {
            if (i == 0 || dot) {
                print(c.toUpperCase())
                dot = false
            }
            else print(c)
        } else {
            if (c == '.') dot = true
            print(c)
        }
    }
    println("")
}
