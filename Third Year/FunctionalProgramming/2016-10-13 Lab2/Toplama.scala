

object Toplama {
  var toplam : Double =0.0
  def topla(x:Double,y:Double)={
    toplam = x+y;
    println("Son toplama sonucu :"+toplam)
    toplam;
  }
  
  def apply (x:Double,y:Double)={
    topla(x,y);
  }
}