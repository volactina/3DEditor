#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "lib.h"

class ObjLoader{
public:
    ObjLoader(string filename);//构造函数
    void Draw();//绘制函数
private:
    vector< vector<GLfloat> >vSets;//存放顶点(x,y,z)坐标
    vector< vector<GLint> >fSets;//存放面的三个顶点索引
};


#endif
