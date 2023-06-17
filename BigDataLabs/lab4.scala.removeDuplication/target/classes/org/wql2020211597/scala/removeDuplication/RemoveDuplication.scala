package org.wql2020211597.scala.removeDuplication
import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.rdd.UnionRDD

/** @author
  *   ${user.name}
  */
class RemoveDuplication {}
object RemoveDuplication {

  def foo(x: Array[String]) = x.foldLeft("")((a, b) => a + b)

  def main(args: Array[String]) {
    val sparkConf =
      new SparkConf().setAppName("remove-duplication").setMaster("yarn")
    val sc = new SparkContext(sparkConf)
    val textA: RDD[String] = sc.textFile("A.txt")
    val textB: RDD[String] = sc.textFile("B.txt")
    val linesA: RDD[String] = textA.flatMap((line: String) => {
      line.split("\n")
    })
    val linesB: RDD[String] = textB.flatMap((line: String) => {
      line.split("\n")
    })
    val linesC: RDD[String] = linesA.union(linesB)
    val ret = linesC.distinct().sortBy(kv => kv.charAt(7), false)
    print(ret.collect().mkString(","))
    ret.saveAsTextFile("hdfs://wql-2020211597-0004:8020/remove-duplication")
    sc.stop()
    // Concat A and B's lines to produce linesC
    // val linesC: RDD[String] = linesA.join(linesB)
  }

}
