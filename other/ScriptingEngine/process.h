#ifndef PROCESS_H
#define PROCESS_H

#include <QVector>
#include <QString>
#include <QFile>

struct InputVariable {
    InputVariable();
    QString variableName;
    QString relation; //better var name, relation between variable and input CAD
//    InputVariable operator= (InputVariable other) const {
//        *this = other;
//    }

};

struct BuildStep {
    QString baseString;
    QVector<InputVariable> stepVariables;
    QString description;
};

struct BuildSequence {
    QVector<BuildStep> sequenceSteps;
};

class Process
{
public:
    Process();
    //Process(QFile sacedProcess);
    QVector<BuildSequence> buildSteps;
    QString description;

};

#endif // PROCESS_H
