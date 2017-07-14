#include <OpenMS/FORMAT/FeatureXMLFile.h>
#include <OpenMS/KERNEL/FeatureMap.h>

#include <OpenMS/APPLICATIONS/TOPPBase.h>
#include <OpenMS/MATH/STATISTICS/LinearRegression.h>
#include <OpenMS/ANALYSIS/ID/PeptideIndexing.h>

#include <QtCore/QProcess>
#include <OpenMS/SYSTEM/JavaInfo.h>
//#include <QtDeclarative>

using namespace OpenMS;
using namespace Math;
using namespace std;

// Good Java reference class:
// src/OpenMSDev/OpenMS/src/topp/MSGFPlusAdapter.cpp

class DinosaurAdapter :
        public TOPPBase
{
public:
    DinosaurAdapter() :
            TOPPBase("DatabaseFilter", "Filters a protein database (FASTA format) based on identified proteins", false)
    // TOPPBase("DatabaseFilter", "Filters a protein database (FASTA format) based on identified proteins", false)
    {
    }

protected:
    void registerOptionsAndFlags_()
    {
        registerInputFile_("in", "<file>", "", "input files separated by blanks");
        setValidFormats_("in", ListUtils::create<String>("mzML"));
        registerOutputFile_("outdir", "<directory>", "", "directory for detected features");
//        setValidFormats_("out", ListUtils::create<String>("tsv"));

        registerInputFile_("executable", "<file>", "dinosaur.jar",
                           "Dinosaur executable (jar)", true, false, ListUtils::create<String>("skipexists"));

        registerInputFile_("java_executable", "<file>", "java", "Java executable path, if not found in PATH", false, false, ListUtils::create<String>("skipexists"));
        registerIntOption_("java_memory", "<num>", 3500, "Maximum Java heap size (in MB)", false);
        registerIntOption_("java_permgen", "<num>", 0, "Max Java permanent generation heap, Java 7 and below", false, true);
    }

    ExitCodes main_(int, const char **)
    {

//    float out = Math::mean();

        String in = getStringOption_("in");
        String out = getStringOption_("outdir");

        String java_executable = getStringOption_("java_executable");

        writeLog_("Hello world to log!");
        writeLog_("Input: " + in);
        writeLog_("Output: " + out);

        if (!JavaInfo::canRun(java_executable))
        {
            writeLog_("Fatal error: Java not properly provided");
            return EXTERNAL_PROGRAM_ERROR;
        }

        QString java_memory = "-Xmx" + QString::number(getIntOption_("java_memory")) + "m";
        QString executable = getStringOption_("executable").toQString();

        QStringList process_params;
        process_params << java_memory
                       << "-jar" << executable
                       << "--outDir=" + out.toQString()
                       << "--concurrency=" + QString::number(getIntOption_("threads"))
                       << in.toQString();

        // Execute Dinosaur

        int status = QProcess::execute(java_executable.toQString(), process_params);
        if (status != 0)
        {
            writeLog_("Fatal error: Running Dinosaur returned an error code '"
                      + String(status) + "'. Does the Dinosaur jar exist?");
        }

        return EXECUTION_OK;
    }

};

int main(int argc, const char ** argv)
{
    DinosaurAdapter tool;
    return tool.main(argc, argv);
}

/// @endcond
