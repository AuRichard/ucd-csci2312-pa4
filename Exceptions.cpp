#include <iosfwd>
#include "Exceptions.h"

using namespace std;

namespace Gaming {

    void GamingException::setName(string name) {__name = name;}

    ostream &operator<<(ostream &os, const GamingException &ex) {
        os << ex.getName() << endl;
        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
        setName("DimensionsEx");
    }

    unsigned DimensionEx::getExpWidth() const {return __exp_width;}

    unsigned DimensionEx::getExpHeight() const {return __exp_height;}

    unsigned DimensionEx::getWidth() const {return __width;}

    unsigned DimensionEx::getHeight() const {return __height;}


    void InsufficientDimensionsEx::__print_args(ostream &os) const {
        os << "Name: " << getName();
        os << "ExpHeight and Height: " << getExpHeight() << ", " << getHeight() << endl;
        os << "ExpWidth and Width: " << getExpWidth() << ", " << getWidth() << endl;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) : DimensionEx(minWidth, minHeight, width, height)  {setName("InsufficientDimensionsEx");}

    void OutOfBoundsEx::__print_args(ostream &os) const {
        os << getName() << ": " << getExpHeight() << " < " <<  getHeight() << " or " << getExpWidth() << " < " << getWidth() << endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height) {setName("OutOfBoundsEx");
    }

    void PositionEx::__print_args(ostream &os) const {os << getName() << ": " << "(" << __x << "," << __y << ")" << endl;}

    PositionEx::PositionEx(unsigned x, unsigned y) {
        __x = x;
        __y = y;
        setName("PositionEx");
    }

    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(0, 0) {setName("PositionNonemptyEx");}

    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(1, 1) {setName("PositionEmptyEx");}

    void PosVectorEmptyEx::__print_args(ostream &os) const {
        os << getName() << endl;
    }

    PosVectorEmptyEx::PosVectorEmptyEx() {setName("PosVectorEmptyEx");}
}

