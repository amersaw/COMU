

object App extends App {
  println("test");
  
  //Yapici
  var k = new Kitap();
  var k2 = new Kitap(1903);
  var k3 = new Kitap("Some Stuff");
  var k4 = new Kitap(s="Some Stuff");
  val kitapDizisi = new Array[Kitap](10);

  //for döngüsü
  for(i<-0 until kitapDizisi.length){
    kitapDizisi(i) = new Kitap("Deneme-"+i);
  }
  
  //for(x <-0 until kitapDizisi.length){
  //  println("Kitap adi : " + kitapDizisi(x).Adi);
  //}
  
  //Yada foreach gibi:
  
  
  for(k <-kitapDizisi){
    println("Kitap adi : " + k.adi);
  }
  
  
  
  
}