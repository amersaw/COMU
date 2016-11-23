import scala.collection.mutable.ListBuffer



class Kisi {
  var ad:String="";
  var soyad:String="";
  var erkekMi:Boolean=false;
  var yas:Int=0;
  var arkadaslar:ListBuffer[Kisi]=new ListBuffer[Kisi]();
  
  def ArkadasEkle(k:Kisi)={
    if(!arkadaslar.contains(k))
      arkadaslar+=k;
  }
  def baglantiBul(k:Kisi,derinlik:Int):Boolean={
    if(arkadaslar.contains(k))
      return true;
    
    for(x<-arkadaslar){
       if(x.baglantiBul(k,derinlik+1))
         return true;
    }
    return false;
  }
  def baglantiBul(f:Kisi=>Boolean,derinlik:Int):ListBuffer[Kisi]{
    for(arkadas<-arkadaslar){
      //......... daha tamamlanmadi
    }
  }
  
  
}
