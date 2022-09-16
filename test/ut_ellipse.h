#include "../src/ellipse.h"

//test driven first not implement code first
//用ASSERT_TRUE不好,蓋房子要搭鷹架 ,軟體的鷹架即是測試 call "scafolding"
TEST(Shapes, CreateEllipse){
  Ellipse(2.0, 1.0);
  ASSERT_NO_THROW(Ellipse(4.0, 3.0));
}
//做完一個測試,就做個code review 做code view讓程式更好
TEST(Shapes, EllipseAreaTest){
  Ellipse ellipse("1",3.712, 2.556);
  ASSERT_NEAR(29.807,ellipse.area(),0.001);
}

TEST(Shapes, EllipsePermiterTest){
  Ellipse ellipse(3.712, 2.556);
  ASSERT_NEAR(20.683,ellipse.perimeter(),0.001);
}

TEST(Shapes, EllipseInfoTest){
  Ellipse ellipse(3.712, 2.556);
  ASSERT_EQ("Ellipse (3.712, 2.556)", ellipse.info());
}

TEST(Shapes, InvalidEllipse){
  try{
    Ellipse("1",0.0, 1.0);
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("This is not an ellipse!", e);
  }
}

TEST(Shapes, InvalidOpeartionEllipseAddShape){
  try{
    Ellipse e43(3.712, 2.556);
    Shape * e76 = new Ellipse(7, 6);
    e43.addShape(e76);
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can add shape!", e);
  }
}

TEST(Shapes, InvalidOpeartionEllipseDeleteShape){
  try{
    Ellipse e76(7, 6);
    e76.deleteShapeById("2");
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can delete shape!", e);
  }
}

TEST(Shapes, InvalidOpeartionEllipseGetId){
  try{
    Ellipse e76(7, 6);
    e76.getShapeById("2");
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can get shape!", e);
  }
}

TEST(Shapes, EllipseColorTest){

  Ellipse e76("5",7, 6);
  Ellipse e54("5",5, 4 , "red");
  ASSERT_EQ("white",e76.color());
  ASSERT_EQ("red",e54.color());
}

TEST(Shapes, EllipseTypeTest){
  Ellipse e76("5",7, 6);
  ASSERT_EQ("Ellipse",e76.type());
}
