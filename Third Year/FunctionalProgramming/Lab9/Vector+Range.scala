object HiScala extends App {

  ///////////////VECTOR
  var sayilar = Vector(2,3,4);
  var vec2 = 1 +: sayilar;  // 1,2,3,4
  var vec3 = vec2 :+ 5;     // 1,2,3,4,5
  var vec4 = 0 +: vec3 :+ 6;// 0,1,2,3,4,5,6

  var range1 = 1 to 5; //1 2 3 4 5
  var range2 = 5 to 1; //5 4 3 2 1
  var range3 = 1 to 10 by 2; //1 3 5 7 9
  var range4 = 1 until 4; // 1 2 3
  var range5 = 9 until 0 by -2; //9 7 5 3 1

}
