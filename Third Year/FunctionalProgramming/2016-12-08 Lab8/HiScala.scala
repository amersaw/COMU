object HiScala extends App {
  val y = 1 :: 2 :: 3 :: Nil

  val a = List(1)
  val b = List(1,2)
  val c = List(1,2,3,4,5)
  val d = List()

  printList(c)
  var l = removeAt(c,9)
  printList(l)

  def removeAt[T] (xs:List[T], n:Int):List[T]={
    xs match{
      case Nil=> Nil
      case y::ys=>{
       if(n==0) ys
       else         y::removeAt(ys,n-1)
      }
    }
  }
  def printList[T](l:List[T])={
    println("===========")
    l.foreach(x=>{
      println(x);
    })
  }

}
