

object Uygulama extends App {
  
  //topla fonksiyonu cagirabiliriz
  Toplama.topla(10 , 20)
  
  //Ya da varsayilan apply method ile cagirabilirz
  Toplama(1,2)
  
  //Sekil tipinden bir array oluşturuyoruz
  //içinde hem Kare hem Diktorgen nesneler ekleyebiliriz
  //cunku ikisi Sekil tipinden miras alıyor
  val sekilDizisi = new Array[Sekil](10);
  
  //birinci eleman diktorgen tipinden 
  sekilDizisi(0) = new Dikdortgen(5,2);
  
  //ikinci eleman Kare tipinden
  sekilDizisi(1) = new Kare(6);
  
  println(sekilDizisi(0).toString())
  println(sekilDizisi(1).toString())
}