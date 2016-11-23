

object Lab5 extends App {
  val karisikSayilar = Array(6,5,2,7,8,3)
  
  val siraliSayilar = sirala(karisikSayilar)
  
  def sirala(dizi:Array[Int]):Array[Int]={
    var sorted :Int=0;
    while(sorted<dizi.length){
      println("--------")
      for(j <- sorted until 0 by -1){
        println("j="+j)
        println(dizi(j-1)+"  with  "+dizi(j))
        if(dizi(j-1)>dizi(j)){
          println("true");
          var temp=dizi(j-1);
          dizi(j-1)=dizi(j)
          dizi(j)=temp
          
          yazdir(dizi)
        }
        
        else{
          println("false")
        }
      }
      sorted=sorted+1;
      println("sorted="+sorted)
    }
    Array(1)
  }
  def yazdir(dizi:Array[Int])={
    for(i <- dizi){
      print(i + " ")
      
    }
    println()
  }
}