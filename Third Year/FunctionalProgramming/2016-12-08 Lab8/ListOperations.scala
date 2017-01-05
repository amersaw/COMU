object HiScala extends App {
  def reverse(lst:List[Int]):List[Int]={
    lst match {
      case Nil => throw new Exception("Error")
      case List(x) => lst
      case x::xs=> reverse(xs) :+ x // (:+) operatoru demek ki sonuna ekleme
    }
  }  

  def last(lst:List[Int]):Int = {
    lst match{
      case Nil => throw new Exception("Error")
      case List(x) => x
      case x::xs => last(xs)
    }
  }

  def head(lst:List[Int]):Int ={
    lst match{
      case Nil => throw new Exception("Error")
      case x::xs => x
    }
  }

  //Son eleman çıkarıtan fonksiyonu
  def Init(lst:List[Int]):List[Int] = {
    lst match{
      case Nil => throw new Exception("Error")
      case List(x) => Nil
      case x::xs => x::Init(xs)
    }
  }

}
