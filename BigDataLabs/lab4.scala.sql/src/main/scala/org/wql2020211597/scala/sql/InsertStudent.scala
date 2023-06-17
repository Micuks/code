package org.wql2020211597.scala.sql

import org.apache.spark.SparkConf
import org.apache.spark.SparkContext
import org.apache.spark.sql.types.StructType
import org.apache.spark.sql.types.StructField
import org.apache.spark.sql.types.IntegerType
import org.apache.spark.sql.types.StringType
import org.apache.spark.sql.Row
import org.apache.spark.sql.SQLContext
import java.util.Properties

/** @author
  *   ${user.name}
  */
class InsertStudent {}
object InsertStudent {
  def main(args: Array[String]): Unit = {
    val sparkConf =
      new SparkConf().setAppName("insert-student").setMaster("local")
    val sc = new SparkContext(sparkConf)
    // Student info RDD
    val studentRDD =
      sc.parallelize(Array("3 Zhang M 26", "4 Liu M 27")).map(_.split(" "))
    // Pattern info
    val schema = StructType(
      List(
        StructField("id", IntegerType, true),
        StructField("name", StringType, true),
        StructField("gender", StringType, true),
        StructField("age", IntegerType, true)
      )
    )
    // Row object
    val rowRDD =
      studentRDD.map(p => Row(p(0).toInt, p(1).trim(), p(2).trim(), p(3).toInt))
    // Construct relationship between Row object and pattern
    val studentDF = new SQLContext(sc).createDataFrame(rowRDD, schema)

    // JDBC connect parameters
    val prop = new Properties()
    prop.put("user", "root")
    prop.put("password", "Wql2020211597!")
    prop.put("driver", "com.mysql.jdbc.Driver")
    // Connect to database and append
    studentDF.write
      .mode("append")
      .jdbc("jdbc:mysql://localhost:3306/spark", "spark.student", prop)
  }

}
