 
/**g++ -o callpy callpy.cpp -I/usr/include/python2.6 -L/usr/lib64/python2.6/config -lpython2.6**/  
// #include <python3.5m/Python.h>  
#include<Python.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<numpy/arrayobject.h>
#include <pthread.h>
// #include <thread>
// #include</usr/local/lib/python3.5/dist-packages/numpy/core/include/numpy/arrayobject.h>
//初始化 numpy 执行环境，主要是导入包，python2.7用void返回类型，python3.0以上用int返回类型
using namespace std;
int init_numpy()
{
    import_array();
    
}
int main(int argc, char** argv){  
    // 初始化Python  
    //在使用Python系统前，必须使用Py_Initialize对其  
    //进行初始化。它会载入Python的内建模块并添加系统路  
    //径到模块搜索路径中。这个函数没有返回值，检查系统  
    //是否初始化成功需要使用Py_IsInitialized。  
    Py_Initialize(); 
    init_numpy(); 
  
    // 检查初始化是否成功  
    if ( !Py_IsInitialized() ) {  
        return -1;  
    }  
    // 添加当前路径  
    //把输入的字符串作为Python代码直接运行，返回0  
    //表示成功，-1表示有错。大多时候错误都是因为字符串  
    //中有语法错误。  
    PyRun_SimpleString("import sys");  
    // PyRun_SimpleString("print 1");  
    PyRun_SimpleString("print('---import sys---')");   
    PyRun_SimpleString("sys.path.append('./')"); 
    cout<<"pyrun"<<endl; 
    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs;  
  
    // 载入名为pytest的脚本  
    //pName = PyString_FromString("pytest1");  
    pModule = PyImport_ImportModule("pytest1");  
    if ( !pModule ) {  
        printf("can't find pytest.py");  
        getchar();  
        return -1;  
    }  
    pDict = PyModule_GetDict(pModule);  
    if ( !pDict ) {  
        return -1;  
    }  
  
    // 找出函数名为run的函数  
    printf("----------------------\n");  
    pFunc = PyDict_GetItemString(pDict, "run");  
    if ( !pFunc || !PyCallable_Check(pFunc) ) {  
        printf("can't find function [run]");  
        getchar();  
        return -1;  
    }
    cv::Mat img = cv::imread("test.png");
    if(img.empty())
        return -1;
    int x,y,z;
    x = img.rows;
    y = img.cols;
    z = img.channels();
    PyObject *ArgList = PyTuple_New(1);
    unsigned char *CArrays = new unsigned char [x*y*z];
    int iChannels = img.channels();
    int iRows = img.rows;
    int iCols = img.cols * iChannels; 
    // unsigned char *data = (unsigned  char*)malloc(sizeof(unsigned char) * m * n);
    uchar* p;
    int id = -1;
    // int i ,;
    for (int i = 0;i<iRows;i++){
        // 获取第i行的地址
        p=img.ptr<uchar>(i);
        for (int j=0;j<iCols;j++){
            CArrays[++id]=p[j];
        }
    }
    npy_intp Dims[3] = {y,x,z};
    PyObject *PyArray = PyArray_SimpleNewFromData(3, Dims, NPY_UBYTE, CArrays);
    // 将pylist对象放入pytuple对象中
    PyTuple_SetItem(ArgList, 0, PyArray);
    PyObject *pReturn = PyObject_CallObject(pFunc, ArgList);

    Py_DECREF(pModule);
    // 关闭Python
    Py_Finalize(); 
    return 0;
  
}
// int main(int argc, char** argv){
//     test();
//     pthread_t T;
//     int ret = pthread_create(&T, NULL,NULL,NULL);    
// }