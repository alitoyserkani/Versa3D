#include "process.h"

Process::Process()
{
    BuildStep holderStep;
    BuildSequence firstBuild; firstBuild.sequenceSteps.push_back(holderStep);
    buildSteps.push_back(firstBuild);
}

InputVariable::InputVariable()
{

}
