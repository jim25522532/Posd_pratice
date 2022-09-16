#include "../src/filter.h"
#include "../src/shape_filter.h"
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_coordinate.h"
#include <list>
#include "../src/shape_setter.h"
class FilterShapeTest : public ::testing::Test {
protected:
  void SetUp() override {

    r34 = new Rectangle("1",3, 4);
    e43 = new Ellipse("3",4, 3);
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    t345 = new Triangle("4",triangleVector);

    shapeList.push_back(e43);
    shapeList.push_back(r34);

    shapeList.push_back(t345);

  }

  void TearDown() override {
      delete r34;
      delete e43;
      delete t345;
 
  }

  Shape * r34;
  Shape * t345;
  Shape * e43;

  std::vector<TwoDimensionalCoordinate*> triangleVector;
  std::list<Shape *> shapeList ;
  std::list<Shape *> resultList ;
};

TEST_F(FilterShapeTest, AreaFilter)
{
    
    Filter * af1 = new ShapeFilter([](Shape* shape){ return shape->area()<20; });


    resultList = af1->push(shapeList);
    Shape * _front = resultList.front();
    ASSERT_NEAR(12, _front->area(), 0.001);
}

TEST_F(FilterShapeTest, ColorFilter)
{

    Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() < 30;});
    Filter* colorSetter = new ShapeSetter([](Shape* shape) {shape->setColor("black");});
    areaFilter->setNext(colorSetter);

    resultList = areaFilter->push(shapeList);
    Shape * _front = resultList.front();

    ASSERT_EQ("black", _front->color());
}
