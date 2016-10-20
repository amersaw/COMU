object Lab3 extends App {
   def fact(n:Int):Int= {
    if (n==1) 1
    else n * fact(n-1)
  }
  def fact2(n:Int,sonSonuc:Int):Int= {
    //println("fact2("+n+","+sonSonuc+")")
    if (n==0 || n==1) sonSonuc
    else fact2(n-1,n*sonSonuc)
  }
  def fact3(n:Int,t:Int,sonSonuc:Int):Int= {
    //println("fact3("+n+","+t+","+sonSonuc+")")
    if (t==n) t*sonSonuc
    else fact3(n,t+1,t*sonSonuc)
  }
  def obeb (a:Int,b:Int):Int ={
    if (b==0) a else obeb(b,a%b)
  }
  
  println("5! normal factoriyal fonksiyonu ile :")
  println(fact(5))
  
  println("5! azatan kuyruksal ozyinilmli factoriyal fonksiyonu ile :")
  println(fact2(5,1))
  
  println("5! arttan kuyruksal ozyinilmli factoriyal fonksiyonu ile :")
  println(fact3(5,1,1))
  
  println("\n\n\n")
  //Yuksek Seviyeli Fonksiyonlar ornek
  println("Yuksek Seviyeli Fonksiyonlar ornek")
  def topla(f:Int=>Int, a:Int,b:Int):Int={
    if(a>b) 0
    else f(a) + topla(f,a+1,b)
  }
  def kubu(x:Int):Int = x*x*x;
  
  println("Topla fonksiyonu 1-3 arasinda kubu fonksiyon ile :")
  println(topla(kubu,1,3))
  
  println("Topla fonksiyonu 1-3 arasinda fact fonksiyon ile :")
  println(topla(fact,1,3))
    
  //anonymous fonksiyon ile
  println("Topla fonksiyonu 1-3 arasinda anonymous kare fonksiyon ile :")
  println(topla(x=>x*x,1,3))
  
}