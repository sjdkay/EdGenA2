#ifndef __EdProcess_h
#define __EdProcess_h

#include "EdPhysics.h"
#include "EdInput.h"
#include "EdOutput.h"
#include "EdModel.h"
#include "TString.h"


class EdProcess {
    public:
         EdProcess(const char *file,char *file2);
	~EdProcess();

	void Run();

    private:

	EdInput    *finp;
	EdOutput   *fout;
	EdPhysics  *fphy;
	EdModel    *fmodel;

};
#endif//__EdProcess_h
