//And fonksiyon
//Bu çözümler aynı sonuç veriyor ama farklı şekilde yazıldı

def and (a:Boolean, b:Boolean) : Boolean ={
	if(a==false && b==false) false
	if(a==false && b==true)  false
	if(a==true && b==false) false
	if(a==true && b==true) true
} 
def and2 (a:Boolean, b:Boolean) : Boolean ={
	if(a==true && b==true) true
	else false
} 
def and3 (a:Boolean, b:Boolean) : Boolean ={
	(a, b)  match {
		case(false, false) =>false
		case(false, true) =>false
		case(true, false) =>false
		case(true, true) =>true 
	} 
} 
def and4 (a:Boolean, b:Boolean) : Boolean ={
	(a, b)  match {
		case(true, true) =>true 
		case _ => false 
	} 
} 
