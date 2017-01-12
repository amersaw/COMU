import scala.annotation.tailrec
object FirstProject extends App {

  case class Kisi (Ad:String,Yas:Int){}
  
  var kisiler = List(Kisi("Amer",23), Kisi("Hasan",26), Kisi("Sakher",29))
  var olderThan25 = for(k<-kisiler if k.Yas>25) yield k
  //yada filter ile :
      olderThan25 = kisiler.filter(k=>k.Yas>25)
  
  for(k<- olderThan25) println(k)
  
  var t = for(i <- 1 until 5;
      j <- 10 until 15;
      if(i+j)>16
        )yield (i,j)
  println(t)
  
  
  def ScalarMultiply(xs:List[Int],ys:List[Int]) :Int = {
    if(xs.length != ys.length) throw new Exception("Error");
    if(xs.length >0)
      xs.head * ys.head + ScalarMultiply(xs.tail, ys.tail)
    else 0      
  }
  
  def ScalarMultiply2(xs:List[Int],ys:List[Int]) :Int = {
    (for(a <- (xs zip ys)) yield a._1*a._2).sum
  }
  
  println(ScalarMultiply(List(2,3), List(5,6)))
  println(ScalarMultiply2(List(2,3), List(5,6)))
  
}
