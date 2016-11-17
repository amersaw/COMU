import domain.{Ucabilen, Yuzebilen}
import info.amersaw.codes._

import scala.collection.mutable.ArrayBuffer

/**
  * Created by Amer on 12/11/2016.
  */
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
