/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tobj.h
 * Author: zoltan
 *
 * Created on November 17, 2017, 7:21 PM
 */

#ifndef TOBJ_H
#define TOBJ_H
template <class T>
class Tobj {
    T ref;
    int versionNumber;
  public:
    Tobj (T objRef, int version)
      {ref=objRef; versionNumber=version;}
    T getVersion (){return versionNumber;}
    void increase () {versionNumber = versionNumber + 1; }
};


#endif /* TOBJ_H */

