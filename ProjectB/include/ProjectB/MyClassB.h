#ifndef PROJECTA_MYCLASSB_H
#define PROJECTA_MYCLASSB_H

#include "ProjectA/MyClassA.h"

class MyClassB : public MyClassA{
 private:
  double fMember;
 public:
  MyClassB();
};
#endif // PROJECTA_MYCLASSB_H
