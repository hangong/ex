#ifndef _OPENCV_mypca_HPP_
#define _OPENCV_mypca_HPP_

#ifdef __cplusplus

#include <opencv2/core/core.hpp>
namespace cv {
class MyPCA
{
public:
    MyPCA();
    MyPCA(InputArray _data);
    Mat getV() const;
    Mat getD() const;
    Mat getX() const;
private:
    Mat V;
    Mat X;
    Mat D;
};
}

#endif
#endif
