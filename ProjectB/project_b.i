%module project_b

%{
#define SWIG_FILE_WITH_INIT
#include <ProjectA/MyClassA.h>
#include "ProjectB/MyClassB.h"
%}

%include <ProjectA/MyClassA.h>
%include "ProjectB/MyClassB.h"

