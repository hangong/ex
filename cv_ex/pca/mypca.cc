#include "mypca.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/core/core_c.h>

namespace cv{
    MyPCA::MyPCA(InputArray _data)
    { 
        Mat ndata = _data.getMat().clone();
        Mat data_cm; 
        reduce(ndata,data_cm,0,CV_REDUCE_AVG); // compute the column-wise mean 
        // compute zero-centred data
        float *data_cm_ptr = data_cm.ptr<float>(0);
        int nl = ndata.rows;
        int nc = ndata.cols * ndata.channels();
        for(int j = 0;j < nl; j++){
            float *dt = ndata.ptr<float>(j);
            for(int i = 0;i < nc; i++, dt++){
                *dt = *dt - *(data_cm_ptr+i);
            }
        }

        Mat C;
        mulTransposed(ndata,C,true); 
        C = C/float(nl-1);
        eigen(C,D,V);
        X = ndata * V.t();
    }
    
    Mat MyPCA::getV() const
    {
        return V;
    }

    Mat MyPCA::getD() const
    {
        return D;
    }

    Mat MyPCA::getX() const
    {
        return X;
    }
}
