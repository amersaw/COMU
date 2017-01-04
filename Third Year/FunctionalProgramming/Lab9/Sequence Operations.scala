import scala.collection.mutable.Queue


object SequenceOperations extends App {

  var even = List(2,4,6,8);
  var odd = List(1,3,5,7,9);
  
  
  //Herhangi eleman s==4 şartı gerçekleştirirse bu fonksiyon true dondürür
  //Sonuc : true
  var x1 = even.exists(s=> s==4)  
  println(x1)

  
  //odd içinde butun elemanlar s%2==1 şartı gerçekleştiriyorsa bu fonksiyon true dondürür
  //Sonuc : true  
  var x2 = odd.forall(s=> s%2==1)
  println(x2)

  
  //even içerisindeki elemanlar odd ile birleşiyor ve 2şer 2şer tuple listesi donduruyor
  //Sonuc : List((2,1), (4,3), (6,5), (8,7))
  var lst = even.zip(odd)
  println(lst)
  
  
  //lst 2şer elemanlar bir liste olması gerekiyor, bunu 2 parça parçanlanıyor
  //1. parça her tuple'in ilk elemanları
  //2. parça her tuple'in ikinci elemanları
  //Sonuc : p1=List(2, 4, 6, 8)
  //        p2=List(1, 3, 5, 7)
  var (p1,p2) = lst.unzip
  println(p1)
  println(p2)

}
