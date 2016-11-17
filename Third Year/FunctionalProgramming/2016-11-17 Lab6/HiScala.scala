
/**
  * Created by Amer on 17/11/2016.
  */
import domain._
object HiScala extends App {
  var Kusler = List(new Sahin(), new Penguin(),new Marti());
  Kusler.foreach(k=>
    {
      println(k.getClass())
      k match {
        case k:Ucabilen with Yuzebilen => k.uc();k.yuz()
        case k:Ucabilen => k.uc();
        case k:Yuzebilen=>k.yuz();
      }
    }
  )
}
