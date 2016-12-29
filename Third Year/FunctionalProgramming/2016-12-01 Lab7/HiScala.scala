object HiScala extends App {
  val y = 1 :: 2 :: 3 :: Nil

  val a = List(1)
  val b = List(1,2)
  val c = List(1,2,3)
  val d = List()

  val lists = List(a,b,c,d)

  lists.foreach(l=>{
    l match  {
      case Nil => println("NIL")
      case x::xs => println("match"+xs)
      case 1::2::Nil => println("second case")
      case 1::2::xs => println("firstCase")
      case _=> println("Else")
    }
  })
}
