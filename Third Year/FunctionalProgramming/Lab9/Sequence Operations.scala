import scala.collection.mutable.Queue


object FirstProject extends App {
 
  var even = List(2,4,6,8);
  var odd = List(1,3,5,7,9);
  
  println("exists\n=========")
  //Herhangi eleman s==4 şartı gerçekleştirirse bu fonksiyon true dondürür
  //Sonuc : true
  var x1 = even.exists(s=> s==4)  
  println(x1)

  
  println("\n\nforall\n=========")
  //odd içinde butun elemanlar s%2==1 şartı gerçekleştiriyorsa bu fonksiyon true dondürür
  //Sonuc : true  
  var x2 = odd.forall(s=> s%2==1)
  println(x2)

  
  println("\n\nzip\n=========")
  //even içerisindeki elemanlar odd ile birleşiyor ve 2şer 2şer tuple listesi donduruyor
  //Sonuc : List((2,1), (4,3), (6,5), (8,7))
  var lst = even.zip(odd)
  println(lst)
  
  
  println("\n\nunzip\n=========")
  //lst 2şer elemanlar bir liste olması gerekiyor, bunu 2 parça parçanlanıyor
  //1. parça her tuple'in ilk elemanları
  //2. parça her tuple'in ikinci elemanları
  //Sonuc : p1=List(2, 4, 6, 8)
  //        p2=List(1, 3, 5, 7)
  var (p1,p2) = lst.unzip
  println(p1)
  println(p2)
  
  
  
  println("\n\nflatten\n=========")
  var ll = List(List(1,2),List(3,4),List(),List(5),List(6,7,8))
  //ll list icerisindeki herhangi kolleksiyion ne olursa bozurarak ve sonuc tek boyutlu bir List döndürür
  //Sonuç:List(1, 2, 3, 4, 5, 6, 7, 8)
  var fl = ll.flatten
  println(fl)

}
