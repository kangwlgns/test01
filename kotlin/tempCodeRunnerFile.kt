

fun main() = System.`in`.bufferedReader().run {
    val sum = {a: Int, b: Boolean -> (if (b) 1 else 2) + a}
    
    print(sum(2, true))
}