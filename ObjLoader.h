#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "lib.h"

class ObjLoader{
public:
    ObjLoader(string filename);//���캯��
    void Draw();//���ƺ���
private:
    vector< vector<GLfloat> >vSets;//��Ŷ���(x,y,z)����
    vector< vector<GLint> >fSets;//������������������
};


#endif
