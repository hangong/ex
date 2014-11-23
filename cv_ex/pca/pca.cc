#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <iostream>
#include "mypca.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: pca data" << endl;
     return -1;
    }

    CvMLData mldata;
    mldata.read_csv(argv[1]);
    const CvMat* tmp = mldata.get_values();
    if(!tmp)
    {
        cout << "Could not open or find the csv data" << endl;
        return -1;
    }
    Mat data(tmp, true);
    data = data.rowRange(1,data.rows);
    MyPCA ps(data); // perform PCA 
    cout<<"V = "<<endl<<" "<<ps.getV()<<endl;
    cout<<"D = "<<endl<<" "<<ps.getD()<<endl;
    return 0;
}
