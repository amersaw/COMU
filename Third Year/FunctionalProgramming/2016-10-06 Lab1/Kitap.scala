

class Kitap {
  var adi:String="";
  var basimYili:Int=0;
  
  
  def this(a:Int){
    this();
    this.basimYili = a;
  }
  
  def this(a:String){
    this();
    this.adi=a;
  }
  
  //varsayilan değer ile yapıcı
  def this(a:Int = 1990,s:String){
    this();
    this.adi = s;
    this.basimYili = a;
  }
}