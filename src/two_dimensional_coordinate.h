#ifndef TWO_DIMENSIONALCOORDINATE_H
#define TWO_DIMENSIONALCOORDINATE_H
class TwoDimensionalCoordinate {
public:
  TwoDimensionalCoordinate(double x, double y){
    this->_x = x;
    this->_y = y;
  }

  double getX() {
    // return x;
    return this->_x;
	}
  double getY() {
    // return y;
    return this->_y;
  }
private:
  double _x,_y;
};
#endif
