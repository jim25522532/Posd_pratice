#include "../src/rectangle.h"
#include <string>
//test driven first not implement code first
//用ASSERT_TRUE不好,蓋房子要搭鷹架 ,軟體的鷹架即是測試 call "scafolding"
TEST(Shapes, CreateRectangle){

  Shape * r34 = new Rectangle(3.0,4.0);
  ASSERT_EQ(12.0, r34->area());

  Shape * r56 = new Rectangle("1",5.0,6.0);
  Shape * r55 = new Rectangle("1",5.0,5.0,"red");
}

TEST(Shapes, invalidOperationOnShape){
  Rectangle * r34 = new Rectangle(3.0,4.0);
  Rectangle * r22 = new Rectangle(2.0,2.0);
  try{
    r34->addShape(r22);
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can add shape!",e);
  }

}

TEST(Shapes, RectangleAreaTest){
  Rectangle r34(3.41,4.22);
  ASSERT_NEAR(14.390,r34.area(),0.001);
}

TEST(Shapes, RectanglePermiterTest){
  Rectangle r34(3.712, 2.556);
  ASSERT_NEAR(12.536,r34.perimeter(),0.001);
}

TEST(Shapes, RectangleInfoTest){
  Rectangle rectangle(3.712, 4);
  ASSERT_EQ("Rectangle (3.712, 4.000)", rectangle.info());

}

TEST(Shapes, InvalidOpeartionRectangleAddShape){
  try{
    Rectangle r22(2, 3);
    Shape * r44 = new Rectangle(4, 4);
    r22.addShape(r44);
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can add shape!", e);
  }
}

TEST(Shapes, InvalidOpeartionRectangleDeleteShape){
  try{
    Rectangle r22(2, 3);
    r22.deleteShapeById("2");
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can delete shape!", e);
  }
}

TEST(Shapes, InvalidOpeartionRectangleGetId){
  try{
    Rectangle r22(2, 3);
    r22.getShapeById("2");
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can get shape!", e);
  }
}

TEST(Shapes, RectangleTypeTest){
  Rectangle r22(2, 3);
  ASSERT_EQ("Rectangle",r22.type());
}
